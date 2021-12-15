/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file TradeServiceXTPLink.cpp
///@brief定义了类CTradeServiceXTPLink
///@history 
///20130703	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef TRADESERVICEXTPLINK_H
#define TRADESERVICEXTPLINK_H

#include "ServiceXTPLink.h"
#include "CMemoryDB.h"
#include "IServiceInterface.h"
#include "XtpData.h"
#include "CErrorEngine.h"
#include "CTransaction.h"
#include "Flow.h"
#include "UFEntityCopy.h"
#include "ReqFlow.h"
#include <list>
#include "CTradeServiceImpl.h"

/////////////////////////////////////////////////////////////////////////
///CInitServiceMemoryLink是一个说明使用XTP的Init服务的连接
///@author	hwp
///@version	1.0,20130703
/////////////////////////////////////////////////////////////////////////


//加入索引类，存储请求信息，以便给应答加上frontid,sessionid等
//by wangwei,20130107
class CSeatOrdActionLocalIDIndex
{
public:
	CSeatOrdActionLocalIDIndex(){};
	~CSeatOrdActionLocalIDIndex(){};
public:
	CSeatIDType	SeatID;//席位
	COrderLocalIDType OrderActionLocalID;//本地报单号
	bool operator > (const CSeatOrdActionLocalIDIndex &m)const
	{
		//会员号	
		if (SeatID > m.SeatID)
		{
			return true;
		}
		else if (SeatID < m.SeatID)
		{
			return false;
		}
		else
		{
			//产品、合约
			if (OrderActionLocalID > m.OrderActionLocalID)
			{
				return true;
			}
			else if (OrderActionLocalID < m.OrderActionLocalID)
			{
				return false;
			}
			else
			{			
				return false;
			}
		}
	}
};

//报单索引
class CSeatOrdLocalIDIndex
{
public:
	CSeatOrdLocalIDIndex(){};
	~CSeatOrdLocalIDIndex(){};
public:
	CSeatIDType	SeatID;//席位
	COrderLocalIDType OrderLocalID;//本地报单号
	bool operator > (const CSeatOrdLocalIDIndex &m)const
	{
		//会员号	
		if (SeatID > m.SeatID)
		{
			return true;
		}
		else if (SeatID < m.SeatID)
		{
			return false;
		}
		else
		{
			//产品、合约
			if (OrderLocalID > m.OrderLocalID)
			{
				return true;
			}
			else if (OrderLocalID < m.OrderLocalID)
			{
				return false;
			}
			else
			{			
				return false;
			}
		}
	}
};

class CXTPHdrOrderAction
{
public:
	CXTPHdrOrderAction(TXTPHeader* pHdr,CWriteableOrderAction* pOrdAct)
	{
		m_pXtpHdr=new TXTPHeader();
		m_pWritableOrderAction = new CWriteableOrderAction();
		memcpy(m_pXtpHdr,pHdr,sizeof(struct TXTPHeader));
		CopyOrderActionEntity(m_pWritableOrderAction,pOrdAct);
		m_pWritableOrderAction->linkOrder(pOrdAct->getOrder());
	}
	CXTPHdrOrderAction(CXTPHdrOrderAction* pHdrOrd)
	{
		m_pXtpHdr=new TXTPHeader();
		m_pWritableOrderAction = new CWriteableOrderAction();
		memcpy(m_pXtpHdr,pHdrOrd->m_pXtpHdr,sizeof(struct TXTPHeader));
		CopyOrderActionEntity(m_pWritableOrderAction,pHdrOrd->m_pWritableOrderAction);
		m_pWritableOrderAction->linkOrder(pHdrOrd->m_pWritableOrderAction->getOrder());
	}
	~CXTPHdrOrderAction()
	{
		if (m_pXtpHdr!=NULL)
		{
			delete m_pXtpHdr;
			m_pXtpHdr=NULL;
		}
		if (m_pWritableOrderAction!=NULL)
		{
			delete m_pWritableOrderAction;
			m_pWritableOrderAction=NULL;
		}
	}
	TXTPHeader* m_pXtpHdr;//xtp头信息
	CWriteableOrderAction* m_pWritableOrderAction;//存储orderaction中的指针
};

//加入PartID，20130620,wangwei
//PartID+ExchangeID+ClientID索引->InvestorID+BrokerID
class CPartExClntIndx
{
public:
	CPartExClntIndx(){};
	~CPartExClntIndx(){};
public:
	CParticipantIDType PartID;//会员号
	CExchangeIDType	ExchangeID;//交易所
	CClientIDType ClientID;//客户号
	CHedgeFlagType HedgeFlag;//投保标志
	
	bool operator > (const CPartExClntIndx &m)const
	{
		//会员号
		if (PartID>m.PartID)
		{
			return true;
		}
		else if (PartID<m.PartID)
		{
			return false;
		}
		else
		{
			if (ExchangeID > m.ExchangeID)
			{
				return true;
			}
			else if (ExchangeID < m.ExchangeID)
			{
				return false;
			}
			else
			{				
				if (ClientID > m.ClientID)
				{
					return true;
				}
				else if (ClientID < m.ClientID)
				{
					return false;
				}
				else
				{			
					if (HedgeFlag > m.HedgeFlag)
					{
						return true;
					}
					else if (HedgeFlag < m.HedgeFlag)
					{
						return false;
					}
					else
					{
						return false;
					}
					
				}
			}
		}

	}
};

struct stBrokerAndInvestorID
{
	CInvestorIDType InvestorID;
	CBrokerIDType BrokerID;
};

