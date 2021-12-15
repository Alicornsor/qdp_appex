// FTDCProtocl.h: interface for the CFTDCProtocl class .
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTDCPROTOCOL_H__C5C04921_6D0B_11D7_BB64_444553540000__INCLUDED_)
#define AFX_FTDCPROTOCOL_H__C5C04921_6D0B_11D7_BB64_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Protocol.h"
#include "FTDCPackage.h"
#include "HashMap.h"
#include "FTDCPubEndPoint.h"
#include "FTDCSubEndPoint.h"

#define MSG_FTDCERR_BADPACKAGE		0xA001

/**协议栈容器的第第三层协议，主要对FTDC包的处理
*/
class  CFTDCProtocol : public CProtocol  
{
public:
	/**构造函数
	* @param pReactor 指向运行引擎的指针
	* @param pBelow    下层协议的指针
	* @param nActiveId 对下层协议而言，本层协议的协议Id
	*/
	CFTDCProtocol(CReactor *pReactor);
	
	/**析构函数
	*/
	virtual ~CFTDCProtocol();

	virtual int Pop(CPackage *pPackage);
	
	/**将各主题的报文发送出去
	*/
	void PublishSend();

	/**收到一个错误的数据包时调用
	* @param pPackage 错误的数据包
	* @return 0   成功
	* @return <>0 失败
	*/
	virtual int OnRecvErrorPackage(CPackage *pPackage);

	void Publish(CReadOnlyFlow *pFlow, WORD nSequenceSeries, int nStartId);
	void UnPublish(WORD nSequenceSeries);
	void RegisterSubscriber(CFTDCSubscriber *pSubscriber);
	void UnRegisterSubscriber(CFTDCSubscriber *pSubscriber);
	void SetCommPhaseNo(WORD wCommPhaseNo);

	void Clear();
	
private:
	CFTDCSubEndPoint *GetSubEndPoint(WORD nSequenceSeries);
	CFTDCPubEndPoint *GetPubEndPoint(WORD nSequenceSeries);

private:
	typedef CHashMap<WORD, CFTDCSubEndPoint *, HashInt> CSubEndPointMap;
	CSubEndPointMap m_mapSubEndPoint;

	typedef CHashMap<WORD, CFTDCPubEndPoint *, HashInt> CPubEndPointMap;
	CPubEndPointMap m_mapPubEndPoint;
};

#endif // !defined(AFX_FTDCPROTOCOL_H__C5C04921_6D0B_11D7_BB64_444553540000__INCLUDED_)
