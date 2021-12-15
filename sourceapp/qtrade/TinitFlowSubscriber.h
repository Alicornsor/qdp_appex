/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file TinitFlowSubscriber.h
///@brief定义了类CTinitFlowSubscriber
///@history 
///20130703	hwp		创建该文件
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


	/**处理收到的一个消息
	*@param pMessage 收到的一个消息
	*/
	virtual void HandleMessage(CXTPPackage *pMessage)
	{
		pMessage->Push(XTPHLEN);
		m_pFlow->Append(pMessage->Address(), pMessage->Length());
		pMessage->Pop(XTPHLEN);
		
		m_nTinitFlowCount++;
	}

protected:
	CFlow *m_pFlow;						/**< 保存收到的消息的Flow */
	DWORD m_nSubjectID;					/**< 要订阅的主题代码 */
	int m_nTinitFlowCount;//tinit流包计数
	int m_nCommPhaseNo;//通讯阶段号
};

#endif // !defined(TINIT_FLOW_SUBSCRIBER_20121123)
