// XTPSubEndPoint.cpp: implementation of the CXTPSubEndPoint class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "XTPSubEndPoint.h"
#include "XTPPackage.h"

const DWORD NAK_TIMEOUT	= 40;				//����. ��һ��NAK���ʱ��,�Ժ�ʱ�ӱ�
const DWORD RECV_HEARTBEAT_TIMEOUT	= 1500;	//����. ����������ʱʱ��
//const DWORD ACK_TIMEOUT = 200;				//����. ACK���ʱ��
const DWORD ACK_TIMEOUT = 200;				//����. ACK���ʱ��



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXTPSubEndPoint::CXTPSubEndPoint(CSubscriber *pSubscriber, DWORD dwSubscriberID, CXTPSubHelper *pControlHelper)
:m_orderingQ(4000)
{
	m_pSubscriber = pSubscriber;
	m_nDisorderClock = 0;
	m_nDeliveryClock = 0;
	m_nNakInterval = NAK_TIMEOUT;
	m_pControlHelper = pControlHelper;
	m_wSubCommPhaseNo = pSubscriber->GetCommPhaseNo();
	m_dwSubscriberID = dwSubscriberID;
	m_dwLastAckClock = 0;
	m_dwGroupID = 0;
	m_orderingQ.SetStartIndex(m_pSubscriber->GetReceivedCount() + 1);
	//add by shepf �����ü�������ʼ���� 1
	m_available=1;
}

CXTPSubEndPoint::~CXTPSubEndPoint()
{
}

int CXTPSubEndPoint::Delivery(CXTPPackage *pXTPPackage)
{
	//modify by shepf�ж�m_pSubscriber�Ƿ�Ϊ�գ���ΪResetSubscriber�ӿڻ��ÿո�ָ��
	if (m_available ==0)
	{
		return 0;
	}
	//����һ��������ע���ڶ��SubEndPoint�����������ͬһ��ŵı��ģ�
	//���δ��������ߣ������Ҫ�Ա��Ľ��й��ˡ�
	//����������ĵ����С�ڵ��ڶ��������յ��ı������������ñ���
	if (pXTPPackage->GetXTPHeader()->CommPhaseNo != m_pSubscriber->GetCommPhaseNo() ||
		pXTPPackage->GetXTPHeader()->SequenceNo <= m_pSubscriber->GetReceivedCount())
		return 0;

	//�Զ����ߵĲ�������ͬ��
	m_pSubscriber->EnterCritical();
	//if (pXTPPackage->GetXTPHeader()->CommPhaseNo == m_pSubscriber->GetCommPhaseNo()&&
	//	pXTPPackage->GetXTPHeader()->SequenceNo > m_pSubscriber->GetReceivedCount())
	//{
	if (pXTPPackage->GetXTPHeader()->CommPhaseNo == m_pSubscriber->GetCommPhaseNo() &&
		pXTPPackage->GetXTPHeader()->SequenceNo == m_pSubscriber->GetReceivedCount()+1)
	{
		m_pSubscriber->HandleMessage(pXTPPackage);
	}
	//}
	m_pSubscriber->LeaveCritical();

	return 0;
}

