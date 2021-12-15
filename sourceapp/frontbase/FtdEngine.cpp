// FtdEngine.cpp: implementation of the CFtdEngine class.
//
// 20061011 hwp  增加对SSL的检查，修改了方法OnReqUserLogin 
//                  OnReqUserLogin可能引起断线，调用处增加对返回值的检查
// 20070509 hwp  原HandleResponse中一上来就将非本前置的应答忽略了，
//                  会造成各前置产生的私有流中的ErrRtn不同。
// 20070704 hwp  增加基于交易员的私有流
// 20070807 hwp  增加登录时对接口版本的检查
// 20070822 hwp  修正QUICK方式订阅私有流和公共流在日初时导致重传的问题
// 20071009 hwp  撤销报单应答和报单操作应答中部分原来为压缩数据而清空
//                  的字段
// 20071019 hwp  撤销所有报单应答中部分原来为压缩数据而清空的字段，
//                  影响FTD_TID_RspOrderInsert和FTD_TID_ErrRtnOrderInsert
// 20071012 hwp  增加订阅指令（ReqSubscribeTopic），使交易员端可以自行
//                  控制流的重传，有利于交易员端保证事务的完整性
// 20071119 xuzh  增加登录时重传起始序号的有效性检查
// 20080626 hwp  NT-0041对话流和查询流不再使用Flow对象，只管理序号，减少内存占用
// 20080701 hwp  NT-0035数据中心通知，登录时检查数据中心代码，根据需要
//                  发出数据流回退通知
// 20080721 hwp  NT-0045-分席位流控：根据RspUserLogin，设定会话流控限额。
// 20080727 hwp  NT-0048:扩展CSessionFactory::CreateSession参数，便于创建
//                  会话时区分不同的连接
// 20081128 hwp  NT-0056-UserAPI增加查询数据流当前长度的方法
// 20090109 hwp	NT-0062:交易前置的登录应答中返回私有流长度
// 20090427 hwp  NT-0071:将会话的心跳模式设置为Slave模式
// 20090510 xuzh  NT-0075：前置恢复传送报单插入时间
// 20090514 hwp  NT-0079：修正RspQryTopic和RspSubscribeTopic应答错误
// 20110922 xuzh  客户查询应答数据转换不用代码自动生成赋值代码
///////////////////////////////////////////////////////////////////////
#include "public.h"
#include "FtdEngine.h"
#include "XtpPackageDesc.h"
#include "FtdPackageDesc.h"
#include "FtdData.h"
#include "UFCopy.h"
#include "monitorIndex.h"

//static CIntTotalMonitorIndex FTDRequestIndex("HandleFTDRequest",5);
//static CIntTotalMonitorIndex FTDQueryIndex("HandleFTDQuery",5);
//static CIntTotalMonitorIndex FTDErrorIndex("HandleFTDError",5);

extern int	   g_StartMode;

extern bool    g_bLatencyOut;

#define MSG_SSLERR_INVALID_USERID	0xB001

//////////////////////////////////////////////////////////////////////
/**收到客户端的业务请求，转发到总线上
*@param XtpTid 转发到总线上的XTP报文的TID
*@param FtdFieldType 收到的FTD报文的业务数据域类型
*@param xtpFieldType 转发到总线上的XTP报文的业务数据域类型
*@param CopyField FTD数据域拷贝到XTP数据域的代码
*/
#define FTD_PREPARE_FORWARD(XtpTid, FtdFieldType, XtpFieldType, CopyField)		\
	FtdFieldType ftdField;													\
	if(FTDC_GET_SINGLE_FIELD(pFTDCPackage, &ftdField) <= 0)					\
	{																		\
		/*没有取到报单请求域，断开连接*/									\
		pSession->Disconnect(MSG_FTDCERR_BADPACKAGE);						\
		return -1;															\
	}																		\
	/*转换报文，发往交易引擎*/												\
	m_pFrontForwarder->PrepareForward(&m_reqPackage, XtpTid,				\
	pSession->GetSessionID(), pFTDCPackage->GetRequestId());		\
	XtpFieldType xtpField;													\
	memset(&xtpField, 0, sizeof(xtpField));									\
	CopyField																\
	XTP_ADD_FIELD(&m_reqPackage, &xtpField);

/**收到客户端的业务请求，转发到总线上
*@param XtpTid 转发到总线上的XTP报文的TID
*@param FtdFieldType 收到的FTD报文的业务数据域类型
*@param xtpFieldType 转发到总线上的XTP报文的业务数据域类型
*@param CopyField FTD数据域拷贝到XTP数据域的代码
*/
#define FTD_REQ_FORWARD(XtpTid, FtdFieldType, XtpFieldType, CopyField)			\
	{																			\
		FTD_PREPARE_FORWARD(XtpTid, FtdFieldType, XtpFieldType, CopyField);		\
		m_pFrontForwarder->ForwardTransaction(&m_reqPackage);					\
	}

/**收到总线的业务应答，转发到对话流 
*@param Chain
*@param FtdTid 转发给客户端的FTD报文的TID
*@param FtdFieldType 转发给客户端的FTD报文的业务数据域类型
*@param xtpFieldType 收到的XTP报文的业务数据域类型
*@param CopyField XTP数据域拷贝到FTD数据域的代码
*/
#define XTP_RSP_TO_DIALOG(FtdTid, FtdFieldType, XtpFieldType, CopyField)		\
		m_rspPackage.PreparePackage(FtdTid, pMessage->GetChain(), FTD_VERSION);	\
		m_rspPackage.SetRequestId(pMessage->GetRequestID());					\
		/*先处理响应信息*/														\
		CRspInfoField rspInfoField;												\
		if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) > 0)					\
		{																		\
			CFTDRspInfoField ftdRspInfoField;									\
			CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);				\
			FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);					\
		}																		\
		/*处理业务信息*/														\
		FtdFieldType ftdField;													\
		XtpFieldType xtpField;													\
		CNamedFieldIterator itor =												\
			pMessage->GetNamedFieldIterator(&XtpFieldType::m_Describe);			\
		while (!itor.IsEnd())													\
		{																		\
			itor.Retrieve(&xtpField);											\
			CopyField;															\
			FTDC_ADD_FIELD(&m_rspPackage, &ftdField);							\
			itor.Next();														\
		}																		\
		/*向客户端出出应答*/													\
		FTDC_HEADER_DEBUG(&m_rspPackage);										\
		if (pSession != NULL)													\
		{																		\
			SendToDialogFlow(pSession, &m_rspPackage);							\
		}																		\

/**收到总线的业务应答，转发到对话流和私有流 
*@param Chain
*@param FtdTid 转发给客户端的FTD报文的TID
*@param FtdFieldType 转发给客户端的FTD报文的业务数据域类型
*@param xtpFieldType 收到的XTP报文的业务数据域类型
*@param CopyField XTP数据域拷贝到FTD数据域的代码
*/
#define XTP_RSP_FORWARD_PRIVATE(FtdTid, PrivateFtdTid, FtdFieldType, XtpFieldType, CopyField)\
	{																			\
		CRspInfoField rspInfoField;												\
		if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)					\
		{																		\
			break;																\
		}																		\
		if(pSession == NULL && rspInfoField.ErrorID == 0)						\
		{																		\
			break;																\
		}																		\
		XtpFieldType xtpField;													\
		if (XTP_GET_SINGLE_FIELD(pMessage, &xtpField) <= 0)						\
		{																		\
			break;																\
		}																		\
		CFTDRspInfoField ftdRspInfoField;										\
		CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);					\
		FtdFieldType ftdField;													\
		CopyField;																\
		if (pSession != NULL)													\
		{																		\
			m_rspPackage.PreparePackage(FtdTid, FTDC_CHAIN_LAST, FTD_VERSION);	\
			m_rspPackage.SetRequestId(pMessage->GetRequestID());				\
			FTDC_ADD_FIELD(&m_rspPackage, &ftdField);							\
			FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);					\
			SendToDialogFlow(pSession, &m_rspPackage);							\
		}																		\
		if (rspInfoField.ErrorID != 0)											\
		{																		\
			m_rspPackage.PreparePackage(PrivateFtdTid, FTDC_CHAIN_LAST, FTD_VERSION);\
			FTDC_ADD_FIELD(&m_rspPackage, &ftdField);							\
			FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);					\
			int nIndex = AppendToPrivateFlow(&m_rspPackage);					\
			SendToPrivateFlow(xtpField.BrokerID, nIndex);					\
			SendToUserFlow(xtpField.BrokerID,xtpField.UserID, nIndex);							\
		}																		\
	}

