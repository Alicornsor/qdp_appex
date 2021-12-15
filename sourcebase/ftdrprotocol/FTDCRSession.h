#if !defined(FTDC_RSESSION_H)
#define FTDC_RSESSION_H

#include "FTDCSession.h"

#define XMP_READ  1
#define XMP_WRITE 2

class CExXMPProtocol : public CProtocol
{
public:
	/**构造函数
	* @param pReactor 指向运行引擎的指针
	* @param pBelow 下层协议的指针
	*/
	CExXMPProtocol(CReactor *pReactor, int type = XMP_READ);
	/**析构函数
	*/
	virtual ~CExXMPProtocol();

	/**加入XMP报头并传至下层协议
	* @param pPackage 上层层协议下传的包
	* @return 0   成功
	* @return <>0 失败
	*/
	virtual int Push(CPackage *pPackage, CProtocol *pUpper);

	void EnableHeartbeat(bool bEnable);
	
	void SetHeartbeatTimeout(DWORD dwReadTimeout);

	void SetWriteTimeout(CXMPPackage *pPackage);

	DWORD GetTimeout();
protected:	
	/**记录当前收到包的时间，判断是否XMP包，并上传
	* @param pPackage 下层协议上传的包
	* @return 0   成功
	* @return <>0 失败
	*/
	virtual int Pop(CPackage *pPackage);

	/**收到一个错误的数据包时调用
	* @param pPackage 错误的数据包
	* @return 0   成功
	* @return <>0 失败
	*/
	virtual int OnRecvErrorPackage(CPackage *pPackage);

	/**处理定时操作，由CReactor调用。检查如果读超时，则通知上层协议。
	* 检查如果写超时，则发送心跳报文。
	* @param nIDEvent 当自身为定时器时，在定时器链表定时器标识   
	*/
	virtual void OnTimer(int nIDEvent);

	int SendHeartbeat();

	/**生成并发送设置心跳超时报文
	* @return >0   成功
	* @return <=0  失败 
	*/
	int SendWriteTimeout(DWORD dwWriteTimeout);
protected:
	bool m_bHeartEnable;		/**< 是否接收/发送心跳 */
	DWORD m_LastReadTime;		/**< 最后收包时间　*/
	DWORD m_dwReadTimeout;		/**< 接收心跳的超时时间 */

	DWORD m_LastWriteTime;		/**< 最后收包时间　*/
	DWORD m_dwWriteTimeout;		/**< 发出心跳的时间间隔 */
	int  m_Type;
};
class CExXMPSession : public CSession
{
public:
	CExXMPSession(CReactor *pReactor,CChannel *pChannel, int type = XMP_READ);
	virtual ~CExXMPSession();

	void SetHeartbeatTimeout(DWORD dwReadTimeout);


	void EnableHeartbeat(bool bEnable);

	DWORD GetTimeout();
protected:
	CExXMPProtocol *m_pExXMPProtocol;	/**< 容器内的第二层协议(从下部开始)*/
};

class CFTDCRSession;

class CFTDCRSessionCallback
{
public:
	virtual int HandlePackage(CFTDCPackage *pFTDCPackage, CFTDCRSession *pSession) = 0;
};


class CFTDCRSession : public CProtocolCallback , public CExXMPSession
{
public:
	/**构造函数，完成协议栈的构造
	* @param pReactor   运行引擎
	* @param pChannel   一个TcpChannel
	*/ 	
	CFTDCRSession(CReactor *pReactor,CChannel *pChannel, int type = XMP_READ);
	
	/**析构函数，释放可控资源
	*/
	virtual ~CFTDCRSession();
	
	/**处理一条消息
	* @param nEventID 消息ID
	* @param dwParam 第一个参数
	* @param pParam 第二个参数
	* @return 处理结果
	*/
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);


	/**获取读、写socket，供select使用
	* @param pReadId   输出参数，返回读所使用的socket，为0表示不需要读
	* @param pWriteId  输出参数，返回写所使用的socket，为0表示不需要写
	* @remark 在这里将发布的主题的数据包传递到最下层协议
	*/
	virtual void GetIds(int *pReadId, int *pWriteId);

	virtual int HandlePackage(CPackage *pPackage,CProtocol *pProtocol);
	
	void RegisterPackageHandler(CFTDCRSessionCallback *pPackageHandler);
	
	CFTDCPackage *CreatePackage();

	void SendRequestPackage(CFTDCPackage *pPackage);

	void Publish(CReadOnlyFlow *pFlow, WORD wSequenceSeries, int nStartId);

	virtual void Disconnect(int nErrorCode);

	void ResetSession(DWORD nSessionID);

	virtual void Closeconnect(int nErrorCode);
protected:
	CFTDCProtocol *m_pFTDCProtocol;		/**< FTDC协议对象*/
	CCompressProtocol *m_pCRPProtocol;	/**< CRP协议对象*/
	CFTDCRSessionCallback *m_pPackageHandler;
	///-----
	///	xuzh，20060223：增加了对FTD协议的版本设置
	///-----
	BYTE m_version;
	int m_type;
};

#endif
