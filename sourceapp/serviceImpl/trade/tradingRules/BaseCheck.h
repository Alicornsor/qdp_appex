/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file BaseCheck.h
///@brief定义了类CBaseCheck(订单基础检查类)
///@history 
///20121222	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////
#ifndef BASE_CHECK_201211222
#define BASE_CHECK_201211222

#include "errorDefine.h"
#include "CMemoryDB.h"
#include "XtpData.h"
#include "IServiceInterface.h"
#include "BaseDataStruct.h"
#include "baseAlgorithms.h"
//ExchangeID+SeatID索引->OrderLocalID
class CExchangeSeatIndex
{
public:
	CExchangeSeatIndex(){};
	~CExchangeSeatIndex(){};
public:
	CExchangeIDType	ExchangeID;//交易所
	CSeatIDType SeatID;
	bool operator > (const CExchangeSeatIndex &m)const
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
				return false;
			}
		}
	}
};

//ExchangeID+PartID索引->SeatID
class CExchangePartIndex
{
public:
	CExchangePartIndex(){};
	~CExchangePartIndex(){};
public:
	CExchangeIDType	ExchangeID;//交易所
	CParticipantIDType ParticipantID;//会员
	bool operator > (const CExchangePartIndex &m)const
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
			if (ParticipantID > m.ParticipantID)
			{
				return true;
			}
			else if (ParticipantID < m.ParticipantID)
			{
				return false;
			}
			else
			{
				return false;
			}
		}
	}
	bool operator < (const CExchangePartIndex &m)const
	{
		if (ExchangeID < m.ExchangeID)
		{
			return true;
		}
		else if (ExchangeID > m.ExchangeID)
		{
			return false;
		}
		else
		{
			if (ParticipantID < m.ParticipantID)
			{
				return true;
			}
			else if (ParticipantID > m.ParticipantID)
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

//Exchange+Seat->最大本地报单号
typedef map<CExchangeSeatIndex, COrderLocalIDType , greater<CExchangeSeatIndex> >  CExchangeSeatOrderLocalIDMap;
// typedef map<CExchangeIDType, int> CExchangeSeatCountMap;
//交易所+会员对应的可用席位
typedef map<CExchangePartIndex, list<CSeatIDType>*> CExPartSeatsMap;

typedef map<CInstrumentIDType, CWriteableInstrument*> CInstrumentMap;

class CBaseCheck
{
public:
	CBaseCheck(CMemoryDB *pDB, CErrorEngine *pErrorEngine);
	virtual ~CBaseCheck();	
	virtual bool OrderCheck(CWriteablePreOrder *pOrder,const TSessionRef &sessionRef,CTransaction* pTransaction);//报单检查
	virtual bool OrderActionCheck(CWriteableOrderAction *pOrderAction,const TSessionRef &sessionRef,CTransaction* pTransaction);//撤单检查	
	virtual bool InvestorCheck(CWriteablePreOrder *pOrder,const TSessionRef &sessionRef,CTransaction* pTransaction);//投资者检查
	virtual bool SessionCheck(CIPAddressType& IPAddress,CMacAddressType& MacAddress,CUserIDType& UserID,CBrokerIDType& BrokerID,const TSessionRef &sessionRef);
	virtual bool RightCheck(CWriteablePreOrder *pOrder,CTransaction* pTransaction);//3.权限检查

	virtual bool LocalIDCheck(CBrokerIDType& BrokerID,CUserOrderLocalIDType& UserOrderLocalID,CUserIDType& UserID,const TSessionRef &sessionRef,CTransaction* pTransaction);
	static void HandleSeatLoginSuccess(CLoginInfoField *pLoginInfo);
	static void HandleSeatDisconnected(CSeatField *pSeat);
protected:
	/*公共函数*/
	virtual bool SysStatusCheck();
	//virtual bool SessionCheck(CWriteablePreOrder *pOrder,const TSessionRef &sessionRef);//1.会话检查
	virtual bool FieldCheck(CWriteablePreOrder *pOrder);//2.字段检查	
	
	//virtual bool LocalIDCheck(CWriteablePreOrder *pOrder,CTransaction* pTransaction);//4.客户本地报单号检查,同时分好系统给他的本地报单号
	virtual bool VolumePriceCheck(CWriteablePreOrder *pOrder);//5.报单价格检查
	/*撤单检查*/
	virtual bool ActionTargetCheck(CWriteableOrderAction *pOrderAction);//操作对象检查
//	virtual bool SessionCheck(CWriteableOrderAction *pOrderAction,const TSessionRef &sessionRef);//1.会话检查
	virtual bool FieldCheck(CWriteableOrderAction *pOrderAction);//2.字段检查
	virtual bool RightCheck(CWriteableOrderAction *pOrderAction);//3.权限检查
	//virtual bool LocalIDCheck(CWriteableOrderAction *pOrderAction,CTransaction* pTransaction);//4.客户本地报单号检查,同时分好系统给他的本地报单号		
private:
	static CMemoryDB *m_pDB;
	CErrorEngine *m_pErrorEngine;
	bool m_bCheckComplianceSwitch;//是否进行合规检查的开关
	static CExchangeSeatOrderLocalIDMap m_ExchangeSeatOrderLocalIDMap;
	static CExPartSeatsMap m_ExPartSeatsMap;
public:
	static CSystemStatusType m_SystemStatus;
	static CInstrumentMap m_InstrumentMap;
	static int m_initcount;
	CBaseAlgorithms baseAlgorithms;
};

#endif

