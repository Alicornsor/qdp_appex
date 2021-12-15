/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file CInitServiceCheckImpl.h
///@brief	定义了类CInitServiceCheckImpl
///@history 
///20060313	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CINITSERVICECHECKIMPL_H
#define CINITSERVICECHECKIMPL_H

#include "CInitServiceImpl.h"

/////////////////////////////////////////////////////////////////////////
///CInitServiceCheckImpl是一个进行一致性检查的数据初始化的实现
///@author	徐忠华
///@version	1.0, 20130122
/////////////////////////////////////////////////////////////////////////
class CInitServiceCheckImpl: public CInitServiceImpl
{
public:
	///构造函数
	///@param	pDB	本实现使用的内存数据库
	///@param	pErrorEngine	用于报错的错误引擎
	///@param	pConfig	使用的配置文件
	CInitServiceCheckImpl(CMemoryDB *pDB, CErrorEngine *pErrorEngine, CConfig *pConfig,CHandleNotify *pHandleNotify);

protected:
	///结算组数据同步后处理
	///@param	pTransaction	本处理属于的事务
	virtual void afterDataSync(CTransaction *pTransaction);
	
	int errorCount;
	CConfig *m_Config;
	FILE *output;
};

#endif