/**收到总线的业务应答，转发到对话流 
*@param Chain
*@param FtdTid 转发给客户端的FTD报文的TID
*@param PrivateFtdTid 需要转发到私有流的FTD报文的TID
*@param FtdFieldType 转发给客户端的FTD报文的业务数据域类型
*@param xtpFieldType 收到的XTP报文的业务数据域类型
*@param CopyField XTP数据域拷贝到FTD数据域的代码
*/
#define XTP_RSP_FORWARD(FtdTid, FtdFieldType, XtpFieldType, CopyField)\
	{																			\
		if (pSession == NULL)													\
		{																		\
			break;																\
		}																		\
		/*转发到对话流*/														\
		XTP_RSP_TO_DIALOG(FtdTid, FtdFieldType, XtpFieldType, CopyField)		\
	}

/**收到总线的查询结果，转发给客户端 
*@param Chain
*@param FtdTid 转发给客户端的FTD报文的TID
*@param FtdFieldType 转发给客户端的FTD报文的业务数据域类型
*@param xtpFieldType 收到的XTP报文的业务数据域类型
*@param CopyField XTP数据域拷贝到FTD数据域的代码
*/
#define XTP_QRY_FORWARD(FtdTid, FtdFieldType, XtpFieldType, CopyField)			\
	{																			\
		if (pSession == NULL)													\
		{																		\
			break;																\
		}																		\
		m_rspPackage.PreparePackage(FtdTid, pMessage->GetChain(), FTD_VERSION);	\
		m_rspPackage.SetRequestId(pMessage->GetRequestID());					\
		/*先处理响应信息*/														\
		CRspInfoField rspInfoField;												\
		if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) > 0)					\
		{																		\
			CFTDRspInfoField ftdRspInfoField;									\
			CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);				\
			FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);					\
		}																		\
		/*处理业务信息*/														\
		FtdFieldType ftdField;													\
		XtpFieldType xtpField;													\
		CNamedFieldIterator itor =												\
			pMessage->GetNamedFieldIterator(&XtpFieldType::m_Describe);			\
		while (!itor.IsEnd())													\
		{																		\
			itor.Retrieve(&xtpField);											\
			CopyField;															\
			FTDC_ADD_FIELD(&m_rspPackage, &ftdField);							\
			itor.Next();														\
		}																		\
		/*向客户端出出应答*/													\
		FTDC_HEADER_DEBUG(&m_rspPackage);										\
		SendToQueryFlow(pSession, &m_rspPackage);								\
	}

/**收到总线的业务通知，转发给客户端的私有流 
*@param FtdTid 转发给客户端的FTD报文的TID
*@param FtdFieldType 转发给客户端的FTD报文的业务数据域类型
*@param xtpFieldType 收到的XTP报文的业务数据域类型
*@param CopyField XTP数据域拷贝到FTD数据域的代码
*/
#define XTP_PRIVATE_FORWARD(FtdTid, FtdFieldType, XtpFieldType, CopyField)		\
	{																			\
		XtpFieldType xtpField;													\
		FtdFieldType ftdField;													\
		CNamedFieldIterator itor =												\
			pMessage->GetNamedFieldIterator(&XtpFieldType::m_Describe);			\
		while (!itor.IsEnd())													\
		{																		\
			itor.Retrieve(&xtpField);											\
			CopyField;															\
			m_rspPackage.PreparePackage(FtdTid, FTDC_CHAIN_LAST, FTD_VERSION);	\
			FTDC_ADD_FIELD(&m_rspPackage, &ftdField);							\
			int nIndex = AppendToPrivateFlow(&m_rspPackage);					\
			SendToPrivateFlow(xtpField.BrokerID, nIndex);						\
			list<CUserIDType>* pListUsers=GetUsersByInvestorID(ftdField.InvestorID); \
			if (pListUsers!=NULL)												\
			{																	\
				list<CUserIDType>::iterator it=pListUsers->begin();				\
				while(it!=pListUsers->end())									\
				{																\
					SendToUserFlow(xtpField.BrokerID,*it, nIndex);								\
					it++;														\
				}																\
			}																	\
			itor.Next();														\
		}																		\
	}

/**收到总线的业务通知，转发给客户端的私有流 
*@param FtdTid 转发给客户端的FTD报文的TID
*@param FtdFieldType 转发给客户端的FTD报文的业务数据域类型
*@param xtpFieldType 收到的XTP报文的业务数据域类型
*@param CopyField XTP数据域拷贝到FTD数据域的代码
*/
#define XTP_PRIVATE_FORWARD4T(FtdTid, FtdFieldType, XtpFieldType, CopyField)		\
	{																			\
		XtpFieldType xtpField;													\
		FtdFieldType ftdField;													\
		CNamedFieldIterator itor =												\
			pMessage->GetNamedFieldIterator(&XtpFieldType::m_Describe);			\
		while (!itor.IsEnd())													\
		{																		\
			itor.Retrieve(&xtpField);											\
			CopyField;															\
			m_rspPackage.PreparePackage(FtdTid, FTDC_CHAIN_LAST, FTD_VERSION);	\
			FTDC_ADD_FIELD(&m_rspPackage, &ftdField);							\
			int nIndex = AppendToPrivateFlow(&m_rspPackage);					\
			SendToPrivateFlow(xtpField.BrokerID, nIndex);					\
			SendToUserFlow(xtpField.OrderUserID, nIndex);						\
			itor.Next();														\
		}																		\
	}


/**收到总线的业务通知，转发给客户端的公共流 
*@param FtdTid 转发给客户端的FTD报文的TID
*@param FtdFieldType 转发给客户端的FTD报文的业务数据域类型
*@param xtpFieldType 收到的XTP报文的业务数据域类型
*@param CopyField XTP数据域拷贝到FTD数据域的代码
*/
#define XTP_PUBLIC_FORWARD(FtdTid, FtdFieldType, XtpFieldType, CopyField)		\
	{																			\
		XtpFieldType xtpField;													\
		FtdFieldType ftdField;													\
		CNamedFieldIterator itor =												\
			pMessage->GetNamedFieldIterator(&XtpFieldType::m_Describe);			\
		while (!itor.IsEnd())													\
		{																		\
			itor.Retrieve(&xtpField);											\
			m_rspPackage.PreparePackage(FtdTid, FTDC_CHAIN_LAST, FTD_VERSION);	\
			CopyField;															\
			FTDC_ADD_FIELD(&m_rspPackage, &ftdField);							\
			SendToPublicFlow(&m_rspPackage);									\
			itor.Next();														\
		}																		\
	}

/**收到客户端的查询请求，转发给查询引擎
*@param XtpTid 转发到总线上的XTP报文的TID
*@param FtdFieldType 收到的FTD报文的业务数据域类型
*@param xtpFieldType 转发到总线上的XTP报文的业务数据域类型
*@param CopyField FTD数据域拷贝到XTP数据域的代码
*/
#define FTD_QUERY_FORWARD(XtpTid, FtdFieldType, XtpFieldType, CopyField)		\
	{																			\
		FTD_PREPARE_FORWARD(XtpTid, FtdFieldType, XtpFieldType, CopyField);		\
		m_pFrontForwarder->ForwardQuery(&m_reqPackage);							\
	}

//////////////////////////////////////////////////////////////////////
CFrontFlowBroken::CFrontFlowBroken()
{
}

CFrontFlowBroken::~CFrontFlowBroken()
{
}

void CFrontFlowBroken::Clear()
{
	m_mapPrivateFlowBroken.clear();
	m_mapUserFlowBroken.clear();
	m_nPublicFlowBroken = 0;
}

void CFrontFlowBroken::RegisterDataCenter(const CDataCenterIDType &DataCenterID)
{
	m_DataCenterID = DataCenterID;
}

void CFrontFlowBroken::RegisterParticpantFlowBorken(const CBrokerIDType &BrokerID,
													int nSequenceNo)
{
	m_mapPrivateFlowBroken[BrokerID] = nSequenceNo;
}

// void CFrontFlowBroken::RegisterUserFlowBorken(const CUserIDType &UserID, int nSequenceNo)
// {
// 	m_mapUserFlowBroken[UserID] = nSequenceNo;
// }

void CFrontFlowBroken::RegisterPublicFlowBroken(int nSequenceNo)
{
	m_nPublicFlowBroken = nSequenceNo;
}

const CDataCenterIDType & CFrontFlowBroken::GetDataCenter()
{
	return m_DataCenterID;
}

int CFrontFlowBroken::GetParticpantFlowBorken(const CBrokerIDType &BrokerID)
{
	CParticipantFlowBrokenMap::iterator i = m_mapPrivateFlowBroken.find(BrokerID);
	if (i == m_mapPrivateFlowBroken.end())
	{
		return 0;
	}
	return (*i).second;
}

int CFrontFlowBroken::GetUserFlowBroken(const CBrokerIDType &BrokerID,const CUserIDType &UserID)
{
	string brokerUserID = BrokerID.getValue();
	brokerUserID += UserID;
	CUserFlowBrokenMap::iterator i = m_mapUserFlowBroken.find(brokerUserID);
	if (i == m_mapUserFlowBroken.end())
	{
		return 0;
	}
	return (*i).second;
}

