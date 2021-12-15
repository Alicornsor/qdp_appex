/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file TradeServiceXTPLink.cpp
///@brief��������CTradeServiceXTPLink
///@history 
///20130703	hwp		�������ļ�
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
///CInitServiceMemoryLink��һ��˵��ʹ��XTP��Init���������
///@author	hwp
///@version	1.0,20130703
/////////////////////////////////////////////////////////////////////////


//���������࣬�洢������Ϣ���Ա��Ӧ�����frontid,sessionid��
//by wangwei,20130107
class CSeatOrdActionLocalIDIndex
{
public:
	CSeatOrdActionLocalIDIndex(){};
	~CSeatOrdActionLocalIDIndex(){};
public:
	CSeatIDType	SeatID;//ϯλ
	COrderLocalIDType OrderActionLocalID;//���ر�����
	bool operator > (const CSeatOrdActionLocalIDIndex &m)const
	{
		//��Ա��	
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
			//��Ʒ����Լ
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

//��������
class CSeatOrdLocalIDIndex
{
public:
	CSeatOrdLocalIDIndex(){};
	~CSeatOrdLocalIDIndex(){};
public:
	CSeatIDType	SeatID;//ϯλ
	COrderLocalIDType OrderLocalID;//���ر�����
	bool operator > (const CSeatOrdLocalIDIndex &m)const
	{
		//��Ա��	
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
			//��Ʒ����Լ
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
	TXTPHeader* m_pXtpHdr;//xtpͷ��Ϣ
	CWriteableOrderAction* m_pWritableOrderAction;//�洢orderaction�е�ָ��
};

//����PartID��20130620,wangwei
//PartID+ExchangeID+ClientID����->InvestorID+BrokerID
class CPartExClntIndx
{
public:
	CPartExClntIndx(){};
	~CPartExClntIndx(){};
public:
	CParticipantIDType PartID;//��Ա��
	CExchangeIDType	ExchangeID;//������
	CClientIDType ClientID;//�ͻ���
	CHedgeFlagType HedgeFlag;//Ͷ����־
	
	bool operator > (const CPartExClntIndx &m)const
	{
		//��Ա��
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

//Seat+OrderActionLocalID ��Ϊ������ȷ��Ψһ�ļ�¼
typedef map<CSeatOrdActionLocalIDIndex, CXTPHdrOrderAction * , greater<CSeatOrdActionLocalIDIndex> >  CSeatOrdActionLocalIDXTPMap;
//������Ϣ�ɶ�����洢�����ﲻ����
typedef map<CSeatOrdLocalIDIndex, TXTPHeader * , greater<CSeatOrdLocalIDIndex> >  CSeatOrdLocalIDXTPMap;
//ExchangeID+ClientID->InvestorID
typedef map<CPartExClntIndx, stBrokerAndInvestorID* , greater<CPartExClntIndx> >  CPartExClntInvBrkMp;
//FAKί�е�ͷ����Ϣ
typedef map<CSeatOrdLocalIDIndex, TFakOrderHeaderInfo * , greater<CSeatOrdLocalIDIndex> >  CFakOrderHeaderXTPMap;

typedef unsigned int UINT4;
struct TActionInfo
{
	vector<UINT4> ActionIdVec;
	int  size;
	int  cur_posi;
};
typedef map<UINT4,TActionInfo> CDCEActionMap;//������SeqNo-ActionID


class CBaseExchApi;
class CTradeServiceXTPLink: public IServiceXTPLink
{
public:
	///���캯��������һ��������init���񣬴���һ��ʹ��XTP������
	///@param	pInitService	ָ���Ľ�����init����
	///@param	pErrorEngine	���ڷ��ش��������
	///@param	verbose	true��ʾ��Ҫ��������flase��ʾ����������
	CTradeServiceXTPLink(CTradeServiceImpl *pTradeService,CErrorEngine *pErrorEngine,IServiceResponser *pServiceResponser,CFlow* pTradeResult,bool verbose=true);
	
	virtual ~CTradeServiceXTPLink();

	///����һ��XTP��
	///@param	pPackage	Ҫ�����XTP��
	///@param	sessionRef	�Ự����
	///@return	true��ʾ����ɹ���false��ʾ����ʧ��
	virtual bool handleMessage(CXTPPackage *pPackage, const TSessionRef &sessionRef);

	///����һ��XTP����
	///@param	pPackage	Ҫ�����XTP��
	///@param	sessionRef	�Ự����
	///@return	true��ʾ����ɹ���false��ʾ����ʧ��
	virtual bool handleRequest(CXTPPackage *pPackage,const TSessionRef &sessionRef,DWORD dwReponseSession);
	
	//virtual void setFlow(CFlow *pFlow);
	virtual void DumpMemDb();//by wangwei,20130701
protected:
	bool AppendTReqFlow();
	bool AppendTSeriesFlow();
//Map��ز���
	CXTPHdrOrderAction* GetReqHdrAndOrdAct(CSeatIDType& SeatID,COrderLocalIDType& OrderActionLocalID);
	bool SaveReqHdrAndWtOrdAct(CSeatIDType& SeatID,COrderLocalIDType& OrderActionLocalID,TXTPHeader* pHdr,CWriteableOrderAction* pOrdAct);
//������ͷ
	bool SaveReqOrdHdr(CSeatIDType& SeatID,COrderLocalIDType& OrderLocalID,TXTPHeader* pHdr);
	TXTPHeader* GetReqOrdHdr(CSeatIDType& SeatID,COrderLocalIDType& OrderLocalID);
//FAK/FOK��������ͷ
	bool SaveFakOrdHdr(CSeatIDType& SeatID,COrderLocalIDType& OrderLocalID,TFakOrderHeaderInfo* pHdr);
	TXTPHeader* GetFakOrdHdr(CSeatIDType& SeatID,COrderLocalIDType& OrderLocalID,int tradeVolume=0);

	//���Ͻ������ͱ�ϵͳ�ı�����Ϣ
	void MergeErrorMsg(CRspInfoField* pExInfo,CRspInfoField* pUsInfo,CRspInfoField& outInfo);
	//ȡ��investor��Ӧ������user�������ɽ�ntf��ϢӦ���͸�������ص�user
	bool GetInvBrkByPartExClnt(CParticipantIDType& PartID,CExchangeIDType& ExchangeID,CClientIDType& ClientID,CInvestorIDType &InvestorID,CBrokerIDType &BrokerID);

private:
	CTradeServiceImpl *m_pTradeService;
	CErrorEngine *m_pErrorEngine;

	CFlow* m_pTradeResult;
	bool m_verbose;
	CTransaction m_Transaction;
	CXTPPackage	 *m_pRspMessage;
	IServiceResponser *m_pServiceResponser;

	CSeatOrdActionLocalIDXTPMap m_SeatOrdActionLocalIDXTPMap;//����������Ϣ��
	CSeatOrdLocalIDXTPMap m_SeatOrdLocalIDXTPMap;//����ͷ��Ϣ��
	CPartExClntInvBrkMp m_PartExClntInvBrkMp;//ExchangeID+ClientID->InvestorID
	CFakOrderHeaderXTPMap m_FakOrderHeaderMap;//FAK/FOKί�е���Ϣ�� add by cgm

	//cgm add 20150820 ������������ֵ
	int m_iActionNums;
	UserActionNumsInfo  m_ActionNumsInfo;
	CDCEActionMap m_DceOrderActionMap;
	char tmp[50];
};

#endif
