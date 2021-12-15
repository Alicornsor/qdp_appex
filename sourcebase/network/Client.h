// Client.h: interface for the CClient class .
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENT_H__FE5CED61_6EC3_11D7_BB64_444553540000__INCLUDED_)
#define AFX_CLIENT_H__FE5CED61_6EC3_11D7_BB64_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Channel.h"
#include "ServiceName.h"

/**CClinet时一个抽象的未完成连接的通讯客户端。实现了一个基于有连接通讯的客户端基本功能。
*不同类型的网络通讯需要继承这个类，以实其真正功能。
*/
class  CClientBase
{
public:
	/**构造函数，完成初始化
	*/
	CClientBase();
	
	/**析构函数
	*/
	virtual ~CClientBase();
	
	/**连接指定的服务。如果连不上，也应当立即返回，不能在此长时间睡眠。本方法将
	*使用ConnectImpl完成真正的连接操作
	* @param   pName	要连接的服务名
	* @return  如果连接上，则返回由其产生的CChannel，如果连接不上，则返回NULL如果连接不上，则可以使用GetErrorEvent获取其错误信息
	*/
	virtual CChannel *Connect(CServiceName *pName)=0;
	
	/**获取最近的错误信息
	* @return	最近的错误信息。如果最近的操作获得成功，则返回NULL
	*/
	inline char *GetErrorMsg(void);
protected:

	/**设置最近发生的错误信息
	* @param  msg  错误信息
	*/
	inline void SetErrorMsg(char *msg);
private:
	
	char *m_pErrorMsg;		/**<存储最近发生的错误信息*/
};

inline char *CClientBase::GetErrorMsg(void)
{
	return m_pErrorMsg;
}

inline void CClientBase::SetErrorMsg(char *msg)
{
	m_pErrorMsg=msg;
}

#endif // !defined(AFX_CLIENT_H__FE5CED61_6EC3_11D7_BB64_444553540000__INCLUDED_)
