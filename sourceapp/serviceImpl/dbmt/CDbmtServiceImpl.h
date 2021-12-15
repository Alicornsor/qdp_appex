/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 中金所技术公司
///@file CDbmtServiceBase.h
///@brief	定义了CDbmtServiceBase
///@history 
///20130119	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////
#ifndef CDBMTSERVICEIMPL_H
#define CDBMTSERVICEIMPL_H

#include "CDbmtServiceBase.h"

class CDbmtServiceImpl:public CDbmtServiceBase
{
public:
	///构造方法
	///@param	pDB	指定的内存数据库
	///@param	pErrorEngine	指定的错误引擎
	CDbmtServiceImpl(CMemoryDB *pDB, CErrorEngine *pErrorEngine):
		CDbmtServiceBase(pDB,pErrorEngine)
	{
	}
	
public:

	///同步数据库表客户资金帐户出入金
	///@param	pInvestorAccountDeposit	要同步的客户资金帐户出入金信息
	///@param	pResDeposit	出入金应答信息
	///@param	topicID	DBMT的主题号
	///@param	seqID	DBMT的序列号
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	bool SyncInvestorAccountDeposit(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit,CAccountDepositResField *pResDeposit,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,
		const TSessionRef &sessionRef,CTransaction *pTransaction);
		
	///同步数据库表客户资金帐户出入金的实现
	///@param	pClientTradingID	要同步的客户资金帐户出入金信息
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncClientTradingID(CWriteableClientTradingID *pClientTradingID,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,
		const TSessionRef &sessionRef,CTransaction *pTransaction);
	
};

#endif
