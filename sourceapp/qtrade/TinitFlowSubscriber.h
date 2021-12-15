/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file TinitFlowSubscriber.h
///@brief��������CTinitFlowSubscriber
///@history 
///20130703	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#if !defined(TINIT_FLOW_SUBSCRIBER_20121123)
#define TINIT_FLOW_SUBSCRIBER_20121123

#include "Subscriber.h"

class CTinitFlowSubscriber : public CSubscriber  
{
public:

	CTinitFlowSubscriber(CFlow *pFlow, DWORD nSubscribeSubjectID)
	{
		m_pFlow = pFlow;
		m_nSubjectID = nSubscribeSubjectID;
		m_nCommPhaseNo=0;
		m_nTinitFlowCount=0;
	}

	virtual WORD GetCommPhaseNo()
	{
		return m_nCommPhaseNo;
	}

	virtual void SetCommPhaseNo(WORD nCommPhaseNo)
	{
		m_nCommPhaseNo=nCommPhaseNo;
	}

	virtual DWORD GetSubjectID()
	{
		return m_nSubjectID;
	}

	virtual DWORD GetReceivedCount()
	{
		return m_nTinitFlowCount;
	}

	virtual void SetReceivedCount(int nTinitFlowCount)
	{
		m_nTinitFlowCount=nTinitFlowCount;
	}


	/**�����յ���һ����Ϣ
	*@param pMessage �յ���һ����Ϣ
	*/
	virtual void HandleMessage(CXTPPackage *pMessage)
	{
		pMessage->Push(XTPHLEN);
		m_pFlow->Append(pMessage->Address(), pMessage->Length());
		pMessage->Pop(XTPHLEN);
		
		m_nTinitFlowCount++;
	}

protected:
	CFlow *m_pFlow;						/**< �����յ�����Ϣ��Flow */
	DWORD m_nSubjectID;					/**< Ҫ���ĵ�������� */
	int m_nTinitFlowCount;//tinit��������
	int m_nCommPhaseNo;//ͨѶ�׶κ�
};

#endif // !defined(TINIT_FLOW_SUBSCRIBER_20121123)
