/////////////////////////////////////////////////////////////////////////
///@system ��������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CDbmtServiceBase.h
///@brief	������CDbmtServiceBase
///@history 
///20060113	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CDBMTSERVICEBASE_H
#define CDBMTSERVICEBASE_H

#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "XtpPackageDesc.h"
#include "CErrorEngine.h"
#include "tradingTools.h"

extern CConfig *currentConfig;

/*** SIR XXXXX BEGIN ***/
///����������ڻ���ϯ
#define INVESTORACCOUNTDEPOSIT_TOPICID_CHAIRMAN      "9001"
#define INVESTORACCOUNTDEPOSIT_FROM_CHAIRMAN         'A'
#define INVESTORACCOUNTDEPOSIT_FROM_MONEYGATE        'M'

///��������Գ���
#define INVESTORACCOUNTDEPOSIT_TOPICID_FIELD         "9002"
#define INVESTORACCOUNTDEPOSIT_FROM_FIELD            'B'
/*** SIR XXXXX END ***/

/////////////////////////////////////////////////////////////////////////
///CDbmtServiceBase��һ���������ͬ����������
///�ڴ����ݿ������
///@author	xuzh
///@version	1.0,20060113
///////////////////////////////////////////////////////////////////////// 
class CDbmtServiceBase
{
public:
	///���췽��
	///@param	pDB	ָ�����ڴ����ݿ�
	///@param	pErrorEngine	ָ���Ĵ�������
	CDbmtServiceBase(CMemoryDB *pDB, CErrorEngine *pErrorEngine);

	///��������
	virtual ~CDbmtServiceBase(void);
	
public:
	///ͬ�����ݿ��ͻ��ʽ��ʻ������
	///@param	pInvestorAccountDeposit	Ҫͬ���Ŀͻ��ʽ��ʻ��������Ϣ
	///@param	pResDeposit	�����Ӧ����Ϣ
	///@param	topicID	DBMT�������
	///@param	seqID	DBMT�����к�
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncInvestorAccountDeposit(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit,CAccountDepositResField *pResDeposit,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,
									const TSessionRef &sessionRef,CTransaction *pTransaction);

