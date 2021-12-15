// FtdEngine.cpp: implementation of the CFtdEngine class.
//
// 20061011 hwp  ���Ӷ�SSL�ļ�飬�޸��˷���OnReqUserLogin 
//                  OnReqUserLogin����������ߣ����ô����ӶԷ���ֵ�ļ��
// 20070509 hwp  ԭHandleResponse��һ�����ͽ��Ǳ�ǰ�õ�Ӧ������ˣ�
//                  ����ɸ�ǰ�ò�����˽�����е�ErrRtn��ͬ��
// 20070704 hwp  ���ӻ��ڽ���Ա��˽����
// 20070807 hwp  ���ӵ�¼ʱ�Խӿڰ汾�ļ��
// 20070822 hwp  ����QUICK��ʽ����˽�����͹��������ճ�ʱ�����ش�������
// 20071009 hwp  ��������Ӧ��ͱ�������Ӧ���в���ԭ��Ϊѹ�����ݶ����
//                  ���ֶ�
// 20071019 hwp  �������б���Ӧ���в���ԭ��Ϊѹ�����ݶ���յ��ֶΣ�
//                  Ӱ��FTD_TID_RspOrderInsert��FTD_TID_ErrRtnOrderInsert
// 20071012 hwp  ���Ӷ���ָ�ReqSubscribeTopic����ʹ����Ա�˿�������
//                  ���������ش��������ڽ���Ա�˱�֤�����������
// 20071119 xuzh  ���ӵ�¼ʱ�ش���ʼ��ŵ���Ч�Լ��
// 20080626 hwp  NT-0041�Ի����Ͳ�ѯ������ʹ��Flow����ֻ������ţ������ڴ�ռ��
// 20080701 hwp  NT-0035��������֪ͨ����¼ʱ����������Ĵ��룬������Ҫ
//                  ��������������֪ͨ
// 20080721 hwp  NT-0045-��ϯλ���أ�����RspUserLogin���趨�Ự�����޶
// 20080727 hwp  NT-0048:��չCSessionFactory::CreateSession���������ڴ���
//                  �Ựʱ���ֲ�ͬ������
// 20081128 hwp  NT-0056-UserAPI���Ӳ�ѯ��������ǰ���ȵķ���
// 20090109 hwp	NT-0062:����ǰ�õĵ�¼Ӧ���з���˽��������
// 20090427 hwp  NT-0071:���Ự������ģʽ����ΪSlaveģʽ
// 20090510 xuzh  NT-0075��ǰ�ûָ����ͱ�������ʱ��
// 20090514 hwp  NT-0079������RspQryTopic��RspSubscribeTopicӦ�����
// 20110922 xuzh  �ͻ���ѯӦ������ת�����ô����Զ����ɸ�ֵ����
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
/**�յ��ͻ��˵�ҵ������ת����������
*@param XtpTid ת���������ϵ�XTP���ĵ�TID
*@param FtdFieldType �յ���FTD���ĵ�ҵ������������
*@param xtpFieldType ת���������ϵ�XTP���ĵ�ҵ������������
*@param CopyField FTD�����򿽱���XTP������Ĵ���
*/
#define FTD_PREPARE_FORWARD(XtpTid, FtdFieldType, XtpFieldType, CopyField)		\
	FtdFieldType ftdField;													\
	if(FTDC_GET_SINGLE_FIELD(pFTDCPackage, &ftdField) <= 0)					\
	{																		\
		/*û��ȡ�����������򣬶Ͽ�����*/									\
		pSession->Disconnect(MSG_FTDCERR_BADPACKAGE);						\
		return -1;															\
	}																		\
	/*ת�����ģ�������������*/												\
	m_pFrontForwarder->PrepareForward(&m_reqPackage, XtpTid,				\
	pSession->GetSessionID(), pFTDCPackage->GetRequestId());		\
	XtpFieldType xtpField;													\
	memset(&xtpField, 0, sizeof(xtpField));									\
	CopyField																\
	XTP_ADD_FIELD(&m_reqPackage, &xtpField);

