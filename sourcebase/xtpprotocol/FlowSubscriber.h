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

/**CFlowSubscriber是一种主题的订阅者。它关联着一个流，将收到的
*  消息记入流中。
*/
class CFlowSubscriber : public CSubscriber  
{
public:
	/**构造函数
	*@param pFlow 保存收到的消息的Flow
	*@param nSubscribeSubjectID 要订阅的主题代码
	*/
	CFlowSubscriber(CFlow *pFlow, DWORD nSubscribeSubjectID)
	{
		m_pFlow = pFlow;
		m_nSubjectID = nSubscribeSubjectID;
	}

	virtual ~CFlowSubscriber(){};
	
	/**获取订阅者的通讯阶段编号
	*@return 订阅者的通讯阶段编号
	*/
	virtual WORD GetCommPhaseNo()
	{
		return m_pFlow->GetCommPhaseNo();
	}

	/**设置订阅者的通讯阶段编号
	*@param  nCommPhaseNo 要设置的订阅者的通讯阶段编号
	*/
	virtual void SetCommPhaseNo(WORD nCommPhaseNo)
	{
		m_pFlow->SetCommPhaseNo(nCommPhaseNo);
	}

	/**获取订阅的主题代码
	*@return 订阅的主题代码
	*/
	virtual DWORD GetSubjectID()
	{
		return m_nSubjectID;
	}

	/**获取已收到的消息个数
	*@return 已收到的消息个数
	*/
	virtual DWORD GetReceivedCount()
	{
		return m_pFlow->GetCount();
	}

	/**处理收到的一个消息
	*@param pMessage 收到的一个消息
	*/
	virtual void HandleMessage(CXTPPackage *pMessage)
	{
		pMessage->Push(XTPHLEN);
		m_pFlow->Append(pMessage->Address(), pMessage->Length());
		pMessage->Pop(XTPHLEN);
	}

protected:
	CFlow *m_pFlow;						/**< 保存收到的消息的Flow */
	DWORD m_nSubjectID;					/**< 要订阅的主题代码 */
};

#endif // !defined(AFX_FLOWSUBSCRIBER_H__3456D5BD_8E16_40BC_8BD4_E1A82BE75BF3__INCLUDED_)
