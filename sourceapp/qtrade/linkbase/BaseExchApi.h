// BaseApi.h: interface for the CBaseApi class.
//
//////////////////////////////////////////////////////////////////////
/************************************************************************
* ��Ȩ���� (C)2005
* 
* �ļ����ƣ�BaseExchApi.cpp
* �ļ���ʶ�� 
* ����ժҪ�� 
* ����˵���� 
* ��ǰ�汾�� 
* ��    �ߣ� ��ΰƽ
* ������ڣ� 2005��8��15��
* 
* �޸ļ�¼1��// �޸���ʷ��¼�������޸����ڡ��޸��߼��޸�����
*    �޸����ڣ�
*    �� �� �ţ�
*    �� �� �ˣ�
*    �޸����ݣ� 
* �޸ļ�¼2����
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


//��������־
#define	EX_PDATA            0           //PDATA
#define	EX_PFRONT           1           //PFront
#define	EX_PMarket		    2           //�������,Ŀǰ��Ƶ�汾��δʹ��

//#define	EX_CFFEX            5            //�н���
//#define	EX_SHFE             6           //������
//#define	EX_DCE              7           //������
//#define	EX_ZCE              8           //֣����



#define CFFEX_NAME "CFFEX"
#define SHFE_NAME "SHFE"
#define SSE_NAME "SSE"
#define SZSE_NAME "SZSE"
#define SGE_NAME "SGE"
#define HKEX_NAME "HKEX"
#define SGX_NAME "SGX"

//����������

#define	DIALOG_FLOW  	1           //�Ի���
#define	PRIVATE_FLOW  	2           //˽����
#define	PUBLIC_FLOW     3           //������
#define	QUERY_FLOW		4			//��ѯ

#define CCY_RMB "1"				    //�����
#define CCY_USDOLLOR "2"			//��Ԫ


#define	ProductInfo  "QDP_v1.0"	//��Ʒ��Ϣ
//#define	ProductInfo  "Femas_v1.01"	//��Ʒ��Ϣ

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
	///����
	virtual int ReqOrderInsert(CInputOrderField &Order){ return 0;};
	virtual int ReqOrderInsert(CWriteablePreOrder &Order, bool needOrderLocalID=true){ return 0;};
	///����
	virtual int ReqOrderAction(COrderActionField &OrderAction){return 0;};
	//��ѯ����
	virtual bool ReqQryMarketData(CExchangeIDType ExchangeID,CInstrumentIDType InstrumentID){return true;};
	//��ѯ�ּ�����
	virtual bool ReqQryMBLMarketData(CQryMBLMarketDataField &pMBLMarketData,const TSessionRef &sessionRef){return true;};
	///��ʼ��ϯλ��Ϣ
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
			//������Ӧʱ��
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

	//��ȡ������������״̬����������ʱ��Ҫ added by chengm 2016-01-14
	bool m_bConnected;
	bool m_bCheckLinked;//������API���ܶ�������ʱ��LinkMange��������
	bool m_bRevRtn;//�Ƿ������ˮ��������ڲ��������߲���Ҫ������ˮ�����ܵ���ˮ��Ϣ�����浽���ļ�������qtrade����

#ifndef WIN32
	struct timeval m_nBeginTime; //ԭʼ����ʱ��
#else
	struct _timeb  m_nBeginTime;
#endif
	
	//����
	COrderLocalIDType	m_OrderLocalID;
	CUserIDType	m_UserID;
	int m_CostTime;
};
#endif
