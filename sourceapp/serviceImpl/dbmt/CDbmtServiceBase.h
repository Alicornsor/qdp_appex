/////////////////////////////////////////////////////////////////////////
///@system 交易引擎系统
///@company 上海量投网络科技有限公司
///@file CDbmtServiceBase.h
///@brief	定义了CDbmtServiceBase
///@history 
///20060113	xuzh		创建该文件
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
///出入金来自期货主席
#define INVESTORACCOUNTDEPOSIT_TOPICID_CHAIRMAN      "9001"
#define INVESTORACCOUNTDEPOSIT_FROM_CHAIRMAN         'A'
#define INVESTORACCOUNTDEPOSIT_FROM_MONEYGATE        'M'

///出入金来自场下
#define INVESTORACCOUNTDEPOSIT_TOPICID_FIELD         "9002"
#define INVESTORACCOUNTDEPOSIT_FROM_FIELD            'B'
/*** SIR XXXXX END ***/

/////////////////////////////////////////////////////////////////////////
///CDbmtServiceBase是一个完成数据同步工作的类
///内存数据库的数据
///@author	xuzh
///@version	1.0,20060113
///////////////////////////////////////////////////////////////////////// 
class CDbmtServiceBase
{
public:
	///构造方法
	///@param	pDB	指定的内存数据库
	///@param	pErrorEngine	指定的错误引擎
	CDbmtServiceBase(CMemoryDB *pDB, CErrorEngine *pErrorEngine);

	///析构方法
	virtual ~CDbmtServiceBase(void);
	
public:
	///同步数据库表客户资金帐户出入金
	///@param	pInvestorAccountDeposit	要同步的客户资金帐户出入金信息
	///@param	pResDeposit	出入金应答信息
	///@param	topicID	DBMT的主题号
	///@param	seqID	DBMT的序列号
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncInvestorAccountDeposit(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit,CAccountDepositResField *pResDeposit,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,
									const TSessionRef &sessionRef,CTransaction *pTransaction);

