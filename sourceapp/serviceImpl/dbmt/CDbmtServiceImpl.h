/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �н���������˾
///@file CDbmtServiceBase.h
///@brief	������CDbmtServiceBase
///@history 
///20130119	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////
#ifndef CDBMTSERVICEIMPL_H
#define CDBMTSERVICEIMPL_H

#include "CDbmtServiceBase.h"

class CDbmtServiceImpl:public CDbmtServiceBase
{
public:
	///���췽��
	///@param	pDB	ָ�����ڴ����ݿ�
	///@param	pErrorEngine	ָ���Ĵ�������
	CDbmtServiceImpl(CMemoryDB *pDB, CErrorEngine *pErrorEngine):
		CDbmtServiceBase(pDB,pErrorEngine)
	{
	}
	
public:

	///ͬ�����ݿ��ͻ��ʽ��ʻ������
	///@param	pInvestorAccountDeposit	Ҫͬ���Ŀͻ��ʽ��ʻ��������Ϣ
	///@param	pResDeposit	�����Ӧ����Ϣ
	///@param	topicID	DBMT�������
	///@param	seqID	DBMT�����к�
	///@param	sessionRef	�Ự����
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	bool SyncInvestorAccountDeposit(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit,CAccountDepositResField *pResDeposit,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,
		const TSessionRef &sessionRef,CTransaction *pTransaction);
		
	///ͬ�����ݿ��ͻ��ʽ��ʻ�������ʵ��
	///@param	pClientTradingID	Ҫͬ���Ŀͻ��ʽ��ʻ��������Ϣ
	///@param	pTransaction	���������ڵ�����
	///@return	true��ʾ�ɹ���false��ʾʧ��
	virtual bool SyncClientTradingID(CWriteableClientTradingID *pClientTradingID,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,
		const TSessionRef &sessionRef,CTransaction *pTransaction);
	
};

#endif
