// BaseApi.h: interface for the CBaseApi class.
//
//////////////////////////////////////////////////////////////////////
/************************************************************************
* 版权所有 (C)2005
* 
* 文件名称：BaseExchApi.cpp
* 文件标识： 
* 内容摘要： 
* 其它说明： 
* 当前版本： 
* 作    者： 胡伟平
* 完成日期： 2005年8月15日
* 
* 修改记录1：// 修改历史记录，包括修改日期、修改者及修改内容
*    修改日期：
*    版 本 号：
*    修 改 人：
*    修改内容： 
* 修改记录2：…
************************************************************************/
#ifndef BaseExchApi_H
#define BaseExchApi_H


#include "XtpData.h"
#include "FlowReader.h"
#include "UFEntityCopy.h"
#include "BaseDataStruct.h"
#include "ExCachedFlow.h"
#include "XTPPackage.h"
#include "IServiceInterface.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//交易所标志
#define	EX_PDATA            0           //PDATA
#define	EX_PFRONT           1           //PFront
#define	EX_PMarket		    2           //行情介入,目前高频版本还未使用

//#define	EX_CFFEX            5            //中金所
//#define	EX_SHFE             6           //上期所
//#define	EX_DCE              7           //大商所
//#define	EX_ZCE              8           //郑商所



#define CFFEX_NAME "CFFEX"
#define SHFE_NAME "SHFE"
#define SSE_NAME "SSE"
#define SZSE_NAME "SZSE"
#define SGE_NAME "SGE"
#define HKEX_NAME "HKEX"
#define SGX_NAME "SGX"

//数据流类型

#define	DIALOG_FLOW  	1           //对话流
#define	PRIVATE_FLOW  	2           //私有流
#define	PUBLIC_FLOW     3           //公共流
#define	QUERY_FLOW		4			//查询

#define CCY_RMB "1"				    //人民币
#define CCY_USDOLLOR "2"			//美元


#define	ProductInfo  "QDP_v1.0"	//产品信息
//#define	ProductInfo  "Femas_v1.01"	//产品信息

#ifndef COPYBASEAPISEATINFO
#define COPYBASEAPISEATINFO(target,source)	\
	(target)->BrokerID=(source)->BrokerID;	\
	(target)->ExchangeID=(source)->ExchangeID;	\
	(target)->ParticipantID=(source)->ParticipantID;
#endif

//extern int GetAPIID(const char *pAPIID);
#include "ExCachedFlow.h"

class CPackage;
class CBaseExchApi
{
public:
	CBaseExchApi()
	{
		m_PublicSeqNO = 0;
		m_PrivateSeqNO = 0;
		m_OrderTimes = 0;
		m_TradeTimes = 0;
		m_bLogin = false;
		m_bInitSeat = false;
		m_pSeriesFlow = NULL;
		m_bConnected = false;
		m_bCheckLinked =false;
		m_bRevRtn = false;
	};
	virtual ~CBaseExchApi(){};
	///报单
	virtual int ReqOrderInsert(CInputOrderField &Order){ return 0;};
	virtual int ReqOrderInsert(CWriteablePreOrder &Order, bool needOrderLocalID=true){ return 0;};
	///撤单
	virtual int ReqOrderAction(COrderActionField &OrderAction){return 0;};
	//查询行情
	virtual bool ReqQryMarketData(CExchangeIDType ExchangeID,CInstrumentIDType InstrumentID){return true;};
	//查询分价行情
	virtual bool ReqQryMBLMarketData(CQryMBLMarketDataField &pMBLMarketData,const TSessionRef &sessionRef){return true;};
	///初始化席位信息
	void InitSeatInfo(CSeatField *pSeat)
	{
		if (!m_bInitSeat)
		{
			//SetPasswd(Seat.SeatPassword.getValue());
			//SetUserID(Seat.SeatID.getValue());
			CopySeatEntity(&m_Seat,pSeat);
			sprintf(m_sIdInfo,"APIID:%d,EXID:%s,SeatID:%s,PartID:%s,Main:%d",m_Seat.APIID.getValue(),m_Seat.ExchangeID.getValue(),m_Seat.SeatID.getValue(),m_Seat.ParticipantID.getValue(),m_Seat.MainSeat.getValue());
			REPORT_EVENT(LOG_CRITICAL, "InitSeatInfo", "%s,SeatID=[%s] Password=[%s]",m_Seat.ExchangeID.getValue(),m_Seat.SeatID.getValue(),"******");
			m_bInitSeat = true;
		}
	};
	virtual bool InitClientIDSet(string szClientID){ return true; };	
	virtual void InitClientTradingID(CClientTradingIDField *clientTradingID){};
	virtual char *GetLocalID(char cExchangID='s'){return NULL;};
	virtual bool GetNextUseNoBuf(CPackage *pPackage)
	{
		return m_reader.GetNextUseNoBuf(pPackage);
	};
	virtual char *GetLocalID(const char *pClientID,char cEoFlag='1'){ return NULL;};
	virtual void StartWork(){};
 	const char *GetUserID()
 	{ 
 		return m_Seat.SeatID.getValue();
 	};	
	virtual bool GetStatus()
	{	
		return m_bLogin;
	}

	virtual void SetFensIp(const char *pIpFensIP){};
	virtual void SetFrontIp(const char *pIpFrontIP){};

	//
	virtual void SetMaxLocalID(int nMaxLocalID){};

	virtual void InputSample(CILocalTimeType &LocalTime)
	{
	#ifndef  WIN32
		gettimeofday(&m_nBeginTime, NULL);
		LocalTime = m_nBeginTime.tv_sec*1000000+m_nBeginTime.tv_usec;
	#else
		_ftime( &m_nBeginTime );
		LocalTime = m_nBeginTime.time*1000+m_nBeginTime.millitm;
#endif	
	}

	virtual void InputResult(COrderLocalIDType &OrderLocalID)
	{
		
		if (OrderLocalID==m_OrderLocalID)
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
		}
		else
		{
			m_CostTime=0;
			return;
		}
	}
public:
	int m_PublicSeqNO;
	int m_PrivateSeqNO;
	//char m_MemberID[20];
	//char m_TraderNo[20];
	//char m_Password[50];
	int  m_OrderTimes;
	int  m_TradeTimes;
	//char m_ExchangeName[20];
	//int  m_ExchangeID;
	bool m_bLogin;
	CExCachedFlow *m_pSeriesFlow;
	CFlowReader m_reader;
	CSeatField m_Seat;
	char m_sIdInfo[512];
	bool m_bInitSeat;

	//获取各交易所连接状态，断线重连时需要 added by chengm 2016-01-14
	bool m_bConnected;
	bool m_bCheckLinked;//交易所API不能断线重连时，LinkMange负责重连
	bool m_bRevRtn;//是否接受流水，如果日期不符，或者不需要接受流水，接受的流水信息不保存到流文件，不像qtrade发送

#ifndef WIN32
	struct timeval m_nBeginTime; //原始采样时间
#else
	struct _timeb  m_nBeginTime;
#endif
	
	//样本
	COrderLocalIDType	m_OrderLocalID;
	CUserIDType	m_UserID;
	int m_CostTime;
};
#endif