	///ͬ�����ݿ��ͻ��ʽ��ʻ�������ʵ��
	///@param	pInvestorAccountDeposit	Ҫͬ���Ŀͻ��ʽ��ʻ��������Ϣ
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncInvestorAccountDepositImpl(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit,CAccountDepositResField *pResDeposit,CTransaction *pTransaction)=0;
	///ͬ�����ݿ�����ӽ����û�
	///@param	pInsUser	Ҫͬ�������ӽ����û���Ϣ
	///@param	topicID	DBMT�������
	///@param	seqID	DBMT�����к�
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncInsUser(CWriteableUser *pUser,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///ͬ�����ݿ�����ӽ����û���ʵ��
	///@param	pInsUser	Ҫͬ�������ӽ����û���Ϣ
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncInsUserImpl(CWriteableUser *pUser,CTransaction *pTransaction);

	///ͬ�����ݿ���޸Ľ����û�
	///@param	pUpdUser	Ҫͬ�����޸Ľ����û���Ϣ
	///@param	topicID	DBMT�������
	///@param	seqID	DBMT�����к�
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncUpdUser(CWriteableUser *pUser,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///ͬ�����ݿ���޸Ľ����û���ʵ��
	///@param	pUpdUser	Ҫͬ�����޸Ľ����û���Ϣ
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncUpdUserImpl(CWriteableUser *pUser,CTransaction *pTransaction);

	///ͬ�����ݿ��ͻ��ʽ��ʻ������
	///@param	pClientTradingID	Ҫͬ���Ŀͻ��ʽ��ʻ��������Ϣ
	///@param	topicID	DBMT�������
	///@param	seqID	DBMT�����к�
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncClientTradingID(CWriteableClientTradingID *pClientTradingID,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///ͬ�����ݿ��ͻ��ʽ��ʻ�������ʵ��
	///@param	pClientTradingID	Ҫͬ���Ŀͻ��ʽ��ʻ��������Ϣ
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncClientTradingIDImpl(CWriteableClientTradingID *pClientTradingID,CTransaction *pTransaction)=0;
	///ͬ�����ݿ���޸�Ͷ����Ȩ��
	///@param	pUpdInvestorTradingRight	Ҫͬ�����޸�Ͷ����Ȩ����Ϣ
	///@param	topicID	DBMT�������
	///@param	seqID	DBMT�����к�
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncUpdInvestorTradingRight(CWriteableInvestorTradingRight *pInvestorTradingRight,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///ͬ�����ݿ���޸�Ͷ����Ȩ�޵�ʵ��
	///@param	pUpdInvestorTradingRight	Ҫͬ�����޸�Ͷ����Ȩ����Ϣ
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncUpdInvestorTradingRightImpl(CWriteableInvestorTradingRight *pInvestorTradingRight,CTransaction *pTransaction);

	///ͬ�����ݿ������Ͷ����Ȩ��
	///@param	pInsInvestorTradingRight	Ҫͬ��������Ͷ����Ȩ����Ϣ
	///@param	topicID	DBMT�������
	///@param	seqID	DBMT�����к�
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncInsInvestorTradingRight(CWriteableInvestorTradingRight *pInvestorTradingRight,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///ͬ�����ݿ������Ͷ����Ȩ�޵�ʵ��
	///@param	pInsInvestorTradingRight	Ҫͬ��������Ͷ����Ȩ����Ϣ
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncInsInvestorTradingRightImpl(CWriteableInvestorTradingRight *pInvestorTradingRight,CTransaction *pTransaction);

	///ͬ�����ݿ��ɾ��Ͷ����Ȩ��
	///@param	pDelInvestorTradingRight	Ҫͬ����ɾ��Ͷ����Ȩ����Ϣ
	///@param	topicID	DBMT�������
	///@param	seqID	DBMT�����к�
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncDelInvestorTradingRight(CWriteableInvestorTradingRight *pInvestorTradingRight,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///ͬ�����ݿ��ɾ��Ͷ����Ȩ�޵�ʵ��
	///@param	pDelInvestorTradingRight	Ҫͬ����ɾ��Ͷ����Ȩ����Ϣ
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncDelInvestorTradingRightImpl(CWriteableInvestorTradingRight *pInvestorTradingRight,CTransaction *pTransaction);

	///ͬ�����ݿ����ԱIP
	///@param	pUpdUserIP	Ҫͬ���Ľ���ԱIP��Ϣ
	///@param	topicID	DBMT�������
	///@param	seqID	DBMT�����к�
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncUpdUserIP(CWriteableUserIP *pUserIP,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///ͬ�����ݿ����ԱIP��ʵ��
	///@param	pUpdUserIP	Ҫͬ���Ľ���ԱIP��Ϣ
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncUpdUserIPImpl(CWriteableUserIP *pUserIP,CTransaction *pTransaction);

	///ͬ�����ݿ����ԱIP
	///@param	pInsUserIP	Ҫͬ���Ľ���ԱIP��Ϣ
	///@param	topicID	DBMT�������
	///@param	seqID	DBMT�����к�
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncInsUserIP(CWriteableUserIP *pUserIP,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///ͬ�����ݿ����ԱIP��ʵ��
	///@param	pInsUserIP	Ҫͬ���Ľ���ԱIP��Ϣ
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncInsUserIPImpl(CWriteableUserIP *pUserIP,CTransaction *pTransaction);

	///ͬ�����ݿ����ԱIP
	///@param	pDelUserIP	Ҫͬ���Ľ���ԱIP��Ϣ
	///@param	topicID	DBMT�������
	///@param	seqID	DBMT�����к�
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncDelUserIP(CWriteableUserIP *pUserIP,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///ͬ�����ݿ����ԱIP��ʵ��
	///@param	pDelUserIP	Ҫͬ���Ľ���ԱIP��Ϣ
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncDelUserIPImpl(CWriteableUserIP *pUserIP,CTransaction *pTransaction);


protected:
	///����Ƿ��ظ������кţ�������ظ������޸����ӳ���
	///@param	topicID	����ʹ�õ������
	///@param	seqID	����ʹ�õ����к�
	///@return	true��ʾ���ظ��ģ�false��ʾ���ظ�
	bool isDuplicate(CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID);

	///���ڽ�������ͬ��ָ�Ŀǰ�Ƿ���ʵĴ���ʱ��
	///@return	true��ʾ���ʣ�false��ʾ������
	bool suitableTime(void);

	///����ͬ��ָ������Ժ���ʵ�ʱ���ٴ���
	///@param	buffer	ָ��Ļ�����
	///@param	len	ָ��ĳ���
	///@param	waitingSeqID	�ȴ����к�
	///@param	tid	ָ���tid
	void saveCommand(void *buffer, int len, int waitingSeqID, int tid);

	CMemoryDB *m_DB;
	CErrorEngine *m_ErrorEngine;
	FILE *m_dbmtLog;
	map<CDbmtTopicIDType,CDbmtSequenceIDType> m_lastSeqMap;
	int m_waitingSeqID;
	typedef struct
	{
		int tid;
		void *buffer;
		int len;
	}	TCommand;
};

#endif