int CFrontFlowBroken::GetPublicFlowBroken()
{
	return m_nPublicFlowBroken;
}



//////////////////////////////////////////////////////////////////////


//初始值
#define LampColor_White  0
//可以采样
#define LampColor_Green  1
//采样中，还没有结果采样
#define LampColor_Yellow 2
//完成结果采样
#define LampColor_Red    3
//超时取消报警秒
#define CancelRspTimeOut  10

CCalcOrderRespTime::CCalcOrderRespTime()
{
	memset(&m_nBeginTime,0,sizeof(m_nBeginTime));
	m_nLampColor=LampColor_White;
	m_CostTime=0;
}

CCalcOrderRespTime::~CCalcOrderRespTime()
{
}


void CCalcOrderRespTime::TimerFlush()
{

	if (LampColor_Green==m_nLampColor)
		return;

	//如果当前为红色/白色，则置为绿色，可以采样
	if (LampColor_Red==m_nLampColor || LampColor_White==m_nLampColor)
		m_nLampColor=LampColor_Green;

	//如果为黄色表示结果采样未得,需要计算是否输出日志
	if (LampColor_Yellow==m_nLampColor)
	{
		time_t nCurrTime;
		time(&nCurrTime);

#ifndef  WIN32
		int inter=nCurrTime-m_nBeginTime.tv_sec;
#else
		int inter=nCurrTime-m_nBeginTime.time;
#endif
		if (inter >2)
		{
			REPORT_EVENT(LOG_CRITICAL, "LoopTime", "Timeout=[%d]second UserID=[%s] UserOrderLocalID=[%s] ", \
				inter,m_UserID.getValue(),m_OrderLocalID.getValue());
		}
		if (inter >CancelRspTimeOut)
		{
			m_nLampColor=LampColor_Green;
		}
	}
}

void CCalcOrderRespTime::InputSample(CUserOrderLocalIDType &OrderLocalID,CUserIDType &UserID)
{
#ifndef  WIN32
	gettimeofday(&m_nBeginTime, NULL);
#else
	_ftime( &m_nBeginTime );
#endif
	m_OrderLocalID=OrderLocalID;
	m_UserID=UserID;

	m_nLampColor=LampColor_Yellow;
}

void CCalcOrderRespTime::InputResult(COrderSysIDType &OrderSysID,CUserOrderLocalIDType &OrderLocalID,CUserIDType &UserID,CBusinessUnitType& ExternalLatency)
{
	if (OrderLocalID==m_OrderLocalID && UserID==m_UserID)
	{
		int nExternalLatency=atoi(ExternalLatency);
		int nInnerLat=0;
#ifndef  WIN32
		//计算响应时间
		struct timeval timeout;
		//20140822 by wangwei
//		memset(&timeout,0,sizeof(timeout));
		gettimeofday(&timeout, NULL);
		m_CostTime=(timeout.tv_sec-m_nBeginTime.tv_sec)*1000000+timeout.tv_usec-m_nBeginTime.tv_usec;
		nInnerLat=m_CostTime-nExternalLatency;
#else
		struct _timeb timeout;
		_ftime( &timeout );
		m_CostTime=(timeout.time-m_nBeginTime.time)*1000+timeout.millitm-m_nBeginTime.millitm;
		nInnerLat=m_CostTime-(nExternalLatency/1000);
#endif
		m_nLampColor=LampColor_Red;
		//输出订单响应日志
		//REPORT_EVENT(LOG_WARNING, "LoopTime", "TotalOrderLoopTime=%d us,InnerLoopTime=%d us",m_CostTime,nInnerLat);
		//将本地报单号和用户代码打印到日志中 liumeng 20141117	
		REPORT_EVENT(LOG_WARNING, "LoopTime", "TotalOrderLoopTime=%d us,InnerLoopTime=%d us, OrderSysID = %s, UserOrderLocalID= %s, UserID= %s ",m_CostTime,nInnerLat,OrderSysID.getValue(),OrderLocalID.getValue(),UserID.getValue());		
	}
	else
		return;
}

