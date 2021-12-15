/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file LockFileFlow.h
///@brief定义了类CLockFileFlow
///@history 
///20130703	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#if !defined(LOCK_FILE_FLOW_H_20121118)
#define LOCK_FILE_FLOW_H_20121118

#include "CachedFileFlow.h"
#include "Mutex.h"

class CLockFileFlow : public CCachedFileFlow  
{
public:
	CLockFileFlow(const char *pszFlowName, const char *pszFlowPath, bool bReuse, int nMaxObjects, int nDataBlockSize);
	virtual int Append(void *pObject, int length);
	virtual ~CLockFileFlow();
private:
#ifdef WIN32
	CMutex m_Mutex;
#else
    CSpinLock m_Mutex;
#endif

};

#endif
