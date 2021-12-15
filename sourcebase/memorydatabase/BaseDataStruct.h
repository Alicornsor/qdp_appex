/////////////////////////////////////////////////////////////////////////
///@system ִ������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file BaseDataStruct.h
///@brief�������ڴ����ݿ��õĻ������ݽṹ�࣬�Լ�iterator��trigger�Ļ���
///@history 
///20121227	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef BASEDATASTRUCT_H
#define BASEDATASTRUCT_H

#include "platform.h"
#include "CBaseObject.h"
#include "customDataType.h"
#include "CTransaction.h"
#include "XtpData.h"

///�жϽ���Ƿ���������
extern bool satisfy(int value,int type);

///�ַ����ȽϺ���
///@param	s1	�ַ���1
///@param	s2	�ַ���2
///@return	1��ʾ���ڣ�0��ʾ���ڣ�-1��ʾС��
int compare(const char *s1, const char *s2);

///�����ȽϺ���
///@param	v1	����1
///@param	v2	����2
///@return	1��ʾ���ڣ�0��ʾ���ڣ�-1��ʾС��
int compare(const int v1,const int v2);

///�����ȽϺ���
///@param	v1	����1
///@param	v2	����2
///@return	1��ʾ���ڣ�0��ʾ���ڣ�-1��ʾС��
int compare(const long v1,const long v2);

///�������ȽϺ���
///@param	v1	������1
///@param	v2	������2
///@return	1��ʾ���ڣ�0��ʾ���ڣ�-1��ʾС��
int compare(const double v1,const double v2);

///��buffer�л�ȡ��һ��token�������token���Զ��Ż��߻��зָ���
///��ʹ��ʱ����һ��Ӧ������ָ����buffer���Ժ�Ӧ����������NULL��
///������������ȡ�����е�token�����������ı�buffer�е����ݣ�����
///���������Լ��������ݡ����������������⣬��һ��ȡtoken�����н�
///��ǰ����ʼ�µ�һ��ȡtoken���У���Ӱ��ǰ��һ���Ľ�����������
///strtok����������
///@param	buffer	Ҫȡtoken��buffer��NULL��ʾ���ϴ�ȡ��buffer��ȡ��һ��
///@return	�õ���token
char *getNextToken(char *buffer);

class CWriteableDataSyncStatus;
class CDataSyncStatusFactory;
class CWriteableSystemStatus;
class CSystemStatusFactory;
class CWriteableOrderAction;
class COrderActionFactory;
class CWriteableOrder;
class COrderFactory;
class CWriteableTrade;
class CTradeFactory;
class CWriteablePreOrder;
class CPreOrderFactory;
class CWriteableIndexPreOrder;
class CIndexPreOrderFactory;
class CWriteableInvestorPosition;
class CInvestorPositionFactory;
class CWriteableInvestorAccount;
class CInvestorAccountFactory;
class CWriteableInvestorAccountDeposit;
class CInvestorAccountDepositFactory;
class CWriteableExchange;
class CExchangeFactory;
class CWriteableSeat;
class CSeatFactory;
class CWriteableInstrument;
class CInstrumentFactory;
class CWriteableCmbInstrumentDetail;
class CCmbInstrumentDetailFactory;
class CWriteableClientTradingID;
class CClientTradingIDFactory;
class CWriteableInvestor;
class CInvestorFactory;
class CWriteableInvestorMargin;
class CInvestorMarginFactory;
class CWriteableInvestorFee;
class CInvestorFeeFactory;
class CWriteableUser;
class CUserFactory;
class CWriteableUserInvestor;
class CUserInvestorFactory;
class CWriteableOrderInsertFailed;
class COrderInsertFailedFactory;
class CWriteableUserTradingRight;
class CUserTradingRightFactory;
class CWriteableCurrentTime;
class CCurrentTimeFactory;
class CWriteableUserSession;
class CUserSessionFactory;
class CWriteableMaxLocalID;
class CMaxLocalIDFactory;
class CWriteableBrkUserIDLocalID;
class CBrkUserIDLocalIDFactory;
class CWriteablePartClientInsGroupPosition;
class CPartClientInsGroupPositionFactory;
class CWriteableClientMarginCombType;
class CClientMarginCombTypeFactory;
class CWriteableInstrumentGroup;
class CInstrumentGroupFactory;
class CWriteableSGEDeferRate;
class CSGEDeferRateFactory;
class CWriteableInvestorTradingRight;
class CInvestorTradingRightFactory;
class CWriteableUserIP;
class CUserIPFactory;
class CWriteableInvestorOptionFee;
class CInvestorOptionFeeFactory;
class CWriteableMarketData;
class CMarketDataFactory;
class CWriteableOrderDelay;
class COrderDelayFactory;
class CWriteableSystemInfo;
class CSystemInfoFactory;