/**�յ��ͻ��˵�ҵ������ת����������
*@param XtpTid ת���������ϵ�XTP���ĵ�TID
*@param FtdFieldType �յ���FTD���ĵ�ҵ������������
*@param xtpFieldType ת���������ϵ�XTP���ĵ�ҵ������������
*@param CopyField FTD�����򿽱���XTP������Ĵ���
*/
#define FTD_REQ_FORWARD(XtpTid, FtdFieldType, XtpFieldType, CopyField)			\
	{																			\
		FTD_PREPARE_FORWARD(XtpTid, FtdFieldType, XtpFieldType, CopyField);		\
		m_pFrontForwarder->ForwardTransaction(&m_reqPackage);					\
	}

/**�յ����ߵ�ҵ��Ӧ��ת�����Ի��� 
*@param Chain
*@param FtdTid ת�����ͻ��˵�FTD���ĵ�TID
*@param FtdFieldType ת�����ͻ��˵�FTD���ĵ�ҵ������������
*@param xtpFieldType �յ���XTP���ĵ�ҵ������������
*@param CopyField XTP�����򿽱���FTD������Ĵ���
*/
#define XTP_RSP_TO_DIALOG(FtdTid, FtdFieldType, XtpFieldType, CopyField)		\
		m_rspPackage.PreparePackage(FtdTid, pMessage->GetChain(), FTD_VERSION);	\
		m_rspPackage.SetRequestId(pMessage->GetRequestID());					\
		/*�ȴ�����Ӧ��Ϣ*/														\
		CRspInfoField rspInfoField;												\
		if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) > 0)					\
		{																		\
			CFTDRspInfoField ftdRspInfoField;									\
			CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);				\
			FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);					\
		}																		\
		/*����ҵ����Ϣ*/														\
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
		/*��ͻ��˳���Ӧ��*/													\
		FTDC_HEADER_DEBUG(&m_rspPackage);										\
		if (pSession != NULL)													\
		{																		\
			SendToDialogFlow(pSession, &m_rspPackage);							\
		}																		\

/**�յ����ߵ�ҵ��Ӧ��ת�����Ի�����˽���� 
*@param Chain
*@param FtdTid ת�����ͻ��˵�FTD���ĵ�TID
*@param FtdFieldType ת�����ͻ��˵�FTD���ĵ�ҵ������������
*@param xtpFieldType �յ���XTP���ĵ�ҵ������������
*@param CopyField XTP�����򿽱���FTD������Ĵ���
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

/**�յ����ߵ�ҵ��Ӧ��ת�����Ի��� 
*@param Chain
*@param FtdTid ת�����ͻ��˵�FTD���ĵ�TID
*@param PrivateFtdTid ��Ҫת����˽������FTD���ĵ�TID
*@param FtdFieldType ת�����ͻ��˵�FTD���ĵ�ҵ������������
*@param xtpFieldType �յ���XTP���ĵ�ҵ������������
*@param CopyField XTP�����򿽱���FTD������Ĵ���
*/
#define XTP_RSP_FORWARD(FtdTid, FtdFieldType, XtpFieldType, CopyField)\
	{																			\
		if (pSession == NULL)													\
		{																		\
			break;																\
		}																		\
		/*ת�����Ի���*/														\
		XTP_RSP_TO_DIALOG(FtdTid, FtdFieldType, XtpFieldType, CopyField)		\
	}

/**�յ����ߵĲ�ѯ�����ת�����ͻ��� 
*@param Chain
*@param FtdTid ת�����ͻ��˵�FTD���ĵ�TID
*@param FtdFieldType ת�����ͻ��˵�FTD���ĵ�ҵ������������
*@param xtpFieldType �յ���XTP���ĵ�ҵ������������
*@param CopyField XTP�����򿽱���FTD������Ĵ���
*/
#define XTP_QRY_FORWARD(FtdTid, FtdFieldType, XtpFieldType, CopyField)			\
	{																			\
		if (pSession == NULL)													\
		{																		\
			break;																\
		}																		\
		m_rspPackage.PreparePackage(FtdTid, pMessage->GetChain(), FTD_VERSION);	\
		m_rspPackage.SetRequestId(pMessage->GetRequestID());					\
		/*�ȴ�����Ӧ��Ϣ*/														\
		CRspInfoField rspInfoField;												\
		if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) > 0)					\
		{																		\
			CFTDRspInfoField ftdRspInfoField;									\
			CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);				\
			FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);					\
		}																		\
		/*����ҵ����Ϣ*/														\
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
		/*��ͻ��˳���Ӧ��*/													\
		FTDC_HEADER_DEBUG(&m_rspPackage);										\
		SendToQueryFlow(pSession, &m_rspPackage);								\
	}