void CCalcOrderRespTime::InputResult(COrderSysIDType &OrderSysID,CUserOrderLocalIDType &OrderLocalID,CUserIDType &UserID)
{
	if (OrderLocalID==m_OrderLocalID && UserID==m_UserID)
	{
#ifndef  WIN32
		//计算响应时间
		struct timeval timeout;
		memset(&timeout,0,sizeof(timeout));
		gettimeofday(&timeout, NULL);
		m_CostTime=(timeout.tv_sec-m_nBeginTime.tv_sec)*1000000+timeout.tv_usec-m_nBeginTime.tv_usec;
#else
		struct _timeb timeout;
		_ftime( &timeout );
		m_CostTime=(timeout.time-m_nBeginTime.time)*1000+timeout.millitm-m_nBeginTime.millitm;
#endif
		m_nLampColor=LampColor_Red;
		//输出订单响应日志
		//REPORT_EVENT(LOG_WARNING, "LoopTime", "OrderLoopTime=%d us",m_CostTime);
		//将本地报单号和用户代码打印到日志中 liumeng 20141117
		REPORT_EVENT(LOG_WARNING, "LoopTime", "OrderLoopTime=%d us, OrderSysID = %s, UserOrderLocalID= %s, UserID= %s ",m_CostTime,OrderSysID.getValue(),OrderLocalID.getValue(),UserID.getValue());
	}
	else
		return;
}
bool CCalcOrderRespTime::IsCanCatch()
{
	if (m_nLampColor==LampColor_Green)
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define ORDER_RSPTIME_TIMER_ID  10
#define ORDER_RSPTIME_INTERVAL	1000

CFtdEngine::CFtdEngine(CReactor *pReactor, CFrontForwarder *pFrontForwarder,
					   const char *pszFlowPath,CFlow* pSlogResult,CSelectReactor* pConnReactor)
:CFrontEngine(pReactor, pFrontForwarder, pszFlowPath,pConnReactor)
{
//	m_DataCenterID = 0;
	m_rspPackage.ConstructAllocate(FTDC_PACKAGE_MAX_SIZE, 1000);
	//写slog非常影响性能，by wangwei ,20130110
 	//OpenChannelLogFile(m_strFlowPathName.c_str()); 
	SetLogFlow(pSlogResult);
	
//	SetTimer(ORDER_RSPTIME_TIMER_ID, ORDER_RSPTIME_INTERVAL);
}

CFtdEngine::~CFtdEngine()
{
	CUserFlowMap::iterator pfitor = m_mapUserFlow.begin();
	while (pfitor != m_mapUserFlow.end())
	{
		delete pfitor->second;
		pfitor ++;
	}
	m_mapUserFlow.clear();
	m_InvestorUserMap.clear();
}

//Add by zbz 订单响应时间采集的定时器
void CFtdEngine::OnTimer(int nIDEvent)
{
	CFrontEngine::OnTimer(nIDEvent);
	if (nIDEvent == ORDER_RSPTIME_TIMER_ID)
	{
		m_CalcOrderRespTime.TimerFlush();
	}
}

CSession *CFtdEngine::CreateSession(CChannel *pChannel, DWORD)
{
	CFTDCSession *pSession =  new CFTDCSession(m_pReactor, pChannel);
	pSession->RegisterPackageHandler(this);

	pSession->SetCompressMethod(CRPCM_ZERO);		//设置压缩算法
	pSession->SetHeartbeatMode(XMPHBT_SLAVE_MODE);

	return pSession;
}

void CFtdEngine::OnSessionDisconnected(CSession *pSession, int nReason)
{
	m_mapDisseminationInfo.Erase(pSession->GetSessionID());

	CFrontEngine::OnSessionDisconnected(pSession, nReason);
}

bool CFtdEngine::HandleNotify(CXTPPackage *pMessage)
{
	switch(pMessage->GetTid()) {
	case TID_InitUserInvestor:
		{
			CUserInvestorField field;
			CNamedFieldIterator it = pMessage->GetNamedFieldIterator(&field.m_Describe);
			while(!it.IsEnd())
			{			
				it.Retrieve(&field);
				CInvestorUserMap::iterator iter=m_InvestorUserMap.find(field.InvestorID);
				if (iter!=m_InvestorUserMap.end())
				{	
					iter->second->push_back(field.UserID);
				}
				else
				{
					list<CUserIDType>* pList=new list<CUserIDType>();
					pList->push_back(field.UserID);
					m_InvestorUserMap.insert(CInvestorUserMap::value_type(field.InvestorID,pList));
				}
				it.Next();
			}	
		}
		break;
	case TID_NtfLifeCycle:
		OnNtfSwitch(pMessage);
		break;
	case TID_NtfDelUserSession:
		{
			OnNtfDelUserSession(pMessage);
			break;
		}
	case TID_NtfOrder:
		XTP_PRIVATE_FORWARD(FTD_TID_RtnOrder, CFTDOrderField, COrderField,
		{
			CopyAPIOrderEntity(&ftdField, &xtpField);
		});
		break;
	case TID_NtfTrade:
		XTP_PRIVATE_FORWARD(FTD_TID_RtnTrade, CFTDTradeField, CTradeField,
		{
			CopyAPITradeEntity(&ftdField, &xtpField);
		});
		break;
	case TID_NtfInstrumentStatusUpdate:
		XTP_PUBLIC_FORWARD(FTD_TID_RtnInstrumentStatus, CFTDInstrumentStatusField, CInstrumentStatusField,
		{
			CopyAPIInstrumentEntity(&ftdField, &xtpField);
		});
		break;
	//by cc, 20130829
	case TID_NtfInvestorAccountDeposit:
		XTP_PRIVATE_FORWARD(FTD_TID_RtnInvestorAccountDeposit, CFTDInvestorAccountDepositResField, CInvestorAccountDepositNtfField,
		{
			CopyAPIInvestorAccountDepositResEntity(&ftdField, &xtpField);

		});
		break;
		//by cgm, 20150820
	case TID_NtfMessageNotify:
		XTP_PRIVATE_FORWARD(FTD_TID_RtnMessageNotify, CFTDMessageNotifyInfoField, CMessageNotifyInfoField,
		{
			CopyAPIMessageNotifyInfoEntity(&ftdField, &xtpField);
		});
		break;
	case TID_NtfSGEDeferRate://金交所递延费率通知
		XTP_PUBLIC_FORWARD(FTD_TID_RtnSGEDeferRate, CFTDSGEDeferRateField, CSGEDeferRateField,
		{
			CopySGEDeferRateEntity(&ftdField, &xtpField);
		});
		break;
	default:
		return false;
	}
	//NET_IO_LOG0("CFtdEngine::HandleNotify\n");
	//by wangwei,影响效率
	//20130116
// 	XTP_PACKAGE_DEBUG(pMessage);
	
	return true;
}

bool CFtdEngine::HandleResponse(CXTPPackage *pMessage)
{
	CFTDCSession *pSession = NULL;

	if (pMessage->GetFrontID() == m_pFrontForwarder->GetFrontID())
	{
		pSession = (CFTDCSession *)GetSession(pMessage->GetSessionID());
	}
	
	switch(pMessage->GetTid())
	{
	case TID_RspUserLogin:
		OnUserLoginRsp(pMessage, pSession);
		break;
	case TID_RspUserLogout:
		OnUserLogoutRsp(pMessage, pSession);
		break;
	case TID_RspOrderInsert:
		{		
			XTP_RSP_FORWARD(FTD_TID_RspOrderInsert,CFTDInputOrderField, CInputOrderField,
			{
				PrintDelayLog(xtpField);
				CopyAPIInputOrderEntity(&ftdField, &xtpField);
			});
			break;
		}
	case TID_RspOrderAction:
		XTP_RSP_FORWARD(FTD_TID_RspOrderAction,CFTDOrderActionField, COrderActionField,
		{
			CopyAPIOrderActionEntity(&ftdField, &xtpField);
			ftdField.LimitPrice=0.0; \
				ftdField.VolumeChange=0; \
		});
		break;
	case TID_RspUserPasswordUpdate:
		XTP_RSP_FORWARD(FTD_TID_RspUserPasswordUpdate, CFTDUserPasswordUpdateField, CUserPasswordUpdateField,
		{
			CopyUserPasswordUpdateEntity(&ftdField, &xtpField);
		});
		break;
	case TID_RspForceUserExit:
		XTP_RSP_FORWARD(FTD_TID_RspForceUserExit, CFTDForceUserExitField, CForceUserExitField,
		{
			CopyForceUserExitEntity(&ftdField, &xtpField);
		});
		break;
	case TID_RspForceUserLogout:
		XTP_RSP_FORWARD(FTD_TID_RspForceUserLogout, CFTDForceUserExitField, CForceUserExitField,
		{
			CopyForceUserExitEntity(&ftdField, &xtpField);
		});
		break;
	case TID_RspAccountDeposit:
		XTP_RSP_FORWARD(FTD_TID_RspAccountDeposit, CFTDRspAccountDepositField, CAccountDepositResField,
		{
			CopyAPIInvestorAccountDepositResEntity(&ftdField, &xtpField);
		});
		break;
	case TID_RspError:
		XTP_RSP_FORWARD(FTD_TID_RspError, CFTDRspInfoField, CRspInfoField,
		{
			CopyErrorTypeEntity(&ftdField, &xtpField);
		});
		break;
		//add by jinpc 20170112
	case TID_RspQryMBLMarketData:
		XTP_RSP_FORWARD(FTD_TID_RspQryMBLMarketData, CFTDMBLMarketDataField, CMBLMarketDataField,
		{
			CopyMBLMarketDataEntity(&ftdField, &xtpField);
		});
		break;
	default:
		return false;
	}
	//NET_IO_LOG0("CFtdEngine::HandleMessage\n");
// 	XTP_PACKAGE_DEBUG(pMessage);	

	return true;
}

void CFtdEngine::HandleMessage(CXTPPackage *pMessage)
{
	if (!HandleNotify(pMessage))
	{
		HandleResponse(pMessage);
	}
}

void CFtdEngine::OnResponse(CXTPPackage *pMessage)
{
	XTP_PACKAGE_DEBUG(pMessage);
	CFTDCSession *pSession = (CFTDCSession *)GetSession(pMessage->GetSessionID());
	if (pSession == NULL)
	{
		return;
	}
	
	switch(pMessage->GetTid()) {
		case TID_RspQryOrder:
		XTP_QRY_FORWARD(FTD_TID_RspQryOrder, CFTDOrderField, COrderField,
		{
			CopyAPIOrderEntity(&ftdField, &xtpField);
		});
		break;
	case TID_RspQryTrade:
		XTP_QRY_FORWARD(FTD_TID_RspQryTrade, CFTDTradeField, CTradeField,
		{
			CopyAPITradeEntity(&ftdField, &xtpField);
		});
		break;
	//可用投资者应答
	case TID_RspQryUserInvestor:
		XTP_QRY_FORWARD(FTD_TID_RspQryUserInvestor, CFTDRspUserInvestorField, CUserInvestorField,
		{
			CopyAPIUserInvestorEntity(&ftdField, &xtpField);
		});
		break;
	//投资者账户查询
	case TID_RspQryInvestorAccount:
		XTP_QRY_FORWARD(FTD_TID_RspQryInvestorAccount, CFTDRspInvestorAccountField, CInvestorAccountField,
		{
			CopyAPIInvestorAccountEntity(&ftdField, &xtpField);
		});
		break;
	
	case TID_RspQryInstrument:
		XTP_QRY_FORWARD(FTD_TID_RspQryInstrument, CFTDRspInstrumentField, CInstrumentField,
		{
			CopyAPIInstrumentEntity(&ftdField, &xtpField);
		});
		break;

	case TID_RspQryMarketData:
		XTP_QRY_FORWARD(FTD_TID_RspQryMarketData, CFTDMarketDataField, CMarketDataField,
		{
			CopyMarketDataEntity(&ftdField, &xtpField);
		});
		break;
		
	//交易所查询
	case TID_RspQryExchange:
		XTP_QRY_FORWARD(FTD_TID_RspQryExchange, CFTDRspExchangeField, CRspExchangeField,
		{
			CopyAPIExchangeEntity(&ftdField, &xtpField);
		});
		break;
		
	//投资者持仓查询
	case TID_RspQryInvestorPosition:
		XTP_QRY_FORWARD(FTD_TID_RspQryInvestorPosition, CFTDRspInvestorPositionField, CInvestorPositionField,
		{
			CopyAPIInvestorPositionEntity(&ftdField, &xtpField);
		});
		break;
	
	//手续费率查询
	case TID_RspQryInvestorFee:
		XTP_QRY_FORWARD(FTD_TID_RspQryInvestorFee, CFTDInvestorFeeField, CInvestorFeeField,
		{
			CopyAPIInvestorFeeEntity(&ftdField, &xtpField);
		});
		break;
		
	//手续费率查询
	case TID_RspQryInvestorMargin:
		XTP_QRY_FORWARD(FTD_TID_RspQryInvestorMargin, CFTDInvestorMarginField, CInvestorMarginField,
		{
			CopyAPIInvestorMarginEntity(&ftdField, &xtpField);
		});
		break;
	//金交所递延费率查询
	case TID_RspQrySGEDeferRate:
		XTP_QRY_FORWARD(FTD_TID_RspQrySGEDeferRate, CFTDSGEDeferRateField, CSGEDeferRateField,
		{
			CopySGEDeferRateEntity(&ftdField, &xtpField);
		});
		break;
	//客户期权手续费率查询应答
	case TID_RspQryInvestorOptionFee:
		{
			XTP_QRY_FORWARD(FTD_TID_RspQryInvestorOptionFee, CFTDRspInvestorOptionFeeField, CInvestorOptionFeeField,
			{
				CopyInvestorOptionFeeEntity(&ftdField, &xtpField);
			});
		}
		break;
	default:
		break;
	}
	
}

int CFtdEngine::HandlePackage(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession)
{
	//NET_IO_LOG0("CFtdEngine::HandlePackage\n");
//	FTDC_PACKAGE_DEBUG(pFTDCPackage);
	CUserIDType	UserID;
	CBrokerIDType	BrokerID;
	if (pFTDCPackage->GetTID() != FTD_TID_ReqUserLogin)
	{
		if (!IsSessionLogin(pSession->GetSessionID()))
		{
			SendErrorRsp(pFTDCPackage, pSession, 1, "Not Login");
			return 0;
		}
		
	}
	GetSessionOwner(pSession->GetSessionID(), UserID, BrokerID);
	//没有流控，暂时取消该代码
// 	CalcFlux(pSession, pFTDCPackage->Length());	//统计流量

	int nRet = 0;
	
	switch(pFTDCPackage->GetTID()) {
	case FTD_TID_ReqOrderInsert:
		{
			m_reqPackage.PreparePublish(TID_ReqOrderInsert);
			m_reqPackage.SetFrontID(m_pFrontForwarder->GetFrontID());
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
			if (g_bLatencyOut)
			{
				long FtdRecDown;
				InputLong(FtdRecDown);
				m_reqPackage.SetGroupID(FtdRecDown);
			}
			m_reqPackage.AddField(&(CInputOrderField::m_Describe),pFTDCPackage->Address()+sizeof(TFieldHeader));
			m_pFrontForwarder->ForwardTransaction(&m_reqPackage);
		}
		break;
	case FTD_TID_ReqOrderAction:		
		FTD_REQ_FORWARD(TID_ReqOrderAction, CFTDOrderActionField, COrderActionField,
		{
			CopyAPIOrderActionEntity(&xtpField, &ftdField);
			xtpField.UserID=UserID;
			xtpField.BrokerID=BrokerID;
		});
		break;
		//新增，为了内存数据库的导出
		//by wangwei,20130114
	case FTD_TID_ReqDumpMemDb:
		{
			DumpDelayLog();
			m_reqPackage.PreparePublish(TID_ReqDumpMemDb);
			m_reqPackage.SetFrontID(m_pFrontForwarder->GetFrontID());
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
			m_reqPackage.AddField(&(CMemDbField::m_Describe),pFTDCPackage->Address()+sizeof(TFieldHeader));
			m_pFrontForwarder->ForwardTransaction(&m_reqPackage);
			
			m_reqPackage.PreparePublish(TID_ReqDumpMemDb);
			m_reqPackage.SetFrontID(m_pFrontForwarder->GetFrontID());
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
			m_reqPackage.AddField(&(CMemDbField::m_Describe),pFTDCPackage->Address()+sizeof(TFieldHeader));
			m_pFrontForwarder->ForwardQuery(&m_reqPackage);
		}
		break;
	case FTD_TID_ReqUserLogin:
		///xuzh：20070608：检查过高版本的API将被禁止登录
	/*	if (pFTDCPackage->GetVersion()>FTD_VERSION)
		{
			SendErrorRsp(pFTDCPackage, pSession, 1, "Too High FTD Version");
			return 0;
		}*/
		nRet = OnReqUserLogin(pFTDCPackage, (CFTDCSession *)pSession);
//		FTDRequestIndex.incValue();
		break;
	case FTD_TID_ReqSubscribeTopic:
		nRet = OnReqSubscribeTopic(pFTDCPackage, (CFTDCSession *)pSession);
//		FTDRequestIndex.incValue();
		break;	
	case FTD_TID_ReqUserLogout:
		FTD_REQ_FORWARD(TID_ReqUserLogout, CFTDRspUserLogoutField, CUserLogoutField,
		{
			CopyAPIUserLogoutEntity(&xtpField, &ftdField);
		});
		break;
	case FTD_TID_ReqUserPasswordUpdate:
		FTD_REQ_FORWARD(TID_ReqUserPasswordUpdate, CFTDUserPasswordUpdateField, CUserPasswordUpdateField,
		{
			CopyUserPasswordUpdateEntity(&xtpField, &ftdField);
		});
		break;
	case FTD_TID_ReqForceUserExit:
		FTD_REQ_FORWARD(TID_ReqForceUserExit, CFTDForceUserExitField, CForceUserExitField,
		{
			CopyForceUserExitEntity(&xtpField, &ftdField);
		});
		break;
	case FTD_TID_ReqForceUserLogout:
		FTD_REQ_FORWARD(TID_ReqForceUserLogout, CFTDForceUserExitField, CForceUserExitField,
		{
			CopyForceUserExitEntity(&xtpField, &ftdField);
		});
		break;
	case FTD_TID_ReqQryOrder:			
			FTD_QUERY_FORWARD(TID_ReqQryOrder, CFTDQryOrderField, CQryOrderField,
			{
				CopyAPIQryOrderEntity(&xtpField, &ftdField);
				xtpField.LogUserID=UserID;
				xtpField.LogBrokerID=BrokerID;
			});
		break;
	case FTD_TID_ReqQryTrade:		
		FTD_QUERY_FORWARD(TID_ReqQryTrade, CFTDQryTradeField, CQryTradeField,
		{
			CopyAPIQryTradeEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
		});
		
		break;
	//可用投资者查询
	case FTD_TID_ReqQryUserInvestor:
		FTD_QUERY_FORWARD(TID_ReqQryUserInvestor, CFTDQryUserInvestorField, CQryUserInvestorField,
		{
			CopyAPIQryUserInvestorEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
		});
		break;
	//投资者账户查询
	case FTD_TID_ReqQryInvestorAccount:	
		FTD_QUERY_FORWARD(TID_ReqQryInvestorAccount, CFTDQryInvestorAccountField, CQryInvestorAccountField,
		{
			CopyAPIQryInvestorAccountEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
		});
		break;
	case FTD_TID_ReqQryInstrument:
		FTD_QUERY_FORWARD(TID_ReqQryInstrument, CFTDQryInstrumentField, CQryInstrumentField,
		{
			CopyAPIQryInstrumentEntity(&xtpField, &ftdField);
		});
		break;
	case FTD_TID_ReqQryMarketData:
		FTD_QUERY_FORWARD(TID_ReqQryMarketData, CFTDQryMarketDataField, CQryMarketDataField,
		{
			CopyAPIQryMarketDataEntity(&xtpField, &ftdField);
		});
		break;
	//交易所查询
	case FTD_TID_ReqQryExchange :
		FTD_QUERY_FORWARD(TID_ReqQryExchange, CFTDQryExchangeField, CQryExchangeField,
		{
			CopyAPIQryExchangeEntity(&xtpField, &ftdField);
		});
		break;
	//投资者持仓查询
	case FTD_TID_ReqQryInvestorPosition:
		FTD_QUERY_FORWARD(TID_ReqQryInvestorPosition, CFTDQryInvestorPositionField, CQryInvestorPositionField,
		{
			CopyAPIQryInvestorPositionEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
		});
		break;
/*		case FTD_TID_ReqQryUser:
		FTD_QUERY_FORWARD(TID_ReqQryUser, CFTDQryUserField, CQryUserField,
		{
			//CopyQryUserEntity(&xtpField, &ftdField);
		});
		break;
*/
	case FTD_TID_ReqQryTopic:
		nRet = OnReqQryTopic(pFTDCPackage, pSession);
		break;
			
	case FTD_TID_ReqQryInvestorFee:
		FTD_QUERY_FORWARD(TID_ReqQryInvestorFee, CFTDQryInvestorFeeField, CQryInvestorFeeField,
		{
			CopyAPIQryInvestorFeeEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
		});
		break;
	case FTD_TID_ReqQryInvestorMargin:
		FTD_QUERY_FORWARD(TID_ReqQryInvestorMargin, CFTDQryInvestorMarginField, CQryInvestorMarginField,
		{
			CopyAPIQryInvestorMarginEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
		});
		break;
	//add by cgm 在userapi加入投资者出入金
	case FTD_TID_ReqAccountDeposit:
		FTD_REQ_FORWARD(TID_DbInvestorAccountDeposit, CFTDReqAccountDepositField, CDbmtInvestorAccountDepositField,
		{
			CopyInvestorAccountDepositEntity(&xtpField, &ftdField);
		});
		break;
		//金交所递延费率查询
	case FTD_TID_ReqQrySGEDeferRate:
		FTD_QUERY_FORWARD(TID_ReqQrySGEDeferRate, CFTDQrySGEDeferRateField, CQrySGEDeferRateField,
		{
			CopyQrySGEDeferRateEntity(&xtpField, &ftdField);
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
		});
		break;
		//分价查询
	case FTD_TID_ReqQryMBLMarketData:
		FTD_REQ_FORWARD(TID_ReqQryMBLMarketData, CFTDQryMBLMarketDataField, CQryMBLMarketDataField,
		{
			CopyQryMBLMarketDataEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
		});
		break;
		//期权手续费率查询
	case FTD_TID_ReqQryInvestorOptionFee:
		FTD_QUERY_FORWARD(TID_ReqQryInvestorOptionFee, CFTDQryInvestorOptionFeeField, CQryInvestorOptionFeeField,
		{
			CopyAPIQryInvestorOptionFeeEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
		});
		break;
	default:
		SendErrorRsp(pFTDCPackage, pSession, 1, "Unrecognized ftd tid");
		break;
	}
	
	return nRet;
}

void CFtdEngine::SendErrorRsp(CFTDCPackage *pRequest, CFTDCSession *pSession, 
							  const int nErrorCode, const char *pszErrorMsg)
{
	
	CFTDRspInfoField ftdRspInfoField;
	ftdRspInfoField.ErrorID = nErrorCode;
	ftdRspInfoField.ErrorMsg = pszErrorMsg;
	m_rspPackage.PrepareResponse(pRequest, FTD_TID_RspError, FTDC_CHAIN_LAST, FTD_VERSION);
	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);
	SendToDialogFlow(pSession, &m_rspPackage);	
	
}