/////////////////////////////////////////////////////////////////////////
///CWriteableDataSyncStatus��һ���洢����ͬ��״̬��Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableDataSyncStatus
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! TradingDay.isValid())
			return 0;
		if (! DataSyncStatus.isValid())
			return 0;
		if (! SystemID.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableDataSyncStatus *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///������
	CDateType TradingDay;
	///����ͬ��״̬
	CDataSyncStatusType DataSyncStatus;
	///QDPϵͳ���
	CSystemIDType SystemID;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableDataSyncStatus CDataSyncStatus;

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusActionTrigger�ǲ�������ͬ��״̬��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusActionTrigger
{
public:
	///���췽��
	CDataSyncStatusActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CDataSyncStatusActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CDataSyncStatusFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pDataSyncStatus	Ҫ�����DataSyncStatus
	virtual void beforeAdd(CWriteableDataSyncStatus *pDataSyncStatus)
	{
		return;
	}
	
	///����󴥷�
	///@param	pDataSyncStatus	�Ѿ������DataSyncStatus
	virtual void afterAdd(CDataSyncStatus *pDataSyncStatus)
	{
		return;
	}

	///����ǰ����	
	///@param	pDataSyncStatus	��ˢ�µ�CDataSyncStatus
	///@param	pNewDataSyncStatus	�µ�ֵ
	virtual void beforeUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pDataSyncStatus	��ˢ�µ�CDataSyncStatus
	virtual void afterUpdate(CDataSyncStatus *pDataSyncStatus)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pDataSyncStatus	Ҫɾ����CDataSyncStatus
	virtual void beforeRemove(CDataSyncStatus *pDataSyncStatus)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CDataSyncStatusFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusCommitTrigger��ȷ������ͬ��״̬��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusCommitTrigger
{
public:
	///���췽��
	CDataSyncStatusCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CDataSyncStatusCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CDataSyncStatusFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pDataSyncStatus	�Ѿ������DataSyncStatus
	virtual void commitAdd(CDataSyncStatus *pDataSyncStatus)
	{
		return;
	}

	///���º󴥷�
	///@param	pDataSyncStatus	��ˢ�µ�CDataSyncStatus
	///@param	poldDataSyncStatus	ԭ����ֵ
	virtual void commitUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pOldDataSyncStatus)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pDataSyncStatus	�Ѿ�ɾ����CDataSyncStatus
	virtual void commitRemove(CWriteableDataSyncStatus *pDataSyncStatus)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CDataSyncStatusFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusIterator��һ��������ͬ��״̬���ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusIterator
{
public:
	///���췽��
	CDataSyncStatusIterator(void)
	{
	}

	///���췽��
	CDataSyncStatusIterator(CDataSyncStatusFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CDataSyncStatusIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��DataSyncStatus
	///@return	��һ����������CDataSyncStatus������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CDataSyncStatus *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CDataSyncStatusFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pDataSyncStatus ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableDataSyncStatus * pDataSyncStatus,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CDataSyncStatusFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableSystemStatus��һ���洢QDP״̬��Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableSystemStatus
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! TradingDay.isValid())
			return 0;
		if (! SystemStatus.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableSystemStatus *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///������
	CDateType TradingDay;
	///ϵͳ״̬
	CSystemStatusType SystemStatus;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableSystemStatus CSystemStatus;

/////////////////////////////////////////////////////////////////////////
///CSystemStatusActionTrigger�ǲ���QDP״̬��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusActionTrigger
{
public:
	///���췽��
	CSystemStatusActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CSystemStatusActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CSystemStatusFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pSystemStatus	Ҫ�����SystemStatus
	virtual void beforeAdd(CWriteableSystemStatus *pSystemStatus)
	{
		return;
	}
	
	///����󴥷�
	///@param	pSystemStatus	�Ѿ������SystemStatus
	virtual void afterAdd(CSystemStatus *pSystemStatus)
	{
		return;
	}

	///����ǰ����	
	///@param	pSystemStatus	��ˢ�µ�CSystemStatus
	///@param	pNewSystemStatus	�µ�ֵ
	virtual void beforeUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pSystemStatus	��ˢ�µ�CSystemStatus
	virtual void afterUpdate(CSystemStatus *pSystemStatus)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pSystemStatus	Ҫɾ����CSystemStatus
	virtual void beforeRemove(CSystemStatus *pSystemStatus)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CSystemStatusFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusCommitTrigger��ȷ��QDP״̬��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusCommitTrigger
{
public:
	///���췽��
	CSystemStatusCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CSystemStatusCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CSystemStatusFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pSystemStatus	�Ѿ������SystemStatus
	virtual void commitAdd(CSystemStatus *pSystemStatus)
	{
		return;
	}

	///���º󴥷�
	///@param	pSystemStatus	��ˢ�µ�CSystemStatus
	///@param	poldSystemStatus	ԭ����ֵ
	virtual void commitUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pOldSystemStatus)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pSystemStatus	�Ѿ�ɾ����CSystemStatus
	virtual void commitRemove(CWriteableSystemStatus *pSystemStatus)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CSystemStatusFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusIterator��һ����QDP״̬���ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusIterator
{
public:
	///���췽��
	CSystemStatusIterator(void)
	{
	}

	///���췽��
	CSystemStatusIterator(CSystemStatusFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CSystemStatusIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��SystemStatus
	///@return	��һ����������CSystemStatus������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSystemStatus *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CSystemStatusFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pSystemStatus ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSystemStatus * pSystemStatus,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CSystemStatusFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableOrderAction��һ���洢���������Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableOrderAction
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! ExchangeID.isValid())
			return 0;
		if (! OrderSysID.isValid())
			return 0;
		if (! BrokerID.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! UserID.isValid())
			return 0;
		if (! InstrumentID.isValid())
			return 0;
		if (! UserOrderActionLocalID.isValid())
			return 0;
		if (! UserOrderLocalID.isValid())
			return 0;
		if (! ActionFlag.isValid())
			return 0;
		if (! LimitPrice.isValid())
			return 0;
		if (! VolumeChange.isValid())
			return 0;
		if (! RecNum.isValid())
			return 0;
		if (! FrontID.isValid())
			return 0;
		if (! SessionID.isValid())
			return 0;
		if (! UserCustom.isValid())
			return 0;
		if (! SeatID.isValid())
			return 0;
		if (! ActionLocalID.isValid())
			return 0;
		if (! ClientID.isValid())
			return 0;
		if (! ParticipantID.isValid())
			return 0;
		if (! CancelTime.isValid())
			return 0;
		if (! ActionSource.isValid())
			return 0;
		if (! Tradable.isValid())
			return 0;
		if (! OrderLocalID.isValid())
			return 0;
		if (! IsForgeRtn.isValid())
			return 0;
		if (! APIID.isValid())
			return 0;
		if (! IPAddress.isValid())
			return 0;
		if (! MacAddress.isValid())
			return 0;
		if (! OrderActionType.isValid())
			return 0;
		if (! OrderBatchNo.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableOrderAction *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///����������
	CExchangeIDType ExchangeID;
	///�������
	COrderSysIDType OrderSysID;
	///���͹�˾���
	CBrokerIDType BrokerID;
	///Ͷ���߱��
	CInvestorIDType InvestorID;
	///�û�����
	CUserIDType UserID;
	///��Լ����
	CInstrumentIDType InstrumentID;
	///���γ��������ı��ر��
	CUserOrderLocalIDType UserOrderActionLocalID;
	///���������ı��ر������
	CUserOrderLocalIDType UserOrderLocalID;
	///����������־
	CActionFlagType ActionFlag;
	///�۸�
	CPriceType LimitPrice;
	///�����仯
	CVolumeType VolumeChange;
	///��¼���
	CSequenceNoType RecNum;
	///ǰ�ñ��
	CFrontIDType FrontID;
	///�Ự���
	CSessionIDType SessionID;
	///�û��Զ�����
	CCustomType UserCustom;
	///�µ�ϯλ��
	CSeatIDType SeatID;
	///�������ر��
	COrderLocalIDType ActionLocalID;
	///�ͻ�����
	CClientIDType ClientID;
	///��Ա����
	CParticipantIDType ParticipantID;
	///����ʱ��
	CTimeType CancelTime;
	///������Դ
	CActionSourceType ActionSource;
	///�Ƿ���Բμӽ���
	CBoolType Tradable;
	///���ر������
	COrderLocalIDType OrderLocalID;
	///α��Rtn
	CBoolType IsForgeRtn;
	///ͨ����Ӧ��APIID
	CNumberType APIID;
	///�µ�IP��ַ
	CIPAddressType IPAddress;
	///�µ�MAC��ַ
	CMacAddressType MacAddress;
	///������Ӧ�ı������
	COrderActionTypeType OrderActionType;
	///�������κ�
	COrderSysIDType OrderBatchNo;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	
	///�����Ӧ�ı�����ָ��
	///@param	pFactory	�����Ӧ�ı�����ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ�ı�����ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableOrder *linkOrder(COrderFactory *pFactory) const;

	///�����Ӧ�ı���ָ��
	///@param	pOrder	Ҫ���ӵ��Ķ���
	///@return	�����pOrder
	const CWriteableOrder *linkOrder(const CWriteableOrder *pOrder) const
	{
		void *target=(void *)(&(this->pOrder));
		*((const CWriteableOrder **)target)=pOrder;
		return pOrder;
	}
	
	///��ȡ��Ӧ�ı�����ָ��
	///@return	�ҵ��Ķ�Ӧ�ı�����ָ�룬����Ҳ����򷵻�NULL
	const CWriteableOrder *getOrder(void) const
	{
		return pOrder;
	}
	///�����Ӧ�ı�����ָ��
	///@param	pFactory	�����Ӧ�ı�����ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ�ı�����ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteablePreOrder *linkPreOrder(CPreOrderFactory *pFactory) const;

	///�����Ӧ�ı���ָ��
	///@param	pPreOrder	Ҫ���ӵ��Ķ���
	///@return	�����pPreOrder
	const CWriteablePreOrder *linkPreOrder(const CWriteablePreOrder *pPreOrder) const
	{
		void *target=(void *)(&(this->pPreOrder));
		*((const CWriteablePreOrder **)target)=pPreOrder;
		return pPreOrder;
	}
	
	///��ȡ��Ӧ�ı�����ָ��
	///@return	�ҵ��Ķ�Ӧ�ı�����ָ�룬����Ҳ����򷵻�NULL
	const CWriteablePreOrder *getPreOrder(void) const
	{
		return pPreOrder;
	}

private:
	///��Ӧ�ı���
	const CWriteableOrder *pOrder;
	///��Ӧ�ı���
	const CWriteablePreOrder *pPreOrder;
};

typedef const CWriteableOrderAction COrderAction;

/////////////////////////////////////////////////////////////////////////
///COrderActionActionTrigger�ǲ�����������ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionActionTrigger
{
public:
	///���췽��
	COrderActionActionTrigger(void)
	{
	}
	
	///��������
	virtual ~COrderActionActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(COrderActionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pOrderAction	Ҫ�����OrderAction
	virtual void beforeAdd(CWriteableOrderAction *pOrderAction)
	{
		return;
	}
	
	///����󴥷�
	///@param	pOrderAction	�Ѿ������OrderAction
	virtual void afterAdd(COrderAction *pOrderAction)
	{
		return;
	}

	///����ǰ����	
	///@param	pOrderAction	��ˢ�µ�COrderAction
	///@param	pNewOrderAction	�µ�ֵ
	virtual void beforeUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pOrderAction	��ˢ�µ�COrderAction
	virtual void afterUpdate(COrderAction *pOrderAction)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pOrderAction	Ҫɾ����COrderAction
	virtual void beforeRemove(COrderAction *pOrderAction)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	COrderActionFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///COrderActionCommitTrigger��ȷ�ϱ�������ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionCommitTrigger
{
public:
	///���췽��
	COrderActionCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~COrderActionCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(COrderActionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pOrderAction	�Ѿ������OrderAction
	virtual void commitAdd(COrderAction *pOrderAction)
	{
		return;
	}

	///���º󴥷�
	///@param	pOrderAction	��ˢ�µ�COrderAction
	///@param	poldOrderAction	ԭ����ֵ
	virtual void commitUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pOldOrderAction)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pOrderAction	�Ѿ�ɾ����COrderAction
	virtual void commitRemove(CWriteableOrderAction *pOrderAction)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	COrderActionFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///COrderActionIterator��һ���Ա���������ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionIterator
{
public:
	///���췽��
	COrderActionIterator(void)
	{
	}

	///���췽��
	COrderActionIterator(COrderActionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~COrderActionIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��OrderAction
	///@return	��һ����������COrderAction������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrderAction *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	COrderActionFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrderAction ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrderAction * pOrderAction,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	COrderActionFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableOrder��һ���洢ί�б�Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableOrder : public COrderField
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! ExchangeID.isValid())
			return 0;
		if (! OrderSysID.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! UserID.isValid())
			return 0;
		if (! InstrumentID.isValid())
			return 0;
		if (! UserOrderLocalID.isValid())
			return 0;
		if (! OrderPriceType.isValid())
			return 0;
		if (! Direction.isValid())
			return 0;
		if (! OffsetFlag.isValid())
			return 0;
		if (! HedgeFlag.isValid())
			return 0;
		if (! LimitPrice.isValid())
			return 0;
		if (! Volume.isValid())
			return 0;
		if (! TimeCondition.isValid())
			return 0;
		if (! GTDDate.isValid())
			return 0;
		if (! VolumeCondition.isValid())
			return 0;
		if (! MinVolume.isValid())
			return 0;
		if (! StopPrice.isValid())
			return 0;
		if (! ForceCloseReason.isValid())
			return 0;
		if (! IsAutoSuspend.isValid())
			return 0;
		if (! BusinessUnit.isValid())
			return 0;
		if (! UserCustom.isValid())
			return 0;
		if (! BranchID.isValid())
			return 0;
		if (! RecNum.isValid())
			return 0;
		if (! BusinessType.isValid())
			return 0;
		if (! TradingDay.isValid())
			return 0;
		if (! ParticipantID.isValid())
			return 0;
		if (! ClientID.isValid())
			return 0;
		if (! SeatID.isValid())
			return 0;
		if (! InsertTime.isValid())
			return 0;
		if (! OrderLocalID.isValid())
			return 0;
		if (! OrderSource.isValid())
			return 0;
		if (! OrderStatus.isValid())
			return 0;
		if (! CancelTime.isValid())
			return 0;
		if (! CancelUserID.isValid())
			return 0;
		if (! VolumeTraded.isValid())
			return 0;
		if (! VolumeRemain.isValid())
			return 0;
		if (! FrontID.isValid())
			return 0;
		if (! SessionID.isValid())
			return 0;
		if (! FrozenFee.isValid())
			return 0;
		if (! FrozenMargin.isValid())
			return 0;
		if (! FrozenPremium.isValid())
			return 0;
		if (! AccountID.isValid())
			return 0;
		if (! OrderUserID.isValid())
			return 0;
		if (! TradeType.isValid())
			return 0;
		if (! DealFlag.isValid())
			return 0;
		if (! TradeCommision.isValid())
			return 0;
		if (! TradeAmnt.isValid())
			return 0;
		if (! CancleVolume.isValid())
			return 0;
		if (! RequestID.isValid())
			return 0;
		if (! APIID.isValid())
			return 0;
		if (! IPAddress.isValid())
			return 0;
		if (! MacAddress.isValid())
			return 0;
		if (! FTdRecvDown.isValid())
			return 0;
		if (! CoreRecvDown.isValid())
			return 0;
		if (! CoreSendUp.isValid())
			return 0;
		if (! CoreRecvUp.isValid())
			return 0;
		if (! CoreSendDown.isValid())
			return 0;
		if (! FTdSendDown.isValid())
			return 0;
		if (! MarginCombType.isValid())
			return 0;
		if (! InstrumentGroupID.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableOrder *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	
	unsigned int HashExchangeIDOrderSysID;
	
	///����ExchangeIDOrderSysID��hashֵ
	void calHashExchangeIDOrderSysID(void)
	{
		unsigned key=0;
		key=ExchangeID.hash(key);
		key=OrderSysID.hash(key);
		HashExchangeIDOrderSysID=key;
	}
	
	///������Ҫ���������ExchangeIDOrderSysID��hashֵ
	void updateHashExchangeIDOrderSysID(void)
	{
	}
	unsigned int HashUserIDAndUserOrderLocalID;
	
	///����UserIDAndUserOrderLocalID��hashֵ
	void calHashUserIDAndUserOrderLocalID(void)
	{
		unsigned key=0;
		key=BrokerID.hash(key);
		key=UserID.hash(key);
		key=UserOrderLocalID.hash(key);
		key=FrontID.hash(key);
		key=SessionID.hash(key);
		HashUserIDAndUserOrderLocalID=key;
	}
	
	///������Ҫ���������UserIDAndUserOrderLocalID��hashֵ
	void updateHashUserIDAndUserOrderLocalID(void)
	{
	}
	
	///�������е�hashֵ
	void calAllHash(void)
	{
		calHashExchangeIDOrderSysID();
		calHashUserIDAndUserOrderLocalID();
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
		updateHashExchangeIDOrderSysID();
		updateHashUserIDAndUserOrderLocalID();
	}
	
	///�����Ӧ��Ͷ���ߵ�ָ��
	///@param	pFactory	�����Ӧ��Ͷ���ߵ�ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ��Ͷ���ߵ�ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestor *linkInvestor(CInvestorFactory *pFactory) const;

	///�����Ӧ��Ͷ����ָ��
	///@param	pInvestor	Ҫ���ӵ��Ķ���
	///@return	�����pInvestor
	const CWriteableInvestor *linkInvestor(const CWriteableInvestor *pInvestor) const
	{
		void *target=(void *)(&(this->pInvestor));
		*((const CWriteableInvestor **)target)=pInvestor;
		return pInvestor;
	}
	
	///��ȡ��Ӧ��Ͷ���ߵ�ָ��
	///@return	�ҵ��Ķ�Ӧ��Ͷ���ߵ�ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestor *getInvestor(void) const
	{
		return pInvestor;
	}
	///�����Ӧ�Ľ��ױ����ָ��
	///@param	pFactory	�����Ӧ�Ľ��ױ����ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ�Ľ��ױ����ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableClientTradingID *linkClientTradingID(CClientTradingIDFactory *pFactory) const;

	///�����Ӧ�Ľ��ױ���ָ��
	///@param	pClientTradingID	Ҫ���ӵ��Ķ���
	///@return	�����pClientTradingID
	const CWriteableClientTradingID *linkClientTradingID(const CWriteableClientTradingID *pClientTradingID) const
	{
		void *target=(void *)(&(this->pClientTradingID));
		*((const CWriteableClientTradingID **)target)=pClientTradingID;
		return pClientTradingID;
	}
	
	///��ȡ��Ӧ�Ľ��ױ����ָ��
	///@return	�ҵ��Ķ�Ӧ�Ľ��ױ����ָ�룬����Ҳ����򷵻�NULL
	const CWriteableClientTradingID *getClientTradingID(void) const
	{
		return pClientTradingID;
	}
	///�����Ӧ���ʻ���ָ��
	///@param	pFactory	�����Ӧ���ʻ���ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ���ʻ���ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorAccount *linkInvestorAccount(CInvestorAccountFactory *pFactory) const;

	///�����Ӧ���ʻ�ָ��
	///@param	pInvestorAccount	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorAccount
	const CWriteableInvestorAccount *linkInvestorAccount(const CWriteableInvestorAccount *pInvestorAccount) const
	{
		void *target=(void *)(&(this->pInvestorAccount));
		*((const CWriteableInvestorAccount **)target)=pInvestorAccount;
		return pInvestorAccount;
	}
	
	///��ȡ��Ӧ���ʻ���ָ��
	///@return	�ҵ��Ķ�Ӧ���ʻ���ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorAccount *getInvestorAccount(void) const
	{
		return pInvestorAccount;
	}
	///�����Ӧ�ĺ�Լ�ֲ���Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ�ֲ���Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ�ֲ���Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorPosition *linkInvestorPosition(CInvestorPositionFactory *pFactory) const;

	///�����Ӧ�ĺ�Լ�ֲ���Ϣָ��
	///@param	pInvestorPosition	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorPosition
	const CWriteableInvestorPosition *linkInvestorPosition(const CWriteableInvestorPosition *pInvestorPosition) const
	{
		void *target=(void *)(&(this->pInvestorPosition));
		*((const CWriteableInvestorPosition **)target)=pInvestorPosition;
		return pInvestorPosition;
	}
	
	///��ȡ��Ӧ�ĺ�Լ�ֲ���Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ�ֲ���Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorPosition *getInvestorPosition(void) const
	{
		return pInvestorPosition;
	}
	///�����Ӧ�ĺ�Լ��Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ��Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ��Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInstrument *linkInstrument(CInstrumentFactory *pFactory) const;

	///�����Ӧ�ĺ�Լ��Ϣָ��
	///@param	pInstrument	Ҫ���ӵ��Ķ���
	///@return	�����pInstrument
	const CWriteableInstrument *linkInstrument(const CWriteableInstrument *pInstrument) const
	{
		void *target=(void *)(&(this->pInstrument));
		*((const CWriteableInstrument **)target)=pInstrument;
		return pInstrument;
	}
	
	///��ȡ��Ӧ�ĺ�Լ��Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ��Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInstrument *getInstrument(void) const
	{
		return pInstrument;
	}
	///�����Ӧ��Ͷ���߱�֤������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ���߱�֤������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ��Ͷ���߱�֤������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorMargin *linkInvestorMargin(CInvestorMarginFactory *pFactory) const;

	///�����Ӧ��Ͷ���߱�֤������Ϣָ��
	///@param	pInvestorMargin	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorMargin
	const CWriteableInvestorMargin *linkInvestorMargin(const CWriteableInvestorMargin *pInvestorMargin) const
	{
		void *target=(void *)(&(this->pInvestorMargin));
		*((const CWriteableInvestorMargin **)target)=pInvestorMargin;
		return pInvestorMargin;
	}
	
	///��ȡ��Ӧ��Ͷ���߱�֤������Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ��Ͷ���߱�֤������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorMargin *getInvestorMargin(void) const
	{
		return pInvestorMargin;
	}
	///�����Ӧ��Ͷ��������������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ��������������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ��Ͷ��������������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorFee *linkInvestorFee(CInvestorFeeFactory *pFactory) const;

	///�����Ӧ��Ͷ��������������Ϣָ��
	///@param	pInvestorFee	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorFee
	const CWriteableInvestorFee *linkInvestorFee(const CWriteableInvestorFee *pInvestorFee) const
	{
		void *target=(void *)(&(this->pInvestorFee));
		*((const CWriteableInvestorFee **)target)=pInvestorFee;
		return pInvestorFee;
	}
	
	///��ȡ��Ӧ��Ͷ��������������Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ��Ͷ��������������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorFee *getInvestorFee(void) const
	{
		return pInvestorFee;
	}
	///�����Ӧ��Ͷ������Ȩ����������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ������Ȩ����������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ��Ͷ������Ȩ����������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorOptionFee *linkInvestorOptionFee(CInvestorOptionFeeFactory *pFactory) const;

	///�����Ӧ��Ͷ������Ȩ����������Ϣָ��
	///@param	pInvestorOptionFee	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorOptionFee
	const CWriteableInvestorOptionFee *linkInvestorOptionFee(const CWriteableInvestorOptionFee *pInvestorOptionFee) const
	{
		void *target=(void *)(&(this->pInvestorOptionFee));
		*((const CWriteableInvestorOptionFee **)target)=pInvestorOptionFee;
		return pInvestorOptionFee;
	}
	
	///��ȡ��Ӧ��Ͷ������Ȩ����������Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ��Ͷ������Ȩ����������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorOptionFee *getInvestorOptionFee(void) const
	{
		return pInvestorOptionFee;
	}
	///�����Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteablePartClientInsGroupPosition *linkClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory) const;

	///�����Ӧ�ĺ�Լ�����ֲ���Ϣָ��
	///@param	pPartClientInsGroupPosition	Ҫ���ӵ��Ķ���
	///@return	�����pPartClientInsGroupPosition
	const CWriteablePartClientInsGroupPosition *linkClientGroupPosition(const CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition) const
	{
		void *target=(void *)(&(this->pClientGroupPosition));
		*((const CWriteablePartClientInsGroupPosition **)target)=pPartClientInsGroupPosition;
		return pPartClientInsGroupPosition;
	}
	
	///��ȡ��Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteablePartClientInsGroupPosition *getClientGroupPosition(void) const
	{
		return pClientGroupPosition;
	}

private:
	///��Ӧ��Ͷ����
	const CWriteableInvestor *pInvestor;
	///��Ӧ�Ľ��ױ���
	const CWriteableClientTradingID *pClientTradingID;
	///��Ӧ���ʻ�
	const CWriteableInvestorAccount *pInvestorAccount;
	///��Ӧ�ĺ�Լ�ֲ���Ϣ
	const CWriteableInvestorPosition *pInvestorPosition;
	///��Ӧ�ĺ�Լ��Ϣ
	const CWriteableInstrument *pInstrument;
	///��Ӧ��Ͷ���߱�֤������Ϣ
	const CWriteableInvestorMargin *pInvestorMargin;
	///��Ӧ��Ͷ��������������Ϣ
	const CWriteableInvestorFee *pInvestorFee;
	///��Ӧ��Ͷ������Ȩ����������Ϣ
	const CWriteableInvestorOptionFee *pInvestorOptionFee;
	///��Ӧ�ĺ�Լ�����ֲ���Ϣ
	const CWriteablePartClientInsGroupPosition *pClientGroupPosition;
};

typedef const CWriteableOrder COrder;

/////////////////////////////////////////////////////////////////////////
///COrderActionTrigger�ǲ���ί�б�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionTrigger
{
public:
	///���췽��
	COrderActionTrigger(void)
	{
	}
	
	///��������
	virtual ~COrderActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(COrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pOrder	Ҫ�����Order
	virtual void beforeAdd(CWriteableOrder *pOrder)
	{
		return;
	}
	
	///����󴥷�
	///@param	pOrder	�Ѿ������Order
	virtual void afterAdd(COrder *pOrder)
	{
		return;
	}

	///����ǰ����	
	///@param	pOrder	��ˢ�µ�COrder
	///@param	pNewOrder	�µ�ֵ
	virtual void beforeUpdate(COrder *pOrder, CWriteableOrder *pNewOrder)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pOrder	��ˢ�µ�COrder
	virtual void afterUpdate(COrder *pOrder)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pOrder	Ҫɾ����COrder
	virtual void beforeRemove(COrder *pOrder)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	COrderFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///COrderCommitTrigger��ȷ��ί�б�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderCommitTrigger
{
public:
	///���췽��
	COrderCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~COrderCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(COrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pOrder	�Ѿ������Order
	virtual void commitAdd(COrder *pOrder)
	{
		return;
	}

	///���º󴥷�
	///@param	pOrder	��ˢ�µ�COrder
	///@param	poldOrder	ԭ����ֵ
	virtual void commitUpdate(COrder *pOrder, CWriteableOrder *pOldOrder)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pOrder	�Ѿ�ɾ����COrder
	virtual void commitRemove(CWriteableOrder *pOrder)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	COrderFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///COrderIterator��һ����ί�б��ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderIterator
{
public:
	///���췽��
	COrderIterator(void)
	{
	}

	///���췽��
	COrderIterator(COrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~COrderIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��Order
	///@return	��һ����������COrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrder *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	COrderFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrder ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrder * pOrder,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	COrderFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableTrade��һ���洢�ɽ���Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableTrade : public CTradeField
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! TradingDay.isValid())
			return 0;
		if (! BrokerID.isValid())
			return 0;
		if (! ExchangeID.isValid())
			return 0;
		if (! ParticipantID.isValid())
			return 0;
		if (! SeatID.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! ClientID.isValid())
			return 0;
		if (! UserID.isValid())
			return 0;
		if (! TradeID.isValid())
			return 0;
		if (! OrderSysID.isValid())
			return 0;
		if (! UserOrderLocalID.isValid())
			return 0;
		if (! InstrumentID.isValid())
			return 0;
		if (! Direction.isValid())
			return 0;
		if (! OffsetFlag.isValid())
			return 0;
		if (! HedgeFlag.isValid())
			return 0;
		if (! TradePrice.isValid())
			return 0;
		if (! TradeVolume.isValid())
			return 0;
		if (! TradeTime.isValid())
			return 0;
		if (! ClearingPartID.isValid())
			return 0;
		if (! TradeAmnt.isValid())
			return 0;
		if (! RecNum.isValid())
			return 0;
		if (! TradeType.isValid())
			return 0;
		if (! Commision.isValid())
			return 0;
		if (! StampTax.isValid())
			return 0;
		if (! TransferFee.isValid())
			return 0;
		if (! UsedFee.isValid())
			return 0;
		if (! UsedMargin.isValid())
			return 0;
		if (! Premium.isValid())
			return 0;
		if (! AccountID.isValid())
			return 0;
		if (! OrderUserID.isValid())
			return 0;
		if (! OrderLocalID.isValid())
			return 0;
		if (! IsForgeRtn.isValid())
			return 0;
		if (! BusinessType.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableTrade *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableTrade CTrade;

/////////////////////////////////////////////////////////////////////////
///CTradeActionTrigger�ǲ����ɽ���ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeActionTrigger
{
public:
	///���췽��
	CTradeActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CTradeActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CTradeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pTrade	Ҫ�����Trade
	virtual void beforeAdd(CWriteableTrade *pTrade)
	{
		return;
	}
	
	///����󴥷�
	///@param	pTrade	�Ѿ������Trade
	virtual void afterAdd(CTrade *pTrade)
	{
		return;
	}

	///����ǰ����	
	///@param	pTrade	��ˢ�µ�CTrade
	///@param	pNewTrade	�µ�ֵ
	virtual void beforeUpdate(CTrade *pTrade, CWriteableTrade *pNewTrade)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pTrade	��ˢ�µ�CTrade
	virtual void afterUpdate(CTrade *pTrade)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pTrade	Ҫɾ����CTrade
	virtual void beforeRemove(CTrade *pTrade)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CTradeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CTradeCommitTrigger��ȷ�ϳɽ���ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeCommitTrigger
{
public:
	///���췽��
	CTradeCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CTradeCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CTradeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pTrade	�Ѿ������Trade
	virtual void commitAdd(CTrade *pTrade)
	{
		return;
	}

	///���º󴥷�
	///@param	pTrade	��ˢ�µ�CTrade
	///@param	poldTrade	ԭ����ֵ
	virtual void commitUpdate(CTrade *pTrade, CWriteableTrade *pOldTrade)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pTrade	�Ѿ�ɾ����CTrade
	virtual void commitRemove(CWriteableTrade *pTrade)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CTradeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CTradeIterator��һ���Գɽ����ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeIterator
{
public:
	///���췽��
	CTradeIterator(void)
	{
	}

	///���췽��
	CTradeIterator(CTradeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CTradeIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��Trade
	///@return	��һ����������CTrade������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CTrade *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CTradeFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pTrade ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableTrade * pTrade,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CTradeFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteablePreOrder��һ���洢Ԥί�б�Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteablePreOrder : public CInputOrderField
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! ExchangeID.isValid())
			return 0;
		if (! OrderSysID.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! UserID.isValid())
			return 0;
		if (! InstrumentID.isValid())
			return 0;
		if (! UserOrderLocalID.isValid())
			return 0;
		if (! OrderPriceType.isValid())
			return 0;
		if (! Direction.isValid())
			return 0;
		if (! OffsetFlag.isValid())
			return 0;
		if (! HedgeFlag.isValid())
			return 0;
		if (! LimitPrice.isValid())
			return 0;
		if (! Volume.isValid())
			return 0;
		if (! TimeCondition.isValid())
			return 0;
		if (! GTDDate.isValid())
			return 0;
		if (! VolumeCondition.isValid())
			return 0;
		if (! MinVolume.isValid())
			return 0;
		if (! StopPrice.isValid())
			return 0;
		if (! ForceCloseReason.isValid())
			return 0;
		if (! IsAutoSuspend.isValid())
			return 0;
		if (! BusinessUnit.isValid())
			return 0;
		if (! UserCustom.isValid())
			return 0;
		if (! BranchID.isValid())
			return 0;
		if (! RecNum.isValid())
			return 0;
		if (! BusinessType.isValid())
			return 0;
		if (! TradingDay.isValid())
			return 0;
		if (! ParticipantID.isValid())
			return 0;
		if (! ClientID.isValid())
			return 0;
		if (! SeatID.isValid())
			return 0;
		if (! InsertTime.isValid())
			return 0;
		if (! OrderLocalID.isValid())
			return 0;
		if (! OrderSource.isValid())
			return 0;
		if (! OrderStatus.isValid())
			return 0;
		if (! CancelTime.isValid())
			return 0;
		if (! CancelUserID.isValid())
			return 0;
		if (! VolumeTraded.isValid())
			return 0;
		if (! VolumeRemain.isValid())
			return 0;
		if (! FrontID.isValid())
			return 0;
		if (! SessionID.isValid())
			return 0;
		if (! FrozenFee.isValid())
			return 0;
		if (! FrozenMargin.isValid())
			return 0;
		if (! FrozenPremium.isValid())
			return 0;
		if (! AccountID.isValid())
			return 0;
		if (! OrderUserID.isValid())
			return 0;
		if (! TradeType.isValid())
			return 0;
		if (! DealFlag.isValid())
			return 0;
		if (! TradeCommision.isValid())
			return 0;
		if (! TradeAmnt.isValid())
			return 0;
		if (! CancleVolume.isValid())
			return 0;
		if (! RequestID.isValid())
			return 0;
		if (! APIID.isValid())
			return 0;
		if (! IPAddress.isValid())
			return 0;
		if (! MacAddress.isValid())
			return 0;
		if (! FTdRecvDown.isValid())
			return 0;
		if (! CoreRecvDown.isValid())
			return 0;
		if (! CoreSendUp.isValid())
			return 0;
		if (! CoreRecvUp.isValid())
			return 0;
		if (! CoreSendDown.isValid())
			return 0;
		if (! FTdSendDown.isValid())
			return 0;
		if (! MarginCombType.isValid())
			return 0;
		if (! InstrumentGroupID.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteablePreOrder *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	
	unsigned int HashUserIDAndUserOrderLocalID;
	
	///����UserIDAndUserOrderLocalID��hashֵ
	void calHashUserIDAndUserOrderLocalID(void)
	{
		unsigned key=0;
		key=BrokerID.hash(key);
		key=UserID.hash(key);
		key=UserOrderLocalID.hash(key);
		key=FrontID.hash(key);
		key=SessionID.hash(key);
		HashUserIDAndUserOrderLocalID=key;
	}
	
	///������Ҫ���������UserIDAndUserOrderLocalID��hashֵ
	void updateHashUserIDAndUserOrderLocalID(void)
	{
	}
	
	///�������е�hashֵ
	void calAllHash(void)
	{
		calHashUserIDAndUserOrderLocalID();
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
		updateHashUserIDAndUserOrderLocalID();
	}
	
	///�����Ӧ��Ͷ���ߵ�ָ��
	///@param	pFactory	�����Ӧ��Ͷ���ߵ�ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ��Ͷ���ߵ�ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestor *linkInvestor(CInvestorFactory *pFactory) const;

	///�����Ӧ��Ͷ����ָ��
	///@param	pInvestor	Ҫ���ӵ��Ķ���
	///@return	�����pInvestor
	const CWriteableInvestor *linkInvestor(const CWriteableInvestor *pInvestor) const
	{
		void *target=(void *)(&(this->pInvestor));
		*((const CWriteableInvestor **)target)=pInvestor;
		return pInvestor;
	}
	
	///��ȡ��Ӧ��Ͷ���ߵ�ָ��
	///@return	�ҵ��Ķ�Ӧ��Ͷ���ߵ�ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestor *getInvestor(void) const
	{
		return pInvestor;
	}
	///�����Ӧ�Ľ��ױ����ָ��
	///@param	pFactory	�����Ӧ�Ľ��ױ����ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ�Ľ��ױ����ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableClientTradingID *linkClientTradingID(CClientTradingIDFactory *pFactory) const;

	///�����Ӧ�Ľ��ױ���ָ��
	///@param	pClientTradingID	Ҫ���ӵ��Ķ���
	///@return	�����pClientTradingID
	const CWriteableClientTradingID *linkClientTradingID(const CWriteableClientTradingID *pClientTradingID) const
	{
		void *target=(void *)(&(this->pClientTradingID));
		*((const CWriteableClientTradingID **)target)=pClientTradingID;
		return pClientTradingID;
	}
	
	///��ȡ��Ӧ�Ľ��ױ����ָ��
	///@return	�ҵ��Ķ�Ӧ�Ľ��ױ����ָ�룬����Ҳ����򷵻�NULL
	const CWriteableClientTradingID *getClientTradingID(void) const
	{
		return pClientTradingID;
	}
	///�����Ӧ���ʻ���ָ��
	///@param	pFactory	�����Ӧ���ʻ���ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ���ʻ���ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorAccount *linkInvestorAccount(CInvestorAccountFactory *pFactory) const;

	///�����Ӧ���ʻ�ָ��
	///@param	pInvestorAccount	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorAccount
	const CWriteableInvestorAccount *linkInvestorAccount(const CWriteableInvestorAccount *pInvestorAccount) const
	{
		void *target=(void *)(&(this->pInvestorAccount));
		*((const CWriteableInvestorAccount **)target)=pInvestorAccount;
		return pInvestorAccount;
	}
	
	///��ȡ��Ӧ���ʻ���ָ��
	///@return	�ҵ��Ķ�Ӧ���ʻ���ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorAccount *getInvestorAccount(void) const
	{
		return pInvestorAccount;
	}
	///�����Ӧ�ĺ�Լ�ֲ���Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ�ֲ���Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ�ֲ���Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorPosition *linkInvestorPosition(CInvestorPositionFactory *pFactory) const;

	///�����Ӧ�ĺ�Լ�ֲ���Ϣָ��
	///@param	pInvestorPosition	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorPosition
	const CWriteableInvestorPosition *linkInvestorPosition(const CWriteableInvestorPosition *pInvestorPosition) const
	{
		void *target=(void *)(&(this->pInvestorPosition));
		*((const CWriteableInvestorPosition **)target)=pInvestorPosition;
		return pInvestorPosition;
	}
	
	///��ȡ��Ӧ�ĺ�Լ�ֲ���Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ�ֲ���Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorPosition *getInvestorPosition(void) const
	{
		return pInvestorPosition;
	}
	///�����Ӧ�ĺ�Լ��Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ��Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ��Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInstrument *linkInstrument(CInstrumentFactory *pFactory) const;

	///�����Ӧ�ĺ�Լ��Ϣָ��
	///@param	pInstrument	Ҫ���ӵ��Ķ���
	///@return	�����pInstrument
	const CWriteableInstrument *linkInstrument(const CWriteableInstrument *pInstrument) const
	{
		void *target=(void *)(&(this->pInstrument));
		*((const CWriteableInstrument **)target)=pInstrument;
		return pInstrument;
	}
	
	///��ȡ��Ӧ�ĺ�Լ��Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ��Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInstrument *getInstrument(void) const
	{
		return pInstrument;
	}
	///�����Ӧ��Ͷ���߱�֤������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ���߱�֤������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ��Ͷ���߱�֤������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorMargin *linkInvestorMargin(CInvestorMarginFactory *pFactory) const;

	///�����Ӧ��Ͷ���߱�֤������Ϣָ��
	///@param	pInvestorMargin	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorMargin
	const CWriteableInvestorMargin *linkInvestorMargin(const CWriteableInvestorMargin *pInvestorMargin) const
	{
		void *target=(void *)(&(this->pInvestorMargin));
		*((const CWriteableInvestorMargin **)target)=pInvestorMargin;
		return pInvestorMargin;
	}
	
	///��ȡ��Ӧ��Ͷ���߱�֤������Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ��Ͷ���߱�֤������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorMargin *getInvestorMargin(void) const
	{
		return pInvestorMargin;
	}
	///�����Ӧ��Ͷ��������������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ��������������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ��Ͷ��������������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorFee *linkInvestorFee(CInvestorFeeFactory *pFactory) const;

	///�����Ӧ��Ͷ��������������Ϣָ��
	///@param	pInvestorFee	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorFee
	const CWriteableInvestorFee *linkInvestorFee(const CWriteableInvestorFee *pInvestorFee) const
	{
		void *target=(void *)(&(this->pInvestorFee));
		*((const CWriteableInvestorFee **)target)=pInvestorFee;
		return pInvestorFee;
	}
	
	///��ȡ��Ӧ��Ͷ��������������Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ��Ͷ��������������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorFee *getInvestorFee(void) const
	{
		return pInvestorFee;
	}
	///�����Ӧ��Ͷ������Ȩ����������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ������Ȩ����������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ��Ͷ������Ȩ����������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorOptionFee *linkInvestorOptionFee(CInvestorOptionFeeFactory *pFactory) const;

	///�����Ӧ��Ͷ������Ȩ����������Ϣָ��
	///@param	pInvestorOptionFee	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorOptionFee
	const CWriteableInvestorOptionFee *linkInvestorOptionFee(const CWriteableInvestorOptionFee *pInvestorOptionFee) const
	{
		void *target=(void *)(&(this->pInvestorOptionFee));
		*((const CWriteableInvestorOptionFee **)target)=pInvestorOptionFee;
		return pInvestorOptionFee;
	}
	
	///��ȡ��Ӧ��Ͷ������Ȩ����������Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ��Ͷ������Ȩ����������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorOptionFee *getInvestorOptionFee(void) const
	{
		return pInvestorOptionFee;
	}
	///�����Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteablePartClientInsGroupPosition *linkClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory) const;

	///�����Ӧ�ĺ�Լ�����ֲ���Ϣָ��
	///@param	pPartClientInsGroupPosition	Ҫ���ӵ��Ķ���
	///@return	�����pPartClientInsGroupPosition
	const CWriteablePartClientInsGroupPosition *linkClientGroupPosition(const CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition) const
	{
		void *target=(void *)(&(this->pClientGroupPosition));
		*((const CWriteablePartClientInsGroupPosition **)target)=pPartClientInsGroupPosition;
		return pPartClientInsGroupPosition;
	}
	
	///��ȡ��Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteablePartClientInsGroupPosition *getClientGroupPosition(void) const
	{
		return pClientGroupPosition;
	}

private:
	///��Ӧ��Ͷ����
	const CWriteableInvestor *pInvestor;
	///��Ӧ�Ľ��ױ���
	const CWriteableClientTradingID *pClientTradingID;
	///��Ӧ���ʻ�
	const CWriteableInvestorAccount *pInvestorAccount;
	///��Ӧ�ĺ�Լ�ֲ���Ϣ
	const CWriteableInvestorPosition *pInvestorPosition;
	///��Ӧ�ĺ�Լ��Ϣ
	const CWriteableInstrument *pInstrument;
	///��Ӧ��Ͷ���߱�֤������Ϣ
	const CWriteableInvestorMargin *pInvestorMargin;
	///��Ӧ��Ͷ��������������Ϣ
	const CWriteableInvestorFee *pInvestorFee;
	///��Ӧ��Ͷ������Ȩ����������Ϣ
	const CWriteableInvestorOptionFee *pInvestorOptionFee;
	///��Ӧ�ĺ�Լ�����ֲ���Ϣ
	const CWriteablePartClientInsGroupPosition *pClientGroupPosition;
};

typedef const CWriteablePreOrder CPreOrder;

/////////////////////////////////////////////////////////////////////////
///CPreOrderActionTrigger�ǲ���Ԥί�б�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderActionTrigger
{
public:
	///���췽��
	CPreOrderActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CPreOrderActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CPreOrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pPreOrder	Ҫ�����PreOrder
	virtual void beforeAdd(CWriteablePreOrder *pPreOrder)
	{
		return;
	}
	
	///����󴥷�
	///@param	pPreOrder	�Ѿ������PreOrder
	virtual void afterAdd(CPreOrder *pPreOrder)
	{
		return;
	}

	///����ǰ����	
	///@param	pPreOrder	��ˢ�µ�CPreOrder
	///@param	pNewPreOrder	�µ�ֵ
	virtual void beforeUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pPreOrder	��ˢ�µ�CPreOrder
	virtual void afterUpdate(CPreOrder *pPreOrder)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pPreOrder	Ҫɾ����CPreOrder
	virtual void beforeRemove(CPreOrder *pPreOrder)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CPreOrderFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderCommitTrigger��ȷ��Ԥί�б�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderCommitTrigger
{
public:
	///���췽��
	CPreOrderCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CPreOrderCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CPreOrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pPreOrder	�Ѿ������PreOrder
	virtual void commitAdd(CPreOrder *pPreOrder)
	{
		return;
	}

	///���º󴥷�
	///@param	pPreOrder	��ˢ�µ�CPreOrder
	///@param	poldPreOrder	ԭ����ֵ
	virtual void commitUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pOldPreOrder)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pPreOrder	�Ѿ�ɾ����CPreOrder
	virtual void commitRemove(CWriteablePreOrder *pPreOrder)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CPreOrderFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderIterator��һ����Ԥί�б��ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderIterator
{
public:
	///���췽��
	CPreOrderIterator(void)
	{
	}

	///���췽��
	CPreOrderIterator(CPreOrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CPreOrderIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��PreOrder
	///@return	��һ����������CPreOrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CPreOrder *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CPreOrderFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pPreOrder ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteablePreOrder * pPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CPreOrderFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableIndexPreOrder��һ���洢����Ԥί�б�Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableIndexPreOrder
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! ExchangeID.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! InstrumentID.isValid())
			return 0;
		if (! HedgeFlag.isValid())
			return 0;
		if (! Direction.isValid())
			return 0;
		if (! APIID.isValid())
			return 0;
		if (! ClientID.isValid())
			return 0;
		if (! MarginCombType.isValid())
			return 0;
		if (! InstrumentGroupID.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableIndexPreOrder *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///����������
	CExchangeIDType ExchangeID;
	///Ͷ���߱��
	CInvestorIDType InvestorID;
	///��Լ����
	CInstrumentIDType InstrumentID;
	///Ͷ���ױ���־
	CHedgeFlagType HedgeFlag;
	///��������
	CDirectionType Direction;
	///ͨ����Ӧ��APIID
	CNumberType APIID;
	///���ױ���
	CClientIDType ClientID;
	///��֤���������
	CClientMarginCombTypeType MarginCombType;
	///��Լ�����
	CInstrumentGroupIDType InstrumentGroupID;
	
	unsigned int HashALLFlds;
	
	///����ALLFlds��hashֵ
	void calHashALLFlds(void)
	{
		unsigned key=0;
		key=ExchangeID.hash(key);
		key=InvestorID.hash(key);
		key=InstrumentID.hash(key);
		key=HedgeFlag.hash(key);
		HashALLFlds=key;
	}
	
	///������Ҫ���������ALLFlds��hashֵ
	void updateHashALLFlds(void)
	{
	}
	
	///�������е�hashֵ
	void calAllHash(void)
	{
		calHashALLFlds();
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
		updateHashALLFlds();
	}
	
	///�����Ӧ��Ͷ���ߵ�ָ��
	///@param	pFactory	�����Ӧ��Ͷ���ߵ�ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ��Ͷ���ߵ�ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestor *linkInvestor(CInvestorFactory *pFactory) const;

	///�����Ӧ��Ͷ����ָ��
	///@param	pInvestor	Ҫ���ӵ��Ķ���
	///@return	�����pInvestor
	const CWriteableInvestor *linkInvestor(const CWriteableInvestor *pInvestor) const
	{
		void *target=(void *)(&(this->pInvestor));
		*((const CWriteableInvestor **)target)=pInvestor;
		return pInvestor;
	}
	
	///��ȡ��Ӧ��Ͷ���ߵ�ָ��
	///@return	�ҵ��Ķ�Ӧ��Ͷ���ߵ�ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestor *getInvestor(void) const
	{
		return pInvestor;
	}
	///�����Ӧ�Ľ��ױ����ָ��
	///@param	pFactory	�����Ӧ�Ľ��ױ����ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ�Ľ��ױ����ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableClientTradingID *linkClientTradingID(CClientTradingIDFactory *pFactory) const;

	///�����Ӧ�Ľ��ױ���ָ��
	///@param	pClientTradingID	Ҫ���ӵ��Ķ���
	///@return	�����pClientTradingID
	const CWriteableClientTradingID *linkClientTradingID(const CWriteableClientTradingID *pClientTradingID) const
	{
		void *target=(void *)(&(this->pClientTradingID));
		*((const CWriteableClientTradingID **)target)=pClientTradingID;
		return pClientTradingID;
	}
	
	///��ȡ��Ӧ�Ľ��ױ����ָ��
	///@return	�ҵ��Ķ�Ӧ�Ľ��ױ����ָ�룬����Ҳ����򷵻�NULL
	const CWriteableClientTradingID *getClientTradingID(void) const
	{
		return pClientTradingID;
	}
	///�����Ӧ���ʻ���ָ��
	///@param	pFactory	�����Ӧ���ʻ���ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ���ʻ���ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorAccount *linkInvestorAccount(CInvestorAccountFactory *pFactory) const;

	///�����Ӧ���ʻ�ָ��
	///@param	pInvestorAccount	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorAccount
	const CWriteableInvestorAccount *linkInvestorAccount(const CWriteableInvestorAccount *pInvestorAccount) const
	{
		void *target=(void *)(&(this->pInvestorAccount));
		*((const CWriteableInvestorAccount **)target)=pInvestorAccount;
		return pInvestorAccount;
	}
	
	///��ȡ��Ӧ���ʻ���ָ��
	///@return	�ҵ��Ķ�Ӧ���ʻ���ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorAccount *getInvestorAccount(void) const
	{
		return pInvestorAccount;
	}
	///�����Ӧ�ĺ�Լ��Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ��Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ��Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInstrument *linkInstrument(CInstrumentFactory *pFactory) const;

	///�����Ӧ�ĺ�Լ��Ϣָ��
	///@param	pInstrument	Ҫ���ӵ��Ķ���
	///@return	�����pInstrument
	const CWriteableInstrument *linkInstrument(const CWriteableInstrument *pInstrument) const
	{
		void *target=(void *)(&(this->pInstrument));
		*((const CWriteableInstrument **)target)=pInstrument;
		return pInstrument;
	}
	
	///��ȡ��Ӧ�ĺ�Լ��Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ��Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInstrument *getInstrument(void) const
	{
		return pInstrument;
	}
	///�����Ӧ��Ͷ���߱�֤������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ���߱�֤������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ��Ͷ���߱�֤������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorMargin *linkInvestorMargin(CInvestorMarginFactory *pFactory) const;

	///�����Ӧ��Ͷ���߱�֤������Ϣָ��
	///@param	pInvestorMargin	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorMargin
	const CWriteableInvestorMargin *linkInvestorMargin(const CWriteableInvestorMargin *pInvestorMargin) const
	{
		void *target=(void *)(&(this->pInvestorMargin));
		*((const CWriteableInvestorMargin **)target)=pInvestorMargin;
		return pInvestorMargin;
	}
	
	///��ȡ��Ӧ��Ͷ���߱�֤������Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ��Ͷ���߱�֤������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorMargin *getInvestorMargin(void) const
	{
		return pInvestorMargin;
	}
	///�����Ӧ��Ͷ��������������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ��������������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ��Ͷ��������������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorFee *linkInvestorFee(CInvestorFeeFactory *pFactory) const;

	///�����Ӧ��Ͷ��������������Ϣָ��
	///@param	pInvestorFee	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorFee
	const CWriteableInvestorFee *linkInvestorFee(const CWriteableInvestorFee *pInvestorFee) const
	{
		void *target=(void *)(&(this->pInvestorFee));
		*((const CWriteableInvestorFee **)target)=pInvestorFee;
		return pInvestorFee;
	}
	
	///��ȡ��Ӧ��Ͷ��������������Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ��Ͷ��������������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorFee *getInvestorFee(void) const
	{
		return pInvestorFee;
	}
	///�����Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteablePartClientInsGroupPosition *linkClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory) const;

	///�����Ӧ�ĺ�Լ�����ֲ���Ϣָ��
	///@param	pPartClientInsGroupPosition	Ҫ���ӵ��Ķ���
	///@return	�����pPartClientInsGroupPosition
	const CWriteablePartClientInsGroupPosition *linkClientGroupPosition(const CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition) const
	{
		void *target=(void *)(&(this->pClientGroupPosition));
		*((const CWriteablePartClientInsGroupPosition **)target)=pPartClientInsGroupPosition;
		return pPartClientInsGroupPosition;
	}
	
	///��ȡ��Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ�����ֲ���Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteablePartClientInsGroupPosition *getClientGroupPosition(void) const
	{
		return pClientGroupPosition;
	}

private:
	///��Ӧ��Ͷ����
	const CWriteableInvestor *pInvestor;
	///��Ӧ�Ľ��ױ���
	const CWriteableClientTradingID *pClientTradingID;
	///��Ӧ���ʻ�
	const CWriteableInvestorAccount *pInvestorAccount;
	///��Ӧ�ĺ�Լ��Ϣ
	const CWriteableInstrument *pInstrument;
	///��Ӧ��Ͷ���߱�֤������Ϣ
	const CWriteableInvestorMargin *pInvestorMargin;
	///��Ӧ��Ͷ��������������Ϣ
	const CWriteableInvestorFee *pInvestorFee;
	///��Ӧ�ĺ�Լ�����ֲ���Ϣ
	const CWriteablePartClientInsGroupPosition *pClientGroupPosition;
};

typedef const CWriteableIndexPreOrder CIndexPreOrder;

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderActionTrigger�ǲ�������Ԥί�б�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderActionTrigger
{
public:
	///���췽��
	CIndexPreOrderActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CIndexPreOrderActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CIndexPreOrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pIndexPreOrder	Ҫ�����IndexPreOrder
	virtual void beforeAdd(CWriteableIndexPreOrder *pIndexPreOrder)
	{
		return;
	}
	
	///����󴥷�
	///@param	pIndexPreOrder	�Ѿ������IndexPreOrder
	virtual void afterAdd(CIndexPreOrder *pIndexPreOrder)
	{
		return;
	}

	///����ǰ����	
	///@param	pIndexPreOrder	��ˢ�µ�CIndexPreOrder
	///@param	pNewIndexPreOrder	�µ�ֵ
	virtual void beforeUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pIndexPreOrder	��ˢ�µ�CIndexPreOrder
	virtual void afterUpdate(CIndexPreOrder *pIndexPreOrder)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pIndexPreOrder	Ҫɾ����CIndexPreOrder
	virtual void beforeRemove(CIndexPreOrder *pIndexPreOrder)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CIndexPreOrderFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderCommitTrigger��ȷ������Ԥί�б�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderCommitTrigger
{
public:
	///���췽��
	CIndexPreOrderCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CIndexPreOrderCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CIndexPreOrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pIndexPreOrder	�Ѿ������IndexPreOrder
	virtual void commitAdd(CIndexPreOrder *pIndexPreOrder)
	{
		return;
	}

	///���º󴥷�
	///@param	pIndexPreOrder	��ˢ�µ�CIndexPreOrder
	///@param	poldIndexPreOrder	ԭ����ֵ
	virtual void commitUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pOldIndexPreOrder)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pIndexPreOrder	�Ѿ�ɾ����CIndexPreOrder
	virtual void commitRemove(CWriteableIndexPreOrder *pIndexPreOrder)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CIndexPreOrderFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderIterator��һ��������Ԥί�б��ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderIterator
{
public:
	///���췽��
	CIndexPreOrderIterator(void)
	{
	}

	///���췽��
	CIndexPreOrderIterator(CIndexPreOrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CIndexPreOrderIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��IndexPreOrder
	///@return	��һ����������CIndexPreOrder������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CIndexPreOrder *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CIndexPreOrderFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pIndexPreOrder ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableIndexPreOrder * pIndexPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CIndexPreOrderFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInvestorPosition��һ���洢�ֱֲ�Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInvestorPosition
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! ExchangeID.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! ParticipantID.isValid())
			return 0;
		if (! ClientID.isValid())
			return 0;
		if (! InstrumentID.isValid())
			return 0;
		if (! Direction.isValid())
			return 0;
		if (! HedgeFlag.isValid())
			return 0;
		if (! UsedMargin.isValid())
			return 0;
		if (! Position.isValid())
			return 0;
		if (! PositionCost.isValid())
			return 0;
		if (! YdPosition.isValid())
			return 0;
		if (! YdPositionCost.isValid())
			return 0;
		if (! FrozenMargin.isValid())
			return 0;
		if (! FrozenPosition.isValid())
			return 0;
		if (! FrozenClosing.isValid())
			return 0;
		if (! FrozenPremium.isValid())
			return 0;
		if (! LastTradeID.isValid())
			return 0;
		if (! LastOrderLocalID.isValid())
			return 0;
		if (! Currency.isValid())
			return 0;
		if (! PositionProfit.isValid())
			return 0;
		if (! TodayPosition.isValid())
			return 0;
		if (! FrozenTodayClosing.isValid())
			return 0;
		if (! TradeType.isValid())
			return 0;
		if (! AccountID.isValid())
			return 0;
		if (! LastPrice.isValid())
			return 0;
		if (! PositionClose.isValid())
			return 0;
		if (! YdPositionClose.isValid())
			return 0;
		if (! YdFrozenClosing.isValid())
			return 0;
		if (! CacalProfitPosition.isValid())
			return 0;
		if (! OptionType.isValid())
			return 0;
		if (! StrikePrice.isValid())
			return 0;
		if (! OptionInstrumentID.isValid())
			return 0;
		if (! TodayPositionCost.isValid())
			return 0;
		if (! ShortPosition.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableInvestorPosition *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///����������
	CExchangeIDType ExchangeID;
	///Ͷ���߱��
	CInvestorIDType InvestorID;
	///��Ա���
	CParticipantIDType ParticipantID;
	///�ͻ�����
	CClientIDType ClientID;
	///��Լ����
	CInstrumentIDType InstrumentID;
	///��������
	CDirectionType Direction;
	///Ͷ���ױ���־
	CHedgeFlagType HedgeFlag;
	///ռ�ñ�֤��
	CMoneyType UsedMargin;
	///�ֲܳ���
	CVolumeType Position;
	///���ճֲֳɱ�
	CPriceType PositionCost;
	///��ֲ���(����ֵ)
	CVolumeType YdPosition;
	///���ճֲֳɱ�
	CMoneyType YdPositionCost;
	///����ı�֤��
	CMoneyType FrozenMargin;
	///���ֶ���ֲ�
	CVolumeType FrozenPosition;
	///ƽ�ֶ���ֲ�
	CVolumeType FrozenClosing;
	///�����Ȩ����
	CMoneyType FrozenPremium;
	///���һ�ʳɽ����
	CTradeIDType LastTradeID;
	///���һ�ʱ��ر������
	COrderLocalIDType LastOrderLocalID;
	///����
	CCurrencyIDType Currency;
	///�ֲ�ӯ��
	CMoneyType PositionProfit;
	///��ֲ���
	CVolumeType TodayPosition;
	///���ƽ�ֶ���
	CVolumeType FrozenTodayClosing;
	///�ɽ�����
	CTradeTypeType TradeType;
	///�ʽ��ʺ�
	CAccountIDType AccountID;
	///���㸡��ӯ�����¼�
	CPriceType LastPrice;
	///�ֲֿܳ�ƽ������(����ƽ�ֶ���ֲ�)
	CVolumeType PositionClose;
	///��ֲֿ�ƽ������(����ƽ�ֶ���ֲ�)
	CVolumeType YdPositionClose;
	///��ֲ�ƽ�ֶ���ֲ�
	CVolumeType YdFrozenClosing;
	///���㸡��ӯ��ʱ���ֲܳ�
	CVolumeType CacalProfitPosition;
	///��Ȩ����
	COptionsTypeType OptionType;
	///��Ȩ��
	CPriceType StrikePrice;
	///��Ȩ��Ӧ�ı�ĺ�Լ����
	CInstrumentIDType OptionInstrumentID;
	///��ֲֳֳɱ�
	CMoneyType TodayPositionCost;
	///���ֲ߳�
	CVolumeType ShortPosition;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableInvestorPosition CInvestorPosition;

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionActionTrigger�ǲ����ֱֲ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionActionTrigger
{
public:
	///���췽��
	CInvestorPositionActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CInvestorPositionActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInvestorPositionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pInvestorPosition	Ҫ�����InvestorPosition
	virtual void beforeAdd(CWriteableInvestorPosition *pInvestorPosition)
	{
		return;
	}
	
	///����󴥷�
	///@param	pInvestorPosition	�Ѿ������InvestorPosition
	virtual void afterAdd(CInvestorPosition *pInvestorPosition)
	{
		return;
	}

	///����ǰ����	
	///@param	pInvestorPosition	��ˢ�µ�CInvestorPosition
	///@param	pNewInvestorPosition	�µ�ֵ
	virtual void beforeUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pInvestorPosition	��ˢ�µ�CInvestorPosition
	virtual void afterUpdate(CInvestorPosition *pInvestorPosition)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pInvestorPosition	Ҫɾ����CInvestorPosition
	virtual void beforeRemove(CInvestorPosition *pInvestorPosition)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInvestorPositionFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionCommitTrigger��ȷ�ϳֱֲ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionCommitTrigger
{
public:
	///���췽��
	CInvestorPositionCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CInvestorPositionCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInvestorPositionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pInvestorPosition	�Ѿ������InvestorPosition
	virtual void commitAdd(CInvestorPosition *pInvestorPosition)
	{
		return;
	}

	///���º󴥷�
	///@param	pInvestorPosition	��ˢ�µ�CInvestorPosition
	///@param	poldInvestorPosition	ԭ����ֵ
	virtual void commitUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pOldInvestorPosition)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pInvestorPosition	�Ѿ�ɾ����CInvestorPosition
	virtual void commitRemove(CWriteableInvestorPosition *pInvestorPosition)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInvestorPositionFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionIterator��һ���Գֱֲ��ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionIterator
{
public:
	///���췽��
	CInvestorPositionIterator(void)
	{
	}

	///���췽��
	CInvestorPositionIterator(CInvestorPositionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorPositionIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��InvestorPosition
	///@return	��һ����������CInvestorPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorPosition *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CInvestorPositionFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorPosition ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorPosition * pInvestorPosition,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CInvestorPositionFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInvestorAccount��һ���洢�˻�ʵʱ�ʽ��Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInvestorAccount
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! AccountID.isValid())
			return 0;
		if (! PreBalance.isValid())
			return 0;
		if (! PreAvailable.isValid())
			return 0;
		if (! Deposit.isValid())
			return 0;
		if (! Withdraw.isValid())
			return 0;
		if (! Margin.isValid())
			return 0;
		if (! Premium.isValid())
			return 0;
		if (! Fee.isValid())
			return 0;
		if (! FrozenMargin.isValid())
			return 0;
		if (! FrozenPremium.isValid())
			return 0;
		if (! FrozenFee.isValid())
			return 0;
		if (! CloseProfit.isValid())
			return 0;
		if (! PositionProfit.isValid())
			return 0;
		if (! Available.isValid())
			return 0;
		if (! Balance.isValid())
			return 0;
		if (! LongMargin.isValid())
			return 0;
		if (! ShortMargin.isValid())
			return 0;
		if (! LongFrozenMargin.isValid())
			return 0;
		if (! ShortFrozenMargin.isValid())
			return 0;
		if (! DynamicRights.isValid())
			return 0;
		if (! Risk.isValid())
			return 0;
		if (! OtherFee.isValid())
			return 0;
		if (! Mortgage.isValid())
			return 0;
		if (! Currency.isValid())
			return 0;
		if (! TotalFrozenPos.isValid())
			return 0;
		if (! TodayInOut.isValid())
			return 0;
		if (! ReleaseMargin.isValid())
			return 0;
		if (! IsProfitCanUse.isValid())
			return 0;
		if (! ManualFrozen.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableInvestorAccount *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///Ͷ���߱��
	CInvestorIDType InvestorID;
	///�ʽ��ʺ�
	CAccountIDType AccountID;
	///�ϴν���׼����
	CMoneyType PreBalance;
	///���տ����ʽ�
	CMoneyType PreAvailable;
	///�����
	CMoneyType Deposit;
	///������
	CMoneyType Withdraw;
	///ռ�ñ�֤��
	CMoneyType Margin;
	///��ȨȨ������֧
	CMoneyType Premium;
	///������
	CMoneyType Fee;
	///����ı�֤��
	CMoneyType FrozenMargin;
	///����Ȩ����
	CMoneyType FrozenPremium;
	///����������
	CMoneyType FrozenFee;
	///ƽ��ӯ��
	CMoneyType CloseProfit;
	///�ֲ�ӯ��
	CMoneyType PositionProfit;
	///�����ʽ�
	CMoneyType Available;
	///����׼����
	CMoneyType Balance;
	///��ͷռ�ñ�֤��
	CMoneyType LongMargin;
	///��ͷռ�ñ�֤��
	CMoneyType ShortMargin;
	///��ͷ����ı�֤��
	CMoneyType LongFrozenMargin;
	///��ͷ����ı�֤��
	CMoneyType ShortFrozenMargin;
	///��̬Ȩ��
	CMoneyType DynamicRights;
	///���ն�
	CMoneyType Risk;
	///��������
	CMoneyType OtherFee;
	///��Ѻ���
	CMoneyType Mortgage;
	///����
	CCurrencyIDType Currency;
	///�ܶ���ֲ�
	CVolumeType TotalFrozenPos;
	///���ճ����
	CMoneyType TodayInOut;
	///�����ͷű�֤��
	CMoneyType ReleaseMargin;
	///��ӯ�Ƿ����
	CBoolType IsProfitCanUse;
	///��ʱ�����ʽ�
	CMoneyType ManualFrozen;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableInvestorAccount CInvestorAccount;

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountActionTrigger�ǲ����˻�ʵʱ�ʽ��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountActionTrigger
{
public:
	///���췽��
	CInvestorAccountActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CInvestorAccountActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInvestorAccountFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pInvestorAccount	Ҫ�����InvestorAccount
	virtual void beforeAdd(CWriteableInvestorAccount *pInvestorAccount)
	{
		return;
	}
	
	///����󴥷�
	///@param	pInvestorAccount	�Ѿ������InvestorAccount
	virtual void afterAdd(CInvestorAccount *pInvestorAccount)
	{
		return;
	}

	///����ǰ����	
	///@param	pInvestorAccount	��ˢ�µ�CInvestorAccount
	///@param	pNewInvestorAccount	�µ�ֵ
	virtual void beforeUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pInvestorAccount	��ˢ�µ�CInvestorAccount
	virtual void afterUpdate(CInvestorAccount *pInvestorAccount)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pInvestorAccount	Ҫɾ����CInvestorAccount
	virtual void beforeRemove(CInvestorAccount *pInvestorAccount)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInvestorAccountFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountCommitTrigger��ȷ���˻�ʵʱ�ʽ��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountCommitTrigger
{
public:
	///���췽��
	CInvestorAccountCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CInvestorAccountCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInvestorAccountFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pInvestorAccount	�Ѿ������InvestorAccount
	virtual void commitAdd(CInvestorAccount *pInvestorAccount)
	{
		return;
	}

	///���º󴥷�
	///@param	pInvestorAccount	��ˢ�µ�CInvestorAccount
	///@param	poldInvestorAccount	ԭ����ֵ
	virtual void commitUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pOldInvestorAccount)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pInvestorAccount	�Ѿ�ɾ����CInvestorAccount
	virtual void commitRemove(CWriteableInvestorAccount *pInvestorAccount)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInvestorAccountFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountIterator��һ�����˻�ʵʱ�ʽ���ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountIterator
{
public:
	///���췽��
	CInvestorAccountIterator(void)
	{
	}

	///���췽��
	CInvestorAccountIterator(CInvestorAccountFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorAccountIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��InvestorAccount
	///@return	��һ����������CInvestorAccount������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorAccount *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CInvestorAccountFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorAccount ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorAccount * pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CInvestorAccountFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInvestorAccountDeposit��һ���洢�˻�ʵʱ������Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInvestorAccountDeposit
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! AccountSeqNo.isValid())
			return 0;
		if (! AccountID.isValid())
			return 0;
		if (! AccountInsideSeqNo.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! Amount.isValid())
			return 0;
		if (! AmountDirection.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableInvestorAccountDeposit *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///�ʽ���ˮ��
	CAccountSeqNoType AccountSeqNo;
	///�ʽ��ʺ�
	CAccountIDType AccountID;
	///�������������ʽ���ˮ��
	CAccountSeqNoType AccountInsideSeqNo;
	///Ͷ���߱��
	CInvestorIDType InvestorID;
	///���
	CMoneyType Amount;
	///�������
	CAccountDirectionType AmountDirection;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableInvestorAccountDeposit CInvestorAccountDeposit;

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositActionTrigger�ǲ����˻�ʵʱ������ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositActionTrigger
{
public:
	///���췽��
	CInvestorAccountDepositActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CInvestorAccountDepositActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInvestorAccountDepositFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pInvestorAccountDeposit	Ҫ�����InvestorAccountDeposit
	virtual void beforeAdd(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return;
	}
	
	///����󴥷�
	///@param	pInvestorAccountDeposit	�Ѿ������InvestorAccountDeposit
	virtual void afterAdd(CInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return;
	}

	///����ǰ����	
	///@param	pInvestorAccountDeposit	��ˢ�µ�CInvestorAccountDeposit
	///@param	pNewInvestorAccountDeposit	�µ�ֵ
	virtual void beforeUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pInvestorAccountDeposit	��ˢ�µ�CInvestorAccountDeposit
	virtual void afterUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pInvestorAccountDeposit	Ҫɾ����CInvestorAccountDeposit
	virtual void beforeRemove(CInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInvestorAccountDepositFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositCommitTrigger��ȷ���˻�ʵʱ������ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositCommitTrigger
{
public:
	///���췽��
	CInvestorAccountDepositCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CInvestorAccountDepositCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInvestorAccountDepositFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pInvestorAccountDeposit	�Ѿ������InvestorAccountDeposit
	virtual void commitAdd(CInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return;
	}

	///���º󴥷�
	///@param	pInvestorAccountDeposit	��ˢ�µ�CInvestorAccountDeposit
	///@param	poldInvestorAccountDeposit	ԭ����ֵ
	virtual void commitUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pOldInvestorAccountDeposit)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pInvestorAccountDeposit	�Ѿ�ɾ����CInvestorAccountDeposit
	virtual void commitRemove(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInvestorAccountDepositFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositIterator��һ�����˻�ʵʱ�������ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositIterator
{
public:
	///���췽��
	CInvestorAccountDepositIterator(void)
	{
	}

	///���췽��
	CInvestorAccountDepositIterator(CInvestorAccountDepositFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorAccountDepositIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��InvestorAccountDeposit
	///@return	��һ����������CInvestorAccountDeposit������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorAccountDeposit *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CInvestorAccountDepositFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorAccountDeposit ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorAccountDeposit * pInvestorAccountDeposit,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CInvestorAccountDepositFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableExchange��һ���洢��������Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableExchange
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! TradingDay.isValid())
			return 0;
		if (! ExchangeID.isValid())
			return 0;
		if (! ExchangeName.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableExchange *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///������
	CTradingDayType TradingDay;
	///����������
	CExchangeIDType ExchangeID;
	///����������
	CExchangeNameType ExchangeName;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableExchange CExchange;

/////////////////////////////////////////////////////////////////////////
///CExchangeActionTrigger�ǲ�����������ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeActionTrigger
{
public:
	///���췽��
	CExchangeActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CExchangeActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CExchangeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pExchange	Ҫ�����Exchange
	virtual void beforeAdd(CWriteableExchange *pExchange)
	{
		return;
	}
	
	///����󴥷�
	///@param	pExchange	�Ѿ������Exchange
	virtual void afterAdd(CExchange *pExchange)
	{
		return;
	}

	///����ǰ����	
	///@param	pExchange	��ˢ�µ�CExchange
	///@param	pNewExchange	�µ�ֵ
	virtual void beforeUpdate(CExchange *pExchange, CWriteableExchange *pNewExchange)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pExchange	��ˢ�µ�CExchange
	virtual void afterUpdate(CExchange *pExchange)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pExchange	Ҫɾ����CExchange
	virtual void beforeRemove(CExchange *pExchange)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CExchangeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CExchangeCommitTrigger��ȷ�Ͻ�������ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeCommitTrigger
{
public:
	///���췽��
	CExchangeCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CExchangeCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CExchangeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pExchange	�Ѿ������Exchange
	virtual void commitAdd(CExchange *pExchange)
	{
		return;
	}

	///���º󴥷�
	///@param	pExchange	��ˢ�µ�CExchange
	///@param	poldExchange	ԭ����ֵ
	virtual void commitUpdate(CExchange *pExchange, CWriteableExchange *pOldExchange)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pExchange	�Ѿ�ɾ����CExchange
	virtual void commitRemove(CWriteableExchange *pExchange)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CExchangeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CExchangeIterator��һ���Խ��������ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeIterator
{
public:
	///���췽��
	CExchangeIterator(void)
	{
	}

	///���췽��
	CExchangeIterator(CExchangeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CExchangeIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��Exchange
	///@return	��һ����������CExchange������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CExchange *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CExchangeFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pExchange ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableExchange * pExchange,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CExchangeFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableSeat��һ���洢�µ�ϯλ��Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableSeat
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! APIID.isValid())
			return 0;
		if (! ExchangeID.isValid())
			return 0;
		if (! ParticipantID.isValid())
			return 0;
		if (! SeatID.isValid())
			return 0;
		if (! SeatPassword.isValid())
			return 0;
		if (! ApiLinkType.isValid())
			return 0;
		if (! RecvRtn.isValid())
			return 0;
		if (! MainSeat.isValid())
			return 0;
		if (! QueryBase.isValid())
			return 0;
		if (! QueryPosition.isValid())
			return 0;
		if (! ResumeType.isValid())
			return 0;
		if (! Heartbeat.isValid())
			return 0;
		if (! IsActive.isValid())
			return 0;
		if (! RiskCheck.isValid())
			return 0;
		if (! FrontAddr.isValid())
			return 0;
		if (! SeatStatus.isValid())
			return 0;
		if (! OrderLocalID.isValid())
			return 0;
		if (! LinkBrokerID.isValid())
			return 0;
		if (! TradingDay.isValid())
			return 0;
		if (! CheckTradingDay.isValid())
			return 0;
		if (! Custom.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableSeat *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///����API�е����
	CNumberType APIID;
	///����������
	CExchangeIDType ExchangeID;
	///��Ա���
	CParticipantIDType ParticipantID;
	///ϯλ��
	CSeatIDType SeatID;
	///ϯλ����
	CPasswordType SeatPassword;
	///ϯλ����api����
	CApiLinkTypeType ApiLinkType;
	///�Ƿ���ջر�
	CBoolType RecvRtn;
	///ϯλ����(�Ƿ��������ϯλ�ر�)
	CBoolType MainSeat;
	///�Ƿ��ѯ������Ϣ
	CBoolType QueryBase;
	///�Ƿ��ѯ�ֲ�
	CBoolType QueryPosition;
	///��ȡ�ر��ķ�ʽ
	CNumberType ResumeType;
	///����ʱ��(��)
	CNumberType Heartbeat;
	///�Ƿ��Ծ
	CBoolType IsActive;
	///�Ƿ����ʽ�ֲַ��
	CBoolType RiskCheck;
	///���ӵ�ַ
	CFrontAddrType FrontAddr;
	///ϯλ״̬
	CSeatStatusType SeatStatus;
	///���ر������
	COrderLocalIDType OrderLocalID;
	///���Ӷ�Ӧ��Broker(guofu/sucden/fcstone)
	CBrokerIDType LinkBrokerID;
	///��Ҫϯλ�����Ľ�������
	CTradingDayType TradingDay;
	///�Ƿ���Ҫ��齻������
	CBoolType CheckTradingDay;
	///�����Զ��������
	CSeatCustomType Custom;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableSeat CSeat;

/////////////////////////////////////////////////////////////////////////
///CSeatActionTrigger�ǲ����µ�ϯλ��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatActionTrigger
{
public:
	///���췽��
	CSeatActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CSeatActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CSeatFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pSeat	Ҫ�����Seat
	virtual void beforeAdd(CWriteableSeat *pSeat)
	{
		return;
	}
	
	///����󴥷�
	///@param	pSeat	�Ѿ������Seat
	virtual void afterAdd(CSeat *pSeat)
	{
		return;
	}

	///����ǰ����	
	///@param	pSeat	��ˢ�µ�CSeat
	///@param	pNewSeat	�µ�ֵ
	virtual void beforeUpdate(CSeat *pSeat, CWriteableSeat *pNewSeat)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pSeat	��ˢ�µ�CSeat
	virtual void afterUpdate(CSeat *pSeat)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pSeat	Ҫɾ����CSeat
	virtual void beforeRemove(CSeat *pSeat)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CSeatFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CSeatCommitTrigger��ȷ���µ�ϯλ��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatCommitTrigger
{
public:
	///���췽��
	CSeatCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CSeatCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CSeatFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pSeat	�Ѿ������Seat
	virtual void commitAdd(CSeat *pSeat)
	{
		return;
	}

	///���º󴥷�
	///@param	pSeat	��ˢ�µ�CSeat
	///@param	poldSeat	ԭ����ֵ
	virtual void commitUpdate(CSeat *pSeat, CWriteableSeat *pOldSeat)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pSeat	�Ѿ�ɾ����CSeat
	virtual void commitRemove(CWriteableSeat *pSeat)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CSeatFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CSeatIterator��һ�����µ�ϯλ���ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatIterator
{
public:
	///���췽��
	CSeatIterator(void)
	{
	}

	///���췽��
	CSeatIterator(CSeatFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CSeatIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��Seat
	///@return	��һ����������CSeat������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSeat *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CSeatFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pSeat ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSeat * pSeat,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CSeatFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInstrument��һ���洢�ڻ���Լ��Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInstrument
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! ExchangeID.isValid())
			return 0;
		if (! ProductID.isValid())
			return 0;
		if (! ProductName.isValid())
			return 0;
		if (! InstrumentID.isValid())
			return 0;
		if (! InstrumentName.isValid())
			return 0;
		if (! DeliveryYear.isValid())
			return 0;
		if (! DeliveryMonth.isValid())
			return 0;
		if (! MaxLimitOrderVolume.isValid())
			return 0;
		if (! MinLimitOrderVolume.isValid())
			return 0;
		if (! MaxMarketOrderVolume.isValid())
			return 0;
		if (! MinMarketOrderVolume.isValid())
			return 0;
		if (! VolumeMultiple.isValid())
			return 0;
		if (! PriceTick.isValid())
			return 0;
		if (! Currency.isValid())
			return 0;
		if (! LongPosLimit.isValid())
			return 0;
		if (! ShortPosLimit.isValid())
			return 0;
		if (! LowerLimitPrice.isValid())
			return 0;
		if (! UpperLimitPrice.isValid())
			return 0;
		if (! PreSettlementPrice.isValid())
			return 0;
		if (! InstrumentStatus.isValid())
			return 0;
		if (! CreateDate.isValid())
			return 0;
		if (! OpenDate.isValid())
			return 0;
		if (! ExpireDate.isValid())
			return 0;
		if (! StartDelivDate.isValid())
			return 0;
		if (! EndDelivDate.isValid())
			return 0;
		if (! BasisPrice.isValid())
			return 0;
		if (! IsTrading.isValid())
			return 0;
		if (! UnderlyingInstrID.isValid())
			return 0;
		if (! UnderlyingMultiple.isValid())
			return 0;
		if (! PositionType.isValid())
			return 0;
		if (! StrikePrice.isValid())
			return 0;
		if (! OptionsType.isValid())
			return 0;
		if (! ProductClass.isValid())
			return 0;
		if (! OptionsMode.isValid())
			return 0;
		if (! ProductGroupID.isValid())
			return 0;
		if (! APIID.isValid())
			return 0;
		if (! LegQty.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableInstrument *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///����������
	CExchangeIDType ExchangeID;
	///Ʒ�ִ���
	CProductIDType ProductID;
	///Ʒ������
	CProductNameType ProductName;
	///��Լ����
	CInstrumentIDType InstrumentID;
	///��Լ����
	CInstrumentNameType InstrumentName;
	///�������
	CYearType DeliveryYear;
	///������
	CMonthType DeliveryMonth;
	///�޼۵�����µ���
	CVolumeType MaxLimitOrderVolume;
	///�޼۵���С�µ���
	CVolumeType MinLimitOrderVolume;
	///�м۵�����µ���
	CVolumeType MaxMarketOrderVolume;
	///�м۵���С�µ���
	CVolumeType MinMarketOrderVolume;
	///��������
	CVolumeMultipleType VolumeMultiple;
	///���۵�λ
	CPriceTickType PriceTick;
	///����
	CCurrencyType Currency;
	///��ͷ�޲�
	CVolumeType LongPosLimit;
	///��ͷ�޲�
	CVolumeType ShortPosLimit;
	///��ͣ���
	CPriceType LowerLimitPrice;
	///��ͣ���
	CPriceType UpperLimitPrice;
	///�����
	CPriceType PreSettlementPrice;
	///��Լ����״̬
	CInstrumentStatusType InstrumentStatus;
	///������
	CDateType CreateDate;
	///������
	CDateType OpenDate;
	///������
	CDateType ExpireDate;
	///��ʼ������
	CDateType StartDelivDate;
	///��󽻸���
	CDateType EndDelivDate;
	///���ƻ�׼��
	CPriceType BasisPrice;
	///��ǰ�Ƿ���
	CBoolType IsTrading;
	///������Ʒ����
	CInstrumentIDType UnderlyingInstrID;
	///������Ʒ����
	CUnderlyingMultipleType UnderlyingMultiple;
	///�ֲ�����
	CPositionTypeType PositionType;
	///ִ�м�
	CPriceType StrikePrice;
	///��Ȩ����
	COptionsTypeType OptionsType;
	///��Ʒ����
	CProductClassType ProductClass;
	///��Ȩ��Ȩ��ʽ
	COptionsModeType OptionsMode;
	///��Ʒ��
	CProductGroupIDType ProductGroupID;
	///ͨ����Ӧ��APIID
	CNumberType APIID;
	///��Ϻ�Լ�ȵ�����
	CNumberType LegQty;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableInstrument CInstrument;

/////////////////////////////////////////////////////////////////////////
///CInstrumentActionTrigger�ǲ����ڻ���Լ��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentActionTrigger
{
public:
	///���췽��
	CInstrumentActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CInstrumentActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInstrumentFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pInstrument	Ҫ�����Instrument
	virtual void beforeAdd(CWriteableInstrument *pInstrument)
	{
		return;
	}
	
	///����󴥷�
	///@param	pInstrument	�Ѿ������Instrument
	virtual void afterAdd(CInstrument *pInstrument)
	{
		return;
	}

	///����ǰ����	
	///@param	pInstrument	��ˢ�µ�CInstrument
	///@param	pNewInstrument	�µ�ֵ
	virtual void beforeUpdate(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pInstrument	��ˢ�µ�CInstrument
	virtual void afterUpdate(CInstrument *pInstrument)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pInstrument	Ҫɾ����CInstrument
	virtual void beforeRemove(CInstrument *pInstrument)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInstrumentFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentCommitTrigger��ȷ���ڻ���Լ��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentCommitTrigger
{
public:
	///���췽��
	CInstrumentCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CInstrumentCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInstrumentFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pInstrument	�Ѿ������Instrument
	virtual void commitAdd(CInstrument *pInstrument)
	{
		return;
	}

	///���º󴥷�
	///@param	pInstrument	��ˢ�µ�CInstrument
	///@param	poldInstrument	ԭ����ֵ
	virtual void commitUpdate(CInstrument *pInstrument, CWriteableInstrument *pOldInstrument)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pInstrument	�Ѿ�ɾ����CInstrument
	virtual void commitRemove(CWriteableInstrument *pInstrument)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInstrumentFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentIterator��һ�����ڻ���Լ���ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentIterator
{
public:
	///���췽��
	CInstrumentIterator(void)
	{
	}

	///���췽��
	CInstrumentIterator(CInstrumentFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInstrumentIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��Instrument
	///@return	��һ����������CInstrument������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInstrument *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CInstrumentFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInstrument ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInstrument * pInstrument,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CInstrumentFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableCmbInstrumentDetail��һ���洢�ڻ���Ϻ�Լ��ϸ��Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableCmbInstrumentDetail
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! ExchangeID.isValid())
			return 0;
		if (! ArbiInstrumentID.isValid())
			return 0;
		if (! SingleInstrumentID.isValid())
			return 0;
		if (! LegNo.isValid())
			return 0;
		if (! Direction.isValid())
			return 0;
		if (! Ratio.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableCmbInstrumentDetail *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///����������
	CExchangeIDType ExchangeID;
	///��Ϻ�Լ����
	CInstrumentIDType ArbiInstrumentID;
	///���Ⱥ�Լ����
	CInstrumentIDType SingleInstrumentID;
	///��Ϻ�Լ�ȵ�����
	CNumberType LegNo;
	///��������
	CDirectionType Direction;
	///��������
	CNumberType Ratio;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableCmbInstrumentDetail CCmbInstrumentDetail;

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailActionTrigger�ǲ����ڻ���Ϻ�Լ��ϸ��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailActionTrigger
{
public:
	///���췽��
	CCmbInstrumentDetailActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CCmbInstrumentDetailActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CCmbInstrumentDetailFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pCmbInstrumentDetail	Ҫ�����CmbInstrumentDetail
	virtual void beforeAdd(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return;
	}
	
	///����󴥷�
	///@param	pCmbInstrumentDetail	�Ѿ������CmbInstrumentDetail
	virtual void afterAdd(CCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return;
	}

	///����ǰ����	
	///@param	pCmbInstrumentDetail	��ˢ�µ�CCmbInstrumentDetail
	///@param	pNewCmbInstrumentDetail	�µ�ֵ
	virtual void beforeUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pCmbInstrumentDetail	��ˢ�µ�CCmbInstrumentDetail
	virtual void afterUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pCmbInstrumentDetail	Ҫɾ����CCmbInstrumentDetail
	virtual void beforeRemove(CCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CCmbInstrumentDetailFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailCommitTrigger��ȷ���ڻ���Ϻ�Լ��ϸ��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailCommitTrigger
{
public:
	///���췽��
	CCmbInstrumentDetailCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CCmbInstrumentDetailCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CCmbInstrumentDetailFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pCmbInstrumentDetail	�Ѿ������CmbInstrumentDetail
	virtual void commitAdd(CCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return;
	}

	///���º󴥷�
	///@param	pCmbInstrumentDetail	��ˢ�µ�CCmbInstrumentDetail
	///@param	poldCmbInstrumentDetail	ԭ����ֵ
	virtual void commitUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pOldCmbInstrumentDetail)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pCmbInstrumentDetail	�Ѿ�ɾ����CCmbInstrumentDetail
	virtual void commitRemove(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CCmbInstrumentDetailFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailIterator��һ�����ڻ���Ϻ�Լ��ϸ���ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailIterator
{
public:
	///���췽��
	CCmbInstrumentDetailIterator(void)
	{
	}

	///���췽��
	CCmbInstrumentDetailIterator(CCmbInstrumentDetailFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CCmbInstrumentDetailIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��CmbInstrumentDetail
	///@return	��һ����������CCmbInstrumentDetail������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CCmbInstrumentDetail *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CCmbInstrumentDetailFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pCmbInstrumentDetail ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableCmbInstrumentDetail * pCmbInstrumentDetail,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CCmbInstrumentDetailFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableClientTradingID��һ���洢�������ͻ������Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableClientTradingID
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! AccountID.isValid())
			return 0;
		if (! ExchangeID.isValid())
			return 0;
		if (! ParticipantID.isValid())
			return 0;
		if (! ClientID.isValid())
			return 0;
		if (! ClientRight.isValid())
			return 0;
		if (! ClientType.isValid())
			return 0;
		if (! ClientHedgeFlag.isValid())
			return 0;
		if (! IsActive.isValid())
			return 0;
		if (! APIID.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableClientTradingID *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///Ͷ���߱��
	CInvestorIDType InvestorID;
	///�ʽ��ʺ�
	CAccountIDType AccountID;
	///����������
	CExchangeIDType ExchangeID;
	///��Ա���
	CParticipantIDType ParticipantID;
	///�ͻ�����
	CClientIDType ClientID;
	///�ͻ�����Ȩ��
	CTradingRightType ClientRight;
	///�ͻ�����
	CClientTypeType ClientType;
	///�ͻ���ֵ����
	CHedgeFlagType ClientHedgeFlag;
	///�Ƿ��Ծ
	CIsActiveType IsActive;
	///ͨ����Ӧ��APIID
	CNumberType APIID;
	
	unsigned int HashBrokerIDExchangeIDPartClientID;
	
	///����BrokerIDExchangeIDPartClientID��hashֵ
	void calHashBrokerIDExchangeIDPartClientID(void)
	{
		unsigned key=0;
		key=BrokerID.hash(key);
		key=ExchangeID.hash(key);
		key=ParticipantID.hash(key);
		key=ClientID.hash(key);
		HashBrokerIDExchangeIDPartClientID=key;
	}
	
	///������Ҫ���������BrokerIDExchangeIDPartClientID��hashֵ
	void updateHashBrokerIDExchangeIDPartClientID(void)
	{
	}
	
	///�������е�hashֵ
	void calAllHash(void)
	{
		calHashBrokerIDExchangeIDPartClientID();
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
		updateHashBrokerIDExchangeIDPartClientID();
	}
	
	///�����Ӧ���ʻ���ָ��
	///@param	pFactory	�����Ӧ���ʻ���ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ���ʻ���ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorAccount *linkInvestorAccount(CInvestorAccountFactory *pFactory) const;

	///�����Ӧ���ʻ�ָ��
	///@param	pInvestorAccount	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorAccount
	const CWriteableInvestorAccount *linkInvestorAccount(const CWriteableInvestorAccount *pInvestorAccount) const
	{
		void *target=(void *)(&(this->pInvestorAccount));
		*((const CWriteableInvestorAccount **)target)=pInvestorAccount;
		return pInvestorAccount;
	}
	
	///��ȡ��Ӧ���ʻ���ָ��
	///@return	�ҵ��Ķ�Ӧ���ʻ���ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorAccount *getInvestorAccount(void) const
	{
		return pInvestorAccount;
	}

private:
	///��Ӧ���ʻ�
	const CWriteableInvestorAccount *pInvestorAccount;
};

typedef const CWriteableClientTradingID CClientTradingID;

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDActionTrigger�ǲ����������ͻ������ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDActionTrigger
{
public:
	///���췽��
	CClientTradingIDActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CClientTradingIDActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CClientTradingIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pClientTradingID	Ҫ�����ClientTradingID
	virtual void beforeAdd(CWriteableClientTradingID *pClientTradingID)
	{
		return;
	}
	
	///����󴥷�
	///@param	pClientTradingID	�Ѿ������ClientTradingID
	virtual void afterAdd(CClientTradingID *pClientTradingID)
	{
		return;
	}

	///����ǰ����	
	///@param	pClientTradingID	��ˢ�µ�CClientTradingID
	///@param	pNewClientTradingID	�µ�ֵ
	virtual void beforeUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pClientTradingID	��ˢ�µ�CClientTradingID
	virtual void afterUpdate(CClientTradingID *pClientTradingID)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pClientTradingID	Ҫɾ����CClientTradingID
	virtual void beforeRemove(CClientTradingID *pClientTradingID)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CClientTradingIDFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDCommitTrigger��ȷ�Ͻ������ͻ������ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDCommitTrigger
{
public:
	///���췽��
	CClientTradingIDCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CClientTradingIDCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CClientTradingIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pClientTradingID	�Ѿ������ClientTradingID
	virtual void commitAdd(CClientTradingID *pClientTradingID)
	{
		return;
	}

	///���º󴥷�
	///@param	pClientTradingID	��ˢ�µ�CClientTradingID
	///@param	poldClientTradingID	ԭ����ֵ
	virtual void commitUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pOldClientTradingID)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pClientTradingID	�Ѿ�ɾ����CClientTradingID
	virtual void commitRemove(CWriteableClientTradingID *pClientTradingID)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CClientTradingIDFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDIterator��һ���Խ������ͻ�������ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDIterator
{
public:
	///���췽��
	CClientTradingIDIterator(void)
	{
	}

	///���췽��
	CClientTradingIDIterator(CClientTradingIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CClientTradingIDIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��ClientTradingID
	///@return	��һ����������CClientTradingID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CClientTradingID *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CClientTradingIDFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pClientTradingID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableClientTradingID * pClientTradingID,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CClientTradingIDFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInvestor��һ���洢Ͷ������Ϣ��Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInvestor
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! InvestorName.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableInvestor *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///Ͷ���߱��
	CInvestorIDType InvestorID;
	///Ͷ��������
	CInvestorNameType InvestorName;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableInvestor CInvestor;

/////////////////////////////////////////////////////////////////////////
///CInvestorActionTrigger�ǲ���Ͷ������Ϣ��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorActionTrigger
{
public:
	///���췽��
	CInvestorActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CInvestorActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInvestorFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pInvestor	Ҫ�����Investor
	virtual void beforeAdd(CWriteableInvestor *pInvestor)
	{
		return;
	}
	
	///����󴥷�
	///@param	pInvestor	�Ѿ������Investor
	virtual void afterAdd(CInvestor *pInvestor)
	{
		return;
	}

	///����ǰ����	
	///@param	pInvestor	��ˢ�µ�CInvestor
	///@param	pNewInvestor	�µ�ֵ
	virtual void beforeUpdate(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pInvestor	��ˢ�µ�CInvestor
	virtual void afterUpdate(CInvestor *pInvestor)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pInvestor	Ҫɾ����CInvestor
	virtual void beforeRemove(CInvestor *pInvestor)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInvestorFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorCommitTrigger��ȷ��Ͷ������Ϣ��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorCommitTrigger
{
public:
	///���췽��
	CInvestorCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CInvestorCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInvestorFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pInvestor	�Ѿ������Investor
	virtual void commitAdd(CInvestor *pInvestor)
	{
		return;
	}

	///���º󴥷�
	///@param	pInvestor	��ˢ�µ�CInvestor
	///@param	poldInvestor	ԭ����ֵ
	virtual void commitUpdate(CInvestor *pInvestor, CWriteableInvestor *pOldInvestor)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pInvestor	�Ѿ�ɾ����CInvestor
	virtual void commitRemove(CWriteableInvestor *pInvestor)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInvestorFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorIterator��һ����Ͷ������Ϣ���ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorIterator
{
public:
	///���췽��
	CInvestorIterator(void)
	{
	}

	///���췽��
	CInvestorIterator(CInvestorFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��Investor
	///@return	��һ����������CInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestor *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CInvestorFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestor ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestor * pInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CInvestorFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInvestorMargin��һ���洢�ͻ��ڻ���֤���ʱ�Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInvestorMargin
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! ExchangeID.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! InstrumentID.isValid())
			return 0;
		if (! HedgeFlag.isValid())
			return 0;
		if (! LongMarginRate.isValid())
			return 0;
		if (! LongMarginAmt.isValid())
			return 0;
		if (! ShortMarginRate.isValid())
			return 0;
		if (! ShortMarginAmt.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableInvestorMargin *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///����������
	CExchangeIDType ExchangeID;
	///Ͷ���߱���
	CInvestorIDType InvestorID;
	///��Լ����
	CInstrumentIDType InstrumentID;
	///Ͷ���ױ���־
	CHedgeFlagType HedgeFlag;
	///��ͷռ�ñ�֤�𰴱���
	CRatioType LongMarginRate;
	///��ͷ��֤������
	CRatioType LongMarginAmt;
	///��ͷռ�ñ�֤�𰴱���
	CRatioType ShortMarginRate;
	///��ͷ��֤������
	CRatioType ShortMarginAmt;
	
	unsigned int HashInstrumentAndClientID;
	
	///����InstrumentAndClientID��hashֵ
	void calHashInstrumentAndClientID(void)
	{
		unsigned key=0;
		key=InstrumentID.hash(key);
		key=InvestorID.hash(key);
		HashInstrumentAndClientID=key;
	}
	
	///������Ҫ���������InstrumentAndClientID��hashֵ
	void updateHashInstrumentAndClientID(void)
	{
	}
	
	///�������е�hashֵ
	void calAllHash(void)
	{
		calHashInstrumentAndClientID();
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
		updateHashInstrumentAndClientID();
	}
	

private:
};

typedef const CWriteableInvestorMargin CInvestorMargin;

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginActionTrigger�ǲ����ͻ��ڻ���֤���ʱ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginActionTrigger
{
public:
	///���췽��
	CInvestorMarginActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CInvestorMarginActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInvestorMarginFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pInvestorMargin	Ҫ�����InvestorMargin
	virtual void beforeAdd(CWriteableInvestorMargin *pInvestorMargin)
	{
		return;
	}
	
	///����󴥷�
	///@param	pInvestorMargin	�Ѿ������InvestorMargin
	virtual void afterAdd(CInvestorMargin *pInvestorMargin)
	{
		return;
	}

	///����ǰ����	
	///@param	pInvestorMargin	��ˢ�µ�CInvestorMargin
	///@param	pNewInvestorMargin	�µ�ֵ
	virtual void beforeUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pInvestorMargin	��ˢ�µ�CInvestorMargin
	virtual void afterUpdate(CInvestorMargin *pInvestorMargin)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pInvestorMargin	Ҫɾ����CInvestorMargin
	virtual void beforeRemove(CInvestorMargin *pInvestorMargin)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInvestorMarginFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginCommitTrigger��ȷ�Ͽͻ��ڻ���֤���ʱ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginCommitTrigger
{
public:
	///���췽��
	CInvestorMarginCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CInvestorMarginCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInvestorMarginFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pInvestorMargin	�Ѿ������InvestorMargin
	virtual void commitAdd(CInvestorMargin *pInvestorMargin)
	{
		return;
	}

	///���º󴥷�
	///@param	pInvestorMargin	��ˢ�µ�CInvestorMargin
	///@param	poldInvestorMargin	ԭ����ֵ
	virtual void commitUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pOldInvestorMargin)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pInvestorMargin	�Ѿ�ɾ����CInvestorMargin
	virtual void commitRemove(CWriteableInvestorMargin *pInvestorMargin)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInvestorMarginFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginIterator��һ���Կͻ��ڻ���֤���ʱ��ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginIterator
{
public:
	///���췽��
	CInvestorMarginIterator(void)
	{
	}

	///���췽��
	CInvestorMarginIterator(CInvestorMarginFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorMarginIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��InvestorMargin
	///@return	��һ����������CInvestorMargin������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorMargin *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CInvestorMarginFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorMargin ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorMargin * pInvestorMargin,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CInvestorMarginFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInvestorFee��һ���洢�ͻ��������ʱ�Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInvestorFee
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! ExchangeID.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! InstrumentID.isValid())
			return 0;
		if (! HedgeFlag.isValid())
			return 0;
		if (! OpenFeeRate.isValid())
			return 0;
		if (! OpenFeeAmt.isValid())
			return 0;
		if (! OffsetFeeRate.isValid())
			return 0;
		if (! OffsetFeeAmt.isValid())
			return 0;
		if (! OTFeeRate.isValid())
			return 0;
		if (! OTFeeAmt.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableInvestorFee *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///����������
	CExchangeIDType ExchangeID;
	///Ͷ���߱���
	CInvestorIDType InvestorID;
	///��Լ����
	CInstrumentIDType InstrumentID;
	///Ͷ���ױ���־
	CHedgeFlagType HedgeFlag;
	///���������Ѱ�����
	CRatioType OpenFeeRate;
	///���������Ѱ�����
	CRatioType OpenFeeAmt;
	///ƽ�������Ѱ�����
	CRatioType OffsetFeeRate;
	///ƽ�������Ѱ�����
	CRatioType OffsetFeeAmt;
	///ƽ��������Ѱ�����
	CRatioType OTFeeRate;
	///ƽ��������Ѱ�����
	CRatioType OTFeeAmt;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableInvestorFee CInvestorFee;

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeActionTrigger�ǲ����ͻ��������ʱ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeActionTrigger
{
public:
	///���췽��
	CInvestorFeeActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CInvestorFeeActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInvestorFeeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pInvestorFee	Ҫ�����InvestorFee
	virtual void beforeAdd(CWriteableInvestorFee *pInvestorFee)
	{
		return;
	}
	
	///����󴥷�
	///@param	pInvestorFee	�Ѿ������InvestorFee
	virtual void afterAdd(CInvestorFee *pInvestorFee)
	{
		return;
	}

	///����ǰ����	
	///@param	pInvestorFee	��ˢ�µ�CInvestorFee
	///@param	pNewInvestorFee	�µ�ֵ
	virtual void beforeUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pInvestorFee	��ˢ�µ�CInvestorFee
	virtual void afterUpdate(CInvestorFee *pInvestorFee)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pInvestorFee	Ҫɾ����CInvestorFee
	virtual void beforeRemove(CInvestorFee *pInvestorFee)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInvestorFeeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeCommitTrigger��ȷ�Ͽͻ��������ʱ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeCommitTrigger
{
public:
	///���췽��
	CInvestorFeeCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CInvestorFeeCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInvestorFeeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pInvestorFee	�Ѿ������InvestorFee
	virtual void commitAdd(CInvestorFee *pInvestorFee)
	{
		return;
	}

	///���º󴥷�
	///@param	pInvestorFee	��ˢ�µ�CInvestorFee
	///@param	poldInvestorFee	ԭ����ֵ
	virtual void commitUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pOldInvestorFee)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pInvestorFee	�Ѿ�ɾ����CInvestorFee
	virtual void commitRemove(CWriteableInvestorFee *pInvestorFee)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInvestorFeeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeIterator��һ���Կͻ��������ʱ��ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeIterator
{
public:
	///���췽��
	CInvestorFeeIterator(void)
	{
	}

	///���췽��
	CInvestorFeeIterator(CInvestorFeeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorFeeIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��InvestorFee
	///@return	��һ����������CInvestorFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorFee *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CInvestorFeeFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorFee ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorFee * pInvestorFee,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CInvestorFeeFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableUser��һ���洢�û���Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableUser
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! UserID.isValid())
			return 0;
		if (! Password.isValid())
			return 0;
		if (! IsActive.isValid())
			return 0;
		if (! UserName.isValid())
			return 0;
		if (! UserType.isValid())
			return 0;
		if (! Department.isValid())
			return 0;
		if (! GrantFuncSet.isValid())
			return 0;
		if (! CheckIpMacAddr.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableUser *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///�û�����
	CUserIDType UserID;
	///�û���¼����
	CPasswordType Password;
	///�Ƿ��Ծ
	CIsActiveType IsActive;
	///�û�����
	CUserNameType UserName;
	///�û�����
	CUserTypeType UserType;
	///Ӫҵ��
	CDepartmentType Department;
	///��Ȩ���ܼ�
	CGrantFuncSetType GrantFuncSet;
	///�Ƿ���IP��MAC
	CBoolType CheckIpMacAddr;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableUser CUser;

/////////////////////////////////////////////////////////////////////////
///CUserActionTrigger�ǲ����û���ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserActionTrigger
{
public:
	///���췽��
	CUserActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CUserActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CUserFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pUser	Ҫ�����User
	virtual void beforeAdd(CWriteableUser *pUser)
	{
		return;
	}
	
	///����󴥷�
	///@param	pUser	�Ѿ������User
	virtual void afterAdd(CUser *pUser)
	{
		return;
	}

	///����ǰ����	
	///@param	pUser	��ˢ�µ�CUser
	///@param	pNewUser	�µ�ֵ
	virtual void beforeUpdate(CUser *pUser, CWriteableUser *pNewUser)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pUser	��ˢ�µ�CUser
	virtual void afterUpdate(CUser *pUser)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pUser	Ҫɾ����CUser
	virtual void beforeRemove(CUser *pUser)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CUserFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserCommitTrigger��ȷ���û���ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserCommitTrigger
{
public:
	///���췽��
	CUserCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CUserCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CUserFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pUser	�Ѿ������User
	virtual void commitAdd(CUser *pUser)
	{
		return;
	}

	///���º󴥷�
	///@param	pUser	��ˢ�µ�CUser
	///@param	poldUser	ԭ����ֵ
	virtual void commitUpdate(CUser *pUser, CWriteableUser *pOldUser)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pUser	�Ѿ�ɾ����CUser
	virtual void commitRemove(CWriteableUser *pUser)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CUserFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserIterator��һ�����û����ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIterator
{
public:
	///���췽��
	CUserIterator(void)
	{
	}

	///���췽��
	CUserIterator(CUserFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��User
	///@return	��һ����������CUser������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUser *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CUserFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUser ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUser * pUser,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CUserFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableUserInvestor��һ���洢�û�Ͷ���߹�ϵ��Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableUserInvestor
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! UserID.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! GrantFuncSet.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableUserInvestor *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///�����û�����
	CUserIDType UserID;
	///Ͷ���߱��
	CInvestorIDType InvestorID;
	///��Ȩ���ܼ�
	CGrantFuncSetType GrantFuncSet;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableUserInvestor CUserInvestor;

/////////////////////////////////////////////////////////////////////////
///CUserInvestorActionTrigger�ǲ����û�Ͷ���߹�ϵ��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorActionTrigger
{
public:
	///���췽��
	CUserInvestorActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CUserInvestorActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CUserInvestorFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pUserInvestor	Ҫ�����UserInvestor
	virtual void beforeAdd(CWriteableUserInvestor *pUserInvestor)
	{
		return;
	}
	
	///����󴥷�
	///@param	pUserInvestor	�Ѿ������UserInvestor
	virtual void afterAdd(CUserInvestor *pUserInvestor)
	{
		return;
	}

	///����ǰ����	
	///@param	pUserInvestor	��ˢ�µ�CUserInvestor
	///@param	pNewUserInvestor	�µ�ֵ
	virtual void beforeUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pUserInvestor	��ˢ�µ�CUserInvestor
	virtual void afterUpdate(CUserInvestor *pUserInvestor)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pUserInvestor	Ҫɾ����CUserInvestor
	virtual void beforeRemove(CUserInvestor *pUserInvestor)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CUserInvestorFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorCommitTrigger��ȷ���û�Ͷ���߹�ϵ��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorCommitTrigger
{
public:
	///���췽��
	CUserInvestorCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CUserInvestorCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CUserInvestorFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pUserInvestor	�Ѿ������UserInvestor
	virtual void commitAdd(CUserInvestor *pUserInvestor)
	{
		return;
	}

	///���º󴥷�
	///@param	pUserInvestor	��ˢ�µ�CUserInvestor
	///@param	poldUserInvestor	ԭ����ֵ
	virtual void commitUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pOldUserInvestor)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pUserInvestor	�Ѿ�ɾ����CUserInvestor
	virtual void commitRemove(CWriteableUserInvestor *pUserInvestor)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CUserInvestorFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorIterator��һ�����û�Ͷ���߹�ϵ���ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorIterator
{
public:
	///���췽��
	CUserInvestorIterator(void)
	{
	}

	///���췽��
	CUserInvestorIterator(CUserInvestorFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserInvestorIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��UserInvestor
	///@return	��һ����������CUserInvestor������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserInvestor *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CUserInvestorFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUserInvestor ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserInvestor * pUserInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CUserInvestorFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableOrderInsertFailed��һ���洢����Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableOrderInsertFailed
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! ExchangeID.isValid())
			return 0;
		if (! OrderSysID.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! UserID.isValid())
			return 0;
		if (! InstrumentID.isValid())
			return 0;
		if (! UserOrderLocalID.isValid())
			return 0;
		if (! OrderPriceType.isValid())
			return 0;
		if (! Direction.isValid())
			return 0;
		if (! OffsetFlag.isValid())
			return 0;
		if (! HedgeFlag.isValid())
			return 0;
		if (! LimitPrice.isValid())
			return 0;
		if (! Volume.isValid())
			return 0;
		if (! TimeCondition.isValid())
			return 0;
		if (! GTDDate.isValid())
			return 0;
		if (! VolumeCondition.isValid())
			return 0;
		if (! MinVolume.isValid())
			return 0;
		if (! StopPrice.isValid())
			return 0;
		if (! ForceCloseReason.isValid())
			return 0;
		if (! IsAutoSuspend.isValid())
			return 0;
		if (! BusinessUnit.isValid())
			return 0;
		if (! UserCustom.isValid())
			return 0;
		if (! BranchID.isValid())
			return 0;
		if (! RecNum.isValid())
			return 0;
		if (! BusinessType.isValid())
			return 0;
		if (! TradingDay.isValid())
			return 0;
		if (! ParticipantID.isValid())
			return 0;
		if (! ClientID.isValid())
			return 0;
		if (! SeatID.isValid())
			return 0;
		if (! InsertTime.isValid())
			return 0;
		if (! OrderLocalID.isValid())
			return 0;
		if (! OrderSource.isValid())
			return 0;
		if (! OrderStatus.isValid())
			return 0;
		if (! CancelTime.isValid())
			return 0;
		if (! CancelUserID.isValid())
			return 0;
		if (! VolumeTraded.isValid())
			return 0;
		if (! VolumeRemain.isValid())
			return 0;
		if (! FrontID.isValid())
			return 0;
		if (! SessionID.isValid())
			return 0;
		if (! FrozenFee.isValid())
			return 0;
		if (! FrozenMargin.isValid())
			return 0;
		if (! FrozenPremium.isValid())
			return 0;
		if (! AccountID.isValid())
			return 0;
		if (! OrderUserID.isValid())
			return 0;
		if (! TradeType.isValid())
			return 0;
		if (! DealFlag.isValid())
			return 0;
		if (! TradeCommision.isValid())
			return 0;
		if (! TradeAmnt.isValid())
			return 0;
		if (! CancleVolume.isValid())
			return 0;
		if (! RequestID.isValid())
			return 0;
		if (! APIID.isValid())
			return 0;
		if (! IPAddress.isValid())
			return 0;
		if (! MacAddress.isValid())
			return 0;
		if (! FTdRecvDown.isValid())
			return 0;
		if (! CoreRecvDown.isValid())
			return 0;
		if (! CoreSendUp.isValid())
			return 0;
		if (! CoreRecvUp.isValid())
			return 0;
		if (! CoreSendDown.isValid())
			return 0;
		if (! FTdSendDown.isValid())
			return 0;
		if (! MarginCombType.isValid())
			return 0;
		if (! InstrumentGroupID.isValid())
			return 0;
		if (! ErrorMsg.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableOrderInsertFailed *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///����������
	CExchangeIDType ExchangeID;
	///ϵͳ�������
	COrderSysIDType OrderSysID;
	///Ͷ���߱��
	CInvestorIDType InvestorID;
	///�û�����
	CUserIDType UserID;
	///��Լ����
	CInstrumentIDType InstrumentID;
	///�û����ر�����
	CUserOrderLocalIDType UserOrderLocalID;
	///�۸�����
	COrderPriceTypeType OrderPriceType;
	///��������
	CDirectionType Direction;
	///��ƽ��־
	COffsetFlagType OffsetFlag;
	///Ͷ���ױ���־
	CHedgeFlagType HedgeFlag;
	///�۸�
	CPriceType LimitPrice;
	///����
	CVolumeType Volume;
	///��Ч������
	CTimeConditionType TimeCondition;
	///GTD����
	CDateType GTDDate;
	///�ɽ�������
	CVolumeConditionType VolumeCondition;
	///��С�ɽ���
	CVolumeType MinVolume;
	///ֹ���
	CPriceType StopPrice;
	///ǿƽԭ��
	CForceCloseReasonType ForceCloseReason;
	///�Զ������־
	CBoolType IsAutoSuspend;
	///ҵ��Ԫ
	CBusinessUnitType BusinessUnit;
	///�û��Զ�����
	CCustomType UserCustom;
	///Ӫҵ������
	CBranchIDType BranchID;
	///��¼���
	CSequenceNoType RecNum;
	///ҵ�����
	CBusinessTypeType BusinessType;
	///������
	CTradingDayType TradingDay;
	///��Ա���
	CParticipantIDType ParticipantID;
	///�ͻ���
	CClientIDType ClientID;
	///�µ�ϯλ��
	CSeatIDType SeatID;
	///����ʱ��
	CTimeType InsertTime;
	///���ر������
	COrderLocalIDType OrderLocalID;
	///������Դ
	COrderSourceType OrderSource;
	///����״̬
	COrderStatusType OrderStatus;
	///����ʱ��
	CTimeType CancelTime;
	///�����û����
	CUserIDType CancelUserID;
	///��ɽ�����
	CVolumeType VolumeTraded;
	///ʣ������
	CVolumeType VolumeRemain;
	///ǰ�ñ��
	CFrontIDType FrontID;
	///�Ự���
	CSessionIDType SessionID;
	///����������
	CMoneyType FrozenFee;
	///����ı�֤��
	CMoneyType FrozenMargin;
	///��ȨȨ������֧
	CMoneyType FrozenPremium;
	///�ʽ��ʺ�
	CAccountIDType AccountID;
	///�µ��û����
	CUserIDType OrderUserID;
	///��������
	CTradeTypeType TradeType;
	///�����־
	CDealFlagType DealFlag;
	///�ѳɽ�Ӷ��
	CMoneyType TradeCommision;
	///�ɽ����
	CMoneyType TradeAmnt;
	///��������
	CVolumeType CancleVolume;
	///������
	CRequestIDType RequestID;
	///ͨ����Ӧ��APIID
	CNumberType APIID;
	///�µ�IP��ַ
	CIPAddressType IPAddress;
	///�µ�MAC��ַ
	CMacAddressType MacAddress;
	///Ftdengine�����²�ʱ���
	CILocalTimeType FTdRecvDown;
	///�����²�ʱ���
	CILocalTimeType CoreRecvDown;
	///�����ϲ�ʱ���
	CILocalTimeType CoreSendUp;
	///�����ϲ�ʱ���
	CILocalTimeType CoreRecvUp;
	///�����²�ʱ���
	CILocalTimeType CoreSendDown;
	///Ftdengine�����²�ʱ���
	CILocalTimeType FTdSendDown;
	///��֤���������
	CClientMarginCombTypeType MarginCombType;
	///��Լ�����
	CInstrumentGroupIDType InstrumentGroupID;
	///������Ϣ
	CErrorMsgType ErrorMsg;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	
	///�����Ӧ���ʻ���ָ��
	///@param	pFactory	�����Ӧ���ʻ���ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ���ʻ���ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorAccount *linkInvestorAccount(CInvestorAccountFactory *pFactory) const;

	///�����Ӧ���ʻ�ָ��
	///@param	pInvestorAccount	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorAccount
	const CWriteableInvestorAccount *linkInvestorAccount(const CWriteableInvestorAccount *pInvestorAccount) const
	{
		void *target=(void *)(&(this->pInvestorAccount));
		*((const CWriteableInvestorAccount **)target)=pInvestorAccount;
		return pInvestorAccount;
	}
	
	///��ȡ��Ӧ���ʻ���ָ��
	///@return	�ҵ��Ķ�Ӧ���ʻ���ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorAccount *getInvestorAccount(void) const
	{
		return pInvestorAccount;
	}
	///�����Ӧ�ĺ�Լ�ֲ���Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ�ֲ���Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ�ֲ���Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorPosition *linkInvestorPosition(CInvestorPositionFactory *pFactory) const;

	///�����Ӧ�ĺ�Լ�ֲ���Ϣָ��
	///@param	pInvestorPosition	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorPosition
	const CWriteableInvestorPosition *linkInvestorPosition(const CWriteableInvestorPosition *pInvestorPosition) const
	{
		void *target=(void *)(&(this->pInvestorPosition));
		*((const CWriteableInvestorPosition **)target)=pInvestorPosition;
		return pInvestorPosition;
	}
	
	///��ȡ��Ӧ�ĺ�Լ�ֲ���Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ�ֲ���Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorPosition *getInvestorPosition(void) const
	{
		return pInvestorPosition;
	}
	///�����Ӧ�ĺ�Լ��Ϣ��ָ��
	///@param	pFactory	�����Ӧ�ĺ�Լ��Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ��Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInstrument *linkInstrument(CInstrumentFactory *pFactory) const;

	///�����Ӧ�ĺ�Լ��Ϣָ��
	///@param	pInstrument	Ҫ���ӵ��Ķ���
	///@return	�����pInstrument
	const CWriteableInstrument *linkInstrument(const CWriteableInstrument *pInstrument) const
	{
		void *target=(void *)(&(this->pInstrument));
		*((const CWriteableInstrument **)target)=pInstrument;
		return pInstrument;
	}
	
	///��ȡ��Ӧ�ĺ�Լ��Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ�ĺ�Լ��Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInstrument *getInstrument(void) const
	{
		return pInstrument;
	}
	///�����Ӧ��Ͷ���߱�֤������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ���߱�֤������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ��Ͷ���߱�֤������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorMargin *linkInvestorMargin(CInvestorMarginFactory *pFactory) const;

	///�����Ӧ��Ͷ���߱�֤������Ϣָ��
	///@param	pInvestorMargin	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorMargin
	const CWriteableInvestorMargin *linkInvestorMargin(const CWriteableInvestorMargin *pInvestorMargin) const
	{
		void *target=(void *)(&(this->pInvestorMargin));
		*((const CWriteableInvestorMargin **)target)=pInvestorMargin;
		return pInvestorMargin;
	}
	
	///��ȡ��Ӧ��Ͷ���߱�֤������Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ��Ͷ���߱�֤������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorMargin *getInvestorMargin(void) const
	{
		return pInvestorMargin;
	}
	///�����Ӧ��Ͷ��������������Ϣ��ָ��
	///@param	pFactory	�����Ӧ��Ͷ��������������Ϣ��ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ��Ͷ��������������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteableInvestorFee *linkInvestorFee(CInvestorFeeFactory *pFactory) const;

	///�����Ӧ��Ͷ��������������Ϣָ��
	///@param	pInvestorFee	Ҫ���ӵ��Ķ���
	///@return	�����pInvestorFee
	const CWriteableInvestorFee *linkInvestorFee(const CWriteableInvestorFee *pInvestorFee) const
	{
		void *target=(void *)(&(this->pInvestorFee));
		*((const CWriteableInvestorFee **)target)=pInvestorFee;
		return pInvestorFee;
	}
	
	///��ȡ��Ӧ��Ͷ��������������Ϣ��ָ��
	///@return	�ҵ��Ķ�Ӧ��Ͷ��������������Ϣ��ָ�룬����Ҳ����򷵻�NULL
	const CWriteableInvestorFee *getInvestorFee(void) const
	{
		return pInvestorFee;
	}

private:
	///��Ӧ���ʻ�
	const CWriteableInvestorAccount *pInvestorAccount;
	///��Ӧ�ĺ�Լ�ֲ���Ϣ
	const CWriteableInvestorPosition *pInvestorPosition;
	///��Ӧ�ĺ�Լ��Ϣ
	const CWriteableInstrument *pInstrument;
	///��Ӧ��Ͷ���߱�֤������Ϣ
	const CWriteableInvestorMargin *pInvestorMargin;
	///��Ӧ��Ͷ��������������Ϣ
	const CWriteableInvestorFee *pInvestorFee;
};

typedef const CWriteableOrderInsertFailed COrderInsertFailed;

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedActionTrigger�ǲ�������ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedActionTrigger
{
public:
	///���췽��
	COrderInsertFailedActionTrigger(void)
	{
	}
	
	///��������
	virtual ~COrderInsertFailedActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(COrderInsertFailedFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pOrderInsertFailed	Ҫ�����OrderInsertFailed
	virtual void beforeAdd(CWriteableOrderInsertFailed *pOrderInsertFailed)
	{
		return;
	}
	
	///����󴥷�
	///@param	pOrderInsertFailed	�Ѿ������OrderInsertFailed
	virtual void afterAdd(COrderInsertFailed *pOrderInsertFailed)
	{
		return;
	}

	///����ǰ����	
	///@param	pOrderInsertFailed	��ˢ�µ�COrderInsertFailed
	///@param	pNewOrderInsertFailed	�µ�ֵ
	virtual void beforeUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pOrderInsertFailed	��ˢ�µ�COrderInsertFailed
	virtual void afterUpdate(COrderInsertFailed *pOrderInsertFailed)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pOrderInsertFailed	Ҫɾ����COrderInsertFailed
	virtual void beforeRemove(COrderInsertFailed *pOrderInsertFailed)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	COrderInsertFailedFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedCommitTrigger��ȷ�ϴ���ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedCommitTrigger
{
public:
	///���췽��
	COrderInsertFailedCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~COrderInsertFailedCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(COrderInsertFailedFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pOrderInsertFailed	�Ѿ������OrderInsertFailed
	virtual void commitAdd(COrderInsertFailed *pOrderInsertFailed)
	{
		return;
	}

	///���º󴥷�
	///@param	pOrderInsertFailed	��ˢ�µ�COrderInsertFailed
	///@param	poldOrderInsertFailed	ԭ����ֵ
	virtual void commitUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pOldOrderInsertFailed)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pOrderInsertFailed	�Ѿ�ɾ����COrderInsertFailed
	virtual void commitRemove(CWriteableOrderInsertFailed *pOrderInsertFailed)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	COrderInsertFailedFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedIterator��һ���Դ����ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedIterator
{
public:
	///���췽��
	COrderInsertFailedIterator(void)
	{
	}

	///���췽��
	COrderInsertFailedIterator(COrderInsertFailedFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~COrderInsertFailedIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��OrderInsertFailed
	///@return	��һ����������COrderInsertFailed������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrderInsertFailed *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	COrderInsertFailedFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrderInsertFailed ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrderInsertFailed * pOrderInsertFailed,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	COrderInsertFailedFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableUserTradingRight��һ���洢�û�����Ȩ�ޱ�Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableUserTradingRight
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! ExchangeID.isValid())
			return 0;
		if (! InstrumentID.isValid())
			return 0;
		if (! UserID.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! TradingRight.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableUserTradingRight *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///����������
	CExchangeIDType ExchangeID;
	///��Լ����
	CInstrumentIDType InstrumentID;
	///�û�����
	CUserIDType UserID;
	///Ͷ���߱��
	CInvestorIDType InvestorID;
	///��Լ����Ȩ��
	CTradingRightType TradingRight;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableUserTradingRight CUserTradingRight;

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightActionTrigger�ǲ����û�����Ȩ�ޱ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightActionTrigger
{
public:
	///���췽��
	CUserTradingRightActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CUserTradingRightActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CUserTradingRightFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pUserTradingRight	Ҫ�����UserTradingRight
	virtual void beforeAdd(CWriteableUserTradingRight *pUserTradingRight)
	{
		return;
	}
	
	///����󴥷�
	///@param	pUserTradingRight	�Ѿ������UserTradingRight
	virtual void afterAdd(CUserTradingRight *pUserTradingRight)
	{
		return;
	}

	///����ǰ����	
	///@param	pUserTradingRight	��ˢ�µ�CUserTradingRight
	///@param	pNewUserTradingRight	�µ�ֵ
	virtual void beforeUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pUserTradingRight	��ˢ�µ�CUserTradingRight
	virtual void afterUpdate(CUserTradingRight *pUserTradingRight)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pUserTradingRight	Ҫɾ����CUserTradingRight
	virtual void beforeRemove(CUserTradingRight *pUserTradingRight)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CUserTradingRightFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightCommitTrigger��ȷ���û�����Ȩ�ޱ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightCommitTrigger
{
public:
	///���췽��
	CUserTradingRightCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CUserTradingRightCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CUserTradingRightFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pUserTradingRight	�Ѿ������UserTradingRight
	virtual void commitAdd(CUserTradingRight *pUserTradingRight)
	{
		return;
	}

	///���º󴥷�
	///@param	pUserTradingRight	��ˢ�µ�CUserTradingRight
	///@param	poldUserTradingRight	ԭ����ֵ
	virtual void commitUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pOldUserTradingRight)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pUserTradingRight	�Ѿ�ɾ����CUserTradingRight
	virtual void commitRemove(CWriteableUserTradingRight *pUserTradingRight)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CUserTradingRightFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightIterator��һ�����û�����Ȩ�ޱ��ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightIterator
{
public:
	///���췽��
	CUserTradingRightIterator(void)
	{
	}

	///���췽��
	CUserTradingRightIterator(CUserTradingRightFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserTradingRightIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��UserTradingRight
	///@return	��һ����������CUserTradingRight������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserTradingRight *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CUserTradingRightFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUserTradingRight ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserTradingRight * pUserTradingRight,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CUserTradingRightFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableCurrentTime��һ���洢��ǰʱ��Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableCurrentTime
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! CurrDate.isValid())
			return 0;
		if (! CurrTime.isValid())
			return 0;
		if (! CurrMillisec.isValid())
			return 0;
		if (! OldTime.isValid())
			return 0;
		if (! OldMillisec.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableCurrentTime *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///��ǰ����
	CDateType CurrDate;
	///��ǰʱ��
	CTimeType CurrTime;
	///��ǰʱ�䣨���룩
	CMillisecType CurrMillisec;
	///ԭ��ʱ��
	CTimeType OldTime;
	///ԭ��ʱ�䣨���룩
	CMillisecType OldMillisec;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableCurrentTime CCurrentTime;

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeActionTrigger�ǲ�����ǰʱ��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeActionTrigger
{
public:
	///���췽��
	CCurrentTimeActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CCurrentTimeActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CCurrentTimeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pCurrentTime	Ҫ�����CurrentTime
	virtual void beforeAdd(CWriteableCurrentTime *pCurrentTime)
	{
		return;
	}
	
	///����󴥷�
	///@param	pCurrentTime	�Ѿ������CurrentTime
	virtual void afterAdd(CCurrentTime *pCurrentTime)
	{
		return;
	}

	///����ǰ����	
	///@param	pCurrentTime	��ˢ�µ�CCurrentTime
	///@param	pNewCurrentTime	�µ�ֵ
	virtual void beforeUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pCurrentTime	��ˢ�µ�CCurrentTime
	virtual void afterUpdate(CCurrentTime *pCurrentTime)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pCurrentTime	Ҫɾ����CCurrentTime
	virtual void beforeRemove(CCurrentTime *pCurrentTime)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CCurrentTimeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeCommitTrigger��ȷ�ϵ�ǰʱ��ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeCommitTrigger
{
public:
	///���췽��
	CCurrentTimeCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CCurrentTimeCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CCurrentTimeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pCurrentTime	�Ѿ������CurrentTime
	virtual void commitAdd(CCurrentTime *pCurrentTime)
	{
		return;
	}

	///���º󴥷�
	///@param	pCurrentTime	��ˢ�µ�CCurrentTime
	///@param	poldCurrentTime	ԭ����ֵ
	virtual void commitUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pOldCurrentTime)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pCurrentTime	�Ѿ�ɾ����CCurrentTime
	virtual void commitRemove(CWriteableCurrentTime *pCurrentTime)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CCurrentTimeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeIterator��һ���Ե�ǰʱ���ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeIterator
{
public:
	///���췽��
	CCurrentTimeIterator(void)
	{
	}

	///���췽��
	CCurrentTimeIterator(CCurrentTimeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CCurrentTimeIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��CurrentTime
	///@return	��һ����������CCurrentTime������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CCurrentTime *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CCurrentTimeFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pCurrentTime ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableCurrentTime * pCurrentTime,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CCurrentTimeFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableUserSession��һ���洢����Ա���߻Ự�Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableUserSession
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! UserID.isValid())
			return 0;
		if (! UserType.isValid())
			return 0;
		if (! SessionID.isValid())
			return 0;
		if (! FrontID.isValid())
			return 0;
		if (! LoginTime.isValid())
			return 0;
		if (! IPAddress.isValid())
			return 0;
		if (! MacAddress.isValid())
			return 0;
		if (! UserProductInfo.isValid())
			return 0;
		if (! InterfaceProductInfo.isValid())
			return 0;
		if (! ProtocolInfo.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableUserSession *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾����
	CBrokerIDType BrokerID;
	///�����û�����
	CUserIDType UserID;
	///�����û�����
	CUserTypeType UserType;
	///�Ự���
	CSessionIDType SessionID;
	///ǰ�ñ��
	CFrontIDType FrontID;
	///��¼ʱ��
	CTimeType LoginTime;
	///IP��ַ
	CIPAddressType IPAddress;
	///Mac��ַ
	CMacAddressType MacAddress;
	///�û��˲�Ʒ��Ϣ
	CProductInfoType UserProductInfo;
	///�ӿڶ˲�Ʒ��Ϣ
	CProductInfoType InterfaceProductInfo;
	///Э����Ϣ
	CProtocolInfoType ProtocolInfo;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableUserSession CUserSession;

/////////////////////////////////////////////////////////////////////////
///CUserSessionActionTrigger�ǲ�������Ա���߻Ựʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionActionTrigger
{
public:
	///���췽��
	CUserSessionActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CUserSessionActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CUserSessionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pUserSession	Ҫ�����UserSession
	virtual void beforeAdd(CWriteableUserSession *pUserSession)
	{
		return;
	}
	
	///����󴥷�
	///@param	pUserSession	�Ѿ������UserSession
	virtual void afterAdd(CUserSession *pUserSession)
	{
		return;
	}

	///����ǰ����	
	///@param	pUserSession	��ˢ�µ�CUserSession
	///@param	pNewUserSession	�µ�ֵ
	virtual void beforeUpdate(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pUserSession	��ˢ�µ�CUserSession
	virtual void afterUpdate(CUserSession *pUserSession)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pUserSession	Ҫɾ����CUserSession
	virtual void beforeRemove(CUserSession *pUserSession)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CUserSessionFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionCommitTrigger��ȷ�Ͻ���Ա���߻Ựʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionCommitTrigger
{
public:
	///���췽��
	CUserSessionCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CUserSessionCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CUserSessionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pUserSession	�Ѿ������UserSession
	virtual void commitAdd(CUserSession *pUserSession)
	{
		return;
	}

	///���º󴥷�
	///@param	pUserSession	��ˢ�µ�CUserSession
	///@param	poldUserSession	ԭ����ֵ
	virtual void commitUpdate(CUserSession *pUserSession, CWriteableUserSession *pOldUserSession)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pUserSession	�Ѿ�ɾ����CUserSession
	virtual void commitRemove(CWriteableUserSession *pUserSession)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CUserSessionFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionIterator��һ���Խ���Ա���߻Ự��ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionIterator
{
public:
	///���췽��
	CUserSessionIterator(void)
	{
	}

	///���췽��
	CUserSessionIterator(CUserSessionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserSessionIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��UserSession
	///@return	��һ����������CUserSession������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserSession *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CUserSessionFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUserSession ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserSession * pUserSession,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CUserSessionFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableMaxLocalID��һ���洢��󱾵ر����ŵĶ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableMaxLocalID
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! UserID.isValid())
			return 0;
		if (! MaxOrderLocalID.isValid())
			return 0;
		if (! FrontID.isValid())
			return 0;
		if (! SessionID.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableMaxLocalID *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾����
	CBrokerIDType BrokerID;
	///�����û�����
	CUserIDType UserID;
	///��󱨵����ر��
	CUserOrderLocalIDType MaxOrderLocalID;
	///ǰ�ñ��
	CFrontIDType FrontID;
	///�Ự���
	CSessionIDType SessionID;
	
	unsigned int HashFrontIDSessionID;
	
	///����FrontIDSessionID��hashֵ
	void calHashFrontIDSessionID(void)
	{
		unsigned key=0;
		key=FrontID.hash(key);
		key=SessionID.hash(key);
		HashFrontIDSessionID=key;
	}
	
	///������Ҫ���������FrontIDSessionID��hashֵ
	void updateHashFrontIDSessionID(void)
	{
	}
	
	///�������е�hashֵ
	void calAllHash(void)
	{
		calHashFrontIDSessionID();
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
		updateHashFrontIDSessionID();
	}
	

private:
};

typedef const CWriteableMaxLocalID CMaxLocalID;

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDActionTrigger�ǲ�����󱾵ر�����ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDActionTrigger
{
public:
	///���췽��
	CMaxLocalIDActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CMaxLocalIDActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CMaxLocalIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pMaxLocalID	Ҫ�����MaxLocalID
	virtual void beforeAdd(CWriteableMaxLocalID *pMaxLocalID)
	{
		return;
	}
	
	///����󴥷�
	///@param	pMaxLocalID	�Ѿ������MaxLocalID
	virtual void afterAdd(CMaxLocalID *pMaxLocalID)
	{
		return;
	}

	///����ǰ����	
	///@param	pMaxLocalID	��ˢ�µ�CMaxLocalID
	///@param	pNewMaxLocalID	�µ�ֵ
	virtual void beforeUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pMaxLocalID	��ˢ�µ�CMaxLocalID
	virtual void afterUpdate(CMaxLocalID *pMaxLocalID)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pMaxLocalID	Ҫɾ����CMaxLocalID
	virtual void beforeRemove(CMaxLocalID *pMaxLocalID)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CMaxLocalIDFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDCommitTrigger��ȷ����󱾵ر�����ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDCommitTrigger
{
public:
	///���췽��
	CMaxLocalIDCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CMaxLocalIDCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CMaxLocalIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pMaxLocalID	�Ѿ������MaxLocalID
	virtual void commitAdd(CMaxLocalID *pMaxLocalID)
	{
		return;
	}

	///���º󴥷�
	///@param	pMaxLocalID	��ˢ�µ�CMaxLocalID
	///@param	poldMaxLocalID	ԭ����ֵ
	virtual void commitUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pOldMaxLocalID)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pMaxLocalID	�Ѿ�ɾ����CMaxLocalID
	virtual void commitRemove(CWriteableMaxLocalID *pMaxLocalID)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CMaxLocalIDFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDIterator��һ������󱾵ر����ŵ�ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDIterator
{
public:
	///���췽��
	CMaxLocalIDIterator(void)
	{
	}

	///���췽��
	CMaxLocalIDIterator(CMaxLocalIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CMaxLocalIDIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��MaxLocalID
	///@return	��һ����������CMaxLocalID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CMaxLocalID *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CMaxLocalIDFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pMaxLocalID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableMaxLocalID * pMaxLocalID,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CMaxLocalIDFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableBrkUserIDLocalID��һ���洢�û����ر����ŵĶ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableBrkUserIDLocalID
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! UserID.isValid())
			return 0;
		if (! UserOrderLocalID.isValid())
			return 0;
		if (! APIID.isValid())
			return 0;
		if (! OrderLocalID.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableBrkUserIDLocalID *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾����
	CBrokerIDType BrokerID;
	///�����û�����
	CUserIDType UserID;
	///�û����ر��
	CUserOrderLocalIDType UserOrderLocalID;
	///ͨ����Ӧ��APIID
	CNumberType APIID;
	///���ر������
	COrderLocalIDType OrderLocalID;
	
	unsigned int HashBrokerIDUserIDLocalID;
	
	///����BrokerIDUserIDLocalID��hashֵ
	void calHashBrokerIDUserIDLocalID(void)
	{
		unsigned key=0;
		key=BrokerID.hash(key);
		key=UserID.hash(key);
		key=UserOrderLocalID.hash(key);
		HashBrokerIDUserIDLocalID=key;
	}
	
	///������Ҫ���������BrokerIDUserIDLocalID��hashֵ
	void updateHashBrokerIDUserIDLocalID(void)
	{
	}
	
	///�������е�hashֵ
	void calAllHash(void)
	{
		calHashBrokerIDUserIDLocalID();
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
		updateHashBrokerIDUserIDLocalID();
	}
	
	///�����Ӧ�ı�����ָ��
	///@param	pFactory	�����Ӧ�ı�����ָ��ʱ��Ѱ�ҵĶ��󹤳�
	///@return	�ҵ��Ķ�Ӧ�ı�����ָ�룬����Ҳ����򷵻�NULL
	inline const CWriteablePreOrder *linkPreOrder(CPreOrderFactory *pFactory) const;

	///�����Ӧ�ı���ָ��
	///@param	pPreOrder	Ҫ���ӵ��Ķ���
	///@return	�����pPreOrder
	const CWriteablePreOrder *linkPreOrder(const CWriteablePreOrder *pPreOrder) const
	{
		void *target=(void *)(&(this->pPreOrder));
		*((const CWriteablePreOrder **)target)=pPreOrder;
		return pPreOrder;
	}
	
	///��ȡ��Ӧ�ı�����ָ��
	///@return	�ҵ��Ķ�Ӧ�ı�����ָ�룬����Ҳ����򷵻�NULL
	const CWriteablePreOrder *getPreOrder(void) const
	{
		return pPreOrder;
	}

private:
	///��Ӧ�ı���
	const CWriteablePreOrder *pPreOrder;
};

typedef const CWriteableBrkUserIDLocalID CBrkUserIDLocalID;

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDActionTrigger�ǲ����û����ر�����ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDActionTrigger
{
public:
	///���췽��
	CBrkUserIDLocalIDActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CBrkUserIDLocalIDActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CBrkUserIDLocalIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pBrkUserIDLocalID	Ҫ�����BrkUserIDLocalID
	virtual void beforeAdd(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return;
	}
	
	///����󴥷�
	///@param	pBrkUserIDLocalID	�Ѿ������BrkUserIDLocalID
	virtual void afterAdd(CBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return;
	}

	///����ǰ����	
	///@param	pBrkUserIDLocalID	��ˢ�µ�CBrkUserIDLocalID
	///@param	pNewBrkUserIDLocalID	�µ�ֵ
	virtual void beforeUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pBrkUserIDLocalID	��ˢ�µ�CBrkUserIDLocalID
	virtual void afterUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pBrkUserIDLocalID	Ҫɾ����CBrkUserIDLocalID
	virtual void beforeRemove(CBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CBrkUserIDLocalIDFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDCommitTrigger��ȷ���û����ر�����ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDCommitTrigger
{
public:
	///���췽��
	CBrkUserIDLocalIDCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CBrkUserIDLocalIDCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CBrkUserIDLocalIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pBrkUserIDLocalID	�Ѿ������BrkUserIDLocalID
	virtual void commitAdd(CBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return;
	}

	///���º󴥷�
	///@param	pBrkUserIDLocalID	��ˢ�µ�CBrkUserIDLocalID
	///@param	poldBrkUserIDLocalID	ԭ����ֵ
	virtual void commitUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pOldBrkUserIDLocalID)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pBrkUserIDLocalID	�Ѿ�ɾ����CBrkUserIDLocalID
	virtual void commitRemove(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CBrkUserIDLocalIDFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDIterator��һ�����û����ر����ŵ�ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDIterator
{
public:
	///���췽��
	CBrkUserIDLocalIDIterator(void)
	{
	}

	///���췽��
	CBrkUserIDLocalIDIterator(CBrkUserIDLocalIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CBrkUserIDLocalIDIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��BrkUserIDLocalID
	///@return	��һ����������CBrkUserIDLocalID������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CBrkUserIDLocalID *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CBrkUserIDLocalIDFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pBrkUserIDLocalID ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableBrkUserIDLocalID * pBrkUserIDLocalID,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CBrkUserIDLocalIDFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteablePartClientInsGroupPosition��һ���洢�ͻ���Լ��ֱֲ�Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteablePartClientInsGroupPosition
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! ParticipantID.isValid())
			return 0;
		if (! ClientID.isValid())
			return 0;
		if (! InstrumentGroupID.isValid())
			return 0;
		if (! LongPosition.isValid())
			return 0;
		if (! LongMargin.isValid())
			return 0;
		if (! ShortPosition.isValid())
			return 0;
		if (! ShortMargin.isValid())
			return 0;
		if (! ActualMargin .isValid())
			return 0;
		if (! LongFrozenPosition.isValid())
			return 0;
		if (! LongFrozenMargin.isValid())
			return 0;
		if (! ShortFrozenPosition.isValid())
			return 0;
		if (! ShortFrozenMargin.isValid())
			return 0;
		if (! ActualFrozenMargin .isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteablePartClientInsGroupPosition *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///��Ա����
	CParticipantIDType ParticipantID;
	///�ͻ�����
	CClientIDType ClientID;
	///��Լ�����
	CInstrumentGroupIDType InstrumentGroupID;
	///��Լ���ͷ�ֲܳ�
	CVolumeType LongPosition;
	///��Լ���ͷ��֤��֮��
	CMoneyType LongMargin;
	///��Լ���ͷ�ֲܳ�
	CVolumeType ShortPosition;
	///��Լ���ͷ��֤��֮��
	CMoneyType ShortMargin;
	///ʵ����ȡ�ı�֤��
	CMoneyType ActualMargin ;
	///��Լ���ͷ�����ֲܳ�
	CVolumeType LongFrozenPosition;
	///��Լ���ͷ���ᱣ֤��֮��
	CMoneyType LongFrozenMargin;
	///��Լ���ͷ�����ֲܳ�
	CVolumeType ShortFrozenPosition;
	///��Լ���ͷ���ᱣ֤��֮��
	CMoneyType ShortFrozenMargin;
	///ʵ�ʶ���ı�֤��
	CMoneyType ActualFrozenMargin ;
	
	unsigned int HashPartClientAndInsGroup;
	
	///����PartClientAndInsGroup��hashֵ
	void calHashPartClientAndInsGroup(void)
	{
		unsigned key=0;
		key=BrokerID.hash(key);
		key=ClientID.hash(key);
		key=InstrumentGroupID.hash(key);
		HashPartClientAndInsGroup=key;
	}
	
	///������Ҫ���������PartClientAndInsGroup��hashֵ
	void updateHashPartClientAndInsGroup(void)
	{
	}
	
	///�������е�hashֵ
	void calAllHash(void)
	{
		calHashPartClientAndInsGroup();
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
		updateHashPartClientAndInsGroup();
	}
	

private:
};

typedef const CWriteablePartClientInsGroupPosition CPartClientInsGroupPosition;

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionActionTrigger�ǲ����ͻ���Լ��ֱֲ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionActionTrigger
{
public:
	///���췽��
	CPartClientInsGroupPositionActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CPartClientInsGroupPositionActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CPartClientInsGroupPositionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pPartClientInsGroupPosition	Ҫ�����PartClientInsGroupPosition
	virtual void beforeAdd(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return;
	}
	
	///����󴥷�
	///@param	pPartClientInsGroupPosition	�Ѿ������PartClientInsGroupPosition
	virtual void afterAdd(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return;
	}

	///����ǰ����	
	///@param	pPartClientInsGroupPosition	��ˢ�µ�CPartClientInsGroupPosition
	///@param	pNewPartClientInsGroupPosition	�µ�ֵ
	virtual void beforeUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pPartClientInsGroupPosition	��ˢ�µ�CPartClientInsGroupPosition
	virtual void afterUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pPartClientInsGroupPosition	Ҫɾ����CPartClientInsGroupPosition
	virtual void beforeRemove(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CPartClientInsGroupPositionFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionCommitTrigger��ȷ�Ͽͻ���Լ��ֱֲ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionCommitTrigger
{
public:
	///���췽��
	CPartClientInsGroupPositionCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CPartClientInsGroupPositionCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CPartClientInsGroupPositionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pPartClientInsGroupPosition	�Ѿ������PartClientInsGroupPosition
	virtual void commitAdd(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return;
	}

	///���º󴥷�
	///@param	pPartClientInsGroupPosition	��ˢ�µ�CPartClientInsGroupPosition
	///@param	poldPartClientInsGroupPosition	ԭ����ֵ
	virtual void commitUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pOldPartClientInsGroupPosition)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pPartClientInsGroupPosition	�Ѿ�ɾ����CPartClientInsGroupPosition
	virtual void commitRemove(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CPartClientInsGroupPositionFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionIterator��һ���Կͻ���Լ��ֱֲ��ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionIterator
{
public:
	///���췽��
	CPartClientInsGroupPositionIterator(void)
	{
	}

	///���췽��
	CPartClientInsGroupPositionIterator(CPartClientInsGroupPositionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CPartClientInsGroupPositionIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��PartClientInsGroupPosition
	///@return	��һ����������CPartClientInsGroupPosition������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CPartClientInsGroupPosition *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CPartClientInsGroupPositionFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pPartClientInsGroupPosition ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteablePartClientInsGroupPosition * pPartClientInsGroupPosition,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CPartClientInsGroupPositionFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableClientMarginCombType��һ���洢���ױ�����ϱ�֤�����͵Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableClientMarginCombType
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! ParticipantID.isValid())
			return 0;
		if (! ClientID.isValid())
			return 0;
		if (! InstrumentGroupID.isValid())
			return 0;
		if (! MarginCombType.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableClientMarginCombType *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///��Ա����
	CParticipantIDType ParticipantID;
	///�ͻ�����
	CClientIDType ClientID;
	///��Լ�����
	CInstrumentGroupIDType InstrumentGroupID;
	///��֤���������
	CClientMarginCombTypeType MarginCombType;
	
	unsigned int HashClientAndInsGroup;
	
	///����ClientAndInsGroup��hashֵ
	void calHashClientAndInsGroup(void)
	{
		unsigned key=0;
		key=BrokerID.hash(key);
		key=ClientID.hash(key);
		key=InstrumentGroupID.hash(key);
		HashClientAndInsGroup=key;
	}
	
	///������Ҫ���������ClientAndInsGroup��hashֵ
	void updateHashClientAndInsGroup(void)
	{
	}
	
	///�������е�hashֵ
	void calAllHash(void)
	{
		calHashClientAndInsGroup();
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
		updateHashClientAndInsGroup();
	}
	

private:
};

typedef const CWriteableClientMarginCombType CClientMarginCombType;

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeActionTrigger�ǲ������ױ�����ϱ�֤������ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeActionTrigger
{
public:
	///���췽��
	CClientMarginCombTypeActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CClientMarginCombTypeActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CClientMarginCombTypeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pClientMarginCombType	Ҫ�����ClientMarginCombType
	virtual void beforeAdd(CWriteableClientMarginCombType *pClientMarginCombType)
	{
		return;
	}
	
	///����󴥷�
	///@param	pClientMarginCombType	�Ѿ������ClientMarginCombType
	virtual void afterAdd(CClientMarginCombType *pClientMarginCombType)
	{
		return;
	}

	///����ǰ����	
	///@param	pClientMarginCombType	��ˢ�µ�CClientMarginCombType
	///@param	pNewClientMarginCombType	�µ�ֵ
	virtual void beforeUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pClientMarginCombType	��ˢ�µ�CClientMarginCombType
	virtual void afterUpdate(CClientMarginCombType *pClientMarginCombType)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pClientMarginCombType	Ҫɾ����CClientMarginCombType
	virtual void beforeRemove(CClientMarginCombType *pClientMarginCombType)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CClientMarginCombTypeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeCommitTrigger��ȷ�Ͻ��ױ�����ϱ�֤������ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeCommitTrigger
{
public:
	///���췽��
	CClientMarginCombTypeCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CClientMarginCombTypeCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CClientMarginCombTypeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pClientMarginCombType	�Ѿ������ClientMarginCombType
	virtual void commitAdd(CClientMarginCombType *pClientMarginCombType)
	{
		return;
	}

	///���º󴥷�
	///@param	pClientMarginCombType	��ˢ�µ�CClientMarginCombType
	///@param	poldClientMarginCombType	ԭ����ֵ
	virtual void commitUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pOldClientMarginCombType)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pClientMarginCombType	�Ѿ�ɾ����CClientMarginCombType
	virtual void commitRemove(CWriteableClientMarginCombType *pClientMarginCombType)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CClientMarginCombTypeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeIterator��һ���Խ��ױ�����ϱ�֤�����͵�ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeIterator
{
public:
	///���췽��
	CClientMarginCombTypeIterator(void)
	{
	}

	///���췽��
	CClientMarginCombTypeIterator(CClientMarginCombTypeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CClientMarginCombTypeIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��ClientMarginCombType
	///@return	��һ����������CClientMarginCombType������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CClientMarginCombType *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CClientMarginCombTypeFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pClientMarginCombType ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableClientMarginCombType * pClientMarginCombType,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CClientMarginCombTypeFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInstrumentGroup��һ���洢��Լ�ͺ�Լ���ϵ�Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInstrumentGroup
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! ExchangeID.isValid())
			return 0;
		if (! BrokerID.isValid())
			return 0;
		if (! InstrumentID.isValid())
			return 0;
		if (! InstrumentGroupID.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableInstrumentGroup *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///����������
	CExchangeIDType ExchangeID;
	///���͹�˾���
	CBrokerIDType BrokerID;
	///��Լ����
	CInstrumentIDType InstrumentID;
	///��Լ�����
	CInstrumentGroupIDType InstrumentGroupID;
	
	unsigned int HashBrokerInstrumentID;
	
	///����BrokerInstrumentID��hashֵ
	void calHashBrokerInstrumentID(void)
	{
		unsigned key=0;
		key=ExchangeID.hash(key);
		key=BrokerID.hash(key);
		key=InstrumentID.hash(key);
		HashBrokerInstrumentID=key;
	}
	
	///������Ҫ���������BrokerInstrumentID��hashֵ
	void updateHashBrokerInstrumentID(void)
	{
	}
	
	///�������е�hashֵ
	void calAllHash(void)
	{
		calHashBrokerInstrumentID();
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
		updateHashBrokerInstrumentID();
	}
	

private:
};

typedef const CWriteableInstrumentGroup CInstrumentGroup;

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupActionTrigger�ǲ�����Լ�ͺ�Լ���ϵʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupActionTrigger
{
public:
	///���췽��
	CInstrumentGroupActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CInstrumentGroupActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInstrumentGroupFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pInstrumentGroup	Ҫ�����InstrumentGroup
	virtual void beforeAdd(CWriteableInstrumentGroup *pInstrumentGroup)
	{
		return;
	}
	
	///����󴥷�
	///@param	pInstrumentGroup	�Ѿ������InstrumentGroup
	virtual void afterAdd(CInstrumentGroup *pInstrumentGroup)
	{
		return;
	}

	///����ǰ����	
	///@param	pInstrumentGroup	��ˢ�µ�CInstrumentGroup
	///@param	pNewInstrumentGroup	�µ�ֵ
	virtual void beforeUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pInstrumentGroup	��ˢ�µ�CInstrumentGroup
	virtual void afterUpdate(CInstrumentGroup *pInstrumentGroup)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pInstrumentGroup	Ҫɾ����CInstrumentGroup
	virtual void beforeRemove(CInstrumentGroup *pInstrumentGroup)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInstrumentGroupFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupCommitTrigger��ȷ�Ϻ�Լ�ͺ�Լ���ϵʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupCommitTrigger
{
public:
	///���췽��
	CInstrumentGroupCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CInstrumentGroupCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInstrumentGroupFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pInstrumentGroup	�Ѿ������InstrumentGroup
	virtual void commitAdd(CInstrumentGroup *pInstrumentGroup)
	{
		return;
	}

	///���º󴥷�
	///@param	pInstrumentGroup	��ˢ�µ�CInstrumentGroup
	///@param	poldInstrumentGroup	ԭ����ֵ
	virtual void commitUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pOldInstrumentGroup)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pInstrumentGroup	�Ѿ�ɾ����CInstrumentGroup
	virtual void commitRemove(CWriteableInstrumentGroup *pInstrumentGroup)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInstrumentGroupFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupIterator��һ���Ժ�Լ�ͺ�Լ���ϵ��ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupIterator
{
public:
	///���췽��
	CInstrumentGroupIterator(void)
	{
	}

	///���췽��
	CInstrumentGroupIterator(CInstrumentGroupFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInstrumentGroupIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��InstrumentGroup
	///@return	��һ����������CInstrumentGroup������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInstrumentGroup *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CInstrumentGroupFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInstrumentGroup ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInstrumentGroup * pInstrumentGroup,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CInstrumentGroupFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableSGEDeferRate��һ���洢�������ӷ��ʱ�Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableSGEDeferRate
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! InstrumentID.isValid())
			return 0;
		if (! ExchangeID.isValid())
			return 0;
		if (! TradeDate.isValid())
			return 0;
		if (! Direction.isValid())
			return 0;
		if (! DeferRate.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableSGEDeferRate *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///��Լ����
	CInstrumentIDType InstrumentID;
	///����������
	CExchangeIDType ExchangeID;
	///��������
	CTradingDayType TradeDate;
	///֧������
	CPayDirectionType Direction;
	///���ӷ���
	CRatioType DeferRate;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableSGEDeferRate CSGEDeferRate;

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateActionTrigger�ǲ����������ӷ��ʱ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateActionTrigger
{
public:
	///���췽��
	CSGEDeferRateActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CSGEDeferRateActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CSGEDeferRateFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pSGEDeferRate	Ҫ�����SGEDeferRate
	virtual void beforeAdd(CWriteableSGEDeferRate *pSGEDeferRate)
	{
		return;
	}
	
	///����󴥷�
	///@param	pSGEDeferRate	�Ѿ������SGEDeferRate
	virtual void afterAdd(CSGEDeferRate *pSGEDeferRate)
	{
		return;
	}

	///����ǰ����	
	///@param	pSGEDeferRate	��ˢ�µ�CSGEDeferRate
	///@param	pNewSGEDeferRate	�µ�ֵ
	virtual void beforeUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pSGEDeferRate	��ˢ�µ�CSGEDeferRate
	virtual void afterUpdate(CSGEDeferRate *pSGEDeferRate)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pSGEDeferRate	Ҫɾ����CSGEDeferRate
	virtual void beforeRemove(CSGEDeferRate *pSGEDeferRate)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CSGEDeferRateFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateCommitTrigger��ȷ�Ͻ������ӷ��ʱ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateCommitTrigger
{
public:
	///���췽��
	CSGEDeferRateCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CSGEDeferRateCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CSGEDeferRateFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pSGEDeferRate	�Ѿ������SGEDeferRate
	virtual void commitAdd(CSGEDeferRate *pSGEDeferRate)
	{
		return;
	}

	///���º󴥷�
	///@param	pSGEDeferRate	��ˢ�µ�CSGEDeferRate
	///@param	poldSGEDeferRate	ԭ����ֵ
	virtual void commitUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pOldSGEDeferRate)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pSGEDeferRate	�Ѿ�ɾ����CSGEDeferRate
	virtual void commitRemove(CWriteableSGEDeferRate *pSGEDeferRate)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CSGEDeferRateFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateIterator��һ���Խ������ӷ��ʱ��ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateIterator
{
public:
	///���췽��
	CSGEDeferRateIterator(void)
	{
	}

	///���췽��
	CSGEDeferRateIterator(CSGEDeferRateFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CSGEDeferRateIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��SGEDeferRate
	///@return	��һ����������CSGEDeferRate������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSGEDeferRate *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CSGEDeferRateFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pSGEDeferRate ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSGEDeferRate * pSGEDeferRate,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CSGEDeferRateFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInvestorTradingRight��һ���洢Ͷ���߽���Ȩ�ޱ�Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInvestorTradingRight
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! ExchangeID.isValid())
			return 0;
		if (! InstrumentID.isValid())
			return 0;
		if (! TradingRight.isValid())
			return 0;
		if (! ProductClass.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableInvestorTradingRight *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///Ͷ���߱��
	CInvestorIDType InvestorID;
	///����������
	CExchangeIDType ExchangeID;
	///��Լ����
	CInstrumentIDType InstrumentID;
	///��Լ����Ȩ��
	CTradingRightType TradingRight;
	///��Ʒ����
	CProductClassType ProductClass;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableInvestorTradingRight CInvestorTradingRight;

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightActionTrigger�ǲ���Ͷ���߽���Ȩ�ޱ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightActionTrigger
{
public:
	///���췽��
	CInvestorTradingRightActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CInvestorTradingRightActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInvestorTradingRightFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pInvestorTradingRight	Ҫ�����InvestorTradingRight
	virtual void beforeAdd(CWriteableInvestorTradingRight *pInvestorTradingRight)
	{
		return;
	}
	
	///����󴥷�
	///@param	pInvestorTradingRight	�Ѿ������InvestorTradingRight
	virtual void afterAdd(CInvestorTradingRight *pInvestorTradingRight)
	{
		return;
	}

	///����ǰ����	
	///@param	pInvestorTradingRight	��ˢ�µ�CInvestorTradingRight
	///@param	pNewInvestorTradingRight	�µ�ֵ
	virtual void beforeUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pInvestorTradingRight	��ˢ�µ�CInvestorTradingRight
	virtual void afterUpdate(CInvestorTradingRight *pInvestorTradingRight)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pInvestorTradingRight	Ҫɾ����CInvestorTradingRight
	virtual void beforeRemove(CInvestorTradingRight *pInvestorTradingRight)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInvestorTradingRightFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightCommitTrigger��ȷ��Ͷ���߽���Ȩ�ޱ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightCommitTrigger
{
public:
	///���췽��
	CInvestorTradingRightCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CInvestorTradingRightCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInvestorTradingRightFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pInvestorTradingRight	�Ѿ������InvestorTradingRight
	virtual void commitAdd(CInvestorTradingRight *pInvestorTradingRight)
	{
		return;
	}

	///���º󴥷�
	///@param	pInvestorTradingRight	��ˢ�µ�CInvestorTradingRight
	///@param	poldInvestorTradingRight	ԭ����ֵ
	virtual void commitUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pOldInvestorTradingRight)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pInvestorTradingRight	�Ѿ�ɾ����CInvestorTradingRight
	virtual void commitRemove(CWriteableInvestorTradingRight *pInvestorTradingRight)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInvestorTradingRightFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightIterator��һ����Ͷ���߽���Ȩ�ޱ��ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightIterator
{
public:
	///���췽��
	CInvestorTradingRightIterator(void)
	{
	}

	///���췽��
	CInvestorTradingRightIterator(CInvestorTradingRightFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorTradingRightIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��InvestorTradingRight
	///@return	��һ����������CInvestorTradingRight������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorTradingRight *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CInvestorTradingRightFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorTradingRight ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorTradingRight * pInvestorTradingRight,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CInvestorTradingRightFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableUserIP��һ���洢����ԱIP��ַ�Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableUserIP
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! UserID.isValid())
			return 0;
		if (! IPAddress.isValid())
			return 0;
		if (! IPMask.isValid())
			return 0;
		if (! MacAddress.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableUserIP *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///�����û�����
	CUserIDType UserID;
	///IP��ַ
	CIPAddressType IPAddress;
	///IP��ַ����
	CIPAddressType IPMask;
	///MAC��ַ
	CMacAddressType MacAddress;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableUserIP CUserIP;

/////////////////////////////////////////////////////////////////////////
///CUserIPActionTrigger�ǲ�������ԱIP��ַʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPActionTrigger
{
public:
	///���췽��
	CUserIPActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CUserIPActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CUserIPFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pUserIP	Ҫ�����UserIP
	virtual void beforeAdd(CWriteableUserIP *pUserIP)
	{
		return;
	}
	
	///����󴥷�
	///@param	pUserIP	�Ѿ������UserIP
	virtual void afterAdd(CUserIP *pUserIP)
	{
		return;
	}

	///����ǰ����	
	///@param	pUserIP	��ˢ�µ�CUserIP
	///@param	pNewUserIP	�µ�ֵ
	virtual void beforeUpdate(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pUserIP	��ˢ�µ�CUserIP
	virtual void afterUpdate(CUserIP *pUserIP)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pUserIP	Ҫɾ����CUserIP
	virtual void beforeRemove(CUserIP *pUserIP)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CUserIPFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserIPCommitTrigger��ȷ�Ͻ���ԱIP��ַʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPCommitTrigger
{
public:
	///���췽��
	CUserIPCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CUserIPCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CUserIPFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pUserIP	�Ѿ������UserIP
	virtual void commitAdd(CUserIP *pUserIP)
	{
		return;
	}

	///���º󴥷�
	///@param	pUserIP	��ˢ�µ�CUserIP
	///@param	poldUserIP	ԭ����ֵ
	virtual void commitUpdate(CUserIP *pUserIP, CWriteableUserIP *pOldUserIP)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pUserIP	�Ѿ�ɾ����CUserIP
	virtual void commitRemove(CWriteableUserIP *pUserIP)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CUserIPFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserIPIterator��һ���Խ���ԱIP��ַ��ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPIterator
{
public:
	///���췽��
	CUserIPIterator(void)
	{
	}

	///���췽��
	CUserIPIterator(CUserIPFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CUserIPIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��UserIP
	///@return	��һ����������CUserIP������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CUserIP *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CUserIPFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pUserIP ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableUserIP * pUserIP,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CUserIPFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInvestorOptionFee��һ���洢�ͻ���Ȩ�������ʱ�Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInvestorOptionFee
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! ExchangeID.isValid())
			return 0;
		if (! InvestorID.isValid())
			return 0;
		if (! InstrumentID.isValid())
			return 0;
		if (! OpenFeeRate.isValid())
			return 0;
		if (! OpenFeeAmt.isValid())
			return 0;
		if (! OffsetFeeRate.isValid())
			return 0;
		if (! OffsetFeeAmt.isValid())
			return 0;
		if (! OTFeeRate.isValid())
			return 0;
		if (! OTFeeAmt.isValid())
			return 0;
		if (! StrikeFeeRate.isValid())
			return 0;
		if (! StrikeFeeAmt.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableInvestorOptionFee *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///����������
	CExchangeIDType ExchangeID;
	///Ͷ���߱���
	CInvestorIDType InvestorID;
	///��Լ����
	CInstrumentIDType InstrumentID;
	///���������Ѱ�����
	CRatioType OpenFeeRate;
	///���������Ѱ�����
	CRatioType OpenFeeAmt;
	///ƽ�������Ѱ�����
	CRatioType OffsetFeeRate;
	///ƽ�������Ѱ�����
	CRatioType OffsetFeeAmt;
	///ƽ��������Ѱ�����
	CRatioType OTFeeRate;
	///ƽ��������Ѱ�����
	CRatioType OTFeeAmt;
	///ִ�������Ѱ�����
	CRatioType StrikeFeeRate;
	///ִ�������Ѱ�����
	CRatioType StrikeFeeAmt;
	
	unsigned int HashBrkIDExIDIstIDVstID;
	
	///����BrkIDExIDIstIDVstID��hashֵ
	void calHashBrkIDExIDIstIDVstID(void)
	{
		unsigned key=0;
		key=BrokerID.hash(key);
		key=ExchangeID.hash(key);
		key=InstrumentID.hash(key);
		key=InvestorID.hash(key);
		HashBrkIDExIDIstIDVstID=key;
	}
	
	///������Ҫ���������BrkIDExIDIstIDVstID��hashֵ
	void updateHashBrkIDExIDIstIDVstID(void)
	{
	}
	
	///�������е�hashֵ
	void calAllHash(void)
	{
		calHashBrkIDExIDIstIDVstID();
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
		updateHashBrkIDExIDIstIDVstID();
	}
	

private:
};

typedef const CWriteableInvestorOptionFee CInvestorOptionFee;

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeActionTrigger�ǲ����ͻ���Ȩ�������ʱ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeActionTrigger
{
public:
	///���췽��
	CInvestorOptionFeeActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CInvestorOptionFeeActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInvestorOptionFeeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pInvestorOptionFee	Ҫ�����InvestorOptionFee
	virtual void beforeAdd(CWriteableInvestorOptionFee *pInvestorOptionFee)
	{
		return;
	}
	
	///����󴥷�
	///@param	pInvestorOptionFee	�Ѿ������InvestorOptionFee
	virtual void afterAdd(CInvestorOptionFee *pInvestorOptionFee)
	{
		return;
	}

	///����ǰ����	
	///@param	pInvestorOptionFee	��ˢ�µ�CInvestorOptionFee
	///@param	pNewInvestorOptionFee	�µ�ֵ
	virtual void beforeUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pInvestorOptionFee	��ˢ�µ�CInvestorOptionFee
	virtual void afterUpdate(CInvestorOptionFee *pInvestorOptionFee)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pInvestorOptionFee	Ҫɾ����CInvestorOptionFee
	virtual void beforeRemove(CInvestorOptionFee *pInvestorOptionFee)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInvestorOptionFeeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeCommitTrigger��ȷ�Ͽͻ���Ȩ�������ʱ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeCommitTrigger
{
public:
	///���췽��
	CInvestorOptionFeeCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CInvestorOptionFeeCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CInvestorOptionFeeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pInvestorOptionFee	�Ѿ������InvestorOptionFee
	virtual void commitAdd(CInvestorOptionFee *pInvestorOptionFee)
	{
		return;
	}

	///���º󴥷�
	///@param	pInvestorOptionFee	��ˢ�µ�CInvestorOptionFee
	///@param	poldInvestorOptionFee	ԭ����ֵ
	virtual void commitUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pOldInvestorOptionFee)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pInvestorOptionFee	�Ѿ�ɾ����CInvestorOptionFee
	virtual void commitRemove(CWriteableInvestorOptionFee *pInvestorOptionFee)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CInvestorOptionFeeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeIterator��һ���Կͻ���Ȩ�������ʱ��ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeIterator
{
public:
	///���췽��
	CInvestorOptionFeeIterator(void)
	{
	}

	///���췽��
	CInvestorOptionFeeIterator(CInvestorOptionFeeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CInvestorOptionFeeIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��InvestorOptionFee
	///@return	��һ����������CInvestorOptionFee������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CInvestorOptionFee *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CInvestorOptionFeeFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pInvestorOptionFee ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableInvestorOptionFee * pInvestorOptionFee,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CInvestorOptionFeeFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableMarketData��һ���洢ʵʱ�����Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableMarketData
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! TradingDay.isValid())
			return 0;
		if (! ExchangeID.isValid())
			return 0;
		if (! InstrumentID.isValid())
			return 0;
		if (! OpenPrice.isValid())
			return 0;
		if (! HighestPrice.isValid())
			return 0;
		if (! LowestPrice.isValid())
			return 0;
		if (! LastPrice.isValid())
			return 0;
		if (! Volume.isValid())
			return 0;
		if (! Turnover.isValid())
			return 0;
		if (! LowerLimitPrice.isValid())
			return 0;
		if (! UpperLimitPrice.isValid())
			return 0;
		if (! OpenInterest.isValid())
			return 0;
		if (! PreClosePrice.isValid())
			return 0;
		if (! PreOpenInterest.isValid())
			return 0;
		if (! PreSettlementPrice.isValid())
			return 0;
		if (! SettlementPrice.isValid())
			return 0;
		if (! UpdateMillisec.isValid())
			return 0;
		if (! UpdateTime.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableMarketData *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///������
	CTradingDayType TradingDay;
	///����������
	CExchangeIDType ExchangeID;
	///��Լ����
	CInstrumentIDType InstrumentID;
	///����
	CPriceType OpenPrice;
	///��߼�
	CPriceType HighestPrice;
	///��ͼ�
	CPriceType LowestPrice;
	///���¼�
	CPriceType LastPrice;
	///����
	CVolumeType Volume;
	///�ɽ����
	CMoneyType Turnover;
	///��ͣ���
	CPriceType LowerLimitPrice;
	///��ͣ���
	CPriceType UpperLimitPrice;
	///�ֲ���
	CVolumeType OpenInterest;
	///������
	CPriceType PreClosePrice;
	///��ֲ���
	CVolumeType PreOpenInterest;
	///�����
	CPriceType PreSettlementPrice;
	///�����
	CPriceType SettlementPrice;
	///����޸ĺ���
	CMillisecType UpdateMillisec;
	///����޸�ʱ��
	CTimeType UpdateTime;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableMarketData CMarketData;

/////////////////////////////////////////////////////////////////////////
///CMarketDataActionTrigger�ǲ���ʵʱ�����ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataActionTrigger
{
public:
	///���췽��
	CMarketDataActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CMarketDataActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CMarketDataFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pMarketData	Ҫ�����MarketData
	virtual void beforeAdd(CWriteableMarketData *pMarketData)
	{
		return;
	}
	
	///����󴥷�
	///@param	pMarketData	�Ѿ������MarketData
	virtual void afterAdd(CMarketData *pMarketData)
	{
		return;
	}

	///����ǰ����	
	///@param	pMarketData	��ˢ�µ�CMarketData
	///@param	pNewMarketData	�µ�ֵ
	virtual void beforeUpdate(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pMarketData	��ˢ�µ�CMarketData
	virtual void afterUpdate(CMarketData *pMarketData)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pMarketData	Ҫɾ����CMarketData
	virtual void beforeRemove(CMarketData *pMarketData)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CMarketDataFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataCommitTrigger��ȷ��ʵʱ�����ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataCommitTrigger
{
public:
	///���췽��
	CMarketDataCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CMarketDataCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CMarketDataFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pMarketData	�Ѿ������MarketData
	virtual void commitAdd(CMarketData *pMarketData)
	{
		return;
	}

	///���º󴥷�
	///@param	pMarketData	��ˢ�µ�CMarketData
	///@param	poldMarketData	ԭ����ֵ
	virtual void commitUpdate(CMarketData *pMarketData, CWriteableMarketData *pOldMarketData)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pMarketData	�Ѿ�ɾ����CMarketData
	virtual void commitRemove(CWriteableMarketData *pMarketData)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CMarketDataFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataIterator��һ����ʵʱ������ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataIterator
{
public:
	///���췽��
	CMarketDataIterator(void)
	{
	}

	///���췽��
	CMarketDataIterator(CMarketDataFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CMarketDataIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��MarketData
	///@return	��һ����������CMarketData������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CMarketData *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CMarketDataFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pMarketData ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableMarketData * pMarketData,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CMarketDataFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableOrderDelay��һ���洢ί���ӳٱ�Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableOrderDelay
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! BrokerID.isValid())
			return 0;
		if (! UserID.isValid())
			return 0;
		if (! UserOrderLocalID.isValid())
			return 0;
		if (! FrontID.isValid())
			return 0;
		if (! SessionID.isValid())
			return 0;
		if (! RequestID.isValid())
			return 0;
		if (! FTdRecvDown.isValid())
			return 0;
		if (! CoreRecvDown.isValid())
			return 0;
		if (! CoreSendUp.isValid())
			return 0;
		if (! CoreRecvUp.isValid())
			return 0;
		if (! CoreSendDown.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableOrderDelay *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///���͹�˾���
	CBrokerIDType BrokerID;
	///�û�����
	CUserIDType UserID;
	///�û����ر�����
	CUserOrderLocalIDType UserOrderLocalID;
	///ǰ�ñ��
	CFrontIDType FrontID;
	///�Ự���
	CSessionIDType SessionID;
	///������
	CRequestIDType RequestID;
	///Ftdengine�����²�ʱ���
	CILocalTimeType FTdRecvDown;
	///�����²�ʱ���
	CILocalTimeType CoreRecvDown;
	///�����ϲ�ʱ���
	CILocalTimeType CoreSendUp;
	///�����ϲ�ʱ���
	CILocalTimeType CoreRecvUp;
	///�����²�ʱ���
	CILocalTimeType CoreSendDown;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableOrderDelay COrderDelay;

/////////////////////////////////////////////////////////////////////////
///COrderDelayActionTrigger�ǲ���ί���ӳٱ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayActionTrigger
{
public:
	///���췽��
	COrderDelayActionTrigger(void)
	{
	}
	
	///��������
	virtual ~COrderDelayActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(COrderDelayFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pOrderDelay	Ҫ�����OrderDelay
	virtual void beforeAdd(CWriteableOrderDelay *pOrderDelay)
	{
		return;
	}
	
	///����󴥷�
	///@param	pOrderDelay	�Ѿ������OrderDelay
	virtual void afterAdd(COrderDelay *pOrderDelay)
	{
		return;
	}

	///����ǰ����	
	///@param	pOrderDelay	��ˢ�µ�COrderDelay
	///@param	pNewOrderDelay	�µ�ֵ
	virtual void beforeUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pOrderDelay	��ˢ�µ�COrderDelay
	virtual void afterUpdate(COrderDelay *pOrderDelay)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pOrderDelay	Ҫɾ����COrderDelay
	virtual void beforeRemove(COrderDelay *pOrderDelay)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	COrderDelayFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayCommitTrigger��ȷ��ί���ӳٱ�ʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayCommitTrigger
{
public:
	///���췽��
	COrderDelayCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~COrderDelayCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(COrderDelayFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pOrderDelay	�Ѿ������OrderDelay
	virtual void commitAdd(COrderDelay *pOrderDelay)
	{
		return;
	}

	///���º󴥷�
	///@param	pOrderDelay	��ˢ�µ�COrderDelay
	///@param	poldOrderDelay	ԭ����ֵ
	virtual void commitUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pOldOrderDelay)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pOrderDelay	�Ѿ�ɾ����COrderDelay
	virtual void commitRemove(CWriteableOrderDelay *pOrderDelay)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	COrderDelayFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayIterator��һ����ί���ӳٱ��ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayIterator
{
public:
	///���췽��
	COrderDelayIterator(void)
	{
	}

	///���췽��
	COrderDelayIterator(COrderDelayFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~COrderDelayIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��OrderDelay
	///@return	��һ����������COrderDelay������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual COrderDelay *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	COrderDelayFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pOrderDelay ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableOrderDelay * pOrderDelay,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	COrderDelayFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableSystemInfo��һ���洢QDPϵͳ��Ϣ�Ķ��󣬿���д����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableSystemInfo
{
public:
	///��CSV�ļ���д��������
	///@param	output	Ҫд�����ļ�
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///��ʼ�������������е��ֶ����
	void init(void);
	
	///���ļ�����
	///@param	input	������ļ�
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int read(FILE *input);
	
	///���ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int write(FILE *output) const;
	
	///��CSV�ļ�����
	///@param	input	������ļ�
	///@param	pNames	�����ֶε����ƣ����ΪNULL����˳�����
	///@return	1��ʾ����ɹ���0��ʾ����ʧ��
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///��CSV�ļ�д��
	///@param	output д�����ļ�
	///@return	1��ʱд���ɹ���0��ʾд��ʧ��
	int writeCSV(FILE *output) const;

	///������ݵĺϷ���
	///@return	1��ʾ�Ϸ���0��ʾ���Ϸ�
	int isValid(void) const
	{
		if (! SystemID.isValid())
			return 0;
		if (! SystemName.isValid())
			return 0;
		if (! SystemIP.isValid())
			return 0;
		return 1;
	}

	///������д���ļ���,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	index	Ҫ��ǰ����ʾ���±�ֵ��һ�����������������ʾ����-1��ʾ����ʾ
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///������д���ļ���ͻ����ʾ�仯������
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	///@param	pOriginal	Ҫ�Ƚϵ�ԭ������
	void dumpDiff(FILE *fp, const CWriteableSystemInfo *pOriginal) const;
	
	///������д���ļ���һ����,����DEBUG
	///@param	fp	Ҫд�����ļ�,NULL��ʾstdout
	void dumpInLine(FILE *fp=NULL) const;

	///������д��һ���ַ�����
	///@param	target	Ҫд���ַ��������÷�Ӧ����֤�����㹻�Ŀռ�
	void dumpString(char *target) const;

	///QDPϵͳ���
	CSystemIDType SystemID;
	///QDPϵͳ����
	CSystemNameType SystemName;
	///QDPϵͳIP��ַ
	CIPAddressType SystemIP;
	
	
	///�������е�hashֵ
	void calAllHash(void)
	{
	}
	
	///�������е�hashֵ
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableSystemInfo CSystemInfo;

/////////////////////////////////////////////////////////////////////////
///CSystemInfoActionTrigger�ǲ���QDPϵͳ��Ϣʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoActionTrigger
{
public:
	///���췽��
	CSystemInfoActionTrigger(void)
	{
	}
	
	///��������
	virtual ~CSystemInfoActionTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CSystemInfoFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����ǰ����
	///@param	pSystemInfo	Ҫ�����SystemInfo
	virtual void beforeAdd(CWriteableSystemInfo *pSystemInfo)
	{
		return;
	}
	
	///����󴥷�
	///@param	pSystemInfo	�Ѿ������SystemInfo
	virtual void afterAdd(CSystemInfo *pSystemInfo)
	{
		return;
	}

	///����ǰ����	
	///@param	pSystemInfo	��ˢ�µ�CSystemInfo
	///@param	pNewSystemInfo	�µ�ֵ
	virtual void beforeUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo)
	{
		return;
	}
	
	///���º󴥷�
	///@param	pSystemInfo	��ˢ�µ�CSystemInfo
	virtual void afterUpdate(CSystemInfo *pSystemInfo)
	{
		return;
	}
	
	///ɾ��ǰ����
	///@param	pSystemInfo	Ҫɾ����CSystemInfo
	virtual void beforeRemove(CSystemInfo *pSystemInfo)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CSystemInfoFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoCommitTrigger��ȷ��QDPϵͳ��Ϣʱ�Ĵ�����
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoCommitTrigger
{
public:
	///���췽��
	CSystemInfoCommitTrigger(void)
	{
	}
	
	///��������
	virtual ~CSystemInfoCommitTrigger(void)
	{
	}

	///�趨��Ӧ�Ķ��󹤳�
	///@param	pFactory	ָ���Ķ��󹤳�
	void setFactory(CSystemInfoFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///����󴥷�
	///@param	pSystemInfo	�Ѿ������SystemInfo
	virtual void commitAdd(CSystemInfo *pSystemInfo)
	{
		return;
	}

	///���º󴥷�
	///@param	pSystemInfo	��ˢ�µ�CSystemInfo
	///@param	poldSystemInfo	ԭ����ֵ
	virtual void commitUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pOldSystemInfo)
	{
		return;
	}
	
	///ɾ���󴥷�
	///@param	pSystemInfo	�Ѿ�ɾ����CSystemInfo
	virtual void commitRemove(CWriteableSystemInfo *pSystemInfo)
	{
		return;
	}
protected:
	///�ô�������Ӧ�Ķ��󹤳�
	CSystemInfoFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoIterator��һ����QDPϵͳ��Ϣ��ö�����ӿ�
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoIterator
{
public:
	///���췽��
	CSystemInfoIterator(void)
	{
	}

	///���췽��
	CSystemInfoIterator(CSystemInfoFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///�����������������ͷ���ռ�õĿռ�
	virtual ~CSystemInfoIterator(void);
	
	///�ͷ��Լ�
	virtual void free(void)
	{
		delete this;
	}

	///�����һ��SystemInfo
	///@return	��һ����������CSystemInfo������Ѿ�û��һ������Ҫ���ˣ��򷵻�NULL
	virtual CSystemInfo *next(void)=0;
	
	///��ö�Ӧ�Ķ��󹤳�
	///@return	��Ӧ�Ķ��󹤳�
	CSystemInfoFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///ɾ��Iterator��ǰָ��ļ�¼
	///@param	pTransaction	�˴�ɾ�����ڵ�����NULL��ʾ�������κ���������ִ��
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///���µ�ǰIteratorָ��ļ�¼
	///@param	pSystemInfo ��Ҫ���³ɵ��¼�¼����
	///@param	pTransaction	�˴θ������ڵ�����NULL��ʾ�������κ���������ִ��
	///@param	updateIndex	true��ʾ��Ҫ����������false��ʾ����Ҫ��������
	virtual void UpdateCurrent(CWriteableSystemInfo * pSystemInfo,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///����ö��������������ȫ�����
	///@param	output	Ҫ�����λ��
	void dump(FILE *output);

protected:
	///���в�ѯʱʹ�õĶ��󹤳�
	CSystemInfoFactory *m_Factory;	
};


#include "databaseFactories.h"

const CWriteableOrder *CWriteableOrderAction::linkOrder(COrderFactory *pFactory) const
{
	void *target=(void *)(&pOrder);
	*((const CWriteableOrder **)target)=pFactory->findByExchangeIDAndOrderSysID(ExchangeID,OrderSysID);
	return pOrder;
}

const CWriteablePreOrder *CWriteableOrderAction::linkPreOrder(CPreOrderFactory *pFactory) const
{
	void *target=(void *)(&pPreOrder);
	*((const CWriteablePreOrder **)target)=pFactory->findByAPIIDAndOrderLocalID(APIID,OrderLocalID);
	return pPreOrder;
}

const CWriteableInvestor *CWriteableOrder::linkInvestor(CInvestorFactory *pFactory) const
{
	void *target=(void *)(&pInvestor);
	*((const CWriteableInvestor **)target)=pFactory->findByBrokerIDInvestorID(BrokerID,InvestorID);
	return pInvestor;
}

const CWriteableClientTradingID *CWriteableOrder::linkClientTradingID(CClientTradingIDFactory *pFactory) const
{
	void *target=(void *)(&pClientTradingID);
	*((const CWriteableClientTradingID **)target)=pFactory->findByBrkIDExIDInvIDHdgFlg(BrokerID,ExchangeID,InvestorID,HedgeFlag);
	return pClientTradingID;
}

const CWriteableInvestorAccount *CWriteableOrder::linkInvestorAccount(CInvestorAccountFactory *pFactory) const
{
	void *target=(void *)(&pInvestorAccount);
	*((const CWriteableInvestorAccount **)target)=pFactory->findByBrokerIDAccountID(BrokerID,AccountID);
	return pInvestorAccount;
}

const CWriteableInvestorPosition *CWriteableOrder::linkInvestorPosition(CInvestorPositionFactory *pFactory) const
{
	void *target=(void *)(&pInvestorPosition);
	*((const CWriteableInvestorPosition **)target)=pFactory->findByBrkIDExIDInvIDInsDirHed(BrokerID,ExchangeID,InvestorID,InstrumentID,Direction,HedgeFlag);
	return pInvestorPosition;
}

const CWriteableInstrument *CWriteableOrder::linkInstrument(CInstrumentFactory *pFactory) const
{
	void *target=(void *)(&pInstrument);
	*((const CWriteableInstrument **)target)=pFactory->findByExchangeIDAndInstrumentID(ExchangeID,InstrumentID);
	return pInstrument;
}

const CWriteableInvestorMargin *CWriteableOrder::linkInvestorMargin(CInvestorMarginFactory *pFactory) const
{
	void *target=(void *)(&pInvestorMargin);
	*((const CWriteableInvestorMargin **)target)=pFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,ExchangeID,InstrumentID,InvestorID,HedgeFlag);
	return pInvestorMargin;
}

const CWriteableInvestorFee *CWriteableOrder::linkInvestorFee(CInvestorFeeFactory *pFactory) const
{
	void *target=(void *)(&pInvestorFee);
	*((const CWriteableInvestorFee **)target)=pFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,ExchangeID,InstrumentID,InvestorID,HedgeFlag);
	return pInvestorFee;
}

const CWriteableInvestorOptionFee *CWriteableOrder::linkInvestorOptionFee(CInvestorOptionFeeFactory *pFactory) const
{
	void *target=(void *)(&pInvestorOptionFee);
	*((const CWriteableInvestorOptionFee **)target)=pFactory->findByBrkIDExIDIstIDVstID(BrokerID,ExchangeID,InstrumentID,InvestorID);
	return pInvestorOptionFee;
}

const CWriteablePartClientInsGroupPosition *CWriteableOrder::linkClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory) const
{
	void *target=(void *)(&pClientGroupPosition);
	*((const CWriteablePartClientInsGroupPosition **)target)=pFactory->findByBrokerClientAndInsGroup(BrokerID,ClientID,InstrumentGroupID);
	return pClientGroupPosition;
}

const CWriteableInvestor *CWriteablePreOrder::linkInvestor(CInvestorFactory *pFactory) const
{
	void *target=(void *)(&pInvestor);
	*((const CWriteableInvestor **)target)=pFactory->findByBrokerIDInvestorID(BrokerID,InvestorID);
	return pInvestor;
}

const CWriteableClientTradingID *CWriteablePreOrder::linkClientTradingID(CClientTradingIDFactory *pFactory) const
{
	void *target=(void *)(&pClientTradingID);
	*((const CWriteableClientTradingID **)target)=pFactory->findByBrkIDExIDInvIDHdgFlg(BrokerID,ExchangeID,InvestorID,HedgeFlag);
	return pClientTradingID;
}

const CWriteableInvestorAccount *CWriteablePreOrder::linkInvestorAccount(CInvestorAccountFactory *pFactory) const
{
	void *target=(void *)(&pInvestorAccount);
	*((const CWriteableInvestorAccount **)target)=pFactory->findByBrokerIDAccountID(BrokerID,AccountID);
	return pInvestorAccount;
}

const CWriteableInvestorPosition *CWriteablePreOrder::linkInvestorPosition(CInvestorPositionFactory *pFactory) const
{
	void *target=(void *)(&pInvestorPosition);
	*((const CWriteableInvestorPosition **)target)=pFactory->findByBrkIDExIDInvIDInsDirHed(BrokerID,ExchangeID,InvestorID,InstrumentID,Direction,HedgeFlag);
	return pInvestorPosition;
}

const CWriteableInstrument *CWriteablePreOrder::linkInstrument(CInstrumentFactory *pFactory) const
{
	void *target=(void *)(&pInstrument);
	*((const CWriteableInstrument **)target)=pFactory->findByExchangeIDAndInstrumentID(ExchangeID,InstrumentID);
	return pInstrument;
}

const CWriteableInvestorMargin *CWriteablePreOrder::linkInvestorMargin(CInvestorMarginFactory *pFactory) const
{
	void *target=(void *)(&pInvestorMargin);
	*((const CWriteableInvestorMargin **)target)=pFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,ExchangeID,InstrumentID,InvestorID,HedgeFlag);
	return pInvestorMargin;
}

const CWriteableInvestorFee *CWriteablePreOrder::linkInvestorFee(CInvestorFeeFactory *pFactory) const
{
	void *target=(void *)(&pInvestorFee);
	*((const CWriteableInvestorFee **)target)=pFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,ExchangeID,InstrumentID,InvestorID,HedgeFlag);
	return pInvestorFee;
}

const CWriteableInvestorOptionFee *CWriteablePreOrder::linkInvestorOptionFee(CInvestorOptionFeeFactory *pFactory) const
{
	void *target=(void *)(&pInvestorOptionFee);
	*((const CWriteableInvestorOptionFee **)target)=pFactory->findByBrkIDExIDIstIDVstID(BrokerID,ExchangeID,InstrumentID,InvestorID);
	return pInvestorOptionFee;
}

const CWriteablePartClientInsGroupPosition *CWriteablePreOrder::linkClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory) const
{
	void *target=(void *)(&pClientGroupPosition);
	*((const CWriteablePartClientInsGroupPosition **)target)=pFactory->findByBrokerClientAndInsGroup(BrokerID,ClientID,InstrumentGroupID);
	return pClientGroupPosition;
}

const CWriteableInvestor *CWriteableIndexPreOrder::linkInvestor(CInvestorFactory *pFactory) const
{
	void *target=(void *)(&pInvestor);
	*((const CWriteableInvestor **)target)=pFactory->findByBrokerIDInvestorID(BrokerID,InvestorID);
	return pInvestor;
}

const CWriteableClientTradingID *CWriteableIndexPreOrder::linkClientTradingID(CClientTradingIDFactory *pFactory) const
{
	void *target=(void *)(&pClientTradingID);
	*((const CWriteableClientTradingID **)target)=pFactory->findByBrkIDExIDInvIDHdgFlg(BrokerID,ExchangeID,InvestorID,HedgeFlag);
	return pClientTradingID;
}

const CWriteableInvestorAccount *CWriteableIndexPreOrder::linkInvestorAccount(CInvestorAccountFactory *pFactory) const
{
	void *target=(void *)(&pInvestorAccount);
	*((const CWriteableInvestorAccount **)target)=pFactory->findByBrokerIDInvestorID(BrokerID,InvestorID);
	return pInvestorAccount;
}

const CWriteableInstrument *CWriteableIndexPreOrder::linkInstrument(CInstrumentFactory *pFactory) const
{
	void *target=(void *)(&pInstrument);
	*((const CWriteableInstrument **)target)=pFactory->findByExchangeIDAndInstrumentID(ExchangeID,InstrumentID);
	return pInstrument;
}

const CWriteableInvestorMargin *CWriteableIndexPreOrder::linkInvestorMargin(CInvestorMarginFactory *pFactory) const
{
	void *target=(void *)(&pInvestorMargin);
	*((const CWriteableInvestorMargin **)target)=pFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,ExchangeID,InstrumentID,InvestorID,HedgeFlag);
	return pInvestorMargin;
}

const CWriteableInvestorFee *CWriteableIndexPreOrder::linkInvestorFee(CInvestorFeeFactory *pFactory) const
{
	void *target=(void *)(&pInvestorFee);
	*((const CWriteableInvestorFee **)target)=pFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,ExchangeID,InstrumentID,InvestorID,HedgeFlag);
	return pInvestorFee;
}

const CWriteablePartClientInsGroupPosition *CWriteableIndexPreOrder::linkClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory) const
{
	void *target=(void *)(&pClientGroupPosition);
	*((const CWriteablePartClientInsGroupPosition **)target)=pFactory->findByBrokerClientAndInsGroup(BrokerID,ClientID,InstrumentGroupID);
	return pClientGroupPosition;
}

const CWriteableInvestorAccount *CWriteableClientTradingID::linkInvestorAccount(CInvestorAccountFactory *pFactory) const
{
	void *target=(void *)(&pInvestorAccount);
	*((const CWriteableInvestorAccount **)target)=pFactory->findByBrokerIDAccountID(BrokerID,AccountID);
	return pInvestorAccount;
}

const CWriteableInvestorAccount *CWriteableOrderInsertFailed::linkInvestorAccount(CInvestorAccountFactory *pFactory) const
{
	void *target=(void *)(&pInvestorAccount);
	*((const CWriteableInvestorAccount **)target)=pFactory->findByBrokerIDAccountID(BrokerID,AccountID);
	return pInvestorAccount;
}

const CWriteableInvestorPosition *CWriteableOrderInsertFailed::linkInvestorPosition(CInvestorPositionFactory *pFactory) const
{
	void *target=(void *)(&pInvestorPosition);
	*((const CWriteableInvestorPosition **)target)=pFactory->findByBrkIDExIDInvIDInsDirHed(BrokerID,ExchangeID,InvestorID,InstrumentID,Direction,HedgeFlag);
	return pInvestorPosition;
}

const CWriteableInstrument *CWriteableOrderInsertFailed::linkInstrument(CInstrumentFactory *pFactory) const
{
	void *target=(void *)(&pInstrument);
	*((const CWriteableInstrument **)target)=pFactory->findByExchangeIDAndInstrumentID(ExchangeID,InstrumentID);
	return pInstrument;
}

const CWriteableInvestorMargin *CWriteableOrderInsertFailed::linkInvestorMargin(CInvestorMarginFactory *pFactory) const
{
	void *target=(void *)(&pInvestorMargin);
	*((const CWriteableInvestorMargin **)target)=pFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,ExchangeID,InstrumentID,InvestorID,HedgeFlag);
	return pInvestorMargin;
}

const CWriteableInvestorFee *CWriteableOrderInsertFailed::linkInvestorFee(CInvestorFeeFactory *pFactory) const
{
	void *target=(void *)(&pInvestorFee);
	*((const CWriteableInvestorFee **)target)=pFactory->findByBrkIDExIDIstIDVstIDHdg(BrokerID,ExchangeID,InstrumentID,InvestorID,HedgeFlag);
	return pInvestorFee;
}

const CWriteablePreOrder *CWriteableBrkUserIDLocalID::linkPreOrder(CPreOrderFactory *pFactory) const
{
	void *target=(void *)(&pPreOrder);
	*((const CWriteablePreOrder **)target)=pFactory->findByAPIIDAndOrderLocalID(APIID,OrderLocalID);
	return pPreOrder;
}

#endif


