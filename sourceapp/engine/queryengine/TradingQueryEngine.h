/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file MemoryTradeEngine.h
///@brief定义了类CMemoryTradeEngine
///@history 
///20060118	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef TRADEQUERYENGINE_H
#define TRADEQUERYENGINE_H

#include "Engine.h"

//#include "CInitServiceCheckImpl.h" //longqy
//#include "InitServiceXTPLink.h" //longqy

#include "TradingQueryServiceImpl.h"
#include "TradingQueryServiceXTPLink.h"

#include "TradingResultImpl.h"
#include "TradingResultServiceXtpLink.h"

#include "CConfig.h"
#include "Flow.h"
#include "FibServerApi.h"
#include "CMemoryDB.h"
#include "XtpData.h"



class CUsScheduler
{
public:
	CUsScheduler(CFlow *pMemChangeFlow);
	virtual ~CUsScheduler();
	virtual void Dispatch(const char *pszObjectName, CFieldDescribe *pDescirbe, const void *pData, CMdbActionTypeType nActionType);
	
private:	
	CXTPPackage	*m_pPubMessage;
	CFlow *m_pMemChangeFlow;	
};


template <typename TF,typename TW,typename T, typename BaseTrigger,bool bInsertSensitive = true, bool bUpdateSensitive = true, bool bDeleteSensitive = false>
class CUsTrigger:public BaseTrigger
{
public:
	///构造方法
	CUsTrigger(CUsScheduler *pMdbSch, const char *pszObjectName, CMemoryDB *pDB, bool bCheckSyncStatus)
	{
		m_pUsSch = pMdbSch;
		m_pszObjectName = pszObjectName;
		m_pDB = pDB;
		m_bCheckSyncStatus = bCheckSyncStatus;	
	}
	
	///析构方法
	virtual ~CUsTrigger(void)
	{
	}
	
	///加入后触发
	///@param TW 要加入的TW数据
	virtual void commitAdd(T* pData)
	{
		if (bInsertSensitive)
		{
			if (!m_bCheckSyncStatus || getDataSyncStatus() == DS_Synchronized)
			{
				m_pUsSch->Dispatch(m_pszObjectName, &TF::m_Describe, pData, MDB_INSERT);
			}
		}
	}
	
	///更新后触发
	///@param T 被刷新的T
	///@param TW 新的值
	virtual void commitUpdate(T* pData, TW *pWriteable)
	{
		if (bUpdateSensitive)
		{
			if (!m_bCheckSyncStatus || getDataSyncStatus() == DS_Synchronized)
			{
				m_pUsSch->Dispatch(m_pszObjectName, &TF::m_Describe, pData, MDB_UPDATE);
			}			
		}
	}
	
	///删除后触发
	///@param T 要删除的T
	virtual void commitRemove(TW* pWriteable)
	{
		if (bDeleteSensitive)
		{
			if (!m_bCheckSyncStatus || getDataSyncStatus() == DS_Synchronized)
			{
				m_pUsSch->Dispatch(m_pszObjectName, &TF::m_Describe, pWriteable, MDB_DELETE);
			}			
		}
	}
	
protected:
	CDataSyncStatusType getDataSyncStatus()
	{
		CDataSyncStatusType retDataSyncStatus=DS_Asynchronous;
		CDataSyncStatus* pDataSyncStatus=m_pDB->m_DataSyncStatusFactory->getFirst();
		m_pDB->m_DataSyncStatusFactory->endGet();
		if (pDataSyncStatus!=NULL)
		{
			retDataSyncStatus=pDataSyncStatus->DataSyncStatus;
		}
		return retDataSyncStatus;
	}
	
protected:
	CUsScheduler *m_pUsSch;	//调度器
	const char *m_pszObjectName;
	CMemoryDB *m_pDB;
	bool m_bCheckSyncStatus;	
};

#define DEFINE_US_MDB_TRIGGER(objtype, objname)		\
	typedef CUsTrigger<C##objtype##Field,CWriteable##objname,C##objname,C##objname##CommitTrigger > C##objname##Trigger; \