void CFtdEngine::OnNtfCommPhaseChange(CXTPPackage *pMessage)
{
	/*
	CCommPhaseField CommPhaseField;
	XTP_GET_SINGLE_FIELD(pMessage, &CommPhaseField);
	CloseChannelLogFile();
	DisconnectAll(0);
	ClearAllMap();
	m_pPrivateFlow->SetCommPhaseNo(CommPhaseField.CommPhaseNo);
	m_pFrontForwarder->SetCommPhaseNo(CommPhaseField.CommPhaseNo);
	OpenChannelLogFile(m_strFlowPathName.c_str());
	m_TradingDay = CommPhaseField.TradingDay;
	*/
}


void CFtdEngine::OnNtfSwitch(CXTPPackage *pMessage)
{
	printf("recv switch datacenter ntf\n");
	REPORT_EVENT(LOG_INFO, "SWITCH", "receive switch notify message tid=[0x%08x] connected",pMessage->GetTid());
	//收到切换通知后，激活监听端口号
	EnableListener(true);
}


int CFtdEngine::OnReqUserLogin(CFTDCPackage *pPackage, CFTDCSession *pSession)
{
	CFTDReqUserLoginField ftdReqUserLoginField;
	memset(&ftdReqUserLoginField, 0, sizeof(ftdReqUserLoginField));
	if(FTDC_GET_SINGLE_FIELD(pPackage, &ftdReqUserLoginField) <= 0)
	{
		//没有取到登录请求域，断开连接
		pSession->Disconnect(MSG_FTDCERR_BADPACKAGE);
		return -1;
	}
	char *pszCommonName = pSession->GetChannel()->GetRemoteCommonName();
	if (pszCommonName != NULL && strcmp(pszCommonName, ftdReqUserLoginField.UserID) != 0)
	{
		//用户名和证书中的不一致
		pSession->Disconnect(MSG_SSLERR_INVALID_USERID);
		return -1;
	}
	
	if (m_strInterfaceMax.compare("") != 0 && 
		m_strInterfaceMax.compare(ftdReqUserLoginField.InterfaceProductInfo) < 0 ||
		m_strInterfaceMin.compare("") != 0 &&
		m_strInterfaceMin.compare(ftdReqUserLoginField.InterfaceProductInfo) > 0 )
	{
		SendErrorRsp(pPackage, pSession, 1, "Invalid interface product info");
		return 0;
	}

	//将客户端的订阅信息缓存起来，供登录成功后使用
	TFtdeDisseminationInfo DisseminationInfo;
	memset(&DisseminationInfo, 0, sizeof(DisseminationInfo));
	DisseminationInfo.nSessionID = pSession->GetSessionID();
	DisseminationInfo.TradingDay = ftdReqUserLoginField.TradingDay;
	if(pPackage->GetVersion() >= 4)
	{
		DisseminationInfo.DataCenterID = ftdReqUserLoginField.DataCenterID;
	}
	
	CFTDDisseminationField ftdDisseminationField;
	CNamedFieldIterator dfIterator = pPackage->GetNamedFieldIterator(
		&CFTDDisseminationField::m_Describe);
	for(int i=0; i<FTDE_MAX_SEQUENCE_SERIES && !dfIterator.IsEnd(); i++)
	{
		dfIterator.Retrieve(&ftdDisseminationField);
		DisseminationInfo.Fields[DisseminationInfo.nFieldCount].nSubStartId = 
			ftdDisseminationField.SequenceNo;
		DisseminationInfo.Fields[DisseminationInfo.nFieldCount].wSequenceSeries = 
			ftdDisseminationField.SequenceSeries;
		DisseminationInfo.nFieldCount++;
		dfIterator.Next();
	}

	if (DisseminationInfo.nFieldCount > 0)
	{
		m_mapDisseminationInfo.Insert(DisseminationInfo.nSessionID, DisseminationInfo);
	}
	
	//转换报文，发往交易引擎
	m_pFrontForwarder->PrepareForward(&m_reqPackage, TID_ReqUserLogin,
		pSession->GetSessionID(), pPackage->GetRequestId());

	CUserLoginField userLoginField;
	userLoginField.IPAddress = pSession->GetChannel()->GetRemoteName();
	userLoginField.MaxOrderLocalID = 0;
	userLoginField.LoginTime = "";
	userLoginField.TradingSystemName = "";

	CopyLoginBaseEntity(&userLoginField,&ftdReqUserLoginField);
	///-----
	///	xuzh，20060223：该用真实的协议中的版本号，而非自己申报的版本号
	///-----
	char buffer[sizeof(CProtocolInfoType)];
	sprintf(buffer,"FTD %d",pPackage->GetVersion());
	userLoginField.ProtocolInfo=buffer;

	XTP_ADD_FIELD(&m_reqPackage, &userLoginField);
	
	m_pFrontForwarder->ForwardTransaction(&m_reqPackage);
	
	//保存本会话的版本
	pSession->SetVersion(pPackage->GetVersion());
	return 0;
}