int CXTPSubEndPoint::HandlePackage(CXTPPackage *pXTPPackage, DWORD nCurrClock)
{
	if (pXTPPackage->GetXTPHeader()->CommPhaseNo < m_wSubCommPhaseNo)
	{
		//�յ���СͨѶ�׶α�ŵı��ģ�ֱ�Ӷ���
		return 0;
	}
	
	if (pXTPPackage->GetXTPHeader()->CommPhaseNo > m_wSubCommPhaseNo)
	{
		if (m_pSubscriber->CheckCommPhaseNo())
		{
			//���ڲ����ͨѶ�׶���ŵĶ����ߣ�
			//���ͨѶ�׶���Ų�һ����ֱ�Ӷ���
			return 0;
		}
		//���ڲ����ͨѶ�׶���ŵĶ����ߣ�
		//���ͨѶ�׶���ű仯������»���ķ�����ͨѶ�׶���ţ�������Ŷ�
		SetSubCommPhaseNo(pXTPPackage->GetXTPHeader()->CommPhaseNo);
		m_orderingQ.Clear();
	}
	
	//DEBUG_LOG2("[%d] [%d]\n",pXTPPackage->GetXTPHeader()->SequenceNo ,(DWORD)m_orderingQ.GetStartIndex());
	if (pXTPPackage->GetXTPHeader()->SequenceNo < (DWORD)m_orderingQ.GetStartIndex())
	{
		return 0;
	}

	if (pXTPPackage->GetXTPHeader()->SequenceNo != (DWORD)m_orderingQ.GetStartIndex())
	{
		if (m_nDisorderClock == 0 && m_dwGroupID == pXTPPackage->GetGroupID())
		{
			m_nDisorderClock = nCurrClock;
			m_nNakInterval = NAK_TIMEOUT;
			m_pControlHelper->SendNak(GetSubjectID(), 
				m_wSubCommPhaseNo, 
				m_dwSubscriberID,
				m_orderingQ.GetStartIndex() - 1);

		}
		pXTPPackage->Push(XTPHLEN);
		m_orderingQ.EnQueue(pXTPPackage->GetXTPHeader()->SequenceNo,
			pXTPPackage->Address(), pXTPPackage->Length());
		pXTPPackage->Pop(XTPHLEN);

		return 0;
	}

	m_dwGroupID = pXTPPackage->GetGroupID();
	Delivery(pXTPPackage);
	m_orderingQ.DeQueue();
	int nPackageLen = 0;
	void *pPackageData = NULL;
	while ((pPackageData = m_orderingQ.QueueFront(nPackageLen)) != NULL)
	{
		//�����
		CPackageBuffer packageBuffer((char *)pPackageData, nPackageLen);
		pXTPPackage->AttachBuffer(&packageBuffer);
		pXTPPackage->ValidPackage();

		//���ϴ���
		Delivery(pXTPPackage);

		//������
		m_orderingQ.DeQueue();
		pXTPPackage->BufRelease();
	}

//	if (m_orderingQ.IsEmpty())
	{
		m_nDeliveryClock = nCurrClock;
		m_nDisorderClock = 0;
	}
	return 0;
}

void CXTPSubEndPoint::OnTimer(DWORD nCurrClock)
{	
	//��ʱ��δ�յ���������������Ϣ��׼������NAK
	if (nCurrClock - m_nDeliveryClock > RECV_HEARTBEAT_TIMEOUT)
	{
		if (m_nDisorderClock == 0)
		{
			m_nDisorderClock = nCurrClock;	
			m_nNakInterval = NAK_TIMEOUT;
		}
	}
	if (m_nDisorderClock != 0)
	{
		DWORD nClock = nCurrClock - m_nDisorderClock;
		if (nClock > m_nNakInterval)
		{
//			DEBUG_LOG3("Send Nak %d %u %u\n", GetSubjectID(),m_orderingQ.GetStartIndex(),
//				nClock);
			m_pControlHelper->SendNak(GetSubjectID(), 
				m_wSubCommPhaseNo, 
				m_dwSubscriberID,
				m_orderingQ.GetStartIndex() - 1);
			m_nDisorderClock = nCurrClock;	
			if (m_nNakInterval < 16*NAK_TIMEOUT)
			{
				m_nNakInterval *= 2;
			}
		}
	}
	//���ڷ���ACK
	if (nCurrClock-m_dwLastAckClock > ACK_TIMEOUT)
	{
		m_pControlHelper->SendAck(GetSubjectID(), 
				m_wSubCommPhaseNo, 
				m_dwSubscriberID,
				m_orderingQ.GetStartIndex() - 1);
		m_dwLastAckClock = nCurrClock;
	}
}

void CXTPSubEndPoint::OnHeartBeat(WORD nCommPhaseNo, int nSeqNo, DWORD nCurrClock)
{
	if (nCommPhaseNo == m_wSubCommPhaseNo && nSeqNo == m_orderingQ.GetStartIndex()-1)
	{
		//�Ѿ���ȫ�����е���Ϣ
		m_nDeliveryClock = nCurrClock;
		m_nDisorderClock = 0;
	}
}

void CXTPSubEndPoint::SetSubCommPhaseNo(WORD wCommPhaseNo)
{
	if (m_wSubCommPhaseNo != wCommPhaseNo)
	{
		m_orderingQ.Clear();
		m_wSubCommPhaseNo = wCommPhaseNo;
	}

	//��ֹ���߳��¶Զ�����ͬʱ����
	m_pSubscriber->EnterCritical();
	m_pSubscriber->SetCommPhaseNo(wCommPhaseNo);	
	m_pSubscriber->LeaveCritical();

	m_nNakInterval = NAK_TIMEOUT;
}

