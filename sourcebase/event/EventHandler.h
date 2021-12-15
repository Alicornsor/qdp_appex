// EventHandler.h: interface for the CEventHandler class .
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTHANDLER_H__D0DAF147_AD16_4C5C_9393_78E357E0A93E__INCLUDED_)
#define AFX_EVENTHANDLER_H__D0DAF147_AD16_4C5C_9393_78E357E0A93E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class  CReactor;
class  CEventHandler;

struct CEvent
{
	CEventHandler *pEventHandler;
	int nEventID;
	DWORD dwParam;
	void *pParam;
	void *pAdd;
};

/**
* CEventHandler是一个抽象的可以运行的对象。它是各种协议、控制器、定时器的抽象基类。
* 有两类事件可触发运行，一种为IO操作，另一种为定时操作，一个CEventHandler对象只有
* 注册到CReactor才能获得核心引擎的调用
*/
class  CEventHandler  
{
public:
	/**构造函数
	* @param pReactor 当前运行对象归属的引擎 
	*/
	CEventHandler(CReactor *pReactor);
	
	/**析构函数
	*/
	virtual ~CEventHandler();
	
	/**处理IO操作的读操作，由CReactor调用
	* @return 保留
	*/
	virtual int HandleInput(){return 0;};
	
	/**处理IO操作的写操作，由CReactor调用
	* @return 保留 
	*/
	virtual int HandleOutput(){return 0;};
 	
	/**处理定时操作，由CReactor调用
	* @param nIDEvent 定时器标识   
	*/
	virtual void OnTimer(int nIDEvent){};
	
	/*向CEventHandler对象发送异步事件
	* @param nEventID 事件ID
	* @param dwParam 双字型参数
	* @param pParam 无符号指针型参数
	*/
	bool PostEvent(int nEventID, DWORD dwParam, void *pParam);

	/*向CEventHandler对象发送同步事件
	* @param nEventID 事件ID
	* @param dwParam 双字型参数
	* @param pParam 无符号指针型参数
	*/
	int SendEvent(int nEventID, DWORD dwParam, void *pParam);

	/**处理一条事件
	* @param nEventID 事件ID
	* @param dwParam 第一个参数
	* @param pParam 第二个参数
	* @return 处理结果
	*/
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam){return 0;};

	/**获取读、写socket，供select使用
	* @param pReadId   输出参数，返回读所使用的socket，为0表示不需要读
	* @param pWriteId  输出参数，返回写所使用的socket，为0表示不需要写 
	*/
	virtual void GetIds(int *pReadId, int *pWriteId){};
protected:
	/**设置定时器
	* @param nIDEvent 定时器标识(不能为0)
	* @param nElapse 定时周期(秒)
	*/
	void SetTimer(int nIDEvent, int nElapse);

	/**取消定时器
	* @param nIDEvent 定时器标识(0表示取消该对象的所有定时器)
	*/
	void KillTimer(int nIDEvent);

protected:
	CReactor *m_pReactor;    /**<当前对象归属引擎的指针*/
};

#endif // !defined(AFX_EVENTHANDLER_H__D0DAF147_AD16_4C5C_9393_78E357E0A93E__INCLUDED_)