/**�յ����ߵ�ҵ��֪ͨ��ת�����ͻ��˵�˽���� 
*@param FtdTid ת�����ͻ��˵�FTD���ĵ�TID
*@param FtdFieldType ת�����ͻ��˵�FTD���ĵ�ҵ������������
*@param xtpFieldType �յ���XTP���ĵ�ҵ������������
*@param CopyField XTP�����򿽱���FTD������Ĵ���
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

/**�յ����ߵ�ҵ��֪ͨ��ת�����ͻ��˵�˽���� 
*@param FtdTid ת�����ͻ��˵�FTD���ĵ�TID
*@param FtdFieldType ת�����ͻ��˵�FTD���ĵ�ҵ������������
*@param xtpFieldType �յ���XTP���ĵ�ҵ������������
*@param CopyField XTP�����򿽱���FTD������Ĵ���
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


/**�յ����ߵ�ҵ��֪ͨ��ת�����ͻ��˵Ĺ����� 
*@param FtdTid ת�����ͻ��˵�FTD���ĵ�TID
*@param FtdFieldType ת�����ͻ��˵�FTD���ĵ�ҵ������������
*@param xtpFieldType �յ���XTP���ĵ�ҵ������������
*@param CopyField XTP�����򿽱���FTD������Ĵ���
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

/**�յ��ͻ��˵Ĳ�ѯ����ת������ѯ����
*@param XtpTid ת���������ϵ�XTP���ĵ�TID
*@param FtdFieldType �յ���FTD���ĵ�ҵ������������
*@param xtpFieldType ת���������ϵ�XTP���ĵ�ҵ������������
*@param CopyField FTD�����򿽱���XTP������Ĵ���
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


//��ʼֵ
#define LampColor_White  0
//���Բ���
#define LampColor_Green  1
//�����У���û�н������
#define LampColor_Yellow 2
//��ɽ������
#define LampColor_Red    3
//��ʱȡ��������
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

	//�����ǰΪ��ɫ/��ɫ������Ϊ��ɫ�����Բ���
	if (LampColor_Red==m_nLampColor || LampColor_White==m_nLampColor)
		m_nLampColor=LampColor_Green;

	//���Ϊ��ɫ��ʾ�������δ��,��Ҫ�����Ƿ������־
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
		//������Ӧʱ��
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
		//���������Ӧ��־
		//REPORT_EVENT(LOG_WARNING, "LoopTime", "TotalOrderLoopTime=%d us,InnerLoopTime=%d us",m_CostTime,nInnerLat);
		//�����ر����ź��û������ӡ����־�� liumeng 20141117	
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
		m_nLampColor=LampColor_Red;
		//���������Ӧ��־
		//REPORT_EVENT(LOG_WARNING, "LoopTime", "OrderLoopTime=%d us",m_CostTime);
		//�����ر����ź��û������ӡ����־�� liumeng 20141117
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
	//дslog�ǳ�Ӱ�����ܣ�by wangwei ,20130110
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

//Add by zbz ������Ӧʱ��ɼ��Ķ�ʱ��
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

	pSession->SetCompressMethod(CRPCM_ZERO);		//����ѹ���㷨
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
	case TID_NtfSGEDeferRate://�������ӷ���֪ͨ
		XTP_PUBLIC_FORWARD(FTD_TID_RtnSGEDeferRate, CFTDSGEDeferRateField, CSGEDeferRateField,
		{
			CopySGEDeferRateEntity(&ftdField, &xtpField);
		});
		break;
	default:
		return false;
	}
	//NET_IO_LOG0("CFtdEngine::HandleNotify\n");
	//by wangwei,Ӱ��Ч��
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
	//����Ͷ����Ӧ��
	case TID_RspQryUserInvestor:
		XTP_QRY_FORWARD(FTD_TID_RspQryUserInvestor, CFTDRspUserInvestorField, CUserInvestorField,
		{
			CopyAPIUserInvestorEntity(&ftdField, &xtpField);
		});
		break;
	//Ͷ�����˻���ѯ
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
		
	//��������ѯ
	case TID_RspQryExchange:
		XTP_QRY_FORWARD(FTD_TID_RspQryExchange, CFTDRspExchangeField, CRspExchangeField,
		{
			CopyAPIExchangeEntity(&ftdField, &xtpField);
		});
		break;
		
	//Ͷ���ֲֲ߳�ѯ
	case TID_RspQryInvestorPosition:
		XTP_QRY_FORWARD(FTD_TID_RspQryInvestorPosition, CFTDRspInvestorPositionField, CInvestorPositionField,
		{
			CopyAPIInvestorPositionEntity(&ftdField, &xtpField);
		});
		break;
	
	//�������ʲ�ѯ
	case TID_RspQryInvestorFee:
		XTP_QRY_FORWARD(FTD_TID_RspQryInvestorFee, CFTDInvestorFeeField, CInvestorFeeField,
		{
			CopyAPIInvestorFeeEntity(&ftdField, &xtpField);
		});
		break;
		
	//�������ʲ�ѯ
	case TID_RspQryInvestorMargin:
		XTP_QRY_FORWARD(FTD_TID_RspQryInvestorMargin, CFTDInvestorMarginField, CInvestorMarginField,
		{
			CopyAPIInvestorMarginEntity(&ftdField, &xtpField);
		});
		break;
	//�������ӷ��ʲ�ѯ
	case TID_RspQrySGEDeferRate:
		XTP_QRY_FORWARD(FTD_TID_RspQrySGEDeferRate, CFTDSGEDeferRateField, CSGEDeferRateField,
		{
			CopySGEDeferRateEntity(&ftdField, &xtpField);
		});
		break;
	//�ͻ���Ȩ�������ʲ�ѯӦ��
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
	//û�����أ���ʱȡ���ô���
// 	CalcFlux(pSession, pFTDCPackage->Length());	//ͳ������

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
		//������Ϊ���ڴ����ݿ�ĵ���
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
		///xuzh��20070608�������߰汾��API������ֹ��¼
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
	//����Ͷ���߲�ѯ
	case FTD_TID_ReqQryUserInvestor:
		FTD_QUERY_FORWARD(TID_ReqQryUserInvestor, CFTDQryUserInvestorField, CQryUserInvestorField,
		{
			CopyAPIQryUserInvestorEntity(&xtpField, &ftdField);
			xtpField.LogUserID=UserID;
			xtpField.LogBrokerID=BrokerID;
		});
		break;
	//Ͷ�����˻���ѯ
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
	//��������ѯ
	case FTD_TID_ReqQryExchange :
		FTD_QUERY_FORWARD(TID_ReqQryExchange, CFTDQryExchangeField, CQryExchangeField,
		{
			CopyAPIQryExchangeEntity(&xtpField, &ftdField);
		});
		break;
	//Ͷ���ֲֲ߳�ѯ
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
	//add by cgm ��userapi����Ͷ���߳����
	case FTD_TID_ReqAccountDeposit:
		FTD_REQ_FORWARD(TID_DbInvestorAccountDeposit, CFTDReqAccountDepositField, CDbmtInvestorAccountDepositField,
		{
			CopyInvestorAccountDepositEntity(&xtpField, &ftdField);
		});
		break;
		//�������ӷ��ʲ�ѯ
	case FTD_TID_ReqQrySGEDeferRate:
		FTD_QUERY_FORWARD(TID_ReqQrySGEDeferRate, CFTDQrySGEDeferRateField, CQrySGEDeferRateField,
		{
			CopyQrySGEDeferRateEntity(&xtpField, &ftdField);
			m_reqPackage.SetSessionID(pSession->GetSessionID());
			m_reqPackage.SetRequestID(pFTDCPackage->GetRequestId());
		});
		break;
		//�ּ۲�ѯ
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
		//��Ȩ�������ʲ�ѯ
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
	//�յ��л�֪ͨ�󣬼�������˿ں�
	EnableListener(true);
}


int CFtdEngine::OnReqUserLogin(CFTDCPackage *pPackage, CFTDCSession *pSession)
{
	CFTDReqUserLoginField ftdReqUserLoginField;
	memset(&ftdReqUserLoginField, 0, sizeof(ftdReqUserLoginField));
	if(FTDC_GET_SINGLE_FIELD(pPackage, &ftdReqUserLoginField) <= 0)
	{
		//û��ȡ����¼�����򣬶Ͽ�����
		pSession->Disconnect(MSG_FTDCERR_BADPACKAGE);
		return -1;
	}
	char *pszCommonName = pSession->GetChannel()->GetRemoteCommonName();
	if (pszCommonName != NULL && strcmp(pszCommonName, ftdReqUserLoginField.UserID) != 0)
	{
		//�û�����֤���еĲ�һ��
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

	//���ͻ��˵Ķ�����Ϣ��������������¼�ɹ���ʹ��
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
	
	//ת�����ģ�������������
	m_pFrontForwarder->PrepareForward(&m_reqPackage, TID_ReqUserLogin,
		pSession->GetSessionID(), pPackage->GetRequestId());

	CUserLoginField userLoginField;
	userLoginField.IPAddress = pSession->GetChannel()->GetRemoteName();
	userLoginField.MaxOrderLocalID = 0;
	userLoginField.LoginTime = "";
	userLoginField.TradingSystemName = "";

	CopyLoginBaseEntity(&userLoginField,&ftdReqUserLoginField);
	///-----
	///	xuzh��20060223��������ʵ��Э���еİ汾�ţ������Լ��걨�İ汾��
	///-----
	char buffer[sizeof(CProtocolInfoType)];
	sprintf(buffer,"FTD %d",pPackage->GetVersion());
	userLoginField.ProtocolInfo=buffer;

	XTP_ADD_FIELD(&m_reqPackage, &userLoginField);
	
	m_pFrontForwarder->ForwardTransaction(&m_reqPackage);
	
	//���汾�Ự�İ汾
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
		//û��ȡ����Ӧ��Ϣ
		return ;
	}
	CFTDRspInfoField ftdRspInfoField;
	CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);

	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);
	
	CUserLoginField userLoginField;
	if(XTP_GET_SINGLE_FIELD(pMessage, &userLoginField) <= 0)
	{
		//û��ȡ����¼��
		return ;
	}
	//��֯FTDC���ĵĵ�¼Ӧ����
	
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
	if (rspInfoField.ErrorID == 0)		//��¼�ɹ�
	{
		CReadOnlyFlow *pPrivateFlow =  GetPrivateFlow(userLoginField.BrokerID);
		CReadOnlyFlow *pUserFlow = GetUserFlow(userLoginField.BrokerID,userLoginField.UserID);
		ftdRspUserLoginField.PrivateFlowSize = pPrivateFlow->GetCount();
		ftdRspUserLoginField.UserFlowSize = pUserFlow->GetCount();
	}
	
	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspUserLoginField);
	
	//�߶Ի����ᵼ�µ�¼Ӧ��󵽣�����ֱ�ӷ���
	pSession->SendRequestPackage(&m_rspPackage);
	if (rspInfoField.ErrorID != 0)		//��¼���ɹ�
	{
		return;
	}
	//�趨�Ự�����
	SetSessionOwner(pSession->GetSessionID(), userLoginField.UserID, userLoginField.BrokerID);
	SetSessionOwnerType(pSession->GetSessionID(), userLoginField.UserType);
	SetSessionMaxCommFlux(pSession->GetSessionID(), userLoginField.MaxCommFlux);

	CFTDDisseminationField fieldDissemination;
	//���ݻ���Ķ�����Ϣ�����췢�ַ��򣬷����ͻ��ˣ���������Ӧ����
	TFtdeDisseminationInfo *pFind = m_mapDisseminationInfo.Find(pSession->GetSessionID());
	if (pFind == NULL)	//û�ҵ�����Ķ�����Ϣ
	{
		return;
	}
	m_rspPackage.PreparePackage(FTD_TID_IntlRtnDissemination, FTDC_CHAIN_LAST, FTD_VERSION);
	int i = 0;
	for (i=0; i<pFind->nFieldCount; i++)
	{
		//����ͻ��˵Ľ������뽻�����治�������0��ʼ����
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
	//ֱ�ӷ��ͷַ���Ϣ֪ͨ
	pSession->SendRequestPackage(&m_rspPackage);
	//by wangwei ,����������������֪ͨ
/*	
	//��������������Ӧ��
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
		//û��ȡ����Ӧ��Ϣ
		return ;
	}
	CFTDRspInfoField ftdRspInfoField;
	CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);
	
	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);
	
	if (rspInfoField.ErrorID == 0)		//�ǳ��ɹ�
	{
		ClearSessionOwner(pSession->GetSessionID());

		CUserLogoutField userLogoutField;
		if(XTP_GET_SINGLE_FIELD(pMessage, &userLogoutField) <= 0)
		{
			//û��ȡ���ǳ���
			return ;
		}
		//��֯FTDC���ĵĵǳ�Ӧ����
		CFTDRspUserLogoutField ftdRspUserLogoutField;
		ftdRspUserLogoutField.UserID = userLogoutField.UserID;
		ftdRspUserLogoutField.UserID = userLogoutField.UserID;
		
		FTDC_ADD_FIELD(&m_rspPackage, &ftdRspUserLogoutField);
	}

	//��ͻ��˳���Ӧ��
	SendToDialogFlow(pSession, &m_rspPackage);
	
}

void CFtdEngine::OnNtfDelUserSession(CXTPPackage *pMessage)
{
	//��Ҫ��д wangwei 	
	CUserSessionField fieldUserSession;
	if(XTP_GET_SINGLE_FIELD(pMessage, &fieldUserSession) <= 0)
	{
		//û��ȡ���Ự��
		return ;
	}
/*
	if (fieldUserSession.FrontID != m_pFrontForwarder->GetFrontID())
	{
		//���Ǹ����ѵģ�ʲôҲ����
		return;
	}
*/
	CSession *pSession = GetSession(fieldUserSession.SessionID);
	if (pSession == NULL)
	{
		//�Ự�Ѿ�û���ˣ�ʲôҲ����
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
	//��д wangwei
	
	CFTDRspInfoField ftdRspInfoField;
	ftdRspInfoField.ErrorID = 0;
	ftdRspInfoField.ErrorMsg = "��ȷ";
	m_rspPackage.PrepareResponse(pPackage, FTD_TID_RspSubscribeTopic,FTDC_CHAIN_LAST, FTD_VERSION);
	
	CFTDDisseminationField fieldDissemination;
	if (FTDC_GET_SINGLE_FIELD(pPackage, &fieldDissemination) <= 0)
	{
		return 0;
	}

	TFtdeDisseminationInfo *pFind = m_mapDisseminationInfo.Find(pSession->GetSessionID());
	if (pFind == NULL)	//û�ҵ�����Ķ�����Ϣ
	{
		return 0;
	}

	int nSubStartId = fieldDissemination.SequenceNo;
	//����ͻ��˵Ľ������뽻�����治�������0��ʼ����
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
		ftdRspInfoField.ErrorMsg = "��Ч�ĻỰ�����ⲻ����";
	}	
	fieldDissemination.SequenceNo = nPubStartId;
	FTDC_ADD_FIELD(&m_rspPackage, &fieldDissemination);
	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);
	//����Ӧ��
	SendToDialogFlow(pSession, &m_rspPackage);


	if (ftdRspInfoField.ErrorID == 0)
	{
		m_rspPackage.PreparePackage(FTD_TID_IntlRtnDissemination, 
			FTDC_CHAIN_LAST, FTD_VERSION);
		FTDC_ADD_FIELD(&m_rspPackage, &fieldDissemination);
		//ֱ�ӷ��ͷַ���Ϣ֪ͨ
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

	//������������ͨ���жϻỰ��ɣ���Ҫ���¶���
	//Ŀǰֻ��˽�����͹�����
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
		//��Ӧ���������·��,wangwei, bCheckDataCenter=false
		nPubStartId = nBorkenSeqNo;
	}
	else
	{
		nPubStartId = nSubStartId;
	}
	
	//������ʼ�����Ч���ж�,�����ʼ���С��0�ҷ�-1,������
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
	//��¼��ǰ˽�����͹������Ŀ���
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
	//��д wangwei
	
	TFrontSessionInfo *pSessionInfo = GetSessionInfo(pSession->GetSessionID());
	if (pSessionInfo == NULL)
	{
		return 0;
	}
	
	CFTDRspInfoField ftdRspInfoField;
	ftdRspInfoField.ErrorID = 0;
	ftdRspInfoField.ErrorMsg = "��ȷ";
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

	//����Ӧ��
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