void CFtdEngine::OnUserLoginRsp(CXTPPackage *pMessage, CFTDCSession *pSession)
{
	if (pSession == NULL)
	{
		return;
	}
	m_rspPackage.PreparePackage(FTD_TID_RspUserLogin, FTDC_CHAIN_LAST, FTD_VERSION);
	m_rspPackage.SetRequestId(pMessage->GetRequestID());

	CRspInfoField rspInfoField;
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		//没有取到响应信息
		return ;
	}
	CFTDRspInfoField ftdRspInfoField;
	CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);

	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);
	
	CUserLoginField userLoginField;
	if(XTP_GET_SINGLE_FIELD(pMessage, &userLoginField) <= 0)
	{
		//没有取到登录域
		return ;
	}
	//组织FTDC报文的登录应答域
	
	CFTDRspUserLoginField ftdRspUserLoginField;
	memset(&ftdRspUserLoginField, 0, sizeof(CFTDRspUserLoginField));
	ftdRspUserLoginField.MaxOrderLocalID = userLoginField.MaxOrderLocalID;
	ftdRspUserLoginField.TradingDay = userLoginField.TradingDay;
	ftdRspUserLoginField.LoginTime = userLoginField.LoginTime;
	ftdRspUserLoginField.UserID = userLoginField.UserID;
	ftdRspUserLoginField.TradingSystemName = userLoginField.TradingSystemName;
	ftdRspUserLoginField.BrokerID=userLoginField.BrokerID;
	ftdRspUserLoginField.SessionID=userLoginField.SessionID;
	ftdRspUserLoginField.FrontID=userLoginField.FrontID;

	m_TradingDay=userLoginField.TradingDay;