struct stUserActionNumsInfo
{
	CExchangeIDType ExchangeID;
	CBrokerIDType   BrokerID;
	CClientIDType   ClientID;
	CParticipantIDType ParticipantID;
	CInvestorIDType InvestorID;
	CBusinessTypeType BusinessType;
	int				TotalNums;
};
typedef vector<stUserActionNumsInfo> UserActionNumsInfo;

struct TFakOrderHeaderInfo
{
	int   OrderVolume;
	TXTPHeader header;
};

//Seat+OrderActionLocalID 作为索引，确定唯一的记录
typedef map<CSeatOrdActionLocalIDIndex, CXTPHdrOrderAction * , greater<CSeatOrdActionLocalIDIndex> >  CSeatOrdActionLocalIDXTPMap;
//订单信息由订单表存储，这里不用了
typedef map<CSeatOrdLocalIDIndex, TXTPHeader * , greater<CSeatOrdLocalIDIndex> >  CSeatOrdLocalIDXTPMap;
//ExchangeID+ClientID->InvestorID
typedef map<CPartExClntIndx, stBrokerAndInvestorID* , greater<CPartExClntIndx> >  CPartExClntInvBrkMp;
//FAK委托单头部信息
typedef map<CSeatOrdLocalIDIndex, TFakOrderHeaderInfo * , greater<CSeatOrdLocalIDIndex> >  CFakOrderHeaderXTPMap;

typedef unsigned int UINT4;
struct TActionInfo
{
	vector<UINT4> ActionIdVec;
	int  size;
	int  cur_posi;
};
typedef map<UINT4,TActionInfo> CDCEActionMap;//交易所SeqNo-ActionID


class CBaseExchApi;
class CTradeServiceXTPLink: public IServiceXTPLink
{
public:
	///构造函数，根据一个交易所init服务，创建一个使用XTP的连接
	///@param	pInitService	指定的交易所init服务
	///@param	pErrorEngine	用于返回错误的引擎
	///@param	verbose	true表示需要输出结果，flase表示不必输出结果
	CTradeServiceXTPLink(CTradeServiceImpl *pTradeService,CErrorEngine *pErrorEngine,IServiceResponser *pServiceResponser,CFlow* pTradeResult,bool verbose=true);
	
	virtual ~CTradeServiceXTPLink();

	///处理一个XTP包
	///@param	pPackage	要处理的XTP包
	///@param	sessionRef	会话引用
	///@return	true表示处理成功，false表示处理失败
	virtual bool handleMessage(CXTPPackage *pPackage, const TSessionRef &sessionRef);

	///处理一个XTP请求
	///@param	pPackage	要处理的XTP包
	///@param	sessionRef	会话引用
	///@return	true表示处理成功，false表示处理失败
	virtual bool handleRequest(CXTPPackage *pPackage,const TSessionRef &sessionRef,DWORD dwReponseSession);
	
	//virtual void setFlow(CFlow *pFlow);
	virtual void DumpMemDb();//by wangwei,20130701
protected:
	bool AppendTReqFlow();
	bool AppendTSeriesFlow();
//Map相关操作
	CXTPHdrOrderAction* GetReqHdrAndOrdAct(CSeatIDType& SeatID,COrderLocalIDType& OrderActionLocalID);
	bool SaveReqHdrAndWtOrdAct(CSeatIDType& SeatID,COrderLocalIDType& OrderActionLocalID,TXTPHeader* pHdr,CWriteableOrderAction* pOrdAct);
//报单包头
	bool SaveReqOrdHdr(CSeatIDType& SeatID,COrderLocalIDType& OrderLocalID,TXTPHeader* pHdr);
	TXTPHeader* GetReqOrdHdr(CSeatIDType& SeatID,COrderLocalIDType& OrderLocalID);
//FAK/FOK单报单包头
	bool SaveFakOrdHdr(CSeatIDType& SeatID,COrderLocalIDType& OrderLocalID,TFakOrderHeaderInfo* pHdr);
	TXTPHeader* GetFakOrdHdr(CSeatIDType& SeatID,COrderLocalIDType& OrderLocalID,int tradeVolume=0);

	//整合交易所和本系统的报错信息
	void MergeErrorMsg(CRspInfoField* pExInfo,CRspInfoField* pUsInfo,CRspInfoField& outInfo);
	//取出investor对应的所有user，订单成交ntf信息应发送给所有相关的user
	bool GetInvBrkByPartExClnt(CParticipantIDType& PartID,CExchangeIDType& ExchangeID,CClientIDType& ClientID,CInvestorIDType &InvestorID,CBrokerIDType &BrokerID);

private:
	CTradeServiceImpl *m_pTradeService;
	CErrorEngine *m_pErrorEngine;

	CFlow* m_pTradeResult;
	bool m_verbose;
	CTransaction m_Transaction;
	CXTPPackage	 *m_pRspMessage;
	IServiceResponser *m_pServiceResponser;

	CSeatOrdActionLocalIDXTPMap m_SeatOrdActionLocalIDXTPMap;//撤单请求信息表
	CSeatOrdLocalIDXTPMap m_SeatOrdLocalIDXTPMap;//订单头信息表
	CPartExClntInvBrkMp m_PartExClntInvBrkMp;//ExchangeID+ClientID->InvestorID
	CFakOrderHeaderXTPMap m_FakOrderHeaderMap;//FAK/FOK委托单信息表 add by cgm

	//cgm add 20150820 撤单次数报警值
	int m_iActionNums;
	UserActionNumsInfo  m_ActionNumsInfo;
	CDCEActionMap m_DceOrderActionMap;
	char tmp[50];
};

#endif
