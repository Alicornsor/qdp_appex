/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file ReqFlow.h
///@brief��������CReqFlow
///@history 
///20130703	hwp		�������ļ�
/////////////////////////////////////////////////////////////////////////

#if !defined(REQ_FLOW_H_20121226)
#define REQ_FLOW_H_20121226

///�ڷ��ݵ�ʱ�򣬲�����ReqFlow��׷����ʷ�ı�����Ϣ��������س�����࣬����Append�Ŀ���,��Redo֮���ٴ򿪿���
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
	bool m_bAppendFlag;///����׷�Ӱ��ı�־
};

#endif