//	ftdRspUserLoginField.DataCenterID = m_DataCenterID;
	if (rspInfoField.ErrorID == 0)		//登录成功
	{
		CReadOnlyFlow *pPrivateFlow =  GetPrivateFlow(userLoginField.BrokerID);
		CReadOnlyFlow *pUserFlow = GetUserFlow(userLoginField.BrokerID,userLoginField.UserID);
		ftdRspUserLoginField.PrivateFlowSize = pPrivateFlow->GetCount();
		ftdRspUserLoginField.UserFlowSize = pUserFlow->GetCount();
	}
	
	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspUserLoginField);
	
	//走对话流会导致登录应答后到，这里直接发送
	pSession->SendRequestPackage(&m_rspPackage);
	if (rspInfoField.ErrorID != 0)		//登录不成功
	{
		return;
	}
	//设定会话的身份
	SetSessionOwner(pSession->GetSessionID(), userLoginField.UserID, userLoginField.BrokerID);
	SetSessionOwnerType(pSession->GetSessionID(), userLoginField.UserType);
	SetSessionMaxCommFlux(pSession->GetSessionID(), userLoginField.MaxCommFlux);

	CFTDDisseminationField fieldDissemination;
	//根据缓存的订阅信息，构造发分发域，发给客户端，并发布相应的流
	TFtdeDisseminationInfo *pFind = m_mapDisseminationInfo.Find(pSession->GetSessionID());
	if (pFind == NULL)	//没找到缓存的订阅信息
	{
		return;
	}
	m_rspPackage.PreparePackage(FTD_TID_IntlRtnDissemination, FTDC_CHAIN_LAST, FTD_VERSION);
	int i = 0;
	for (i=0; i<pFind->nFieldCount; i++)
	{
		//如果客户端的交易日与交易引擎不符，则从0开始订阅
		if (pFind->TradingDay != m_TradingDay && 
			 pFind->Fields[i].nSubStartId != -1)
		{
			 pFind->Fields[i].nSubStartId = 0;
		}
		
		//by wangwei, 20121221
		PublishFlow(pSession,  pFind->Fields[i].wSequenceSeries,pFind->Fields[i].nSubStartId, pFind->Fields[i].nPubStartId,false);
		
		fieldDissemination.SequenceNo = pFind->Fields[i].nPubStartId;
		fieldDissemination.SequenceSeries = pFind->Fields[i].wSequenceSeries;
		FTDC_ADD_FIELD(&m_rspPackage, &fieldDissemination);
	}
	//直接发送分发信息通知
	pSession->SendRequestPackage(&m_rspPackage);
	//by wangwei ,不再有数据流回退通知
/*	
	//发送数据流回退应答
	m_rspPackage.PreparePackage(FTD_TID_RtnFlowMessageCancel, FTDC_CHAIN_LAST, FTD_VERSION);
	CFTDFlowMessageCancelField fieldFlowMessageCancel;
	for (i=0; i<pFind->nFieldCount; i++)
	{
		if (pFind->Fields[i].nSubStartId > pFind->Fields[i].nPubStartId)
		{
			fieldFlowMessageCancel.DataCenterID = pFind->DataCenterID;
			fieldFlowMessageCancel.StartSequenceNo = pFind->Fields[i].nPubStartId;
			fieldFlowMessageCancel.EndSequenceNo = pFind->Fields[i].nSubStartId;
			fieldFlowMessageCancel.SequenceSeries = pFind->Fields[i].wSequenceSeries;
			fieldFlowMessageCancel.TradingDay = pFind->TradingDay;
			FTDC_ADD_FIELD(&m_rspPackage, &fieldFlowMessageCancel);
		}
	}
	if (m_rspPackage.Length() > 0)
	{
		pSession->SendRequestPackage(&m_rspPackage);
	}
*/	
}

void CFtdEngine::OnUserLogoutRsp(CXTPPackage *pMessage, CFTDCSession *pSession)
{
	
	if (pSession == NULL)
	{
		return;
	}
	m_rspPackage.PreparePackage(FTD_TID_RspUserLogout, FTDC_CHAIN_LAST, FTD_VERSION);
	m_rspPackage.SetRequestId(pMessage->GetRequestID());

	CRspInfoField rspInfoField;
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		//没有取到响应信息
		return ;
	}
	CFTDRspInfoField ftdRspInfoField;
	CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);
	
	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);
	
	if (rspInfoField.ErrorID == 0)		//登出成功
	{
		ClearSessionOwner(pSession->GetSessionID());

		CUserLogoutField userLogoutField;
		if(XTP_GET_SINGLE_FIELD(pMessage, &userLogoutField) <= 0)
		{
			//没有取到登出域
			return ;
		}
		//组织FTDC报文的登出应答域
		CFTDRspUserLogoutField ftdRspUserLogoutField;
		ftdRspUserLogoutField.UserID = userLogoutField.UserID;
		ftdRspUserLogoutField.UserID = userLogoutField.UserID;
		
		FTDC_ADD_FIELD(&m_rspPackage, &ftdRspUserLogoutField);
	}

	//向客户端出出应答
	SendToDialogFlow(pSession, &m_rspPackage);
	
}

void CFtdEngine::OnNtfDelUserSession(CXTPPackage *pMessage)
{
	//需要重写 wangwei 	
	CUserSessionField fieldUserSession;
	if(XTP_GET_SINGLE_FIELD(pMessage, &fieldUserSession) <= 0)
	{
		//没有取到会话域
		return ;
	}
/*
	if (fieldUserSession.FrontID != m_pFrontForwarder->GetFrontID())
	{
		//不是给自已的，什么也不做
		return;
	}
*/
	CSession *pSession = GetSession(fieldUserSession.SessionID);
	if (pSession == NULL)
	{
		//会话已经没有了，什么也不做
		return;
	}
	pSession->Disconnect(0);
	
}

CIndexPackageFlow *CFtdEngine::GetUserFlow(const CBrokerIDType &brokerID,const CUserIDType &userID)
{	
	CIndexPackageFlow *pFlow = NULL;
	string brokerUserID = brokerID.getValue();
	brokerUserID += userID;
	CUserFlowMap::iterator iter = m_mapUserFlow.find(brokerUserID);
	if (iter == m_mapUserFlow.end())
	{
		pFlow = new CIndexPackageFlow();
		pFlow->AttachUnderFlow(m_pPrivateFlow);
		m_mapUserFlow.insert(CUserFlowMap::value_type(brokerUserID, pFlow));
	}
	else
	{
		pFlow = iter->second;
	}
	return pFlow;
}

void CFtdEngine::SendToUserFlow(const CBrokerIDType &brokerID,const CUserIDType &userID, int nIndex)
{
	CIndexPackageFlow *pFlow = GetUserFlow(brokerID,userID);
	pFlow->Append(nIndex);
}

int CFtdEngine::OnReqSubscribeTopic(CFTDCPackage *pPackage, CFTDCSession *pSession)
{
	//重写 wangwei
	
	CFTDRspInfoField ftdRspInfoField;
	ftdRspInfoField.ErrorID = 0;
	ftdRspInfoField.ErrorMsg = "正确";
	m_rspPackage.PrepareResponse(pPackage, FTD_TID_RspSubscribeTopic,FTDC_CHAIN_LAST, FTD_VERSION);
	
	CFTDDisseminationField fieldDissemination;
	if (FTDC_GET_SINGLE_FIELD(pPackage, &fieldDissemination) <= 0)
	{
		return 0;
	}

	TFtdeDisseminationInfo *pFind = m_mapDisseminationInfo.Find(pSession->GetSessionID());
	if (pFind == NULL)	//没找到缓存的订阅信息
	{
		return 0;
	}

	int nSubStartId = fieldDissemination.SequenceNo;
	//如果客户端的交易日与交易引擎不符，则从0开始订阅
	if (pFind->TradingDay != m_TradingDay && 
		 nSubStartId != -1)
	{
		 nSubStartId = 0;
	}
	
	int nPubStartId = 0;
	if(!PublishFlow(pSession, fieldDissemination.SequenceSeries, nSubStartId,
		nPubStartId, pFind->DataCenterID != 0))
	{
		ftdRspInfoField.ErrorID = 1;
		ftdRspInfoField.ErrorMsg = "无效的会话或主题不存在";
	}	
	fieldDissemination.SequenceNo = nPubStartId;
	FTDC_ADD_FIELD(&m_rspPackage, &fieldDissemination);
	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);
	//发送应答
	SendToDialogFlow(pSession, &m_rspPackage);


	if (ftdRspInfoField.ErrorID == 0)
	{
		m_rspPackage.PreparePackage(FTD_TID_IntlRtnDissemination, 
			FTDC_CHAIN_LAST, FTD_VERSION);
		FTDC_ADD_FIELD(&m_rspPackage, &fieldDissemination);
		//直接发送分发信息通知
		pSession->SendRequestPackage(&m_rspPackage);

		if (nSubStartId > nPubStartId)
		{
			m_rspPackage.PreparePackage(FTD_TID_RtnFlowMessageCancel, FTDC_CHAIN_LAST, FTD_VERSION);
			CFTDFlowMessageCancelField fieldFlowMessageCancel;
			fieldFlowMessageCancel.DataCenterID = pFind->DataCenterID;
			fieldFlowMessageCancel.StartSequenceNo = nPubStartId;
			fieldFlowMessageCancel.EndSequenceNo = nSubStartId;
			fieldFlowMessageCancel.SequenceSeries =fieldDissemination.SequenceSeries;
			fieldFlowMessageCancel.TradingDay = pFind->TradingDay;
			FTDC_ADD_FIELD(&m_rspPackage, &fieldFlowMessageCancel);
			pSession->SendRequestPackage(&m_rspPackage);
		}
	}
	return 0;
}

