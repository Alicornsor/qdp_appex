// XTPProtocl.h: interface for the CXTPProtocl class .
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XTPPROTOCOL_H__C5C04921_6D0B_11D7_BB64_444553540000__INCLUDED_)
#define AFX_XTPPROTOCOL_H__C5C04921_6D0B_11D7_BB64_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Protocol.h"
#include "XTPPackage.h"
#include "HashMap.h"
#include "XTPPubEndPoint.h"
#include "XTPSubEndPoint.h"

#define MSG_XTPERR_BADPACKAGE		0x3001

/**协议栈容器的第第三层协议，主要对XTP包的处理
*/
class  CXTPProtocol : public CProtocol  
{
public:
	/**构造函数
	* @param pReactor 指向运行引擎的指针
	* @param pPubHelper    下层协议的指针
	* @param nActiveId 对下层协议而言，本层协议的协议Id
	*/
	CXTPProtocol(CReactor *pReactor, CXTPPubHelper *pPubHelper, CXTPSubHelper *pSubHelper);
	
	/**析构函数
	*/
	virtual ~CXTPProtocol();

	/**将包传送到合适的上层协议
	* @param pPackage 需要上传的包的指针
	* @return 0   成功
	* @return <>0 失败
	*/
	virtual int Pop(CPackage *pPackage);
	
	/**处理定时操作，由CReactor调用
	* @param nIDEvent 定时器事件标识   
	*/
	virtual void OnTimer(int nIDEvent);

	/**收到一个错误的数据包时调用
	* @param pPackage 错误的数据包
	* @return 0   成功
	* @return <>0 失败
	*/
	virtual int OnRecvErrorPackage(CPackage *pPackage);

	void OnHeartBeat(DWORD nSubjectID, WORD nCommPhaseNo, int nSeqNo);
	
	void Publish(CReadOnlyFlow *pFlow, DWORD nSubjectID, WORD nCommPhaseNo, 
		DWORD dwSubscriberID, int nStartId);
	void UnPublish(DWORD nSubjectID);
	void RegisterSubscriber(CSubscriber *pSubscriber, DWORD dwSubscriberID);
	void UnRegisterSubscriber(CSubscriber *pSubscriber);
	void OnAck(DWORD dwSubscriberID, DWORD dwSubjectID, 
		int nStartId, WORD wCommPhaseNo);
	void SetSubCommPhaseNo(WORD nCommPhaseNo);
	
	/**add by zbz 此处主要功能是由核心线程触发一次发布动作
	* @param pReadId   输出参数，返回读所使用的socket，为0表示不需要读
	* @param pWriteId  输出参数，返回写所使用的socket，为0表示不需要写 
	*/
	virtual void GetIds(int *pReadId, int *pWriteId);
protected:
	
private:
	CXTPSubEndPoint *GetSubEndPoint(DWORD nSubjectID);
	CXTPPubEndPoint *GetPubEndPoint(DWORD nSubjectID);

private:
	typedef CHashMap<DWORD, CXTPSubEndPoint *, HashInt> CSubEndPointMap;
	CSubEndPointMap m_mapSubEndPoint;

	typedef CHashMap<DWORD, CXTPPubEndPoint *, HashInt> CPubEndPointMap;
	CPubEndPointMap m_mapPubEndPoint;

	CXTPPubHelper *m_pPubHelper;
	CXTPSubHelper *m_pSubHelper;
	
	WORD m_nSubCommPhaseNo;
};

#endif // !defined(AFX_XTPPROTOCOL_H__C5C04921_6D0B_11D7_BB64_444553540000__INCLUDED_)