C##objname##Trigger  *m_p##objname##Trigger;

#define DEFINE_US_MDB_DELETE_TRIGGER(objtype, objname)		\
	typedef CUsTrigger<C##objtype##Field,CWriteable##objname,C##objname,C##objname##CommitTrigger,true,true,true > C##objname##Trigger; \
	C##objname##Trigger  *m_p##objname##Trigger;


/////////////////////////////////////////////////////////////////////////
///CMemoryTradeEngine是一个基于内存消息传送的交易引擎，包含了交易用的内存
///服务连接
///@author	xuzh
///@version	1.0,20060118
/////////////////////////////////////////////////////////////////////////
class CTradingQueryEngine: public CEngine
{
public:
	///构造函数
	///@param	pConfig	创建引擎需要使用的配置
	///@param	pApi	用于返回查询结果的API
	///@param	recovery	是否使用恢复模式
	///@param	verbose	true表示要输出结果，flase表示不要输出结果
	CTradingQueryEngine(CConfig *pConfig,CFibServerApi *pApi,CFlow * pSendFlow,CUsScheduler *pMDBScheduler,bool verbose=true);
	
	virtual ~CTradingQueryEngine(void);	

private:
	DEFINE_US_MDB_TRIGGER(Order, Order);//委托
	DEFINE_US_MDB_TRIGGER(Trade, Trade);//成交
	DEFINE_US_MDB_TRIGGER(InvestorAccount, InvestorAccount);//资金
	DEFINE_US_MDB_TRIGGER(InvestorPosition, InvestorPosition);//持仓
	DEFINE_US_MDB_TRIGGER(User, User);//修改用户密码
	DEFINE_US_MDB_DELETE_TRIGGER(UserSession, UserSession);//UserSession
	DEFINE_US_MDB_TRIGGER(Instrument, Instrument);//合约表
	DEFINE_US_MDB_TRIGGER(MarketData, MarketData);
	DEFINE_US_MDB_TRIGGER(Exchange, Exchange);//交易所表
	//DEFINE_US_MDB_TRIGGER(ExchTimeDiff, ExchTimeDiff);//交易所时间偏差
	//	DEFINE_US_MDB_TRIGGER(SystemStatus, SystemStatus);//系统状态表
	DEFINE_US_MDB_TRIGGER(OrderInsertFailed, OrderInsertFailed);//错单表  liumeng 20140817
	DEFINE_US_MDB_TRIGGER(ClientTradingID, ClientTradingID);
	DEFINE_US_MDB_TRIGGER(InvestorMargin, InvestorMargin);
	DEFINE_US_MDB_TRIGGER(InvestorFee, InvestorFee);
	DEFINE_US_MDB_TRIGGER(Investor, Investor);
	DEFINE_US_MDB_TRIGGER(UserInvestor, UserInvestor);
	DEFINE_US_MDB_TRIGGER(Seat, Seat);
	DEFINE_US_MDB_TRIGGER(DataSyncStatus,DataSyncStatus);
	DEFINE_US_MDB_TRIGGER(SGEDeferRate,SGEDeferRate);
	DEFINE_US_MDB_DELETE_TRIGGER(InvestorTradingRight, InvestorTradingRight);
	DEFINE_US_MDB_TRIGGER(InvestorOptionFee, InvestorOptionFee);
	DEFINE_US_MDB_TRIGGER(SystemInfo, SystemInfo);

	IServiceResponser	 *m_pServiceResponser;
	IServiceResponser    *m_pRequestResponser;
	CFibServerApi *m_pServerApi;

	CTradingQueryServiceXtpLink *m_pTradingQueryXTPLink;
	CTradingQueryImpl			*m_pTradingQueryService;
	
	CTradingResultServiceXtpLink *m_pTradingResultServiceXtpLink;
	CTradingResultImpl			*m_pTradingResultService;

	CUsScheduler *m_pMDBScheduler;
	
};

#endif
