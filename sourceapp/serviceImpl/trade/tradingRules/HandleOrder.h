/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file CInitServiceImpl.h
///@brief定义了类CInitServiceImpl
///@history 
///20060113	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CHandleOrder_H
#define CHandleOrder_H

#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "XtpData.h"
#include "errorDefine.h"
#include "CMemoryDB.h"
#include "Flow.h"
#include "XTPPackage.h"
#include "XtpPackageDesc.h"
#include "RuleHandleBase.h"
#include "customDataType.h"
#include "platform.h"
#include "BaseCheck.h"


#define EX_SGE "SGE"
typedef vector<CWriteableSeat*>  VectorSeatInfo;
/////////////////////////////////////////////////////////////////////////
///CInitServiceImpl是一个完成交易所数据初始化的实现
///@author	xuzh
///@version	1.0,20060113
/////////////////////////////////////////////////////////////////////////
class CHandleOrder : public CRuleHandleBase
{
public:
	///构造函数
	///@param	pDB	本实现使用的内存数据库
	///@param	pErrorEngine	用于报错的错误引擎
	
	virtual ~CHandleOrder();
	virtual bool HandleOrderInsert(CWriteableIndexPreOrder *pIndexPreOrder,CWriteablePreOrder *pPreOrder,const TSessionRef &sessionRef,CTransaction *pTransaction);
	virtual bool HandleRspOrderInsert(CPreOrder *PreOrder,CWriteablePreOrder *wtbPreOrder,CRspInfoField*  pRspInfoField,CTransaction *pTransaction);
    virtual bool HandleRtnOrder(COrderField *pOrderField,const TSessionRef &sessionRef,CTransaction *pTransaction,bool bSendRtn=true);
	virtual bool HandleLocalOrderInsertFailed(CInputOrderField *pOrderField);
	virtual bool HandleLocalOrderInsertFailed(CWriteablePreOrder *pPreOrder);
    virtual bool DumpDebugInfo();

	void AddOrderDelay(CPreOrder *pPreOrder);
	void InputLong(long &LocalTime)
	{
#ifndef  WIN32
		gettimeofday(&m_nBeginTime, NULL);
		LocalTime = m_nBeginTime.tv_sec*1000000+m_nBeginTime.tv_usec;
#else
		_ftime( &m_nBeginTime );
		LocalTime = m_nBeginTime.time*1000+m_nBeginTime.millitm;
#endif	
	}
	void InputLocalTime(CILocalTimeType &LocalTime)
	{
#ifndef  WIN32
		gettimeofday(&m_nBeginTime, NULL);
		LocalTime = m_nBeginTime.tv_sec*1000000+m_nBeginTime.tv_usec;
#else
		_ftime( &m_nBeginTime );
		LocalTime = m_nBeginTime.time*1000+m_nBeginTime.millitm;
#endif	
	}
protected:
    //构造函数定义为受保护的，是为了防止生成CHandleOrder对象。必须生成子类对象。
	CHandleOrder(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult);
	bool HandleRtnOrderCancel(COrderField *pOrderField,const TSessionRef &sessionRef,CTransaction *pTransaction,bool bSendRtn=true);
	void CopyFieldOrderFromOrderInsertFailed(CInputOrderField* pInputOrderField, COrderInsertFailed* pOrderInsertFailed);
	void CopyFieldOrderFromPreOrder(COrderField* pOrderField, CPreOrder* pPreOrder);
	void PrepareWritableOrder(CWriteableOrder* pWritableOrder, CPreOrder* pPreOrder);
	void PrepareWritableOrder(CWriteableOrder* pWritableOrder, CPreOrder* pPreOrder,COrderField* pOrderField);
    void PrepareWritableOrder(CWriteableOrder* pWritableOrder, COrderField *pOrderField);
	void CopyFieldInputOrderFromPreOrder(CInputOrderField* pOrderField, CPreOrder* pPreOrder);
    bool RtnOrderFromRecoveryOrPrivateFlow(COrderField** ppOrderField,CTransaction *pTransaction);
	void CopyFieldOrderFromOrder(COrderField* pOrderField, COrder* pOrder);

	void SendOrderField(COrderField *pOrderField,bool bSendRtn=true);
private:
	///检查是否超级会话
	///@param	sessionRef	会话引用
	///@return	true表示是，false表示否
protected:
	CXTPPackage                               *m_pPubMessage;
	map<CExchangeIDType,VectorSeatInfo*>		m_MapSeats;
    CBaseCheck	                              *m_pBaseCheck;
	int  m_CZCEForQuoteInterval;
#ifndef WIN32
	struct timeval m_nBeginTime; //原始采样时间
#else
	struct _timeb  m_nBeginTime;
#endif
};

#endif
