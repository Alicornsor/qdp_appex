// Session.h: interface for the CSession class .
//
// 20080620 hwp 增加检查是否写繁忙的接口IsChannelWriteBusy
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SESSION_H__D0D24001_7352_4285_9A26_A5DAC8C09F03__INCLUDED_)
#define AFX_SESSION_H__D0D24001_7352_4285_9A26_A5DAC8C09F03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EventHandler.h"
#include "ChannelProtocol.h"

class CSession;

class CSessionCallback
{
public:
	virtual void OnSessionConnected(CSession *pSession) = 0;
	virtual void OnSessionDisconnected(CSession *pSession, int nReason) = 0;
	virtual void OnSessionWarning(CSession *pSession, int nReason, int nParam) = 0;
	virtual ~CSessionCallback(){};
};


/**是一个存放协议栈的容器，容器的最下层协议是CSession。
该类不能实例化，一般作为面向TCP连接的协议栈的基类 */
class  CSession : public CEventHandler  
{
public:
	/**构造函数
	* @param pReactor   运行引擎
	* @param pChannel   最下层协议绑定的Channel
	* @param MaxPackageSize  上层协议包的最大长度 
	*/ 	
	CSession(CReactor *pReactor,CChannel *pChannel,int MaxPackageSize);

	/**析构函数
	*/
	virtual ~CSession();
	
	inline DWORD GetSessionID();
//	inline long GetSessionID();
	/* add by zbz 20141120 为防止不同的线程中SessionID相同
	* @param nID 改变ID的高位
	*/
	void ReSetSessionID(int nThreadID);

	/**当网络有可读数据包时被调用
	* @return 0   成功
	* @return <>0 失败
	*/
	virtual int HandleInput();
	
	/**当Reactor发现需要向网络发送数据包时被调用
	* @return >=0   成功
	* @return <0    失败
	*/
	virtual int HandleOutput();
	
	/**处理一条消息
	* @param nEventID 消息ID
	* @param dwParam 第一个参数
	* @param pParam 第二个参数
	* @return 处理结果
	*/
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);

	/**取最下层协议绑定的Channel
	* @return 最下层协议绑定的Channel
	*/
	inline CChannel *GetChannel();

	/**断开网络连接
	* @param ErrorCode  断路的原因
	*/
	virtual void Disconnect(int nErrorCode);

	/**获取读、写socket，供select使用
	* @param pReadId   输出参数，返回读所使用的socket，为0表示不需要读
	* @param pWriteId  输出参数，返回写所使用的socket，为0表示不需要写 
	*/
	virtual void GetIds(int *pReadId, int *pWriteId);

	inline void RegisterSessionCallback(CSessionCallback *pSessionCallback);

	/**挂起/恢复读操作
	*@param bSuspend true 挂起读操作    false恢复读操作 
	*/
	void SuspendRead(bool bSuspend);

	/**打开Channel日志文件
	*@param pszPath 日志文件路径
	*@param pszFileName 日志文件名
	*@return true 成功
	*@return false 失败
	*/
	bool OpenChannelLogFile(const char *pszPath, const char *pszFileName);

	/**关闭Channel日志文件
	*/
	void CloseChannelLogFile();

	/**检查Channel是否有要写出的内容
	* @return true 有要写出的内容, false 没有要写出的内容
	*/
	bool IsChannelWriteBusy();
protected:	
	/**网络断路消息处理程序，每当发现网络断路时叫用此函数
	* @param ErrorCode  断路的原因
	*/
	virtual void OnChannelLost(int nErrorCode);
protected:
	DWORD m_nSessionID;
//	long m_nSessionID;

	CChannel *m_pChannel;		/**< 容器捆绑的Channel */
	CChannelProtocol *m_pChannelProtocol;	/**< 容器内的底层协议 */
	CSessionCallback *m_pSessionCallback;

	bool m_bSuspendRead;
};

inline CChannel *CSession::GetChannel()
{
	return m_pChannel;
}

inline void CSession::RegisterSessionCallback(CSessionCallback *pSessionCallback)
{
	m_pSessionCallback = pSessionCallback;
}

inline DWORD CSession::GetSessionID()
//inline long CSession::GetSessionID()
{
	return m_nSessionID;
}

#endif // !defined(AFX_SESSION_H__D0D24001_7352_4285_9A26_A5DAC8C09F03__INCLUDED_)
