/////////////////////////////////////////////////////////////////////////
///@system ִ������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file databaseFactories.h
///@brief���������ɸ��ڴ����ݿ�Ķ��󹤳�
///@history 
///20121227	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef DATABASEFACTORIES_H
#define DATABASEFACTORIES_H

#include "platform.h"
#include "CBaseObject.h"
#include "CConfig.h"
#include "CAVLTree.h"
#include "CHashIndex.h"
#include "customDataType.h"
#include "CDatabaseDataFactory.h"
#include "CTransaction.h"
#include "BaseDataStruct.h"
#include "CDatabaseResource.h"
#include "Allocator.h"

class CDataSyncStatusFactory;
class CDataSyncStatusResource;
class CSystemStatusFactory;
class CSystemStatusResource;
class COrderActionFactory;
class COrderActionResource;
class COrderFactory;
class COrderResource;
class CTradeFactory;
class CTradeResource;
class CPreOrderFactory;
class CPreOrderResource;
class CIndexPreOrderFactory;
class CIndexPreOrderResource;
class CInvestorPositionFactory;
class CInvestorPositionResource;
class CInvestorAccountFactory;
class CInvestorAccountResource;
class CInvestorAccountDepositFactory;
class CInvestorAccountDepositResource;
class CExchangeFactory;
class CExchangeResource;
class CSeatFactory;
class CSeatResource;
class CInstrumentFactory;
class CInstrumentResource;
class CCmbInstrumentDetailFactory;
class CCmbInstrumentDetailResource;
class CClientTradingIDFactory;
class CClientTradingIDResource;
class CInvestorFactory;
class CInvestorResource;
class CInvestorMarginFactory;
class CInvestorMarginResource;
class CInvestorFeeFactory;
class CInvestorFeeResource;
class CUserFactory;
class CUserResource;
class CUserInvestorFactory;
class CUserInvestorResource;
class COrderInsertFailedFactory;
class COrderInsertFailedResource;
class CUserTradingRightFactory;
class CUserTradingRightResource;
class CCurrentTimeFactory;
class CCurrentTimeResource;
class CUserSessionFactory;
class CUserSessionResource;
class CMaxLocalIDFactory;
class CMaxLocalIDResource;
class CBrkUserIDLocalIDFactory;
class CBrkUserIDLocalIDResource;
class CPartClientInsGroupPositionFactory;
class CPartClientInsGroupPositionResource;
class CClientMarginCombTypeFactory;
class CClientMarginCombTypeResource;
class CInstrumentGroupFactory;
class CInstrumentGroupResource;
class CSGEDeferRateFactory;
class CSGEDeferRateResource;
class CInvestorTradingRightFactory;
class CInvestorTradingRightResource;
class CUserIPFactory;
class CUserIPResource;
class CInvestorOptionFeeFactory;
class CInvestorOptionFeeResource;
class CMarketDataFactory;
class CMarketDataResource;
class COrderDelayFactory;
class COrderDelayResource;
class CSystemInfoFactory;
class CSystemInfoResource;

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusFactory��һ������ͬ��״̬��Ķ��󹤳�����������һ������ͬ��״̬��
///ͬʱ�ֽ����������������Է����ѯ��
///	TradingdayIndex
///ʹ�ñ����󹤳���������ɶ�����ͬ��״̬�����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByTradingday��Ψһ�ҵ�����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CDataSyncStatusFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxDataSyncStatus��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CDataSyncStatusFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CDataSyncStatusFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�DataSyncStatus
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�DataSyncStatus���ļ��������������ļ��еĶ���DataSyncStatusCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�DataSyncStatus
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�DataSyncStatus���ļ��������������ļ��еĶ���DataSyncStatusCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CDataSyncStatusResource;

	///��һ��CDataSyncStatus���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pDataSyncStatus	Ҫ�����DataSyncStatus
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CDataSyncStatus *add(CWriteableDataSyncStatus *pDataSyncStatus, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CDataSyncStatus��ֵ
	///@param	pDataSyncStatus	��ˢ�µ�CDataSyncStatus
	///@param	pNewDataSyncStatus	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pDataSyncStatus	  ��Ҫ��ˢ�»���������CDataSyncStatus,����NULL��ʾ����Ҫ������
	///@param	pNewDataSyncStatus	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CDataSyncStatus* addOrUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CDataSyncStatus��ͬʱɾ��������
	///@param	pDataSyncStatus	Ҫɾ����CDataSyncStatus
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CDataSyncStatus *pDataSyncStatus, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CDataSyncStatus
	///@param	pDataSyncStatus	Ҫ��ȡ��CDataSyncStatus
	///@param	pTragetDataSyncStatus	��Ž����CDataSyncStatus
	void retrieve(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pTargetDataSyncStatus);
	
	///��ȡ��һ��CDataSyncStatus
	///@return	�õ��ĵ�һ��CDataSyncStatus�����û�У��򷵻�NULL
	CDataSyncStatus *getFirst(void);
	
	///��ȡ��һ��CDataSyncStatus
	///@return	�õ���һ��CDataSyncStatus�����û�У��򷵻�NULL
	CDataSyncStatus *getNext(void);
	
	///������ȡCDataSyncStatus
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CDataSyncStatusActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CDataSyncStatusActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CDataSyncStatusCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CDataSyncStatusCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CDataSyncStatus
	///@param	TradingDay	������
	///@return	�ҵ���CDataSyncStatus������Ҳ���������NULL
	CDataSyncStatus *findByTradingday( const CReadOnlyDateType&  TradingDay);



private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CDataSyncStatus���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pDataSyncStatus	Ҫ�����DataSyncStatus
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CDataSyncStatus *internalAdd(CWriteableDataSyncStatus *pDataSyncStatus, bool bNoTransaction);
	
	
	///ˢ�¸�CDataSyncStatus�ļ�ֵ
	///@param	pDataSyncStatus	��ˢ�µ�CDataSyncStatus
	///@param	pNewDataSyncStatus	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CDataSyncStatus��ͬʱɾ��������
	///@param	pDataSyncStatus	Ҫɾ����CDataSyncStatus
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CDataSyncStatus *pDataSyncStatus, bool bNoTransaction);
/*
	///���ĳ��CDataSyncStatus�Ƿ����ڱ����󹤳�
	///@param	pDataSyncStatus	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CDataSyncStatus *pDataSyncStatus);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����TradingDay������
	CAVLTree *pTradingdayIndex;
	
	
	
	///����ǰ����
	///@param	pDataSyncStatus	Ҫ�����DataSyncStatus
	virtual void beforeAdd(CWriteableDataSyncStatus *pDataSyncStatus);
	
	///����󴥷�
	///@param	pDataSyncStatus	�Ѿ������DataSyncStatus
	virtual void afterAdd(CDataSyncStatus *pDataSyncStatus);

	///����ǰ����	
	///@param	pDataSyncStatus	��ˢ�µ�CDataSyncStatus
	///@param	pNewDataSyncStatus	�µ�ֵ
	virtual void beforeUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus);
	
	///���º󴥷�
	///@param	pDataSyncStatus	��ˢ�µ�CDataSyncStatus
	virtual void afterUpdate(CDataSyncStatus *pDataSyncStatus);
	
	///ɾ��ǰ����
	///@param	pDataSyncStatus	Ҫɾ����CDataSyncStatus
	virtual void beforeRemove(CDataSyncStatus *pDataSyncStatus);
	
	///ȷ�ϼ���󴥷�
	///@param	pDataSyncStatus	�Ѿ������DataSyncStatus
	virtual void commitAdd(CDataSyncStatus *pDataSyncStatus);

	///ȷ�ϸ��º󴥷�
	///@param	pDataSyncStatus	��ˢ�µ�CDataSyncStatus
	///@param	poldDataSyncStatus	ԭ����ֵ
	virtual void commitUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pOldDataSyncStatus);
	
	///ȷ��ɾ���󴥷�
	///@param	pDataSyncStatus	�Ѿ�ɾ����CDataSyncStatus
	virtual void commitRemove(CWriteableDataSyncStatus *pDataSyncStatus);

	///������صĴ�����
	vector<CDataSyncStatusActionTrigger *> *pActionTriggers;
	vector<CDataSyncStatusCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableDataSyncStatus compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusFactory��һ��QDP״̬��Ķ��󹤳�����������һ��QDP״̬��
///ͬʱ�ֽ����������������Է����ѯ��
///	TradingDay
///ʹ�ñ����󹤳���������ɶ�QDP״̬�����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByTradingDay��Ψһ�ҵ�����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CSystemStatusFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxSystemStatus��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CSystemStatusFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CSystemStatusFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�SystemStatus
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�SystemStatus���ļ��������������ļ��еĶ���SystemStatusCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�SystemStatus
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�SystemStatus���ļ��������������ļ��еĶ���SystemStatusCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CSystemStatusResource;

	///��һ��CSystemStatus���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pSystemStatus	Ҫ�����SystemStatus
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CSystemStatus *add(CWriteableSystemStatus *pSystemStatus, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CSystemStatus��ֵ
	///@param	pSystemStatus	��ˢ�µ�CSystemStatus
	///@param	pNewSystemStatus	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pSystemStatus	  ��Ҫ��ˢ�»���������CSystemStatus,����NULL��ʾ����Ҫ������
	///@param	pNewSystemStatus	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CSystemStatus* addOrUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CSystemStatus��ͬʱɾ��������
	///@param	pSystemStatus	Ҫɾ����CSystemStatus
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CSystemStatus *pSystemStatus, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CSystemStatus
	///@param	pSystemStatus	Ҫ��ȡ��CSystemStatus
	///@param	pTragetSystemStatus	��Ž����CSystemStatus
	void retrieve(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pTargetSystemStatus);
	
	///��ȡ��һ��CSystemStatus
	///@return	�õ��ĵ�һ��CSystemStatus�����û�У��򷵻�NULL
	CSystemStatus *getFirst(void);
	
	///��ȡ��һ��CSystemStatus
	///@return	�õ���һ��CSystemStatus�����û�У��򷵻�NULL
	CSystemStatus *getNext(void);
	
	///������ȡCSystemStatus
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CSystemStatusActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CSystemStatusActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CSystemStatusCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CSystemStatusCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CSystemStatus
	///@param	TradingDay	������
	///@return	�ҵ���CSystemStatus������Ҳ���������NULL
	CSystemStatus *findByTradingDay( const CReadOnlyDateType&  TradingDay);

	///��������Ѱ��
	///@param	TradingDay	������
	///@return	�ҵ���CSystemStatus������Ҳ���������NULL
	CSystemStatus *findByPK( const CReadOnlyDateType&  TradingDay);
	
	///��������Ѱ��CSystemStatus
	///@param	pSystemStatus	Ҫ�ҵ�ֵ
	///@return	�ҵ���CSystemStatus������Ҳ���������NULL
	CSystemStatus *findByPK(CWriteableSystemStatus *pSystemStatus);

	///����������ȡCSystemStatus
	///@param	pSystemStatus	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CSystemStatus������Ҳ���������NULL
	bool retrieveByPK(CWriteableSystemStatus *pSystemStatus);

	///�������������µ�CSystemStatus
	///@param	pSystemStatus	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CSystemStatus���������ʧ�ܣ��򷵻�NULL
	CSystemStatus *addByPK(CWriteableSystemStatus *pSystemStatus, CTransaction *pTransaction=NULL);

	///������������CSystemStatus��ֵ
	///@param	pSystemStatus	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableSystemStatus *pSystemStatus, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CSystemStatus
	///@param	pSystemStatus	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableSystemStatus *pSystemStatus, CTransaction *pTransaction=NULL);


private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CSystemStatus���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pSystemStatus	Ҫ�����SystemStatus
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CSystemStatus *internalAdd(CWriteableSystemStatus *pSystemStatus, bool bNoTransaction);
	
	
	///ˢ�¸�CSystemStatus�ļ�ֵ
	///@param	pSystemStatus	��ˢ�µ�CSystemStatus
	///@param	pNewSystemStatus	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CSystemStatus��ͬʱɾ��������
	///@param	pSystemStatus	Ҫɾ����CSystemStatus
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CSystemStatus *pSystemStatus, bool bNoTransaction);
/*
	///���ĳ��CSystemStatus�Ƿ����ڱ����󹤳�
	///@param	pSystemStatus	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CSystemStatus *pSystemStatus);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����TradingDay������
	CAVLTree *pTradingDay;
	
	
	
	///����ǰ����
	///@param	pSystemStatus	Ҫ�����SystemStatus
	virtual void beforeAdd(CWriteableSystemStatus *pSystemStatus);
	
	///����󴥷�
	///@param	pSystemStatus	�Ѿ������SystemStatus
	virtual void afterAdd(CSystemStatus *pSystemStatus);

	///����ǰ����	
	///@param	pSystemStatus	��ˢ�µ�CSystemStatus
	///@param	pNewSystemStatus	�µ�ֵ
	virtual void beforeUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus);
	
	///���º󴥷�
	///@param	pSystemStatus	��ˢ�µ�CSystemStatus
	virtual void afterUpdate(CSystemStatus *pSystemStatus);
	
	///ɾ��ǰ����
	///@param	pSystemStatus	Ҫɾ����CSystemStatus
	virtual void beforeRemove(CSystemStatus *pSystemStatus);
	
	///ȷ�ϼ���󴥷�
	///@param	pSystemStatus	�Ѿ������SystemStatus
	virtual void commitAdd(CSystemStatus *pSystemStatus);

	///ȷ�ϸ��º󴥷�
	///@param	pSystemStatus	��ˢ�µ�CSystemStatus
	///@param	poldSystemStatus	ԭ����ֵ
	virtual void commitUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pOldSystemStatus);
	
	///ȷ��ɾ���󴥷�
	///@param	pSystemStatus	�Ѿ�ɾ����CSystemStatus
	virtual void commitRemove(CWriteableSystemStatus *pSystemStatus);

	///������صĴ�����
	vector<CSystemStatusActionTrigger *> *pActionTriggers;
	vector<CSystemStatusCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableSystemStatus compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///COrderActionFactory��һ�����������Ķ��󹤳�����������һ������������
///ͬʱ�ֽ����������������Է����ѯ��
///ʹ�ñ����󹤳���������ɶԱ�����������ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	COrderActionFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxOrderAction��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	COrderActionFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~COrderActionFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�OrderAction
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�OrderAction���ļ��������������ļ��еĶ���OrderActionCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�OrderAction
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�OrderAction���ļ��������������ļ��еĶ���OrderActionCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class COrderActionResource;

	///��һ��COrderAction���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pOrderAction	Ҫ�����OrderAction
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	COrderAction *add(CWriteableOrderAction *pOrderAction, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�COrderAction��ֵ
	///@param	pOrderAction	��ˢ�µ�COrderAction
	///@param	pNewOrderAction	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pOrderAction	  ��Ҫ��ˢ�»���������COrderAction,����NULL��ʾ����Ҫ������
	///@param	pNewOrderAction	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	COrderAction* addOrUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��COrderAction��ͬʱɾ��������
	///@param	pOrderAction	Ҫɾ����COrderAction
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(COrderAction *pOrderAction, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��COrderAction
	///@param	pOrderAction	Ҫ��ȡ��COrderAction
	///@param	pTragetOrderAction	��Ž����COrderAction
	void retrieve(COrderAction *pOrderAction, CWriteableOrderAction *pTargetOrderAction);
	
	///��ȡ��һ��COrderAction
	///@return	�õ��ĵ�һ��COrderAction�����û�У��򷵻�NULL
	COrderAction *getFirst(void);
	
	///��ȡ��һ��COrderAction
	///@return	�õ���һ��COrderAction�����û�У��򷵻�NULL
	COrderAction *getNext(void);
	
	///������ȡCOrderAction
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(COrderActionActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(COrderActionActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(COrderActionCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(COrderActionCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///�������ж�Ӧ�ı�����ָ��
	///@param	pFactory	�����Ӧ�ı�����ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllOrder(COrderFactory *pFactory);
	
	///�������ж�Ӧ�ı�����ָ��
	///@param	pFactory	�����Ӧ�ı�����ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllPreOrder(CPreOrderFactory *pFactory);
	
private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��COrderAction���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pOrderAction	Ҫ�����OrderAction
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	COrderAction *internalAdd(CWriteableOrderAction *pOrderAction, bool bNoTransaction);
	
	
	///ˢ�¸�COrderAction�ļ�ֵ
	///@param	pOrderAction	��ˢ�µ�COrderAction
	///@param	pNewOrderAction	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��COrderAction��ͬʱɾ��������
	///@param	pOrderAction	Ҫɾ����COrderAction
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(COrderAction *pOrderAction, bool bNoTransaction);
/*
	///���ĳ��COrderAction�Ƿ����ڱ����󹤳�
	///@param	pOrderAction	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(COrderAction *pOrderAction);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	
	
	
	///����ǰ����
	///@param	pOrderAction	Ҫ�����OrderAction
	virtual void beforeAdd(CWriteableOrderAction *pOrderAction);
	
	///����󴥷�
	///@param	pOrderAction	�Ѿ������OrderAction
	virtual void afterAdd(COrderAction *pOrderAction);

	///����ǰ����	
	///@param	pOrderAction	��ˢ�µ�COrderAction
	///@param	pNewOrderAction	�µ�ֵ
	virtual void beforeUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction);
	
	///���º󴥷�
	///@param	pOrderAction	��ˢ�µ�COrderAction
	virtual void afterUpdate(COrderAction *pOrderAction);
	
	///ɾ��ǰ����
	///@param	pOrderAction	Ҫɾ����COrderAction
	virtual void beforeRemove(COrderAction *pOrderAction);
	
	///ȷ�ϼ���󴥷�
	///@param	pOrderAction	�Ѿ������OrderAction
	virtual void commitAdd(COrderAction *pOrderAction);

	///ȷ�ϸ��º󴥷�
	///@param	pOrderAction	��ˢ�µ�COrderAction
	///@param	poldOrderAction	ԭ����ֵ
	virtual void commitUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pOldOrderAction);
	
	///ȷ��ɾ���󴥷�
	///@param	pOrderAction	�Ѿ�ɾ����COrderAction
	virtual void commitRemove(CWriteableOrderAction *pOrderAction);

	///������صĴ�����
	vector<COrderActionActionTrigger *> *pActionTriggers;
	vector<COrderActionCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableOrderAction compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///COrderFactory��һ��ί�б�Ķ��󹤳�����������һ��ί�б�
///ͬʱ�ֽ����������������Է����ѯ��
///ʹ�ñ����󹤳���������ɶ�ί�б����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByExchangeIDAndOrderSysID��Ψһ�ҵ�����
///		ʹ��findByUserIDAndUserOrderLocalID��Ψһ�ҵ�����
///		ʹ��startFindAllByUserID��findNextAllByUserID��endFindAllByUserID��ɲ�ѯ����
///		ʹ��startFindAllByInvestorID��findNextAllByInvestorID��endFindAllByInvestorID��ɲ�ѯ����
///		ʹ��startFindAllByExchIDInvIDUserID��findNextAllByExchIDInvIDUserID��endFindAllByExchIDInvIDUserID��ɲ�ѯ����
///		ʹ��startFindAllByExchIDInstruIDUserID��findNextAllByExchIDInstruIDUserID��endFindAllByExchIDInstruIDUserID��ɲ�ѯ����
///		ʹ��startFindAll��findNextAll��endFindAll��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	COrderFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxOrder��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	COrderFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~COrderFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�Order
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�Order���ļ��������������ļ��еĶ���OrderCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�Order
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�Order���ļ��������������ļ��еĶ���OrderCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class COrderResource;

	///��һ��COrder���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pOrder	Ҫ�����Order
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	COrder *add(CWriteableOrder *pOrder, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�COrder��ֵ
	///@param	pOrder	��ˢ�µ�COrder
	///@param	pNewOrder	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(COrder *pOrder, CWriteableOrder *pNewOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pOrder	  ��Ҫ��ˢ�»���������COrder,����NULL��ʾ����Ҫ������
	///@param	pNewOrder	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	COrder* addOrUpdate(COrder *pOrder, CWriteableOrder *pNewOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��COrder��ͬʱɾ��������
	///@param	pOrder	Ҫɾ����COrder
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(COrder *pOrder, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��COrder
	///@param	pOrder	Ҫ��ȡ��COrder
	///@param	pTragetOrder	��Ž����COrder
	void retrieve(COrder *pOrder, CWriteableOrder *pTargetOrder);
	
	///��ȡ��һ��COrder
	///@return	�õ��ĵ�һ��COrder�����û�У��򷵻�NULL
	COrder *getFirst(void);
	
	///��ȡ��һ��COrder
	///@return	�õ���һ��COrder�����û�У��򷵻�NULL
	COrder *getNext(void);
	
	///������ȡCOrder
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(COrderActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(COrderActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(COrderCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(COrderCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///�������ж�Ӧ��Ͷ���ߵ�ָ��
	///@param	pFactory	�����Ӧ��Ͷ���ߵ�ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestor(CInvestorFactory *pFactory);
	
	///�������ж�Ӧ�Ľ��ױ����ָ��
	///@param	pFactory	�����Ӧ�Ľ��ױ����ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllClientTradingID(CClientTradingIDFactory *pFactory);
	
	///�������ж�Ӧ���ʻ���ָ��
	///@param	pFactory	�����Ӧ���ʻ���ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorAccount(CInvestorAccountFactory *pFactory);
	
	///�������ж�Ӧ�ĺ�Լ�ֲ���Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ�ֲ���Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorPosition(CInvestorPositionFactory *pFactory);
	
	///�������ж�Ӧ�ĺ�Լ��Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ��Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInstrument(CInstrumentFactory *pFactory);
	
	///�������ж�Ӧ��Ͷ���߱�֤������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ���߱�֤������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorMargin(CInvestorMarginFactory *pFactory);
	
	///�������ж�Ӧ��Ͷ��������������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ��������������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorFee(CInvestorFeeFactory *pFactory);
	
	///�������ж�Ӧ��Ͷ������Ȩ����������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ������Ȩ����������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorOptionFee(CInvestorOptionFeeFactory *pFactory);
	
	///�������ж�Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory);
	
	///Ѱ��COrder
	///@param	ExchangeID	����������
	///@param	OrderSysID	�ʽ��ʺ�
	///@return	�ҵ���COrder������Ҳ���������NULL
	COrder *findByExchangeIDAndOrderSysID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyOrderSysIDType&  OrderSysID);

	///��������Ѱ��
	///@param	ExchangeID	����������
	///@param	OrderSysID	�ʽ��ʺ�
	///@return	�ҵ���COrder������Ҳ���������NULL
	COrder *findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyOrderSysIDType&  OrderSysID);
	
	///��������Ѱ��COrder
	///@param	pOrder	Ҫ�ҵ�ֵ
	///@return	�ҵ���COrder������Ҳ���������NULL
	COrder *findByPK(CWriteableOrder *pOrder);

	///����������ȡCOrder
	///@param	pOrder	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���COrder������Ҳ���������NULL
	bool retrieveByPK(CWriteableOrder *pOrder);

	///�������������µ�COrder
	///@param	pOrder	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����COrder���������ʧ�ܣ��򷵻�NULL
	COrder *addByPK(CWriteableOrder *pOrder, CTransaction *pTransaction=NULL);

	///������������COrder��ֵ
	///@param	pOrder	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableOrder *pOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��COrder
	///@param	pOrder	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableOrder *pOrder, CTransaction *pTransaction=NULL);


	///Ѱ��COrder
	///@param	BrokerID	���͹�˾����
	///@param	UserID	�����û�����
	///@param	UserOrderLocalID	�û����ر������
	///@param	FrontID	ǰ�ú�
	///@param	SessionID	�Ự��
	///@return	�ҵ���COrder������Ҳ���������NULL
	COrder *findByUserIDAndUserOrderLocalID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyUserOrderLocalIDType&  UserOrderLocalID,  const CReadOnlyFrontIDType&  FrontID,  const CReadOnlySessionIDType&  SessionID);



	friend class COrderIteratorAllByUserID;

	///��ʼѰ��COrder
	///@param	UserID	�����û�����
	///@return	���������ĵ�һ��COrder������Ҳ���������NULL
	COrder *startFindAllByUserID( const CReadOnlyUserIDType& UserID);

	///Ѱ����һ������������COrder��������startFindAllByUserID�Ժ�endFindAllByUserID֮ǰ����
	///@return	��һ����������COrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	COrder *findNextAllByUserID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByUserID(void);

	friend class COrderIteratorAllByInvestorID;

	///��ʼѰ��COrder
	///@param	InvestorID	Ͷ���߱��
	///@return	���������ĵ�һ��COrder������Ҳ���������NULL
	COrder *startFindAllByInvestorID( const CReadOnlyInvestorIDType& InvestorID);

	///Ѱ����һ������������COrder��������startFindAllByInvestorID�Ժ�endFindAllByInvestorID֮ǰ����
	///@return	��һ����������COrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	COrder *findNextAllByInvestorID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByInvestorID(void);

	friend class COrderIteratorAllByExchIDInvIDUserID;

	///��ʼѰ��COrder
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱��
	///@param	UserID	�����û�����
	///@return	���������ĵ�һ��COrder������Ҳ���������NULL
	COrder *startFindAllByExchIDInvIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInvestorIDType& InvestorID,  const CReadOnlyUserIDType& UserID);

	///Ѱ����һ������������COrder��������startFindAllByExchIDInvIDUserID�Ժ�endFindAllByExchIDInvIDUserID֮ǰ����
	///@return	��һ����������COrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	COrder *findNextAllByExchIDInvIDUserID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByExchIDInvIDUserID(void);

	friend class COrderIteratorAllByExchIDInstruIDUserID;

	///��ʼѰ��COrder
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ��
	///@param	UserID	�����û�����
	///@return	���������ĵ�һ��COrder������Ҳ���������NULL
	COrder *startFindAllByExchIDInstruIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& InstrumentID,  const CReadOnlyUserIDType& UserID);

	///Ѱ����һ������������COrder��������startFindAllByExchIDInstruIDUserID�Ժ�endFindAllByExchIDInstruIDUserID֮ǰ����
	///@return	��һ����������COrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	COrder *findNextAllByExchIDInstruIDUserID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByExchIDInstruIDUserID(void);

	friend class COrderIteratorAll;

	///��ʼѰ��COrder
	///@return	���������ĵ�һ��COrder������Ҳ���������NULL
	COrder *startFindAll();

	///Ѱ����һ������������COrder��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������COrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	COrder *findNextAll(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAll(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��COrder���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pOrder	Ҫ�����Order
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	COrder *internalAdd(CWriteableOrder *pOrder, bool bNoTransaction);
	
	
	///ˢ�¸�COrder�ļ�ֵ
	///@param	pOrder	��ˢ�µ�COrder
	///@param	pNewOrder	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(COrder *pOrder, CWriteableOrder *pNewOrder, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��COrder��ͬʱɾ��������
	///@param	pOrder	Ҫɾ����COrder
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(COrder *pOrder, bool bNoTransaction);
/*
	///���ĳ��COrder�Ƿ����ڱ����󹤳�
	///@param	pOrder	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(COrder *pOrder);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	
	///����ExchangeIDOrderSysID��hash����
	CHashIndex *pExchangeIDOrderSysIDHashIndex;
	///����UserIDAndUserOrderLocalID��hash����
	CHashIndex *pUserIDAndUserOrderLocalIDHashIndex;
	
	///����UserID����ʱ���洢�Ĳ�ѯ����
	CUserIDType queryUserIDInSearchAllByUserID;
	
	///����UserID����ʱ���洢���һ���ҵ��������ڵ�
	COrder *pLastFoundInSearchAllByUserID;
	///����InvestorID����ʱ���洢�Ĳ�ѯ����
	CInvestorIDType queryInvestorIDInSearchAllByInvestorID;
	
	///����InvestorID����ʱ���洢���һ���ҵ��������ڵ�
	COrder *pLastFoundInSearchAllByInvestorID;
	///����ExchangeID��InvestorID��UserID����ʱ���洢�Ĳ�ѯ����
	CExchangeIDType queryExchangeIDInSearchAllByExchIDInvIDUserID;
	CInvestorIDType queryInvestorIDInSearchAllByExchIDInvIDUserID;
	CUserIDType queryUserIDInSearchAllByExchIDInvIDUserID;
	
	///����ExchangeID��InvestorID��UserID����ʱ���洢���һ���ҵ��������ڵ�
	COrder *pLastFoundInSearchAllByExchIDInvIDUserID;
	///����ExchangeID��InstrumentID��UserID����ʱ���洢�Ĳ�ѯ����
	CExchangeIDType queryExchangeIDInSearchAllByExchIDInstruIDUserID;
	CInstrumentIDType queryInstrumentIDInSearchAllByExchIDInstruIDUserID;
	CUserIDType queryUserIDInSearchAllByExchIDInstruIDUserID;
	
	///����ExchangeID��InstrumentID��UserID����ʱ���洢���һ���ҵ��������ڵ�
	COrder *pLastFoundInSearchAllByExchIDInstruIDUserID;
	///���ռ���ʱ���洢�Ĳ�ѯ����
	
	///���ռ���ʱ���洢���һ���ҵ��������ڵ�
	COrder *pLastFoundInSearchAll;
	
	///����ǰ����
	///@param	pOrder	Ҫ�����Order
	virtual void beforeAdd(CWriteableOrder *pOrder);
	
	///����󴥷�
	///@param	pOrder	�Ѿ������Order
	virtual void afterAdd(COrder *pOrder);

	///����ǰ����	
	///@param	pOrder	��ˢ�µ�COrder
	///@param	pNewOrder	�µ�ֵ
	virtual void beforeUpdate(COrder *pOrder, CWriteableOrder *pNewOrder);
	
	///���º󴥷�
	///@param	pOrder	��ˢ�µ�COrder
	virtual void afterUpdate(COrder *pOrder);
	
	///ɾ��ǰ����
	///@param	pOrder	Ҫɾ����COrder
	virtual void beforeRemove(COrder *pOrder);
	
	///ȷ�ϼ���󴥷�
	///@param	pOrder	�Ѿ������Order
	virtual void commitAdd(COrder *pOrder);

	///ȷ�ϸ��º󴥷�
	///@param	pOrder	��ˢ�µ�COrder
	///@param	poldOrder	ԭ����ֵ
	virtual void commitUpdate(COrder *pOrder, CWriteableOrder *pOldOrder);
	
	///ȷ��ɾ���󴥷�
	///@param	pOrder	�Ѿ�ɾ����COrder
	virtual void commitRemove(CWriteableOrder *pOrder);

	///������صĴ�����
	vector<COrderActionTrigger *> *pActionTriggers;
	vector<COrderCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableOrder compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CTradeFactory��һ���ɽ���Ķ��󹤳�����������һ���ɽ���
///ͬʱ�ֽ����������������Է����ѯ��
///	ExchangeIDTradeIDIndex
///	ExchangeIDTradeIDOrderSysIDIndex
///ʹ�ñ����󹤳���������ɶԳɽ������ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByExchangeIDTradeIDOrderSysID��Ψһ�ҵ�����
///		ʹ��startFindByExchangeIDAndTradeID��findNextByExchangeIDAndTradeID��endFindByExchangeIDAndTradeID��ɲ�ѯ����
///		ʹ��startFindAllByExchIDInvIDUserID��findNextAllByExchIDInvIDUserID��endFindAllByExchIDInvIDUserID��ɲ�ѯ����
///		ʹ��startFindAllByInvestorID��findNextAllByInvestorID��endFindAllByInvestorID��ɲ�ѯ����
///		ʹ��startFindAllByExchIDInstruIDUserID��findNextAllByExchIDInstruIDUserID��endFindAllByExchIDInstruIDUserID��ɲ�ѯ����
///		ʹ��startFindAll��findNextAll��endFindAll��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CTradeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxTrade��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CTradeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CTradeFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�Trade
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�Trade���ļ��������������ļ��еĶ���TradeCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�Trade
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�Trade���ļ��������������ļ��еĶ���TradeCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CTradeResource;

	///��һ��CTrade���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pTrade	Ҫ�����Trade
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CTrade *add(CWriteableTrade *pTrade, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CTrade��ֵ
	///@param	pTrade	��ˢ�µ�CTrade
	///@param	pNewTrade	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CTrade *pTrade, CWriteableTrade *pNewTrade, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pTrade	  ��Ҫ��ˢ�»���������CTrade,����NULL��ʾ����Ҫ������
	///@param	pNewTrade	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CTrade* addOrUpdate(CTrade *pTrade, CWriteableTrade *pNewTrade, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CTrade��ͬʱɾ��������
	///@param	pTrade	Ҫɾ����CTrade
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CTrade *pTrade, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CTrade
	///@param	pTrade	Ҫ��ȡ��CTrade
	///@param	pTragetTrade	��Ž����CTrade
	void retrieve(CTrade *pTrade, CWriteableTrade *pTargetTrade);
	
	///��ȡ��һ��CTrade
	///@return	�õ��ĵ�һ��CTrade�����û�У��򷵻�NULL
	CTrade *getFirst(void);
	
	///��ȡ��һ��CTrade
	///@return	�õ���һ��CTrade�����û�У��򷵻�NULL
	CTrade *getNext(void);
	
	///������ȡCTrade
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CTradeActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CTradeActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CTradeCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CTradeCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CTrade
	///@param	ExchangeID	���������
	///@param	TradeID	�ɽ����
	///@param	OrderSysID	ϵͳ������
	///@return	�ҵ���CTrade������Ҳ���������NULL
	CTrade *findByExchangeIDTradeIDOrderSysID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyTradeIDType&  TradeID,  const CReadOnlyOrderSysIDType&  OrderSysID);

	///��������Ѱ��
	///@param	ExchangeID	���������
	///@param	TradeID	�ɽ����
	///@param	OrderSysID	ϵͳ������
	///@return	�ҵ���CTrade������Ҳ���������NULL
	CTrade *findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyTradeIDType&  TradeID,  const CReadOnlyOrderSysIDType&  OrderSysID);
	
	///��������Ѱ��CTrade
	///@param	pTrade	Ҫ�ҵ�ֵ
	///@return	�ҵ���CTrade������Ҳ���������NULL
	CTrade *findByPK(CWriteableTrade *pTrade);

	///����������ȡCTrade
	///@param	pTrade	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CTrade������Ҳ���������NULL
	bool retrieveByPK(CWriteableTrade *pTrade);

	///�������������µ�CTrade
	///@param	pTrade	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CTrade���������ʧ�ܣ��򷵻�NULL
	CTrade *addByPK(CWriteableTrade *pTrade, CTransaction *pTransaction=NULL);

	///������������CTrade��ֵ
	///@param	pTrade	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableTrade *pTrade, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CTrade
	///@param	pTrade	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableTrade *pTrade, CTransaction *pTransaction=NULL);


	friend class CTradeIteratorByExchangeIDAndTradeID;

	///��ʼѰ��CTrade
	///@param	ExchangeID	����������
	///@param	TradeID	�ɽ����
	///@return	���������ĵ�һ��CTrade������Ҳ���������NULL
	CTrade *startFindByExchangeIDAndTradeID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyTradeIDType& TradeID);

	///Ѱ����һ������������CTrade��������startFindByExchangeIDAndTradeID�Ժ�endFindByExchangeIDAndTradeID֮ǰ����
	///@return	��һ����������CTrade������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CTrade *findNextByExchangeIDAndTradeID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindByExchangeIDAndTradeID(void);

	friend class CTradeIteratorAllByExchIDInvIDUserID;

	///��ʼѰ��CTrade
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱��
	///@param	UserID	�����û�����
	///@return	���������ĵ�һ��CTrade������Ҳ���������NULL
	CTrade *startFindAllByExchIDInvIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInvestorIDType& InvestorID,  const CReadOnlyUserIDType& UserID);

	///Ѱ����һ������������CTrade��������startFindAllByExchIDInvIDUserID�Ժ�endFindAllByExchIDInvIDUserID֮ǰ����
	///@return	��һ����������CTrade������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CTrade *findNextAllByExchIDInvIDUserID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByExchIDInvIDUserID(void);

	friend class CTradeIteratorAllByInvestorID;

	///��ʼѰ��CTrade
	///@param	InvestorID	Ͷ���߱��
	///@return	���������ĵ�һ��CTrade������Ҳ���������NULL
	CTrade *startFindAllByInvestorID( const CReadOnlyInvestorIDType& InvestorID);

	///Ѱ����һ������������CTrade��������startFindAllByInvestorID�Ժ�endFindAllByInvestorID֮ǰ����
	///@return	��һ����������CTrade������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CTrade *findNextAllByInvestorID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByInvestorID(void);

	friend class CTradeIteratorAllByExchIDInstruIDUserID;

	///��ʼѰ��CTrade
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ��
	///@param	UserID	�����û�����
	///@return	���������ĵ�һ��CTrade������Ҳ���������NULL
	CTrade *startFindAllByExchIDInstruIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& InstrumentID,  const CReadOnlyUserIDType& UserID);

	///Ѱ����һ������������CTrade��������startFindAllByExchIDInstruIDUserID�Ժ�endFindAllByExchIDInstruIDUserID֮ǰ����
	///@return	��һ����������CTrade������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CTrade *findNextAllByExchIDInstruIDUserID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByExchIDInstruIDUserID(void);

	friend class CTradeIteratorAll;

	///��ʼѰ��CTrade
	///@return	���������ĵ�һ��CTrade������Ҳ���������NULL
	CTrade *startFindAll();

	///Ѱ����һ������������CTrade��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CTrade������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CTrade *findNextAll(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAll(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CTrade���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pTrade	Ҫ�����Trade
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CTrade *internalAdd(CWriteableTrade *pTrade, bool bNoTransaction);
	
	
	///ˢ�¸�CTrade�ļ�ֵ
	///@param	pTrade	��ˢ�µ�CTrade
	///@param	pNewTrade	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CTrade *pTrade, CWriteableTrade *pNewTrade, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CTrade��ͬʱɾ��������
	///@param	pTrade	Ҫɾ����CTrade
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CTrade *pTrade, bool bNoTransaction);
/*
	///���ĳ��CTrade�Ƿ����ڱ����󹤳�
	///@param	pTrade	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CTrade *pTrade);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����ExchangeID+TradeID������
	CAVLTree *pExchangeIDTradeIDIndex;
	///����ExchangeID+TradeID+OrderSysID������
	CAVLTree *pExchangeIDTradeIDOrderSysIDIndex;
	
	
	///����ExchangeID��TradeID����ʱ���洢�Ĳ�ѯ����
	CExchangeIDType queryExchangeIDInSearchByExchangeIDAndTradeID;
	CTradeIDType queryTradeIDInSearchByExchangeIDAndTradeID;
	
	///����ExchangeID��TradeID����ʱ���洢���һ���ҵ��������ڵ�
	CAVLNode *pLastFoundInSearchByExchangeIDAndTradeID;
	///����ExchangeID��InvestorID��UserID����ʱ���洢�Ĳ�ѯ����
	CExchangeIDType queryExchangeIDInSearchAllByExchIDInvIDUserID;
	CInvestorIDType queryInvestorIDInSearchAllByExchIDInvIDUserID;
	CUserIDType queryUserIDInSearchAllByExchIDInvIDUserID;
	
	///����ExchangeID��InvestorID��UserID����ʱ���洢���һ���ҵ��������ڵ�
	CTrade *pLastFoundInSearchAllByExchIDInvIDUserID;
	///����InvestorID����ʱ���洢�Ĳ�ѯ����
	CInvestorIDType queryInvestorIDInSearchAllByInvestorID;
	
	///����InvestorID����ʱ���洢���һ���ҵ��������ڵ�
	CTrade *pLastFoundInSearchAllByInvestorID;
	///����ExchangeID��InstrumentID��UserID����ʱ���洢�Ĳ�ѯ����
	CExchangeIDType queryExchangeIDInSearchAllByExchIDInstruIDUserID;
	CInstrumentIDType queryInstrumentIDInSearchAllByExchIDInstruIDUserID;
	CUserIDType queryUserIDInSearchAllByExchIDInstruIDUserID;
	
	///����ExchangeID��InstrumentID��UserID����ʱ���洢���һ���ҵ��������ڵ�
	CTrade *pLastFoundInSearchAllByExchIDInstruIDUserID;
	///���ռ���ʱ���洢�Ĳ�ѯ����
	
	///���ռ���ʱ���洢���һ���ҵ��������ڵ�
	CTrade *pLastFoundInSearchAll;
	
	///����ǰ����
	///@param	pTrade	Ҫ�����Trade
	virtual void beforeAdd(CWriteableTrade *pTrade);
	
	///����󴥷�
	///@param	pTrade	�Ѿ������Trade
	virtual void afterAdd(CTrade *pTrade);

	///����ǰ����	
	///@param	pTrade	��ˢ�µ�CTrade
	///@param	pNewTrade	�µ�ֵ
	virtual void beforeUpdate(CTrade *pTrade, CWriteableTrade *pNewTrade);
	
	///���º󴥷�
	///@param	pTrade	��ˢ�µ�CTrade
	virtual void afterUpdate(CTrade *pTrade);
	
	///ɾ��ǰ����
	///@param	pTrade	Ҫɾ����CTrade
	virtual void beforeRemove(CTrade *pTrade);
	
	///ȷ�ϼ���󴥷�
	///@param	pTrade	�Ѿ������Trade
	virtual void commitAdd(CTrade *pTrade);

	///ȷ�ϸ��º󴥷�
	///@param	pTrade	��ˢ�µ�CTrade
	///@param	poldTrade	ԭ����ֵ
	virtual void commitUpdate(CTrade *pTrade, CWriteableTrade *pOldTrade);
	
	///ȷ��ɾ���󴥷�
	///@param	pTrade	�Ѿ�ɾ����CTrade
	virtual void commitRemove(CWriteableTrade *pTrade);

	///������صĴ�����
	vector<CTradeActionTrigger *> *pActionTriggers;
	vector<CTradeCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableTrade compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderFactory��һ��Ԥί�б�Ķ��󹤳�����������һ��Ԥί�б�
///ͬʱ�ֽ����������������Է����ѯ��
///	APIIDAndOrderLocalIDIndex
///	APIIDIndex
///ʹ�ñ����󹤳���������ɶ�Ԥί�б����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByAPIIDAndOrderLocalID��Ψһ�ҵ�����
///		ʹ��findByUserIDAndUserOrderLocalID��Ψһ�ҵ�����
///		ʹ��startFindByAPIID��findNextByAPIID��endFindByAPIID��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CPreOrderFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxPreOrder��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CPreOrderFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CPreOrderFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�PreOrder
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�PreOrder���ļ��������������ļ��еĶ���PreOrderCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�PreOrder
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�PreOrder���ļ��������������ļ��еĶ���PreOrderCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CPreOrderResource;

	///��һ��CPreOrder���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pPreOrder	Ҫ�����PreOrder
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CPreOrder *add(CWriteablePreOrder *pPreOrder, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CPreOrder��ֵ
	///@param	pPreOrder	��ˢ�µ�CPreOrder
	///@param	pNewPreOrder	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pPreOrder	  ��Ҫ��ˢ�»���������CPreOrder,����NULL��ʾ����Ҫ������
	///@param	pNewPreOrder	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CPreOrder* addOrUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CPreOrder��ͬʱɾ��������
	///@param	pPreOrder	Ҫɾ����CPreOrder
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CPreOrder *pPreOrder, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CPreOrder
	///@param	pPreOrder	Ҫ��ȡ��CPreOrder
	///@param	pTragetPreOrder	��Ž����CPreOrder
	void retrieve(CPreOrder *pPreOrder, CWriteablePreOrder *pTargetPreOrder);
	
	///��ȡ��һ��CPreOrder
	///@return	�õ��ĵ�һ��CPreOrder�����û�У��򷵻�NULL
	CPreOrder *getFirst(void);
	
	///��ȡ��һ��CPreOrder
	///@return	�õ���һ��CPreOrder�����û�У��򷵻�NULL
	CPreOrder *getNext(void);
	
	///������ȡCPreOrder
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CPreOrderActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CPreOrderActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CPreOrderCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CPreOrderCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///�������ж�Ӧ��Ͷ���ߵ�ָ��
	///@param	pFactory	�����Ӧ��Ͷ���ߵ�ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestor(CInvestorFactory *pFactory);
	
	///�������ж�Ӧ�Ľ��ױ����ָ��
	///@param	pFactory	�����Ӧ�Ľ��ױ����ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllClientTradingID(CClientTradingIDFactory *pFactory);
	
	///�������ж�Ӧ���ʻ���ָ��
	///@param	pFactory	�����Ӧ���ʻ���ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorAccount(CInvestorAccountFactory *pFactory);
	
	///�������ж�Ӧ�ĺ�Լ�ֲ���Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ�ֲ���Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorPosition(CInvestorPositionFactory *pFactory);
	
	///�������ж�Ӧ�ĺ�Լ��Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ��Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInstrument(CInstrumentFactory *pFactory);
	
	///�������ж�Ӧ��Ͷ���߱�֤������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ���߱�֤������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorMargin(CInvestorMarginFactory *pFactory);
	
	///�������ж�Ӧ��Ͷ��������������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ��������������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorFee(CInvestorFeeFactory *pFactory);
	
	///�������ж�Ӧ��Ͷ������Ȩ����������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ������Ȩ����������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorOptionFee(CInvestorOptionFeeFactory *pFactory);
	
	///�������ж�Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory);
	
	///Ѱ��CPreOrder
	///@param	APIID	ͨ�����
	///@param	OrderLocalID	���ر������
	///@return	�ҵ���CPreOrder������Ҳ���������NULL
	CPreOrder *findByAPIIDAndOrderLocalID( const CReadOnlyNumberType&  APIID,  const CReadOnlyOrderLocalIDType&  OrderLocalID);

	///��������Ѱ��
	///@param	APIID	ͨ�����
	///@param	OrderLocalID	���ر������
	///@return	�ҵ���CPreOrder������Ҳ���������NULL
	CPreOrder *findByPK( const CReadOnlyNumberType&  APIID,  const CReadOnlyOrderLocalIDType&  OrderLocalID);
	
	///��������Ѱ��CPreOrder
	///@param	pPreOrder	Ҫ�ҵ�ֵ
	///@return	�ҵ���CPreOrder������Ҳ���������NULL
	CPreOrder *findByPK(CWriteablePreOrder *pPreOrder);

	///����������ȡCPreOrder
	///@param	pPreOrder	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CPreOrder������Ҳ���������NULL
	bool retrieveByPK(CWriteablePreOrder *pPreOrder);

	///�������������µ�CPreOrder
	///@param	pPreOrder	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CPreOrder���������ʧ�ܣ��򷵻�NULL
	CPreOrder *addByPK(CWriteablePreOrder *pPreOrder, CTransaction *pTransaction=NULL);

	///������������CPreOrder��ֵ
	///@param	pPreOrder	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteablePreOrder *pPreOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CPreOrder
	///@param	pPreOrder	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteablePreOrder *pPreOrder, CTransaction *pTransaction=NULL);


	///Ѱ��CPreOrder
	///@param	BrokerID	���͹�˾����
	///@param	UserID	�����û�����
	///@param	UserOrderLocalID	�û����ر������
	///@param	FrontID	ǰ�ú�
	///@param	SessionID	�Ự��
	///@return	�ҵ���CPreOrder������Ҳ���������NULL
	CPreOrder *findByUserIDAndUserOrderLocalID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyUserOrderLocalIDType&  UserOrderLocalID,  const CReadOnlyFrontIDType&  FrontID,  const CReadOnlySessionIDType&  SessionID);



	friend class CPreOrderIteratorByAPIID;

	///��ʼѰ��CPreOrder
	///@param	APIID	ͨ����
	///@return	���������ĵ�һ��CPreOrder������Ҳ���������NULL
	CPreOrder *startFindByAPIID( const CReadOnlyNumberType& APIID);

	///Ѱ����һ������������CPreOrder��������startFindByAPIID�Ժ�endFindByAPIID֮ǰ����
	///@return	��һ����������CPreOrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CPreOrder *findNextByAPIID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindByAPIID(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CPreOrder���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pPreOrder	Ҫ�����PreOrder
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CPreOrder *internalAdd(CWriteablePreOrder *pPreOrder, bool bNoTransaction);
	
	
	///ˢ�¸�CPreOrder�ļ�ֵ
	///@param	pPreOrder	��ˢ�µ�CPreOrder
	///@param	pNewPreOrder	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CPreOrder��ͬʱɾ��������
	///@param	pPreOrder	Ҫɾ����CPreOrder
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CPreOrder *pPreOrder, bool bNoTransaction);
/*
	///���ĳ��CPreOrder�Ƿ����ڱ����󹤳�
	///@param	pPreOrder	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CPreOrder *pPreOrder);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����APIID+OrderLocalID������
	CAVLTree *pAPIIDAndOrderLocalIDIndex;
	///����APIID������
	CAVLTree *pAPIIDIndex;
	
	///����UserIDAndUserOrderLocalID��hash����
	CHashIndex *pUserIDAndUserOrderLocalIDHashIndex;
	
	///����APIID����ʱ���洢�Ĳ�ѯ����
	CNumberType queryAPIIDInSearchByAPIID;
	
	///����APIID����ʱ���洢���һ���ҵ��������ڵ�
	CAVLNode *pLastFoundInSearchByAPIID;
	
	///����ǰ����
	///@param	pPreOrder	Ҫ�����PreOrder
	virtual void beforeAdd(CWriteablePreOrder *pPreOrder);
	
	///����󴥷�
	///@param	pPreOrder	�Ѿ������PreOrder
	virtual void afterAdd(CPreOrder *pPreOrder);

	///����ǰ����	
	///@param	pPreOrder	��ˢ�µ�CPreOrder
	///@param	pNewPreOrder	�µ�ֵ
	virtual void beforeUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder);
	
	///���º󴥷�
	///@param	pPreOrder	��ˢ�µ�CPreOrder
	virtual void afterUpdate(CPreOrder *pPreOrder);
	
	///ɾ��ǰ����
	///@param	pPreOrder	Ҫɾ����CPreOrder
	virtual void beforeRemove(CPreOrder *pPreOrder);
	
	///ȷ�ϼ���󴥷�
	///@param	pPreOrder	�Ѿ������PreOrder
	virtual void commitAdd(CPreOrder *pPreOrder);

	///ȷ�ϸ��º󴥷�
	///@param	pPreOrder	��ˢ�µ�CPreOrder
	///@param	poldPreOrder	ԭ����ֵ
	virtual void commitUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pOldPreOrder);
	
	///ȷ��ɾ���󴥷�
	///@param	pPreOrder	�Ѿ�ɾ����CPreOrder
	virtual void commitRemove(CWriteablePreOrder *pPreOrder);

	///������صĴ�����
	vector<CPreOrderActionTrigger *> *pActionTriggers;
	vector<CPreOrderCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteablePreOrder compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderFactory��һ������Ԥί�б�Ķ��󹤳�����������һ������Ԥί�б�
///ͬʱ�ֽ����������������Է����ѯ��
///ʹ�ñ����󹤳���������ɶ�����Ԥί�б����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByALLFlds��Ψһ�ҵ�����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CIndexPreOrderFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxIndexPreOrder��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CIndexPreOrderFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CIndexPreOrderFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�IndexPreOrder
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�IndexPreOrder���ļ��������������ļ��еĶ���IndexPreOrderCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�IndexPreOrder
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�IndexPreOrder���ļ��������������ļ��еĶ���IndexPreOrderCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CIndexPreOrderResource;

	///��һ��CIndexPreOrder���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pIndexPreOrder	Ҫ�����IndexPreOrder
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CIndexPreOrder *add(CWriteableIndexPreOrder *pIndexPreOrder, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CIndexPreOrder��ֵ
	///@param	pIndexPreOrder	��ˢ�µ�CIndexPreOrder
	///@param	pNewIndexPreOrder	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pIndexPreOrder	  ��Ҫ��ˢ�»���������CIndexPreOrder,����NULL��ʾ����Ҫ������
	///@param	pNewIndexPreOrder	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CIndexPreOrder* addOrUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CIndexPreOrder��ͬʱɾ��������
	///@param	pIndexPreOrder	Ҫɾ����CIndexPreOrder
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CIndexPreOrder *pIndexPreOrder, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CIndexPreOrder
	///@param	pIndexPreOrder	Ҫ��ȡ��CIndexPreOrder
	///@param	pTragetIndexPreOrder	��Ž����CIndexPreOrder
	void retrieve(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pTargetIndexPreOrder);
	
	///��ȡ��һ��CIndexPreOrder
	///@return	�õ��ĵ�һ��CIndexPreOrder�����û�У��򷵻�NULL
	CIndexPreOrder *getFirst(void);
	
	///��ȡ��һ��CIndexPreOrder
	///@return	�õ���һ��CIndexPreOrder�����û�У��򷵻�NULL
	CIndexPreOrder *getNext(void);
	
	///������ȡCIndexPreOrder
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CIndexPreOrderActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CIndexPreOrderActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CIndexPreOrderCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CIndexPreOrderCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///�������ж�Ӧ��Ͷ���ߵ�ָ��
	///@param	pFactory	�����Ӧ��Ͷ���ߵ�ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestor(CInvestorFactory *pFactory);
	
	///�������ж�Ӧ�Ľ��ױ����ָ��
	///@param	pFactory	�����Ӧ�Ľ��ױ����ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllClientTradingID(CClientTradingIDFactory *pFactory);
	
	///�������ж�Ӧ���ʻ���ָ��
	///@param	pFactory	�����Ӧ���ʻ���ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorAccount(CInvestorAccountFactory *pFactory);
	
	///�������ж�Ӧ�ĺ�Լ��Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ��Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInstrument(CInstrumentFactory *pFactory);
	
	///�������ж�Ӧ��Ͷ���߱�֤������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ���߱�֤������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorMargin(CInvestorMarginFactory *pFactory);
	
	///�������ж�Ӧ��Ͷ��������������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ��������������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorFee(CInvestorFeeFactory *pFactory);
	
	///�������ж�Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory);
	
	///Ѱ��CIndexPreOrder
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱��
	///@param	InstrumentID	��Լ���
	///@param	HedgeFlag	Ͷ���ױ���־
	///@return	�ҵ���CIndexPreOrder������Ҳ���������NULL
	CIndexPreOrder *findByALLFlds( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyHedgeFlagType&  HedgeFlag);

	///��������Ѱ��
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱��
	///@param	InstrumentID	��Լ���
	///@param	HedgeFlag	Ͷ���ױ���־
	///@return	�ҵ���CIndexPreOrder������Ҳ���������NULL
	CIndexPreOrder *findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyHedgeFlagType&  HedgeFlag);
	
	///��������Ѱ��CIndexPreOrder
	///@param	pIndexPreOrder	Ҫ�ҵ�ֵ
	///@return	�ҵ���CIndexPreOrder������Ҳ���������NULL
	CIndexPreOrder *findByPK(CWriteableIndexPreOrder *pIndexPreOrder);

	///����������ȡCIndexPreOrder
	///@param	pIndexPreOrder	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CIndexPreOrder������Ҳ���������NULL
	bool retrieveByPK(CWriteableIndexPreOrder *pIndexPreOrder);

	///�������������µ�CIndexPreOrder
	///@param	pIndexPreOrder	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CIndexPreOrder���������ʧ�ܣ��򷵻�NULL
	CIndexPreOrder *addByPK(CWriteableIndexPreOrder *pIndexPreOrder, CTransaction *pTransaction=NULL);

	///������������CIndexPreOrder��ֵ
	///@param	pIndexPreOrder	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableIndexPreOrder *pIndexPreOrder, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CIndexPreOrder
	///@param	pIndexPreOrder	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableIndexPreOrder *pIndexPreOrder, CTransaction *pTransaction=NULL);


private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CIndexPreOrder���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pIndexPreOrder	Ҫ�����IndexPreOrder
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CIndexPreOrder *internalAdd(CWriteableIndexPreOrder *pIndexPreOrder, bool bNoTransaction);
	
	
	///ˢ�¸�CIndexPreOrder�ļ�ֵ
	///@param	pIndexPreOrder	��ˢ�µ�CIndexPreOrder
	///@param	pNewIndexPreOrder	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CIndexPreOrder��ͬʱɾ��������
	///@param	pIndexPreOrder	Ҫɾ����CIndexPreOrder
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CIndexPreOrder *pIndexPreOrder, bool bNoTransaction);
/*
	///���ĳ��CIndexPreOrder�Ƿ����ڱ����󹤳�
	///@param	pIndexPreOrder	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CIndexPreOrder *pIndexPreOrder);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	
	///����ALLFlds��hash����
	CHashIndex *pALLFldsHashIndex;
	
	
	///����ǰ����
	///@param	pIndexPreOrder	Ҫ�����IndexPreOrder
	virtual void beforeAdd(CWriteableIndexPreOrder *pIndexPreOrder);
	
	///����󴥷�
	///@param	pIndexPreOrder	�Ѿ������IndexPreOrder
	virtual void afterAdd(CIndexPreOrder *pIndexPreOrder);

	///����ǰ����	
	///@param	pIndexPreOrder	��ˢ�µ�CIndexPreOrder
	///@param	pNewIndexPreOrder	�µ�ֵ
	virtual void beforeUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder);
	
	///���º󴥷�
	///@param	pIndexPreOrder	��ˢ�µ�CIndexPreOrder
	virtual void afterUpdate(CIndexPreOrder *pIndexPreOrder);
	
	///ɾ��ǰ����
	///@param	pIndexPreOrder	Ҫɾ����CIndexPreOrder
	virtual void beforeRemove(CIndexPreOrder *pIndexPreOrder);
	
	///ȷ�ϼ���󴥷�
	///@param	pIndexPreOrder	�Ѿ������IndexPreOrder
	virtual void commitAdd(CIndexPreOrder *pIndexPreOrder);

	///ȷ�ϸ��º󴥷�
	///@param	pIndexPreOrder	��ˢ�µ�CIndexPreOrder
	///@param	poldIndexPreOrder	ԭ����ֵ
	virtual void commitUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pOldIndexPreOrder);
	
	///ȷ��ɾ���󴥷�
	///@param	pIndexPreOrder	�Ѿ�ɾ����CIndexPreOrder
	virtual void commitRemove(CWriteableIndexPreOrder *pIndexPreOrder);

	///������صĴ�����
	vector<CIndexPreOrderActionTrigger *> *pActionTriggers;
	vector<CIndexPreOrderCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableIndexPreOrder compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionFactory��һ���ֱֲ�Ķ��󹤳�����������һ���ֱֲ�
///ͬʱ�ֽ����������������Է����ѯ��
///	BrkIDExIDInvIDInsIDDirHedIndex
///	ExIDAndInstrumentIDIndex
///	InvestorIDIndex
///ʹ�ñ����󹤳���������ɶԳֱֲ����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrkIDExIDInvIDInsDirHed��Ψһ�ҵ�����
///		ʹ��startFindAllByExIDAndInstrumentID��findNextAllByExIDAndInstrumentID��endFindAllByExIDAndInstrumentID��ɲ�ѯ����
///		ʹ��startFindByInvestorID��findNextByInvestorID��endFindByInvestorID��ɲ�ѯ����
///		ʹ��startFindAllByBrokerID��findNextAllByBrokerID��endFindAllByBrokerID��ɲ�ѯ����
///		ʹ��startFindAllByInstrumentID��findNextAllByInstrumentID��endFindAllByInstrumentID��ɲ�ѯ����
///		ʹ��startFindAllByExchangeID��findNextAllByExchangeID��endFindAllByExchangeID��ɲ�ѯ����
///		ʹ��startFindAllByInvestorIDAndInstrumentID��findNextAllByInvestorIDAndInstrumentID��endFindAllByInvestorIDAndInstrumentID��ɲ�ѯ����
///		ʹ��startFindAll��findNextAll��endFindAll��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInvestorPositionFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxInvestorPosition��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInvestorPositionFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorPositionFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�InvestorPosition
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�InvestorPosition���ļ��������������ļ��еĶ���InvestorPositionCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�InvestorPosition
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�InvestorPosition���ļ��������������ļ��еĶ���InvestorPositionCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CInvestorPositionResource;

	///��һ��CInvestorPosition���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInvestorPosition	Ҫ�����InvestorPosition
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInvestorPosition *add(CWriteableInvestorPosition *pInvestorPosition, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CInvestorPosition��ֵ
	///@param	pInvestorPosition	��ˢ�µ�CInvestorPosition
	///@param	pNewInvestorPosition	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pInvestorPosition	  ��Ҫ��ˢ�»���������CInvestorPosition,����NULL��ʾ����Ҫ������
	///@param	pNewInvestorPosition	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CInvestorPosition* addOrUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CInvestorPosition��ͬʱɾ��������
	///@param	pInvestorPosition	Ҫɾ����CInvestorPosition
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CInvestorPosition *pInvestorPosition, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CInvestorPosition
	///@param	pInvestorPosition	Ҫ��ȡ��CInvestorPosition
	///@param	pTragetInvestorPosition	��Ž����CInvestorPosition
	void retrieve(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pTargetInvestorPosition);
	
	///��ȡ��һ��CInvestorPosition
	///@return	�õ��ĵ�һ��CInvestorPosition�����û�У��򷵻�NULL
	CInvestorPosition *getFirst(void);
	
	///��ȡ��һ��CInvestorPosition
	///@return	�õ���һ��CInvestorPosition�����û�У��򷵻�NULL
	CInvestorPosition *getNext(void);
	
	///������ȡCInvestorPosition
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CInvestorPositionActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CInvestorPositionActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CInvestorPositionCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CInvestorPositionCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CInvestorPosition
	///@param	BrokerID	���͹�˾����
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱��
	///@param	InstrumentID	��Լ���
	///@param	Direction	��շ���
	///@param	HedgeFlag	Ͷ���ױ���־
	///@return	�ҵ���CInvestorPosition������Ҳ���������NULL
	CInvestorPosition *findByBrkIDExIDInvIDInsDirHed( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyDirectionType&  Direction,  const CReadOnlyHedgeFlagType&  HedgeFlag);

	///��������Ѱ��
	///@param	BrokerID	���͹�˾����
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱��
	///@param	InstrumentID	��Լ���
	///@param	Direction	��շ���
	///@param	HedgeFlag	Ͷ���ױ���־
	///@return	�ҵ���CInvestorPosition������Ҳ���������NULL
	CInvestorPosition *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyDirectionType&  Direction,  const CReadOnlyHedgeFlagType&  HedgeFlag);
	
	///��������Ѱ��CInvestorPosition
	///@param	pInvestorPosition	Ҫ�ҵ�ֵ
	///@return	�ҵ���CInvestorPosition������Ҳ���������NULL
	CInvestorPosition *findByPK(CWriteableInvestorPosition *pInvestorPosition);

	///����������ȡCInvestorPosition
	///@param	pInvestorPosition	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CInvestorPosition������Ҳ���������NULL
	bool retrieveByPK(CWriteableInvestorPosition *pInvestorPosition);

	///�������������µ�CInvestorPosition
	///@param	pInvestorPosition	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CInvestorPosition���������ʧ�ܣ��򷵻�NULL
	CInvestorPosition *addByPK(CWriteableInvestorPosition *pInvestorPosition, CTransaction *pTransaction=NULL);

	///������������CInvestorPosition��ֵ
	///@param	pInvestorPosition	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableInvestorPosition *pInvestorPosition, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CInvestorPosition
	///@param	pInvestorPosition	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableInvestorPosition *pInvestorPosition, CTransaction *pTransaction=NULL);


	friend class CInvestorPositionIteratorAllByExIDAndInstrumentID;

	///��ʼѰ��CInvestorPosition
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ���
	///@return	���������ĵ�һ��CInvestorPosition������Ҳ���������NULL
	CInvestorPosition *startFindAllByExIDAndInstrumentID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& InstrumentID);

	///Ѱ����һ������������CInvestorPosition��������startFindAllByExIDAndInstrumentID�Ժ�endFindAllByExIDAndInstrumentID֮ǰ����
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorPosition *findNextAllByExIDAndInstrumentID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByExIDAndInstrumentID(void);

	friend class CInvestorPositionIteratorByInvestorID;

	///��ʼѰ��CInvestorPosition
	///@param	InvestorID	Ͷ���ߺ�
	///@return	���������ĵ�һ��CInvestorPosition������Ҳ���������NULL
	CInvestorPosition *startFindByInvestorID( const CReadOnlyInvestorIDType& InvestorID);

	///Ѱ����һ������������CInvestorPosition��������startFindByInvestorID�Ժ�endFindByInvestorID֮ǰ����
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorPosition *findNextByInvestorID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindByInvestorID(void);

	friend class CInvestorPositionIteratorAllByBrokerID;

	///��ʼѰ��CInvestorPosition
	///@param	BrokerID	���͹�˾����
	///@return	���������ĵ�һ��CInvestorPosition������Ҳ���������NULL
	CInvestorPosition *startFindAllByBrokerID( const CReadOnlyBrokerIDType& BrokerID);

	///Ѱ����һ������������CInvestorPosition��������startFindAllByBrokerID�Ժ�endFindAllByBrokerID֮ǰ����
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorPosition *findNextAllByBrokerID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByBrokerID(void);

	friend class CInvestorPositionIteratorAllByInstrumentID;

	///��ʼѰ��CInvestorPosition
	///@param	InstrumentID	��Լ����
	///@return	���������ĵ�һ��CInvestorPosition������Ҳ���������NULL
	CInvestorPosition *startFindAllByInstrumentID( const CReadOnlyInstrumentIDType& InstrumentID);

	///Ѱ����һ������������CInvestorPosition��������startFindAllByInstrumentID�Ժ�endFindAllByInstrumentID֮ǰ����
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorPosition *findNextAllByInstrumentID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByInstrumentID(void);

	friend class CInvestorPositionIteratorAllByExchangeID;

	///��ʼѰ��CInvestorPosition
	///@param	ExchangeID	���������
	///@return	���������ĵ�һ��CInvestorPosition������Ҳ���������NULL
	CInvestorPosition *startFindAllByExchangeID( const CReadOnlyExchangeIDType& ExchangeID);

	///Ѱ����һ������������CInvestorPosition��������startFindAllByExchangeID�Ժ�endFindAllByExchangeID֮ǰ����
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorPosition *findNextAllByExchangeID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByExchangeID(void);

	friend class CInvestorPositionIteratorAllByInvestorIDAndInstrumentID;

	///��ʼѰ��CInvestorPosition
	///@param	InvestorID	�ͻ���
	///@param	InstrumentID	��Լ����
	///@return	���������ĵ�һ��CInvestorPosition������Ҳ���������NULL
	CInvestorPosition *startFindAllByInvestorIDAndInstrumentID( const CReadOnlyInvestorIDType& InvestorID,  const CReadOnlyInstrumentIDType& InstrumentID);

	///Ѱ����һ������������CInvestorPosition��������startFindAllByInvestorIDAndInstrumentID�Ժ�endFindAllByInvestorIDAndInstrumentID֮ǰ����
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorPosition *findNextAllByInvestorIDAndInstrumentID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByInvestorIDAndInstrumentID(void);

	friend class CInvestorPositionIteratorAll;

	///��ʼѰ��CInvestorPosition
	///@return	���������ĵ�һ��CInvestorPosition������Ҳ���������NULL
	CInvestorPosition *startFindAll();

	///Ѱ����һ������������CInvestorPosition��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorPosition *findNextAll(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAll(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CInvestorPosition���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInvestorPosition	Ҫ�����InvestorPosition
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInvestorPosition *internalAdd(CWriteableInvestorPosition *pInvestorPosition, bool bNoTransaction);
	
	
	///ˢ�¸�CInvestorPosition�ļ�ֵ
	///@param	pInvestorPosition	��ˢ�µ�CInvestorPosition
	///@param	pNewInvestorPosition	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CInvestorPosition��ͬʱɾ��������
	///@param	pInvestorPosition	Ҫɾ����CInvestorPosition
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CInvestorPosition *pInvestorPosition, bool bNoTransaction);
/*
	///���ĳ��CInvestorPosition�Ƿ����ڱ����󹤳�
	///@param	pInvestorPosition	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CInvestorPosition *pInvestorPosition);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����BrokerID+ExchangeID+InvestorID+InstrumentID+Direction+HedgeFlag������
	CAVLTree *pBrkIDExIDInvIDInsIDDirHedIndex;
	///����ExchangeID+InstrumentID������
	CAVLTree *pExIDAndInstrumentIDIndex;
	///����InvestorID������
	CAVLTree *pInvestorIDIndex;
	
	
	///����ExchangeID��InstrumentID����ʱ���洢�Ĳ�ѯ����
	CExchangeIDType queryExchangeIDInSearchAllByExIDAndInstrumentID;
	CInstrumentIDType queryInstrumentIDInSearchAllByExIDAndInstrumentID;
	
	///����ExchangeID��InstrumentID����ʱ���洢���һ���ҵ��������ڵ�
	CAVLNode *pLastFoundInSearchAllByExIDAndInstrumentID;
	///����InvestorID����ʱ���洢�Ĳ�ѯ����
	CInvestorIDType queryInvestorIDInSearchByInvestorID;
	
	///����InvestorID����ʱ���洢���һ���ҵ��������ڵ�
	CAVLNode *pLastFoundInSearchByInvestorID;
	///����BrokerID����ʱ���洢�Ĳ�ѯ����
	CBrokerIDType queryBrokerIDInSearchAllByBrokerID;
	
	///����BrokerID����ʱ���洢���һ���ҵ��������ڵ�
	CInvestorPosition *pLastFoundInSearchAllByBrokerID;
	///����InstrumentID����ʱ���洢�Ĳ�ѯ����
	CInstrumentIDType queryInstrumentIDInSearchAllByInstrumentID;
	
	///����InstrumentID����ʱ���洢���һ���ҵ��������ڵ�
	CInvestorPosition *pLastFoundInSearchAllByInstrumentID;
	///����ExchangeID����ʱ���洢�Ĳ�ѯ����
	CExchangeIDType queryExchangeIDInSearchAllByExchangeID;
	
	///����ExchangeID����ʱ���洢���һ���ҵ��������ڵ�
	CInvestorPosition *pLastFoundInSearchAllByExchangeID;
	///����InvestorID��InstrumentID����ʱ���洢�Ĳ�ѯ����
	CInvestorIDType queryInvestorIDInSearchAllByInvestorIDAndInstrumentID;
	CInstrumentIDType queryInstrumentIDInSearchAllByInvestorIDAndInstrumentID;
	
	///����InvestorID��InstrumentID����ʱ���洢���һ���ҵ��������ڵ�
	CInvestorPosition *pLastFoundInSearchAllByInvestorIDAndInstrumentID;
	///���ռ���ʱ���洢�Ĳ�ѯ����
	
	///���ռ���ʱ���洢���һ���ҵ��������ڵ�
	CInvestorPosition *pLastFoundInSearchAll;
	
	///����ǰ����
	///@param	pInvestorPosition	Ҫ�����InvestorPosition
	virtual void beforeAdd(CWriteableInvestorPosition *pInvestorPosition);
	
	///����󴥷�
	///@param	pInvestorPosition	�Ѿ������InvestorPosition
	virtual void afterAdd(CInvestorPosition *pInvestorPosition);

	///����ǰ����	
	///@param	pInvestorPosition	��ˢ�µ�CInvestorPosition
	///@param	pNewInvestorPosition	�µ�ֵ
	virtual void beforeUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition);
	
	///���º󴥷�
	///@param	pInvestorPosition	��ˢ�µ�CInvestorPosition
	virtual void afterUpdate(CInvestorPosition *pInvestorPosition);
	
	///ɾ��ǰ����
	///@param	pInvestorPosition	Ҫɾ����CInvestorPosition
	virtual void beforeRemove(CInvestorPosition *pInvestorPosition);
	
	///ȷ�ϼ���󴥷�
	///@param	pInvestorPosition	�Ѿ������InvestorPosition
	virtual void commitAdd(CInvestorPosition *pInvestorPosition);

	///ȷ�ϸ��º󴥷�
	///@param	pInvestorPosition	��ˢ�µ�CInvestorPosition
	///@param	poldInvestorPosition	ԭ����ֵ
	virtual void commitUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pOldInvestorPosition);
	
	///ȷ��ɾ���󴥷�
	///@param	pInvestorPosition	�Ѿ�ɾ����CInvestorPosition
	virtual void commitRemove(CWriteableInvestorPosition *pInvestorPosition);

	///������صĴ�����
	vector<CInvestorPositionActionTrigger *> *pActionTriggers;
	vector<CInvestorPositionCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableInvestorPosition compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountFactory��һ���˻�ʵʱ�ʽ��Ķ��󹤳�����������һ���˻�ʵʱ�ʽ��
///ͬʱ�ֽ����������������Է����ѯ��
///	BrokerIDAccountIDIndex
///	BrokerIDInvestorIDIndex
///ʹ�ñ����󹤳���������ɶ��˻�ʵʱ�ʽ�����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrokerIDAccountID��Ψһ�ҵ�����
///		ʹ��startFindAllByInvestorID��findNextAllByInvestorID��endFindAllByInvestorID��ɲ�ѯ����
///		ʹ��findByBrokerIDInvestorID��Ψһ�ҵ�����
///		ʹ��startFindAllByBrokerID��findNextAllByBrokerID��endFindAllByBrokerID��ɲ�ѯ����
///		ʹ��startFindAll��findNextAll��endFindAll��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInvestorAccountFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxInvestorAccount��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInvestorAccountFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorAccountFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�InvestorAccount
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�InvestorAccount���ļ��������������ļ��еĶ���InvestorAccountCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�InvestorAccount
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�InvestorAccount���ļ��������������ļ��еĶ���InvestorAccountCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CInvestorAccountResource;

	///��һ��CInvestorAccount���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInvestorAccount	Ҫ�����InvestorAccount
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInvestorAccount *add(CWriteableInvestorAccount *pInvestorAccount, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CInvestorAccount��ֵ
	///@param	pInvestorAccount	��ˢ�µ�CInvestorAccount
	///@param	pNewInvestorAccount	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pInvestorAccount	  ��Ҫ��ˢ�»���������CInvestorAccount,����NULL��ʾ����Ҫ������
	///@param	pNewInvestorAccount	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CInvestorAccount* addOrUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CInvestorAccount��ͬʱɾ��������
	///@param	pInvestorAccount	Ҫɾ����CInvestorAccount
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CInvestorAccount *pInvestorAccount, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CInvestorAccount
	///@param	pInvestorAccount	Ҫ��ȡ��CInvestorAccount
	///@param	pTragetInvestorAccount	��Ž����CInvestorAccount
	void retrieve(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pTargetInvestorAccount);
	
	///��ȡ��һ��CInvestorAccount
	///@return	�õ��ĵ�һ��CInvestorAccount�����û�У��򷵻�NULL
	CInvestorAccount *getFirst(void);
	
	///��ȡ��һ��CInvestorAccount
	///@return	�õ���һ��CInvestorAccount�����û�У��򷵻�NULL
	CInvestorAccount *getNext(void);
	
	///������ȡCInvestorAccount
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CInvestorAccountActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CInvestorAccountActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CInvestorAccountCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CInvestorAccountCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CInvestorAccount
	///@param	BrokerID	�����̱��
	///@param	AccountID	�ʽ��ʺ�
	///@return	�ҵ���CInvestorAccount������Ҳ���������NULL
	CInvestorAccount *findByBrokerIDAccountID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyAccountIDType&  AccountID);

	///��������Ѱ��
	///@param	BrokerID	�����̱��
	///@param	AccountID	�ʽ��ʺ�
	///@return	�ҵ���CInvestorAccount������Ҳ���������NULL
	CInvestorAccount *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyAccountIDType&  AccountID);
	
	///��������Ѱ��CInvestorAccount
	///@param	pInvestorAccount	Ҫ�ҵ�ֵ
	///@return	�ҵ���CInvestorAccount������Ҳ���������NULL
	CInvestorAccount *findByPK(CWriteableInvestorAccount *pInvestorAccount);

	///����������ȡCInvestorAccount
	///@param	pInvestorAccount	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CInvestorAccount������Ҳ���������NULL
	bool retrieveByPK(CWriteableInvestorAccount *pInvestorAccount);

	///�������������µ�CInvestorAccount
	///@param	pInvestorAccount	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CInvestorAccount���������ʧ�ܣ��򷵻�NULL
	CInvestorAccount *addByPK(CWriteableInvestorAccount *pInvestorAccount, CTransaction *pTransaction=NULL);

	///������������CInvestorAccount��ֵ
	///@param	pInvestorAccount	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableInvestorAccount *pInvestorAccount, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CInvestorAccount
	///@param	pInvestorAccount	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableInvestorAccount *pInvestorAccount, CTransaction *pTransaction=NULL);


	friend class CInvestorAccountIteratorAllByInvestorID;

	///��ʼѰ��CInvestorAccount
	///@param	InvestorID	Ͷ���߱��
	///@return	���������ĵ�һ��CInvestorAccount������Ҳ���������NULL
	CInvestorAccount *startFindAllByInvestorID( const CReadOnlyInvestorIDType& InvestorID);

	///Ѱ����һ������������CInvestorAccount��������startFindAllByInvestorID�Ժ�endFindAllByInvestorID֮ǰ����
	///@return	��һ����������CInvestorAccount������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorAccount *findNextAllByInvestorID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByInvestorID(void);

	///Ѱ��CInvestorAccount
	///@param	BrokerID	�����̱��
	///@param	InvestorID	Ͷ���߱��
	///@return	�ҵ���CInvestorAccount������Ҳ���������NULL
	CInvestorAccount *findByBrokerIDInvestorID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInvestorIDType&  InvestorID);



	friend class CInvestorAccountIteratorAllByBrokerID;

	///��ʼѰ��CInvestorAccount
	///@param	BrokerID	���͹�˾����
	///@return	���������ĵ�һ��CInvestorAccount������Ҳ���������NULL
	CInvestorAccount *startFindAllByBrokerID( const CReadOnlyBrokerIDType& BrokerID);

	///Ѱ����һ������������CInvestorAccount��������startFindAllByBrokerID�Ժ�endFindAllByBrokerID֮ǰ����
	///@return	��һ����������CInvestorAccount������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorAccount *findNextAllByBrokerID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByBrokerID(void);

	friend class CInvestorAccountIteratorAll;

	///��ʼѰ��CInvestorAccount
	///@return	���������ĵ�һ��CInvestorAccount������Ҳ���������NULL
	CInvestorAccount *startFindAll();

	///Ѱ����һ������������CInvestorAccount��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CInvestorAccount������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorAccount *findNextAll(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAll(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CInvestorAccount���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInvestorAccount	Ҫ�����InvestorAccount
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInvestorAccount *internalAdd(CWriteableInvestorAccount *pInvestorAccount, bool bNoTransaction);
	
	
	///ˢ�¸�CInvestorAccount�ļ�ֵ
	///@param	pInvestorAccount	��ˢ�µ�CInvestorAccount
	///@param	pNewInvestorAccount	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CInvestorAccount��ͬʱɾ��������
	///@param	pInvestorAccount	Ҫɾ����CInvestorAccount
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CInvestorAccount *pInvestorAccount, bool bNoTransaction);
/*
	///���ĳ��CInvestorAccount�Ƿ����ڱ����󹤳�
	///@param	pInvestorAccount	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CInvestorAccount *pInvestorAccount);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����BrokerID+AccountID������
	CAVLTree *pBrokerIDAccountIDIndex;
	///����BrokerID+InvestorID������
	CAVLTree *pBrokerIDInvestorIDIndex;
	
	
	///����InvestorID����ʱ���洢�Ĳ�ѯ����
	CInvestorIDType queryInvestorIDInSearchAllByInvestorID;
	
	///����InvestorID����ʱ���洢���һ���ҵ��������ڵ�
	CInvestorAccount *pLastFoundInSearchAllByInvestorID;
	///����BrokerID����ʱ���洢�Ĳ�ѯ����
	CBrokerIDType queryBrokerIDInSearchAllByBrokerID;
	
	///����BrokerID����ʱ���洢���һ���ҵ��������ڵ�
	CInvestorAccount *pLastFoundInSearchAllByBrokerID;
	///���ռ���ʱ���洢�Ĳ�ѯ����
	
	///���ռ���ʱ���洢���һ���ҵ��������ڵ�
	CInvestorAccount *pLastFoundInSearchAll;
	
	///����ǰ����
	///@param	pInvestorAccount	Ҫ�����InvestorAccount
	virtual void beforeAdd(CWriteableInvestorAccount *pInvestorAccount);
	
	///����󴥷�
	///@param	pInvestorAccount	�Ѿ������InvestorAccount
	virtual void afterAdd(CInvestorAccount *pInvestorAccount);

	///����ǰ����	
	///@param	pInvestorAccount	��ˢ�µ�CInvestorAccount
	///@param	pNewInvestorAccount	�µ�ֵ
	virtual void beforeUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount);
	
	///���º󴥷�
	///@param	pInvestorAccount	��ˢ�µ�CInvestorAccount
	virtual void afterUpdate(CInvestorAccount *pInvestorAccount);
	
	///ɾ��ǰ����
	///@param	pInvestorAccount	Ҫɾ����CInvestorAccount
	virtual void beforeRemove(CInvestorAccount *pInvestorAccount);
	
	///ȷ�ϼ���󴥷�
	///@param	pInvestorAccount	�Ѿ������InvestorAccount
	virtual void commitAdd(CInvestorAccount *pInvestorAccount);

	///ȷ�ϸ��º󴥷�
	///@param	pInvestorAccount	��ˢ�µ�CInvestorAccount
	///@param	poldInvestorAccount	ԭ����ֵ
	virtual void commitUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pOldInvestorAccount);
	
	///ȷ��ɾ���󴥷�
	///@param	pInvestorAccount	�Ѿ�ɾ����CInvestorAccount
	virtual void commitRemove(CWriteableInvestorAccount *pInvestorAccount);

	///������صĴ�����
	vector<CInvestorAccountActionTrigger *> *pActionTriggers;
	vector<CInvestorAccountCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableInvestorAccount compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositFactory��һ���˻�ʵʱ������Ķ��󹤳�����������һ���˻�ʵʱ������
///ͬʱ�ֽ����������������Է����ѯ��
///	BrokerIDAccountSeqNoIndex
///ʹ�ñ����󹤳���������ɶ��˻�ʵʱ���������ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrokerIDAccountSeqNo��Ψһ�ҵ�����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInvestorAccountDepositFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxInvestorAccountDeposit��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInvestorAccountDepositFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorAccountDepositFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�InvestorAccountDeposit
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�InvestorAccountDeposit���ļ��������������ļ��еĶ���InvestorAccountDepositCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�InvestorAccountDeposit
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�InvestorAccountDeposit���ļ��������������ļ��еĶ���InvestorAccountDepositCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CInvestorAccountDepositResource;

	///��һ��CInvestorAccountDeposit���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInvestorAccountDeposit	Ҫ�����InvestorAccountDeposit
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInvestorAccountDeposit *add(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CInvestorAccountDeposit��ֵ
	///@param	pInvestorAccountDeposit	��ˢ�µ�CInvestorAccountDeposit
	///@param	pNewInvestorAccountDeposit	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pInvestorAccountDeposit	  ��Ҫ��ˢ�»���������CInvestorAccountDeposit,����NULL��ʾ����Ҫ������
	///@param	pNewInvestorAccountDeposit	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CInvestorAccountDeposit* addOrUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CInvestorAccountDeposit��ͬʱɾ��������
	///@param	pInvestorAccountDeposit	Ҫɾ����CInvestorAccountDeposit
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CInvestorAccountDeposit *pInvestorAccountDeposit, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CInvestorAccountDeposit
	///@param	pInvestorAccountDeposit	Ҫ��ȡ��CInvestorAccountDeposit
	///@param	pTragetInvestorAccountDeposit	��Ž����CInvestorAccountDeposit
	void retrieve(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pTargetInvestorAccountDeposit);
	
	///��ȡ��һ��CInvestorAccountDeposit
	///@return	�õ��ĵ�һ��CInvestorAccountDeposit�����û�У��򷵻�NULL
	CInvestorAccountDeposit *getFirst(void);
	
	///��ȡ��һ��CInvestorAccountDeposit
	///@return	�õ���һ��CInvestorAccountDeposit�����û�У��򷵻�NULL
	CInvestorAccountDeposit *getNext(void);
	
	///������ȡCInvestorAccountDeposit
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CInvestorAccountDepositActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CInvestorAccountDepositActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CInvestorAccountDepositCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CInvestorAccountDepositCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CInvestorAccountDeposit
	///@param	BrokerID	�����̱��
	///@param	AccountSeqNo	�ʽ���ˮ��
	///@return	�ҵ���CInvestorAccountDeposit������Ҳ���������NULL
	CInvestorAccountDeposit *findByBrokerIDAccountSeqNo( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyAccountSeqNoType&  AccountSeqNo);

	///��������Ѱ��
	///@param	BrokerID	�����̱��
	///@param	AccountSeqNo	�ʽ���ˮ��
	///@return	�ҵ���CInvestorAccountDeposit������Ҳ���������NULL
	CInvestorAccountDeposit *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyAccountSeqNoType&  AccountSeqNo);
	
	///��������Ѱ��CInvestorAccountDeposit
	///@param	pInvestorAccountDeposit	Ҫ�ҵ�ֵ
	///@return	�ҵ���CInvestorAccountDeposit������Ҳ���������NULL
	CInvestorAccountDeposit *findByPK(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit);

	///����������ȡCInvestorAccountDeposit
	///@param	pInvestorAccountDeposit	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CInvestorAccountDeposit������Ҳ���������NULL
	bool retrieveByPK(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit);

	///�������������µ�CInvestorAccountDeposit
	///@param	pInvestorAccountDeposit	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CInvestorAccountDeposit���������ʧ�ܣ��򷵻�NULL
	CInvestorAccountDeposit *addByPK(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit, CTransaction *pTransaction=NULL);

	///������������CInvestorAccountDeposit��ֵ
	///@param	pInvestorAccountDeposit	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CInvestorAccountDeposit
	///@param	pInvestorAccountDeposit	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit, CTransaction *pTransaction=NULL);


private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CInvestorAccountDeposit���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInvestorAccountDeposit	Ҫ�����InvestorAccountDeposit
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInvestorAccountDeposit *internalAdd(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit, bool bNoTransaction);
	
	
	///ˢ�¸�CInvestorAccountDeposit�ļ�ֵ
	///@param	pInvestorAccountDeposit	��ˢ�µ�CInvestorAccountDeposit
	///@param	pNewInvestorAccountDeposit	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CInvestorAccountDeposit��ͬʱɾ��������
	///@param	pInvestorAccountDeposit	Ҫɾ����CInvestorAccountDeposit
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CInvestorAccountDeposit *pInvestorAccountDeposit, bool bNoTransaction);
/*
	///���ĳ��CInvestorAccountDeposit�Ƿ����ڱ����󹤳�
	///@param	pInvestorAccountDeposit	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CInvestorAccountDeposit *pInvestorAccountDeposit);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����BrokerID+AccountSeqNo������
	CAVLTree *pBrokerIDAccountSeqNoIndex;
	
	
	
	///����ǰ����
	///@param	pInvestorAccountDeposit	Ҫ�����InvestorAccountDeposit
	virtual void beforeAdd(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit);
	
	///����󴥷�
	///@param	pInvestorAccountDeposit	�Ѿ������InvestorAccountDeposit
	virtual void afterAdd(CInvestorAccountDeposit *pInvestorAccountDeposit);

	///����ǰ����	
	///@param	pInvestorAccountDeposit	��ˢ�µ�CInvestorAccountDeposit
	///@param	pNewInvestorAccountDeposit	�µ�ֵ
	virtual void beforeUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit);
	
	///���º󴥷�
	///@param	pInvestorAccountDeposit	��ˢ�µ�CInvestorAccountDeposit
	virtual void afterUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit);
	
	///ɾ��ǰ����
	///@param	pInvestorAccountDeposit	Ҫɾ����CInvestorAccountDeposit
	virtual void beforeRemove(CInvestorAccountDeposit *pInvestorAccountDeposit);
	
	///ȷ�ϼ���󴥷�
	///@param	pInvestorAccountDeposit	�Ѿ������InvestorAccountDeposit
	virtual void commitAdd(CInvestorAccountDeposit *pInvestorAccountDeposit);

	///ȷ�ϸ��º󴥷�
	///@param	pInvestorAccountDeposit	��ˢ�µ�CInvestorAccountDeposit
	///@param	poldInvestorAccountDeposit	ԭ����ֵ
	virtual void commitUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pOldInvestorAccountDeposit);
	
	///ȷ��ɾ���󴥷�
	///@param	pInvestorAccountDeposit	�Ѿ�ɾ����CInvestorAccountDeposit
	virtual void commitRemove(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit);

	///������صĴ�����
	vector<CInvestorAccountDepositActionTrigger *> *pActionTriggers;
	vector<CInvestorAccountDepositCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableInvestorAccountDeposit compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CExchangeFactory��һ����������Ķ��󹤳�����������һ����������
///ͬʱ�ֽ����������������Է����ѯ��
///	ExchangeIDIndex
///ʹ�ñ����󹤳���������ɶԽ����������ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByExchangeID��Ψһ�ҵ�����
///		ʹ��startFindStartByExchangeID��findNextStartByExchangeID��endFindStartByExchangeID��ɲ�ѯ����
///		ʹ��startFindAll��findNextAll��endFindAll��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CExchangeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxExchange��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CExchangeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CExchangeFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�Exchange
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�Exchange���ļ��������������ļ��еĶ���ExchangeCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�Exchange
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�Exchange���ļ��������������ļ��еĶ���ExchangeCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CExchangeResource;

	///��һ��CExchange���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pExchange	Ҫ�����Exchange
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CExchange *add(CWriteableExchange *pExchange, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CExchange��ֵ
	///@param	pExchange	��ˢ�µ�CExchange
	///@param	pNewExchange	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CExchange *pExchange, CWriteableExchange *pNewExchange, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pExchange	  ��Ҫ��ˢ�»���������CExchange,����NULL��ʾ����Ҫ������
	///@param	pNewExchange	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CExchange* addOrUpdate(CExchange *pExchange, CWriteableExchange *pNewExchange, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CExchange��ͬʱɾ��������
	///@param	pExchange	Ҫɾ����CExchange
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CExchange *pExchange, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CExchange
	///@param	pExchange	Ҫ��ȡ��CExchange
	///@param	pTragetExchange	��Ž����CExchange
	void retrieve(CExchange *pExchange, CWriteableExchange *pTargetExchange);
	
	///��ȡ��һ��CExchange
	///@return	�õ��ĵ�һ��CExchange�����û�У��򷵻�NULL
	CExchange *getFirst(void);
	
	///��ȡ��һ��CExchange
	///@return	�õ���һ��CExchange�����û�У��򷵻�NULL
	CExchange *getNext(void);
	
	///������ȡCExchange
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CExchangeActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CExchangeActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CExchangeCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CExchangeCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CExchange
	///@param	ExchangeID	����������
	///@return	�ҵ���CExchange������Ҳ���������NULL
	CExchange *findByExchangeID( const CReadOnlyExchangeIDType&  ExchangeID);

	///��������Ѱ��
	///@param	ExchangeID	����������
	///@return	�ҵ���CExchange������Ҳ���������NULL
	CExchange *findByPK( const CReadOnlyExchangeIDType&  ExchangeID);
	
	///��������Ѱ��CExchange
	///@param	pExchange	Ҫ�ҵ�ֵ
	///@return	�ҵ���CExchange������Ҳ���������NULL
	CExchange *findByPK(CWriteableExchange *pExchange);

	///����������ȡCExchange
	///@param	pExchange	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CExchange������Ҳ���������NULL
	bool retrieveByPK(CWriteableExchange *pExchange);

	///�������������µ�CExchange
	///@param	pExchange	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CExchange���������ʧ�ܣ��򷵻�NULL
	CExchange *addByPK(CWriteableExchange *pExchange, CTransaction *pTransaction=NULL);

	///������������CExchange��ֵ
	///@param	pExchange	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableExchange *pExchange, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CExchange
	///@param	pExchange	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableExchange *pExchange, CTransaction *pTransaction=NULL);


	friend class CExchangeIteratorStartByExchangeID;

	///��ʼѰ��CExchange
	///@param	ExchangeID	����������
	///@return	���������ĵ�һ��CExchange������Ҳ���������NULL
	CExchange *startFindStartByExchangeID( const CReadOnlyExchangeIDType& ExchangeID);

	///Ѱ����һ������������CExchange��������startFindStartByExchangeID�Ժ�endFindStartByExchangeID֮ǰ����
	///@return	��һ����������CExchange������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CExchange *findNextStartByExchangeID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindStartByExchangeID(void);

	friend class CExchangeIteratorAll;

	///��ʼѰ��CExchange
	///@return	���������ĵ�һ��CExchange������Ҳ���������NULL
	CExchange *startFindAll();

	///Ѱ����һ������������CExchange��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CExchange������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CExchange *findNextAll(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAll(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CExchange���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pExchange	Ҫ�����Exchange
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CExchange *internalAdd(CWriteableExchange *pExchange, bool bNoTransaction);
	
	
	///ˢ�¸�CExchange�ļ�ֵ
	///@param	pExchange	��ˢ�µ�CExchange
	///@param	pNewExchange	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CExchange *pExchange, CWriteableExchange *pNewExchange, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CExchange��ͬʱɾ��������
	///@param	pExchange	Ҫɾ����CExchange
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CExchange *pExchange, bool bNoTransaction);
/*
	///���ĳ��CExchange�Ƿ����ڱ����󹤳�
	///@param	pExchange	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CExchange *pExchange);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����ExchangeID������
	CAVLTree *pExchangeIDIndex;
	
	
	///����ExchangeID����ʱ���洢�Ĳ�ѯ����
	CExchangeIDType queryExchangeIDInSearchStartByExchangeID;
	
	///����ExchangeID����ʱ���洢���һ���ҵ��������ڵ�
	CAVLNode *pLastFoundInSearchStartByExchangeID;
	///���ռ���ʱ���洢�Ĳ�ѯ����
	
	///���ռ���ʱ���洢���һ���ҵ��������ڵ�
	CExchange *pLastFoundInSearchAll;
	
	///����ǰ����
	///@param	pExchange	Ҫ�����Exchange
	virtual void beforeAdd(CWriteableExchange *pExchange);
	
	///����󴥷�
	///@param	pExchange	�Ѿ������Exchange
	virtual void afterAdd(CExchange *pExchange);

	///����ǰ����	
	///@param	pExchange	��ˢ�µ�CExchange
	///@param	pNewExchange	�µ�ֵ
	virtual void beforeUpdate(CExchange *pExchange, CWriteableExchange *pNewExchange);
	
	///���º󴥷�
	///@param	pExchange	��ˢ�µ�CExchange
	virtual void afterUpdate(CExchange *pExchange);
	
	///ɾ��ǰ����
	///@param	pExchange	Ҫɾ����CExchange
	virtual void beforeRemove(CExchange *pExchange);
	
	///ȷ�ϼ���󴥷�
	///@param	pExchange	�Ѿ������Exchange
	virtual void commitAdd(CExchange *pExchange);

	///ȷ�ϸ��º󴥷�
	///@param	pExchange	��ˢ�µ�CExchange
	///@param	poldExchange	ԭ����ֵ
	virtual void commitUpdate(CExchange *pExchange, CWriteableExchange *pOldExchange);
	
	///ȷ��ɾ���󴥷�
	///@param	pExchange	�Ѿ�ɾ����CExchange
	virtual void commitRemove(CWriteableExchange *pExchange);

	///������صĴ�����
	vector<CExchangeActionTrigger *> *pActionTriggers;
	vector<CExchangeCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableExchange compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CSeatFactory��һ���µ�ϯλ��Ķ��󹤳�����������һ���µ�ϯλ��
///ͬʱ�ֽ����������������Է����ѯ��
///	BrokerIDExchangeIDSeatIDIndex
///	ExchangeIDParticipantIDSeatIDIndex
///ʹ�ñ����󹤳���������ɶ��µ�ϯλ�����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrokerIDExchangeIDSeatID��Ψһ�ҵ�����
///		ʹ��findByExchangeIDParticipantIDSeatID��Ψһ�ҵ�����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CSeatFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxSeat��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CSeatFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CSeatFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�Seat
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�Seat���ļ��������������ļ��еĶ���SeatCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�Seat
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�Seat���ļ��������������ļ��еĶ���SeatCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CSeatResource;

	///��һ��CSeat���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pSeat	Ҫ�����Seat
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CSeat *add(CWriteableSeat *pSeat, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CSeat��ֵ
	///@param	pSeat	��ˢ�µ�CSeat
	///@param	pNewSeat	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CSeat *pSeat, CWriteableSeat *pNewSeat, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pSeat	  ��Ҫ��ˢ�»���������CSeat,����NULL��ʾ����Ҫ������
	///@param	pNewSeat	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CSeat* addOrUpdate(CSeat *pSeat, CWriteableSeat *pNewSeat, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CSeat��ͬʱɾ��������
	///@param	pSeat	Ҫɾ����CSeat
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CSeat *pSeat, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CSeat
	///@param	pSeat	Ҫ��ȡ��CSeat
	///@param	pTragetSeat	��Ž����CSeat
	void retrieve(CSeat *pSeat, CWriteableSeat *pTargetSeat);
	
	///��ȡ��һ��CSeat
	///@return	�õ��ĵ�һ��CSeat�����û�У��򷵻�NULL
	CSeat *getFirst(void);
	
	///��ȡ��һ��CSeat
	///@return	�õ���һ��CSeat�����û�У��򷵻�NULL
	CSeat *getNext(void);
	
	///������ȡCSeat
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CSeatActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CSeatActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CSeatCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CSeatCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CSeat
	///@param	BrokerID	�����̱��
	///@param	ExchangeID	����������
	///@param	SeatID	ϯλ��
	///@return	�ҵ���CSeat������Ҳ���������NULL
	CSeat *findByBrokerIDExchangeIDSeatID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlySeatIDType&  SeatID);

	///��������Ѱ��
	///@param	BrokerID	�����̱��
	///@param	ExchangeID	����������
	///@param	SeatID	ϯλ��
	///@return	�ҵ���CSeat������Ҳ���������NULL
	CSeat *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlySeatIDType&  SeatID);
	
	///��������Ѱ��CSeat
	///@param	pSeat	Ҫ�ҵ�ֵ
	///@return	�ҵ���CSeat������Ҳ���������NULL
	CSeat *findByPK(CWriteableSeat *pSeat);

	///����������ȡCSeat
	///@param	pSeat	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CSeat������Ҳ���������NULL
	bool retrieveByPK(CWriteableSeat *pSeat);

	///�������������µ�CSeat
	///@param	pSeat	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CSeat���������ʧ�ܣ��򷵻�NULL
	CSeat *addByPK(CWriteableSeat *pSeat, CTransaction *pTransaction=NULL);

	///������������CSeat��ֵ
	///@param	pSeat	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableSeat *pSeat, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CSeat
	///@param	pSeat	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableSeat *pSeat, CTransaction *pTransaction=NULL);


	///Ѱ��CSeat
	///@param	ExchangeID	����������
	///@param	ParticipantID	��Ա���
	///@param	SeatID	ϯλ��
	///@return	�ҵ���CSeat������Ҳ���������NULL
	CSeat *findByExchangeIDParticipantIDSeatID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyParticipantIDType&  ParticipantID,  const CReadOnlySeatIDType&  SeatID);



private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CSeat���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pSeat	Ҫ�����Seat
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CSeat *internalAdd(CWriteableSeat *pSeat, bool bNoTransaction);
	
	
	///ˢ�¸�CSeat�ļ�ֵ
	///@param	pSeat	��ˢ�µ�CSeat
	///@param	pNewSeat	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CSeat *pSeat, CWriteableSeat *pNewSeat, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CSeat��ͬʱɾ��������
	///@param	pSeat	Ҫɾ����CSeat
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CSeat *pSeat, bool bNoTransaction);
/*
	///���ĳ��CSeat�Ƿ����ڱ����󹤳�
	///@param	pSeat	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CSeat *pSeat);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����BrokerID+ExchangeID+SeatID������
	CAVLTree *pBrokerIDExchangeIDSeatIDIndex;
	///����ExchangeID+ParticipantID+SeatID������
	CAVLTree *pExchangeIDParticipantIDSeatIDIndex;
	
	
	
	///����ǰ����
	///@param	pSeat	Ҫ�����Seat
	virtual void beforeAdd(CWriteableSeat *pSeat);
	
	///����󴥷�
	///@param	pSeat	�Ѿ������Seat
	virtual void afterAdd(CSeat *pSeat);

	///����ǰ����	
	///@param	pSeat	��ˢ�µ�CSeat
	///@param	pNewSeat	�µ�ֵ
	virtual void beforeUpdate(CSeat *pSeat, CWriteableSeat *pNewSeat);
	
	///���º󴥷�
	///@param	pSeat	��ˢ�µ�CSeat
	virtual void afterUpdate(CSeat *pSeat);
	
	///ɾ��ǰ����
	///@param	pSeat	Ҫɾ����CSeat
	virtual void beforeRemove(CSeat *pSeat);
	
	///ȷ�ϼ���󴥷�
	///@param	pSeat	�Ѿ������Seat
	virtual void commitAdd(CSeat *pSeat);

	///ȷ�ϸ��º󴥷�
	///@param	pSeat	��ˢ�µ�CSeat
	///@param	poldSeat	ԭ����ֵ
	virtual void commitUpdate(CSeat *pSeat, CWriteableSeat *pOldSeat);
	
	///ȷ��ɾ���󴥷�
	///@param	pSeat	�Ѿ�ɾ����CSeat
	virtual void commitRemove(CWriteableSeat *pSeat);

	///������صĴ�����
	vector<CSeatActionTrigger *> *pActionTriggers;
	vector<CSeatCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableSeat compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentFactory��һ���ڻ���Լ��Ķ��󹤳�����������һ���ڻ���Լ��
///ͬʱ�ֽ����������������Է����ѯ��
///	ExchangeIDInstrumentIDIndex
///	InstrumentIDIndex
///ʹ�ñ����󹤳���������ɶ��ڻ���Լ�����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByExchangeIDAndInstrumentID��Ψһ�ҵ�����
///		ʹ��startFindAllByInstrumentID��findNextAllByInstrumentID��endFindAllByInstrumentID��ɲ�ѯ����
///		ʹ��startFindAllByExchangeID��findNextAllByExchangeID��endFindAllByExchangeID��ɲ�ѯ����
///		ʹ��startFindAllByProductID��findNextAllByProductID��endFindAllByProductID��ɲ�ѯ����
///		ʹ��startFindAll��findNextAll��endFindAll��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInstrumentFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxInstrument��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInstrumentFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInstrumentFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�Instrument
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�Instrument���ļ��������������ļ��еĶ���InstrumentCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�Instrument
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�Instrument���ļ��������������ļ��еĶ���InstrumentCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CInstrumentResource;

	///��һ��CInstrument���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInstrument	Ҫ�����Instrument
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInstrument *add(CWriteableInstrument *pInstrument, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CInstrument��ֵ
	///@param	pInstrument	��ˢ�µ�CInstrument
	///@param	pNewInstrument	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pInstrument	  ��Ҫ��ˢ�»���������CInstrument,����NULL��ʾ����Ҫ������
	///@param	pNewInstrument	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CInstrument* addOrUpdate(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CInstrument��ͬʱɾ��������
	///@param	pInstrument	Ҫɾ����CInstrument
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CInstrument *pInstrument, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CInstrument
	///@param	pInstrument	Ҫ��ȡ��CInstrument
	///@param	pTragetInstrument	��Ž����CInstrument
	void retrieve(CInstrument *pInstrument, CWriteableInstrument *pTargetInstrument);
	
	///��ȡ��һ��CInstrument
	///@return	�õ��ĵ�һ��CInstrument�����û�У��򷵻�NULL
	CInstrument *getFirst(void);
	
	///��ȡ��һ��CInstrument
	///@return	�õ���һ��CInstrument�����û�У��򷵻�NULL
	CInstrument *getNext(void);
	
	///������ȡCInstrument
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CInstrumentActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CInstrumentActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CInstrumentCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CInstrumentCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CInstrument
	///@param	ExchangeID	���������
	///@param	InstrumentID	��Լ���
	///@return	�ҵ���CInstrument������Ҳ���������NULL
	CInstrument *findByExchangeIDAndInstrumentID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID);

	///��������Ѱ��
	///@param	ExchangeID	���������
	///@param	InstrumentID	��Լ���
	///@return	�ҵ���CInstrument������Ҳ���������NULL
	CInstrument *findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID);
	
	///��������Ѱ��CInstrument
	///@param	pInstrument	Ҫ�ҵ�ֵ
	///@return	�ҵ���CInstrument������Ҳ���������NULL
	CInstrument *findByPK(CWriteableInstrument *pInstrument);

	///����������ȡCInstrument
	///@param	pInstrument	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CInstrument������Ҳ���������NULL
	bool retrieveByPK(CWriteableInstrument *pInstrument);

	///�������������µ�CInstrument
	///@param	pInstrument	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CInstrument���������ʧ�ܣ��򷵻�NULL
	CInstrument *addByPK(CWriteableInstrument *pInstrument, CTransaction *pTransaction=NULL);

	///������������CInstrument��ֵ
	///@param	pInstrument	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableInstrument *pInstrument, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CInstrument
	///@param	pInstrument	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableInstrument *pInstrument, CTransaction *pTransaction=NULL);


	friend class CInstrumentIteratorAllByInstrumentID;

	///��ʼѰ��CInstrument
	///@param	InstrumentID	��Լ����
	///@return	���������ĵ�һ��CInstrument������Ҳ���������NULL
	CInstrument *startFindAllByInstrumentID( const CReadOnlyInstrumentIDType& InstrumentID);

	///Ѱ����һ������������CInstrument��������startFindAllByInstrumentID�Ժ�endFindAllByInstrumentID֮ǰ����
	///@return	��һ����������CInstrument������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInstrument *findNextAllByInstrumentID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByInstrumentID(void);

	friend class CInstrumentIteratorAllByExchangeID;

	///��ʼѰ��CInstrument
	///@param	ExchangeID	���������
	///@return	���������ĵ�һ��CInstrument������Ҳ���������NULL
	CInstrument *startFindAllByExchangeID( const CReadOnlyExchangeIDType& ExchangeID);

	///Ѱ����һ������������CInstrument��������startFindAllByExchangeID�Ժ�endFindAllByExchangeID֮ǰ����
	///@return	��һ����������CInstrument������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInstrument *findNextAllByExchangeID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByExchangeID(void);

	friend class CInstrumentIteratorAllByProductID;

	///��ʼѰ��CInstrument
	///@param	ProductID	��Ʒ����
	///@return	���������ĵ�һ��CInstrument������Ҳ���������NULL
	CInstrument *startFindAllByProductID( const CReadOnlyProductIDType& ProductID);

	///Ѱ����һ������������CInstrument��������startFindAllByProductID�Ժ�endFindAllByProductID֮ǰ����
	///@return	��һ����������CInstrument������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInstrument *findNextAllByProductID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByProductID(void);

	friend class CInstrumentIteratorAll;

	///��ʼѰ��CInstrument
	///@return	���������ĵ�һ��CInstrument������Ҳ���������NULL
	CInstrument *startFindAll();

	///Ѱ����һ������������CInstrument��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CInstrument������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInstrument *findNextAll(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAll(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CInstrument���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInstrument	Ҫ�����Instrument
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInstrument *internalAdd(CWriteableInstrument *pInstrument, bool bNoTransaction);
	
	
	///ˢ�¸�CInstrument�ļ�ֵ
	///@param	pInstrument	��ˢ�µ�CInstrument
	///@param	pNewInstrument	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CInstrument��ͬʱɾ��������
	///@param	pInstrument	Ҫɾ����CInstrument
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CInstrument *pInstrument, bool bNoTransaction);
/*
	///���ĳ��CInstrument�Ƿ����ڱ����󹤳�
	///@param	pInstrument	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CInstrument *pInstrument);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����ExchangeID+InstrumentID������
	CAVLTree *pExchangeIDInstrumentIDIndex;
	///����InstrumentID������
	CAVLTree *pInstrumentIDIndex;
	
	
	///����InstrumentID����ʱ���洢�Ĳ�ѯ����
	CInstrumentIDType queryInstrumentIDInSearchAllByInstrumentID;
	
	///����InstrumentID����ʱ���洢���һ���ҵ��������ڵ�
	CAVLNode *pLastFoundInSearchAllByInstrumentID;
	///����ExchangeID����ʱ���洢�Ĳ�ѯ����
	CExchangeIDType queryExchangeIDInSearchAllByExchangeID;
	
	///����ExchangeID����ʱ���洢���һ���ҵ��������ڵ�
	CInstrument *pLastFoundInSearchAllByExchangeID;
	///����ProductID����ʱ���洢�Ĳ�ѯ����
	CProductIDType queryProductIDInSearchAllByProductID;
	
	///����ProductID����ʱ���洢���һ���ҵ��������ڵ�
	CInstrument *pLastFoundInSearchAllByProductID;
	///���ռ���ʱ���洢�Ĳ�ѯ����
	
	///���ռ���ʱ���洢���һ���ҵ��������ڵ�
	CInstrument *pLastFoundInSearchAll;
	
	///����ǰ����
	///@param	pInstrument	Ҫ�����Instrument
	virtual void beforeAdd(CWriteableInstrument *pInstrument);
	
	///����󴥷�
	///@param	pInstrument	�Ѿ������Instrument
	virtual void afterAdd(CInstrument *pInstrument);

	///����ǰ����	
	///@param	pInstrument	��ˢ�µ�CInstrument
	///@param	pNewInstrument	�µ�ֵ
	virtual void beforeUpdate(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument);
	
	///���º󴥷�
	///@param	pInstrument	��ˢ�µ�CInstrument
	virtual void afterUpdate(CInstrument *pInstrument);
	
	///ɾ��ǰ����
	///@param	pInstrument	Ҫɾ����CInstrument
	virtual void beforeRemove(CInstrument *pInstrument);
	
	///ȷ�ϼ���󴥷�
	///@param	pInstrument	�Ѿ������Instrument
	virtual void commitAdd(CInstrument *pInstrument);

	///ȷ�ϸ��º󴥷�
	///@param	pInstrument	��ˢ�µ�CInstrument
	///@param	poldInstrument	ԭ����ֵ
	virtual void commitUpdate(CInstrument *pInstrument, CWriteableInstrument *pOldInstrument);
	
	///ȷ��ɾ���󴥷�
	///@param	pInstrument	�Ѿ�ɾ����CInstrument
	virtual void commitRemove(CWriteableInstrument *pInstrument);

	///������صĴ�����
	vector<CInstrumentActionTrigger *> *pActionTriggers;
	vector<CInstrumentCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableInstrument compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailFactory��һ���ڻ���Ϻ�Լ��ϸ��Ķ��󹤳�����������һ���ڻ���Ϻ�Լ��ϸ��
///ͬʱ�ֽ����������������Է����ѯ��
///	ExchangeIDArbiInstrumentIDSingelInstrumentIDIndex
///	ExchangeIDArbiInstrumentIDIndex
///	ExchangeIDSingleInstrumentIDIndex
///ʹ�ñ����󹤳���������ɶ��ڻ���Ϻ�Լ��ϸ�����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByExchangeIDAndArbiInstrumentIDAndSingelInstrumentID��Ψһ�ҵ�����
///		ʹ��startFindAllByExchangeIDAndArbiInstrumentID��findNextAllByExchangeIDAndArbiInstrumentID��endFindAllByExchangeIDAndArbiInstrumentID��ɲ�ѯ����
///		ʹ��startFindAllByExchangeIDAndSingleInstrumentID��findNextAllByExchangeIDAndSingleInstrumentID��endFindAllByExchangeIDAndSingleInstrumentID��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CCmbInstrumentDetailFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxCmbInstrumentDetail��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CCmbInstrumentDetailFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CCmbInstrumentDetailFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�CmbInstrumentDetail
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�CmbInstrumentDetail���ļ��������������ļ��еĶ���CmbInstrumentDetailCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�CmbInstrumentDetail
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�CmbInstrumentDetail���ļ��������������ļ��еĶ���CmbInstrumentDetailCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CCmbInstrumentDetailResource;

	///��һ��CCmbInstrumentDetail���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pCmbInstrumentDetail	Ҫ�����CmbInstrumentDetail
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CCmbInstrumentDetail *add(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CCmbInstrumentDetail��ֵ
	///@param	pCmbInstrumentDetail	��ˢ�µ�CCmbInstrumentDetail
	///@param	pNewCmbInstrumentDetail	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pCmbInstrumentDetail	  ��Ҫ��ˢ�»���������CCmbInstrumentDetail,����NULL��ʾ����Ҫ������
	///@param	pNewCmbInstrumentDetail	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CCmbInstrumentDetail* addOrUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CCmbInstrumentDetail��ͬʱɾ��������
	///@param	pCmbInstrumentDetail	Ҫɾ����CCmbInstrumentDetail
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CCmbInstrumentDetail *pCmbInstrumentDetail, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CCmbInstrumentDetail
	///@param	pCmbInstrumentDetail	Ҫ��ȡ��CCmbInstrumentDetail
	///@param	pTragetCmbInstrumentDetail	��Ž����CCmbInstrumentDetail
	void retrieve(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pTargetCmbInstrumentDetail);
	
	///��ȡ��һ��CCmbInstrumentDetail
	///@return	�õ��ĵ�һ��CCmbInstrumentDetail�����û�У��򷵻�NULL
	CCmbInstrumentDetail *getFirst(void);
	
	///��ȡ��һ��CCmbInstrumentDetail
	///@return	�õ���һ��CCmbInstrumentDetail�����û�У��򷵻�NULL
	CCmbInstrumentDetail *getNext(void);
	
	///������ȡCCmbInstrumentDetail
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CCmbInstrumentDetailActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CCmbInstrumentDetailActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CCmbInstrumentDetailCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CCmbInstrumentDetailCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CCmbInstrumentDetail
	///@param	ExchangeID	���������
	///@param	ArbiInstrumentID	��Ϻ�Լ���
	///@param	SingleInstrumentID	���Ⱥ�Լ���
	///@return	�ҵ���CCmbInstrumentDetail������Ҳ���������NULL
	CCmbInstrumentDetail *findByExchangeIDAndArbiInstrumentIDAndSingelInstrumentID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  ArbiInstrumentID,  const CReadOnlyInstrumentIDType&  SingleInstrumentID);

	///��������Ѱ��
	///@param	ExchangeID	���������
	///@param	ArbiInstrumentID	��Ϻ�Լ���
	///@param	SingleInstrumentID	���Ⱥ�Լ���
	///@return	�ҵ���CCmbInstrumentDetail������Ҳ���������NULL
	CCmbInstrumentDetail *findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  ArbiInstrumentID,  const CReadOnlyInstrumentIDType&  SingleInstrumentID);
	
	///��������Ѱ��CCmbInstrumentDetail
	///@param	pCmbInstrumentDetail	Ҫ�ҵ�ֵ
	///@return	�ҵ���CCmbInstrumentDetail������Ҳ���������NULL
	CCmbInstrumentDetail *findByPK(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail);

	///����������ȡCCmbInstrumentDetail
	///@param	pCmbInstrumentDetail	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CCmbInstrumentDetail������Ҳ���������NULL
	bool retrieveByPK(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail);

	///�������������µ�CCmbInstrumentDetail
	///@param	pCmbInstrumentDetail	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CCmbInstrumentDetail���������ʧ�ܣ��򷵻�NULL
	CCmbInstrumentDetail *addByPK(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail, CTransaction *pTransaction=NULL);

	///������������CCmbInstrumentDetail��ֵ
	///@param	pCmbInstrumentDetail	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CCmbInstrumentDetail
	///@param	pCmbInstrumentDetail	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail, CTransaction *pTransaction=NULL);


	friend class CCmbInstrumentDetailIteratorAllByExchangeIDAndArbiInstrumentID;

	///��ʼѰ��CCmbInstrumentDetail
	///@param	ExchangeID	���������
	///@param	ArbiInstrumentID	��Ϻ�Լ���
	///@return	���������ĵ�һ��CCmbInstrumentDetail������Ҳ���������NULL
	CCmbInstrumentDetail *startFindAllByExchangeIDAndArbiInstrumentID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& ArbiInstrumentID);

	///Ѱ����һ������������CCmbInstrumentDetail��������startFindAllByExchangeIDAndArbiInstrumentID�Ժ�endFindAllByExchangeIDAndArbiInstrumentID֮ǰ����
	///@return	��һ����������CCmbInstrumentDetail������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CCmbInstrumentDetail *findNextAllByExchangeIDAndArbiInstrumentID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByExchangeIDAndArbiInstrumentID(void);

	friend class CCmbInstrumentDetailIteratorAllByExchangeIDAndSingleInstrumentID;

	///��ʼѰ��CCmbInstrumentDetail
	///@param	ExchangeID	���������
	///@param	SingleInstrumentID	���Ⱥ�Լ���
	///@return	���������ĵ�һ��CCmbInstrumentDetail������Ҳ���������NULL
	CCmbInstrumentDetail *startFindAllByExchangeIDAndSingleInstrumentID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& SingleInstrumentID);

	///Ѱ����һ������������CCmbInstrumentDetail��������startFindAllByExchangeIDAndSingleInstrumentID�Ժ�endFindAllByExchangeIDAndSingleInstrumentID֮ǰ����
	///@return	��һ����������CCmbInstrumentDetail������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CCmbInstrumentDetail *findNextAllByExchangeIDAndSingleInstrumentID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByExchangeIDAndSingleInstrumentID(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CCmbInstrumentDetail���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pCmbInstrumentDetail	Ҫ�����CmbInstrumentDetail
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CCmbInstrumentDetail *internalAdd(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail, bool bNoTransaction);
	
	
	///ˢ�¸�CCmbInstrumentDetail�ļ�ֵ
	///@param	pCmbInstrumentDetail	��ˢ�µ�CCmbInstrumentDetail
	///@param	pNewCmbInstrumentDetail	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CCmbInstrumentDetail��ͬʱɾ��������
	///@param	pCmbInstrumentDetail	Ҫɾ����CCmbInstrumentDetail
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CCmbInstrumentDetail *pCmbInstrumentDetail, bool bNoTransaction);
/*
	///���ĳ��CCmbInstrumentDetail�Ƿ����ڱ����󹤳�
	///@param	pCmbInstrumentDetail	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CCmbInstrumentDetail *pCmbInstrumentDetail);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����ExchangeID+ArbiInstrumentID+SingleInstrumentID������
	CAVLTree *pExchangeIDArbiInstrumentIDSingelInstrumentIDIndex;
	///����ExchangeID+ArbiInstrumentID������
	CAVLTree *pExchangeIDArbiInstrumentIDIndex;
	///����ExchangeID+SingleInstrumentID������
	CAVLTree *pExchangeIDSingleInstrumentIDIndex;
	
	
	///����ExchangeID��ArbiInstrumentID����ʱ���洢�Ĳ�ѯ����
	CExchangeIDType queryExchangeIDInSearchAllByExchangeIDAndArbiInstrumentID;
	CInstrumentIDType queryArbiInstrumentIDInSearchAllByExchangeIDAndArbiInstrumentID;
	
	///����ExchangeID��ArbiInstrumentID����ʱ���洢���һ���ҵ��������ڵ�
	CAVLNode *pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID;
	///����ExchangeID��SingleInstrumentID����ʱ���洢�Ĳ�ѯ����
	CExchangeIDType queryExchangeIDInSearchAllByExchangeIDAndSingleInstrumentID;
	CInstrumentIDType querySingleInstrumentIDInSearchAllByExchangeIDAndSingleInstrumentID;
	
	///����ExchangeID��SingleInstrumentID����ʱ���洢���һ���ҵ��������ڵ�
	CAVLNode *pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID;
	
	///����ǰ����
	///@param	pCmbInstrumentDetail	Ҫ�����CmbInstrumentDetail
	virtual void beforeAdd(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail);
	
	///����󴥷�
	///@param	pCmbInstrumentDetail	�Ѿ������CmbInstrumentDetail
	virtual void afterAdd(CCmbInstrumentDetail *pCmbInstrumentDetail);

	///����ǰ����	
	///@param	pCmbInstrumentDetail	��ˢ�µ�CCmbInstrumentDetail
	///@param	pNewCmbInstrumentDetail	�µ�ֵ
	virtual void beforeUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail);
	
	///���º󴥷�
	///@param	pCmbInstrumentDetail	��ˢ�µ�CCmbInstrumentDetail
	virtual void afterUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail);
	
	///ɾ��ǰ����
	///@param	pCmbInstrumentDetail	Ҫɾ����CCmbInstrumentDetail
	virtual void beforeRemove(CCmbInstrumentDetail *pCmbInstrumentDetail);
	
	///ȷ�ϼ���󴥷�
	///@param	pCmbInstrumentDetail	�Ѿ������CmbInstrumentDetail
	virtual void commitAdd(CCmbInstrumentDetail *pCmbInstrumentDetail);

	///ȷ�ϸ��º󴥷�
	///@param	pCmbInstrumentDetail	��ˢ�µ�CCmbInstrumentDetail
	///@param	poldCmbInstrumentDetail	ԭ����ֵ
	virtual void commitUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pOldCmbInstrumentDetail);
	
	///ȷ��ɾ���󴥷�
	///@param	pCmbInstrumentDetail	�Ѿ�ɾ����CCmbInstrumentDetail
	virtual void commitRemove(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail);

	///������صĴ�����
	vector<CCmbInstrumentDetailActionTrigger *> *pActionTriggers;
	vector<CCmbInstrumentDetailCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableCmbInstrumentDetail compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDFactory��һ���������ͻ������Ķ��󹤳�����������һ���������ͻ������
///ͬʱ�ֽ����������������Է����ѯ��
///	BrkIDExIDInvIDHdgFlgIndex
///	BrokerIDInvestorIDIndex
///ʹ�ñ����󹤳���������ɶԽ������ͻ���������ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrokerIDExchangeIDPartClientID��Ψһ�ҵ�����
///		ʹ��findByBrkIDExIDInvIDHdgFlg��Ψһ�ҵ�����
///		ʹ��startFindByBrokerIDInvestorID��findNextByBrokerIDInvestorID��endFindByBrokerIDInvestorID��ɲ�ѯ����
///		ʹ��startFindAllByBrokerID��findNextAllByBrokerID��endFindAllByBrokerID��ɲ�ѯ����
///		ʹ��startFindAll��findNextAll��endFindAll��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CClientTradingIDFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxClientTradingID��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CClientTradingIDFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CClientTradingIDFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�ClientTradingID
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�ClientTradingID���ļ��������������ļ��еĶ���ClientTradingIDCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�ClientTradingID
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�ClientTradingID���ļ��������������ļ��еĶ���ClientTradingIDCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CClientTradingIDResource;

	///��һ��CClientTradingID���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pClientTradingID	Ҫ�����ClientTradingID
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CClientTradingID *add(CWriteableClientTradingID *pClientTradingID, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CClientTradingID��ֵ
	///@param	pClientTradingID	��ˢ�µ�CClientTradingID
	///@param	pNewClientTradingID	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pClientTradingID	  ��Ҫ��ˢ�»���������CClientTradingID,����NULL��ʾ����Ҫ������
	///@param	pNewClientTradingID	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CClientTradingID* addOrUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CClientTradingID��ͬʱɾ��������
	///@param	pClientTradingID	Ҫɾ����CClientTradingID
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CClientTradingID *pClientTradingID, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CClientTradingID
	///@param	pClientTradingID	Ҫ��ȡ��CClientTradingID
	///@param	pTragetClientTradingID	��Ž����CClientTradingID
	void retrieve(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pTargetClientTradingID);
	
	///��ȡ��һ��CClientTradingID
	///@return	�õ��ĵ�һ��CClientTradingID�����û�У��򷵻�NULL
	CClientTradingID *getFirst(void);
	
	///��ȡ��һ��CClientTradingID
	///@return	�õ���һ��CClientTradingID�����û�У��򷵻�NULL
	CClientTradingID *getNext(void);
	
	///������ȡCClientTradingID
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CClientTradingIDActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CClientTradingIDActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CClientTradingIDCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CClientTradingIDCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///�������ж�Ӧ���ʻ���ָ��
	///@param	pFactory	�����Ӧ���ʻ���ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorAccount(CInvestorAccountFactory *pFactory);
	
	///Ѱ��CClientTradingID
	///@param	BrokerID	�����̱��
	///@param	ExchangeID	����������
	///@param	ParticipantID	��Ա��
	///@param	ClientID	�ͻ�����
	///@return	�ҵ���CClientTradingID������Ҳ���������NULL
	CClientTradingID *findByBrokerIDExchangeIDPartClientID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyParticipantIDType&  ParticipantID,  const CReadOnlyClientIDType&  ClientID);

	///��������Ѱ��
	///@param	BrokerID	�����̱��
	///@param	ExchangeID	����������
	///@param	ParticipantID	��Ա��
	///@param	ClientID	�ͻ�����
	///@return	�ҵ���CClientTradingID������Ҳ���������NULL
	CClientTradingID *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyParticipantIDType&  ParticipantID,  const CReadOnlyClientIDType&  ClientID);
	
	///��������Ѱ��CClientTradingID
	///@param	pClientTradingID	Ҫ�ҵ�ֵ
	///@return	�ҵ���CClientTradingID������Ҳ���������NULL
	CClientTradingID *findByPK(CWriteableClientTradingID *pClientTradingID);

	///����������ȡCClientTradingID
	///@param	pClientTradingID	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CClientTradingID������Ҳ���������NULL
	bool retrieveByPK(CWriteableClientTradingID *pClientTradingID);

	///�������������µ�CClientTradingID
	///@param	pClientTradingID	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CClientTradingID���������ʧ�ܣ��򷵻�NULL
	CClientTradingID *addByPK(CWriteableClientTradingID *pClientTradingID, CTransaction *pTransaction=NULL);

	///������������CClientTradingID��ֵ
	///@param	pClientTradingID	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableClientTradingID *pClientTradingID, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CClientTradingID
	///@param	pClientTradingID	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableClientTradingID *pClientTradingID, CTransaction *pTransaction=NULL);


	///Ѱ��CClientTradingID
	///@param	BrokerID	�����̱��
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱���
	///@param	ClientHedgeFlag	Ͷ���ױ���־
	///@return	�ҵ���CClientTradingID������Ҳ���������NULL
	CClientTradingID *findByBrkIDExIDInvIDHdgFlg( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  ClientHedgeFlag);



	friend class CClientTradingIDIteratorByBrokerIDInvestorID;

	///��ʼѰ��CClientTradingID
	///@param	BrokerID	�����̱��
	///@param	InvestorID	�ͻ�����
	///@return	���������ĵ�һ��CClientTradingID������Ҳ���������NULL
	CClientTradingID *startFindByBrokerIDInvestorID( const CReadOnlyBrokerIDType& BrokerID,  const CReadOnlyInvestorIDType& InvestorID);

	///Ѱ����һ������������CClientTradingID��������startFindByBrokerIDInvestorID�Ժ�endFindByBrokerIDInvestorID֮ǰ����
	///@return	��һ����������CClientTradingID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CClientTradingID *findNextByBrokerIDInvestorID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindByBrokerIDInvestorID(void);

	friend class CClientTradingIDIteratorAllByBrokerID;

	///��ʼѰ��CClientTradingID
	///@param	BrokerID	���͹�˾����
	///@return	���������ĵ�һ��CClientTradingID������Ҳ���������NULL
	CClientTradingID *startFindAllByBrokerID( const CReadOnlyBrokerIDType& BrokerID);

	///Ѱ����һ������������CClientTradingID��������startFindAllByBrokerID�Ժ�endFindAllByBrokerID֮ǰ����
	///@return	��һ����������CClientTradingID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CClientTradingID *findNextAllByBrokerID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByBrokerID(void);

	friend class CClientTradingIDIteratorAll;

	///��ʼѰ��CClientTradingID
	///@return	���������ĵ�һ��CClientTradingID������Ҳ���������NULL
	CClientTradingID *startFindAll();

	///Ѱ����һ������������CClientTradingID��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CClientTradingID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CClientTradingID *findNextAll(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAll(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CClientTradingID���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pClientTradingID	Ҫ�����ClientTradingID
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CClientTradingID *internalAdd(CWriteableClientTradingID *pClientTradingID, bool bNoTransaction);
	
	
	///ˢ�¸�CClientTradingID�ļ�ֵ
	///@param	pClientTradingID	��ˢ�µ�CClientTradingID
	///@param	pNewClientTradingID	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CClientTradingID��ͬʱɾ��������
	///@param	pClientTradingID	Ҫɾ����CClientTradingID
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CClientTradingID *pClientTradingID, bool bNoTransaction);
/*
	///���ĳ��CClientTradingID�Ƿ����ڱ����󹤳�
	///@param	pClientTradingID	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CClientTradingID *pClientTradingID);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����BrokerID+ExchangeID+InvestorID+ClientHedgeFlag������
	CAVLTree *pBrkIDExIDInvIDHdgFlgIndex;
	///����BrokerID+InvestorID������
	CAVLTree *pBrokerIDInvestorIDIndex;
	
	///����BrokerIDExchangeIDPartClientID��hash����
	CHashIndex *pBrokerIDExchangeIDPartClientIDHashIndex;
	
	///����BrokerID��InvestorID����ʱ���洢�Ĳ�ѯ����
	CBrokerIDType queryBrokerIDInSearchByBrokerIDInvestorID;
	CInvestorIDType queryInvestorIDInSearchByBrokerIDInvestorID;
	
	///����BrokerID��InvestorID����ʱ���洢���һ���ҵ��������ڵ�
	CAVLNode *pLastFoundInSearchByBrokerIDInvestorID;
	///����BrokerID����ʱ���洢�Ĳ�ѯ����
	CBrokerIDType queryBrokerIDInSearchAllByBrokerID;
	
	///����BrokerID����ʱ���洢���һ���ҵ��������ڵ�
	CClientTradingID *pLastFoundInSearchAllByBrokerID;
	///���ռ���ʱ���洢�Ĳ�ѯ����
	
	///���ռ���ʱ���洢���һ���ҵ��������ڵ�
	CClientTradingID *pLastFoundInSearchAll;
	
	///����ǰ����
	///@param	pClientTradingID	Ҫ�����ClientTradingID
	virtual void beforeAdd(CWriteableClientTradingID *pClientTradingID);
	
	///����󴥷�
	///@param	pClientTradingID	�Ѿ������ClientTradingID
	virtual void afterAdd(CClientTradingID *pClientTradingID);

	///����ǰ����	
	///@param	pClientTradingID	��ˢ�µ�CClientTradingID
	///@param	pNewClientTradingID	�µ�ֵ
	virtual void beforeUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID);
	
	///���º󴥷�
	///@param	pClientTradingID	��ˢ�µ�CClientTradingID
	virtual void afterUpdate(CClientTradingID *pClientTradingID);
	
	///ɾ��ǰ����
	///@param	pClientTradingID	Ҫɾ����CClientTradingID
	virtual void beforeRemove(CClientTradingID *pClientTradingID);
	
	///ȷ�ϼ���󴥷�
	///@param	pClientTradingID	�Ѿ������ClientTradingID
	virtual void commitAdd(CClientTradingID *pClientTradingID);

	///ȷ�ϸ��º󴥷�
	///@param	pClientTradingID	��ˢ�µ�CClientTradingID
	///@param	poldClientTradingID	ԭ����ֵ
	virtual void commitUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pOldClientTradingID);
	
	///ȷ��ɾ���󴥷�
	///@param	pClientTradingID	�Ѿ�ɾ����CClientTradingID
	virtual void commitRemove(CWriteableClientTradingID *pClientTradingID);

	///������صĴ�����
	vector<CClientTradingIDActionTrigger *> *pActionTriggers;
	vector<CClientTradingIDCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableClientTradingID compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFactory��һ��Ͷ������Ϣ��Ķ��󹤳�����������һ��Ͷ������Ϣ��
///ͬʱ�ֽ����������������Է����ѯ��
///	BrokerIDInvestorIDIndex
///ʹ�ñ����󹤳���������ɶ�Ͷ������Ϣ�����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrokerIDInvestorID��Ψһ�ҵ�����
///		ʹ��startFindByInvestorID��findNextByInvestorID��endFindByInvestorID��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInvestorFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxInvestor��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInvestorFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�Investor
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�Investor���ļ��������������ļ��еĶ���InvestorCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�Investor
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�Investor���ļ��������������ļ��еĶ���InvestorCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CInvestorResource;

	///��һ��CInvestor���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInvestor	Ҫ�����Investor
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInvestor *add(CWriteableInvestor *pInvestor, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CInvestor��ֵ
	///@param	pInvestor	��ˢ�µ�CInvestor
	///@param	pNewInvestor	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pInvestor	  ��Ҫ��ˢ�»���������CInvestor,����NULL��ʾ����Ҫ������
	///@param	pNewInvestor	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CInvestor* addOrUpdate(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CInvestor��ͬʱɾ��������
	///@param	pInvestor	Ҫɾ����CInvestor
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CInvestor *pInvestor, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CInvestor
	///@param	pInvestor	Ҫ��ȡ��CInvestor
	///@param	pTragetInvestor	��Ž����CInvestor
	void retrieve(CInvestor *pInvestor, CWriteableInvestor *pTargetInvestor);
	
	///��ȡ��һ��CInvestor
	///@return	�õ��ĵ�һ��CInvestor�����û�У��򷵻�NULL
	CInvestor *getFirst(void);
	
	///��ȡ��һ��CInvestor
	///@return	�õ���һ��CInvestor�����û�У��򷵻�NULL
	CInvestor *getNext(void);
	
	///������ȡCInvestor
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CInvestorActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CInvestorActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CInvestorCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CInvestorCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CInvestor
	///@param	BrokerID	���͹�˾����
	///@param	InvestorID	Ͷ���߱��
	///@return	�ҵ���CInvestor������Ҳ���������NULL
	CInvestor *findByBrokerIDInvestorID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInvestorIDType&  InvestorID);

	///��������Ѱ��
	///@param	BrokerID	���͹�˾����
	///@param	InvestorID	Ͷ���߱��
	///@return	�ҵ���CInvestor������Ҳ���������NULL
	CInvestor *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInvestorIDType&  InvestorID);
	
	///��������Ѱ��CInvestor
	///@param	pInvestor	Ҫ�ҵ�ֵ
	///@return	�ҵ���CInvestor������Ҳ���������NULL
	CInvestor *findByPK(CWriteableInvestor *pInvestor);

	///����������ȡCInvestor
	///@param	pInvestor	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CInvestor������Ҳ���������NULL
	bool retrieveByPK(CWriteableInvestor *pInvestor);

	///�������������µ�CInvestor
	///@param	pInvestor	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CInvestor���������ʧ�ܣ��򷵻�NULL
	CInvestor *addByPK(CWriteableInvestor *pInvestor, CTransaction *pTransaction=NULL);

	///������������CInvestor��ֵ
	///@param	pInvestor	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableInvestor *pInvestor, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CInvestor
	///@param	pInvestor	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableInvestor *pInvestor, CTransaction *pTransaction=NULL);


	friend class CInvestorIteratorByInvestorID;

	///��ʼѰ��CInvestor
	///@param	InvestorID	Ͷ���߱��
	///@return	���������ĵ�һ��CInvestor������Ҳ���������NULL
	CInvestor *startFindByInvestorID( const CReadOnlyInvestorIDType& InvestorID);

	///Ѱ����һ������������CInvestor��������startFindByInvestorID�Ժ�endFindByInvestorID֮ǰ����
	///@return	��һ����������CInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestor *findNextByInvestorID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindByInvestorID(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CInvestor���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInvestor	Ҫ�����Investor
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInvestor *internalAdd(CWriteableInvestor *pInvestor, bool bNoTransaction);
	
	
	///ˢ�¸�CInvestor�ļ�ֵ
	///@param	pInvestor	��ˢ�µ�CInvestor
	///@param	pNewInvestor	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CInvestor��ͬʱɾ��������
	///@param	pInvestor	Ҫɾ����CInvestor
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CInvestor *pInvestor, bool bNoTransaction);
/*
	///���ĳ��CInvestor�Ƿ����ڱ����󹤳�
	///@param	pInvestor	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CInvestor *pInvestor);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����BrokerID+InvestorID������
	CAVLTree *pBrokerIDInvestorIDIndex;
	
	
	///����InvestorID����ʱ���洢�Ĳ�ѯ����
	CInvestorIDType queryInvestorIDInSearchByInvestorID;
	
	///����InvestorID����ʱ���洢���һ���ҵ��������ڵ�
	CAVLNode *pLastFoundInSearchByInvestorID;
	
	///����ǰ����
	///@param	pInvestor	Ҫ�����Investor
	virtual void beforeAdd(CWriteableInvestor *pInvestor);
	
	///����󴥷�
	///@param	pInvestor	�Ѿ������Investor
	virtual void afterAdd(CInvestor *pInvestor);

	///����ǰ����	
	///@param	pInvestor	��ˢ�µ�CInvestor
	///@param	pNewInvestor	�µ�ֵ
	virtual void beforeUpdate(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor);
	
	///���º󴥷�
	///@param	pInvestor	��ˢ�µ�CInvestor
	virtual void afterUpdate(CInvestor *pInvestor);
	
	///ɾ��ǰ����
	///@param	pInvestor	Ҫɾ����CInvestor
	virtual void beforeRemove(CInvestor *pInvestor);
	
	///ȷ�ϼ���󴥷�
	///@param	pInvestor	�Ѿ������Investor
	virtual void commitAdd(CInvestor *pInvestor);

	///ȷ�ϸ��º󴥷�
	///@param	pInvestor	��ˢ�µ�CInvestor
	///@param	poldInvestor	ԭ����ֵ
	virtual void commitUpdate(CInvestor *pInvestor, CWriteableInvestor *pOldInvestor);
	
	///ȷ��ɾ���󴥷�
	///@param	pInvestor	�Ѿ�ɾ����CInvestor
	virtual void commitRemove(CWriteableInvestor *pInvestor);

	///������صĴ�����
	vector<CInvestorActionTrigger *> *pActionTriggers;
	vector<CInvestorCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableInvestor compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginFactory��һ���ͻ��ڻ���֤���ʱ�Ķ��󹤳�����������һ���ͻ��ڻ���֤���ʱ�
///ͬʱ�ֽ����������������Է����ѯ��
///	BrokerIDClientIDIndex
///	BrkIDExIDIstIDVstIDHdgIndex
///	BrkIDExIDIstIDVstIDIndex
///ʹ�ñ����󹤳���������ɶԿͻ��ڻ���֤���ʱ����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrokerIDClientID��Ψһ�ҵ�����
///		ʹ��findByBrkIDExIDIstIDVstIDHdg��Ψһ�ҵ�����
///		ʹ��startFindByBrkIDExIDIstIDVstID��findNextByBrkIDExIDIstIDVstID��endFindByBrkIDExIDIstIDVstID��ɲ�ѯ����
///		ʹ��startFindByInstrumentID��findNextByInstrumentID��endFindByInstrumentID��ɲ�ѯ����
///		ʹ��startFindByBrokerID��findNextByBrokerID��endFindByBrokerID��ɲ�ѯ����
///		ʹ��startFindAll��findNextAll��endFindAll��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInvestorMarginFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxInvestorMargin��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInvestorMarginFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorMarginFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�InvestorMargin
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�InvestorMargin���ļ��������������ļ��еĶ���InvestorMarginCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�InvestorMargin
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�InvestorMargin���ļ��������������ļ��еĶ���InvestorMarginCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CInvestorMarginResource;

	///��һ��CInvestorMargin���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInvestorMargin	Ҫ�����InvestorMargin
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInvestorMargin *add(CWriteableInvestorMargin *pInvestorMargin, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CInvestorMargin��ֵ
	///@param	pInvestorMargin	��ˢ�µ�CInvestorMargin
	///@param	pNewInvestorMargin	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pInvestorMargin	  ��Ҫ��ˢ�»���������CInvestorMargin,����NULL��ʾ����Ҫ������
	///@param	pNewInvestorMargin	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CInvestorMargin* addOrUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CInvestorMargin��ͬʱɾ��������
	///@param	pInvestorMargin	Ҫɾ����CInvestorMargin
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CInvestorMargin *pInvestorMargin, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CInvestorMargin
	///@param	pInvestorMargin	Ҫ��ȡ��CInvestorMargin
	///@param	pTragetInvestorMargin	��Ž����CInvestorMargin
	void retrieve(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pTargetInvestorMargin);
	
	///��ȡ��һ��CInvestorMargin
	///@return	�õ��ĵ�һ��CInvestorMargin�����û�У��򷵻�NULL
	CInvestorMargin *getFirst(void);
	
	///��ȡ��һ��CInvestorMargin
	///@return	�õ���һ��CInvestorMargin�����û�У��򷵻�NULL
	CInvestorMargin *getNext(void);
	
	///������ȡCInvestorMargin
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CInvestorMarginActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CInvestorMarginActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CInvestorMarginCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CInvestorMarginCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CInvestorMargin
	///@param	BrokerID	���͹�˾����
	///@param	InvestorID	�ͻ�����
	///@return	�ҵ���CInvestorMargin������Ҳ���������NULL
	CInvestorMargin *findByBrokerIDClientID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInvestorIDType&  InvestorID);



	///Ѱ��CInvestorMargin
	///@param	BrokerID	���͹�˾����
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ����
	///@param	InvestorID	Ͷ���߱���
	///@param	HedgeFlag	Ͷ���ױ���־
	///@return	�ҵ���CInvestorMargin������Ҳ���������NULL
	CInvestorMargin *findByBrkIDExIDIstIDVstIDHdg( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag);

	///��������Ѱ��
	///@param	BrokerID	���͹�˾����
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ����
	///@param	InvestorID	Ͷ���߱���
	///@param	HedgeFlag	Ͷ���ױ���־
	///@return	�ҵ���CInvestorMargin������Ҳ���������NULL
	CInvestorMargin *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag);
	
	///��������Ѱ��CInvestorMargin
	///@param	pInvestorMargin	Ҫ�ҵ�ֵ
	///@return	�ҵ���CInvestorMargin������Ҳ���������NULL
	CInvestorMargin *findByPK(CWriteableInvestorMargin *pInvestorMargin);

	///����������ȡCInvestorMargin
	///@param	pInvestorMargin	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CInvestorMargin������Ҳ���������NULL
	bool retrieveByPK(CWriteableInvestorMargin *pInvestorMargin);

	///�������������µ�CInvestorMargin
	///@param	pInvestorMargin	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CInvestorMargin���������ʧ�ܣ��򷵻�NULL
	CInvestorMargin *addByPK(CWriteableInvestorMargin *pInvestorMargin, CTransaction *pTransaction=NULL);

	///������������CInvestorMargin��ֵ
	///@param	pInvestorMargin	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableInvestorMargin *pInvestorMargin, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CInvestorMargin
	///@param	pInvestorMargin	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableInvestorMargin *pInvestorMargin, CTransaction *pTransaction=NULL);


	friend class CInvestorMarginIteratorByBrkIDExIDIstIDVstID;

	///��ʼѰ��CInvestorMargin
	///@param	BrokerID	���͹�˾����
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ����
	///@param	InvestorID	Ͷ���߱���
	///@return	���������ĵ�һ��CInvestorMargin������Ҳ���������NULL
	CInvestorMargin *startFindByBrkIDExIDIstIDVstID( const CReadOnlyBrokerIDType& BrokerID,  const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& InstrumentID,  const CReadOnlyInvestorIDType& InvestorID);

	///Ѱ����һ������������CInvestorMargin��������startFindByBrkIDExIDIstIDVstID�Ժ�endFindByBrkIDExIDIstIDVstID֮ǰ����
	///@return	��һ����������CInvestorMargin������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorMargin *findNextByBrkIDExIDIstIDVstID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindByBrkIDExIDIstIDVstID(void);

	friend class CInvestorMarginIteratorByInstrumentID;

	///��ʼѰ��CInvestorMargin
	///@param	InstrumentID	��Լ����
	///@return	���������ĵ�һ��CInvestorMargin������Ҳ���������NULL
	CInvestorMargin *startFindByInstrumentID( const CReadOnlyInstrumentIDType& InstrumentID);

	///Ѱ����һ������������CInvestorMargin��������startFindByInstrumentID�Ժ�endFindByInstrumentID֮ǰ����
	///@return	��һ����������CInvestorMargin������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorMargin *findNextByInstrumentID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindByInstrumentID(void);

	friend class CInvestorMarginIteratorByBrokerID;

	///��ʼѰ��CInvestorMargin
	///@param	BrokerID	��Լ����
	///@return	���������ĵ�һ��CInvestorMargin������Ҳ���������NULL
	CInvestorMargin *startFindByBrokerID( const CReadOnlyBrokerIDType& BrokerID);

	///Ѱ����һ������������CInvestorMargin��������startFindByBrokerID�Ժ�endFindByBrokerID֮ǰ����
	///@return	��һ����������CInvestorMargin������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorMargin *findNextByBrokerID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindByBrokerID(void);

	friend class CInvestorMarginIteratorAll;

	///��ʼѰ��CInvestorMargin
	///@return	���������ĵ�һ��CInvestorMargin������Ҳ���������NULL
	CInvestorMargin *startFindAll();

	///Ѱ����һ������������CInvestorMargin��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CInvestorMargin������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorMargin *findNextAll(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAll(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CInvestorMargin���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInvestorMargin	Ҫ�����InvestorMargin
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInvestorMargin *internalAdd(CWriteableInvestorMargin *pInvestorMargin, bool bNoTransaction);
	
	
	///ˢ�¸�CInvestorMargin�ļ�ֵ
	///@param	pInvestorMargin	��ˢ�µ�CInvestorMargin
	///@param	pNewInvestorMargin	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CInvestorMargin��ͬʱɾ��������
	///@param	pInvestorMargin	Ҫɾ����CInvestorMargin
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CInvestorMargin *pInvestorMargin, bool bNoTransaction);
/*
	///���ĳ��CInvestorMargin�Ƿ����ڱ����󹤳�
	///@param	pInvestorMargin	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CInvestorMargin *pInvestorMargin);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����BrokerID+InvestorID������
	CAVLTree *pBrokerIDClientIDIndex;
	///����BrokerID+ExchangeID+InstrumentID+InvestorID+HedgeFlag������
	CAVLTree *pBrkIDExIDIstIDVstIDHdgIndex;
	///����BrokerID+ExchangeID+InstrumentID+InvestorID������
	CAVLTree *pBrkIDExIDIstIDVstIDIndex;
	
	///����InstrumentAndClientID��hash����
	CHashIndex *pInstrumentAndClientID;
	
	///����BrokerID��ExchangeID��InstrumentID��InvestorID����ʱ���洢�Ĳ�ѯ����
	CBrokerIDType queryBrokerIDInSearchByBrkIDExIDIstIDVstID;
	CExchangeIDType queryExchangeIDInSearchByBrkIDExIDIstIDVstID;
	CInstrumentIDType queryInstrumentIDInSearchByBrkIDExIDIstIDVstID;
	CInvestorIDType queryInvestorIDInSearchByBrkIDExIDIstIDVstID;
	
	///����BrokerID��ExchangeID��InstrumentID��InvestorID����ʱ���洢���һ���ҵ��������ڵ�
	CAVLNode *pLastFoundInSearchByBrkIDExIDIstIDVstID;
	///����InstrumentID����ʱ���洢�Ĳ�ѯ����
	CInstrumentIDType queryInstrumentIDInSearchByInstrumentID;
	
	///����InstrumentID����ʱ���洢���һ���ҵ��������ڵ�
	CInvestorMargin *pLastFoundInSearchByInstrumentID;
	///����BrokerID����ʱ���洢�Ĳ�ѯ����
	CBrokerIDType queryBrokerIDInSearchByBrokerID;
	
	///����BrokerID����ʱ���洢���һ���ҵ��������ڵ�
	CInvestorMargin *pLastFoundInSearchByBrokerID;
	///���ռ���ʱ���洢�Ĳ�ѯ����
	
	///���ռ���ʱ���洢���һ���ҵ��������ڵ�
	CInvestorMargin *pLastFoundInSearchAll;
	
	///����ǰ����
	///@param	pInvestorMargin	Ҫ�����InvestorMargin
	virtual void beforeAdd(CWriteableInvestorMargin *pInvestorMargin);
	
	///����󴥷�
	///@param	pInvestorMargin	�Ѿ������InvestorMargin
	virtual void afterAdd(CInvestorMargin *pInvestorMargin);

	///����ǰ����	
	///@param	pInvestorMargin	��ˢ�µ�CInvestorMargin
	///@param	pNewInvestorMargin	�µ�ֵ
	virtual void beforeUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin);
	
	///���º󴥷�
	///@param	pInvestorMargin	��ˢ�µ�CInvestorMargin
	virtual void afterUpdate(CInvestorMargin *pInvestorMargin);
	
	///ɾ��ǰ����
	///@param	pInvestorMargin	Ҫɾ����CInvestorMargin
	virtual void beforeRemove(CInvestorMargin *pInvestorMargin);
	
	///ȷ�ϼ���󴥷�
	///@param	pInvestorMargin	�Ѿ������InvestorMargin
	virtual void commitAdd(CInvestorMargin *pInvestorMargin);

	///ȷ�ϸ��º󴥷�
	///@param	pInvestorMargin	��ˢ�µ�CInvestorMargin
	///@param	poldInvestorMargin	ԭ����ֵ
	virtual void commitUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pOldInvestorMargin);
	
	///ȷ��ɾ���󴥷�
	///@param	pInvestorMargin	�Ѿ�ɾ����CInvestorMargin
	virtual void commitRemove(CWriteableInvestorMargin *pInvestorMargin);

	///������صĴ�����
	vector<CInvestorMarginActionTrigger *> *pActionTriggers;
	vector<CInvestorMarginCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableInvestorMargin compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeFactory��һ���ͻ��������ʱ�Ķ��󹤳�����������һ���ͻ��������ʱ�
///ͬʱ�ֽ����������������Է����ѯ��
///	InstrumentIDIndex
///	BrkIDExIDIstIDVstIDHdgIndex
///ʹ�ñ����󹤳���������ɶԿͻ��������ʱ����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrkIDExIDIstIDVstIDHdg��Ψһ�ҵ�����
///		ʹ��startFindByInstrumentID��findNextByInstrumentID��endFindByInstrumentID��ɲ�ѯ����
///		ʹ��startFindByBrokerID��findNextByBrokerID��endFindByBrokerID��ɲ�ѯ����
///		ʹ��startFindAll��findNextAll��endFindAll��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInvestorFeeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxInvestorFee��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInvestorFeeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorFeeFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�InvestorFee
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�InvestorFee���ļ��������������ļ��еĶ���InvestorFeeCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�InvestorFee
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�InvestorFee���ļ��������������ļ��еĶ���InvestorFeeCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CInvestorFeeResource;

	///��һ��CInvestorFee���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInvestorFee	Ҫ�����InvestorFee
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInvestorFee *add(CWriteableInvestorFee *pInvestorFee, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CInvestorFee��ֵ
	///@param	pInvestorFee	��ˢ�µ�CInvestorFee
	///@param	pNewInvestorFee	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pInvestorFee	  ��Ҫ��ˢ�»���������CInvestorFee,����NULL��ʾ����Ҫ������
	///@param	pNewInvestorFee	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CInvestorFee* addOrUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CInvestorFee��ͬʱɾ��������
	///@param	pInvestorFee	Ҫɾ����CInvestorFee
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CInvestorFee *pInvestorFee, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CInvestorFee
	///@param	pInvestorFee	Ҫ��ȡ��CInvestorFee
	///@param	pTragetInvestorFee	��Ž����CInvestorFee
	void retrieve(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pTargetInvestorFee);
	
	///��ȡ��һ��CInvestorFee
	///@return	�õ��ĵ�һ��CInvestorFee�����û�У��򷵻�NULL
	CInvestorFee *getFirst(void);
	
	///��ȡ��һ��CInvestorFee
	///@return	�õ���һ��CInvestorFee�����û�У��򷵻�NULL
	CInvestorFee *getNext(void);
	
	///������ȡCInvestorFee
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CInvestorFeeActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CInvestorFeeActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CInvestorFeeCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CInvestorFeeCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CInvestorFee
	///@param	BrokerID	���͹�˾����
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ����
	///@param	InvestorID	�ͻ���
	///@param	HedgeFlag	Ͷ���ױ���־
	///@return	�ҵ���CInvestorFee������Ҳ���������NULL
	CInvestorFee *findByBrkIDExIDIstIDVstIDHdg( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag);

	///��������Ѱ��
	///@param	BrokerID	���͹�˾����
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ����
	///@param	InvestorID	�ͻ���
	///@param	HedgeFlag	Ͷ���ױ���־
	///@return	�ҵ���CInvestorFee������Ҳ���������NULL
	CInvestorFee *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyHedgeFlagType&  HedgeFlag);
	
	///��������Ѱ��CInvestorFee
	///@param	pInvestorFee	Ҫ�ҵ�ֵ
	///@return	�ҵ���CInvestorFee������Ҳ���������NULL
	CInvestorFee *findByPK(CWriteableInvestorFee *pInvestorFee);

	///����������ȡCInvestorFee
	///@param	pInvestorFee	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CInvestorFee������Ҳ���������NULL
	bool retrieveByPK(CWriteableInvestorFee *pInvestorFee);

	///�������������µ�CInvestorFee
	///@param	pInvestorFee	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CInvestorFee���������ʧ�ܣ��򷵻�NULL
	CInvestorFee *addByPK(CWriteableInvestorFee *pInvestorFee, CTransaction *pTransaction=NULL);

	///������������CInvestorFee��ֵ
	///@param	pInvestorFee	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableInvestorFee *pInvestorFee, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CInvestorFee
	///@param	pInvestorFee	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableInvestorFee *pInvestorFee, CTransaction *pTransaction=NULL);


	friend class CInvestorFeeIteratorByInstrumentID;

	///��ʼѰ��CInvestorFee
	///@param	InstrumentID	��Լ���
	///@return	���������ĵ�һ��CInvestorFee������Ҳ���������NULL
	CInvestorFee *startFindByInstrumentID( const CReadOnlyInstrumentIDType& InstrumentID);

	///Ѱ����һ������������CInvestorFee��������startFindByInstrumentID�Ժ�endFindByInstrumentID֮ǰ����
	///@return	��һ����������CInvestorFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorFee *findNextByInstrumentID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindByInstrumentID(void);

	friend class CInvestorFeeIteratorByBrokerID;

	///��ʼѰ��CInvestorFee
	///@param	BrokerID	��Լ���
	///@return	���������ĵ�һ��CInvestorFee������Ҳ���������NULL
	CInvestorFee *startFindByBrokerID( const CReadOnlyBrokerIDType& BrokerID);

	///Ѱ����һ������������CInvestorFee��������startFindByBrokerID�Ժ�endFindByBrokerID֮ǰ����
	///@return	��һ����������CInvestorFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorFee *findNextByBrokerID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindByBrokerID(void);

	friend class CInvestorFeeIteratorAll;

	///��ʼѰ��CInvestorFee
	///@return	���������ĵ�һ��CInvestorFee������Ҳ���������NULL
	CInvestorFee *startFindAll();

	///Ѱ����һ������������CInvestorFee��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CInvestorFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CInvestorFee *findNextAll(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAll(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CInvestorFee���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInvestorFee	Ҫ�����InvestorFee
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInvestorFee *internalAdd(CWriteableInvestorFee *pInvestorFee, bool bNoTransaction);
	
	
	///ˢ�¸�CInvestorFee�ļ�ֵ
	///@param	pInvestorFee	��ˢ�µ�CInvestorFee
	///@param	pNewInvestorFee	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CInvestorFee��ͬʱɾ��������
	///@param	pInvestorFee	Ҫɾ����CInvestorFee
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CInvestorFee *pInvestorFee, bool bNoTransaction);
/*
	///���ĳ��CInvestorFee�Ƿ����ڱ����󹤳�
	///@param	pInvestorFee	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CInvestorFee *pInvestorFee);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����InstrumentID������
	CAVLTree *pInstrumentIDIndex;
	///����BrokerID+ExchangeID+InstrumentID+InvestorID+HedgeFlag������
	CAVLTree *pBrkIDExIDIstIDVstIDHdgIndex;
	
	
	///����InstrumentID����ʱ���洢�Ĳ�ѯ����
	CInstrumentIDType queryInstrumentIDInSearchByInstrumentID;
	
	///����InstrumentID����ʱ���洢���һ���ҵ��������ڵ�
	CAVLNode *pLastFoundInSearchByInstrumentID;
	///����BrokerID����ʱ���洢�Ĳ�ѯ����
	CBrokerIDType queryBrokerIDInSearchByBrokerID;
	
	///����BrokerID����ʱ���洢���һ���ҵ��������ڵ�
	CInvestorFee *pLastFoundInSearchByBrokerID;
	///���ռ���ʱ���洢�Ĳ�ѯ����
	
	///���ռ���ʱ���洢���һ���ҵ��������ڵ�
	CInvestorFee *pLastFoundInSearchAll;
	
	///����ǰ����
	///@param	pInvestorFee	Ҫ�����InvestorFee
	virtual void beforeAdd(CWriteableInvestorFee *pInvestorFee);
	
	///����󴥷�
	///@param	pInvestorFee	�Ѿ������InvestorFee
	virtual void afterAdd(CInvestorFee *pInvestorFee);

	///����ǰ����	
	///@param	pInvestorFee	��ˢ�µ�CInvestorFee
	///@param	pNewInvestorFee	�µ�ֵ
	virtual void beforeUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee);
	
	///���º󴥷�
	///@param	pInvestorFee	��ˢ�µ�CInvestorFee
	virtual void afterUpdate(CInvestorFee *pInvestorFee);
	
	///ɾ��ǰ����
	///@param	pInvestorFee	Ҫɾ����CInvestorFee
	virtual void beforeRemove(CInvestorFee *pInvestorFee);
	
	///ȷ�ϼ���󴥷�
	///@param	pInvestorFee	�Ѿ������InvestorFee
	virtual void commitAdd(CInvestorFee *pInvestorFee);

	///ȷ�ϸ��º󴥷�
	///@param	pInvestorFee	��ˢ�µ�CInvestorFee
	///@param	poldInvestorFee	ԭ����ֵ
	virtual void commitUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pOldInvestorFee);
	
	///ȷ��ɾ���󴥷�
	///@param	pInvestorFee	�Ѿ�ɾ����CInvestorFee
	virtual void commitRemove(CWriteableInvestorFee *pInvestorFee);

	///������صĴ�����
	vector<CInvestorFeeActionTrigger *> *pActionTriggers;
	vector<CInvestorFeeCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableInvestorFee compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CUserFactory��һ���û���Ķ��󹤳�����������һ���û���
///ͬʱ�ֽ����������������Է����ѯ��
///	BrokerIDUserIDIndex
///	UserIDIndex
///ʹ�ñ����󹤳���������ɶ��û������ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrokerIDUserID��Ψһ�ҵ�����
///		ʹ��startFindStartByUserID��findNextStartByUserID��endFindStartByUserID��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CUserFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxUser��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CUserFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�User
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�User���ļ��������������ļ��еĶ���UserCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�User
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�User���ļ��������������ļ��еĶ���UserCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CUserResource;

	///��һ��CUser���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pUser	Ҫ�����User
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CUser *add(CWriteableUser *pUser, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CUser��ֵ
	///@param	pUser	��ˢ�µ�CUser
	///@param	pNewUser	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CUser *pUser, CWriteableUser *pNewUser, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pUser	  ��Ҫ��ˢ�»���������CUser,����NULL��ʾ����Ҫ������
	///@param	pNewUser	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CUser* addOrUpdate(CUser *pUser, CWriteableUser *pNewUser, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CUser��ͬʱɾ��������
	///@param	pUser	Ҫɾ����CUser
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CUser *pUser, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CUser
	///@param	pUser	Ҫ��ȡ��CUser
	///@param	pTragetUser	��Ž����CUser
	void retrieve(CUser *pUser, CWriteableUser *pTargetUser);
	
	///��ȡ��һ��CUser
	///@return	�õ��ĵ�һ��CUser�����û�У��򷵻�NULL
	CUser *getFirst(void);
	
	///��ȡ��һ��CUser
	///@return	�õ���һ��CUser�����û�У��򷵻�NULL
	CUser *getNext(void);
	
	///������ȡCUser
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CUserActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CUserActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CUserCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CUserCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CUser
	///@param	BrokerID	���͹�˾����
	///@param	UserID	�����û�����
	///@return	�ҵ���CUser������Ҳ���������NULL
	CUser *findByBrokerIDUserID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID);

	///��������Ѱ��
	///@param	BrokerID	���͹�˾����
	///@param	UserID	�����û�����
	///@return	�ҵ���CUser������Ҳ���������NULL
	CUser *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID);
	
	///��������Ѱ��CUser
	///@param	pUser	Ҫ�ҵ�ֵ
	///@return	�ҵ���CUser������Ҳ���������NULL
	CUser *findByPK(CWriteableUser *pUser);

	///����������ȡCUser
	///@param	pUser	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CUser������Ҳ���������NULL
	bool retrieveByPK(CWriteableUser *pUser);

	///�������������µ�CUser
	///@param	pUser	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CUser���������ʧ�ܣ��򷵻�NULL
	CUser *addByPK(CWriteableUser *pUser, CTransaction *pTransaction=NULL);

	///������������CUser��ֵ
	///@param	pUser	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableUser *pUser, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CUser
	///@param	pUser	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableUser *pUser, CTransaction *pTransaction=NULL);


	friend class CUserIteratorStartByUserID;

	///��ʼѰ��CUser
	///@param	UserID	�û����
	///@return	���������ĵ�һ��CUser������Ҳ���������NULL
	CUser *startFindStartByUserID( const CReadOnlyUserIDType& UserID);

	///Ѱ����һ������������CUser��������startFindStartByUserID�Ժ�endFindStartByUserID֮ǰ����
	///@return	��һ����������CUser������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CUser *findNextStartByUserID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindStartByUserID(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CUser���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pUser	Ҫ�����User
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CUser *internalAdd(CWriteableUser *pUser, bool bNoTransaction);
	
	
	///ˢ�¸�CUser�ļ�ֵ
	///@param	pUser	��ˢ�µ�CUser
	///@param	pNewUser	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CUser *pUser, CWriteableUser *pNewUser, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CUser��ͬʱɾ��������
	///@param	pUser	Ҫɾ����CUser
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CUser *pUser, bool bNoTransaction);
/*
	///���ĳ��CUser�Ƿ����ڱ����󹤳�
	///@param	pUser	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CUser *pUser);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����BrokerID+UserID������
	CAVLTree *pBrokerIDUserIDIndex;
	///����UserID������
	CAVLTree *pUserIDIndex;
	
	
	///����UserID����ʱ���洢�Ĳ�ѯ����
	CUserIDType queryUserIDInSearchStartByUserID;
	
	///����UserID����ʱ���洢���һ���ҵ��������ڵ�
	CAVLNode *pLastFoundInSearchStartByUserID;
	
	///����ǰ����
	///@param	pUser	Ҫ�����User
	virtual void beforeAdd(CWriteableUser *pUser);
	
	///����󴥷�
	///@param	pUser	�Ѿ������User
	virtual void afterAdd(CUser *pUser);

	///����ǰ����	
	///@param	pUser	��ˢ�µ�CUser
	///@param	pNewUser	�µ�ֵ
	virtual void beforeUpdate(CUser *pUser, CWriteableUser *pNewUser);
	
	///���º󴥷�
	///@param	pUser	��ˢ�µ�CUser
	virtual void afterUpdate(CUser *pUser);
	
	///ɾ��ǰ����
	///@param	pUser	Ҫɾ����CUser
	virtual void beforeRemove(CUser *pUser);
	
	///ȷ�ϼ���󴥷�
	///@param	pUser	�Ѿ������User
	virtual void commitAdd(CUser *pUser);

	///ȷ�ϸ��º󴥷�
	///@param	pUser	��ˢ�µ�CUser
	///@param	poldUser	ԭ����ֵ
	virtual void commitUpdate(CUser *pUser, CWriteableUser *pOldUser);
	
	///ȷ��ɾ���󴥷�
	///@param	pUser	�Ѿ�ɾ����CUser
	virtual void commitRemove(CWriteableUser *pUser);

	///������صĴ�����
	vector<CUserActionTrigger *> *pActionTriggers;
	vector<CUserCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableUser compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorFactory��һ���û�Ͷ���߹�ϵ��Ķ��󹤳�����������һ���û�Ͷ���߹�ϵ��
///ͬʱ�ֽ����������������Է����ѯ��
///	BrokerIDUserIDInvestorIDIndex
///	BrokerIDInvestorIDIndex
///ʹ�ñ����󹤳���������ɶ��û�Ͷ���߹�ϵ�����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrokerIDUserIDInvestorID��Ψһ�ҵ�����
///		ʹ��startFindByBrokerIDInvestorID��findNextByBrokerIDInvestorID��endFindByBrokerIDInvestorID��ɲ�ѯ����
///		ʹ��startFindAllByUserID��findNextAllByUserID��endFindAllByUserID��ɲ�ѯ����
///		ʹ��startFindAllByBrokerIDUserID��findNextAllByBrokerIDUserID��endFindAllByBrokerIDUserID��ɲ�ѯ����
///		ʹ��startFindAllByBrokerID��findNextAllByBrokerID��endFindAllByBrokerID��ɲ�ѯ����
///		ʹ��startFindAll��findNextAll��endFindAll��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CUserInvestorFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxUserInvestor��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CUserInvestorFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserInvestorFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�UserInvestor
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�UserInvestor���ļ��������������ļ��еĶ���UserInvestorCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�UserInvestor
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�UserInvestor���ļ��������������ļ��еĶ���UserInvestorCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CUserInvestorResource;

	///��һ��CUserInvestor���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pUserInvestor	Ҫ�����UserInvestor
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CUserInvestor *add(CWriteableUserInvestor *pUserInvestor, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CUserInvestor��ֵ
	///@param	pUserInvestor	��ˢ�µ�CUserInvestor
	///@param	pNewUserInvestor	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pUserInvestor	  ��Ҫ��ˢ�»���������CUserInvestor,����NULL��ʾ����Ҫ������
	///@param	pNewUserInvestor	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CUserInvestor* addOrUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CUserInvestor��ͬʱɾ��������
	///@param	pUserInvestor	Ҫɾ����CUserInvestor
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CUserInvestor *pUserInvestor, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CUserInvestor
	///@param	pUserInvestor	Ҫ��ȡ��CUserInvestor
	///@param	pTragetUserInvestor	��Ž����CUserInvestor
	void retrieve(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pTargetUserInvestor);
	
	///��ȡ��һ��CUserInvestor
	///@return	�õ��ĵ�һ��CUserInvestor�����û�У��򷵻�NULL
	CUserInvestor *getFirst(void);
	
	///��ȡ��һ��CUserInvestor
	///@return	�õ���һ��CUserInvestor�����û�У��򷵻�NULL
	CUserInvestor *getNext(void);
	
	///������ȡCUserInvestor
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CUserInvestorActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CUserInvestorActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CUserInvestorCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CUserInvestorCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CUserInvestor
	///@param	BrokerID	���͹�˾����
	///@param	UserID	�����û�����
	///@param	InvestorID	Ͷ���߱��
	///@return	�ҵ���CUserInvestor������Ҳ���������NULL
	CUserInvestor *findByBrokerIDUserIDInvestorID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyInvestorIDType&  InvestorID);

	///��������Ѱ��
	///@param	BrokerID	���͹�˾����
	///@param	UserID	�����û�����
	///@param	InvestorID	Ͷ���߱��
	///@return	�ҵ���CUserInvestor������Ҳ���������NULL
	CUserInvestor *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyInvestorIDType&  InvestorID);
	
	///��������Ѱ��CUserInvestor
	///@param	pUserInvestor	Ҫ�ҵ�ֵ
	///@return	�ҵ���CUserInvestor������Ҳ���������NULL
	CUserInvestor *findByPK(CWriteableUserInvestor *pUserInvestor);

	///����������ȡCUserInvestor
	///@param	pUserInvestor	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CUserInvestor������Ҳ���������NULL
	bool retrieveByPK(CWriteableUserInvestor *pUserInvestor);

	///�������������µ�CUserInvestor
	///@param	pUserInvestor	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CUserInvestor���������ʧ�ܣ��򷵻�NULL
	CUserInvestor *addByPK(CWriteableUserInvestor *pUserInvestor, CTransaction *pTransaction=NULL);

	///������������CUserInvestor��ֵ
	///@param	pUserInvestor	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableUserInvestor *pUserInvestor, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CUserInvestor
	///@param	pUserInvestor	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableUserInvestor *pUserInvestor, CTransaction *pTransaction=NULL);


	friend class CUserInvestorIteratorByBrokerIDInvestorID;

	///��ʼѰ��CUserInvestor
	///@param	BrokerID	���͹�˾����
	///@param	InvestorID	Ͷ���߱��
	///@return	���������ĵ�һ��CUserInvestor������Ҳ���������NULL
	CUserInvestor *startFindByBrokerIDInvestorID( const CReadOnlyBrokerIDType& BrokerID,  const CReadOnlyInvestorIDType& InvestorID);

	///Ѱ����һ������������CUserInvestor��������startFindByBrokerIDInvestorID�Ժ�endFindByBrokerIDInvestorID֮ǰ����
	///@return	��һ����������CUserInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CUserInvestor *findNextByBrokerIDInvestorID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindByBrokerIDInvestorID(void);

	friend class CUserInvestorIteratorAllByUserID;

	///��ʼѰ��CUserInvestor
	///@param	UserID	��Ա����
	///@return	���������ĵ�һ��CUserInvestor������Ҳ���������NULL
	CUserInvestor *startFindAllByUserID( const CReadOnlyUserIDType& UserID);

	///Ѱ����һ������������CUserInvestor��������startFindAllByUserID�Ժ�endFindAllByUserID֮ǰ����
	///@return	��һ����������CUserInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CUserInvestor *findNextAllByUserID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByUserID(void);

	friend class CUserInvestorIteratorAllByBrokerIDUserID;

	///��ʼѰ��CUserInvestor
	///@param	BrokerID	���͹�˾����
	///@param	UserID	��Ա����
	///@return	���������ĵ�һ��CUserInvestor������Ҳ���������NULL
	CUserInvestor *startFindAllByBrokerIDUserID( const CReadOnlyBrokerIDType& BrokerID,  const CReadOnlyUserIDType& UserID);

	///Ѱ����һ������������CUserInvestor��������startFindAllByBrokerIDUserID�Ժ�endFindAllByBrokerIDUserID֮ǰ����
	///@return	��һ����������CUserInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CUserInvestor *findNextAllByBrokerIDUserID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByBrokerIDUserID(void);

	friend class CUserInvestorIteratorAllByBrokerID;

	///��ʼѰ��CUserInvestor
	///@param	BrokerID	���͹�˾����
	///@return	���������ĵ�һ��CUserInvestor������Ҳ���������NULL
	CUserInvestor *startFindAllByBrokerID( const CReadOnlyBrokerIDType& BrokerID);

	///Ѱ����һ������������CUserInvestor��������startFindAllByBrokerID�Ժ�endFindAllByBrokerID֮ǰ����
	///@return	��һ����������CUserInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CUserInvestor *findNextAllByBrokerID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByBrokerID(void);

	friend class CUserInvestorIteratorAll;

	///��ʼѰ��CUserInvestor
	///@return	���������ĵ�һ��CUserInvestor������Ҳ���������NULL
	CUserInvestor *startFindAll();

	///Ѱ����һ������������CUserInvestor��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CUserInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CUserInvestor *findNextAll(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAll(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CUserInvestor���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pUserInvestor	Ҫ�����UserInvestor
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CUserInvestor *internalAdd(CWriteableUserInvestor *pUserInvestor, bool bNoTransaction);
	
	
	///ˢ�¸�CUserInvestor�ļ�ֵ
	///@param	pUserInvestor	��ˢ�µ�CUserInvestor
	///@param	pNewUserInvestor	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CUserInvestor��ͬʱɾ��������
	///@param	pUserInvestor	Ҫɾ����CUserInvestor
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CUserInvestor *pUserInvestor, bool bNoTransaction);
/*
	///���ĳ��CUserInvestor�Ƿ����ڱ����󹤳�
	///@param	pUserInvestor	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CUserInvestor *pUserInvestor);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����BrokerID+UserID+InvestorID������
	CAVLTree *pBrokerIDUserIDInvestorIDIndex;
	///����BrokerID+InvestorID������
	CAVLTree *pBrokerIDInvestorIDIndex;
	
	
	///����BrokerID��InvestorID����ʱ���洢�Ĳ�ѯ����
	CBrokerIDType queryBrokerIDInSearchByBrokerIDInvestorID;
	CInvestorIDType queryInvestorIDInSearchByBrokerIDInvestorID;
	
	///����BrokerID��InvestorID����ʱ���洢���һ���ҵ��������ڵ�
	CAVLNode *pLastFoundInSearchByBrokerIDInvestorID;
	///����UserID����ʱ���洢�Ĳ�ѯ����
	CUserIDType queryUserIDInSearchAllByUserID;
	
	///����UserID����ʱ���洢���һ���ҵ��������ڵ�
	CUserInvestor *pLastFoundInSearchAllByUserID;
	///����BrokerID��UserID����ʱ���洢�Ĳ�ѯ����
	CBrokerIDType queryBrokerIDInSearchAllByBrokerIDUserID;
	CUserIDType queryUserIDInSearchAllByBrokerIDUserID;
	
	///����BrokerID��UserID����ʱ���洢���һ���ҵ��������ڵ�
	CUserInvestor *pLastFoundInSearchAllByBrokerIDUserID;
	///����BrokerID����ʱ���洢�Ĳ�ѯ����
	CBrokerIDType queryBrokerIDInSearchAllByBrokerID;
	
	///����BrokerID����ʱ���洢���һ���ҵ��������ڵ�
	CUserInvestor *pLastFoundInSearchAllByBrokerID;
	///���ռ���ʱ���洢�Ĳ�ѯ����
	
	///���ռ���ʱ���洢���һ���ҵ��������ڵ�
	CUserInvestor *pLastFoundInSearchAll;
	
	///����ǰ����
	///@param	pUserInvestor	Ҫ�����UserInvestor
	virtual void beforeAdd(CWriteableUserInvestor *pUserInvestor);
	
	///����󴥷�
	///@param	pUserInvestor	�Ѿ������UserInvestor
	virtual void afterAdd(CUserInvestor *pUserInvestor);

	///����ǰ����	
	///@param	pUserInvestor	��ˢ�µ�CUserInvestor
	///@param	pNewUserInvestor	�µ�ֵ
	virtual void beforeUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor);
	
	///���º󴥷�
	///@param	pUserInvestor	��ˢ�µ�CUserInvestor
	virtual void afterUpdate(CUserInvestor *pUserInvestor);
	
	///ɾ��ǰ����
	///@param	pUserInvestor	Ҫɾ����CUserInvestor
	virtual void beforeRemove(CUserInvestor *pUserInvestor);
	
	///ȷ�ϼ���󴥷�
	///@param	pUserInvestor	�Ѿ������UserInvestor
	virtual void commitAdd(CUserInvestor *pUserInvestor);

	///ȷ�ϸ��º󴥷�
	///@param	pUserInvestor	��ˢ�µ�CUserInvestor
	///@param	poldUserInvestor	ԭ����ֵ
	virtual void commitUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pOldUserInvestor);
	
	///ȷ��ɾ���󴥷�
	///@param	pUserInvestor	�Ѿ�ɾ����CUserInvestor
	virtual void commitRemove(CWriteableUserInvestor *pUserInvestor);

	///������صĴ�����
	vector<CUserInvestorActionTrigger *> *pActionTriggers;
	vector<CUserInvestorCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableUserInvestor compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedFactory��һ������Ķ��󹤳�����������һ������
///ͬʱ�ֽ����������������Է����ѯ��
///	OrderUserIDIndex
///	OrderLocalIDIndex
///	ExchangeIDOrderSysIDIndex
///	ExchangeIDSeatIDOrderLocalIDIndex
///ʹ�ñ����󹤳���������ɶԴ������ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByOrderUserID��Ψһ�ҵ�����
///		ʹ��findByOrderLocalID��Ψһ�ҵ�����
///		ʹ��findByExchangeIDAndOrderSysID��Ψһ�ҵ�����
///		ʹ��startFindAllByExchIDInvIDUserID��findNextAllByExchIDInvIDUserID��endFindAllByExchIDInvIDUserID��ɲ�ѯ����
///		ʹ��startFindAllByExchIDInstruIDUserID��findNextAllByExchIDInstruIDUserID��endFindAllByExchIDInstruIDUserID��ɲ�ѯ����
///		ʹ��startFindAll��findNextAll��endFindAll��ɲ�ѯ����
///		ʹ��findByExchangeIDSeatIDAndOrderLocalID��Ψһ�ҵ�����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	COrderInsertFailedFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxOrderInsertFailed��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	COrderInsertFailedFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~COrderInsertFailedFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�OrderInsertFailed
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�OrderInsertFailed���ļ��������������ļ��еĶ���OrderInsertFailedCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�OrderInsertFailed
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�OrderInsertFailed���ļ��������������ļ��еĶ���OrderInsertFailedCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class COrderInsertFailedResource;

	///��һ��COrderInsertFailed���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pOrderInsertFailed	Ҫ�����OrderInsertFailed
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	COrderInsertFailed *add(CWriteableOrderInsertFailed *pOrderInsertFailed, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�COrderInsertFailed��ֵ
	///@param	pOrderInsertFailed	��ˢ�µ�COrderInsertFailed
	///@param	pNewOrderInsertFailed	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pOrderInsertFailed	  ��Ҫ��ˢ�»���������COrderInsertFailed,����NULL��ʾ����Ҫ������
	///@param	pNewOrderInsertFailed	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	COrderInsertFailed* addOrUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��COrderInsertFailed��ͬʱɾ��������
	///@param	pOrderInsertFailed	Ҫɾ����COrderInsertFailed
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(COrderInsertFailed *pOrderInsertFailed, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��COrderInsertFailed
	///@param	pOrderInsertFailed	Ҫ��ȡ��COrderInsertFailed
	///@param	pTragetOrderInsertFailed	��Ž����COrderInsertFailed
	void retrieve(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pTargetOrderInsertFailed);
	
	///��ȡ��һ��COrderInsertFailed
	///@return	�õ��ĵ�һ��COrderInsertFailed�����û�У��򷵻�NULL
	COrderInsertFailed *getFirst(void);
	
	///��ȡ��һ��COrderInsertFailed
	///@return	�õ���һ��COrderInsertFailed�����û�У��򷵻�NULL
	COrderInsertFailed *getNext(void);
	
	///������ȡCOrderInsertFailed
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(COrderInsertFailedActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(COrderInsertFailedActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(COrderInsertFailedCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(COrderInsertFailedCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///�������ж�Ӧ���ʻ���ָ��
	///@param	pFactory	�����Ӧ���ʻ���ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorAccount(CInvestorAccountFactory *pFactory);
	
	///�������ж�Ӧ�ĺ�Լ�ֲ���Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ�ֲ���Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorPosition(CInvestorPositionFactory *pFactory);
	
	///�������ж�Ӧ�ĺ�Լ��Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ��Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInstrument(CInstrumentFactory *pFactory);
	
	///�������ж�Ӧ��Ͷ���߱�֤������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ���߱�֤������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorMargin(CInvestorMarginFactory *pFactory);
	
	///�������ж�Ӧ��Ͷ��������������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ��������������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllInvestorFee(CInvestorFeeFactory *pFactory);
	
	///Ѱ��COrderInsertFailed
	///@param	OrderUserID	�����û�����
	///@return	�ҵ���COrderInsertFailed������Ҳ���������NULL
	COrderInsertFailed *findByOrderUserID( const CReadOnlyUserIDType&  OrderUserID);



	///Ѱ��COrderInsertFailed
	///@param	OrderLocalID	���ر�����
	///@return	�ҵ���COrderInsertFailed������Ҳ���������NULL
	COrderInsertFailed *findByOrderLocalID( const CReadOnlyOrderLocalIDType&  OrderLocalID);



	///Ѱ��COrderInsertFailed
	///@param	ExchangeID	����������
	///@param	OrderSysID	�ʽ��ʺ�
	///@return	�ҵ���COrderInsertFailed������Ҳ���������NULL
	COrderInsertFailed *findByExchangeIDAndOrderSysID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyOrderSysIDType&  OrderSysID);



	friend class COrderInsertFailedIteratorAllByExchIDInvIDUserID;

	///��ʼѰ��COrderInsertFailed
	///@param	ExchangeID	����������
	///@param	InvestorID	Ͷ���߱��
	///@param	UserID	�����û�����
	///@return	���������ĵ�һ��COrderInsertFailed������Ҳ���������NULL
	COrderInsertFailed *startFindAllByExchIDInvIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInvestorIDType& InvestorID,  const CReadOnlyUserIDType& UserID);

	///Ѱ����һ������������COrderInsertFailed��������startFindAllByExchIDInvIDUserID�Ժ�endFindAllByExchIDInvIDUserID֮ǰ����
	///@return	��һ����������COrderInsertFailed������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	COrderInsertFailed *findNextAllByExchIDInvIDUserID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByExchIDInvIDUserID(void);

	friend class COrderInsertFailedIteratorAllByExchIDInstruIDUserID;

	///��ʼѰ��COrderInsertFailed
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ��
	///@param	UserID	�����û�����
	///@return	���������ĵ�һ��COrderInsertFailed������Ҳ���������NULL
	COrderInsertFailed *startFindAllByExchIDInstruIDUserID( const CReadOnlyExchangeIDType& ExchangeID,  const CReadOnlyInstrumentIDType& InstrumentID,  const CReadOnlyUserIDType& UserID);

	///Ѱ����һ������������COrderInsertFailed��������startFindAllByExchIDInstruIDUserID�Ժ�endFindAllByExchIDInstruIDUserID֮ǰ����
	///@return	��һ����������COrderInsertFailed������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	COrderInsertFailed *findNextAllByExchIDInstruIDUserID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByExchIDInstruIDUserID(void);

	friend class COrderInsertFailedIteratorAll;

	///��ʼѰ��COrderInsertFailed
	///@return	���������ĵ�һ��COrderInsertFailed������Ҳ���������NULL
	COrderInsertFailed *startFindAll();

	///Ѱ����һ������������COrderInsertFailed��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������COrderInsertFailed������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	COrderInsertFailed *findNextAll(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAll(void);

	///Ѱ��COrderInsertFailed
	///@param	ExchangeID	����������
	///@param	SeatID	ϯλ����
	///@param	OrderLocalID	���ر������
	///@return	�ҵ���COrderInsertFailed������Ҳ���������NULL
	COrderInsertFailed *findByExchangeIDSeatIDAndOrderLocalID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlySeatIDType&  SeatID,  const CReadOnlyOrderLocalIDType&  OrderLocalID);

	///��������Ѱ��
	///@param	ExchangeID	����������
	///@param	SeatID	ϯλ����
	///@param	OrderLocalID	���ر������
	///@return	�ҵ���COrderInsertFailed������Ҳ���������NULL
	COrderInsertFailed *findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlySeatIDType&  SeatID,  const CReadOnlyOrderLocalIDType&  OrderLocalID);
	
	///��������Ѱ��COrderInsertFailed
	///@param	pOrderInsertFailed	Ҫ�ҵ�ֵ
	///@return	�ҵ���COrderInsertFailed������Ҳ���������NULL
	COrderInsertFailed *findByPK(CWriteableOrderInsertFailed *pOrderInsertFailed);

	///����������ȡCOrderInsertFailed
	///@param	pOrderInsertFailed	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���COrderInsertFailed������Ҳ���������NULL
	bool retrieveByPK(CWriteableOrderInsertFailed *pOrderInsertFailed);

	///�������������µ�COrderInsertFailed
	///@param	pOrderInsertFailed	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����COrderInsertFailed���������ʧ�ܣ��򷵻�NULL
	COrderInsertFailed *addByPK(CWriteableOrderInsertFailed *pOrderInsertFailed, CTransaction *pTransaction=NULL);

	///������������COrderInsertFailed��ֵ
	///@param	pOrderInsertFailed	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableOrderInsertFailed *pOrderInsertFailed, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��COrderInsertFailed
	///@param	pOrderInsertFailed	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableOrderInsertFailed *pOrderInsertFailed, CTransaction *pTransaction=NULL);


private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��COrderInsertFailed���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pOrderInsertFailed	Ҫ�����OrderInsertFailed
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	COrderInsertFailed *internalAdd(CWriteableOrderInsertFailed *pOrderInsertFailed, bool bNoTransaction);
	
	
	///ˢ�¸�COrderInsertFailed�ļ�ֵ
	///@param	pOrderInsertFailed	��ˢ�µ�COrderInsertFailed
	///@param	pNewOrderInsertFailed	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��COrderInsertFailed��ͬʱɾ��������
	///@param	pOrderInsertFailed	Ҫɾ����COrderInsertFailed
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(COrderInsertFailed *pOrderInsertFailed, bool bNoTransaction);
/*
	///���ĳ��COrderInsertFailed�Ƿ����ڱ����󹤳�
	///@param	pOrderInsertFailed	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(COrderInsertFailed *pOrderInsertFailed);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����OrderUserID������
	CAVLTree *pOrderUserIDIndex;
	///����OrderLocalID������
	CAVLTree *pOrderLocalIDIndex;
	///����ExchangeID+OrderSysID������
	CAVLTree *pExchangeIDOrderSysIDIndex;
	///����ExchangeID+SeatID+OrderLocalID������
	CAVLTree *pExchangeIDSeatIDOrderLocalIDIndex;
	
	
	///����ExchangeID��InvestorID��UserID����ʱ���洢�Ĳ�ѯ����
	CExchangeIDType queryExchangeIDInSearchAllByExchIDInvIDUserID;
	CInvestorIDType queryInvestorIDInSearchAllByExchIDInvIDUserID;
	CUserIDType queryUserIDInSearchAllByExchIDInvIDUserID;
	
	///����ExchangeID��InvestorID��UserID����ʱ���洢���һ���ҵ��������ڵ�
	COrderInsertFailed *pLastFoundInSearchAllByExchIDInvIDUserID;
	///����ExchangeID��InstrumentID��UserID����ʱ���洢�Ĳ�ѯ����
	CExchangeIDType queryExchangeIDInSearchAllByExchIDInstruIDUserID;
	CInstrumentIDType queryInstrumentIDInSearchAllByExchIDInstruIDUserID;
	CUserIDType queryUserIDInSearchAllByExchIDInstruIDUserID;
	
	///����ExchangeID��InstrumentID��UserID����ʱ���洢���һ���ҵ��������ڵ�
	COrderInsertFailed *pLastFoundInSearchAllByExchIDInstruIDUserID;
	///���ռ���ʱ���洢�Ĳ�ѯ����
	
	///���ռ���ʱ���洢���һ���ҵ��������ڵ�
	COrderInsertFailed *pLastFoundInSearchAll;
	
	///����ǰ����
	///@param	pOrderInsertFailed	Ҫ�����OrderInsertFailed
	virtual void beforeAdd(CWriteableOrderInsertFailed *pOrderInsertFailed);
	
	///����󴥷�
	///@param	pOrderInsertFailed	�Ѿ������OrderInsertFailed
	virtual void afterAdd(COrderInsertFailed *pOrderInsertFailed);

	///����ǰ����	
	///@param	pOrderInsertFailed	��ˢ�µ�COrderInsertFailed
	///@param	pNewOrderInsertFailed	�µ�ֵ
	virtual void beforeUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed);
	
	///���º󴥷�
	///@param	pOrderInsertFailed	��ˢ�µ�COrderInsertFailed
	virtual void afterUpdate(COrderInsertFailed *pOrderInsertFailed);
	
	///ɾ��ǰ����
	///@param	pOrderInsertFailed	Ҫɾ����COrderInsertFailed
	virtual void beforeRemove(COrderInsertFailed *pOrderInsertFailed);
	
	///ȷ�ϼ���󴥷�
	///@param	pOrderInsertFailed	�Ѿ������OrderInsertFailed
	virtual void commitAdd(COrderInsertFailed *pOrderInsertFailed);

	///ȷ�ϸ��º󴥷�
	///@param	pOrderInsertFailed	��ˢ�µ�COrderInsertFailed
	///@param	poldOrderInsertFailed	ԭ����ֵ
	virtual void commitUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pOldOrderInsertFailed);
	
	///ȷ��ɾ���󴥷�
	///@param	pOrderInsertFailed	�Ѿ�ɾ����COrderInsertFailed
	virtual void commitRemove(CWriteableOrderInsertFailed *pOrderInsertFailed);

	///������صĴ�����
	vector<COrderInsertFailedActionTrigger *> *pActionTriggers;
	vector<COrderInsertFailedCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableOrderInsertFailed compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightFactory��һ���û�����Ȩ�ޱ�Ķ��󹤳�����������һ���û�����Ȩ�ޱ�
///ͬʱ�ֽ����������������Է����ѯ��
///	BrkExIDInsUserInvIndex
///ʹ�ñ����󹤳���������ɶ��û�����Ȩ�ޱ����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrkExIDInsUserInv��Ψһ�ҵ�����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CUserTradingRightFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxUserTradingRight��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CUserTradingRightFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserTradingRightFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�UserTradingRight
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�UserTradingRight���ļ��������������ļ��еĶ���UserTradingRightCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�UserTradingRight
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�UserTradingRight���ļ��������������ļ��еĶ���UserTradingRightCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CUserTradingRightResource;

	///��һ��CUserTradingRight���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pUserTradingRight	Ҫ�����UserTradingRight
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CUserTradingRight *add(CWriteableUserTradingRight *pUserTradingRight, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CUserTradingRight��ֵ
	///@param	pUserTradingRight	��ˢ�µ�CUserTradingRight
	///@param	pNewUserTradingRight	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pUserTradingRight	  ��Ҫ��ˢ�»���������CUserTradingRight,����NULL��ʾ����Ҫ������
	///@param	pNewUserTradingRight	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CUserTradingRight* addOrUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CUserTradingRight��ͬʱɾ��������
	///@param	pUserTradingRight	Ҫɾ����CUserTradingRight
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CUserTradingRight *pUserTradingRight, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CUserTradingRight
	///@param	pUserTradingRight	Ҫ��ȡ��CUserTradingRight
	///@param	pTragetUserTradingRight	��Ž����CUserTradingRight
	void retrieve(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pTargetUserTradingRight);
	
	///��ȡ��һ��CUserTradingRight
	///@return	�õ��ĵ�һ��CUserTradingRight�����û�У��򷵻�NULL
	CUserTradingRight *getFirst(void);
	
	///��ȡ��һ��CUserTradingRight
	///@return	�õ���һ��CUserTradingRight�����û�У��򷵻�NULL
	CUserTradingRight *getNext(void);
	
	///������ȡCUserTradingRight
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CUserTradingRightActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CUserTradingRightActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CUserTradingRightCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CUserTradingRightCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CUserTradingRight
	///@param	BrokerID	���͹�˾����
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ���
	///@param	UserID	��¼�û�����
	///@param	InvestorID	Ͷ���ߴ���
	///@return	�ҵ���CUserTradingRight������Ҳ���������NULL
	CUserTradingRight *findByBrkExIDInsUserInv( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyInvestorIDType&  InvestorID);

	///��������Ѱ��
	///@param	BrokerID	���͹�˾����
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ���
	///@param	UserID	��¼�û�����
	///@param	InvestorID	Ͷ���ߴ���
	///@return	�ҵ���CUserTradingRight������Ҳ���������NULL
	CUserTradingRight *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyInvestorIDType&  InvestorID);
	
	///��������Ѱ��CUserTradingRight
	///@param	pUserTradingRight	Ҫ�ҵ�ֵ
	///@return	�ҵ���CUserTradingRight������Ҳ���������NULL
	CUserTradingRight *findByPK(CWriteableUserTradingRight *pUserTradingRight);

	///����������ȡCUserTradingRight
	///@param	pUserTradingRight	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CUserTradingRight������Ҳ���������NULL
	bool retrieveByPK(CWriteableUserTradingRight *pUserTradingRight);

	///�������������µ�CUserTradingRight
	///@param	pUserTradingRight	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CUserTradingRight���������ʧ�ܣ��򷵻�NULL
	CUserTradingRight *addByPK(CWriteableUserTradingRight *pUserTradingRight, CTransaction *pTransaction=NULL);

	///������������CUserTradingRight��ֵ
	///@param	pUserTradingRight	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableUserTradingRight *pUserTradingRight, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CUserTradingRight
	///@param	pUserTradingRight	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableUserTradingRight *pUserTradingRight, CTransaction *pTransaction=NULL);


private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CUserTradingRight���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pUserTradingRight	Ҫ�����UserTradingRight
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CUserTradingRight *internalAdd(CWriteableUserTradingRight *pUserTradingRight, bool bNoTransaction);
	
	
	///ˢ�¸�CUserTradingRight�ļ�ֵ
	///@param	pUserTradingRight	��ˢ�µ�CUserTradingRight
	///@param	pNewUserTradingRight	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CUserTradingRight��ͬʱɾ��������
	///@param	pUserTradingRight	Ҫɾ����CUserTradingRight
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CUserTradingRight *pUserTradingRight, bool bNoTransaction);
/*
	///���ĳ��CUserTradingRight�Ƿ����ڱ����󹤳�
	///@param	pUserTradingRight	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CUserTradingRight *pUserTradingRight);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����BrokerID+ExchangeID+InstrumentID+UserID+InvestorID������
	CAVLTree *pBrkExIDInsUserInvIndex;
	
	
	
	///����ǰ����
	///@param	pUserTradingRight	Ҫ�����UserTradingRight
	virtual void beforeAdd(CWriteableUserTradingRight *pUserTradingRight);
	
	///����󴥷�
	///@param	pUserTradingRight	�Ѿ������UserTradingRight
	virtual void afterAdd(CUserTradingRight *pUserTradingRight);

	///����ǰ����	
	///@param	pUserTradingRight	��ˢ�µ�CUserTradingRight
	///@param	pNewUserTradingRight	�µ�ֵ
	virtual void beforeUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight);
	
	///���º󴥷�
	///@param	pUserTradingRight	��ˢ�µ�CUserTradingRight
	virtual void afterUpdate(CUserTradingRight *pUserTradingRight);
	
	///ɾ��ǰ����
	///@param	pUserTradingRight	Ҫɾ����CUserTradingRight
	virtual void beforeRemove(CUserTradingRight *pUserTradingRight);
	
	///ȷ�ϼ���󴥷�
	///@param	pUserTradingRight	�Ѿ������UserTradingRight
	virtual void commitAdd(CUserTradingRight *pUserTradingRight);

	///ȷ�ϸ��º󴥷�
	///@param	pUserTradingRight	��ˢ�µ�CUserTradingRight
	///@param	poldUserTradingRight	ԭ����ֵ
	virtual void commitUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pOldUserTradingRight);
	
	///ȷ��ɾ���󴥷�
	///@param	pUserTradingRight	�Ѿ�ɾ����CUserTradingRight
	virtual void commitRemove(CWriteableUserTradingRight *pUserTradingRight);

	///������صĴ�����
	vector<CUserTradingRightActionTrigger *> *pActionTriggers;
	vector<CUserTradingRightCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableUserTradingRight compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeFactory��һ����ǰʱ��Ķ��󹤳�����������һ����ǰʱ�䣬
///ͬʱ�ֽ����������������Է����ѯ��
///ʹ�ñ����󹤳���������ɶԵ�ǰʱ�����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CCurrentTimeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxCurrentTime��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CCurrentTimeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CCurrentTimeFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�CurrentTime
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�CurrentTime���ļ��������������ļ��еĶ���CurrentTimeCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�CurrentTime
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�CurrentTime���ļ��������������ļ��еĶ���CurrentTimeCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CCurrentTimeResource;

	///��һ��CCurrentTime���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pCurrentTime	Ҫ�����CurrentTime
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CCurrentTime *add(CWriteableCurrentTime *pCurrentTime, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CCurrentTime��ֵ
	///@param	pCurrentTime	��ˢ�µ�CCurrentTime
	///@param	pNewCurrentTime	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pCurrentTime	  ��Ҫ��ˢ�»���������CCurrentTime,����NULL��ʾ����Ҫ������
	///@param	pNewCurrentTime	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CCurrentTime* addOrUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CCurrentTime��ͬʱɾ��������
	///@param	pCurrentTime	Ҫɾ����CCurrentTime
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CCurrentTime *pCurrentTime, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CCurrentTime
	///@param	pCurrentTime	Ҫ��ȡ��CCurrentTime
	///@param	pTragetCurrentTime	��Ž����CCurrentTime
	void retrieve(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pTargetCurrentTime);
	
	///��ȡ��һ��CCurrentTime
	///@return	�õ��ĵ�һ��CCurrentTime�����û�У��򷵻�NULL
	CCurrentTime *getFirst(void);
	
	///��ȡ��һ��CCurrentTime
	///@return	�õ���һ��CCurrentTime�����û�У��򷵻�NULL
	CCurrentTime *getNext(void);
	
	///������ȡCCurrentTime
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CCurrentTimeActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CCurrentTimeActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CCurrentTimeCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CCurrentTimeCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CCurrentTime���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pCurrentTime	Ҫ�����CurrentTime
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CCurrentTime *internalAdd(CWriteableCurrentTime *pCurrentTime, bool bNoTransaction);
	
	
	///ˢ�¸�CCurrentTime�ļ�ֵ
	///@param	pCurrentTime	��ˢ�µ�CCurrentTime
	///@param	pNewCurrentTime	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CCurrentTime��ͬʱɾ��������
	///@param	pCurrentTime	Ҫɾ����CCurrentTime
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CCurrentTime *pCurrentTime, bool bNoTransaction);
/*
	///���ĳ��CCurrentTime�Ƿ����ڱ����󹤳�
	///@param	pCurrentTime	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CCurrentTime *pCurrentTime);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	
	
	
	///����ǰ����
	///@param	pCurrentTime	Ҫ�����CurrentTime
	virtual void beforeAdd(CWriteableCurrentTime *pCurrentTime);
	
	///����󴥷�
	///@param	pCurrentTime	�Ѿ������CurrentTime
	virtual void afterAdd(CCurrentTime *pCurrentTime);

	///����ǰ����	
	///@param	pCurrentTime	��ˢ�µ�CCurrentTime
	///@param	pNewCurrentTime	�µ�ֵ
	virtual void beforeUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime);
	
	///���º󴥷�
	///@param	pCurrentTime	��ˢ�µ�CCurrentTime
	virtual void afterUpdate(CCurrentTime *pCurrentTime);
	
	///ɾ��ǰ����
	///@param	pCurrentTime	Ҫɾ����CCurrentTime
	virtual void beforeRemove(CCurrentTime *pCurrentTime);
	
	///ȷ�ϼ���󴥷�
	///@param	pCurrentTime	�Ѿ������CurrentTime
	virtual void commitAdd(CCurrentTime *pCurrentTime);

	///ȷ�ϸ��º󴥷�
	///@param	pCurrentTime	��ˢ�µ�CCurrentTime
	///@param	poldCurrentTime	ԭ����ֵ
	virtual void commitUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pOldCurrentTime);
	
	///ȷ��ɾ���󴥷�
	///@param	pCurrentTime	�Ѿ�ɾ����CCurrentTime
	virtual void commitRemove(CWriteableCurrentTime *pCurrentTime);

	///������صĴ�����
	vector<CCurrentTimeActionTrigger *> *pActionTriggers;
	vector<CCurrentTimeCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableCurrentTime compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionFactory��һ������Ա���߻Ự�Ķ��󹤳�����������һ������Ա���߻Ự��
///ͬʱ�ֽ����������������Է����ѯ��
///	SessionIDFrontIDIndex
///	BrokerIDUserIDSFIDIndex
///	UserIndex
///ʹ�ñ����󹤳���������ɶԽ���Ա���߻Ự����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findBySessionIDFrontID��Ψһ�ҵ�����
///		ʹ��findByBrokerIDUserIDSFID��Ψһ�ҵ�����
///		ʹ��startFindByUserID��findNextByUserID��endFindByUserID��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CUserSessionFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxUserSession��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CUserSessionFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserSessionFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�UserSession
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�UserSession���ļ��������������ļ��еĶ���UserSessionCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�UserSession
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�UserSession���ļ��������������ļ��еĶ���UserSessionCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CUserSessionResource;

	///��һ��CUserSession���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pUserSession	Ҫ�����UserSession
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CUserSession *add(CWriteableUserSession *pUserSession, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CUserSession��ֵ
	///@param	pUserSession	��ˢ�µ�CUserSession
	///@param	pNewUserSession	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pUserSession	  ��Ҫ��ˢ�»���������CUserSession,����NULL��ʾ����Ҫ������
	///@param	pNewUserSession	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CUserSession* addOrUpdate(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CUserSession��ͬʱɾ��������
	///@param	pUserSession	Ҫɾ����CUserSession
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CUserSession *pUserSession, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CUserSession
	///@param	pUserSession	Ҫ��ȡ��CUserSession
	///@param	pTragetUserSession	��Ž����CUserSession
	void retrieve(CUserSession *pUserSession, CWriteableUserSession *pTargetUserSession);
	
	///��ȡ��һ��CUserSession
	///@return	�õ��ĵ�һ��CUserSession�����û�У��򷵻�NULL
	CUserSession *getFirst(void);
	
	///��ȡ��һ��CUserSession
	///@return	�õ���һ��CUserSession�����û�У��򷵻�NULL
	CUserSession *getNext(void);
	
	///������ȡCUserSession
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CUserSessionActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CUserSessionActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CUserSessionCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CUserSessionCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CUserSession
	///@param	SessionID	�Ự��
	///@param	FrontID	ǰ�ñ��
	///@return	�ҵ���CUserSession������Ҳ���������NULL
	CUserSession *findBySessionIDFrontID( const CReadOnlySessionIDType&  SessionID,  const CReadOnlyFrontIDType&  FrontID);

	///��������Ѱ��
	///@param	SessionID	�Ự��
	///@param	FrontID	ǰ�ñ��
	///@return	�ҵ���CUserSession������Ҳ���������NULL
	CUserSession *findByPK( const CReadOnlySessionIDType&  SessionID,  const CReadOnlyFrontIDType&  FrontID);
	
	///��������Ѱ��CUserSession
	///@param	pUserSession	Ҫ�ҵ�ֵ
	///@return	�ҵ���CUserSession������Ҳ���������NULL
	CUserSession *findByPK(CWriteableUserSession *pUserSession);

	///����������ȡCUserSession
	///@param	pUserSession	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CUserSession������Ҳ���������NULL
	bool retrieveByPK(CWriteableUserSession *pUserSession);

	///�������������µ�CUserSession
	///@param	pUserSession	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CUserSession���������ʧ�ܣ��򷵻�NULL
	CUserSession *addByPK(CWriteableUserSession *pUserSession, CTransaction *pTransaction=NULL);

	///������������CUserSession��ֵ
	///@param	pUserSession	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableUserSession *pUserSession, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CUserSession
	///@param	pUserSession	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableUserSession *pUserSession, CTransaction *pTransaction=NULL);


	///Ѱ��CUserSession
	///@param	BrokerID	���͹�˾���
	///@param	UserID	�û���
	///@param	SessionID	�Ự��
	///@param	FrontID	ǰ�ñ��
	///@return	�ҵ���CUserSession������Ҳ���������NULL
	CUserSession *findByBrokerIDUserIDSFID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlySessionIDType&  SessionID,  const CReadOnlyFrontIDType&  FrontID);



	friend class CUserSessionIteratorByUserID;

	///��ʼѰ��CUserSession
	///@param	UserID	�û���
	///@return	���������ĵ�һ��CUserSession������Ҳ���������NULL
	CUserSession *startFindByUserID( const CReadOnlyUserIDType& UserID);

	///Ѱ����һ������������CUserSession��������startFindByUserID�Ժ�endFindByUserID֮ǰ����
	///@return	��һ����������CUserSession������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CUserSession *findNextByUserID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindByUserID(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CUserSession���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pUserSession	Ҫ�����UserSession
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CUserSession *internalAdd(CWriteableUserSession *pUserSession, bool bNoTransaction);
	
	
	///ˢ�¸�CUserSession�ļ�ֵ
	///@param	pUserSession	��ˢ�µ�CUserSession
	///@param	pNewUserSession	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CUserSession��ͬʱɾ��������
	///@param	pUserSession	Ҫɾ����CUserSession
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CUserSession *pUserSession, bool bNoTransaction);
/*
	///���ĳ��CUserSession�Ƿ����ڱ����󹤳�
	///@param	pUserSession	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CUserSession *pUserSession);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����SessionID+FrontID������
	CAVLTree *pSessionIDFrontIDIndex;
	///����BrokerID+UserID+SessionID+FrontID������
	CAVLTree *pBrokerIDUserIDSFIDIndex;
	///����UserID������
	CAVLTree *pUserIndex;
	
	
	///����UserID����ʱ���洢�Ĳ�ѯ����
	CUserIDType queryUserIDInSearchByUserID;
	
	///����UserID����ʱ���洢���һ���ҵ��������ڵ�
	CAVLNode *pLastFoundInSearchByUserID;
	
	///����ǰ����
	///@param	pUserSession	Ҫ�����UserSession
	virtual void beforeAdd(CWriteableUserSession *pUserSession);
	
	///����󴥷�
	///@param	pUserSession	�Ѿ������UserSession
	virtual void afterAdd(CUserSession *pUserSession);

	///����ǰ����	
	///@param	pUserSession	��ˢ�µ�CUserSession
	///@param	pNewUserSession	�µ�ֵ
	virtual void beforeUpdate(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession);
	
	///���º󴥷�
	///@param	pUserSession	��ˢ�µ�CUserSession
	virtual void afterUpdate(CUserSession *pUserSession);
	
	///ɾ��ǰ����
	///@param	pUserSession	Ҫɾ����CUserSession
	virtual void beforeRemove(CUserSession *pUserSession);
	
	///ȷ�ϼ���󴥷�
	///@param	pUserSession	�Ѿ������UserSession
	virtual void commitAdd(CUserSession *pUserSession);

	///ȷ�ϸ��º󴥷�
	///@param	pUserSession	��ˢ�µ�CUserSession
	///@param	poldUserSession	ԭ����ֵ
	virtual void commitUpdate(CUserSession *pUserSession, CWriteableUserSession *pOldUserSession);
	
	///ȷ��ɾ���󴥷�
	///@param	pUserSession	�Ѿ�ɾ����CUserSession
	virtual void commitRemove(CWriteableUserSession *pUserSession);

	///������صĴ�����
	vector<CUserSessionActionTrigger *> *pActionTriggers;
	vector<CUserSessionCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableUserSession compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDFactory��һ����󱾵ر����ŵĶ��󹤳�����������һ����󱾵ر����ţ�
///ͬʱ�ֽ����������������Է����ѯ��
///ʹ�ñ����󹤳���������ɶ���󱾵ر����ŵ���ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByFrontIDSessionID��Ψһ�ҵ�����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CMaxLocalIDFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxMaxLocalID��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CMaxLocalIDFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CMaxLocalIDFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�MaxLocalID
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�MaxLocalID���ļ��������������ļ��еĶ���MaxLocalIDCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�MaxLocalID
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�MaxLocalID���ļ��������������ļ��еĶ���MaxLocalIDCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CMaxLocalIDResource;

	///��һ��CMaxLocalID���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pMaxLocalID	Ҫ�����MaxLocalID
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CMaxLocalID *add(CWriteableMaxLocalID *pMaxLocalID, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CMaxLocalID��ֵ
	///@param	pMaxLocalID	��ˢ�µ�CMaxLocalID
	///@param	pNewMaxLocalID	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pMaxLocalID	  ��Ҫ��ˢ�»���������CMaxLocalID,����NULL��ʾ����Ҫ������
	///@param	pNewMaxLocalID	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CMaxLocalID* addOrUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CMaxLocalID��ͬʱɾ��������
	///@param	pMaxLocalID	Ҫɾ����CMaxLocalID
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CMaxLocalID *pMaxLocalID, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CMaxLocalID
	///@param	pMaxLocalID	Ҫ��ȡ��CMaxLocalID
	///@param	pTragetMaxLocalID	��Ž����CMaxLocalID
	void retrieve(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pTargetMaxLocalID);
	
	///��ȡ��һ��CMaxLocalID
	///@return	�õ��ĵ�һ��CMaxLocalID�����û�У��򷵻�NULL
	CMaxLocalID *getFirst(void);
	
	///��ȡ��һ��CMaxLocalID
	///@return	�õ���һ��CMaxLocalID�����û�У��򷵻�NULL
	CMaxLocalID *getNext(void);
	
	///������ȡCMaxLocalID
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CMaxLocalIDActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CMaxLocalIDActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CMaxLocalIDCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CMaxLocalIDCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CMaxLocalID
	///@param	FrontID	ǰ�ñ��
	///@param	SessionID	�Ự��
	///@return	�ҵ���CMaxLocalID������Ҳ���������NULL
	CMaxLocalID *findByFrontIDSessionID( const CReadOnlyFrontIDType&  FrontID,  const CReadOnlySessionIDType&  SessionID);

	///��������Ѱ��
	///@param	FrontID	ǰ�ñ��
	///@param	SessionID	�Ự��
	///@return	�ҵ���CMaxLocalID������Ҳ���������NULL
	CMaxLocalID *findByPK( const CReadOnlyFrontIDType&  FrontID,  const CReadOnlySessionIDType&  SessionID);
	
	///��������Ѱ��CMaxLocalID
	///@param	pMaxLocalID	Ҫ�ҵ�ֵ
	///@return	�ҵ���CMaxLocalID������Ҳ���������NULL
	CMaxLocalID *findByPK(CWriteableMaxLocalID *pMaxLocalID);

	///����������ȡCMaxLocalID
	///@param	pMaxLocalID	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CMaxLocalID������Ҳ���������NULL
	bool retrieveByPK(CWriteableMaxLocalID *pMaxLocalID);

	///�������������µ�CMaxLocalID
	///@param	pMaxLocalID	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CMaxLocalID���������ʧ�ܣ��򷵻�NULL
	CMaxLocalID *addByPK(CWriteableMaxLocalID *pMaxLocalID, CTransaction *pTransaction=NULL);

	///������������CMaxLocalID��ֵ
	///@param	pMaxLocalID	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableMaxLocalID *pMaxLocalID, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CMaxLocalID
	///@param	pMaxLocalID	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableMaxLocalID *pMaxLocalID, CTransaction *pTransaction=NULL);


private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CMaxLocalID���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pMaxLocalID	Ҫ�����MaxLocalID
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CMaxLocalID *internalAdd(CWriteableMaxLocalID *pMaxLocalID, bool bNoTransaction);
	
	
	///ˢ�¸�CMaxLocalID�ļ�ֵ
	///@param	pMaxLocalID	��ˢ�µ�CMaxLocalID
	///@param	pNewMaxLocalID	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CMaxLocalID��ͬʱɾ��������
	///@param	pMaxLocalID	Ҫɾ����CMaxLocalID
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CMaxLocalID *pMaxLocalID, bool bNoTransaction);
/*
	///���ĳ��CMaxLocalID�Ƿ����ڱ����󹤳�
	///@param	pMaxLocalID	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CMaxLocalID *pMaxLocalID);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	
	///����FrontIDSessionID��hash����
	CHashIndex *pFrontIDSessionIDHashIndex;
	
	
	///����ǰ����
	///@param	pMaxLocalID	Ҫ�����MaxLocalID
	virtual void beforeAdd(CWriteableMaxLocalID *pMaxLocalID);
	
	///����󴥷�
	///@param	pMaxLocalID	�Ѿ������MaxLocalID
	virtual void afterAdd(CMaxLocalID *pMaxLocalID);

	///����ǰ����	
	///@param	pMaxLocalID	��ˢ�µ�CMaxLocalID
	///@param	pNewMaxLocalID	�µ�ֵ
	virtual void beforeUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID);
	
	///���º󴥷�
	///@param	pMaxLocalID	��ˢ�µ�CMaxLocalID
	virtual void afterUpdate(CMaxLocalID *pMaxLocalID);
	
	///ɾ��ǰ����
	///@param	pMaxLocalID	Ҫɾ����CMaxLocalID
	virtual void beforeRemove(CMaxLocalID *pMaxLocalID);
	
	///ȷ�ϼ���󴥷�
	///@param	pMaxLocalID	�Ѿ������MaxLocalID
	virtual void commitAdd(CMaxLocalID *pMaxLocalID);

	///ȷ�ϸ��º󴥷�
	///@param	pMaxLocalID	��ˢ�µ�CMaxLocalID
	///@param	poldMaxLocalID	ԭ����ֵ
	virtual void commitUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pOldMaxLocalID);
	
	///ȷ��ɾ���󴥷�
	///@param	pMaxLocalID	�Ѿ�ɾ����CMaxLocalID
	virtual void commitRemove(CWriteableMaxLocalID *pMaxLocalID);

	///������صĴ�����
	vector<CMaxLocalIDActionTrigger *> *pActionTriggers;
	vector<CMaxLocalIDCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableMaxLocalID compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDFactory��һ���û����ر����ŵĶ��󹤳�����������һ���û����ر����ţ�
///ͬʱ�ֽ����������������Է����ѯ��
///ʹ�ñ����󹤳���������ɶ��û����ر����ŵ���ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrokerIDUserIDLocalID��Ψһ�ҵ�����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CBrkUserIDLocalIDFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxBrkUserIDLocalID��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CBrkUserIDLocalIDFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CBrkUserIDLocalIDFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�BrkUserIDLocalID
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�BrkUserIDLocalID���ļ��������������ļ��еĶ���BrkUserIDLocalIDCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�BrkUserIDLocalID
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�BrkUserIDLocalID���ļ��������������ļ��еĶ���BrkUserIDLocalIDCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CBrkUserIDLocalIDResource;

	///��һ��CBrkUserIDLocalID���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pBrkUserIDLocalID	Ҫ�����BrkUserIDLocalID
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CBrkUserIDLocalID *add(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CBrkUserIDLocalID��ֵ
	///@param	pBrkUserIDLocalID	��ˢ�µ�CBrkUserIDLocalID
	///@param	pNewBrkUserIDLocalID	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pBrkUserIDLocalID	  ��Ҫ��ˢ�»���������CBrkUserIDLocalID,����NULL��ʾ����Ҫ������
	///@param	pNewBrkUserIDLocalID	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CBrkUserIDLocalID* addOrUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CBrkUserIDLocalID��ͬʱɾ��������
	///@param	pBrkUserIDLocalID	Ҫɾ����CBrkUserIDLocalID
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CBrkUserIDLocalID *pBrkUserIDLocalID, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CBrkUserIDLocalID
	///@param	pBrkUserIDLocalID	Ҫ��ȡ��CBrkUserIDLocalID
	///@param	pTragetBrkUserIDLocalID	��Ž����CBrkUserIDLocalID
	void retrieve(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pTargetBrkUserIDLocalID);
	
	///��ȡ��һ��CBrkUserIDLocalID
	///@return	�õ��ĵ�һ��CBrkUserIDLocalID�����û�У��򷵻�NULL
	CBrkUserIDLocalID *getFirst(void);
	
	///��ȡ��һ��CBrkUserIDLocalID
	///@return	�õ���һ��CBrkUserIDLocalID�����û�У��򷵻�NULL
	CBrkUserIDLocalID *getNext(void);
	
	///������ȡCBrkUserIDLocalID
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CBrkUserIDLocalIDActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CBrkUserIDLocalIDActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CBrkUserIDLocalIDCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CBrkUserIDLocalIDCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///�������ж�Ӧ�ı�����ָ��
	///@param	pFactory	�����Ӧ�ı�����ָ��ʱ��Ѱ�ҵĶ��󹤳�
	void linkAllPreOrder(CPreOrderFactory *pFactory);
	
	///Ѱ��CBrkUserIDLocalID
	///@param	BrokerID	���͹�˾���
	///@param	UserID	�û����
	///@param	UserOrderLocalID	���ر�����
	///@return	�ҵ���CBrkUserIDLocalID������Ҳ���������NULL
	CBrkUserIDLocalID *findByBrokerIDUserIDLocalID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyUserOrderLocalIDType&  UserOrderLocalID);

	///��������Ѱ��
	///@param	BrokerID	���͹�˾���
	///@param	UserID	�û����
	///@param	UserOrderLocalID	���ر�����
	///@return	�ҵ���CBrkUserIDLocalID������Ҳ���������NULL
	CBrkUserIDLocalID *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyUserOrderLocalIDType&  UserOrderLocalID);
	
	///��������Ѱ��CBrkUserIDLocalID
	///@param	pBrkUserIDLocalID	Ҫ�ҵ�ֵ
	///@return	�ҵ���CBrkUserIDLocalID������Ҳ���������NULL
	CBrkUserIDLocalID *findByPK(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID);

	///����������ȡCBrkUserIDLocalID
	///@param	pBrkUserIDLocalID	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CBrkUserIDLocalID������Ҳ���������NULL
	bool retrieveByPK(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID);

	///�������������µ�CBrkUserIDLocalID
	///@param	pBrkUserIDLocalID	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CBrkUserIDLocalID���������ʧ�ܣ��򷵻�NULL
	CBrkUserIDLocalID *addByPK(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID, CTransaction *pTransaction=NULL);

	///������������CBrkUserIDLocalID��ֵ
	///@param	pBrkUserIDLocalID	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CBrkUserIDLocalID
	///@param	pBrkUserIDLocalID	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID, CTransaction *pTransaction=NULL);


private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CBrkUserIDLocalID���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pBrkUserIDLocalID	Ҫ�����BrkUserIDLocalID
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CBrkUserIDLocalID *internalAdd(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID, bool bNoTransaction);
	
	
	///ˢ�¸�CBrkUserIDLocalID�ļ�ֵ
	///@param	pBrkUserIDLocalID	��ˢ�µ�CBrkUserIDLocalID
	///@param	pNewBrkUserIDLocalID	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CBrkUserIDLocalID��ͬʱɾ��������
	///@param	pBrkUserIDLocalID	Ҫɾ����CBrkUserIDLocalID
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CBrkUserIDLocalID *pBrkUserIDLocalID, bool bNoTransaction);
/*
	///���ĳ��CBrkUserIDLocalID�Ƿ����ڱ����󹤳�
	///@param	pBrkUserIDLocalID	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CBrkUserIDLocalID *pBrkUserIDLocalID);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	
	///����BrokerIDUserIDLocalID��hash����
	CHashIndex *pBrokerIDUserIDLocalIDHashIndex;
	
	
	///����ǰ����
	///@param	pBrkUserIDLocalID	Ҫ�����BrkUserIDLocalID
	virtual void beforeAdd(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID);
	
	///����󴥷�
	///@param	pBrkUserIDLocalID	�Ѿ������BrkUserIDLocalID
	virtual void afterAdd(CBrkUserIDLocalID *pBrkUserIDLocalID);

	///����ǰ����	
	///@param	pBrkUserIDLocalID	��ˢ�µ�CBrkUserIDLocalID
	///@param	pNewBrkUserIDLocalID	�µ�ֵ
	virtual void beforeUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID);
	
	///���º󴥷�
	///@param	pBrkUserIDLocalID	��ˢ�µ�CBrkUserIDLocalID
	virtual void afterUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID);
	
	///ɾ��ǰ����
	///@param	pBrkUserIDLocalID	Ҫɾ����CBrkUserIDLocalID
	virtual void beforeRemove(CBrkUserIDLocalID *pBrkUserIDLocalID);
	
	///ȷ�ϼ���󴥷�
	///@param	pBrkUserIDLocalID	�Ѿ������BrkUserIDLocalID
	virtual void commitAdd(CBrkUserIDLocalID *pBrkUserIDLocalID);

	///ȷ�ϸ��º󴥷�
	///@param	pBrkUserIDLocalID	��ˢ�µ�CBrkUserIDLocalID
	///@param	poldBrkUserIDLocalID	ԭ����ֵ
	virtual void commitUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pOldBrkUserIDLocalID);
	
	///ȷ��ɾ���󴥷�
	///@param	pBrkUserIDLocalID	�Ѿ�ɾ����CBrkUserIDLocalID
	virtual void commitRemove(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID);

	///������صĴ�����
	vector<CBrkUserIDLocalIDActionTrigger *> *pActionTriggers;
	vector<CBrkUserIDLocalIDCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableBrkUserIDLocalID compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionFactory��һ���ͻ���Լ��ֱֲ�Ķ��󹤳�����������һ���ͻ���Լ��ֱֲ�
///ͬʱ�ֽ����������������Է����ѯ��
///ʹ�ñ����󹤳���������ɶԿͻ���Լ��ֱֲ����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrokerClientAndInsGroup��Ψһ�ҵ�����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CPartClientInsGroupPositionFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxPartClientInsGroupPosition��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CPartClientInsGroupPositionFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CPartClientInsGroupPositionFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�PartClientInsGroupPosition
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�PartClientInsGroupPosition���ļ��������������ļ��еĶ���PartClientInsGroupPositionCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�PartClientInsGroupPosition
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�PartClientInsGroupPosition���ļ��������������ļ��еĶ���PartClientInsGroupPositionCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CPartClientInsGroupPositionResource;

	///��һ��CPartClientInsGroupPosition���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pPartClientInsGroupPosition	Ҫ�����PartClientInsGroupPosition
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CPartClientInsGroupPosition *add(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CPartClientInsGroupPosition��ֵ
	///@param	pPartClientInsGroupPosition	��ˢ�µ�CPartClientInsGroupPosition
	///@param	pNewPartClientInsGroupPosition	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pPartClientInsGroupPosition	  ��Ҫ��ˢ�»���������CPartClientInsGroupPosition,����NULL��ʾ����Ҫ������
	///@param	pNewPartClientInsGroupPosition	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CPartClientInsGroupPosition* addOrUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CPartClientInsGroupPosition��ͬʱɾ��������
	///@param	pPartClientInsGroupPosition	Ҫɾ����CPartClientInsGroupPosition
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CPartClientInsGroupPosition
	///@param	pPartClientInsGroupPosition	Ҫ��ȡ��CPartClientInsGroupPosition
	///@param	pTragetPartClientInsGroupPosition	��Ž����CPartClientInsGroupPosition
	void retrieve(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pTargetPartClientInsGroupPosition);
	
	///��ȡ��һ��CPartClientInsGroupPosition
	///@return	�õ��ĵ�һ��CPartClientInsGroupPosition�����û�У��򷵻�NULL
	CPartClientInsGroupPosition *getFirst(void);
	
	///��ȡ��һ��CPartClientInsGroupPosition
	///@return	�õ���һ��CPartClientInsGroupPosition�����û�У��򷵻�NULL
	CPartClientInsGroupPosition *getNext(void);
	
	///������ȡCPartClientInsGroupPosition
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CPartClientInsGroupPositionActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CPartClientInsGroupPositionActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CPartClientInsGroupPositionCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CPartClientInsGroupPositionCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CPartClientInsGroupPosition
	///@param	BrokerID	��Ա��
	///@param	ClientID	�ͻ���
	///@param	InstrumentGroupID	��Լ���
	///@return	�ҵ���CPartClientInsGroupPosition������Ҳ���������NULL
	CPartClientInsGroupPosition *findByBrokerClientAndInsGroup( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyClientIDType&  ClientID,  const CReadOnlyInstrumentGroupIDType&  InstrumentGroupID);



private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CPartClientInsGroupPosition���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pPartClientInsGroupPosition	Ҫ�����PartClientInsGroupPosition
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CPartClientInsGroupPosition *internalAdd(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition, bool bNoTransaction);
	
	
	///ˢ�¸�CPartClientInsGroupPosition�ļ�ֵ
	///@param	pPartClientInsGroupPosition	��ˢ�µ�CPartClientInsGroupPosition
	///@param	pNewPartClientInsGroupPosition	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CPartClientInsGroupPosition��ͬʱɾ��������
	///@param	pPartClientInsGroupPosition	Ҫɾ����CPartClientInsGroupPosition
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CPartClientInsGroupPosition *pPartClientInsGroupPosition, bool bNoTransaction);
/*
	///���ĳ��CPartClientInsGroupPosition�Ƿ����ڱ����󹤳�
	///@param	pPartClientInsGroupPosition	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CPartClientInsGroupPosition *pPartClientInsGroupPosition);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	
	///����PartClientAndInsGroup��hash����
	CHashIndex *pPartClientAndInsGroupHashIndex;
	
	
	///����ǰ����
	///@param	pPartClientInsGroupPosition	Ҫ�����PartClientInsGroupPosition
	virtual void beforeAdd(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition);
	
	///����󴥷�
	///@param	pPartClientInsGroupPosition	�Ѿ������PartClientInsGroupPosition
	virtual void afterAdd(CPartClientInsGroupPosition *pPartClientInsGroupPosition);

	///����ǰ����	
	///@param	pPartClientInsGroupPosition	��ˢ�µ�CPartClientInsGroupPosition
	///@param	pNewPartClientInsGroupPosition	�µ�ֵ
	virtual void beforeUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition);
	
	///���º󴥷�
	///@param	pPartClientInsGroupPosition	��ˢ�µ�CPartClientInsGroupPosition
	virtual void afterUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition);
	
	///ɾ��ǰ����
	///@param	pPartClientInsGroupPosition	Ҫɾ����CPartClientInsGroupPosition
	virtual void beforeRemove(CPartClientInsGroupPosition *pPartClientInsGroupPosition);
	
	///ȷ�ϼ���󴥷�
	///@param	pPartClientInsGroupPosition	�Ѿ������PartClientInsGroupPosition
	virtual void commitAdd(CPartClientInsGroupPosition *pPartClientInsGroupPosition);

	///ȷ�ϸ��º󴥷�
	///@param	pPartClientInsGroupPosition	��ˢ�µ�CPartClientInsGroupPosition
	///@param	poldPartClientInsGroupPosition	ԭ����ֵ
	virtual void commitUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pOldPartClientInsGroupPosition);
	
	///ȷ��ɾ���󴥷�
	///@param	pPartClientInsGroupPosition	�Ѿ�ɾ����CPartClientInsGroupPosition
	virtual void commitRemove(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition);

	///������صĴ�����
	vector<CPartClientInsGroupPositionActionTrigger *> *pActionTriggers;
	vector<CPartClientInsGroupPositionCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteablePartClientInsGroupPosition compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeFactory��һ�����ױ�����ϱ�֤�����͵Ķ��󹤳�����������һ�����ױ�����ϱ�֤�����ͣ�
///ͬʱ�ֽ����������������Է����ѯ��
///ʹ�ñ����󹤳���������ɶԽ��ױ�����ϱ�֤�����͵���ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrokerClientAndInsGroup��Ψһ�ҵ�����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CClientMarginCombTypeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxClientMarginCombType��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CClientMarginCombTypeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CClientMarginCombTypeFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�ClientMarginCombType
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�ClientMarginCombType���ļ��������������ļ��еĶ���ClientMarginCombTypeCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�ClientMarginCombType
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�ClientMarginCombType���ļ��������������ļ��еĶ���ClientMarginCombTypeCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CClientMarginCombTypeResource;

	///��һ��CClientMarginCombType���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pClientMarginCombType	Ҫ�����ClientMarginCombType
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CClientMarginCombType *add(CWriteableClientMarginCombType *pClientMarginCombType, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CClientMarginCombType��ֵ
	///@param	pClientMarginCombType	��ˢ�µ�CClientMarginCombType
	///@param	pNewClientMarginCombType	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pClientMarginCombType	  ��Ҫ��ˢ�»���������CClientMarginCombType,����NULL��ʾ����Ҫ������
	///@param	pNewClientMarginCombType	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CClientMarginCombType* addOrUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CClientMarginCombType��ͬʱɾ��������
	///@param	pClientMarginCombType	Ҫɾ����CClientMarginCombType
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CClientMarginCombType *pClientMarginCombType, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CClientMarginCombType
	///@param	pClientMarginCombType	Ҫ��ȡ��CClientMarginCombType
	///@param	pTragetClientMarginCombType	��Ž����CClientMarginCombType
	void retrieve(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pTargetClientMarginCombType);
	
	///��ȡ��һ��CClientMarginCombType
	///@return	�õ��ĵ�һ��CClientMarginCombType�����û�У��򷵻�NULL
	CClientMarginCombType *getFirst(void);
	
	///��ȡ��һ��CClientMarginCombType
	///@return	�õ���һ��CClientMarginCombType�����û�У��򷵻�NULL
	CClientMarginCombType *getNext(void);
	
	///������ȡCClientMarginCombType
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CClientMarginCombTypeActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CClientMarginCombTypeActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CClientMarginCombTypeCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CClientMarginCombTypeCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CClientMarginCombType
	///@param	BrokerID	��Ա��
	///@param	ClientID	�ͻ���
	///@param	InstrumentGroupID	�ͻ���
	///@return	�ҵ���CClientMarginCombType������Ҳ���������NULL
	CClientMarginCombType *findByBrokerClientAndInsGroup( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyClientIDType&  ClientID,  const CReadOnlyInstrumentGroupIDType&  InstrumentGroupID);

	///��������Ѱ��
	///@param	BrokerID	��Ա��
	///@param	ClientID	�ͻ���
	///@param	InstrumentGroupID	�ͻ���
	///@return	�ҵ���CClientMarginCombType������Ҳ���������NULL
	CClientMarginCombType *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyClientIDType&  ClientID,  const CReadOnlyInstrumentGroupIDType&  InstrumentGroupID);
	
	///��������Ѱ��CClientMarginCombType
	///@param	pClientMarginCombType	Ҫ�ҵ�ֵ
	///@return	�ҵ���CClientMarginCombType������Ҳ���������NULL
	CClientMarginCombType *findByPK(CWriteableClientMarginCombType *pClientMarginCombType);

	///����������ȡCClientMarginCombType
	///@param	pClientMarginCombType	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CClientMarginCombType������Ҳ���������NULL
	bool retrieveByPK(CWriteableClientMarginCombType *pClientMarginCombType);

	///�������������µ�CClientMarginCombType
	///@param	pClientMarginCombType	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CClientMarginCombType���������ʧ�ܣ��򷵻�NULL
	CClientMarginCombType *addByPK(CWriteableClientMarginCombType *pClientMarginCombType, CTransaction *pTransaction=NULL);

	///������������CClientMarginCombType��ֵ
	///@param	pClientMarginCombType	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableClientMarginCombType *pClientMarginCombType, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CClientMarginCombType
	///@param	pClientMarginCombType	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableClientMarginCombType *pClientMarginCombType, CTransaction *pTransaction=NULL);


private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CClientMarginCombType���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pClientMarginCombType	Ҫ�����ClientMarginCombType
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CClientMarginCombType *internalAdd(CWriteableClientMarginCombType *pClientMarginCombType, bool bNoTransaction);
	
	
	///ˢ�¸�CClientMarginCombType�ļ�ֵ
	///@param	pClientMarginCombType	��ˢ�µ�CClientMarginCombType
	///@param	pNewClientMarginCombType	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CClientMarginCombType��ͬʱɾ��������
	///@param	pClientMarginCombType	Ҫɾ����CClientMarginCombType
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CClientMarginCombType *pClientMarginCombType, bool bNoTransaction);
/*
	///���ĳ��CClientMarginCombType�Ƿ����ڱ����󹤳�
	///@param	pClientMarginCombType	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CClientMarginCombType *pClientMarginCombType);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	
	///����ClientAndInsGroup��hash����
	CHashIndex *pClientAndInsGroupHashIndex;
	
	
	///����ǰ����
	///@param	pClientMarginCombType	Ҫ�����ClientMarginCombType
	virtual void beforeAdd(CWriteableClientMarginCombType *pClientMarginCombType);
	
	///����󴥷�
	///@param	pClientMarginCombType	�Ѿ������ClientMarginCombType
	virtual void afterAdd(CClientMarginCombType *pClientMarginCombType);

	///����ǰ����	
	///@param	pClientMarginCombType	��ˢ�µ�CClientMarginCombType
	///@param	pNewClientMarginCombType	�µ�ֵ
	virtual void beforeUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType);
	
	///���º󴥷�
	///@param	pClientMarginCombType	��ˢ�µ�CClientMarginCombType
	virtual void afterUpdate(CClientMarginCombType *pClientMarginCombType);
	
	///ɾ��ǰ����
	///@param	pClientMarginCombType	Ҫɾ����CClientMarginCombType
	virtual void beforeRemove(CClientMarginCombType *pClientMarginCombType);
	
	///ȷ�ϼ���󴥷�
	///@param	pClientMarginCombType	�Ѿ������ClientMarginCombType
	virtual void commitAdd(CClientMarginCombType *pClientMarginCombType);

	///ȷ�ϸ��º󴥷�
	///@param	pClientMarginCombType	��ˢ�µ�CClientMarginCombType
	///@param	poldClientMarginCombType	ԭ����ֵ
	virtual void commitUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pOldClientMarginCombType);
	
	///ȷ��ɾ���󴥷�
	///@param	pClientMarginCombType	�Ѿ�ɾ����CClientMarginCombType
	virtual void commitRemove(CWriteableClientMarginCombType *pClientMarginCombType);

	///������صĴ�����
	vector<CClientMarginCombTypeActionTrigger *> *pActionTriggers;
	vector<CClientMarginCombTypeCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableClientMarginCombType compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupFactory��һ����Լ�ͺ�Լ���ϵ�Ķ��󹤳�����������һ����Լ�ͺ�Լ���ϵ��
///ͬʱ�ֽ����������������Է����ѯ��
///ʹ�ñ����󹤳���������ɶԺ�Լ�ͺ�Լ���ϵ����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrokerInstrumentID��Ψһ�ҵ�����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInstrumentGroupFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxInstrumentGroup��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInstrumentGroupFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInstrumentGroupFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�InstrumentGroup
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�InstrumentGroup���ļ��������������ļ��еĶ���InstrumentGroupCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�InstrumentGroup
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�InstrumentGroup���ļ��������������ļ��еĶ���InstrumentGroupCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CInstrumentGroupResource;

	///��һ��CInstrumentGroup���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInstrumentGroup	Ҫ�����InstrumentGroup
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInstrumentGroup *add(CWriteableInstrumentGroup *pInstrumentGroup, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CInstrumentGroup��ֵ
	///@param	pInstrumentGroup	��ˢ�µ�CInstrumentGroup
	///@param	pNewInstrumentGroup	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pInstrumentGroup	  ��Ҫ��ˢ�»���������CInstrumentGroup,����NULL��ʾ����Ҫ������
	///@param	pNewInstrumentGroup	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CInstrumentGroup* addOrUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CInstrumentGroup��ͬʱɾ��������
	///@param	pInstrumentGroup	Ҫɾ����CInstrumentGroup
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CInstrumentGroup *pInstrumentGroup, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CInstrumentGroup
	///@param	pInstrumentGroup	Ҫ��ȡ��CInstrumentGroup
	///@param	pTragetInstrumentGroup	��Ž����CInstrumentGroup
	void retrieve(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pTargetInstrumentGroup);
	
	///��ȡ��һ��CInstrumentGroup
	///@return	�õ��ĵ�һ��CInstrumentGroup�����û�У��򷵻�NULL
	CInstrumentGroup *getFirst(void);
	
	///��ȡ��һ��CInstrumentGroup
	///@return	�õ���һ��CInstrumentGroup�����û�У��򷵻�NULL
	CInstrumentGroup *getNext(void);
	
	///������ȡCInstrumentGroup
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CInstrumentGroupActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CInstrumentGroupActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CInstrumentGroupCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CInstrumentGroupCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CInstrumentGroup
	///@param	ExchangeID	����������
	///@param	BrokerID	��Ա��
	///@param	InstrumentID	��Լ��
	///@return	�ҵ���CInstrumentGroup������Ҳ���������NULL
	CInstrumentGroup *findByBrokerInstrumentID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInstrumentIDType&  InstrumentID);

	///��������Ѱ��
	///@param	ExchangeID	����������
	///@param	BrokerID	��Ա��
	///@param	InstrumentID	��Լ��
	///@return	�ҵ���CInstrumentGroup������Ҳ���������NULL
	CInstrumentGroup *findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyInstrumentIDType&  InstrumentID);
	
	///��������Ѱ��CInstrumentGroup
	///@param	pInstrumentGroup	Ҫ�ҵ�ֵ
	///@return	�ҵ���CInstrumentGroup������Ҳ���������NULL
	CInstrumentGroup *findByPK(CWriteableInstrumentGroup *pInstrumentGroup);

	///����������ȡCInstrumentGroup
	///@param	pInstrumentGroup	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CInstrumentGroup������Ҳ���������NULL
	bool retrieveByPK(CWriteableInstrumentGroup *pInstrumentGroup);

	///�������������µ�CInstrumentGroup
	///@param	pInstrumentGroup	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CInstrumentGroup���������ʧ�ܣ��򷵻�NULL
	CInstrumentGroup *addByPK(CWriteableInstrumentGroup *pInstrumentGroup, CTransaction *pTransaction=NULL);

	///������������CInstrumentGroup��ֵ
	///@param	pInstrumentGroup	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableInstrumentGroup *pInstrumentGroup, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CInstrumentGroup
	///@param	pInstrumentGroup	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableInstrumentGroup *pInstrumentGroup, CTransaction *pTransaction=NULL);


private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CInstrumentGroup���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInstrumentGroup	Ҫ�����InstrumentGroup
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInstrumentGroup *internalAdd(CWriteableInstrumentGroup *pInstrumentGroup, bool bNoTransaction);
	
	
	///ˢ�¸�CInstrumentGroup�ļ�ֵ
	///@param	pInstrumentGroup	��ˢ�µ�CInstrumentGroup
	///@param	pNewInstrumentGroup	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CInstrumentGroup��ͬʱɾ��������
	///@param	pInstrumentGroup	Ҫɾ����CInstrumentGroup
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CInstrumentGroup *pInstrumentGroup, bool bNoTransaction);
/*
	///���ĳ��CInstrumentGroup�Ƿ����ڱ����󹤳�
	///@param	pInstrumentGroup	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CInstrumentGroup *pInstrumentGroup);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	
	///����BrokerInstrumentID��hash����
	CHashIndex *pBrokerInstrumentIDHashIndex;
	
	
	///����ǰ����
	///@param	pInstrumentGroup	Ҫ�����InstrumentGroup
	virtual void beforeAdd(CWriteableInstrumentGroup *pInstrumentGroup);
	
	///����󴥷�
	///@param	pInstrumentGroup	�Ѿ������InstrumentGroup
	virtual void afterAdd(CInstrumentGroup *pInstrumentGroup);

	///����ǰ����	
	///@param	pInstrumentGroup	��ˢ�µ�CInstrumentGroup
	///@param	pNewInstrumentGroup	�µ�ֵ
	virtual void beforeUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup);
	
	///���º󴥷�
	///@param	pInstrumentGroup	��ˢ�µ�CInstrumentGroup
	virtual void afterUpdate(CInstrumentGroup *pInstrumentGroup);
	
	///ɾ��ǰ����
	///@param	pInstrumentGroup	Ҫɾ����CInstrumentGroup
	virtual void beforeRemove(CInstrumentGroup *pInstrumentGroup);
	
	///ȷ�ϼ���󴥷�
	///@param	pInstrumentGroup	�Ѿ������InstrumentGroup
	virtual void commitAdd(CInstrumentGroup *pInstrumentGroup);

	///ȷ�ϸ��º󴥷�
	///@param	pInstrumentGroup	��ˢ�µ�CInstrumentGroup
	///@param	poldInstrumentGroup	ԭ����ֵ
	virtual void commitUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pOldInstrumentGroup);
	
	///ȷ��ɾ���󴥷�
	///@param	pInstrumentGroup	�Ѿ�ɾ����CInstrumentGroup
	virtual void commitRemove(CWriteableInstrumentGroup *pInstrumentGroup);

	///������صĴ�����
	vector<CInstrumentGroupActionTrigger *> *pActionTriggers;
	vector<CInstrumentGroupCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableInstrumentGroup compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateFactory��һ���������ӷ��ʱ�Ķ��󹤳�����������һ���������ӷ��ʱ�
///ͬʱ�ֽ����������������Է����ѯ��
///	TradeDateInstrumentIDIndex
///ʹ�ñ����󹤳���������ɶԽ������ӷ��ʱ����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByTradeDateInstrumentIDIndex��Ψһ�ҵ�����
///		ʹ��startFindAllByInstrumentID��findNextAllByInstrumentID��endFindAllByInstrumentID��ɲ�ѯ����
///		ʹ��startFindAll��findNextAll��endFindAll��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CSGEDeferRateFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxSGEDeferRate��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CSGEDeferRateFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CSGEDeferRateFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�SGEDeferRate
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�SGEDeferRate���ļ��������������ļ��еĶ���SGEDeferRateCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�SGEDeferRate
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�SGEDeferRate���ļ��������������ļ��еĶ���SGEDeferRateCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CSGEDeferRateResource;

	///��һ��CSGEDeferRate���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pSGEDeferRate	Ҫ�����SGEDeferRate
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CSGEDeferRate *add(CWriteableSGEDeferRate *pSGEDeferRate, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CSGEDeferRate��ֵ
	///@param	pSGEDeferRate	��ˢ�µ�CSGEDeferRate
	///@param	pNewSGEDeferRate	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pSGEDeferRate	  ��Ҫ��ˢ�»���������CSGEDeferRate,����NULL��ʾ����Ҫ������
	///@param	pNewSGEDeferRate	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CSGEDeferRate* addOrUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CSGEDeferRate��ͬʱɾ��������
	///@param	pSGEDeferRate	Ҫɾ����CSGEDeferRate
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CSGEDeferRate *pSGEDeferRate, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CSGEDeferRate
	///@param	pSGEDeferRate	Ҫ��ȡ��CSGEDeferRate
	///@param	pTragetSGEDeferRate	��Ž����CSGEDeferRate
	void retrieve(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pTargetSGEDeferRate);
	
	///��ȡ��һ��CSGEDeferRate
	///@return	�õ��ĵ�һ��CSGEDeferRate�����û�У��򷵻�NULL
	CSGEDeferRate *getFirst(void);
	
	///��ȡ��һ��CSGEDeferRate
	///@return	�õ���һ��CSGEDeferRate�����û�У��򷵻�NULL
	CSGEDeferRate *getNext(void);
	
	///������ȡCSGEDeferRate
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CSGEDeferRateActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CSGEDeferRateActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CSGEDeferRateCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CSGEDeferRateCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CSGEDeferRate
	///@param	TradeDate	��������
	///@param	InstrumentID	��Լ����
	///@return	�ҵ���CSGEDeferRate������Ҳ���������NULL
	CSGEDeferRate *findByTradeDateInstrumentIDIndex( const CReadOnlyTradingDayType&  TradeDate,  const CReadOnlyInstrumentIDType&  InstrumentID);

	///��������Ѱ��
	///@param	TradeDate	��������
	///@param	InstrumentID	��Լ����
	///@return	�ҵ���CSGEDeferRate������Ҳ���������NULL
	CSGEDeferRate *findByPK( const CReadOnlyTradingDayType&  TradeDate,  const CReadOnlyInstrumentIDType&  InstrumentID);
	
	///��������Ѱ��CSGEDeferRate
	///@param	pSGEDeferRate	Ҫ�ҵ�ֵ
	///@return	�ҵ���CSGEDeferRate������Ҳ���������NULL
	CSGEDeferRate *findByPK(CWriteableSGEDeferRate *pSGEDeferRate);

	///����������ȡCSGEDeferRate
	///@param	pSGEDeferRate	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CSGEDeferRate������Ҳ���������NULL
	bool retrieveByPK(CWriteableSGEDeferRate *pSGEDeferRate);

	///�������������µ�CSGEDeferRate
	///@param	pSGEDeferRate	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CSGEDeferRate���������ʧ�ܣ��򷵻�NULL
	CSGEDeferRate *addByPK(CWriteableSGEDeferRate *pSGEDeferRate, CTransaction *pTransaction=NULL);

	///������������CSGEDeferRate��ֵ
	///@param	pSGEDeferRate	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableSGEDeferRate *pSGEDeferRate, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CSGEDeferRate
	///@param	pSGEDeferRate	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableSGEDeferRate *pSGEDeferRate, CTransaction *pTransaction=NULL);


	friend class CSGEDeferRateIteratorAllByInstrumentID;

	///��ʼѰ��CSGEDeferRate
	///@param	InstrumentID	��Լ����
	///@return	���������ĵ�һ��CSGEDeferRate������Ҳ���������NULL
	CSGEDeferRate *startFindAllByInstrumentID( const CReadOnlyInstrumentIDType& InstrumentID);

	///Ѱ����һ������������CSGEDeferRate��������startFindAllByInstrumentID�Ժ�endFindAllByInstrumentID֮ǰ����
	///@return	��һ����������CSGEDeferRate������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CSGEDeferRate *findNextAllByInstrumentID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAllByInstrumentID(void);

	friend class CSGEDeferRateIteratorAll;

	///��ʼѰ��CSGEDeferRate
	///@return	���������ĵ�һ��CSGEDeferRate������Ҳ���������NULL
	CSGEDeferRate *startFindAll();

	///Ѱ����һ������������CSGEDeferRate��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CSGEDeferRate������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CSGEDeferRate *findNextAll(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAll(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CSGEDeferRate���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pSGEDeferRate	Ҫ�����SGEDeferRate
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CSGEDeferRate *internalAdd(CWriteableSGEDeferRate *pSGEDeferRate, bool bNoTransaction);
	
	
	///ˢ�¸�CSGEDeferRate�ļ�ֵ
	///@param	pSGEDeferRate	��ˢ�µ�CSGEDeferRate
	///@param	pNewSGEDeferRate	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CSGEDeferRate��ͬʱɾ��������
	///@param	pSGEDeferRate	Ҫɾ����CSGEDeferRate
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CSGEDeferRate *pSGEDeferRate, bool bNoTransaction);
/*
	///���ĳ��CSGEDeferRate�Ƿ����ڱ����󹤳�
	///@param	pSGEDeferRate	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CSGEDeferRate *pSGEDeferRate);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����TradeDate+InstrumentID������
	CAVLTree *pTradeDateInstrumentIDIndex;
	
	
	///����InstrumentID����ʱ���洢�Ĳ�ѯ����
	CInstrumentIDType queryInstrumentIDInSearchAllByInstrumentID;
	
	///����InstrumentID����ʱ���洢���һ���ҵ��������ڵ�
	CSGEDeferRate *pLastFoundInSearchAllByInstrumentID;
	///���ռ���ʱ���洢�Ĳ�ѯ����
	
	///���ռ���ʱ���洢���һ���ҵ��������ڵ�
	CSGEDeferRate *pLastFoundInSearchAll;
	
	///����ǰ����
	///@param	pSGEDeferRate	Ҫ�����SGEDeferRate
	virtual void beforeAdd(CWriteableSGEDeferRate *pSGEDeferRate);
	
	///����󴥷�
	///@param	pSGEDeferRate	�Ѿ������SGEDeferRate
	virtual void afterAdd(CSGEDeferRate *pSGEDeferRate);

	///����ǰ����	
	///@param	pSGEDeferRate	��ˢ�µ�CSGEDeferRate
	///@param	pNewSGEDeferRate	�µ�ֵ
	virtual void beforeUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate);
	
	///���º󴥷�
	///@param	pSGEDeferRate	��ˢ�µ�CSGEDeferRate
	virtual void afterUpdate(CSGEDeferRate *pSGEDeferRate);
	
	///ɾ��ǰ����
	///@param	pSGEDeferRate	Ҫɾ����CSGEDeferRate
	virtual void beforeRemove(CSGEDeferRate *pSGEDeferRate);
	
	///ȷ�ϼ���󴥷�
	///@param	pSGEDeferRate	�Ѿ������SGEDeferRate
	virtual void commitAdd(CSGEDeferRate *pSGEDeferRate);

	///ȷ�ϸ��º󴥷�
	///@param	pSGEDeferRate	��ˢ�µ�CSGEDeferRate
	///@param	poldSGEDeferRate	ԭ����ֵ
	virtual void commitUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pOldSGEDeferRate);
	
	///ȷ��ɾ���󴥷�
	///@param	pSGEDeferRate	�Ѿ�ɾ����CSGEDeferRate
	virtual void commitRemove(CWriteableSGEDeferRate *pSGEDeferRate);

	///������صĴ�����
	vector<CSGEDeferRateActionTrigger *> *pActionTriggers;
	vector<CSGEDeferRateCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableSGEDeferRate compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightFactory��һ��Ͷ���߽���Ȩ�ޱ�Ķ��󹤳�����������һ��Ͷ���߽���Ȩ�ޱ�
///ͬʱ�ֽ����������������Է����ѯ��
///	BrkExIDInsInvIndex
///ʹ�ñ����󹤳���������ɶ�Ͷ���߽���Ȩ�ޱ����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrkExIDInsInv��Ψһ�ҵ�����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInvestorTradingRightFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxInvestorTradingRight��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInvestorTradingRightFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorTradingRightFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�InvestorTradingRight
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�InvestorTradingRight���ļ��������������ļ��еĶ���InvestorTradingRightCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�InvestorTradingRight
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�InvestorTradingRight���ļ��������������ļ��еĶ���InvestorTradingRightCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CInvestorTradingRightResource;

	///��һ��CInvestorTradingRight���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInvestorTradingRight	Ҫ�����InvestorTradingRight
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInvestorTradingRight *add(CWriteableInvestorTradingRight *pInvestorTradingRight, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CInvestorTradingRight��ֵ
	///@param	pInvestorTradingRight	��ˢ�µ�CInvestorTradingRight
	///@param	pNewInvestorTradingRight	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pInvestorTradingRight	  ��Ҫ��ˢ�»���������CInvestorTradingRight,����NULL��ʾ����Ҫ������
	///@param	pNewInvestorTradingRight	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CInvestorTradingRight* addOrUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CInvestorTradingRight��ͬʱɾ��������
	///@param	pInvestorTradingRight	Ҫɾ����CInvestorTradingRight
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CInvestorTradingRight *pInvestorTradingRight, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CInvestorTradingRight
	///@param	pInvestorTradingRight	Ҫ��ȡ��CInvestorTradingRight
	///@param	pTragetInvestorTradingRight	��Ž����CInvestorTradingRight
	void retrieve(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pTargetInvestorTradingRight);
	
	///��ȡ��һ��CInvestorTradingRight
	///@return	�õ��ĵ�һ��CInvestorTradingRight�����û�У��򷵻�NULL
	CInvestorTradingRight *getFirst(void);
	
	///��ȡ��һ��CInvestorTradingRight
	///@return	�õ���һ��CInvestorTradingRight�����û�У��򷵻�NULL
	CInvestorTradingRight *getNext(void);
	
	///������ȡCInvestorTradingRight
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CInvestorTradingRightActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CInvestorTradingRightActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CInvestorTradingRightCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CInvestorTradingRightCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CInvestorTradingRight
	///@param	BrokerID	���͹�˾����
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ���
	///@param	InvestorID	Ͷ���ߴ���
	///@param	ProductClass	��Ʒ����
	///@return	�ҵ���CInvestorTradingRight������Ҳ���������NULL
	CInvestorTradingRight *findByBrkExIDInsInv( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyProductClassType&  ProductClass);

	///��������Ѱ��
	///@param	BrokerID	���͹�˾����
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ���
	///@param	InvestorID	Ͷ���ߴ���
	///@param	ProductClass	��Ʒ����
	///@return	�ҵ���CInvestorTradingRight������Ҳ���������NULL
	CInvestorTradingRight *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID,  const CReadOnlyProductClassType&  ProductClass);
	
	///��������Ѱ��CInvestorTradingRight
	///@param	pInvestorTradingRight	Ҫ�ҵ�ֵ
	///@return	�ҵ���CInvestorTradingRight������Ҳ���������NULL
	CInvestorTradingRight *findByPK(CWriteableInvestorTradingRight *pInvestorTradingRight);

	///����������ȡCInvestorTradingRight
	///@param	pInvestorTradingRight	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CInvestorTradingRight������Ҳ���������NULL
	bool retrieveByPK(CWriteableInvestorTradingRight *pInvestorTradingRight);

	///�������������µ�CInvestorTradingRight
	///@param	pInvestorTradingRight	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CInvestorTradingRight���������ʧ�ܣ��򷵻�NULL
	CInvestorTradingRight *addByPK(CWriteableInvestorTradingRight *pInvestorTradingRight, CTransaction *pTransaction=NULL);

	///������������CInvestorTradingRight��ֵ
	///@param	pInvestorTradingRight	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableInvestorTradingRight *pInvestorTradingRight, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CInvestorTradingRight
	///@param	pInvestorTradingRight	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableInvestorTradingRight *pInvestorTradingRight, CTransaction *pTransaction=NULL);


private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CInvestorTradingRight���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInvestorTradingRight	Ҫ�����InvestorTradingRight
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInvestorTradingRight *internalAdd(CWriteableInvestorTradingRight *pInvestorTradingRight, bool bNoTransaction);
	
	
	///ˢ�¸�CInvestorTradingRight�ļ�ֵ
	///@param	pInvestorTradingRight	��ˢ�µ�CInvestorTradingRight
	///@param	pNewInvestorTradingRight	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CInvestorTradingRight��ͬʱɾ��������
	///@param	pInvestorTradingRight	Ҫɾ����CInvestorTradingRight
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CInvestorTradingRight *pInvestorTradingRight, bool bNoTransaction);
/*
	///���ĳ��CInvestorTradingRight�Ƿ����ڱ����󹤳�
	///@param	pInvestorTradingRight	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CInvestorTradingRight *pInvestorTradingRight);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����BrokerID+ExchangeID+InstrumentID+InvestorID+ProductClass������
	CAVLTree *pBrkExIDInsInvIndex;
	
	
	
	///����ǰ����
	///@param	pInvestorTradingRight	Ҫ�����InvestorTradingRight
	virtual void beforeAdd(CWriteableInvestorTradingRight *pInvestorTradingRight);
	
	///����󴥷�
	///@param	pInvestorTradingRight	�Ѿ������InvestorTradingRight
	virtual void afterAdd(CInvestorTradingRight *pInvestorTradingRight);

	///����ǰ����	
	///@param	pInvestorTradingRight	��ˢ�µ�CInvestorTradingRight
	///@param	pNewInvestorTradingRight	�µ�ֵ
	virtual void beforeUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight);
	
	///���º󴥷�
	///@param	pInvestorTradingRight	��ˢ�µ�CInvestorTradingRight
	virtual void afterUpdate(CInvestorTradingRight *pInvestorTradingRight);
	
	///ɾ��ǰ����
	///@param	pInvestorTradingRight	Ҫɾ����CInvestorTradingRight
	virtual void beforeRemove(CInvestorTradingRight *pInvestorTradingRight);
	
	///ȷ�ϼ���󴥷�
	///@param	pInvestorTradingRight	�Ѿ������InvestorTradingRight
	virtual void commitAdd(CInvestorTradingRight *pInvestorTradingRight);

	///ȷ�ϸ��º󴥷�
	///@param	pInvestorTradingRight	��ˢ�µ�CInvestorTradingRight
	///@param	poldInvestorTradingRight	ԭ����ֵ
	virtual void commitUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pOldInvestorTradingRight);
	
	///ȷ��ɾ���󴥷�
	///@param	pInvestorTradingRight	�Ѿ�ɾ����CInvestorTradingRight
	virtual void commitRemove(CWriteableInvestorTradingRight *pInvestorTradingRight);

	///������صĴ�����
	vector<CInvestorTradingRightActionTrigger *> *pActionTriggers;
	vector<CInvestorTradingRightCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableInvestorTradingRight compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CUserIPFactory��һ������ԱIP��ַ�Ķ��󹤳�����������һ������ԱIP��ַ��
///ͬʱ�ֽ����������������Է����ѯ��
///	UserIPMaskIndex
///ʹ�ñ����󹤳���������ɶԽ���ԱIP��ַ����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��startFindByUserID��findNextByUserID��endFindByUserID��ɲ�ѯ����
///		ʹ��findByUserIPAndMask��Ψһ�ҵ�����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CUserIPFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxUserIP��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CUserIPFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserIPFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�UserIP
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�UserIP���ļ��������������ļ��еĶ���UserIPCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�UserIP
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�UserIP���ļ��������������ļ��еĶ���UserIPCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CUserIPResource;

	///��һ��CUserIP���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pUserIP	Ҫ�����UserIP
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CUserIP *add(CWriteableUserIP *pUserIP, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CUserIP��ֵ
	///@param	pUserIP	��ˢ�µ�CUserIP
	///@param	pNewUserIP	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pUserIP	  ��Ҫ��ˢ�»���������CUserIP,����NULL��ʾ����Ҫ������
	///@param	pNewUserIP	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CUserIP* addOrUpdate(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CUserIP��ͬʱɾ��������
	///@param	pUserIP	Ҫɾ����CUserIP
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CUserIP *pUserIP, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CUserIP
	///@param	pUserIP	Ҫ��ȡ��CUserIP
	///@param	pTragetUserIP	��Ž����CUserIP
	void retrieve(CUserIP *pUserIP, CWriteableUserIP *pTargetUserIP);
	
	///��ȡ��һ��CUserIP
	///@return	�õ��ĵ�һ��CUserIP�����û�У��򷵻�NULL
	CUserIP *getFirst(void);
	
	///��ȡ��һ��CUserIP
	///@return	�õ���һ��CUserIP�����û�У��򷵻�NULL
	CUserIP *getNext(void);
	
	///������ȡCUserIP
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CUserIPActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CUserIPActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CUserIPCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CUserIPCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	friend class CUserIPIteratorByUserID;

	///��ʼѰ��CUserIP
	///@param	BrokerID	���͹�˾����
	///@param	UserID	�û����
	///@return	���������ĵ�һ��CUserIP������Ҳ���������NULL
	CUserIP *startFindByUserID( const CReadOnlyBrokerIDType& BrokerID,  const CReadOnlyUserIDType& UserID);

	///Ѱ����һ������������CUserIP��������startFindByUserID�Ժ�endFindByUserID֮ǰ����
	///@return	��һ����������CUserIP������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CUserIP *findNextByUserID(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindByUserID(void);

	///Ѱ��CUserIP
	///@param	BrokerID	���͹�˾����
	///@param	UserID	�û����
	///@param	IPAddress	IP��ַ
	///@param	IPMask	IP��ַ����
	///@return	�ҵ���CUserIP������Ҳ���������NULL
	CUserIP *findByUserIPAndMask( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyIPAddressType&  IPAddress,  const CReadOnlyIPAddressType&  IPMask);

	///��������Ѱ��
	///@param	BrokerID	���͹�˾����
	///@param	UserID	�û����
	///@param	IPAddress	IP��ַ
	///@param	IPMask	IP��ַ����
	///@return	�ҵ���CUserIP������Ҳ���������NULL
	CUserIP *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyUserIDType&  UserID,  const CReadOnlyIPAddressType&  IPAddress,  const CReadOnlyIPAddressType&  IPMask);
	
	///��������Ѱ��CUserIP
	///@param	pUserIP	Ҫ�ҵ�ֵ
	///@return	�ҵ���CUserIP������Ҳ���������NULL
	CUserIP *findByPK(CWriteableUserIP *pUserIP);

	///����������ȡCUserIP
	///@param	pUserIP	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CUserIP������Ҳ���������NULL
	bool retrieveByPK(CWriteableUserIP *pUserIP);

	///�������������µ�CUserIP
	///@param	pUserIP	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CUserIP���������ʧ�ܣ��򷵻�NULL
	CUserIP *addByPK(CWriteableUserIP *pUserIP, CTransaction *pTransaction=NULL);

	///������������CUserIP��ֵ
	///@param	pUserIP	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableUserIP *pUserIP, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CUserIP
	///@param	pUserIP	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableUserIP *pUserIP, CTransaction *pTransaction=NULL);


private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CUserIP���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pUserIP	Ҫ�����UserIP
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CUserIP *internalAdd(CWriteableUserIP *pUserIP, bool bNoTransaction);
	
	
	///ˢ�¸�CUserIP�ļ�ֵ
	///@param	pUserIP	��ˢ�µ�CUserIP
	///@param	pNewUserIP	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CUserIP��ͬʱɾ��������
	///@param	pUserIP	Ҫɾ����CUserIP
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CUserIP *pUserIP, bool bNoTransaction);
/*
	///���ĳ��CUserIP�Ƿ����ڱ����󹤳�
	///@param	pUserIP	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CUserIP *pUserIP);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����BrokerID+UserID+IPAddress+IPMask������
	CAVLTree *pUserIPMaskIndex;
	
	
	///����BrokerID��UserID����ʱ���洢�Ĳ�ѯ����
	CBrokerIDType queryBrokerIDInSearchByUserID;
	CUserIDType queryUserIDInSearchByUserID;
	
	///����BrokerID��UserID����ʱ���洢���һ���ҵ��������ڵ�
	CAVLNode *pLastFoundInSearchByUserID;
	
	///����ǰ����
	///@param	pUserIP	Ҫ�����UserIP
	virtual void beforeAdd(CWriteableUserIP *pUserIP);
	
	///����󴥷�
	///@param	pUserIP	�Ѿ������UserIP
	virtual void afterAdd(CUserIP *pUserIP);

	///����ǰ����	
	///@param	pUserIP	��ˢ�µ�CUserIP
	///@param	pNewUserIP	�µ�ֵ
	virtual void beforeUpdate(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP);
	
	///���º󴥷�
	///@param	pUserIP	��ˢ�µ�CUserIP
	virtual void afterUpdate(CUserIP *pUserIP);
	
	///ɾ��ǰ����
	///@param	pUserIP	Ҫɾ����CUserIP
	virtual void beforeRemove(CUserIP *pUserIP);
	
	///ȷ�ϼ���󴥷�
	///@param	pUserIP	�Ѿ������UserIP
	virtual void commitAdd(CUserIP *pUserIP);

	///ȷ�ϸ��º󴥷�
	///@param	pUserIP	��ˢ�µ�CUserIP
	///@param	poldUserIP	ԭ����ֵ
	virtual void commitUpdate(CUserIP *pUserIP, CWriteableUserIP *pOldUserIP);
	
	///ȷ��ɾ���󴥷�
	///@param	pUserIP	�Ѿ�ɾ����CUserIP
	virtual void commitRemove(CWriteableUserIP *pUserIP);

	///������صĴ�����
	vector<CUserIPActionTrigger *> *pActionTriggers;
	vector<CUserIPCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableUserIP compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeFactory��һ���ͻ���Ȩ�������ʱ�Ķ��󹤳�����������һ���ͻ���Ȩ�������ʱ�
///ͬʱ�ֽ����������������Է����ѯ��
///ʹ�ñ����󹤳���������ɶԿͻ���Ȩ�������ʱ����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByBrkIDExIDIstIDVstID��Ψһ�ҵ�����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInvestorOptionFeeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxInvestorOptionFee��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CInvestorOptionFeeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorOptionFeeFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�InvestorOptionFee
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�InvestorOptionFee���ļ��������������ļ��еĶ���InvestorOptionFeeCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�InvestorOptionFee
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�InvestorOptionFee���ļ��������������ļ��еĶ���InvestorOptionFeeCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CInvestorOptionFeeResource;

	///��һ��CInvestorOptionFee���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInvestorOptionFee	Ҫ�����InvestorOptionFee
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInvestorOptionFee *add(CWriteableInvestorOptionFee *pInvestorOptionFee, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CInvestorOptionFee��ֵ
	///@param	pInvestorOptionFee	��ˢ�µ�CInvestorOptionFee
	///@param	pNewInvestorOptionFee	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pInvestorOptionFee	  ��Ҫ��ˢ�»���������CInvestorOptionFee,����NULL��ʾ����Ҫ������
	///@param	pNewInvestorOptionFee	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CInvestorOptionFee* addOrUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CInvestorOptionFee��ͬʱɾ��������
	///@param	pInvestorOptionFee	Ҫɾ����CInvestorOptionFee
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CInvestorOptionFee *pInvestorOptionFee, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CInvestorOptionFee
	///@param	pInvestorOptionFee	Ҫ��ȡ��CInvestorOptionFee
	///@param	pTragetInvestorOptionFee	��Ž����CInvestorOptionFee
	void retrieve(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pTargetInvestorOptionFee);
	
	///��ȡ��һ��CInvestorOptionFee
	///@return	�õ��ĵ�һ��CInvestorOptionFee�����û�У��򷵻�NULL
	CInvestorOptionFee *getFirst(void);
	
	///��ȡ��һ��CInvestorOptionFee
	///@return	�õ���һ��CInvestorOptionFee�����û�У��򷵻�NULL
	CInvestorOptionFee *getNext(void);
	
	///������ȡCInvestorOptionFee
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CInvestorOptionFeeActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CInvestorOptionFeeActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CInvestorOptionFeeCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CInvestorOptionFeeCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CInvestorOptionFee
	///@param	BrokerID	���͹�˾����
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ����
	///@param	InvestorID	Ͷ���ߺ�
	///@return	�ҵ���CInvestorOptionFee������Ҳ���������NULL
	CInvestorOptionFee *findByBrkIDExIDIstIDVstID( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID);

	///��������Ѱ��
	///@param	BrokerID	���͹�˾����
	///@param	ExchangeID	����������
	///@param	InstrumentID	��Լ����
	///@param	InvestorID	Ͷ���ߺ�
	///@return	�ҵ���CInvestorOptionFee������Ҳ���������NULL
	CInvestorOptionFee *findByPK( const CReadOnlyBrokerIDType&  BrokerID,  const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID,  const CReadOnlyInvestorIDType&  InvestorID);
	
	///��������Ѱ��CInvestorOptionFee
	///@param	pInvestorOptionFee	Ҫ�ҵ�ֵ
	///@return	�ҵ���CInvestorOptionFee������Ҳ���������NULL
	CInvestorOptionFee *findByPK(CWriteableInvestorOptionFee *pInvestorOptionFee);

	///����������ȡCInvestorOptionFee
	///@param	pInvestorOptionFee	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CInvestorOptionFee������Ҳ���������NULL
	bool retrieveByPK(CWriteableInvestorOptionFee *pInvestorOptionFee);

	///�������������µ�CInvestorOptionFee
	///@param	pInvestorOptionFee	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CInvestorOptionFee���������ʧ�ܣ��򷵻�NULL
	CInvestorOptionFee *addByPK(CWriteableInvestorOptionFee *pInvestorOptionFee, CTransaction *pTransaction=NULL);

	///������������CInvestorOptionFee��ֵ
	///@param	pInvestorOptionFee	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableInvestorOptionFee *pInvestorOptionFee, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CInvestorOptionFee
	///@param	pInvestorOptionFee	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableInvestorOptionFee *pInvestorOptionFee, CTransaction *pTransaction=NULL);


private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CInvestorOptionFee���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pInvestorOptionFee	Ҫ�����InvestorOptionFee
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CInvestorOptionFee *internalAdd(CWriteableInvestorOptionFee *pInvestorOptionFee, bool bNoTransaction);
	
	
	///ˢ�¸�CInvestorOptionFee�ļ�ֵ
	///@param	pInvestorOptionFee	��ˢ�µ�CInvestorOptionFee
	///@param	pNewInvestorOptionFee	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CInvestorOptionFee��ͬʱɾ��������
	///@param	pInvestorOptionFee	Ҫɾ����CInvestorOptionFee
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CInvestorOptionFee *pInvestorOptionFee, bool bNoTransaction);
/*
	///���ĳ��CInvestorOptionFee�Ƿ����ڱ����󹤳�
	///@param	pInvestorOptionFee	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CInvestorOptionFee *pInvestorOptionFee);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	
	///����BrkIDExIDIstIDVstID��hash����
	CHashIndex *pBrkIDExIDIstIDVstIDHashIndex;
	
	
	///����ǰ����
	///@param	pInvestorOptionFee	Ҫ�����InvestorOptionFee
	virtual void beforeAdd(CWriteableInvestorOptionFee *pInvestorOptionFee);
	
	///����󴥷�
	///@param	pInvestorOptionFee	�Ѿ������InvestorOptionFee
	virtual void afterAdd(CInvestorOptionFee *pInvestorOptionFee);

	///����ǰ����	
	///@param	pInvestorOptionFee	��ˢ�µ�CInvestorOptionFee
	///@param	pNewInvestorOptionFee	�µ�ֵ
	virtual void beforeUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee);
	
	///���º󴥷�
	///@param	pInvestorOptionFee	��ˢ�µ�CInvestorOptionFee
	virtual void afterUpdate(CInvestorOptionFee *pInvestorOptionFee);
	
	///ɾ��ǰ����
	///@param	pInvestorOptionFee	Ҫɾ����CInvestorOptionFee
	virtual void beforeRemove(CInvestorOptionFee *pInvestorOptionFee);
	
	///ȷ�ϼ���󴥷�
	///@param	pInvestorOptionFee	�Ѿ������InvestorOptionFee
	virtual void commitAdd(CInvestorOptionFee *pInvestorOptionFee);

	///ȷ�ϸ��º󴥷�
	///@param	pInvestorOptionFee	��ˢ�µ�CInvestorOptionFee
	///@param	poldInvestorOptionFee	ԭ����ֵ
	virtual void commitUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pOldInvestorOptionFee);
	
	///ȷ��ɾ���󴥷�
	///@param	pInvestorOptionFee	�Ѿ�ɾ����CInvestorOptionFee
	virtual void commitRemove(CWriteableInvestorOptionFee *pInvestorOptionFee);

	///������صĴ�����
	vector<CInvestorOptionFeeActionTrigger *> *pActionTriggers;
	vector<CInvestorOptionFeeCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableInvestorOptionFee compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataFactory��һ��ʵʱ�����Ķ��󹤳�����������һ��ʵʱ�����
///ͬʱ�ֽ����������������Է����ѯ��
///	ExchangeIDAndInstrumentIDIndex
///ʹ�ñ����󹤳���������ɶ�ʵʱ��������ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findByExchangeIDAndInstrumentID��Ψһ�ҵ�����
///		ʹ��startFindAll��findNextAll��endFindAll��ɲ�ѯ����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CMarketDataFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxMarketData��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CMarketDataFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CMarketDataFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�MarketData
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�MarketData���ļ��������������ļ��еĶ���MarketDataCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�MarketData
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�MarketData���ļ��������������ļ��еĶ���MarketDataCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CMarketDataResource;

	///��һ��CMarketData���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pMarketData	Ҫ�����MarketData
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CMarketData *add(CWriteableMarketData *pMarketData, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CMarketData��ֵ
	///@param	pMarketData	��ˢ�µ�CMarketData
	///@param	pNewMarketData	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pMarketData	  ��Ҫ��ˢ�»���������CMarketData,����NULL��ʾ����Ҫ������
	///@param	pNewMarketData	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CMarketData* addOrUpdate(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CMarketData��ͬʱɾ��������
	///@param	pMarketData	Ҫɾ����CMarketData
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CMarketData *pMarketData, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CMarketData
	///@param	pMarketData	Ҫ��ȡ��CMarketData
	///@param	pTragetMarketData	��Ž����CMarketData
	void retrieve(CMarketData *pMarketData, CWriteableMarketData *pTargetMarketData);
	
	///��ȡ��һ��CMarketData
	///@return	�õ��ĵ�һ��CMarketData�����û�У��򷵻�NULL
	CMarketData *getFirst(void);
	
	///��ȡ��һ��CMarketData
	///@return	�õ���һ��CMarketData�����û�У��򷵻�NULL
	CMarketData *getNext(void);
	
	///������ȡCMarketData
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CMarketDataActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CMarketDataActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CMarketDataCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CMarketDataCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CMarketData
	///@param	ExchangeID	���������
	///@param	InstrumentID	��Լ���
	///@return	�ҵ���CMarketData������Ҳ���������NULL
	CMarketData *findByExchangeIDAndInstrumentID( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID);

	///��������Ѱ��
	///@param	ExchangeID	���������
	///@param	InstrumentID	��Լ���
	///@return	�ҵ���CMarketData������Ҳ���������NULL
	CMarketData *findByPK( const CReadOnlyExchangeIDType&  ExchangeID,  const CReadOnlyInstrumentIDType&  InstrumentID);
	
	///��������Ѱ��CMarketData
	///@param	pMarketData	Ҫ�ҵ�ֵ
	///@return	�ҵ���CMarketData������Ҳ���������NULL
	CMarketData *findByPK(CWriteableMarketData *pMarketData);

	///����������ȡCMarketData
	///@param	pMarketData	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CMarketData������Ҳ���������NULL
	bool retrieveByPK(CWriteableMarketData *pMarketData);

	///�������������µ�CMarketData
	///@param	pMarketData	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CMarketData���������ʧ�ܣ��򷵻�NULL
	CMarketData *addByPK(CWriteableMarketData *pMarketData, CTransaction *pTransaction=NULL);

	///������������CMarketData��ֵ
	///@param	pMarketData	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableMarketData *pMarketData, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CMarketData
	///@param	pMarketData	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableMarketData *pMarketData, CTransaction *pTransaction=NULL);


	friend class CMarketDataIteratorAll;

	///��ʼѰ��CMarketData
	///@return	���������ĵ�һ��CMarketData������Ҳ���������NULL
	CMarketData *startFindAll();

	///Ѱ����һ������������CMarketData��������startFindAll�Ժ�endFindAll֮ǰ����
	///@return	��һ����������CMarketData������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	CMarketData *findNextAll(void);

	///������һ�β�ѯ������ɲ�ѯ�������ñ�����
	void endFindAll(void);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CMarketData���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pMarketData	Ҫ�����MarketData
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CMarketData *internalAdd(CWriteableMarketData *pMarketData, bool bNoTransaction);
	
	
	///ˢ�¸�CMarketData�ļ�ֵ
	///@param	pMarketData	��ˢ�µ�CMarketData
	///@param	pNewMarketData	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CMarketData��ͬʱɾ��������
	///@param	pMarketData	Ҫɾ����CMarketData
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CMarketData *pMarketData, bool bNoTransaction);
/*
	///���ĳ��CMarketData�Ƿ����ڱ����󹤳�
	///@param	pMarketData	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CMarketData *pMarketData);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����ExchangeID+InstrumentID������
	CAVLTree *pExchangeIDAndInstrumentIDIndex;
	
	
	///���ռ���ʱ���洢�Ĳ�ѯ����
	
	///���ռ���ʱ���洢���һ���ҵ��������ڵ�
	CMarketData *pLastFoundInSearchAll;
	
	///����ǰ����
	///@param	pMarketData	Ҫ�����MarketData
	virtual void beforeAdd(CWriteableMarketData *pMarketData);
	
	///����󴥷�
	///@param	pMarketData	�Ѿ������MarketData
	virtual void afterAdd(CMarketData *pMarketData);

	///����ǰ����	
	///@param	pMarketData	��ˢ�µ�CMarketData
	///@param	pNewMarketData	�µ�ֵ
	virtual void beforeUpdate(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData);
	
	///���º󴥷�
	///@param	pMarketData	��ˢ�µ�CMarketData
	virtual void afterUpdate(CMarketData *pMarketData);
	
	///ɾ��ǰ����
	///@param	pMarketData	Ҫɾ����CMarketData
	virtual void beforeRemove(CMarketData *pMarketData);
	
	///ȷ�ϼ���󴥷�
	///@param	pMarketData	�Ѿ������MarketData
	virtual void commitAdd(CMarketData *pMarketData);

	///ȷ�ϸ��º󴥷�
	///@param	pMarketData	��ˢ�µ�CMarketData
	///@param	poldMarketData	ԭ����ֵ
	virtual void commitUpdate(CMarketData *pMarketData, CWriteableMarketData *pOldMarketData);
	
	///ȷ��ɾ���󴥷�
	///@param	pMarketData	�Ѿ�ɾ����CMarketData
	virtual void commitRemove(CWriteableMarketData *pMarketData);

	///������صĴ�����
	vector<CMarketDataActionTrigger *> *pActionTriggers;
	vector<CMarketDataCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableMarketData compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayFactory��һ��ί���ӳٱ�Ķ��󹤳�����������һ��ί���ӳٱ�
///ͬʱ�ֽ����������������Է����ѯ��
///ʹ�ñ����󹤳���������ɶ�ί���ӳٱ����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	COrderDelayFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxOrderDelay��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	COrderDelayFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~COrderDelayFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�OrderDelay
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�OrderDelay���ļ��������������ļ��еĶ���OrderDelayCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�OrderDelay
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�OrderDelay���ļ��������������ļ��еĶ���OrderDelayCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class COrderDelayResource;

	///��һ��COrderDelay���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pOrderDelay	Ҫ�����OrderDelay
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	COrderDelay *add(CWriteableOrderDelay *pOrderDelay, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�COrderDelay��ֵ
	///@param	pOrderDelay	��ˢ�µ�COrderDelay
	///@param	pNewOrderDelay	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pOrderDelay	  ��Ҫ��ˢ�»���������COrderDelay,����NULL��ʾ����Ҫ������
	///@param	pNewOrderDelay	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	COrderDelay* addOrUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��COrderDelay��ͬʱɾ��������
	///@param	pOrderDelay	Ҫɾ����COrderDelay
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(COrderDelay *pOrderDelay, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��COrderDelay
	///@param	pOrderDelay	Ҫ��ȡ��COrderDelay
	///@param	pTragetOrderDelay	��Ž����COrderDelay
	void retrieve(COrderDelay *pOrderDelay, CWriteableOrderDelay *pTargetOrderDelay);
	
	///��ȡ��һ��COrderDelay
	///@return	�õ��ĵ�һ��COrderDelay�����û�У��򷵻�NULL
	COrderDelay *getFirst(void);
	
	///��ȡ��һ��COrderDelay
	///@return	�õ���һ��COrderDelay�����û�У��򷵻�NULL
	COrderDelay *getNext(void);
	
	///������ȡCOrderDelay
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(COrderDelayActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(COrderDelayActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(COrderDelayCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(COrderDelayCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��COrderDelay���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pOrderDelay	Ҫ�����OrderDelay
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	COrderDelay *internalAdd(CWriteableOrderDelay *pOrderDelay, bool bNoTransaction);
	
	
	///ˢ�¸�COrderDelay�ļ�ֵ
	///@param	pOrderDelay	��ˢ�µ�COrderDelay
	///@param	pNewOrderDelay	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��COrderDelay��ͬʱɾ��������
	///@param	pOrderDelay	Ҫɾ����COrderDelay
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(COrderDelay *pOrderDelay, bool bNoTransaction);
/*
	///���ĳ��COrderDelay�Ƿ����ڱ����󹤳�
	///@param	pOrderDelay	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(COrderDelay *pOrderDelay);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	
	
	
	///����ǰ����
	///@param	pOrderDelay	Ҫ�����OrderDelay
	virtual void beforeAdd(CWriteableOrderDelay *pOrderDelay);
	
	///����󴥷�
	///@param	pOrderDelay	�Ѿ������OrderDelay
	virtual void afterAdd(COrderDelay *pOrderDelay);

	///����ǰ����	
	///@param	pOrderDelay	��ˢ�µ�COrderDelay
	///@param	pNewOrderDelay	�µ�ֵ
	virtual void beforeUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay);
	
	///���º󴥷�
	///@param	pOrderDelay	��ˢ�µ�COrderDelay
	virtual void afterUpdate(COrderDelay *pOrderDelay);
	
	///ɾ��ǰ����
	///@param	pOrderDelay	Ҫɾ����COrderDelay
	virtual void beforeRemove(COrderDelay *pOrderDelay);
	
	///ȷ�ϼ���󴥷�
	///@param	pOrderDelay	�Ѿ������OrderDelay
	virtual void commitAdd(COrderDelay *pOrderDelay);

	///ȷ�ϸ��º󴥷�
	///@param	pOrderDelay	��ˢ�µ�COrderDelay
	///@param	poldOrderDelay	ԭ����ֵ
	virtual void commitUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pOldOrderDelay);
	
	///ȷ��ɾ���󴥷�
	///@param	pOrderDelay	�Ѿ�ɾ����COrderDelay
	virtual void commitRemove(CWriteableOrderDelay *pOrderDelay);

	///������صĴ�����
	vector<COrderDelayActionTrigger *> *pActionTriggers;
	vector<COrderDelayCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableOrderDelay compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoFactory��һ��QDPϵͳ��Ϣ�Ķ��󹤳�����������һ��QDPϵͳ��Ϣ��
///ͬʱ�ֽ����������������Է����ѯ��
///	SystemIDIndex
///ʹ�ñ����󹤳���������ɶ�QDPϵͳ��Ϣ����ɾ�Ĳ���������巽�����£�
///	���ӣ�����add����ɼ���
///	ɾ��������remove�Ϳ���ɾ��
///	��ѯ�������·������Բ�ѯ��
///		ʹ��findBySystemID��Ψһ�ҵ�����
///	�޸ģ����ڲ鵽�Ľ��������ͨ��retrieveȡ�����޸ĺ�ͨ��update�Ż�
///	����������е����ӡ�ɾ�����޸Ķ�����ָ������������commitʱ������д��
///		��retrieveʱ��Ҳ����ָ�����񣬴�ʱ��ȡ������update��������
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoFactory :public CDatabaseDataFactory
{
public:
	///���췽��
	///@param	maxUnit	��ʼ�����ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CSystemInfoFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID=-1, int readOnly=0);
	
	///���췽��
	///@param	pConfig	��ǰ�������ļ��������󽫸��������ļ��еĶ���MaxSystemInfo��������Ķ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	CSystemInfoFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse=false, int reuseID = -1,int readOnly=0);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CSystemInfoFactory(void);

	virtual void output(CLogger *pLogger,int indent=0);
	
	///��CSV�ļ��ж�ȡ���е�SystemInfo
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(char *filename);

	///��CSV�ļ��ж�ȡ���е�SystemInfo���ļ��������������ļ��еĶ���SystemInfoCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int readCSV(CConfig *pConfig);
	
	///��CSV�ļ���д�����е�SystemInfo
	///@param	filename	�ļ���
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(char *filename);

	///��CSV�ļ���д�����е�SystemInfo���ļ��������������ļ��еĶ���SystemInfoCSVFile
	///@param	pConfig	��ǰ�������ļ�
	///@return	1��ʾ��ɣ�0��ʾû�����
	virtual int writeCSV(CConfig *pConfig);

	///������д���ļ���,����DEBUG
	virtual void dump(FILE *);

	///������д���ļ���,����DEBUG
	virtual void dump(char *filename);

	///������еļ�¼
	virtual void clearAll(void);

	friend class CSystemInfoResource;

	///��һ��CSystemInfo���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pSystemInfo	Ҫ�����SystemInfo
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CSystemInfo *add(CWriteableSystemInfo *pSystemInfo, CTransaction *pTransaction=NULL);
	
	///ˢ�¸�CSystemInfo��ֵ
	///@param	pSystemInfo	��ˢ�µ�CSystemInfo
	///@param	pNewSystemInfo	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	void update(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///���ӻ��߸�������
	///@param	pSystemInfo	  ��Ҫ��ˢ�»���������CSystemInfo,����NULL��ʾ����Ҫ������
	///@param	pNewSystemInfo	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	  �Ƿ���Ҫ��������
	///@param	���������޸ĺ������
	CSystemInfo* addOrUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo, CTransaction *pTransaction=NULL, bool updateIndex=true);
	
	///ɾ��һ��CSystemInfo��ͬʱɾ��������
	///@param	pSystemInfo	Ҫɾ����CSystemInfo
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	void remove(CSystemInfo *pSystemInfo, CTransaction *pTransaction=NULL);
	
	///��ȡĳ��CSystemInfo
	///@param	pSystemInfo	Ҫ��ȡ��CSystemInfo
	///@param	pTragetSystemInfo	��Ž����CSystemInfo
	void retrieve(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pTargetSystemInfo);
	
	///��ȡ��һ��CSystemInfo
	///@return	�õ��ĵ�һ��CSystemInfo�����û�У��򷵻�NULL
	CSystemInfo *getFirst(void);
	
	///��ȡ��һ��CSystemInfo
	///@return	�õ���һ��CSystemInfo�����û�У��򷵻�NULL
	CSystemInfo *getNext(void);
	
	///������ȡCSystemInfo
	void endGet(void);

	///����һ������������
	///@param	pTrigger	Ҫ����Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addActionTrigger(CSystemInfoActionTrigger *pTrigger);
	
	///ɾ��һ������������
	///@param	pTrigger	Ҫɾ���Ĳ���������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeActionTrigger(CSystemInfoActionTrigger *pTrigger);

	///����һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫ�����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int addCommitTrigger(CSystemInfoCommitTrigger *pTrigger);
	
	///ɾ��һ��ȷ�ϴ�����
	///@param	pTrigger	Ҫɾ����ȷ�ϴ�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int removeCommitTrigger(CSystemInfoCommitTrigger *pTrigger);
	
	///����ȷ�ϴ�������ȱʡ�Ǽ����
	///@param	activation	true��ʾҪ���false��ʾҪͣ��
	void activeCommitTrigger(bool activation);

	///Ѱ��CSystemInfo
	///@param	SystemID	���������
	///@return	�ҵ���CSystemInfo������Ҳ���������NULL
	CSystemInfo *findBySystemID( const CReadOnlySystemIDType&  SystemID);

	///��������Ѱ��
	///@param	SystemID	���������
	///@return	�ҵ���CSystemInfo������Ҳ���������NULL
	CSystemInfo *findByPK( const CReadOnlySystemIDType&  SystemID);
	
	///��������Ѱ��CSystemInfo
	///@param	pSystemInfo	Ҫ�ҵ�ֵ
	///@return	�ҵ���CSystemInfo������Ҳ���������NULL
	CSystemInfo *findByPK(CWriteableSystemInfo *pSystemInfo);

	///����������ȡCSystemInfo
	///@param	pSystemInfo	Ҫ��ȡ��ֵ��ͬʱ���ڴ�ŷ��صĽ��
	///@return	�ҵ���CSystemInfo������Ҳ���������NULL
	bool retrieveByPK(CWriteableSystemInfo *pSystemInfo);

	///�������������µ�CSystemInfo
	///@param	pSystemInfo	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	���ز����CSystemInfo���������ʧ�ܣ��򷵻�NULL
	CSystemInfo *addByPK(CWriteableSystemInfo *pSystemInfo, CTransaction *pTransaction=NULL);

	///������������CSystemInfo��ֵ
	///@param	pSystemInfo	�µ�ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool updateByPK(CWriteableSystemInfo *pSystemInfo, CTransaction *pTransaction=NULL, bool updateIndex=true);

	///��������ɾ��CSystemInfo
	///@param	pSystemInfo	Ҫɾ����ֵ
	///@param	pTransaction	���β������������������NULL����ʾ��ʹ���������������Ч��������Ҫ�ڸ�����commitʱ��Ч
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool removeByPK(CWriteableSystemInfo *pSystemInfo, CTransaction *pTransaction=NULL);


private:
	///����Լ��ĳ�ʼ������
	///@param	maxUnit	�������ݶ������
	///@param	pAllocator	�����ڴ����ķ�����
	///@param	pIndexMap	�������ƺ��ڴ��ŵĶ�Ӧ���ڷ�����ʱ��д�룬������ʱֻ����
	///@param	reuse	�Ƿ�����
	///@param	reuseID	���ñ�ţ�������ʱӦ����Ϊ-1
	///@param	readOnly	1��ʾ��CFixMem��ֻ���ģ�0��ʾ���Զ�д
	void init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly);
	
	
	///��һ��CSystemInfo���뵽�ö��󹤳���ʵ����������޸������Ĺ���
	///@param	pSystemInfo	Ҫ�����SystemInfo
	///@param	bNoTransaction �Ƿ������κ�����
	///@return	�����ö����λ�ã���pTransaction!=NULLʱ�����Ƿ���NULL
	CSystemInfo *internalAdd(CWriteableSystemInfo *pSystemInfo, bool bNoTransaction);
	
	
	///ˢ�¸�CSystemInfo�ļ�ֵ
	///@param	pSystemInfo	��ˢ�µ�CSystemInfo
	///@param	pNewSystemInfo	�µ�ֵ
	///@param	updateIndex	�Ƿ���Ҫ��������
	///@param	bNoTransaction �Ƿ������κ�����
	void internalUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo, bool updateIndex,bool bNoTransaction);
	
	///ɾ��һ��CSystemInfo��ͬʱɾ��������
	///@param	pSystemInfo	Ҫɾ����CSystemInfo
	///@param	bNoTransaction �Ƿ������κ�����
	void internalRemove(CSystemInfo *pSystemInfo, bool bNoTransaction);
/*
	///���ĳ��CSystemInfo�Ƿ����ڱ����󹤳�
	///@param	pSystemInfo	Ҫ���Ķ���
	///@exception	CDesignError	��������ڣ����׳����쳣
	void checkAddress(CSystemInfo *pSystemInfo);
*/
	///ʹ�õ������ļ�
	CConfig *m_pConfig;

	///����SystemID������
	CAVLTree *pSystemIDIndex;
	
	
	
	///����ǰ����
	///@param	pSystemInfo	Ҫ�����SystemInfo
	virtual void beforeAdd(CWriteableSystemInfo *pSystemInfo);
	
	///����󴥷�
	///@param	pSystemInfo	�Ѿ������SystemInfo
	virtual void afterAdd(CSystemInfo *pSystemInfo);

	///����ǰ����	
	///@param	pSystemInfo	��ˢ�µ�CSystemInfo
	///@param	pNewSystemInfo	�µ�ֵ
	virtual void beforeUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo);
	
	///���º󴥷�
	///@param	pSystemInfo	��ˢ�µ�CSystemInfo
	virtual void afterUpdate(CSystemInfo *pSystemInfo);
	
	///ɾ��ǰ����
	///@param	pSystemInfo	Ҫɾ����CSystemInfo
	virtual void beforeRemove(CSystemInfo *pSystemInfo);
	
	///ȷ�ϼ���󴥷�
	///@param	pSystemInfo	�Ѿ������SystemInfo
	virtual void commitAdd(CSystemInfo *pSystemInfo);

	///ȷ�ϸ��º󴥷�
	///@param	pSystemInfo	��ˢ�µ�CSystemInfo
	///@param	poldSystemInfo	ԭ����ֵ
	virtual void commitUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pOldSystemInfo);
	
	///ȷ��ɾ���󴥷�
	///@param	pSystemInfo	�Ѿ�ɾ����CSystemInfo
	virtual void commitRemove(CWriteableSystemInfo *pSystemInfo);

	///������صĴ�����
	vector<CSystemInfoActionTrigger *> *pActionTriggers;
	vector<CSystemInfoCommitTrigger *> *pCommitTriggers;
	
	///���в�ѯʱ�����ڱȽϵĶ���
	CWriteableSystemInfo compareObject;
	
	///�Ƿ񼤻�ȷ�ϴ�����
	bool m_activeCommitTrigger;
};

#endif