bool CFtdEngine::PublishFlow(CFTDCSession *pSession, WORD wSequenceSeries, int nSubStartId,
							 int &nPubStartId, bool bCheckDataCenter)
{
	TFrontSessionInfo *pSessionInfo = GetSessionInfo(pSession->GetSessionID());
	if (pSessionInfo == NULL)
	{
		return false;
	}
	
	int nBorkenSeqNo = 0;

	//交易流的清理通过中断会话完成，不要重新订阅
	//目前只有私有流和公共流
	CReadOnlyFlow *pFlow = NULL;
	switch (wSequenceSeries)
	{
	case TSS_PRIVATE:
		if (pSessionInfo->UserType == UT_Manager)
		{
			pFlow = GetPrivateFlow(pSessionInfo->BrokerID);
			nBorkenSeqNo = m_FrontFlowBroken.GetParticpantFlowBorken(pSessionInfo->BrokerID);
		}
		else
		{
			pFlow = GetUserFlow(pSessionInfo->BrokerID,pSessionInfo->UserID);
			nBorkenSeqNo = m_FrontFlowBroken.GetUserFlowBroken(pSessionInfo->BrokerID,pSessionInfo->UserID);
		}
		break;
	case TSS_PUBLIC:
		pFlow = GetPublicFlow();
		nBorkenSeqNo = m_FrontFlowBroken.GetPublicFlowBroken();
		break;
	case TSS_USER:
		pFlow = GetUserFlow(pSessionInfo->BrokerID,pSessionInfo->UserID);
		nBorkenSeqNo = m_FrontFlowBroken.GetUserFlowBroken(pSessionInfo->BrokerID,pSessionInfo->UserID);
		break;
	default:
		break;
	}
	if (pFlow == NULL)
	{
		return false;
	}
	
	if (nBorkenSeqNo < nSubStartId)
	{
		REPORT_EVENT(LOG_CRITICAL,"PublishFlow", " BorkenSeqNo:%d, PublishSeqNo:%d ", nBorkenSeqNo, nSubStartId);
		//不应该走入这个路径,wangwei, bCheckDataCenter=false
		nPubStartId = nBorkenSeqNo;
	}
	else
	{
		nPubStartId = nSubStartId;
	}
	
	//增加起始序号有效性判断,如果起始序号小于0且非-1,则清零
	if (nSubStartId == -1)
	{
		nPubStartId = pFlow->GetCount();
	}
	else if (nSubStartId < 0)
	{
		nPubStartId = 0;
	}
		
	pSession->Publish(pFlow, wSequenceSeries, nPubStartId);
	return true;
}

void CFtdEngine::SendToDialogFlow(CFTDCSession *pSession, CFTDCPackage *pPackage)
{
	TFrontSessionInfo *pSessionInfo = GetSessionInfo(pSession->GetSessionID());
	if (pSessionInfo == NULL)
	{
		return;
	}
	TFTDCHeader  *pHeader = pPackage->GetFTDCHeader();
	pHeader->SequenceNumber = ++(pSessionInfo->nDialogFlowSeqNo);
	pHeader->SequenceSeries = TSS_DIALOG;
	pSession->SendRequestPackage(pPackage);
}

void CFtdEngine::SendToQueryFlow(CFTDCSession *pSession, CFTDCPackage *pPackage)
{
	TFrontSessionInfo *pSessionInfo = GetSessionInfo(pSession->GetSessionID());
	if (pSessionInfo == NULL)
	{
		return;
	}
	TFTDCHeader  *pHeader = pPackage->GetFTDCHeader();
	pHeader->SequenceNumber = ++(pSessionInfo->nQueryFlowSeqNo);
	pHeader->SequenceSeries = TSS_QUERY;
	pSession->SendRequestPackage(pPackage);
}

/*
void CFtdEngine::OnNtfDataCenterDesc(CXTPPackage *pMessage)
{
	CDataCenterDescField fieldDataCenterDesc;

	XTP_GET_SINGLE_FIELD(pMessage, &fieldDataCenterDesc);

	if (m_DataCenterID == fieldDataCenterDesc.DataCenterID)
	{
		return;
	}

	m_DataCenterID = fieldDataCenterDesc.DataCenterID;
	//记录当前私有流和公共流的快照
	CParticipantFlowMap::iterator pitor = m_mapPrivateFlow.Begin();
	for (; !pitor.IsEnd(); pitor++)
	{
		m_FrontFlowBroken.RegisterParticpantFlowBorken(pitor.GetKey(),
			(*pitor)->GetCount());
	}

	CUserFlowMap::iterator uitor = m_mapUserFlow.Begin();
	for (; !uitor.IsEnd(); uitor++)
	{
		m_FrontFlowBroken.RegisterUserFlowBorken(uitor.GetKey(),
			(*uitor)->GetCount());
	}

	m_FrontFlowBroken.RegisterPublicFlowBroken(m_pPublicFlow->GetCount());
	
}
*/
int CFtdEngine::OnReqQryTopic(CFTDCPackage *pPackage, CFTDCSession *pSession)
{
	//重写 wangwei
	
	TFrontSessionInfo *pSessionInfo = GetSessionInfo(pSession->GetSessionID());
	if (pSessionInfo == NULL)
	{
		return 0;
	}
	
	CFTDRspInfoField ftdRspInfoField;
	ftdRspInfoField.ErrorID = 0;
	ftdRspInfoField.ErrorMsg = "正确";
	m_rspPackage.PrepareResponse(pPackage, FTD_TID_RspQryTopic,		FTDC_CHAIN_LAST, FTD_VERSION);
	
	CFTDDisseminationField fieldDissemination;
	if (FTDC_GET_SINGLE_FIELD(pPackage, &fieldDissemination) <= 0)
	{
		return 0;
	}
	CReadOnlyFlow *pFlow = NULL;
	switch (fieldDissemination.SequenceSeries)
	{
	case TSS_PRIVATE:
		if (pSessionInfo->UserType == UT_Manager)
		{
			pFlow = GetPrivateFlow(pSessionInfo->BrokerID);
		}
		else
		{
			pFlow = GetUserFlow(pSessionInfo->BrokerID,pSessionInfo->UserID);
		}
		break;
	case TSS_PUBLIC:
		pFlow = GetPublicFlow();
		break;
	case TSS_USER:
		pFlow = GetUserFlow(pSessionInfo->BrokerID,pSessionInfo->UserID);
		break;
	default:
		break;
	}
	fieldDissemination.SequenceNo = (pFlow==NULL)?0:pFlow->GetCount();

	FTDC_ADD_FIELD(&m_rspPackage, &fieldDissemination);
	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);

	//发送应答
	SendToQueryFlow(pSession, &m_rspPackage);

	return 0;
}
bool CFtdEngine::DispatcherEvent(int nEventID, DWORD dwParam, void *pParam)
{
	return PostEvent(nEventID,dwParam,pParam);
}

int CFtdEngine::HandleEvent(int nEventID, DWORD dwParam, void *pParam)
{
	switch(nEventID) 
	{
	case UM_DISPATCHERMESSAGE:
		{
			CXTPPackage *pMessagePackage =(CXTPPackage*)pParam;
			HandleMessage(pMessagePackage);
			delete pMessagePackage;
		}
		return 0;
	default:
		break;
	} 
	return CSessionFactory::HandleEvent(nEventID, dwParam, pParam);

}
list<CUserIDType>* CFtdEngine::GetUsersByInvestorID(CInvestorIDType& InvestorID)
{
	if (InvestorID.isNull())
	{
		return NULL;
	}
	CInvestorUserMap::iterator it=m_InvestorUserMap.find(InvestorID);
	if (it==m_InvestorUserMap.end())
	{
		return NULL;
	}
	return it->second;
}

void CFtdEngine::PrintDelayLog(CInputOrderField &field)
{
	if (g_bLatencyOut)
	{
		InputLocalTime(field.FTdSendDown);
		memset(tmp,0,sizeof(tmp));
		sprintf(tmp,"%s,%s,%s,%d,%d,%d,%d,%d,%d,%d",field.BrokerID.getValue(),field.UserID.getValue(),field.UserOrderLocalID.getValue(),\
			field.FrontID.getValue(),field.SessionID.getValue(),field.APIID.getValue(),field.RequestID.getValue(),\
			field.FTdRecvDown.getValue(),field.FTdSendDown.getValue(),field.FTdSendDown.getValue()-field.FTdRecvDown.getValue());
		m_Delay.push_back(tmp);
	}
}

void CFtdEngine::DumpDelayLog()
{
	FILE *output;
	output=mfopen("FtdOrderDelay.csv","wt");
	if (output!=NULL)
	{
		fprintf(output,"BrokerID,UserID,UserOrderLocalID,FrontID,SessionID,APIID,RequestID,FTdRecvDown,FTdSendDown,Delay\n");
		for (CDelayVector::iterator itor=m_Delay.begin(); itor!=m_Delay.end(); itor++)
		{
			fprintf(output,"%s\n",itor->c_str());
		}
		fclose(output);
	}
}