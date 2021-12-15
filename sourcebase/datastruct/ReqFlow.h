/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file ReqFlow.h
///@brief定义了类CReqFlow
///@history 
///20130703	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#if !defined(REQ_FLOW_H_20121226)
#define REQ_FLOW_H_20121226

///在反演的时候，不能往ReqFlow中追加历史的报单信息，因此重载出这个类，增加Append的开关,在Redo之后再打开开关
///by wangwei,20121226
#include "CachedFlow.h"

class CReqFlow : public CCachedFlow  
{
public:
	CReqFlow(bool bSyncFlag, int nMaxObjects, int nDataBlockSize);
	~CReqFlow();
	virtual void SetAppendFlag(bool bAppendFlag);
	virtual bool GetAppendFlag();
	virtual int Append(void *pObject, int length);	
private:
	bool m_bAppendFlag;///可以追加包的标志
};

#endif
