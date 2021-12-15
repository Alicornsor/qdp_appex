// FTDCSession.h: interface for the CFTDCSession class .
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTDCSESSION_H__88022E6A_66E9_46E0_B66F_8F73B23CDEFA__INCLUDED_)
#define AFX_FTDCSESSION_H__88022E6A_66E9_46E0_B66F_8F73B23CDEFA__INCLUDED_

#include "EventHandler.h"
#include "XMPSession.h"
#include "XMPProtocol.h"
#include "CompressProtocol.h"
#include "FTDCProtocol.h"
#include "FlowReader.h"
#include "FtdPackageDesc.h"

class CFTDCSession;

class CFTDCSessionCallback
{
public:
	virtual int HandlePackage(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession) = 0;
};

/**是一个存放协议栈的容器，是基于IO处理的EventHandler类，一般是由ListenCtrl
*创建，它必须注册到一个Reactor。容器的底部捆绑在一个TcpChannel上，容器内的
*协议只有通过容器的才能得到读写操作 */
class CFTDCSession : public CProtocolCallback, public CXMPSession
{
public:
	/**构造函数，完成协议栈的构造
	* @param pReactor   运行引擎
	* @param pChannel   一个TcpChannel
	*/ 	
	CFTDCSession(CReactor *pReactor,CChannel *pChannel);
	
	/**析构函数，释放可控资源
	*/
	virtual ~CFTDCSession();
	
	/**处理一条消息
	* @param nEventID 消息ID
	* @param dwParam 第一个参数
	* @param pParam 第二个参数
	* @return 处理结果
	*/
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);

	virtual int HandlePackage(CPackage *pPackage,CProtocol *pProtocol);

	/**获取读、写socket，供select使用
	* @param pReadId   输出参数，返回读所使用的socket，为0表示不需要读
	* @param pWriteId  输出参数，返回写所使用的socket，为0表示不需要写
	* @remark 在这里将发布的主题的数据包传递到最下层协议
	*/
	virtual void GetIds(int *pReadId, int *pWriteId);
	
	void RegisterPackageHandler(CFTDCSessionCallback *pPackageHandler);

	void Publish(CReadOnlyFlow *pFlow, WORD wSequenceSeries, int nStartId);
	void UnPublish(WORD wSequenceSeries);
	void RegisterSubscriber(CFTDCSubscriber *pSubscriber);
	void UnRegisterSubscriber(CFTDCSubscriber *pSubscriber);
	
	CFTDCPackage *CreatePackage();
	
	void SendRequestPackage(CFTDCPackage *pPackage);
	
	void SetCommPhaseNo(WORD wCommPhaseNo);	

	virtual void Disconnect(int nErrorCode);

	/**设置针对FTDC的压缩算法
	*@param chCompressMethod 压缩算法代码，0表示不压缩
	*/
	void SetCompressMethod(BYTE chCompressMethod);
	
	/**设置本会话的版本
	*@param	version	版本号
	*/
	void SetVersion(BYTE version);
	
	/**获取本会话的版本
	*@return	本会话的版本
	*/
	BYTE GetVersion(void);

	void CreatSubInstrument();
	bool InsertInstrumentID(DWORD instrumentIDCount,CInstrumentIDType instrumentID);
	bool DeleteInstrumentID(DWORD instrumentIDCount);
	void DisplayInstrumentID();
	void RspAllSubInstrumentID(DWORD RspType);

	CSubInstrumentMap *m_pmapSubInstrument;	
	
protected:
	CFTDCProtocol *m_pFTDCProtocol;		/**< FTDC协议对象*/
	CCompressProtocol *m_pCRPProtocol;	/**< CRP协议对象*/
	CFTDCSessionCallback *m_pPackageHandler;
	///-----
	///	xuzh，20060223：增加了对FTD协议的版本设置
	///-----
	BYTE m_version;
	
	//add by jinpc 20160928 订阅完成后不再全部推送所有的合约，只推送订阅的合约。
	vector<CInstrumentIDType> v_subinstrumet;
};

#endif // !defined(AFX_FTDCSESSION_H__88022E6A_66E9_46E0_B66F_8F73B23CDEFA__INCLUDED_)