	///同步数据库表客户资金帐户出入金的实现
	///@param	pInvestorAccountDeposit	要同步的客户资金帐户出入金信息
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncInvestorAccountDepositImpl(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit,CAccountDepositResField *pResDeposit,CTransaction *pTransaction)=0;
	///同步数据库表增加交易用户
	///@param	pInsUser	要同步的增加交易用户信息
	///@param	topicID	DBMT的主题号
	///@param	seqID	DBMT的序列号
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncInsUser(CWriteableUser *pUser,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///同步数据库表增加交易用户的实现
	///@param	pInsUser	要同步的增加交易用户信息
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncInsUserImpl(CWriteableUser *pUser,CTransaction *pTransaction);

	///同步数据库表修改交易用户
	///@param	pUpdUser	要同步的修改交易用户信息
	///@param	topicID	DBMT的主题号
	///@param	seqID	DBMT的序列号
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncUpdUser(CWriteableUser *pUser,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///同步数据库表修改交易用户的实现
	///@param	pUpdUser	要同步的修改交易用户信息
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncUpdUserImpl(CWriteableUser *pUser,CTransaction *pTransaction);

	///同步数据库表客户资金帐户出入金
	///@param	pClientTradingID	要同步的客户资金帐户出入金信息
	///@param	topicID	DBMT的主题号
	///@param	seqID	DBMT的序列号
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncClientTradingID(CWriteableClientTradingID *pClientTradingID,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///同步数据库表客户资金帐户出入金的实现
	///@param	pClientTradingID	要同步的客户资金帐户出入金信息
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncClientTradingIDImpl(CWriteableClientTradingID *pClientTradingID,CTransaction *pTransaction)=0;
	///同步数据库表修改投资者权限
	///@param	pUpdInvestorTradingRight	要同步的修改投资者权限信息
	///@param	topicID	DBMT的主题号
	///@param	seqID	DBMT的序列号
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncUpdInvestorTradingRight(CWriteableInvestorTradingRight *pInvestorTradingRight,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///同步数据库表修改投资者权限的实现
	///@param	pUpdInvestorTradingRight	要同步的修改投资者权限信息
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncUpdInvestorTradingRightImpl(CWriteableInvestorTradingRight *pInvestorTradingRight,CTransaction *pTransaction);

	///同步数据库表增加投资者权限
	///@param	pInsInvestorTradingRight	要同步的增加投资者权限信息
	///@param	topicID	DBMT的主题号
	///@param	seqID	DBMT的序列号
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncInsInvestorTradingRight(CWriteableInvestorTradingRight *pInvestorTradingRight,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///同步数据库表增加投资者权限的实现
	///@param	pInsInvestorTradingRight	要同步的增加投资者权限信息
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncInsInvestorTradingRightImpl(CWriteableInvestorTradingRight *pInvestorTradingRight,CTransaction *pTransaction);

	///同步数据库表删除投资者权限
	///@param	pDelInvestorTradingRight	要同步的删除投资者权限信息
	///@param	topicID	DBMT的主题号
	///@param	seqID	DBMT的序列号
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncDelInvestorTradingRight(CWriteableInvestorTradingRight *pInvestorTradingRight,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///同步数据库表删除投资者权限的实现
	///@param	pDelInvestorTradingRight	要同步的删除投资者权限信息
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncDelInvestorTradingRightImpl(CWriteableInvestorTradingRight *pInvestorTradingRight,CTransaction *pTransaction);

	///同步数据库表交易员IP
	///@param	pUpdUserIP	要同步的交易员IP信息
	///@param	topicID	DBMT的主题号
	///@param	seqID	DBMT的序列号
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncUpdUserIP(CWriteableUserIP *pUserIP,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///同步数据库表交易员IP的实现
	///@param	pUpdUserIP	要同步的交易员IP信息
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncUpdUserIPImpl(CWriteableUserIP *pUserIP,CTransaction *pTransaction);

	///同步数据库表交易员IP
	///@param	pInsUserIP	要同步的交易员IP信息
	///@param	topicID	DBMT的主题号
	///@param	seqID	DBMT的序列号
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncInsUserIP(CWriteableUserIP *pUserIP,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///同步数据库表交易员IP的实现
	///@param	pInsUserIP	要同步的交易员IP信息
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncInsUserIPImpl(CWriteableUserIP *pUserIP,CTransaction *pTransaction);

	///同步数据库表交易员IP
	///@param	pDelUserIP	要同步的交易员IP信息
	///@param	topicID	DBMT的主题号
	///@param	seqID	DBMT的序列号
	///@param	sessionRef	会话引用
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncDelUserIP(CWriteableUserIP *pUserIP,CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID,const TSessionRef &sessionRef,CTransaction *pTransaction);

	///同步数据库表交易员IP的实现
	///@param	pDelUserIP	要同步的交易员IP信息
	///@param	pTransaction	本操作属于的事务
	///@return	true表示成功，false表示失败
	virtual bool SyncDelUserIPImpl(CWriteableUserIP *pUserIP,CTransaction *pTransaction);


protected:
	///检查是否重复的序列号，如果不重复，则修改相关映射表
	///@param	topicID	本次使用的主题号
	///@param	seqID	本次使用的序列号
	///@return	true表示是重复的，false表示不重复
	bool isDuplicate(CDbmtTopicIDType topicID,CDbmtSequenceIDType seqID);

	///对于交易所的同步指令，目前是否合适的处理时间
	///@return	true表示合适，false表示不合适
	bool suitableTime(void);

	///保存同步指令，用于以后合适的时间再处理
	///@param	buffer	指令的缓冲区
	///@param	len	指令的长度
	///@param	waitingSeqID	等待序列号
	///@param	tid	指令的tid
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
