// FlowSubscriber.h: interface for the CFlowSubscriber class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLOWSUBSCRIBER_H__3456D5BD_8E16_40BC_8BD4_E1A82BE75BF3__INCLUDED_)
#define AFX_FLOWSUBSCRIBER_H__3456D5BD_8E16_40BC_8BD4_E1A82BE75BF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Subscriber.h"
#include "Flow.h"

/**CFlowSubscriber��һ������Ķ����ߡ���������һ���������յ���
*  ��Ϣ�������С�
*/
class CFlowSubscriber : public CSubscriber  
{
public:
	/**���캯��
	*@param pFlow �����յ�����Ϣ��Flow
	*@param nSubscribeSubjectID Ҫ���ĵ��������
	*/
	CFlowSubscriber(CFlow *pFlow, DWORD nSubscribeSubjectID)
	{
		m_pFlow = pFlow;
		m_nSubjectID = nSubscribeSubjectID;
	}

	virtual ~CFlowSubscriber(){};
	
	/**��ȡ�����ߵ�ͨѶ�׶α��
	*@return �����ߵ�ͨѶ�׶α��
	*/
	virtual WORD GetCommPhaseNo()
	{
		return m_pFlow->GetCommPhaseNo();
	}

	/**���ö����ߵ�ͨѶ�׶α��
	*@param  nCommPhaseNo Ҫ���õĶ����ߵ�ͨѶ�׶α��
	*/
	virtual void SetCommPhaseNo(WORD nCommPhaseNo)
	{
		m_pFlow->SetCommPhaseNo(nCommPhaseNo);
	}

	/**��ȡ���ĵ��������
	*@return ���ĵ��������
	*/
	virtual DWORD GetSubjectID()
	{
		return m_nSubjectID;
	}

	/**��ȡ���յ�����Ϣ����
	*@return ���յ�����Ϣ����
	*/
	virtual DWORD GetReceivedCount()
	{
		return m_pFlow->GetCount();
	}

	/**�����յ���һ����Ϣ
	*@param pMessage �յ���һ����Ϣ
	*/
	virtual void HandleMessage(CXTPPackage *pMessage)
	{
		pMessage->Push(XTPHLEN);
		m_pFlow->Append(pMessage->Address(), pMessage->Length());
		pMessage->Pop(XTPHLEN);
	}

protected:
	CFlow *m_pFlow;						/**< �����յ�����Ϣ��Flow */
	DWORD m_nSubjectID;					/**< Ҫ���ĵ�������� */
};

#endif // !defined(AFX_FLOWSUBSCRIBER_H__3456D5BD_8E16_40BC_8BD4_E1A82BE75BF3__INCLUDED_)
