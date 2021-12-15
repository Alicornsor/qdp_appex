#ifndef __SUBSCRIBER_H_
#define __SUBSCRIBER_H_

#include "XTPPackage.h"

/** 订阅者接口，需要订阅的应用继承该类。一个订阅者只能订阅一个主题。
* 订阅者必须指明通讯阶段序号、已接收消息个数，用于可靠传输
* 当指定主题的消息抵达时，订阅驱动器将调用HandleMessage方法，用户可
* 以重载该方法，对消息进行处理。
*/
class CSubscriber
{
public:

	virtual ~CSubscriber(){};

	/**获取订阅者的通讯阶段编号
	*@return 订阅者的通讯阶段编号
	*/
	virtual WORD GetCommPhaseNo() = 0;
	
	/**设置订阅者的通讯阶段编号
	*@param  nCommPhaseNo 要设置的订阅者的通讯阶段编号
	*/
	virtual void SetCommPhaseNo(WORD nCommPhaseNo) = 0;

	/**获取订阅的主题代码
	*@return 订阅的主题代码
	*/
	virtual DWORD GetSubjectID() = 0;

	/**获取已收到的消息个数
	*@return 已收到的消息个数
	*/
	virtual DWORD GetReceivedCount() = 0;

	/**处理收到的一个消息
	*@param pMessage 收到的一个消息
	*/
	virtual void HandleMessage(CXTPPackage *pMessage) = 0;

	/**是否检查通讯阶段编号的一致性
	*@return true 检查，false 不检查
	*@remark 若检查通讯阶段编号的一致性，则当收到的消息的通讯阶段编号与订阅者
	*@remark 的通讯阶段编号不一致时，该消息将被丢弃。
	*@remark 若不检查通讯阶段编号的一致性，则当收到的消息的通讯阶段编号与订阅者
	*@remark 的通讯阶段编号不一致时，消息仍被提交，且订阅者的SetCommPhaseNo方法
	*@remark 会被调用。
	*/
	virtual bool CheckCommPhaseNo()
	{
		return false;
	}

	/**进入临界区
	*/
	virtual void EnterCritical() {}
	
	/**离开临界区
	*/
	virtual void LeaveCritical() {}

};

#endif

