/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file BaseDataStruct.h
///@brief定义了内存数据库用的基本数据结构类，以及iterator、trigger的基类
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef BASEDATASTRUCT_H
#define BASEDATASTRUCT_H

#include "platform.h"
#include "CBaseObject.h"
#include "customDataType.h"
#include "CTransaction.h"
#include "XtpData.h"

///判断结果是否满足条件
extern bool satisfy(int value,int type);

///字符串比较函数
///@param	s1	字符串1
///@param	s2	字符串2
///@return	1表示大于，0表示等于，-1表示小于
int compare(const char *s1, const char *s2);

///整数比较函数
///@param	v1	整数1
///@param	v2	整数2
///@return	1表示大于，0表示等于，-1表示小于
int compare(const int v1,const int v2);

///整数比较函数
///@param	v1	整数1
///@param	v2	整数2
///@return	1表示大于，0表示等于，-1表示小于
int compare(const long v1,const long v2);

///浮点数比较函数
///@param	v1	浮点数1
///@param	v2	浮点数2
///@return	1表示大于，0表示等于，-1表示小于
int compare(const double v1,const double v2);

///从buffer中获取下一个token，这里的token是以逗号或者换行分隔的
///在使用时，第一次应当传入指定的buffer，以后应当反复传入NULL，
///这样可以依次取出所有的token。本函数将改变buffer中的内容，叫用
///方有责任自己保护数据。本函数有重入问题，在一个取token的序列结
///束前，开始新的一个取token序列，将影响前面一个的结果。此问题和
///strtok的问题类似
///@param	buffer	要取token的buffer，NULL表示从上次取的buffer中取下一个
///@return	得到的token
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
///CWriteableDataSyncStatus是一个存储数据同步状态表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableDataSyncStatus
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableDataSyncStatus *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///交易日
	CDateType TradingDay;
	///数据同步状态
	CDataSyncStatusType DataSyncStatus;
	///QDP系统编号
	CSystemIDType SystemID;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableDataSyncStatus CDataSyncStatus;

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusActionTrigger是操作数据同步状态表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusActionTrigger
{
public:
	///构造方法
	CDataSyncStatusActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CDataSyncStatusActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CDataSyncStatusFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pDataSyncStatus	要加入的DataSyncStatus
	virtual void beforeAdd(CWriteableDataSyncStatus *pDataSyncStatus)
	{
		return;
	}
	
	///加入后触发
	///@param	pDataSyncStatus	已经加入的DataSyncStatus
	virtual void afterAdd(CDataSyncStatus *pDataSyncStatus)
	{
		return;
	}

	///更新前触发	
	///@param	pDataSyncStatus	被刷新的CDataSyncStatus
	///@param	pNewDataSyncStatus	新的值
	virtual void beforeUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus)
	{
		return;
	}
	
	///更新后触发
	///@param	pDataSyncStatus	被刷新的CDataSyncStatus
	virtual void afterUpdate(CDataSyncStatus *pDataSyncStatus)
	{
		return;
	}
	
	///删除前触发
	///@param	pDataSyncStatus	要删除的CDataSyncStatus
	virtual void beforeRemove(CDataSyncStatus *pDataSyncStatus)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CDataSyncStatusFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusCommitTrigger是确认数据同步状态表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusCommitTrigger
{
public:
	///构造方法
	CDataSyncStatusCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CDataSyncStatusCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CDataSyncStatusFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pDataSyncStatus	已经加入的DataSyncStatus
	virtual void commitAdd(CDataSyncStatus *pDataSyncStatus)
	{
		return;
	}

	///更新后触发
	///@param	pDataSyncStatus	被刷新的CDataSyncStatus
	///@param	poldDataSyncStatus	原来的值
	virtual void commitUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pOldDataSyncStatus)
	{
		return;
	}
	
	///删除后触发
	///@param	pDataSyncStatus	已经删除的CDataSyncStatus
	virtual void commitRemove(CWriteableDataSyncStatus *pDataSyncStatus)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CDataSyncStatusFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CDataSyncStatusIterator是一个对数据同步状态表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CDataSyncStatusIterator
{
public:
	///构造方法
	CDataSyncStatusIterator(void)
	{
	}

	///构造方法
	CDataSyncStatusIterator(CDataSyncStatusFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CDataSyncStatusIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个DataSyncStatus
	///@return	下一个满足条件CDataSyncStatus，如果已经没有一个满足要求了，则返回NULL
	virtual CDataSyncStatus *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CDataSyncStatusFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pDataSyncStatus 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableDataSyncStatus * pDataSyncStatus,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CDataSyncStatusFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableSystemStatus是一个存储QDP状态表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableSystemStatus
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
	int isValid(void) const
	{
		if (! TradingDay.isValid())
			return 0;
		if (! SystemStatus.isValid())
			return 0;
		return 1;
	}

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableSystemStatus *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///交易日
	CDateType TradingDay;
	///系统状态
	CSystemStatusType SystemStatus;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableSystemStatus CSystemStatus;

/////////////////////////////////////////////////////////////////////////
///CSystemStatusActionTrigger是操作QDP状态表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusActionTrigger
{
public:
	///构造方法
	CSystemStatusActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CSystemStatusActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CSystemStatusFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pSystemStatus	要加入的SystemStatus
	virtual void beforeAdd(CWriteableSystemStatus *pSystemStatus)
	{
		return;
	}
	
	///加入后触发
	///@param	pSystemStatus	已经加入的SystemStatus
	virtual void afterAdd(CSystemStatus *pSystemStatus)
	{
		return;
	}

	///更新前触发	
	///@param	pSystemStatus	被刷新的CSystemStatus
	///@param	pNewSystemStatus	新的值
	virtual void beforeUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus)
	{
		return;
	}
	
	///更新后触发
	///@param	pSystemStatus	被刷新的CSystemStatus
	virtual void afterUpdate(CSystemStatus *pSystemStatus)
	{
		return;
	}
	
	///删除前触发
	///@param	pSystemStatus	要删除的CSystemStatus
	virtual void beforeRemove(CSystemStatus *pSystemStatus)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CSystemStatusFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusCommitTrigger是确认QDP状态表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusCommitTrigger
{
public:
	///构造方法
	CSystemStatusCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CSystemStatusCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CSystemStatusFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pSystemStatus	已经加入的SystemStatus
	virtual void commitAdd(CSystemStatus *pSystemStatus)
	{
		return;
	}

	///更新后触发
	///@param	pSystemStatus	被刷新的CSystemStatus
	///@param	poldSystemStatus	原来的值
	virtual void commitUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pOldSystemStatus)
	{
		return;
	}
	
	///删除后触发
	///@param	pSystemStatus	已经删除的CSystemStatus
	virtual void commitRemove(CWriteableSystemStatus *pSystemStatus)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CSystemStatusFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CSystemStatusIterator是一个对QDP状态表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemStatusIterator
{
public:
	///构造方法
	CSystemStatusIterator(void)
	{
	}

	///构造方法
	CSystemStatusIterator(CSystemStatusFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CSystemStatusIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个SystemStatus
	///@return	下一个满足条件CSystemStatus，如果已经没有一个满足要求了，则返回NULL
	virtual CSystemStatus *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CSystemStatusFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pSystemStatus 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSystemStatus * pSystemStatus,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CSystemStatusFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableOrderAction是一个存储报单操作的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableOrderAction
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableOrderAction *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///交易所代码
	CExchangeIDType ExchangeID;
	///报单编号
	COrderSysIDType OrderSysID;
	///经纪公司编号
	CBrokerIDType BrokerID;
	///投资者编号
	CInvestorIDType InvestorID;
	///用户代码
	CUserIDType UserID;
	///合约代码
	CInstrumentIDType InstrumentID;
	///本次撤单操作的本地编号
	CUserOrderLocalIDType UserOrderActionLocalID;
	///被撤订单的本地报单编号
	CUserOrderLocalIDType UserOrderLocalID;
	///报单操作标志
	CActionFlagType ActionFlag;
	///价格
	CPriceType LimitPrice;
	///数量变化
	CVolumeType VolumeChange;
	///记录编号
	CSequenceNoType RecNum;
	///前置编号
	CFrontIDType FrontID;
	///会话编号
	CSessionIDType SessionID;
	///用户自定义域
	CCustomType UserCustom;
	///下单席位号
	CSeatIDType SeatID;
	///操作本地编号
	COrderLocalIDType ActionLocalID;
	///客户代码
	CClientIDType ClientID;
	///会员代码
	CParticipantIDType ParticipantID;
	///撤销时间
	CTimeType CancelTime;
	///操作来源
	CActionSourceType ActionSource;
	///是否可以参加交易
	CBoolType Tradable;
	///本地报单编号
	COrderLocalIDType OrderLocalID;
	///伪造Rtn
	CBoolType IsForgeRtn;
	///通道对应的APIID
	CNumberType APIID;
	///下单IP地址
	CIPAddressType IPAddress;
	///下单MAC地址
	CMacAddressType MacAddress;
	///撤单对应的报单类别
	COrderActionTypeType OrderActionType;
	///报单批次号
	COrderSysIDType OrderBatchNo;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	
	///构造对应的报单的指针
	///@param	pFactory	构造对应的报单的指针时，寻找的对象工厂
	///@return	找到的对应的报单的指针，如果找不到则返回NULL
	inline const CWriteableOrder *linkOrder(COrderFactory *pFactory) const;

	///构造对应的报单指针
	///@param	pOrder	要连接到的对象
	///@return	输入的pOrder
	const CWriteableOrder *linkOrder(const CWriteableOrder *pOrder) const
	{
		void *target=(void *)(&(this->pOrder));
		*((const CWriteableOrder **)target)=pOrder;
		return pOrder;
	}
	
	///获取对应的报单的指针
	///@return	找到的对应的报单的指针，如果找不到则返回NULL
	const CWriteableOrder *getOrder(void) const
	{
		return pOrder;
	}
	///构造对应的报单的指针
	///@param	pFactory	构造对应的报单的指针时，寻找的对象工厂
	///@return	找到的对应的报单的指针，如果找不到则返回NULL
	inline const CWriteablePreOrder *linkPreOrder(CPreOrderFactory *pFactory) const;

	///构造对应的报单指针
	///@param	pPreOrder	要连接到的对象
	///@return	输入的pPreOrder
	const CWriteablePreOrder *linkPreOrder(const CWriteablePreOrder *pPreOrder) const
	{
		void *target=(void *)(&(this->pPreOrder));
		*((const CWriteablePreOrder **)target)=pPreOrder;
		return pPreOrder;
	}
	
	///获取对应的报单的指针
	///@return	找到的对应的报单的指针，如果找不到则返回NULL
	const CWriteablePreOrder *getPreOrder(void) const
	{
		return pPreOrder;
	}

private:
	///对应的报单
	const CWriteableOrder *pOrder;
	///对应的报单
	const CWriteablePreOrder *pPreOrder;
};

typedef const CWriteableOrderAction COrderAction;

/////////////////////////////////////////////////////////////////////////
///COrderActionActionTrigger是操作报单操作时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionActionTrigger
{
public:
	///构造方法
	COrderActionActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~COrderActionActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(COrderActionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pOrderAction	要加入的OrderAction
	virtual void beforeAdd(CWriteableOrderAction *pOrderAction)
	{
		return;
	}
	
	///加入后触发
	///@param	pOrderAction	已经加入的OrderAction
	virtual void afterAdd(COrderAction *pOrderAction)
	{
		return;
	}

	///更新前触发	
	///@param	pOrderAction	被刷新的COrderAction
	///@param	pNewOrderAction	新的值
	virtual void beforeUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction)
	{
		return;
	}
	
	///更新后触发
	///@param	pOrderAction	被刷新的COrderAction
	virtual void afterUpdate(COrderAction *pOrderAction)
	{
		return;
	}
	
	///删除前触发
	///@param	pOrderAction	要删除的COrderAction
	virtual void beforeRemove(COrderAction *pOrderAction)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	COrderActionFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///COrderActionCommitTrigger是确认报单操作时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionCommitTrigger
{
public:
	///构造方法
	COrderActionCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~COrderActionCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(COrderActionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pOrderAction	已经加入的OrderAction
	virtual void commitAdd(COrderAction *pOrderAction)
	{
		return;
	}

	///更新后触发
	///@param	pOrderAction	被刷新的COrderAction
	///@param	poldOrderAction	原来的值
	virtual void commitUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pOldOrderAction)
	{
		return;
	}
	
	///删除后触发
	///@param	pOrderAction	已经删除的COrderAction
	virtual void commitRemove(CWriteableOrderAction *pOrderAction)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	COrderActionFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///COrderActionIterator是一个对报单操作的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionIterator
{
public:
	///构造方法
	COrderActionIterator(void)
	{
	}

	///构造方法
	COrderActionIterator(COrderActionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~COrderActionIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个OrderAction
	///@return	下一个满足条件COrderAction，如果已经没有一个满足要求了，则返回NULL
	virtual COrderAction *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	COrderActionFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pOrderAction 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrderAction * pOrderAction,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	COrderActionFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableOrder是一个存储委托表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableOrder : public COrderField
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableOrder *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	
	unsigned int HashExchangeIDOrderSysID;
	
	///计算ExchangeIDOrderSysID的hash值
	void calHashExchangeIDOrderSysID(void)
	{
		unsigned key=0;
		key=ExchangeID.hash(key);
		key=OrderSysID.hash(key);
		HashExchangeIDOrderSysID=key;
	}
	
	///根据需要情况，更新ExchangeIDOrderSysID的hash值
	void updateHashExchangeIDOrderSysID(void)
	{
	}
	unsigned int HashUserIDAndUserOrderLocalID;
	
	///计算UserIDAndUserOrderLocalID的hash值
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
	
	///根据需要情况，更新UserIDAndUserOrderLocalID的hash值
	void updateHashUserIDAndUserOrderLocalID(void)
	{
	}
	
	///计算所有的hash值
	void calAllHash(void)
	{
		calHashExchangeIDOrderSysID();
		calHashUserIDAndUserOrderLocalID();
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
		updateHashExchangeIDOrderSysID();
		updateHashUserIDAndUserOrderLocalID();
	}
	
	///构造对应的投资者的指针
	///@param	pFactory	构造对应的投资者的指针时，寻找的对象工厂
	///@return	找到的对应的投资者的指针，如果找不到则返回NULL
	inline const CWriteableInvestor *linkInvestor(CInvestorFactory *pFactory) const;

	///构造对应的投资者指针
	///@param	pInvestor	要连接到的对象
	///@return	输入的pInvestor
	const CWriteableInvestor *linkInvestor(const CWriteableInvestor *pInvestor) const
	{
		void *target=(void *)(&(this->pInvestor));
		*((const CWriteableInvestor **)target)=pInvestor;
		return pInvestor;
	}
	
	///获取对应的投资者的指针
	///@return	找到的对应的投资者的指针，如果找不到则返回NULL
	const CWriteableInvestor *getInvestor(void) const
	{
		return pInvestor;
	}
	///构造对应的交易编码的指针
	///@param	pFactory	构造对应的交易编码的指针时，寻找的对象工厂
	///@return	找到的对应的交易编码的指针，如果找不到则返回NULL
	inline const CWriteableClientTradingID *linkClientTradingID(CClientTradingIDFactory *pFactory) const;

	///构造对应的交易编码指针
	///@param	pClientTradingID	要连接到的对象
	///@return	输入的pClientTradingID
	const CWriteableClientTradingID *linkClientTradingID(const CWriteableClientTradingID *pClientTradingID) const
	{
		void *target=(void *)(&(this->pClientTradingID));
		*((const CWriteableClientTradingID **)target)=pClientTradingID;
		return pClientTradingID;
	}
	
	///获取对应的交易编码的指针
	///@return	找到的对应的交易编码的指针，如果找不到则返回NULL
	const CWriteableClientTradingID *getClientTradingID(void) const
	{
		return pClientTradingID;
	}
	///构造对应的帐户的指针
	///@param	pFactory	构造对应的帐户的指针时，寻找的对象工厂
	///@return	找到的对应的帐户的指针，如果找不到则返回NULL
	inline const CWriteableInvestorAccount *linkInvestorAccount(CInvestorAccountFactory *pFactory) const;

	///构造对应的帐户指针
	///@param	pInvestorAccount	要连接到的对象
	///@return	输入的pInvestorAccount
	const CWriteableInvestorAccount *linkInvestorAccount(const CWriteableInvestorAccount *pInvestorAccount) const
	{
		void *target=(void *)(&(this->pInvestorAccount));
		*((const CWriteableInvestorAccount **)target)=pInvestorAccount;
		return pInvestorAccount;
	}
	
	///获取对应的帐户的指针
	///@return	找到的对应的帐户的指针，如果找不到则返回NULL
	const CWriteableInvestorAccount *getInvestorAccount(void) const
	{
		return pInvestorAccount;
	}
	///构造对应的合约持仓信息的指针
	///@param	pFactory	构造对应的合约持仓信息的指针时，寻找的对象工厂
	///@return	找到的对应的合约持仓信息的指针，如果找不到则返回NULL
	inline const CWriteableInvestorPosition *linkInvestorPosition(CInvestorPositionFactory *pFactory) const;

	///构造对应的合约持仓信息指针
	///@param	pInvestorPosition	要连接到的对象
	///@return	输入的pInvestorPosition
	const CWriteableInvestorPosition *linkInvestorPosition(const CWriteableInvestorPosition *pInvestorPosition) const
	{
		void *target=(void *)(&(this->pInvestorPosition));
		*((const CWriteableInvestorPosition **)target)=pInvestorPosition;
		return pInvestorPosition;
	}
	
	///获取对应的合约持仓信息的指针
	///@return	找到的对应的合约持仓信息的指针，如果找不到则返回NULL
	const CWriteableInvestorPosition *getInvestorPosition(void) const
	{
		return pInvestorPosition;
	}
	///构造对应的合约信息的指针
	///@param	pFactory	构造对应的合约信息的指针时，寻找的对象工厂
	///@return	找到的对应的合约信息的指针，如果找不到则返回NULL
	inline const CWriteableInstrument *linkInstrument(CInstrumentFactory *pFactory) const;

	///构造对应的合约信息指针
	///@param	pInstrument	要连接到的对象
	///@return	输入的pInstrument
	const CWriteableInstrument *linkInstrument(const CWriteableInstrument *pInstrument) const
	{
		void *target=(void *)(&(this->pInstrument));
		*((const CWriteableInstrument **)target)=pInstrument;
		return pInstrument;
	}
	
	///获取对应的合约信息的指针
	///@return	找到的对应的合约信息的指针，如果找不到则返回NULL
	const CWriteableInstrument *getInstrument(void) const
	{
		return pInstrument;
	}
	///构造对应的投资者保证金率信息的指针
	///@param	pFactory	构造对应的投资者保证金率信息的指针时，寻找的对象工厂
	///@return	找到的对应的投资者保证金率信息的指针，如果找不到则返回NULL
	inline const CWriteableInvestorMargin *linkInvestorMargin(CInvestorMarginFactory *pFactory) const;

	///构造对应的投资者保证金率信息指针
	///@param	pInvestorMargin	要连接到的对象
	///@return	输入的pInvestorMargin
	const CWriteableInvestorMargin *linkInvestorMargin(const CWriteableInvestorMargin *pInvestorMargin) const
	{
		void *target=(void *)(&(this->pInvestorMargin));
		*((const CWriteableInvestorMargin **)target)=pInvestorMargin;
		return pInvestorMargin;
	}
	
	///获取对应的投资者保证金率信息的指针
	///@return	找到的对应的投资者保证金率信息的指针，如果找不到则返回NULL
	const CWriteableInvestorMargin *getInvestorMargin(void) const
	{
		return pInvestorMargin;
	}
	///构造对应的投资者手续费率信息的指针
	///@param	pFactory	构造对应的投资者手续费率信息的指针时，寻找的对象工厂
	///@return	找到的对应的投资者手续费率信息的指针，如果找不到则返回NULL
	inline const CWriteableInvestorFee *linkInvestorFee(CInvestorFeeFactory *pFactory) const;

	///构造对应的投资者手续费率信息指针
	///@param	pInvestorFee	要连接到的对象
	///@return	输入的pInvestorFee
	const CWriteableInvestorFee *linkInvestorFee(const CWriteableInvestorFee *pInvestorFee) const
	{
		void *target=(void *)(&(this->pInvestorFee));
		*((const CWriteableInvestorFee **)target)=pInvestorFee;
		return pInvestorFee;
	}
	
	///获取对应的投资者手续费率信息的指针
	///@return	找到的对应的投资者手续费率信息的指针，如果找不到则返回NULL
	const CWriteableInvestorFee *getInvestorFee(void) const
	{
		return pInvestorFee;
	}
	///构造对应的投资者期权手续费率信息的指针
	///@param	pFactory	构造对应的投资者期权手续费率信息的指针时，寻找的对象工厂
	///@return	找到的对应的投资者期权手续费率信息的指针，如果找不到则返回NULL
	inline const CWriteableInvestorOptionFee *linkInvestorOptionFee(CInvestorOptionFeeFactory *pFactory) const;

	///构造对应的投资者期权手续费率信息指针
	///@param	pInvestorOptionFee	要连接到的对象
	///@return	输入的pInvestorOptionFee
	const CWriteableInvestorOptionFee *linkInvestorOptionFee(const CWriteableInvestorOptionFee *pInvestorOptionFee) const
	{
		void *target=(void *)(&(this->pInvestorOptionFee));
		*((const CWriteableInvestorOptionFee **)target)=pInvestorOptionFee;
		return pInvestorOptionFee;
	}
	
	///获取对应的投资者期权手续费率信息的指针
	///@return	找到的对应的投资者期权手续费率信息的指针，如果找不到则返回NULL
	const CWriteableInvestorOptionFee *getInvestorOptionFee(void) const
	{
		return pInvestorOptionFee;
	}
	///构造对应的合约大边组持仓信息的指针
	///@param	pFactory	构造对应的合约大边组持仓信息的指针时，寻找的对象工厂
	///@return	找到的对应的合约大边组持仓信息的指针，如果找不到则返回NULL
	inline const CWriteablePartClientInsGroupPosition *linkClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory) const;

	///构造对应的合约大边组持仓信息指针
	///@param	pPartClientInsGroupPosition	要连接到的对象
	///@return	输入的pPartClientInsGroupPosition
	const CWriteablePartClientInsGroupPosition *linkClientGroupPosition(const CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition) const
	{
		void *target=(void *)(&(this->pClientGroupPosition));
		*((const CWriteablePartClientInsGroupPosition **)target)=pPartClientInsGroupPosition;
		return pPartClientInsGroupPosition;
	}
	
	///获取对应的合约大边组持仓信息的指针
	///@return	找到的对应的合约大边组持仓信息的指针，如果找不到则返回NULL
	const CWriteablePartClientInsGroupPosition *getClientGroupPosition(void) const
	{
		return pClientGroupPosition;
	}

private:
	///对应的投资者
	const CWriteableInvestor *pInvestor;
	///对应的交易编码
	const CWriteableClientTradingID *pClientTradingID;
	///对应的帐户
	const CWriteableInvestorAccount *pInvestorAccount;
	///对应的合约持仓信息
	const CWriteableInvestorPosition *pInvestorPosition;
	///对应的合约信息
	const CWriteableInstrument *pInstrument;
	///对应的投资者保证金率信息
	const CWriteableInvestorMargin *pInvestorMargin;
	///对应的投资者手续费率信息
	const CWriteableInvestorFee *pInvestorFee;
	///对应的投资者期权手续费率信息
	const CWriteableInvestorOptionFee *pInvestorOptionFee;
	///对应的合约大边组持仓信息
	const CWriteablePartClientInsGroupPosition *pClientGroupPosition;
};

typedef const CWriteableOrder COrder;

/////////////////////////////////////////////////////////////////////////
///COrderActionTrigger是操作委托表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderActionTrigger
{
public:
	///构造方法
	COrderActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~COrderActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(COrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pOrder	要加入的Order
	virtual void beforeAdd(CWriteableOrder *pOrder)
	{
		return;
	}
	
	///加入后触发
	///@param	pOrder	已经加入的Order
	virtual void afterAdd(COrder *pOrder)
	{
		return;
	}

	///更新前触发	
	///@param	pOrder	被刷新的COrder
	///@param	pNewOrder	新的值
	virtual void beforeUpdate(COrder *pOrder, CWriteableOrder *pNewOrder)
	{
		return;
	}
	
	///更新后触发
	///@param	pOrder	被刷新的COrder
	virtual void afterUpdate(COrder *pOrder)
	{
		return;
	}
	
	///删除前触发
	///@param	pOrder	要删除的COrder
	virtual void beforeRemove(COrder *pOrder)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	COrderFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///COrderCommitTrigger是确认委托表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderCommitTrigger
{
public:
	///构造方法
	COrderCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~COrderCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(COrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pOrder	已经加入的Order
	virtual void commitAdd(COrder *pOrder)
	{
		return;
	}

	///更新后触发
	///@param	pOrder	被刷新的COrder
	///@param	poldOrder	原来的值
	virtual void commitUpdate(COrder *pOrder, CWriteableOrder *pOldOrder)
	{
		return;
	}
	
	///删除后触发
	///@param	pOrder	已经删除的COrder
	virtual void commitRemove(CWriteableOrder *pOrder)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	COrderFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///COrderIterator是一个对委托表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderIterator
{
public:
	///构造方法
	COrderIterator(void)
	{
	}

	///构造方法
	COrderIterator(COrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~COrderIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个Order
	///@return	下一个满足条件COrder，如果已经没有一个满足要求了，则返回NULL
	virtual COrder *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	COrderFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pOrder 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrder * pOrder,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	COrderFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableTrade是一个存储成交表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableTrade : public CTradeField
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableTrade *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableTrade CTrade;

/////////////////////////////////////////////////////////////////////////
///CTradeActionTrigger是操作成交表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeActionTrigger
{
public:
	///构造方法
	CTradeActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CTradeActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CTradeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pTrade	要加入的Trade
	virtual void beforeAdd(CWriteableTrade *pTrade)
	{
		return;
	}
	
	///加入后触发
	///@param	pTrade	已经加入的Trade
	virtual void afterAdd(CTrade *pTrade)
	{
		return;
	}

	///更新前触发	
	///@param	pTrade	被刷新的CTrade
	///@param	pNewTrade	新的值
	virtual void beforeUpdate(CTrade *pTrade, CWriteableTrade *pNewTrade)
	{
		return;
	}
	
	///更新后触发
	///@param	pTrade	被刷新的CTrade
	virtual void afterUpdate(CTrade *pTrade)
	{
		return;
	}
	
	///删除前触发
	///@param	pTrade	要删除的CTrade
	virtual void beforeRemove(CTrade *pTrade)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CTradeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CTradeCommitTrigger是确认成交表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeCommitTrigger
{
public:
	///构造方法
	CTradeCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CTradeCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CTradeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pTrade	已经加入的Trade
	virtual void commitAdd(CTrade *pTrade)
	{
		return;
	}

	///更新后触发
	///@param	pTrade	被刷新的CTrade
	///@param	poldTrade	原来的值
	virtual void commitUpdate(CTrade *pTrade, CWriteableTrade *pOldTrade)
	{
		return;
	}
	
	///删除后触发
	///@param	pTrade	已经删除的CTrade
	virtual void commitRemove(CWriteableTrade *pTrade)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CTradeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CTradeIterator是一个对成交表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CTradeIterator
{
public:
	///构造方法
	CTradeIterator(void)
	{
	}

	///构造方法
	CTradeIterator(CTradeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CTradeIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个Trade
	///@return	下一个满足条件CTrade，如果已经没有一个满足要求了，则返回NULL
	virtual CTrade *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CTradeFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pTrade 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableTrade * pTrade,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CTradeFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteablePreOrder是一个存储预委托表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteablePreOrder : public CInputOrderField
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteablePreOrder *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	
	unsigned int HashUserIDAndUserOrderLocalID;
	
	///计算UserIDAndUserOrderLocalID的hash值
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
	
	///根据需要情况，更新UserIDAndUserOrderLocalID的hash值
	void updateHashUserIDAndUserOrderLocalID(void)
	{
	}
	
	///计算所有的hash值
	void calAllHash(void)
	{
		calHashUserIDAndUserOrderLocalID();
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
		updateHashUserIDAndUserOrderLocalID();
	}
	
	///构造对应的投资者的指针
	///@param	pFactory	构造对应的投资者的指针时，寻找的对象工厂
	///@return	找到的对应的投资者的指针，如果找不到则返回NULL
	inline const CWriteableInvestor *linkInvestor(CInvestorFactory *pFactory) const;

	///构造对应的投资者指针
	///@param	pInvestor	要连接到的对象
	///@return	输入的pInvestor
	const CWriteableInvestor *linkInvestor(const CWriteableInvestor *pInvestor) const
	{
		void *target=(void *)(&(this->pInvestor));
		*((const CWriteableInvestor **)target)=pInvestor;
		return pInvestor;
	}
	
	///获取对应的投资者的指针
	///@return	找到的对应的投资者的指针，如果找不到则返回NULL
	const CWriteableInvestor *getInvestor(void) const
	{
		return pInvestor;
	}
	///构造对应的交易编码的指针
	///@param	pFactory	构造对应的交易编码的指针时，寻找的对象工厂
	///@return	找到的对应的交易编码的指针，如果找不到则返回NULL
	inline const CWriteableClientTradingID *linkClientTradingID(CClientTradingIDFactory *pFactory) const;

	///构造对应的交易编码指针
	///@param	pClientTradingID	要连接到的对象
	///@return	输入的pClientTradingID
	const CWriteableClientTradingID *linkClientTradingID(const CWriteableClientTradingID *pClientTradingID) const
	{
		void *target=(void *)(&(this->pClientTradingID));
		*((const CWriteableClientTradingID **)target)=pClientTradingID;
		return pClientTradingID;
	}
	
	///获取对应的交易编码的指针
	///@return	找到的对应的交易编码的指针，如果找不到则返回NULL
	const CWriteableClientTradingID *getClientTradingID(void) const
	{
		return pClientTradingID;
	}
	///构造对应的帐户的指针
	///@param	pFactory	构造对应的帐户的指针时，寻找的对象工厂
	///@return	找到的对应的帐户的指针，如果找不到则返回NULL
	inline const CWriteableInvestorAccount *linkInvestorAccount(CInvestorAccountFactory *pFactory) const;

	///构造对应的帐户指针
	///@param	pInvestorAccount	要连接到的对象
	///@return	输入的pInvestorAccount
	const CWriteableInvestorAccount *linkInvestorAccount(const CWriteableInvestorAccount *pInvestorAccount) const
	{
		void *target=(void *)(&(this->pInvestorAccount));
		*((const CWriteableInvestorAccount **)target)=pInvestorAccount;
		return pInvestorAccount;
	}
	
	///获取对应的帐户的指针
	///@return	找到的对应的帐户的指针，如果找不到则返回NULL
	const CWriteableInvestorAccount *getInvestorAccount(void) const
	{
		return pInvestorAccount;
	}
	///构造对应的合约持仓信息的指针
	///@param	pFactory	构造对应的合约持仓信息的指针时，寻找的对象工厂
	///@return	找到的对应的合约持仓信息的指针，如果找不到则返回NULL
	inline const CWriteableInvestorPosition *linkInvestorPosition(CInvestorPositionFactory *pFactory) const;

	///构造对应的合约持仓信息指针
	///@param	pInvestorPosition	要连接到的对象
	///@return	输入的pInvestorPosition
	const CWriteableInvestorPosition *linkInvestorPosition(const CWriteableInvestorPosition *pInvestorPosition) const
	{
		void *target=(void *)(&(this->pInvestorPosition));
		*((const CWriteableInvestorPosition **)target)=pInvestorPosition;
		return pInvestorPosition;
	}
	
	///获取对应的合约持仓信息的指针
	///@return	找到的对应的合约持仓信息的指针，如果找不到则返回NULL
	const CWriteableInvestorPosition *getInvestorPosition(void) const
	{
		return pInvestorPosition;
	}
	///构造对应的合约信息的指针
	///@param	pFactory	构造对应的合约信息的指针时，寻找的对象工厂
	///@return	找到的对应的合约信息的指针，如果找不到则返回NULL
	inline const CWriteableInstrument *linkInstrument(CInstrumentFactory *pFactory) const;

	///构造对应的合约信息指针
	///@param	pInstrument	要连接到的对象
	///@return	输入的pInstrument
	const CWriteableInstrument *linkInstrument(const CWriteableInstrument *pInstrument) const
	{
		void *target=(void *)(&(this->pInstrument));
		*((const CWriteableInstrument **)target)=pInstrument;
		return pInstrument;
	}
	
	///获取对应的合约信息的指针
	///@return	找到的对应的合约信息的指针，如果找不到则返回NULL
	const CWriteableInstrument *getInstrument(void) const
	{
		return pInstrument;
	}
	///构造对应的投资者保证金率信息的指针
	///@param	pFactory	构造对应的投资者保证金率信息的指针时，寻找的对象工厂
	///@return	找到的对应的投资者保证金率信息的指针，如果找不到则返回NULL
	inline const CWriteableInvestorMargin *linkInvestorMargin(CInvestorMarginFactory *pFactory) const;

	///构造对应的投资者保证金率信息指针
	///@param	pInvestorMargin	要连接到的对象
	///@return	输入的pInvestorMargin
	const CWriteableInvestorMargin *linkInvestorMargin(const CWriteableInvestorMargin *pInvestorMargin) const
	{
		void *target=(void *)(&(this->pInvestorMargin));
		*((const CWriteableInvestorMargin **)target)=pInvestorMargin;
		return pInvestorMargin;
	}
	
	///获取对应的投资者保证金率信息的指针
	///@return	找到的对应的投资者保证金率信息的指针，如果找不到则返回NULL
	const CWriteableInvestorMargin *getInvestorMargin(void) const
	{
		return pInvestorMargin;
	}
	///构造对应的投资者手续费率信息的指针
	///@param	pFactory	构造对应的投资者手续费率信息的指针时，寻找的对象工厂
	///@return	找到的对应的投资者手续费率信息的指针，如果找不到则返回NULL
	inline const CWriteableInvestorFee *linkInvestorFee(CInvestorFeeFactory *pFactory) const;

	///构造对应的投资者手续费率信息指针
	///@param	pInvestorFee	要连接到的对象
	///@return	输入的pInvestorFee
	const CWriteableInvestorFee *linkInvestorFee(const CWriteableInvestorFee *pInvestorFee) const
	{
		void *target=(void *)(&(this->pInvestorFee));
		*((const CWriteableInvestorFee **)target)=pInvestorFee;
		return pInvestorFee;
	}
	
	///获取对应的投资者手续费率信息的指针
	///@return	找到的对应的投资者手续费率信息的指针，如果找不到则返回NULL
	const CWriteableInvestorFee *getInvestorFee(void) const
	{
		return pInvestorFee;
	}
	///构造对应的投资者期权手续费率信息的指针
	///@param	pFactory	构造对应的投资者期权手续费率信息的指针时，寻找的对象工厂
	///@return	找到的对应的投资者期权手续费率信息的指针，如果找不到则返回NULL
	inline const CWriteableInvestorOptionFee *linkInvestorOptionFee(CInvestorOptionFeeFactory *pFactory) const;

	///构造对应的投资者期权手续费率信息指针
	///@param	pInvestorOptionFee	要连接到的对象
	///@return	输入的pInvestorOptionFee
	const CWriteableInvestorOptionFee *linkInvestorOptionFee(const CWriteableInvestorOptionFee *pInvestorOptionFee) const
	{
		void *target=(void *)(&(this->pInvestorOptionFee));
		*((const CWriteableInvestorOptionFee **)target)=pInvestorOptionFee;
		return pInvestorOptionFee;
	}
	
	///获取对应的投资者期权手续费率信息的指针
	///@return	找到的对应的投资者期权手续费率信息的指针，如果找不到则返回NULL
	const CWriteableInvestorOptionFee *getInvestorOptionFee(void) const
	{
		return pInvestorOptionFee;
	}
	///构造对应的合约大边组持仓信息的指针
	///@param	pFactory	构造对应的合约大边组持仓信息的指针时，寻找的对象工厂
	///@return	找到的对应的合约大边组持仓信息的指针，如果找不到则返回NULL
	inline const CWriteablePartClientInsGroupPosition *linkClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory) const;

	///构造对应的合约大边组持仓信息指针
	///@param	pPartClientInsGroupPosition	要连接到的对象
	///@return	输入的pPartClientInsGroupPosition
	const CWriteablePartClientInsGroupPosition *linkClientGroupPosition(const CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition) const
	{
		void *target=(void *)(&(this->pClientGroupPosition));
		*((const CWriteablePartClientInsGroupPosition **)target)=pPartClientInsGroupPosition;
		return pPartClientInsGroupPosition;
	}
	
	///获取对应的合约大边组持仓信息的指针
	///@return	找到的对应的合约大边组持仓信息的指针，如果找不到则返回NULL
	const CWriteablePartClientInsGroupPosition *getClientGroupPosition(void) const
	{
		return pClientGroupPosition;
	}

private:
	///对应的投资者
	const CWriteableInvestor *pInvestor;
	///对应的交易编码
	const CWriteableClientTradingID *pClientTradingID;
	///对应的帐户
	const CWriteableInvestorAccount *pInvestorAccount;
	///对应的合约持仓信息
	const CWriteableInvestorPosition *pInvestorPosition;
	///对应的合约信息
	const CWriteableInstrument *pInstrument;
	///对应的投资者保证金率信息
	const CWriteableInvestorMargin *pInvestorMargin;
	///对应的投资者手续费率信息
	const CWriteableInvestorFee *pInvestorFee;
	///对应的投资者期权手续费率信息
	const CWriteableInvestorOptionFee *pInvestorOptionFee;
	///对应的合约大边组持仓信息
	const CWriteablePartClientInsGroupPosition *pClientGroupPosition;
};

typedef const CWriteablePreOrder CPreOrder;

/////////////////////////////////////////////////////////////////////////
///CPreOrderActionTrigger是操作预委托表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderActionTrigger
{
public:
	///构造方法
	CPreOrderActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CPreOrderActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CPreOrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pPreOrder	要加入的PreOrder
	virtual void beforeAdd(CWriteablePreOrder *pPreOrder)
	{
		return;
	}
	
	///加入后触发
	///@param	pPreOrder	已经加入的PreOrder
	virtual void afterAdd(CPreOrder *pPreOrder)
	{
		return;
	}

	///更新前触发	
	///@param	pPreOrder	被刷新的CPreOrder
	///@param	pNewPreOrder	新的值
	virtual void beforeUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder)
	{
		return;
	}
	
	///更新后触发
	///@param	pPreOrder	被刷新的CPreOrder
	virtual void afterUpdate(CPreOrder *pPreOrder)
	{
		return;
	}
	
	///删除前触发
	///@param	pPreOrder	要删除的CPreOrder
	virtual void beforeRemove(CPreOrder *pPreOrder)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CPreOrderFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderCommitTrigger是确认预委托表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderCommitTrigger
{
public:
	///构造方法
	CPreOrderCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CPreOrderCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CPreOrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pPreOrder	已经加入的PreOrder
	virtual void commitAdd(CPreOrder *pPreOrder)
	{
		return;
	}

	///更新后触发
	///@param	pPreOrder	被刷新的CPreOrder
	///@param	poldPreOrder	原来的值
	virtual void commitUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pOldPreOrder)
	{
		return;
	}
	
	///删除后触发
	///@param	pPreOrder	已经删除的CPreOrder
	virtual void commitRemove(CWriteablePreOrder *pPreOrder)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CPreOrderFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CPreOrderIterator是一个对预委托表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPreOrderIterator
{
public:
	///构造方法
	CPreOrderIterator(void)
	{
	}

	///构造方法
	CPreOrderIterator(CPreOrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CPreOrderIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个PreOrder
	///@return	下一个满足条件CPreOrder，如果已经没有一个满足要求了，则返回NULL
	virtual CPreOrder *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CPreOrderFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pPreOrder 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteablePreOrder * pPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CPreOrderFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableIndexPreOrder是一个存储索引预委托表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableIndexPreOrder
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableIndexPreOrder *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///交易所代码
	CExchangeIDType ExchangeID;
	///投资者编号
	CInvestorIDType InvestorID;
	///合约代码
	CInstrumentIDType InstrumentID;
	///投机套保标志
	CHedgeFlagType HedgeFlag;
	///买卖方向
	CDirectionType Direction;
	///通道对应的APIID
	CNumberType APIID;
	///交易编码
	CClientIDType ClientID;
	///保证金组合类型
	CClientMarginCombTypeType MarginCombType;
	///合约组代码
	CInstrumentGroupIDType InstrumentGroupID;
	
	unsigned int HashALLFlds;
	
	///计算ALLFlds的hash值
	void calHashALLFlds(void)
	{
		unsigned key=0;
		key=ExchangeID.hash(key);
		key=InvestorID.hash(key);
		key=InstrumentID.hash(key);
		key=HedgeFlag.hash(key);
		HashALLFlds=key;
	}
	
	///根据需要情况，更新ALLFlds的hash值
	void updateHashALLFlds(void)
	{
	}
	
	///计算所有的hash值
	void calAllHash(void)
	{
		calHashALLFlds();
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
		updateHashALLFlds();
	}
	
	///构造对应的投资者的指针
	///@param	pFactory	构造对应的投资者的指针时，寻找的对象工厂
	///@return	找到的对应的投资者的指针，如果找不到则返回NULL
	inline const CWriteableInvestor *linkInvestor(CInvestorFactory *pFactory) const;

	///构造对应的投资者指针
	///@param	pInvestor	要连接到的对象
	///@return	输入的pInvestor
	const CWriteableInvestor *linkInvestor(const CWriteableInvestor *pInvestor) const
	{
		void *target=(void *)(&(this->pInvestor));
		*((const CWriteableInvestor **)target)=pInvestor;
		return pInvestor;
	}
	
	///获取对应的投资者的指针
	///@return	找到的对应的投资者的指针，如果找不到则返回NULL
	const CWriteableInvestor *getInvestor(void) const
	{
		return pInvestor;
	}
	///构造对应的交易编码的指针
	///@param	pFactory	构造对应的交易编码的指针时，寻找的对象工厂
	///@return	找到的对应的交易编码的指针，如果找不到则返回NULL
	inline const CWriteableClientTradingID *linkClientTradingID(CClientTradingIDFactory *pFactory) const;

	///构造对应的交易编码指针
	///@param	pClientTradingID	要连接到的对象
	///@return	输入的pClientTradingID
	const CWriteableClientTradingID *linkClientTradingID(const CWriteableClientTradingID *pClientTradingID) const
	{
		void *target=(void *)(&(this->pClientTradingID));
		*((const CWriteableClientTradingID **)target)=pClientTradingID;
		return pClientTradingID;
	}
	
	///获取对应的交易编码的指针
	///@return	找到的对应的交易编码的指针，如果找不到则返回NULL
	const CWriteableClientTradingID *getClientTradingID(void) const
	{
		return pClientTradingID;
	}
	///构造对应的帐户的指针
	///@param	pFactory	构造对应的帐户的指针时，寻找的对象工厂
	///@return	找到的对应的帐户的指针，如果找不到则返回NULL
	inline const CWriteableInvestorAccount *linkInvestorAccount(CInvestorAccountFactory *pFactory) const;

	///构造对应的帐户指针
	///@param	pInvestorAccount	要连接到的对象
	///@return	输入的pInvestorAccount
	const CWriteableInvestorAccount *linkInvestorAccount(const CWriteableInvestorAccount *pInvestorAccount) const
	{
		void *target=(void *)(&(this->pInvestorAccount));
		*((const CWriteableInvestorAccount **)target)=pInvestorAccount;
		return pInvestorAccount;
	}
	
	///获取对应的帐户的指针
	///@return	找到的对应的帐户的指针，如果找不到则返回NULL
	const CWriteableInvestorAccount *getInvestorAccount(void) const
	{
		return pInvestorAccount;
	}
	///构造对应的合约信息的指针
	///@param	pFactory	构造对应的合约信息的指针时，寻找的对象工厂
	///@return	找到的对应的合约信息的指针，如果找不到则返回NULL
	inline const CWriteableInstrument *linkInstrument(CInstrumentFactory *pFactory) const;

	///构造对应的合约信息指针
	///@param	pInstrument	要连接到的对象
	///@return	输入的pInstrument
	const CWriteableInstrument *linkInstrument(const CWriteableInstrument *pInstrument) const
	{
		void *target=(void *)(&(this->pInstrument));
		*((const CWriteableInstrument **)target)=pInstrument;
		return pInstrument;
	}
	
	///获取对应的合约信息的指针
	///@return	找到的对应的合约信息的指针，如果找不到则返回NULL
	const CWriteableInstrument *getInstrument(void) const
	{
		return pInstrument;
	}
	///构造对应的投资者保证金率信息的指针
	///@param	pFactory	构造对应的投资者保证金率信息的指针时，寻找的对象工厂
	///@return	找到的对应的投资者保证金率信息的指针，如果找不到则返回NULL
	inline const CWriteableInvestorMargin *linkInvestorMargin(CInvestorMarginFactory *pFactory) const;

	///构造对应的投资者保证金率信息指针
	///@param	pInvestorMargin	要连接到的对象
	///@return	输入的pInvestorMargin
	const CWriteableInvestorMargin *linkInvestorMargin(const CWriteableInvestorMargin *pInvestorMargin) const
	{
		void *target=(void *)(&(this->pInvestorMargin));
		*((const CWriteableInvestorMargin **)target)=pInvestorMargin;
		return pInvestorMargin;
	}
	
	///获取对应的投资者保证金率信息的指针
	///@return	找到的对应的投资者保证金率信息的指针，如果找不到则返回NULL
	const CWriteableInvestorMargin *getInvestorMargin(void) const
	{
		return pInvestorMargin;
	}
	///构造对应的投资者手续费率信息的指针
	///@param	pFactory	构造对应的投资者手续费率信息的指针时，寻找的对象工厂
	///@return	找到的对应的投资者手续费率信息的指针，如果找不到则返回NULL
	inline const CWriteableInvestorFee *linkInvestorFee(CInvestorFeeFactory *pFactory) const;

	///构造对应的投资者手续费率信息指针
	///@param	pInvestorFee	要连接到的对象
	///@return	输入的pInvestorFee
	const CWriteableInvestorFee *linkInvestorFee(const CWriteableInvestorFee *pInvestorFee) const
	{
		void *target=(void *)(&(this->pInvestorFee));
		*((const CWriteableInvestorFee **)target)=pInvestorFee;
		return pInvestorFee;
	}
	
	///获取对应的投资者手续费率信息的指针
	///@return	找到的对应的投资者手续费率信息的指针，如果找不到则返回NULL
	const CWriteableInvestorFee *getInvestorFee(void) const
	{
		return pInvestorFee;
	}
	///构造对应的合约大边组持仓信息的指针
	///@param	pFactory	构造对应的合约大边组持仓信息的指针时，寻找的对象工厂
	///@return	找到的对应的合约大边组持仓信息的指针，如果找不到则返回NULL
	inline const CWriteablePartClientInsGroupPosition *linkClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory) const;

	///构造对应的合约大边组持仓信息指针
	///@param	pPartClientInsGroupPosition	要连接到的对象
	///@return	输入的pPartClientInsGroupPosition
	const CWriteablePartClientInsGroupPosition *linkClientGroupPosition(const CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition) const
	{
		void *target=(void *)(&(this->pClientGroupPosition));
		*((const CWriteablePartClientInsGroupPosition **)target)=pPartClientInsGroupPosition;
		return pPartClientInsGroupPosition;
	}
	
	///获取对应的合约大边组持仓信息的指针
	///@return	找到的对应的合约大边组持仓信息的指针，如果找不到则返回NULL
	const CWriteablePartClientInsGroupPosition *getClientGroupPosition(void) const
	{
		return pClientGroupPosition;
	}

private:
	///对应的投资者
	const CWriteableInvestor *pInvestor;
	///对应的交易编码
	const CWriteableClientTradingID *pClientTradingID;
	///对应的帐户
	const CWriteableInvestorAccount *pInvestorAccount;
	///对应的合约信息
	const CWriteableInstrument *pInstrument;
	///对应的投资者保证金率信息
	const CWriteableInvestorMargin *pInvestorMargin;
	///对应的投资者手续费率信息
	const CWriteableInvestorFee *pInvestorFee;
	///对应的合约大边组持仓信息
	const CWriteablePartClientInsGroupPosition *pClientGroupPosition;
};

typedef const CWriteableIndexPreOrder CIndexPreOrder;

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderActionTrigger是操作索引预委托表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderActionTrigger
{
public:
	///构造方法
	CIndexPreOrderActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CIndexPreOrderActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CIndexPreOrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pIndexPreOrder	要加入的IndexPreOrder
	virtual void beforeAdd(CWriteableIndexPreOrder *pIndexPreOrder)
	{
		return;
	}
	
	///加入后触发
	///@param	pIndexPreOrder	已经加入的IndexPreOrder
	virtual void afterAdd(CIndexPreOrder *pIndexPreOrder)
	{
		return;
	}

	///更新前触发	
	///@param	pIndexPreOrder	被刷新的CIndexPreOrder
	///@param	pNewIndexPreOrder	新的值
	virtual void beforeUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder)
	{
		return;
	}
	
	///更新后触发
	///@param	pIndexPreOrder	被刷新的CIndexPreOrder
	virtual void afterUpdate(CIndexPreOrder *pIndexPreOrder)
	{
		return;
	}
	
	///删除前触发
	///@param	pIndexPreOrder	要删除的CIndexPreOrder
	virtual void beforeRemove(CIndexPreOrder *pIndexPreOrder)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CIndexPreOrderFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderCommitTrigger是确认索引预委托表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderCommitTrigger
{
public:
	///构造方法
	CIndexPreOrderCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CIndexPreOrderCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CIndexPreOrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pIndexPreOrder	已经加入的IndexPreOrder
	virtual void commitAdd(CIndexPreOrder *pIndexPreOrder)
	{
		return;
	}

	///更新后触发
	///@param	pIndexPreOrder	被刷新的CIndexPreOrder
	///@param	poldIndexPreOrder	原来的值
	virtual void commitUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pOldIndexPreOrder)
	{
		return;
	}
	
	///删除后触发
	///@param	pIndexPreOrder	已经删除的CIndexPreOrder
	virtual void commitRemove(CWriteableIndexPreOrder *pIndexPreOrder)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CIndexPreOrderFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CIndexPreOrderIterator是一个对索引预委托表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CIndexPreOrderIterator
{
public:
	///构造方法
	CIndexPreOrderIterator(void)
	{
	}

	///构造方法
	CIndexPreOrderIterator(CIndexPreOrderFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CIndexPreOrderIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个IndexPreOrder
	///@return	下一个满足条件CIndexPreOrder，如果已经没有一个满足要求了，则返回NULL
	virtual CIndexPreOrder *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CIndexPreOrderFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pIndexPreOrder 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableIndexPreOrder * pIndexPreOrder,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CIndexPreOrderFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInvestorPosition是一个存储持仓表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInvestorPosition
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableInvestorPosition *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///交易所代码
	CExchangeIDType ExchangeID;
	///投资者编号
	CInvestorIDType InvestorID;
	///会员编号
	CParticipantIDType ParticipantID;
	///客户代码
	CClientIDType ClientID;
	///合约代码
	CInstrumentIDType InstrumentID;
	///买卖方向
	CDirectionType Direction;
	///投机套保标志
	CHedgeFlagType HedgeFlag;
	///占用保证金
	CMoneyType UsedMargin;
	///总持仓量
	CVolumeType Position;
	///今日持仓成本
	CPriceType PositionCost;
	///昨持仓量(不变值)
	CVolumeType YdPosition;
	///昨日持仓成本
	CMoneyType YdPositionCost;
	///冻结的保证金
	CMoneyType FrozenMargin;
	///开仓冻结持仓
	CVolumeType FrozenPosition;
	///平仓冻结持仓
	CVolumeType FrozenClosing;
	///冻结的权利金
	CMoneyType FrozenPremium;
	///最后一笔成交编号
	CTradeIDType LastTradeID;
	///最后一笔本地报单编号
	COrderLocalIDType LastOrderLocalID;
	///币种
	CCurrencyIDType Currency;
	///持仓盈亏
	CMoneyType PositionProfit;
	///今持仓量
	CVolumeType TodayPosition;
	///今仓平仓冻结
	CVolumeType FrozenTodayClosing;
	///成交类型
	CTradeTypeType TradeType;
	///资金帐号
	CAccountIDType AccountID;
	///计算浮动盈亏最新价
	CPriceType LastPrice;
	///总持仓可平仓数量(包括平仓冻结持仓)
	CVolumeType PositionClose;
	///昨持仓可平仓数量(包括平仓冻结持仓)
	CVolumeType YdPositionClose;
	///昨持仓平仓冻结持仓
	CVolumeType YdFrozenClosing;
	///计算浮动盈亏时的总持仓
	CVolumeType CacalProfitPosition;
	///期权类型
	COptionsTypeType OptionType;
	///行权价
	CPriceType StrikePrice;
	///期权对应的标的合约代码
	CInstrumentIDType OptionInstrumentID;
	///今仓持仓成本
	CMoneyType TodayPositionCost;
	///短线持仓
	CVolumeType ShortPosition;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableInvestorPosition CInvestorPosition;

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionActionTrigger是操作持仓表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionActionTrigger
{
public:
	///构造方法
	CInvestorPositionActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInvestorPositionActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInvestorPositionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pInvestorPosition	要加入的InvestorPosition
	virtual void beforeAdd(CWriteableInvestorPosition *pInvestorPosition)
	{
		return;
	}
	
	///加入后触发
	///@param	pInvestorPosition	已经加入的InvestorPosition
	virtual void afterAdd(CInvestorPosition *pInvestorPosition)
	{
		return;
	}

	///更新前触发	
	///@param	pInvestorPosition	被刷新的CInvestorPosition
	///@param	pNewInvestorPosition	新的值
	virtual void beforeUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition)
	{
		return;
	}
	
	///更新后触发
	///@param	pInvestorPosition	被刷新的CInvestorPosition
	virtual void afterUpdate(CInvestorPosition *pInvestorPosition)
	{
		return;
	}
	
	///删除前触发
	///@param	pInvestorPosition	要删除的CInvestorPosition
	virtual void beforeRemove(CInvestorPosition *pInvestorPosition)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInvestorPositionFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionCommitTrigger是确认持仓表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionCommitTrigger
{
public:
	///构造方法
	CInvestorPositionCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInvestorPositionCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInvestorPositionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pInvestorPosition	已经加入的InvestorPosition
	virtual void commitAdd(CInvestorPosition *pInvestorPosition)
	{
		return;
	}

	///更新后触发
	///@param	pInvestorPosition	被刷新的CInvestorPosition
	///@param	poldInvestorPosition	原来的值
	virtual void commitUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pOldInvestorPosition)
	{
		return;
	}
	
	///删除后触发
	///@param	pInvestorPosition	已经删除的CInvestorPosition
	virtual void commitRemove(CWriteableInvestorPosition *pInvestorPosition)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInvestorPositionFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorPositionIterator是一个对持仓表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorPositionIterator
{
public:
	///构造方法
	CInvestorPositionIterator(void)
	{
	}

	///构造方法
	CInvestorPositionIterator(CInvestorPositionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorPositionIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个InvestorPosition
	///@return	下一个满足条件CInvestorPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorPosition *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CInvestorPositionFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorPosition 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorPosition * pInvestorPosition,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CInvestorPositionFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInvestorAccount是一个存储账户实时资金表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInvestorAccount
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableInvestorAccount *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///投资者编号
	CInvestorIDType InvestorID;
	///资金帐号
	CAccountIDType AccountID;
	///上次结算准备金
	CMoneyType PreBalance;
	///上日可用资金
	CMoneyType PreAvailable;
	///入金金额
	CMoneyType Deposit;
	///出金金额
	CMoneyType Withdraw;
	///占用保证金
	CMoneyType Margin;
	///期权权利金收支
	CMoneyType Premium;
	///手续费
	CMoneyType Fee;
	///冻结的保证金
	CMoneyType FrozenMargin;
	///冻结权利金
	CMoneyType FrozenPremium;
	///冻结手续费
	CMoneyType FrozenFee;
	///平仓盈亏
	CMoneyType CloseProfit;
	///持仓盈亏
	CMoneyType PositionProfit;
	///可用资金
	CMoneyType Available;
	///结算准备金
	CMoneyType Balance;
	///多头占用保证金
	CMoneyType LongMargin;
	///空头占用保证金
	CMoneyType ShortMargin;
	///多头冻结的保证金
	CMoneyType LongFrozenMargin;
	///空头冻结的保证金
	CMoneyType ShortFrozenMargin;
	///动态权益
	CMoneyType DynamicRights;
	///风险度
	CMoneyType Risk;
	///其他费用
	CMoneyType OtherFee;
	///质押金额
	CMoneyType Mortgage;
	///币种
	CCurrencyIDType Currency;
	///总冻结持仓
	CVolumeType TotalFrozenPos;
	///今日出入金
	CMoneyType TodayInOut;
	///当日释放保证金
	CMoneyType ReleaseMargin;
	///浮盈是否可用
	CBoolType IsProfitCanUse;
	///临时冻结资金
	CMoneyType ManualFrozen;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableInvestorAccount CInvestorAccount;

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountActionTrigger是操作账户实时资金表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountActionTrigger
{
public:
	///构造方法
	CInvestorAccountActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInvestorAccountActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInvestorAccountFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pInvestorAccount	要加入的InvestorAccount
	virtual void beforeAdd(CWriteableInvestorAccount *pInvestorAccount)
	{
		return;
	}
	
	///加入后触发
	///@param	pInvestorAccount	已经加入的InvestorAccount
	virtual void afterAdd(CInvestorAccount *pInvestorAccount)
	{
		return;
	}

	///更新前触发	
	///@param	pInvestorAccount	被刷新的CInvestorAccount
	///@param	pNewInvestorAccount	新的值
	virtual void beforeUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount)
	{
		return;
	}
	
	///更新后触发
	///@param	pInvestorAccount	被刷新的CInvestorAccount
	virtual void afterUpdate(CInvestorAccount *pInvestorAccount)
	{
		return;
	}
	
	///删除前触发
	///@param	pInvestorAccount	要删除的CInvestorAccount
	virtual void beforeRemove(CInvestorAccount *pInvestorAccount)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInvestorAccountFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountCommitTrigger是确认账户实时资金表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountCommitTrigger
{
public:
	///构造方法
	CInvestorAccountCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInvestorAccountCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInvestorAccountFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pInvestorAccount	已经加入的InvestorAccount
	virtual void commitAdd(CInvestorAccount *pInvestorAccount)
	{
		return;
	}

	///更新后触发
	///@param	pInvestorAccount	被刷新的CInvestorAccount
	///@param	poldInvestorAccount	原来的值
	virtual void commitUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pOldInvestorAccount)
	{
		return;
	}
	
	///删除后触发
	///@param	pInvestorAccount	已经删除的CInvestorAccount
	virtual void commitRemove(CWriteableInvestorAccount *pInvestorAccount)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInvestorAccountFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountIterator是一个对账户实时资金表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountIterator
{
public:
	///构造方法
	CInvestorAccountIterator(void)
	{
	}

	///构造方法
	CInvestorAccountIterator(CInvestorAccountFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorAccountIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个InvestorAccount
	///@return	下一个满足条件CInvestorAccount，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorAccount *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CInvestorAccountFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorAccount 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorAccount * pInvestorAccount,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CInvestorAccountFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInvestorAccountDeposit是一个存储账户实时出入金表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInvestorAccountDeposit
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableInvestorAccountDeposit *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///资金流水号
	CAccountSeqNoType AccountSeqNo;
	///资金帐号
	CAccountIDType AccountID;
	///连续递增的总资金流水号
	CAccountSeqNoType AccountInsideSeqNo;
	///投资者编号
	CInvestorIDType InvestorID;
	///金额
	CMoneyType Amount;
	///出入金方向
	CAccountDirectionType AmountDirection;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableInvestorAccountDeposit CInvestorAccountDeposit;

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositActionTrigger是操作账户实时出入金表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositActionTrigger
{
public:
	///构造方法
	CInvestorAccountDepositActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInvestorAccountDepositActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInvestorAccountDepositFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pInvestorAccountDeposit	要加入的InvestorAccountDeposit
	virtual void beforeAdd(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return;
	}
	
	///加入后触发
	///@param	pInvestorAccountDeposit	已经加入的InvestorAccountDeposit
	virtual void afterAdd(CInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return;
	}

	///更新前触发	
	///@param	pInvestorAccountDeposit	被刷新的CInvestorAccountDeposit
	///@param	pNewInvestorAccountDeposit	新的值
	virtual void beforeUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit)
	{
		return;
	}
	
	///更新后触发
	///@param	pInvestorAccountDeposit	被刷新的CInvestorAccountDeposit
	virtual void afterUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return;
	}
	
	///删除前触发
	///@param	pInvestorAccountDeposit	要删除的CInvestorAccountDeposit
	virtual void beforeRemove(CInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInvestorAccountDepositFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositCommitTrigger是确认账户实时出入金表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositCommitTrigger
{
public:
	///构造方法
	CInvestorAccountDepositCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInvestorAccountDepositCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInvestorAccountDepositFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pInvestorAccountDeposit	已经加入的InvestorAccountDeposit
	virtual void commitAdd(CInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return;
	}

	///更新后触发
	///@param	pInvestorAccountDeposit	被刷新的CInvestorAccountDeposit
	///@param	poldInvestorAccountDeposit	原来的值
	virtual void commitUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pOldInvestorAccountDeposit)
	{
		return;
	}
	
	///删除后触发
	///@param	pInvestorAccountDeposit	已经删除的CInvestorAccountDeposit
	virtual void commitRemove(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInvestorAccountDepositFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorAccountDepositIterator是一个对账户实时出入金表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorAccountDepositIterator
{
public:
	///构造方法
	CInvestorAccountDepositIterator(void)
	{
	}

	///构造方法
	CInvestorAccountDepositIterator(CInvestorAccountDepositFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorAccountDepositIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个InvestorAccountDeposit
	///@return	下一个满足条件CInvestorAccountDeposit，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorAccountDeposit *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CInvestorAccountDepositFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorAccountDeposit 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorAccountDeposit * pInvestorAccountDeposit,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CInvestorAccountDepositFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableExchange是一个存储交易所表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableExchange
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableExchange *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///交易日
	CTradingDayType TradingDay;
	///交易所代码
	CExchangeIDType ExchangeID;
	///交易所名称
	CExchangeNameType ExchangeName;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableExchange CExchange;

/////////////////////////////////////////////////////////////////////////
///CExchangeActionTrigger是操作交易所表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeActionTrigger
{
public:
	///构造方法
	CExchangeActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CExchangeActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CExchangeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pExchange	要加入的Exchange
	virtual void beforeAdd(CWriteableExchange *pExchange)
	{
		return;
	}
	
	///加入后触发
	///@param	pExchange	已经加入的Exchange
	virtual void afterAdd(CExchange *pExchange)
	{
		return;
	}

	///更新前触发	
	///@param	pExchange	被刷新的CExchange
	///@param	pNewExchange	新的值
	virtual void beforeUpdate(CExchange *pExchange, CWriteableExchange *pNewExchange)
	{
		return;
	}
	
	///更新后触发
	///@param	pExchange	被刷新的CExchange
	virtual void afterUpdate(CExchange *pExchange)
	{
		return;
	}
	
	///删除前触发
	///@param	pExchange	要删除的CExchange
	virtual void beforeRemove(CExchange *pExchange)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CExchangeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CExchangeCommitTrigger是确认交易所表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeCommitTrigger
{
public:
	///构造方法
	CExchangeCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CExchangeCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CExchangeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pExchange	已经加入的Exchange
	virtual void commitAdd(CExchange *pExchange)
	{
		return;
	}

	///更新后触发
	///@param	pExchange	被刷新的CExchange
	///@param	poldExchange	原来的值
	virtual void commitUpdate(CExchange *pExchange, CWriteableExchange *pOldExchange)
	{
		return;
	}
	
	///删除后触发
	///@param	pExchange	已经删除的CExchange
	virtual void commitRemove(CWriteableExchange *pExchange)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CExchangeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CExchangeIterator是一个对交易所表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CExchangeIterator
{
public:
	///构造方法
	CExchangeIterator(void)
	{
	}

	///构造方法
	CExchangeIterator(CExchangeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CExchangeIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个Exchange
	///@return	下一个满足条件CExchange，如果已经没有一个满足要求了，则返回NULL
	virtual CExchange *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CExchangeFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pExchange 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableExchange * pExchange,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CExchangeFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableSeat是一个存储下单席位表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableSeat
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableSeat *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///交易API中的序号
	CNumberType APIID;
	///交易所代码
	CExchangeIDType ExchangeID;
	///会员编号
	CParticipantIDType ParticipantID;
	///席位号
	CSeatIDType SeatID;
	///席位密码
	CPasswordType SeatPassword;
	///席位连接api类型
	CApiLinkTypeType ApiLinkType;
	///是否接收回报
	CBoolType RecvRtn;
	///席位密码(是否接收所有席位回报)
	CBoolType MainSeat;
	///是否查询基础信息
	CBoolType QueryBase;
	///是否查询持仓
	CBoolType QueryPosition;
	///收取回报的方式
	CNumberType ResumeType;
	///心跳时间(秒)
	CNumberType Heartbeat;
	///是否活跃
	CBoolType IsActive;
	///是否检查资金持仓风控
	CBoolType RiskCheck;
	///连接地址
	CFrontAddrType FrontAddr;
	///席位状态
	CSeatStatusType SeatStatus;
	///本地报单编号
	COrderLocalIDType OrderLocalID;
	///连接对应的Broker(guofu/sucden/fcstone)
	CBrokerIDType LinkBrokerID;
	///需要席位操作的交易日期
	CTradingDayType TradingDay;
	///是否需要检查交易日期
	CBoolType CheckTradingDay;
	///报盘自定义的属性
	CSeatCustomType Custom;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableSeat CSeat;

/////////////////////////////////////////////////////////////////////////
///CSeatActionTrigger是操作下单席位表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatActionTrigger
{
public:
	///构造方法
	CSeatActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CSeatActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CSeatFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pSeat	要加入的Seat
	virtual void beforeAdd(CWriteableSeat *pSeat)
	{
		return;
	}
	
	///加入后触发
	///@param	pSeat	已经加入的Seat
	virtual void afterAdd(CSeat *pSeat)
	{
		return;
	}

	///更新前触发	
	///@param	pSeat	被刷新的CSeat
	///@param	pNewSeat	新的值
	virtual void beforeUpdate(CSeat *pSeat, CWriteableSeat *pNewSeat)
	{
		return;
	}
	
	///更新后触发
	///@param	pSeat	被刷新的CSeat
	virtual void afterUpdate(CSeat *pSeat)
	{
		return;
	}
	
	///删除前触发
	///@param	pSeat	要删除的CSeat
	virtual void beforeRemove(CSeat *pSeat)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CSeatFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CSeatCommitTrigger是确认下单席位表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatCommitTrigger
{
public:
	///构造方法
	CSeatCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CSeatCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CSeatFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pSeat	已经加入的Seat
	virtual void commitAdd(CSeat *pSeat)
	{
		return;
	}

	///更新后触发
	///@param	pSeat	被刷新的CSeat
	///@param	poldSeat	原来的值
	virtual void commitUpdate(CSeat *pSeat, CWriteableSeat *pOldSeat)
	{
		return;
	}
	
	///删除后触发
	///@param	pSeat	已经删除的CSeat
	virtual void commitRemove(CWriteableSeat *pSeat)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CSeatFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CSeatIterator是一个对下单席位表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSeatIterator
{
public:
	///构造方法
	CSeatIterator(void)
	{
	}

	///构造方法
	CSeatIterator(CSeatFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CSeatIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个Seat
	///@return	下一个满足条件CSeat，如果已经没有一个满足要求了，则返回NULL
	virtual CSeat *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CSeatFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pSeat 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSeat * pSeat,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CSeatFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInstrument是一个存储期货合约表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInstrument
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableInstrument *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///交易所代码
	CExchangeIDType ExchangeID;
	///品种代码
	CProductIDType ProductID;
	///品种名称
	CProductNameType ProductName;
	///合约代码
	CInstrumentIDType InstrumentID;
	///合约名称
	CInstrumentNameType InstrumentName;
	///交割年份
	CYearType DeliveryYear;
	///交割月
	CMonthType DeliveryMonth;
	///限价单最大下单量
	CVolumeType MaxLimitOrderVolume;
	///限价单最小下单量
	CVolumeType MinLimitOrderVolume;
	///市价单最大下单量
	CVolumeType MaxMarketOrderVolume;
	///市价单最小下单量
	CVolumeType MinMarketOrderVolume;
	///数量乘数
	CVolumeMultipleType VolumeMultiple;
	///报价单位
	CPriceTickType PriceTick;
	///币种
	CCurrencyType Currency;
	///多头限仓
	CVolumeType LongPosLimit;
	///空头限仓
	CVolumeType ShortPosLimit;
	///跌停板价
	CPriceType LowerLimitPrice;
	///涨停板价
	CPriceType UpperLimitPrice;
	///昨结算
	CPriceType PreSettlementPrice;
	///合约交易状态
	CInstrumentStatusType InstrumentStatus;
	///创建日
	CDateType CreateDate;
	///上市日
	CDateType OpenDate;
	///到期日
	CDateType ExpireDate;
	///开始交割日
	CDateType StartDelivDate;
	///最后交割日
	CDateType EndDelivDate;
	///挂牌基准价
	CPriceType BasisPrice;
	///当前是否交易
	CBoolType IsTrading;
	///基础商品代码
	CInstrumentIDType UnderlyingInstrID;
	///基础商品乘数
	CUnderlyingMultipleType UnderlyingMultiple;
	///持仓类型
	CPositionTypeType PositionType;
	///执行价
	CPriceType StrikePrice;
	///期权类型
	COptionsTypeType OptionsType;
	///产品类型
	CProductClassType ProductClass;
	///期权行权方式
	COptionsModeType OptionsMode;
	///产品组
	CProductGroupIDType ProductGroupID;
	///通道对应的APIID
	CNumberType APIID;
	///组合合约腿的数量
	CNumberType LegQty;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableInstrument CInstrument;

/////////////////////////////////////////////////////////////////////////
///CInstrumentActionTrigger是操作期货合约表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentActionTrigger
{
public:
	///构造方法
	CInstrumentActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInstrumentActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInstrumentFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pInstrument	要加入的Instrument
	virtual void beforeAdd(CWriteableInstrument *pInstrument)
	{
		return;
	}
	
	///加入后触发
	///@param	pInstrument	已经加入的Instrument
	virtual void afterAdd(CInstrument *pInstrument)
	{
		return;
	}

	///更新前触发	
	///@param	pInstrument	被刷新的CInstrument
	///@param	pNewInstrument	新的值
	virtual void beforeUpdate(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument)
	{
		return;
	}
	
	///更新后触发
	///@param	pInstrument	被刷新的CInstrument
	virtual void afterUpdate(CInstrument *pInstrument)
	{
		return;
	}
	
	///删除前触发
	///@param	pInstrument	要删除的CInstrument
	virtual void beforeRemove(CInstrument *pInstrument)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInstrumentFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentCommitTrigger是确认期货合约表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentCommitTrigger
{
public:
	///构造方法
	CInstrumentCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInstrumentCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInstrumentFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pInstrument	已经加入的Instrument
	virtual void commitAdd(CInstrument *pInstrument)
	{
		return;
	}

	///更新后触发
	///@param	pInstrument	被刷新的CInstrument
	///@param	poldInstrument	原来的值
	virtual void commitUpdate(CInstrument *pInstrument, CWriteableInstrument *pOldInstrument)
	{
		return;
	}
	
	///删除后触发
	///@param	pInstrument	已经删除的CInstrument
	virtual void commitRemove(CWriteableInstrument *pInstrument)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInstrumentFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentIterator是一个对期货合约表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentIterator
{
public:
	///构造方法
	CInstrumentIterator(void)
	{
	}

	///构造方法
	CInstrumentIterator(CInstrumentFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CInstrumentIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个Instrument
	///@return	下一个满足条件CInstrument，如果已经没有一个满足要求了，则返回NULL
	virtual CInstrument *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CInstrumentFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pInstrument 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInstrument * pInstrument,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CInstrumentFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableCmbInstrumentDetail是一个存储期货组合合约明细表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableCmbInstrumentDetail
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableCmbInstrumentDetail *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///交易所代码
	CExchangeIDType ExchangeID;
	///组合合约代码
	CInstrumentIDType ArbiInstrumentID;
	///单腿合约代码
	CInstrumentIDType SingleInstrumentID;
	///组合合约腿的数量
	CNumberType LegNo;
	///买卖方向
	CDirectionType Direction;
	///数量比例
	CNumberType Ratio;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableCmbInstrumentDetail CCmbInstrumentDetail;

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailActionTrigger是操作期货组合合约明细表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailActionTrigger
{
public:
	///构造方法
	CCmbInstrumentDetailActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CCmbInstrumentDetailActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CCmbInstrumentDetailFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pCmbInstrumentDetail	要加入的CmbInstrumentDetail
	virtual void beforeAdd(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return;
	}
	
	///加入后触发
	///@param	pCmbInstrumentDetail	已经加入的CmbInstrumentDetail
	virtual void afterAdd(CCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return;
	}

	///更新前触发	
	///@param	pCmbInstrumentDetail	被刷新的CCmbInstrumentDetail
	///@param	pNewCmbInstrumentDetail	新的值
	virtual void beforeUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail)
	{
		return;
	}
	
	///更新后触发
	///@param	pCmbInstrumentDetail	被刷新的CCmbInstrumentDetail
	virtual void afterUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return;
	}
	
	///删除前触发
	///@param	pCmbInstrumentDetail	要删除的CCmbInstrumentDetail
	virtual void beforeRemove(CCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CCmbInstrumentDetailFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailCommitTrigger是确认期货组合合约明细表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailCommitTrigger
{
public:
	///构造方法
	CCmbInstrumentDetailCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CCmbInstrumentDetailCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CCmbInstrumentDetailFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pCmbInstrumentDetail	已经加入的CmbInstrumentDetail
	virtual void commitAdd(CCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return;
	}

	///更新后触发
	///@param	pCmbInstrumentDetail	被刷新的CCmbInstrumentDetail
	///@param	poldCmbInstrumentDetail	原来的值
	virtual void commitUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pOldCmbInstrumentDetail)
	{
		return;
	}
	
	///删除后触发
	///@param	pCmbInstrumentDetail	已经删除的CCmbInstrumentDetail
	virtual void commitRemove(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CCmbInstrumentDetailFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CCmbInstrumentDetailIterator是一个对期货组合合约明细表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCmbInstrumentDetailIterator
{
public:
	///构造方法
	CCmbInstrumentDetailIterator(void)
	{
	}

	///构造方法
	CCmbInstrumentDetailIterator(CCmbInstrumentDetailFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CCmbInstrumentDetailIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个CmbInstrumentDetail
	///@return	下一个满足条件CCmbInstrumentDetail，如果已经没有一个满足要求了，则返回NULL
	virtual CCmbInstrumentDetail *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CCmbInstrumentDetailFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pCmbInstrumentDetail 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableCmbInstrumentDetail * pCmbInstrumentDetail,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CCmbInstrumentDetailFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableClientTradingID是一个存储交易所客户编码表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableClientTradingID
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableClientTradingID *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///投资者编号
	CInvestorIDType InvestorID;
	///资金帐号
	CAccountIDType AccountID;
	///交易所代码
	CExchangeIDType ExchangeID;
	///会员编号
	CParticipantIDType ParticipantID;
	///客户代码
	CClientIDType ClientID;
	///客户代码权限
	CTradingRightType ClientRight;
	///客户类型
	CClientTypeType ClientType;
	///客户保值类型
	CHedgeFlagType ClientHedgeFlag;
	///是否活跃
	CIsActiveType IsActive;
	///通道对应的APIID
	CNumberType APIID;
	
	unsigned int HashBrokerIDExchangeIDPartClientID;
	
	///计算BrokerIDExchangeIDPartClientID的hash值
	void calHashBrokerIDExchangeIDPartClientID(void)
	{
		unsigned key=0;
		key=BrokerID.hash(key);
		key=ExchangeID.hash(key);
		key=ParticipantID.hash(key);
		key=ClientID.hash(key);
		HashBrokerIDExchangeIDPartClientID=key;
	}
	
	///根据需要情况，更新BrokerIDExchangeIDPartClientID的hash值
	void updateHashBrokerIDExchangeIDPartClientID(void)
	{
	}
	
	///计算所有的hash值
	void calAllHash(void)
	{
		calHashBrokerIDExchangeIDPartClientID();
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
		updateHashBrokerIDExchangeIDPartClientID();
	}
	
	///构造对应的帐户的指针
	///@param	pFactory	构造对应的帐户的指针时，寻找的对象工厂
	///@return	找到的对应的帐户的指针，如果找不到则返回NULL
	inline const CWriteableInvestorAccount *linkInvestorAccount(CInvestorAccountFactory *pFactory) const;

	///构造对应的帐户指针
	///@param	pInvestorAccount	要连接到的对象
	///@return	输入的pInvestorAccount
	const CWriteableInvestorAccount *linkInvestorAccount(const CWriteableInvestorAccount *pInvestorAccount) const
	{
		void *target=(void *)(&(this->pInvestorAccount));
		*((const CWriteableInvestorAccount **)target)=pInvestorAccount;
		return pInvestorAccount;
	}
	
	///获取对应的帐户的指针
	///@return	找到的对应的帐户的指针，如果找不到则返回NULL
	const CWriteableInvestorAccount *getInvestorAccount(void) const
	{
		return pInvestorAccount;
	}

private:
	///对应的帐户
	const CWriteableInvestorAccount *pInvestorAccount;
};

typedef const CWriteableClientTradingID CClientTradingID;

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDActionTrigger是操作交易所客户编码表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDActionTrigger
{
public:
	///构造方法
	CClientTradingIDActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CClientTradingIDActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CClientTradingIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pClientTradingID	要加入的ClientTradingID
	virtual void beforeAdd(CWriteableClientTradingID *pClientTradingID)
	{
		return;
	}
	
	///加入后触发
	///@param	pClientTradingID	已经加入的ClientTradingID
	virtual void afterAdd(CClientTradingID *pClientTradingID)
	{
		return;
	}

	///更新前触发	
	///@param	pClientTradingID	被刷新的CClientTradingID
	///@param	pNewClientTradingID	新的值
	virtual void beforeUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID)
	{
		return;
	}
	
	///更新后触发
	///@param	pClientTradingID	被刷新的CClientTradingID
	virtual void afterUpdate(CClientTradingID *pClientTradingID)
	{
		return;
	}
	
	///删除前触发
	///@param	pClientTradingID	要删除的CClientTradingID
	virtual void beforeRemove(CClientTradingID *pClientTradingID)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CClientTradingIDFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDCommitTrigger是确认交易所客户编码表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDCommitTrigger
{
public:
	///构造方法
	CClientTradingIDCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CClientTradingIDCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CClientTradingIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pClientTradingID	已经加入的ClientTradingID
	virtual void commitAdd(CClientTradingID *pClientTradingID)
	{
		return;
	}

	///更新后触发
	///@param	pClientTradingID	被刷新的CClientTradingID
	///@param	poldClientTradingID	原来的值
	virtual void commitUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pOldClientTradingID)
	{
		return;
	}
	
	///删除后触发
	///@param	pClientTradingID	已经删除的CClientTradingID
	virtual void commitRemove(CWriteableClientTradingID *pClientTradingID)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CClientTradingIDFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CClientTradingIDIterator是一个对交易所客户编码表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientTradingIDIterator
{
public:
	///构造方法
	CClientTradingIDIterator(void)
	{
	}

	///构造方法
	CClientTradingIDIterator(CClientTradingIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CClientTradingIDIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个ClientTradingID
	///@return	下一个满足条件CClientTradingID，如果已经没有一个满足要求了，则返回NULL
	virtual CClientTradingID *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CClientTradingIDFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pClientTradingID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableClientTradingID * pClientTradingID,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CClientTradingIDFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInvestor是一个存储投资者信息表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInvestor
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableInvestor *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///投资者编号
	CInvestorIDType InvestorID;
	///投资者名称
	CInvestorNameType InvestorName;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableInvestor CInvestor;

/////////////////////////////////////////////////////////////////////////
///CInvestorActionTrigger是操作投资者信息表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorActionTrigger
{
public:
	///构造方法
	CInvestorActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInvestorActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInvestorFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pInvestor	要加入的Investor
	virtual void beforeAdd(CWriteableInvestor *pInvestor)
	{
		return;
	}
	
	///加入后触发
	///@param	pInvestor	已经加入的Investor
	virtual void afterAdd(CInvestor *pInvestor)
	{
		return;
	}

	///更新前触发	
	///@param	pInvestor	被刷新的CInvestor
	///@param	pNewInvestor	新的值
	virtual void beforeUpdate(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor)
	{
		return;
	}
	
	///更新后触发
	///@param	pInvestor	被刷新的CInvestor
	virtual void afterUpdate(CInvestor *pInvestor)
	{
		return;
	}
	
	///删除前触发
	///@param	pInvestor	要删除的CInvestor
	virtual void beforeRemove(CInvestor *pInvestor)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInvestorFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorCommitTrigger是确认投资者信息表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorCommitTrigger
{
public:
	///构造方法
	CInvestorCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInvestorCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInvestorFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pInvestor	已经加入的Investor
	virtual void commitAdd(CInvestor *pInvestor)
	{
		return;
	}

	///更新后触发
	///@param	pInvestor	被刷新的CInvestor
	///@param	poldInvestor	原来的值
	virtual void commitUpdate(CInvestor *pInvestor, CWriteableInvestor *pOldInvestor)
	{
		return;
	}
	
	///删除后触发
	///@param	pInvestor	已经删除的CInvestor
	virtual void commitRemove(CWriteableInvestor *pInvestor)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInvestorFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorIterator是一个对投资者信息表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorIterator
{
public:
	///构造方法
	CInvestorIterator(void)
	{
	}

	///构造方法
	CInvestorIterator(CInvestorFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个Investor
	///@return	下一个满足条件CInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestor *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CInvestorFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pInvestor 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestor * pInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CInvestorFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInvestorMargin是一个存储客户期货保证金率表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInvestorMargin
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableInvestorMargin *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///交易所代码
	CExchangeIDType ExchangeID;
	///投资者编码
	CInvestorIDType InvestorID;
	///合约代码
	CInstrumentIDType InstrumentID;
	///投机套保标志
	CHedgeFlagType HedgeFlag;
	///多头占用保证金按比例
	CRatioType LongMarginRate;
	///多头保证金按手数
	CRatioType LongMarginAmt;
	///空头占用保证金按比例
	CRatioType ShortMarginRate;
	///空头保证金按手数
	CRatioType ShortMarginAmt;
	
	unsigned int HashInstrumentAndClientID;
	
	///计算InstrumentAndClientID的hash值
	void calHashInstrumentAndClientID(void)
	{
		unsigned key=0;
		key=InstrumentID.hash(key);
		key=InvestorID.hash(key);
		HashInstrumentAndClientID=key;
	}
	
	///根据需要情况，更新InstrumentAndClientID的hash值
	void updateHashInstrumentAndClientID(void)
	{
	}
	
	///计算所有的hash值
	void calAllHash(void)
	{
		calHashInstrumentAndClientID();
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
		updateHashInstrumentAndClientID();
	}
	

private:
};

typedef const CWriteableInvestorMargin CInvestorMargin;

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginActionTrigger是操作客户期货保证金率表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginActionTrigger
{
public:
	///构造方法
	CInvestorMarginActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInvestorMarginActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInvestorMarginFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pInvestorMargin	要加入的InvestorMargin
	virtual void beforeAdd(CWriteableInvestorMargin *pInvestorMargin)
	{
		return;
	}
	
	///加入后触发
	///@param	pInvestorMargin	已经加入的InvestorMargin
	virtual void afterAdd(CInvestorMargin *pInvestorMargin)
	{
		return;
	}

	///更新前触发	
	///@param	pInvestorMargin	被刷新的CInvestorMargin
	///@param	pNewInvestorMargin	新的值
	virtual void beforeUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin)
	{
		return;
	}
	
	///更新后触发
	///@param	pInvestorMargin	被刷新的CInvestorMargin
	virtual void afterUpdate(CInvestorMargin *pInvestorMargin)
	{
		return;
	}
	
	///删除前触发
	///@param	pInvestorMargin	要删除的CInvestorMargin
	virtual void beforeRemove(CInvestorMargin *pInvestorMargin)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInvestorMarginFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginCommitTrigger是确认客户期货保证金率表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginCommitTrigger
{
public:
	///构造方法
	CInvestorMarginCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInvestorMarginCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInvestorMarginFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pInvestorMargin	已经加入的InvestorMargin
	virtual void commitAdd(CInvestorMargin *pInvestorMargin)
	{
		return;
	}

	///更新后触发
	///@param	pInvestorMargin	被刷新的CInvestorMargin
	///@param	poldInvestorMargin	原来的值
	virtual void commitUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pOldInvestorMargin)
	{
		return;
	}
	
	///删除后触发
	///@param	pInvestorMargin	已经删除的CInvestorMargin
	virtual void commitRemove(CWriteableInvestorMargin *pInvestorMargin)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInvestorMarginFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorMarginIterator是一个对客户期货保证金率表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorMarginIterator
{
public:
	///构造方法
	CInvestorMarginIterator(void)
	{
	}

	///构造方法
	CInvestorMarginIterator(CInvestorMarginFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorMarginIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个InvestorMargin
	///@return	下一个满足条件CInvestorMargin，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorMargin *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CInvestorMarginFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorMargin 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorMargin * pInvestorMargin,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CInvestorMarginFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInvestorFee是一个存储客户手续费率表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInvestorFee
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableInvestorFee *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///交易所代码
	CExchangeIDType ExchangeID;
	///投资者编码
	CInvestorIDType InvestorID;
	///合约代码
	CInstrumentIDType InstrumentID;
	///投机套保标志
	CHedgeFlagType HedgeFlag;
	///开仓手续费按比例
	CRatioType OpenFeeRate;
	///开仓手续费按手数
	CRatioType OpenFeeAmt;
	///平仓手续费按比例
	CRatioType OffsetFeeRate;
	///平仓手续费按手数
	CRatioType OffsetFeeAmt;
	///平今仓手续费按比例
	CRatioType OTFeeRate;
	///平今仓手续费按手数
	CRatioType OTFeeAmt;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableInvestorFee CInvestorFee;

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeActionTrigger是操作客户手续费率表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeActionTrigger
{
public:
	///构造方法
	CInvestorFeeActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInvestorFeeActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInvestorFeeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pInvestorFee	要加入的InvestorFee
	virtual void beforeAdd(CWriteableInvestorFee *pInvestorFee)
	{
		return;
	}
	
	///加入后触发
	///@param	pInvestorFee	已经加入的InvestorFee
	virtual void afterAdd(CInvestorFee *pInvestorFee)
	{
		return;
	}

	///更新前触发	
	///@param	pInvestorFee	被刷新的CInvestorFee
	///@param	pNewInvestorFee	新的值
	virtual void beforeUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee)
	{
		return;
	}
	
	///更新后触发
	///@param	pInvestorFee	被刷新的CInvestorFee
	virtual void afterUpdate(CInvestorFee *pInvestorFee)
	{
		return;
	}
	
	///删除前触发
	///@param	pInvestorFee	要删除的CInvestorFee
	virtual void beforeRemove(CInvestorFee *pInvestorFee)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInvestorFeeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeCommitTrigger是确认客户手续费率表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeCommitTrigger
{
public:
	///构造方法
	CInvestorFeeCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInvestorFeeCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInvestorFeeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pInvestorFee	已经加入的InvestorFee
	virtual void commitAdd(CInvestorFee *pInvestorFee)
	{
		return;
	}

	///更新后触发
	///@param	pInvestorFee	被刷新的CInvestorFee
	///@param	poldInvestorFee	原来的值
	virtual void commitUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pOldInvestorFee)
	{
		return;
	}
	
	///删除后触发
	///@param	pInvestorFee	已经删除的CInvestorFee
	virtual void commitRemove(CWriteableInvestorFee *pInvestorFee)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInvestorFeeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorFeeIterator是一个对客户手续费率表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorFeeIterator
{
public:
	///构造方法
	CInvestorFeeIterator(void)
	{
	}

	///构造方法
	CInvestorFeeIterator(CInvestorFeeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorFeeIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个InvestorFee
	///@return	下一个满足条件CInvestorFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorFee *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CInvestorFeeFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorFee 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorFee * pInvestorFee,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CInvestorFeeFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableUser是一个存储用户表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableUser
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableUser *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///用户代码
	CUserIDType UserID;
	///用户登录密码
	CPasswordType Password;
	///是否活跃
	CIsActiveType IsActive;
	///用户名称
	CUserNameType UserName;
	///用户类型
	CUserTypeType UserType;
	///营业部
	CDepartmentType Department;
	///授权功能集
	CGrantFuncSetType GrantFuncSet;
	///是否检查IP和MAC
	CBoolType CheckIpMacAddr;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableUser CUser;

/////////////////////////////////////////////////////////////////////////
///CUserActionTrigger是操作用户表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserActionTrigger
{
public:
	///构造方法
	CUserActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CUserActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CUserFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pUser	要加入的User
	virtual void beforeAdd(CWriteableUser *pUser)
	{
		return;
	}
	
	///加入后触发
	///@param	pUser	已经加入的User
	virtual void afterAdd(CUser *pUser)
	{
		return;
	}

	///更新前触发	
	///@param	pUser	被刷新的CUser
	///@param	pNewUser	新的值
	virtual void beforeUpdate(CUser *pUser, CWriteableUser *pNewUser)
	{
		return;
	}
	
	///更新后触发
	///@param	pUser	被刷新的CUser
	virtual void afterUpdate(CUser *pUser)
	{
		return;
	}
	
	///删除前触发
	///@param	pUser	要删除的CUser
	virtual void beforeRemove(CUser *pUser)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CUserFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserCommitTrigger是确认用户表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserCommitTrigger
{
public:
	///构造方法
	CUserCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CUserCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CUserFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pUser	已经加入的User
	virtual void commitAdd(CUser *pUser)
	{
		return;
	}

	///更新后触发
	///@param	pUser	被刷新的CUser
	///@param	poldUser	原来的值
	virtual void commitUpdate(CUser *pUser, CWriteableUser *pOldUser)
	{
		return;
	}
	
	///删除后触发
	///@param	pUser	已经删除的CUser
	virtual void commitRemove(CWriteableUser *pUser)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CUserFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserIterator是一个对用户表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIterator
{
public:
	///构造方法
	CUserIterator(void)
	{
	}

	///构造方法
	CUserIterator(CUserFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CUserIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个User
	///@return	下一个满足条件CUser，如果已经没有一个满足要求了，则返回NULL
	virtual CUser *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CUserFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pUser 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUser * pUser,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CUserFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableUserInvestor是一个存储用户投资者关系表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableUserInvestor
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableUserInvestor *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///交易用户代码
	CUserIDType UserID;
	///投资者编号
	CInvestorIDType InvestorID;
	///授权功能集
	CGrantFuncSetType GrantFuncSet;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableUserInvestor CUserInvestor;

/////////////////////////////////////////////////////////////////////////
///CUserInvestorActionTrigger是操作用户投资者关系表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorActionTrigger
{
public:
	///构造方法
	CUserInvestorActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CUserInvestorActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CUserInvestorFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pUserInvestor	要加入的UserInvestor
	virtual void beforeAdd(CWriteableUserInvestor *pUserInvestor)
	{
		return;
	}
	
	///加入后触发
	///@param	pUserInvestor	已经加入的UserInvestor
	virtual void afterAdd(CUserInvestor *pUserInvestor)
	{
		return;
	}

	///更新前触发	
	///@param	pUserInvestor	被刷新的CUserInvestor
	///@param	pNewUserInvestor	新的值
	virtual void beforeUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor)
	{
		return;
	}
	
	///更新后触发
	///@param	pUserInvestor	被刷新的CUserInvestor
	virtual void afterUpdate(CUserInvestor *pUserInvestor)
	{
		return;
	}
	
	///删除前触发
	///@param	pUserInvestor	要删除的CUserInvestor
	virtual void beforeRemove(CUserInvestor *pUserInvestor)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CUserInvestorFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorCommitTrigger是确认用户投资者关系表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorCommitTrigger
{
public:
	///构造方法
	CUserInvestorCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CUserInvestorCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CUserInvestorFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pUserInvestor	已经加入的UserInvestor
	virtual void commitAdd(CUserInvestor *pUserInvestor)
	{
		return;
	}

	///更新后触发
	///@param	pUserInvestor	被刷新的CUserInvestor
	///@param	poldUserInvestor	原来的值
	virtual void commitUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pOldUserInvestor)
	{
		return;
	}
	
	///删除后触发
	///@param	pUserInvestor	已经删除的CUserInvestor
	virtual void commitRemove(CWriteableUserInvestor *pUserInvestor)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CUserInvestorFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserInvestorIterator是一个对用户投资者关系表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserInvestorIterator
{
public:
	///构造方法
	CUserInvestorIterator(void)
	{
	}

	///构造方法
	CUserInvestorIterator(CUserInvestorFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CUserInvestorIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个UserInvestor
	///@return	下一个满足条件CUserInvestor，如果已经没有一个满足要求了，则返回NULL
	virtual CUserInvestor *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CUserInvestorFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pUserInvestor 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserInvestor * pUserInvestor,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CUserInvestorFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableOrderInsertFailed是一个存储错单表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableOrderInsertFailed
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableOrderInsertFailed *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///交易所代码
	CExchangeIDType ExchangeID;
	///系统报单编号
	COrderSysIDType OrderSysID;
	///投资者编号
	CInvestorIDType InvestorID;
	///用户代码
	CUserIDType UserID;
	///合约代码
	CInstrumentIDType InstrumentID;
	///用户本地报单号
	CUserOrderLocalIDType UserOrderLocalID;
	///价格类型
	COrderPriceTypeType OrderPriceType;
	///买卖方向
	CDirectionType Direction;
	///开平标志
	COffsetFlagType OffsetFlag;
	///投机套保标志
	CHedgeFlagType HedgeFlag;
	///价格
	CPriceType LimitPrice;
	///数量
	CVolumeType Volume;
	///有效期类型
	CTimeConditionType TimeCondition;
	///GTD日期
	CDateType GTDDate;
	///成交量类型
	CVolumeConditionType VolumeCondition;
	///最小成交量
	CVolumeType MinVolume;
	///止损价
	CPriceType StopPrice;
	///强平原因
	CForceCloseReasonType ForceCloseReason;
	///自动挂起标志
	CBoolType IsAutoSuspend;
	///业务单元
	CBusinessUnitType BusinessUnit;
	///用户自定义域
	CCustomType UserCustom;
	///营业部代码
	CBranchIDType BranchID;
	///记录编号
	CSequenceNoType RecNum;
	///业务类别
	CBusinessTypeType BusinessType;
	///交易日
	CTradingDayType TradingDay;
	///会员编号
	CParticipantIDType ParticipantID;
	///客户号
	CClientIDType ClientID;
	///下单席位号
	CSeatIDType SeatID;
	///插入时间
	CTimeType InsertTime;
	///本地报单编号
	COrderLocalIDType OrderLocalID;
	///报单来源
	COrderSourceType OrderSource;
	///报单状态
	COrderStatusType OrderStatus;
	///撤销时间
	CTimeType CancelTime;
	///撤单用户编号
	CUserIDType CancelUserID;
	///今成交数量
	CVolumeType VolumeTraded;
	///剩余数量
	CVolumeType VolumeRemain;
	///前置编号
	CFrontIDType FrontID;
	///会话编号
	CSessionIDType SessionID;
	///冻结手续费
	CMoneyType FrozenFee;
	///冻结的保证金
	CMoneyType FrozenMargin;
	///期权权利金收支
	CMoneyType FrozenPremium;
	///资金帐号
	CAccountIDType AccountID;
	///下单用户编号
	CUserIDType OrderUserID;
	///交易类型
	CTradeTypeType TradeType;
	///处理标志
	CDealFlagType DealFlag;
	///已成交佣金
	CMoneyType TradeCommision;
	///成交金额
	CMoneyType TradeAmnt;
	///撤单数量
	CVolumeType CancleVolume;
	///请求编号
	CRequestIDType RequestID;
	///通道对应的APIID
	CNumberType APIID;
	///下单IP地址
	CIPAddressType IPAddress;
	///下单MAC地址
	CMacAddressType MacAddress;
	///Ftdengine接受下层时间戳
	CILocalTimeType FTdRecvDown;
	///接受下层时间戳
	CILocalTimeType CoreRecvDown;
	///发送上层时间戳
	CILocalTimeType CoreSendUp;
	///接受上层时间戳
	CILocalTimeType CoreRecvUp;
	///发送下层时间戳
	CILocalTimeType CoreSendDown;
	///Ftdengine接受下层时间戳
	CILocalTimeType FTdSendDown;
	///保证金组合类型
	CClientMarginCombTypeType MarginCombType;
	///合约组代码
	CInstrumentGroupIDType InstrumentGroupID;
	///错误信息
	CErrorMsgType ErrorMsg;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	
	///构造对应的帐户的指针
	///@param	pFactory	构造对应的帐户的指针时，寻找的对象工厂
	///@return	找到的对应的帐户的指针，如果找不到则返回NULL
	inline const CWriteableInvestorAccount *linkInvestorAccount(CInvestorAccountFactory *pFactory) const;

	///构造对应的帐户指针
	///@param	pInvestorAccount	要连接到的对象
	///@return	输入的pInvestorAccount
	const CWriteableInvestorAccount *linkInvestorAccount(const CWriteableInvestorAccount *pInvestorAccount) const
	{
		void *target=(void *)(&(this->pInvestorAccount));
		*((const CWriteableInvestorAccount **)target)=pInvestorAccount;
		return pInvestorAccount;
	}
	
	///获取对应的帐户的指针
	///@return	找到的对应的帐户的指针，如果找不到则返回NULL
	const CWriteableInvestorAccount *getInvestorAccount(void) const
	{
		return pInvestorAccount;
	}
	///构造对应的合约持仓信息的指针
	///@param	pFactory	构造对应的合约持仓信息的指针时，寻找的对象工厂
	///@return	找到的对应的合约持仓信息的指针，如果找不到则返回NULL
	inline const CWriteableInvestorPosition *linkInvestorPosition(CInvestorPositionFactory *pFactory) const;

	///构造对应的合约持仓信息指针
	///@param	pInvestorPosition	要连接到的对象
	///@return	输入的pInvestorPosition
	const CWriteableInvestorPosition *linkInvestorPosition(const CWriteableInvestorPosition *pInvestorPosition) const
	{
		void *target=(void *)(&(this->pInvestorPosition));
		*((const CWriteableInvestorPosition **)target)=pInvestorPosition;
		return pInvestorPosition;
	}
	
	///获取对应的合约持仓信息的指针
	///@return	找到的对应的合约持仓信息的指针，如果找不到则返回NULL
	const CWriteableInvestorPosition *getInvestorPosition(void) const
	{
		return pInvestorPosition;
	}
	///构造对应的合约信息的指针
	///@param	pFactory	构造对应的合约信息的指针时，寻找的对象工厂
	///@return	找到的对应的合约信息的指针，如果找不到则返回NULL
	inline const CWriteableInstrument *linkInstrument(CInstrumentFactory *pFactory) const;

	///构造对应的合约信息指针
	///@param	pInstrument	要连接到的对象
	///@return	输入的pInstrument
	const CWriteableInstrument *linkInstrument(const CWriteableInstrument *pInstrument) const
	{
		void *target=(void *)(&(this->pInstrument));
		*((const CWriteableInstrument **)target)=pInstrument;
		return pInstrument;
	}
	
	///获取对应的合约信息的指针
	///@return	找到的对应的合约信息的指针，如果找不到则返回NULL
	const CWriteableInstrument *getInstrument(void) const
	{
		return pInstrument;
	}
	///构造对应的投资者保证金率信息的指针
	///@param	pFactory	构造对应的投资者保证金率信息的指针时，寻找的对象工厂
	///@return	找到的对应的投资者保证金率信息的指针，如果找不到则返回NULL
	inline const CWriteableInvestorMargin *linkInvestorMargin(CInvestorMarginFactory *pFactory) const;

	///构造对应的投资者保证金率信息指针
	///@param	pInvestorMargin	要连接到的对象
	///@return	输入的pInvestorMargin
	const CWriteableInvestorMargin *linkInvestorMargin(const CWriteableInvestorMargin *pInvestorMargin) const
	{
		void *target=(void *)(&(this->pInvestorMargin));
		*((const CWriteableInvestorMargin **)target)=pInvestorMargin;
		return pInvestorMargin;
	}
	
	///获取对应的投资者保证金率信息的指针
	///@return	找到的对应的投资者保证金率信息的指针，如果找不到则返回NULL
	const CWriteableInvestorMargin *getInvestorMargin(void) const
	{
		return pInvestorMargin;
	}
	///构造对应的投资者手续费率信息的指针
	///@param	pFactory	构造对应的投资者手续费率信息的指针时，寻找的对象工厂
	///@return	找到的对应的投资者手续费率信息的指针，如果找不到则返回NULL
	inline const CWriteableInvestorFee *linkInvestorFee(CInvestorFeeFactory *pFactory) const;

	///构造对应的投资者手续费率信息指针
	///@param	pInvestorFee	要连接到的对象
	///@return	输入的pInvestorFee
	const CWriteableInvestorFee *linkInvestorFee(const CWriteableInvestorFee *pInvestorFee) const
	{
		void *target=(void *)(&(this->pInvestorFee));
		*((const CWriteableInvestorFee **)target)=pInvestorFee;
		return pInvestorFee;
	}
	
	///获取对应的投资者手续费率信息的指针
	///@return	找到的对应的投资者手续费率信息的指针，如果找不到则返回NULL
	const CWriteableInvestorFee *getInvestorFee(void) const
	{
		return pInvestorFee;
	}

private:
	///对应的帐户
	const CWriteableInvestorAccount *pInvestorAccount;
	///对应的合约持仓信息
	const CWriteableInvestorPosition *pInvestorPosition;
	///对应的合约信息
	const CWriteableInstrument *pInstrument;
	///对应的投资者保证金率信息
	const CWriteableInvestorMargin *pInvestorMargin;
	///对应的投资者手续费率信息
	const CWriteableInvestorFee *pInvestorFee;
};

typedef const CWriteableOrderInsertFailed COrderInsertFailed;

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedActionTrigger是操作错单表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedActionTrigger
{
public:
	///构造方法
	COrderInsertFailedActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~COrderInsertFailedActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(COrderInsertFailedFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pOrderInsertFailed	要加入的OrderInsertFailed
	virtual void beforeAdd(CWriteableOrderInsertFailed *pOrderInsertFailed)
	{
		return;
	}
	
	///加入后触发
	///@param	pOrderInsertFailed	已经加入的OrderInsertFailed
	virtual void afterAdd(COrderInsertFailed *pOrderInsertFailed)
	{
		return;
	}

	///更新前触发	
	///@param	pOrderInsertFailed	被刷新的COrderInsertFailed
	///@param	pNewOrderInsertFailed	新的值
	virtual void beforeUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed)
	{
		return;
	}
	
	///更新后触发
	///@param	pOrderInsertFailed	被刷新的COrderInsertFailed
	virtual void afterUpdate(COrderInsertFailed *pOrderInsertFailed)
	{
		return;
	}
	
	///删除前触发
	///@param	pOrderInsertFailed	要删除的COrderInsertFailed
	virtual void beforeRemove(COrderInsertFailed *pOrderInsertFailed)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	COrderInsertFailedFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedCommitTrigger是确认错单表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedCommitTrigger
{
public:
	///构造方法
	COrderInsertFailedCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~COrderInsertFailedCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(COrderInsertFailedFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pOrderInsertFailed	已经加入的OrderInsertFailed
	virtual void commitAdd(COrderInsertFailed *pOrderInsertFailed)
	{
		return;
	}

	///更新后触发
	///@param	pOrderInsertFailed	被刷新的COrderInsertFailed
	///@param	poldOrderInsertFailed	原来的值
	virtual void commitUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pOldOrderInsertFailed)
	{
		return;
	}
	
	///删除后触发
	///@param	pOrderInsertFailed	已经删除的COrderInsertFailed
	virtual void commitRemove(CWriteableOrderInsertFailed *pOrderInsertFailed)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	COrderInsertFailedFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///COrderInsertFailedIterator是一个对错单表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderInsertFailedIterator
{
public:
	///构造方法
	COrderInsertFailedIterator(void)
	{
	}

	///构造方法
	COrderInsertFailedIterator(COrderInsertFailedFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~COrderInsertFailedIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个OrderInsertFailed
	///@return	下一个满足条件COrderInsertFailed，如果已经没有一个满足要求了，则返回NULL
	virtual COrderInsertFailed *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	COrderInsertFailedFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pOrderInsertFailed 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrderInsertFailed * pOrderInsertFailed,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	COrderInsertFailedFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableUserTradingRight是一个存储用户交易权限表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableUserTradingRight
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableUserTradingRight *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///交易所代码
	CExchangeIDType ExchangeID;
	///合约代码
	CInstrumentIDType InstrumentID;
	///用户代码
	CUserIDType UserID;
	///投资者编号
	CInvestorIDType InvestorID;
	///合约交易权限
	CTradingRightType TradingRight;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableUserTradingRight CUserTradingRight;

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightActionTrigger是操作用户交易权限表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightActionTrigger
{
public:
	///构造方法
	CUserTradingRightActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CUserTradingRightActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CUserTradingRightFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pUserTradingRight	要加入的UserTradingRight
	virtual void beforeAdd(CWriteableUserTradingRight *pUserTradingRight)
	{
		return;
	}
	
	///加入后触发
	///@param	pUserTradingRight	已经加入的UserTradingRight
	virtual void afterAdd(CUserTradingRight *pUserTradingRight)
	{
		return;
	}

	///更新前触发	
	///@param	pUserTradingRight	被刷新的CUserTradingRight
	///@param	pNewUserTradingRight	新的值
	virtual void beforeUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight)
	{
		return;
	}
	
	///更新后触发
	///@param	pUserTradingRight	被刷新的CUserTradingRight
	virtual void afterUpdate(CUserTradingRight *pUserTradingRight)
	{
		return;
	}
	
	///删除前触发
	///@param	pUserTradingRight	要删除的CUserTradingRight
	virtual void beforeRemove(CUserTradingRight *pUserTradingRight)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CUserTradingRightFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightCommitTrigger是确认用户交易权限表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightCommitTrigger
{
public:
	///构造方法
	CUserTradingRightCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CUserTradingRightCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CUserTradingRightFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pUserTradingRight	已经加入的UserTradingRight
	virtual void commitAdd(CUserTradingRight *pUserTradingRight)
	{
		return;
	}

	///更新后触发
	///@param	pUserTradingRight	被刷新的CUserTradingRight
	///@param	poldUserTradingRight	原来的值
	virtual void commitUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pOldUserTradingRight)
	{
		return;
	}
	
	///删除后触发
	///@param	pUserTradingRight	已经删除的CUserTradingRight
	virtual void commitRemove(CWriteableUserTradingRight *pUserTradingRight)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CUserTradingRightFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserTradingRightIterator是一个对用户交易权限表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserTradingRightIterator
{
public:
	///构造方法
	CUserTradingRightIterator(void)
	{
	}

	///构造方法
	CUserTradingRightIterator(CUserTradingRightFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CUserTradingRightIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个UserTradingRight
	///@return	下一个满足条件CUserTradingRight，如果已经没有一个满足要求了，则返回NULL
	virtual CUserTradingRight *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CUserTradingRightFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pUserTradingRight 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserTradingRight * pUserTradingRight,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CUserTradingRightFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableCurrentTime是一个存储当前时间的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableCurrentTime
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableCurrentTime *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///当前日期
	CDateType CurrDate;
	///当前时间
	CTimeType CurrTime;
	///当前时间（毫秒）
	CMillisecType CurrMillisec;
	///原来时间
	CTimeType OldTime;
	///原来时间（毫秒）
	CMillisecType OldMillisec;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableCurrentTime CCurrentTime;

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeActionTrigger是操作当前时间时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeActionTrigger
{
public:
	///构造方法
	CCurrentTimeActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CCurrentTimeActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CCurrentTimeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pCurrentTime	要加入的CurrentTime
	virtual void beforeAdd(CWriteableCurrentTime *pCurrentTime)
	{
		return;
	}
	
	///加入后触发
	///@param	pCurrentTime	已经加入的CurrentTime
	virtual void afterAdd(CCurrentTime *pCurrentTime)
	{
		return;
	}

	///更新前触发	
	///@param	pCurrentTime	被刷新的CCurrentTime
	///@param	pNewCurrentTime	新的值
	virtual void beforeUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime)
	{
		return;
	}
	
	///更新后触发
	///@param	pCurrentTime	被刷新的CCurrentTime
	virtual void afterUpdate(CCurrentTime *pCurrentTime)
	{
		return;
	}
	
	///删除前触发
	///@param	pCurrentTime	要删除的CCurrentTime
	virtual void beforeRemove(CCurrentTime *pCurrentTime)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CCurrentTimeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeCommitTrigger是确认当前时间时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeCommitTrigger
{
public:
	///构造方法
	CCurrentTimeCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CCurrentTimeCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CCurrentTimeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pCurrentTime	已经加入的CurrentTime
	virtual void commitAdd(CCurrentTime *pCurrentTime)
	{
		return;
	}

	///更新后触发
	///@param	pCurrentTime	被刷新的CCurrentTime
	///@param	poldCurrentTime	原来的值
	virtual void commitUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pOldCurrentTime)
	{
		return;
	}
	
	///删除后触发
	///@param	pCurrentTime	已经删除的CCurrentTime
	virtual void commitRemove(CWriteableCurrentTime *pCurrentTime)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CCurrentTimeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CCurrentTimeIterator是一个对当前时间的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CCurrentTimeIterator
{
public:
	///构造方法
	CCurrentTimeIterator(void)
	{
	}

	///构造方法
	CCurrentTimeIterator(CCurrentTimeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CCurrentTimeIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个CurrentTime
	///@return	下一个满足条件CCurrentTime，如果已经没有一个满足要求了，则返回NULL
	virtual CCurrentTime *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CCurrentTimeFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pCurrentTime 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableCurrentTime * pCurrentTime,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CCurrentTimeFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableUserSession是一个存储交易员在线会话的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableUserSession
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableUserSession *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司代码
	CBrokerIDType BrokerID;
	///交易用户代码
	CUserIDType UserID;
	///交易用户类型
	CUserTypeType UserType;
	///会话编号
	CSessionIDType SessionID;
	///前置编号
	CFrontIDType FrontID;
	///登录时间
	CTimeType LoginTime;
	///IP地址
	CIPAddressType IPAddress;
	///Mac地址
	CMacAddressType MacAddress;
	///用户端产品信息
	CProductInfoType UserProductInfo;
	///接口端产品信息
	CProductInfoType InterfaceProductInfo;
	///协议信息
	CProtocolInfoType ProtocolInfo;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableUserSession CUserSession;

/////////////////////////////////////////////////////////////////////////
///CUserSessionActionTrigger是操作交易员在线会话时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionActionTrigger
{
public:
	///构造方法
	CUserSessionActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CUserSessionActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CUserSessionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pUserSession	要加入的UserSession
	virtual void beforeAdd(CWriteableUserSession *pUserSession)
	{
		return;
	}
	
	///加入后触发
	///@param	pUserSession	已经加入的UserSession
	virtual void afterAdd(CUserSession *pUserSession)
	{
		return;
	}

	///更新前触发	
	///@param	pUserSession	被刷新的CUserSession
	///@param	pNewUserSession	新的值
	virtual void beforeUpdate(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession)
	{
		return;
	}
	
	///更新后触发
	///@param	pUserSession	被刷新的CUserSession
	virtual void afterUpdate(CUserSession *pUserSession)
	{
		return;
	}
	
	///删除前触发
	///@param	pUserSession	要删除的CUserSession
	virtual void beforeRemove(CUserSession *pUserSession)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CUserSessionFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionCommitTrigger是确认交易员在线会话时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionCommitTrigger
{
public:
	///构造方法
	CUserSessionCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CUserSessionCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CUserSessionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pUserSession	已经加入的UserSession
	virtual void commitAdd(CUserSession *pUserSession)
	{
		return;
	}

	///更新后触发
	///@param	pUserSession	被刷新的CUserSession
	///@param	poldUserSession	原来的值
	virtual void commitUpdate(CUserSession *pUserSession, CWriteableUserSession *pOldUserSession)
	{
		return;
	}
	
	///删除后触发
	///@param	pUserSession	已经删除的CUserSession
	virtual void commitRemove(CWriteableUserSession *pUserSession)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CUserSessionFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserSessionIterator是一个对交易员在线会话的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserSessionIterator
{
public:
	///构造方法
	CUserSessionIterator(void)
	{
	}

	///构造方法
	CUserSessionIterator(CUserSessionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CUserSessionIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个UserSession
	///@return	下一个满足条件CUserSession，如果已经没有一个满足要求了，则返回NULL
	virtual CUserSession *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CUserSessionFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pUserSession 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserSession * pUserSession,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CUserSessionFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableMaxLocalID是一个存储最大本地报单号的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableMaxLocalID
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableMaxLocalID *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司代码
	CBrokerIDType BrokerID;
	///交易用户代码
	CUserIDType UserID;
	///最大报单本地编号
	CUserOrderLocalIDType MaxOrderLocalID;
	///前置编号
	CFrontIDType FrontID;
	///会话编号
	CSessionIDType SessionID;
	
	unsigned int HashFrontIDSessionID;
	
	///计算FrontIDSessionID的hash值
	void calHashFrontIDSessionID(void)
	{
		unsigned key=0;
		key=FrontID.hash(key);
		key=SessionID.hash(key);
		HashFrontIDSessionID=key;
	}
	
	///根据需要情况，更新FrontIDSessionID的hash值
	void updateHashFrontIDSessionID(void)
	{
	}
	
	///计算所有的hash值
	void calAllHash(void)
	{
		calHashFrontIDSessionID();
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
		updateHashFrontIDSessionID();
	}
	

private:
};

typedef const CWriteableMaxLocalID CMaxLocalID;

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDActionTrigger是操作最大本地报单号时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDActionTrigger
{
public:
	///构造方法
	CMaxLocalIDActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CMaxLocalIDActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CMaxLocalIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pMaxLocalID	要加入的MaxLocalID
	virtual void beforeAdd(CWriteableMaxLocalID *pMaxLocalID)
	{
		return;
	}
	
	///加入后触发
	///@param	pMaxLocalID	已经加入的MaxLocalID
	virtual void afterAdd(CMaxLocalID *pMaxLocalID)
	{
		return;
	}

	///更新前触发	
	///@param	pMaxLocalID	被刷新的CMaxLocalID
	///@param	pNewMaxLocalID	新的值
	virtual void beforeUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID)
	{
		return;
	}
	
	///更新后触发
	///@param	pMaxLocalID	被刷新的CMaxLocalID
	virtual void afterUpdate(CMaxLocalID *pMaxLocalID)
	{
		return;
	}
	
	///删除前触发
	///@param	pMaxLocalID	要删除的CMaxLocalID
	virtual void beforeRemove(CMaxLocalID *pMaxLocalID)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CMaxLocalIDFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDCommitTrigger是确认最大本地报单号时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDCommitTrigger
{
public:
	///构造方法
	CMaxLocalIDCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CMaxLocalIDCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CMaxLocalIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pMaxLocalID	已经加入的MaxLocalID
	virtual void commitAdd(CMaxLocalID *pMaxLocalID)
	{
		return;
	}

	///更新后触发
	///@param	pMaxLocalID	被刷新的CMaxLocalID
	///@param	poldMaxLocalID	原来的值
	virtual void commitUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pOldMaxLocalID)
	{
		return;
	}
	
	///删除后触发
	///@param	pMaxLocalID	已经删除的CMaxLocalID
	virtual void commitRemove(CWriteableMaxLocalID *pMaxLocalID)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CMaxLocalIDFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CMaxLocalIDIterator是一个对最大本地报单号的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMaxLocalIDIterator
{
public:
	///构造方法
	CMaxLocalIDIterator(void)
	{
	}

	///构造方法
	CMaxLocalIDIterator(CMaxLocalIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CMaxLocalIDIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个MaxLocalID
	///@return	下一个满足条件CMaxLocalID，如果已经没有一个满足要求了，则返回NULL
	virtual CMaxLocalID *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CMaxLocalIDFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pMaxLocalID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableMaxLocalID * pMaxLocalID,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CMaxLocalIDFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableBrkUserIDLocalID是一个存储用户本地报单号的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableBrkUserIDLocalID
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableBrkUserIDLocalID *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司代码
	CBrokerIDType BrokerID;
	///交易用户代码
	CUserIDType UserID;
	///用户本地编号
	CUserOrderLocalIDType UserOrderLocalID;
	///通道对应的APIID
	CNumberType APIID;
	///本地报单编号
	COrderLocalIDType OrderLocalID;
	
	unsigned int HashBrokerIDUserIDLocalID;
	
	///计算BrokerIDUserIDLocalID的hash值
	void calHashBrokerIDUserIDLocalID(void)
	{
		unsigned key=0;
		key=BrokerID.hash(key);
		key=UserID.hash(key);
		key=UserOrderLocalID.hash(key);
		HashBrokerIDUserIDLocalID=key;
	}
	
	///根据需要情况，更新BrokerIDUserIDLocalID的hash值
	void updateHashBrokerIDUserIDLocalID(void)
	{
	}
	
	///计算所有的hash值
	void calAllHash(void)
	{
		calHashBrokerIDUserIDLocalID();
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
		updateHashBrokerIDUserIDLocalID();
	}
	
	///构造对应的报单的指针
	///@param	pFactory	构造对应的报单的指针时，寻找的对象工厂
	///@return	找到的对应的报单的指针，如果找不到则返回NULL
	inline const CWriteablePreOrder *linkPreOrder(CPreOrderFactory *pFactory) const;

	///构造对应的报单指针
	///@param	pPreOrder	要连接到的对象
	///@return	输入的pPreOrder
	const CWriteablePreOrder *linkPreOrder(const CWriteablePreOrder *pPreOrder) const
	{
		void *target=(void *)(&(this->pPreOrder));
		*((const CWriteablePreOrder **)target)=pPreOrder;
		return pPreOrder;
	}
	
	///获取对应的报单的指针
	///@return	找到的对应的报单的指针，如果找不到则返回NULL
	const CWriteablePreOrder *getPreOrder(void) const
	{
		return pPreOrder;
	}

private:
	///对应的报单
	const CWriteablePreOrder *pPreOrder;
};

typedef const CWriteableBrkUserIDLocalID CBrkUserIDLocalID;

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDActionTrigger是操作用户本地报单号时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDActionTrigger
{
public:
	///构造方法
	CBrkUserIDLocalIDActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CBrkUserIDLocalIDActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CBrkUserIDLocalIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pBrkUserIDLocalID	要加入的BrkUserIDLocalID
	virtual void beforeAdd(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return;
	}
	
	///加入后触发
	///@param	pBrkUserIDLocalID	已经加入的BrkUserIDLocalID
	virtual void afterAdd(CBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return;
	}

	///更新前触发	
	///@param	pBrkUserIDLocalID	被刷新的CBrkUserIDLocalID
	///@param	pNewBrkUserIDLocalID	新的值
	virtual void beforeUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID)
	{
		return;
	}
	
	///更新后触发
	///@param	pBrkUserIDLocalID	被刷新的CBrkUserIDLocalID
	virtual void afterUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return;
	}
	
	///删除前触发
	///@param	pBrkUserIDLocalID	要删除的CBrkUserIDLocalID
	virtual void beforeRemove(CBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CBrkUserIDLocalIDFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDCommitTrigger是确认用户本地报单号时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDCommitTrigger
{
public:
	///构造方法
	CBrkUserIDLocalIDCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CBrkUserIDLocalIDCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CBrkUserIDLocalIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pBrkUserIDLocalID	已经加入的BrkUserIDLocalID
	virtual void commitAdd(CBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return;
	}

	///更新后触发
	///@param	pBrkUserIDLocalID	被刷新的CBrkUserIDLocalID
	///@param	poldBrkUserIDLocalID	原来的值
	virtual void commitUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pOldBrkUserIDLocalID)
	{
		return;
	}
	
	///删除后触发
	///@param	pBrkUserIDLocalID	已经删除的CBrkUserIDLocalID
	virtual void commitRemove(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CBrkUserIDLocalIDFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CBrkUserIDLocalIDIterator是一个对用户本地报单号的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CBrkUserIDLocalIDIterator
{
public:
	///构造方法
	CBrkUserIDLocalIDIterator(void)
	{
	}

	///构造方法
	CBrkUserIDLocalIDIterator(CBrkUserIDLocalIDFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CBrkUserIDLocalIDIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个BrkUserIDLocalID
	///@return	下一个满足条件CBrkUserIDLocalID，如果已经没有一个满足要求了，则返回NULL
	virtual CBrkUserIDLocalID *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CBrkUserIDLocalIDFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pBrkUserIDLocalID 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableBrkUserIDLocalID * pBrkUserIDLocalID,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CBrkUserIDLocalIDFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteablePartClientInsGroupPosition是一个存储客户合约组持仓表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteablePartClientInsGroupPosition
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteablePartClientInsGroupPosition *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///会员代码
	CParticipantIDType ParticipantID;
	///客户代码
	CClientIDType ClientID;
	///合约组代码
	CInstrumentGroupIDType InstrumentGroupID;
	///合约组多头总持仓
	CVolumeType LongPosition;
	///合约组多头保证金之和
	CMoneyType LongMargin;
	///合约组空头总持仓
	CVolumeType ShortPosition;
	///合约组空头保证金之和
	CMoneyType ShortMargin;
	///实际收取的保证金
	CMoneyType ActualMargin ;
	///合约组多头冻结总持仓
	CVolumeType LongFrozenPosition;
	///合约组多头冻结保证金之和
	CMoneyType LongFrozenMargin;
	///合约组空头冻结总持仓
	CVolumeType ShortFrozenPosition;
	///合约组空头冻结保证金之和
	CMoneyType ShortFrozenMargin;
	///实际冻结的保证金
	CMoneyType ActualFrozenMargin ;
	
	unsigned int HashPartClientAndInsGroup;
	
	///计算PartClientAndInsGroup的hash值
	void calHashPartClientAndInsGroup(void)
	{
		unsigned key=0;
		key=BrokerID.hash(key);
		key=ClientID.hash(key);
		key=InstrumentGroupID.hash(key);
		HashPartClientAndInsGroup=key;
	}
	
	///根据需要情况，更新PartClientAndInsGroup的hash值
	void updateHashPartClientAndInsGroup(void)
	{
	}
	
	///计算所有的hash值
	void calAllHash(void)
	{
		calHashPartClientAndInsGroup();
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
		updateHashPartClientAndInsGroup();
	}
	

private:
};

typedef const CWriteablePartClientInsGroupPosition CPartClientInsGroupPosition;

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionActionTrigger是操作客户合约组持仓表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionActionTrigger
{
public:
	///构造方法
	CPartClientInsGroupPositionActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CPartClientInsGroupPositionActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CPartClientInsGroupPositionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pPartClientInsGroupPosition	要加入的PartClientInsGroupPosition
	virtual void beforeAdd(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return;
	}
	
	///加入后触发
	///@param	pPartClientInsGroupPosition	已经加入的PartClientInsGroupPosition
	virtual void afterAdd(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return;
	}

	///更新前触发	
	///@param	pPartClientInsGroupPosition	被刷新的CPartClientInsGroupPosition
	///@param	pNewPartClientInsGroupPosition	新的值
	virtual void beforeUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition)
	{
		return;
	}
	
	///更新后触发
	///@param	pPartClientInsGroupPosition	被刷新的CPartClientInsGroupPosition
	virtual void afterUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return;
	}
	
	///删除前触发
	///@param	pPartClientInsGroupPosition	要删除的CPartClientInsGroupPosition
	virtual void beforeRemove(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CPartClientInsGroupPositionFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionCommitTrigger是确认客户合约组持仓表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionCommitTrigger
{
public:
	///构造方法
	CPartClientInsGroupPositionCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CPartClientInsGroupPositionCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CPartClientInsGroupPositionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pPartClientInsGroupPosition	已经加入的PartClientInsGroupPosition
	virtual void commitAdd(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return;
	}

	///更新后触发
	///@param	pPartClientInsGroupPosition	被刷新的CPartClientInsGroupPosition
	///@param	poldPartClientInsGroupPosition	原来的值
	virtual void commitUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pOldPartClientInsGroupPosition)
	{
		return;
	}
	
	///删除后触发
	///@param	pPartClientInsGroupPosition	已经删除的CPartClientInsGroupPosition
	virtual void commitRemove(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CPartClientInsGroupPositionFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CPartClientInsGroupPositionIterator是一个对客户合约组持仓表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CPartClientInsGroupPositionIterator
{
public:
	///构造方法
	CPartClientInsGroupPositionIterator(void)
	{
	}

	///构造方法
	CPartClientInsGroupPositionIterator(CPartClientInsGroupPositionFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CPartClientInsGroupPositionIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个PartClientInsGroupPosition
	///@return	下一个满足条件CPartClientInsGroupPosition，如果已经没有一个满足要求了，则返回NULL
	virtual CPartClientInsGroupPosition *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CPartClientInsGroupPositionFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pPartClientInsGroupPosition 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteablePartClientInsGroupPosition * pPartClientInsGroupPosition,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CPartClientInsGroupPositionFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableClientMarginCombType是一个存储交易编码组合保证金类型的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableClientMarginCombType
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableClientMarginCombType *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///会员代码
	CParticipantIDType ParticipantID;
	///客户代码
	CClientIDType ClientID;
	///合约组代码
	CInstrumentGroupIDType InstrumentGroupID;
	///保证金组合类型
	CClientMarginCombTypeType MarginCombType;
	
	unsigned int HashClientAndInsGroup;
	
	///计算ClientAndInsGroup的hash值
	void calHashClientAndInsGroup(void)
	{
		unsigned key=0;
		key=BrokerID.hash(key);
		key=ClientID.hash(key);
		key=InstrumentGroupID.hash(key);
		HashClientAndInsGroup=key;
	}
	
	///根据需要情况，更新ClientAndInsGroup的hash值
	void updateHashClientAndInsGroup(void)
	{
	}
	
	///计算所有的hash值
	void calAllHash(void)
	{
		calHashClientAndInsGroup();
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
		updateHashClientAndInsGroup();
	}
	

private:
};

typedef const CWriteableClientMarginCombType CClientMarginCombType;

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeActionTrigger是操作交易编码组合保证金类型时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeActionTrigger
{
public:
	///构造方法
	CClientMarginCombTypeActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CClientMarginCombTypeActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CClientMarginCombTypeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pClientMarginCombType	要加入的ClientMarginCombType
	virtual void beforeAdd(CWriteableClientMarginCombType *pClientMarginCombType)
	{
		return;
	}
	
	///加入后触发
	///@param	pClientMarginCombType	已经加入的ClientMarginCombType
	virtual void afterAdd(CClientMarginCombType *pClientMarginCombType)
	{
		return;
	}

	///更新前触发	
	///@param	pClientMarginCombType	被刷新的CClientMarginCombType
	///@param	pNewClientMarginCombType	新的值
	virtual void beforeUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType)
	{
		return;
	}
	
	///更新后触发
	///@param	pClientMarginCombType	被刷新的CClientMarginCombType
	virtual void afterUpdate(CClientMarginCombType *pClientMarginCombType)
	{
		return;
	}
	
	///删除前触发
	///@param	pClientMarginCombType	要删除的CClientMarginCombType
	virtual void beforeRemove(CClientMarginCombType *pClientMarginCombType)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CClientMarginCombTypeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeCommitTrigger是确认交易编码组合保证金类型时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeCommitTrigger
{
public:
	///构造方法
	CClientMarginCombTypeCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CClientMarginCombTypeCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CClientMarginCombTypeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pClientMarginCombType	已经加入的ClientMarginCombType
	virtual void commitAdd(CClientMarginCombType *pClientMarginCombType)
	{
		return;
	}

	///更新后触发
	///@param	pClientMarginCombType	被刷新的CClientMarginCombType
	///@param	poldClientMarginCombType	原来的值
	virtual void commitUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pOldClientMarginCombType)
	{
		return;
	}
	
	///删除后触发
	///@param	pClientMarginCombType	已经删除的CClientMarginCombType
	virtual void commitRemove(CWriteableClientMarginCombType *pClientMarginCombType)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CClientMarginCombTypeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CClientMarginCombTypeIterator是一个对交易编码组合保证金类型的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CClientMarginCombTypeIterator
{
public:
	///构造方法
	CClientMarginCombTypeIterator(void)
	{
	}

	///构造方法
	CClientMarginCombTypeIterator(CClientMarginCombTypeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CClientMarginCombTypeIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个ClientMarginCombType
	///@return	下一个满足条件CClientMarginCombType，如果已经没有一个满足要求了，则返回NULL
	virtual CClientMarginCombType *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CClientMarginCombTypeFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pClientMarginCombType 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableClientMarginCombType * pClientMarginCombType,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CClientMarginCombTypeFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInstrumentGroup是一个存储合约和合约组关系的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInstrumentGroup
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableInstrumentGroup *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///交易所代码
	CExchangeIDType ExchangeID;
	///经纪公司编号
	CBrokerIDType BrokerID;
	///合约代码
	CInstrumentIDType InstrumentID;
	///合约组代码
	CInstrumentGroupIDType InstrumentGroupID;
	
	unsigned int HashBrokerInstrumentID;
	
	///计算BrokerInstrumentID的hash值
	void calHashBrokerInstrumentID(void)
	{
		unsigned key=0;
		key=ExchangeID.hash(key);
		key=BrokerID.hash(key);
		key=InstrumentID.hash(key);
		HashBrokerInstrumentID=key;
	}
	
	///根据需要情况，更新BrokerInstrumentID的hash值
	void updateHashBrokerInstrumentID(void)
	{
	}
	
	///计算所有的hash值
	void calAllHash(void)
	{
		calHashBrokerInstrumentID();
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
		updateHashBrokerInstrumentID();
	}
	

private:
};

typedef const CWriteableInstrumentGroup CInstrumentGroup;

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupActionTrigger是操作合约和合约组关系时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupActionTrigger
{
public:
	///构造方法
	CInstrumentGroupActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInstrumentGroupActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInstrumentGroupFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pInstrumentGroup	要加入的InstrumentGroup
	virtual void beforeAdd(CWriteableInstrumentGroup *pInstrumentGroup)
	{
		return;
	}
	
	///加入后触发
	///@param	pInstrumentGroup	已经加入的InstrumentGroup
	virtual void afterAdd(CInstrumentGroup *pInstrumentGroup)
	{
		return;
	}

	///更新前触发	
	///@param	pInstrumentGroup	被刷新的CInstrumentGroup
	///@param	pNewInstrumentGroup	新的值
	virtual void beforeUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup)
	{
		return;
	}
	
	///更新后触发
	///@param	pInstrumentGroup	被刷新的CInstrumentGroup
	virtual void afterUpdate(CInstrumentGroup *pInstrumentGroup)
	{
		return;
	}
	
	///删除前触发
	///@param	pInstrumentGroup	要删除的CInstrumentGroup
	virtual void beforeRemove(CInstrumentGroup *pInstrumentGroup)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInstrumentGroupFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupCommitTrigger是确认合约和合约组关系时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupCommitTrigger
{
public:
	///构造方法
	CInstrumentGroupCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInstrumentGroupCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInstrumentGroupFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pInstrumentGroup	已经加入的InstrumentGroup
	virtual void commitAdd(CInstrumentGroup *pInstrumentGroup)
	{
		return;
	}

	///更新后触发
	///@param	pInstrumentGroup	被刷新的CInstrumentGroup
	///@param	poldInstrumentGroup	原来的值
	virtual void commitUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pOldInstrumentGroup)
	{
		return;
	}
	
	///删除后触发
	///@param	pInstrumentGroup	已经删除的CInstrumentGroup
	virtual void commitRemove(CWriteableInstrumentGroup *pInstrumentGroup)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInstrumentGroupFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInstrumentGroupIterator是一个对合约和合约组关系的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInstrumentGroupIterator
{
public:
	///构造方法
	CInstrumentGroupIterator(void)
	{
	}

	///构造方法
	CInstrumentGroupIterator(CInstrumentGroupFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CInstrumentGroupIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个InstrumentGroup
	///@return	下一个满足条件CInstrumentGroup，如果已经没有一个满足要求了，则返回NULL
	virtual CInstrumentGroup *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CInstrumentGroupFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pInstrumentGroup 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInstrumentGroup * pInstrumentGroup,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CInstrumentGroupFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableSGEDeferRate是一个存储金交所递延费率表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableSGEDeferRate
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableSGEDeferRate *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///合约代码
	CInstrumentIDType InstrumentID;
	///交易所代码
	CExchangeIDType ExchangeID;
	///交易日期
	CTradingDayType TradeDate;
	///支付方向
	CPayDirectionType Direction;
	///递延费率
	CRatioType DeferRate;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableSGEDeferRate CSGEDeferRate;

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateActionTrigger是操作金交所递延费率表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateActionTrigger
{
public:
	///构造方法
	CSGEDeferRateActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CSGEDeferRateActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CSGEDeferRateFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pSGEDeferRate	要加入的SGEDeferRate
	virtual void beforeAdd(CWriteableSGEDeferRate *pSGEDeferRate)
	{
		return;
	}
	
	///加入后触发
	///@param	pSGEDeferRate	已经加入的SGEDeferRate
	virtual void afterAdd(CSGEDeferRate *pSGEDeferRate)
	{
		return;
	}

	///更新前触发	
	///@param	pSGEDeferRate	被刷新的CSGEDeferRate
	///@param	pNewSGEDeferRate	新的值
	virtual void beforeUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate)
	{
		return;
	}
	
	///更新后触发
	///@param	pSGEDeferRate	被刷新的CSGEDeferRate
	virtual void afterUpdate(CSGEDeferRate *pSGEDeferRate)
	{
		return;
	}
	
	///删除前触发
	///@param	pSGEDeferRate	要删除的CSGEDeferRate
	virtual void beforeRemove(CSGEDeferRate *pSGEDeferRate)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CSGEDeferRateFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateCommitTrigger是确认金交所递延费率表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateCommitTrigger
{
public:
	///构造方法
	CSGEDeferRateCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CSGEDeferRateCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CSGEDeferRateFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pSGEDeferRate	已经加入的SGEDeferRate
	virtual void commitAdd(CSGEDeferRate *pSGEDeferRate)
	{
		return;
	}

	///更新后触发
	///@param	pSGEDeferRate	被刷新的CSGEDeferRate
	///@param	poldSGEDeferRate	原来的值
	virtual void commitUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pOldSGEDeferRate)
	{
		return;
	}
	
	///删除后触发
	///@param	pSGEDeferRate	已经删除的CSGEDeferRate
	virtual void commitRemove(CWriteableSGEDeferRate *pSGEDeferRate)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CSGEDeferRateFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CSGEDeferRateIterator是一个对金交所递延费率表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSGEDeferRateIterator
{
public:
	///构造方法
	CSGEDeferRateIterator(void)
	{
	}

	///构造方法
	CSGEDeferRateIterator(CSGEDeferRateFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CSGEDeferRateIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个SGEDeferRate
	///@return	下一个满足条件CSGEDeferRate，如果已经没有一个满足要求了，则返回NULL
	virtual CSGEDeferRate *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CSGEDeferRateFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pSGEDeferRate 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSGEDeferRate * pSGEDeferRate,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CSGEDeferRateFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInvestorTradingRight是一个存储投资者交易权限表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInvestorTradingRight
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableInvestorTradingRight *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///投资者编号
	CInvestorIDType InvestorID;
	///交易所代码
	CExchangeIDType ExchangeID;
	///合约代码
	CInstrumentIDType InstrumentID;
	///合约交易权限
	CTradingRightType TradingRight;
	///产品类型
	CProductClassType ProductClass;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableInvestorTradingRight CInvestorTradingRight;

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightActionTrigger是操作投资者交易权限表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightActionTrigger
{
public:
	///构造方法
	CInvestorTradingRightActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInvestorTradingRightActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInvestorTradingRightFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pInvestorTradingRight	要加入的InvestorTradingRight
	virtual void beforeAdd(CWriteableInvestorTradingRight *pInvestorTradingRight)
	{
		return;
	}
	
	///加入后触发
	///@param	pInvestorTradingRight	已经加入的InvestorTradingRight
	virtual void afterAdd(CInvestorTradingRight *pInvestorTradingRight)
	{
		return;
	}

	///更新前触发	
	///@param	pInvestorTradingRight	被刷新的CInvestorTradingRight
	///@param	pNewInvestorTradingRight	新的值
	virtual void beforeUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight)
	{
		return;
	}
	
	///更新后触发
	///@param	pInvestorTradingRight	被刷新的CInvestorTradingRight
	virtual void afterUpdate(CInvestorTradingRight *pInvestorTradingRight)
	{
		return;
	}
	
	///删除前触发
	///@param	pInvestorTradingRight	要删除的CInvestorTradingRight
	virtual void beforeRemove(CInvestorTradingRight *pInvestorTradingRight)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInvestorTradingRightFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightCommitTrigger是确认投资者交易权限表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightCommitTrigger
{
public:
	///构造方法
	CInvestorTradingRightCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInvestorTradingRightCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInvestorTradingRightFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pInvestorTradingRight	已经加入的InvestorTradingRight
	virtual void commitAdd(CInvestorTradingRight *pInvestorTradingRight)
	{
		return;
	}

	///更新后触发
	///@param	pInvestorTradingRight	被刷新的CInvestorTradingRight
	///@param	poldInvestorTradingRight	原来的值
	virtual void commitUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pOldInvestorTradingRight)
	{
		return;
	}
	
	///删除后触发
	///@param	pInvestorTradingRight	已经删除的CInvestorTradingRight
	virtual void commitRemove(CWriteableInvestorTradingRight *pInvestorTradingRight)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInvestorTradingRightFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorTradingRightIterator是一个对投资者交易权限表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorTradingRightIterator
{
public:
	///构造方法
	CInvestorTradingRightIterator(void)
	{
	}

	///构造方法
	CInvestorTradingRightIterator(CInvestorTradingRightFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorTradingRightIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个InvestorTradingRight
	///@return	下一个满足条件CInvestorTradingRight，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorTradingRight *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CInvestorTradingRightFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorTradingRight 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorTradingRight * pInvestorTradingRight,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CInvestorTradingRightFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableUserIP是一个存储交易员IP地址的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableUserIP
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableUserIP *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///交易用户代码
	CUserIDType UserID;
	///IP地址
	CIPAddressType IPAddress;
	///IP地址掩码
	CIPAddressType IPMask;
	///MAC地址
	CMacAddressType MacAddress;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableUserIP CUserIP;

/////////////////////////////////////////////////////////////////////////
///CUserIPActionTrigger是操作交易员IP地址时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPActionTrigger
{
public:
	///构造方法
	CUserIPActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CUserIPActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CUserIPFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pUserIP	要加入的UserIP
	virtual void beforeAdd(CWriteableUserIP *pUserIP)
	{
		return;
	}
	
	///加入后触发
	///@param	pUserIP	已经加入的UserIP
	virtual void afterAdd(CUserIP *pUserIP)
	{
		return;
	}

	///更新前触发	
	///@param	pUserIP	被刷新的CUserIP
	///@param	pNewUserIP	新的值
	virtual void beforeUpdate(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP)
	{
		return;
	}
	
	///更新后触发
	///@param	pUserIP	被刷新的CUserIP
	virtual void afterUpdate(CUserIP *pUserIP)
	{
		return;
	}
	
	///删除前触发
	///@param	pUserIP	要删除的CUserIP
	virtual void beforeRemove(CUserIP *pUserIP)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CUserIPFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserIPCommitTrigger是确认交易员IP地址时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPCommitTrigger
{
public:
	///构造方法
	CUserIPCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CUserIPCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CUserIPFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pUserIP	已经加入的UserIP
	virtual void commitAdd(CUserIP *pUserIP)
	{
		return;
	}

	///更新后触发
	///@param	pUserIP	被刷新的CUserIP
	///@param	poldUserIP	原来的值
	virtual void commitUpdate(CUserIP *pUserIP, CWriteableUserIP *pOldUserIP)
	{
		return;
	}
	
	///删除后触发
	///@param	pUserIP	已经删除的CUserIP
	virtual void commitRemove(CWriteableUserIP *pUserIP)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CUserIPFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CUserIPIterator是一个对交易员IP地址的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CUserIPIterator
{
public:
	///构造方法
	CUserIPIterator(void)
	{
	}

	///构造方法
	CUserIPIterator(CUserIPFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CUserIPIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个UserIP
	///@return	下一个满足条件CUserIP，如果已经没有一个满足要求了，则返回NULL
	virtual CUserIP *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CUserIPFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pUserIP 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableUserIP * pUserIP,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CUserIPFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableInvestorOptionFee是一个存储客户期权手续费率表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableInvestorOptionFee
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableInvestorOptionFee *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///交易所代码
	CExchangeIDType ExchangeID;
	///投资者编码
	CInvestorIDType InvestorID;
	///合约代码
	CInstrumentIDType InstrumentID;
	///开仓手续费按比例
	CRatioType OpenFeeRate;
	///开仓手续费按手数
	CRatioType OpenFeeAmt;
	///平仓手续费按比例
	CRatioType OffsetFeeRate;
	///平仓手续费按手数
	CRatioType OffsetFeeAmt;
	///平今仓手续费按比例
	CRatioType OTFeeRate;
	///平今仓手续费按手数
	CRatioType OTFeeAmt;
	///执行手续费按比例
	CRatioType StrikeFeeRate;
	///执行手续费按手数
	CRatioType StrikeFeeAmt;
	
	unsigned int HashBrkIDExIDIstIDVstID;
	
	///计算BrkIDExIDIstIDVstID的hash值
	void calHashBrkIDExIDIstIDVstID(void)
	{
		unsigned key=0;
		key=BrokerID.hash(key);
		key=ExchangeID.hash(key);
		key=InstrumentID.hash(key);
		key=InvestorID.hash(key);
		HashBrkIDExIDIstIDVstID=key;
	}
	
	///根据需要情况，更新BrkIDExIDIstIDVstID的hash值
	void updateHashBrkIDExIDIstIDVstID(void)
	{
	}
	
	///计算所有的hash值
	void calAllHash(void)
	{
		calHashBrkIDExIDIstIDVstID();
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
		updateHashBrkIDExIDIstIDVstID();
	}
	

private:
};

typedef const CWriteableInvestorOptionFee CInvestorOptionFee;

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeActionTrigger是操作客户期权手续费率表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeActionTrigger
{
public:
	///构造方法
	CInvestorOptionFeeActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInvestorOptionFeeActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInvestorOptionFeeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pInvestorOptionFee	要加入的InvestorOptionFee
	virtual void beforeAdd(CWriteableInvestorOptionFee *pInvestorOptionFee)
	{
		return;
	}
	
	///加入后触发
	///@param	pInvestorOptionFee	已经加入的InvestorOptionFee
	virtual void afterAdd(CInvestorOptionFee *pInvestorOptionFee)
	{
		return;
	}

	///更新前触发	
	///@param	pInvestorOptionFee	被刷新的CInvestorOptionFee
	///@param	pNewInvestorOptionFee	新的值
	virtual void beforeUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee)
	{
		return;
	}
	
	///更新后触发
	///@param	pInvestorOptionFee	被刷新的CInvestorOptionFee
	virtual void afterUpdate(CInvestorOptionFee *pInvestorOptionFee)
	{
		return;
	}
	
	///删除前触发
	///@param	pInvestorOptionFee	要删除的CInvestorOptionFee
	virtual void beforeRemove(CInvestorOptionFee *pInvestorOptionFee)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInvestorOptionFeeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeCommitTrigger是确认客户期权手续费率表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeCommitTrigger
{
public:
	///构造方法
	CInvestorOptionFeeCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CInvestorOptionFeeCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CInvestorOptionFeeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pInvestorOptionFee	已经加入的InvestorOptionFee
	virtual void commitAdd(CInvestorOptionFee *pInvestorOptionFee)
	{
		return;
	}

	///更新后触发
	///@param	pInvestorOptionFee	被刷新的CInvestorOptionFee
	///@param	poldInvestorOptionFee	原来的值
	virtual void commitUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pOldInvestorOptionFee)
	{
		return;
	}
	
	///删除后触发
	///@param	pInvestorOptionFee	已经删除的CInvestorOptionFee
	virtual void commitRemove(CWriteableInvestorOptionFee *pInvestorOptionFee)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CInvestorOptionFeeFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CInvestorOptionFeeIterator是一个对客户期权手续费率表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CInvestorOptionFeeIterator
{
public:
	///构造方法
	CInvestorOptionFeeIterator(void)
	{
	}

	///构造方法
	CInvestorOptionFeeIterator(CInvestorOptionFeeFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CInvestorOptionFeeIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个InvestorOptionFee
	///@return	下一个满足条件CInvestorOptionFee，如果已经没有一个满足要求了，则返回NULL
	virtual CInvestorOptionFee *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CInvestorOptionFeeFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pInvestorOptionFee 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableInvestorOptionFee * pInvestorOptionFee,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CInvestorOptionFeeFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableMarketData是一个存储实时行情表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableMarketData
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableMarketData *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///交易日
	CTradingDayType TradingDay;
	///交易所代码
	CExchangeIDType ExchangeID;
	///合约代码
	CInstrumentIDType InstrumentID;
	///今开盘
	CPriceType OpenPrice;
	///最高价
	CPriceType HighestPrice;
	///最低价
	CPriceType LowestPrice;
	///最新价
	CPriceType LastPrice;
	///数量
	CVolumeType Volume;
	///成交金额
	CMoneyType Turnover;
	///跌停板价
	CPriceType LowerLimitPrice;
	///涨停板价
	CPriceType UpperLimitPrice;
	///持仓量
	CVolumeType OpenInterest;
	///昨收盘
	CPriceType PreClosePrice;
	///昨持仓量
	CVolumeType PreOpenInterest;
	///昨结算
	CPriceType PreSettlementPrice;
	///今结算
	CPriceType SettlementPrice;
	///最后修改毫秒
	CMillisecType UpdateMillisec;
	///最后修改时间
	CTimeType UpdateTime;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableMarketData CMarketData;

/////////////////////////////////////////////////////////////////////////
///CMarketDataActionTrigger是操作实时行情表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataActionTrigger
{
public:
	///构造方法
	CMarketDataActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CMarketDataActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CMarketDataFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pMarketData	要加入的MarketData
	virtual void beforeAdd(CWriteableMarketData *pMarketData)
	{
		return;
	}
	
	///加入后触发
	///@param	pMarketData	已经加入的MarketData
	virtual void afterAdd(CMarketData *pMarketData)
	{
		return;
	}

	///更新前触发	
	///@param	pMarketData	被刷新的CMarketData
	///@param	pNewMarketData	新的值
	virtual void beforeUpdate(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData)
	{
		return;
	}
	
	///更新后触发
	///@param	pMarketData	被刷新的CMarketData
	virtual void afterUpdate(CMarketData *pMarketData)
	{
		return;
	}
	
	///删除前触发
	///@param	pMarketData	要删除的CMarketData
	virtual void beforeRemove(CMarketData *pMarketData)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CMarketDataFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataCommitTrigger是确认实时行情表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataCommitTrigger
{
public:
	///构造方法
	CMarketDataCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CMarketDataCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CMarketDataFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pMarketData	已经加入的MarketData
	virtual void commitAdd(CMarketData *pMarketData)
	{
		return;
	}

	///更新后触发
	///@param	pMarketData	被刷新的CMarketData
	///@param	poldMarketData	原来的值
	virtual void commitUpdate(CMarketData *pMarketData, CWriteableMarketData *pOldMarketData)
	{
		return;
	}
	
	///删除后触发
	///@param	pMarketData	已经删除的CMarketData
	virtual void commitRemove(CWriteableMarketData *pMarketData)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CMarketDataFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CMarketDataIterator是一个对实时行情表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CMarketDataIterator
{
public:
	///构造方法
	CMarketDataIterator(void)
	{
	}

	///构造方法
	CMarketDataIterator(CMarketDataFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CMarketDataIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个MarketData
	///@return	下一个满足条件CMarketData，如果已经没有一个满足要求了，则返回NULL
	virtual CMarketData *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CMarketDataFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pMarketData 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableMarketData * pMarketData,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	CMarketDataFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableOrderDelay是一个存储委托延迟表的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableOrderDelay
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableOrderDelay *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///经纪公司编号
	CBrokerIDType BrokerID;
	///用户代码
	CUserIDType UserID;
	///用户本地报单号
	CUserOrderLocalIDType UserOrderLocalID;
	///前置编号
	CFrontIDType FrontID;
	///会话编号
	CSessionIDType SessionID;
	///请求编号
	CRequestIDType RequestID;
	///Ftdengine接受下层时间戳
	CILocalTimeType FTdRecvDown;
	///接受下层时间戳
	CILocalTimeType CoreRecvDown;
	///发送上层时间戳
	CILocalTimeType CoreSendUp;
	///接受上层时间戳
	CILocalTimeType CoreRecvUp;
	///发送下层时间戳
	CILocalTimeType CoreSendDown;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableOrderDelay COrderDelay;

/////////////////////////////////////////////////////////////////////////
///COrderDelayActionTrigger是操作委托延迟表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayActionTrigger
{
public:
	///构造方法
	COrderDelayActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~COrderDelayActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(COrderDelayFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pOrderDelay	要加入的OrderDelay
	virtual void beforeAdd(CWriteableOrderDelay *pOrderDelay)
	{
		return;
	}
	
	///加入后触发
	///@param	pOrderDelay	已经加入的OrderDelay
	virtual void afterAdd(COrderDelay *pOrderDelay)
	{
		return;
	}

	///更新前触发	
	///@param	pOrderDelay	被刷新的COrderDelay
	///@param	pNewOrderDelay	新的值
	virtual void beforeUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay)
	{
		return;
	}
	
	///更新后触发
	///@param	pOrderDelay	被刷新的COrderDelay
	virtual void afterUpdate(COrderDelay *pOrderDelay)
	{
		return;
	}
	
	///删除前触发
	///@param	pOrderDelay	要删除的COrderDelay
	virtual void beforeRemove(COrderDelay *pOrderDelay)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	COrderDelayFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayCommitTrigger是确认委托延迟表时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayCommitTrigger
{
public:
	///构造方法
	COrderDelayCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~COrderDelayCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(COrderDelayFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pOrderDelay	已经加入的OrderDelay
	virtual void commitAdd(COrderDelay *pOrderDelay)
	{
		return;
	}

	///更新后触发
	///@param	pOrderDelay	被刷新的COrderDelay
	///@param	poldOrderDelay	原来的值
	virtual void commitUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pOldOrderDelay)
	{
		return;
	}
	
	///删除后触发
	///@param	pOrderDelay	已经删除的COrderDelay
	virtual void commitRemove(CWriteableOrderDelay *pOrderDelay)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	COrderDelayFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///COrderDelayIterator是一个对委托延迟表的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class COrderDelayIterator
{
public:
	///构造方法
	COrderDelayIterator(void)
	{
	}

	///构造方法
	COrderDelayIterator(COrderDelayFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~COrderDelayIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个OrderDelay
	///@return	下一个满足条件COrderDelay，如果已经没有一个满足要求了，则返回NULL
	virtual COrderDelay *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	COrderDelayFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pOrderDelay 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableOrderDelay * pOrderDelay,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
	COrderDelayFactory *m_Factory;	
};

/////////////////////////////////////////////////////////////////////////
///CWriteableSystemInfo是一个存储QDP系统信息的对象，可以写出。
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CWriteableSystemInfo
{
public:
	///向CSV文件中写出标题行
	///@param	output	要写出的文件
	static void writeCSVHead(FILE *output);

	void output(CLogger *pLogger,int indent=0);
	
	///初始化操作，将所有的字段清空
	void init(void);
	
	///从文件读入
	///@param	input	读入的文件
	///@return	1表示读入成功，0表示读入失败
	int read(FILE *input);
	
	///向文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int write(FILE *output) const;
	
	///从CSV文件读入
	///@param	input	读入的文件
	///@param	pNames	各个字段的名称，如果为NULL，则顺序读出
	///@return	1表示读入成功，0表示读入失败
	int readCSV(FILE *input,vector<char *> *pNames=NULL);
	
	///向CSV文件写出
	///@param	output 写出的文件
	///@return	1表时写出成功，0表示写出失败
	int writeCSV(FILE *output) const;

	///检查数据的合法性
	///@return	1表示合法，0表示不合法
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

	///将内容写到文件中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	index	要在前面显示的下标值，一般用于数组分量的显示，用-1表示不显示
	void dump(FILE *fp=NULL,int index=-1) const;
	
	///将内容写入文件，突出显示变化的内容
	///@param	fp	要写出的文件,NULL表示stdout
	///@param	pOriginal	要比较的原来内容
	void dumpDiff(FILE *fp, const CWriteableSystemInfo *pOriginal) const;
	
	///将内容写到文件的一行中,用于DEBUG
	///@param	fp	要写出的文件,NULL表示stdout
	void dumpInLine(FILE *fp=NULL) const;

	///将内容写到一个字符串中
	///@param	target	要写的字符串，叫用方应当保证其有足够的空间
	void dumpString(char *target) const;

	///QDP系统编号
	CSystemIDType SystemID;
	///QDP系统名称
	CSystemNameType SystemName;
	///QDP系统IP地址
	CIPAddressType SystemIP;
	
	
	///计算所有的hash值
	void calAllHash(void)
	{
	}
	
	///更新所有的hash值
	void updateAllHash(void)
	{
	}
	

private:
};

typedef const CWriteableSystemInfo CSystemInfo;

/////////////////////////////////////////////////////////////////////////
///CSystemInfoActionTrigger是操作QDP系统信息时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoActionTrigger
{
public:
	///构造方法
	CSystemInfoActionTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CSystemInfoActionTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CSystemInfoFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入前触发
	///@param	pSystemInfo	要加入的SystemInfo
	virtual void beforeAdd(CWriteableSystemInfo *pSystemInfo)
	{
		return;
	}
	
	///加入后触发
	///@param	pSystemInfo	已经加入的SystemInfo
	virtual void afterAdd(CSystemInfo *pSystemInfo)
	{
		return;
	}

	///更新前触发	
	///@param	pSystemInfo	被刷新的CSystemInfo
	///@param	pNewSystemInfo	新的值
	virtual void beforeUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo)
	{
		return;
	}
	
	///更新后触发
	///@param	pSystemInfo	被刷新的CSystemInfo
	virtual void afterUpdate(CSystemInfo *pSystemInfo)
	{
		return;
	}
	
	///删除前触发
	///@param	pSystemInfo	要删除的CSystemInfo
	virtual void beforeRemove(CSystemInfo *pSystemInfo)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CSystemInfoFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoCommitTrigger是确认QDP系统信息时的触发器
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoCommitTrigger
{
public:
	///构造方法
	CSystemInfoCommitTrigger(void)
	{
	}
	
	///析构方法
	virtual ~CSystemInfoCommitTrigger(void)
	{
	}

	///设定对应的对象工厂
	///@param	pFactory	指定的对象工厂
	void setFactory(CSystemInfoFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///加入后触发
	///@param	pSystemInfo	已经加入的SystemInfo
	virtual void commitAdd(CSystemInfo *pSystemInfo)
	{
		return;
	}

	///更新后触发
	///@param	pSystemInfo	被刷新的CSystemInfo
	///@param	poldSystemInfo	原来的值
	virtual void commitUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pOldSystemInfo)
	{
		return;
	}
	
	///删除后触发
	///@param	pSystemInfo	已经删除的CSystemInfo
	virtual void commitRemove(CWriteableSystemInfo *pSystemInfo)
	{
		return;
	}
protected:
	///该触发器对应的对象工厂
	CSystemInfoFactory *m_Factory;
};

/////////////////////////////////////////////////////////////////////////
///CSystemInfoIterator是一个对QDP系统信息的枚举器接口
///@author	XUZH
///@version	1.0
/////////////////////////////////////////////////////////////////////////
class CSystemInfoIterator
{
public:
	///构造方法
	CSystemInfoIterator(void)
	{
	}

	///构造方法
	CSystemInfoIterator(CSystemInfoFactory *pFactory)
	{
		m_Factory=pFactory;
	}

	///析构方法，将负责释放所占用的空间
	virtual ~CSystemInfoIterator(void);
	
	///释放自己
	virtual void free(void)
	{
		delete this;
	}

	///获得下一个SystemInfo
	///@return	下一个满足条件CSystemInfo，如果已经没有一个满足要求了，则返回NULL
	virtual CSystemInfo *next(void)=0;
	
	///获得对应的对象工厂
	///@return	对应的对象工厂
	CSystemInfoFactory *getFactory(void)
	{
		return m_Factory;
	}
	
	///删除Iterator当前指向的纪录
	///@param	pTransaction	此次删除属于的事务，NULL表示不属于任何事务，立即执行
	virtual void DeleteCurrent(CTransaction *pTransaction = NULL) = 0;
	
	///更新当前Iterator指向的纪录
	///@param	pSystemInfo 需要更新成的新纪录内容
	///@param	pTransaction	此次更新属于的事务，NULL表示不属于任何事务，立即执行
	///@param	updateIndex	true表示需要更新索引，false表示不需要更新索引
	virtual void UpdateCurrent(CWriteableSystemInfo * pSystemInfo,CTransaction *pTransaction = NULL, bool updateIndex=true)=0;
	
	///将本枚举器中所有内容全部输出
	///@param	output	要输出的位置
	void dump(FILE *output);

protected:
	///进行查询时使用的对象工厂
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


