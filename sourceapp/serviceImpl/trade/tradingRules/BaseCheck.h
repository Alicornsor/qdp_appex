/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file BaseCheck.h
///@brief��������CBaseCheck(�������������)
///@history 
///20121222	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////
#ifndef BASE_CHECK_201211222
#define BASE_CHECK_201211222

#include "errorDefine.h"
#include "CMemoryDB.h"
#include "XtpData.h"
#include "IServiceInterface.h"
#include "BaseDataStruct.h"
#include "baseAlgorithms.h"
//ExchangeID+SeatID����->OrderLocalID
class CExchangeSeatIndex
{
public:
	CExchangeSeatIndex(){};
	~CExchangeSeatIndex(){};
public:
	CExchangeIDType	ExchangeID;//������
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

//ExchangeID+PartID����->SeatID
class CExchangePartIndex
{
public:
	CExchangePartIndex(){};
	~CExchangePartIndex(){};
public:
	CExchangeIDType	ExchangeID;//������
	CParticipantIDType ParticipantID;//��Ա
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

//Exchange+Seat->��󱾵ر�����
typedef map<CExchangeSeatIndex, COrderLocalIDType , greater<CExchangeSeatIndex> >  CExchangeSeatOrderLocalIDMap;
// typedef map<CExchangeIDType, int> CExchangeSeatCountMap;
//������+��Ա��Ӧ�Ŀ���ϯλ
typedef map<CExchangePartIndex, list<CSeatIDType>*> CExPartSeatsMap;

typedef map<CInstrumentIDType, CWriteableInstrument*> CInstrumentMap;

class CBaseCheck
{
public:
	CBaseCheck(CMemoryDB *pDB, CErrorEngine *pErrorEngine);
	virtual ~CBaseCheck();	
	virtual bool OrderCheck(CWriteablePreOrder *pOrder,const TSessionRef &sessionRef,CTransaction* pTransaction);//�������
	virtual bool OrderActionCheck(CWriteableOrderAction *pOrderAction,const TSessionRef &sessionRef,CTransaction* pTransaction);//�������	
	virtual bool InvestorCheck(CWriteablePreOrder *pOrder,const TSessionRef &sessionRef,CTransaction* pTransaction);//Ͷ���߼��
	virtual bool SessionCheck(CIPAddressType& IPAddress,CMacAddressType& MacAddress,CUserIDType& UserID,CBrokerIDType& BrokerID,const TSessionRef &sessionRef);
	virtual bool RightCheck(CWriteablePreOrder *pOrder,CTransaction* pTransaction);//3.Ȩ�޼��

	virtual bool LocalIDCheck(CBrokerIDType& BrokerID,CUserOrderLocalIDType& UserOrderLocalID,CUserIDType& UserID,const TSessionRef &sessionRef,CTransaction* pTransaction);
	static void HandleSeatLoginSuccess(CLoginInfoField *pLoginInfo);
	static void HandleSeatDisconnected(CSeatField *pSeat);
protected:
	/*��������*/
	virtual bool SysStatusCheck();
	//virtual bool SessionCheck(CWriteablePreOrder *pOrder,const TSessionRef &sessionRef);//1.�Ự���
	virtual bool FieldCheck(CWriteablePreOrder *pOrder);//2.�ֶμ��	
	
	//virtual bool LocalIDCheck(CWriteablePreOrder *pOrder,CTransaction* pTransaction);//4.�ͻ����ر����ż��,ͬʱ�ֺ�ϵͳ�����ı��ر�����
	virtual bool VolumePriceCheck(CWriteablePreOrder *pOrder);//5.�����۸���
	/*�������*/
	virtual bool ActionTargetCheck(CWriteableOrderAction *pOrderAction);//����������
//	virtual bool SessionCheck(CWriteableOrderAction *pOrderAction,const TSessionRef &sessionRef);//1.�Ự���
	virtual bool FieldCheck(CWriteableOrderAction *pOrderAction);//2.�ֶμ��
	virtual bool RightCheck(CWriteableOrderAction *pOrderAction);//3.Ȩ�޼��
	//virtual bool LocalIDCheck(CWriteableOrderAction *pOrderAction,CTransaction* pTransaction);//4.�ͻ����ر����ż��,ͬʱ�ֺ�ϵͳ�����ı��ر�����		
private:
	static CMemoryDB *m_pDB;
	CErrorEngine *m_pErrorEngine;
	bool m_bCheckComplianceSwitch;//�Ƿ���кϹ���Ŀ���
	static CExchangeSeatOrderLocalIDMap m_ExchangeSeatOrderLocalIDMap;
	static CExPartSeatsMap m_ExPartSeatsMap;
public:
	static CSystemStatusType m_SystemStatus;
	static CInstrumentMap m_InstrumentMap;
	static int m_initcount;
	CBaseAlgorithms baseAlgorithms;
};

#endif

