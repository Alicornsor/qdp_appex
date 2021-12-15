/////////////////////////////////////////////////////////////////////////
///@system 前置风控系统
///@company 上海量投网络科技有限公司
///@file CInitServiceCheckImpl.h
///@brief	实现了类CInitServiceCheckImpl
///@history 
///20060313	xuzh		创建该文件
///20081028	xuzh		完善了对初始化数据中价格绑定的检查（NT-0053）
///20081203	xuzh		调整日初检查时对会员客户表的检查方法（NT-0057）
///20081205	xuzh		check中增加了对会员没有订阅行情的检查（NT-0059）
///20090118	xuzh		调整日初数据检查时增加对昨结算价的检查（NT-0064）
///20091203	xuzh		改变长操作的处理模式（NT-0091）
// 20110725 xuzh    保证金设置到客户，支持投机套保
// 20110922 xuzh    687客户限仓明细表增加HedgeFlag
///20120420 xuzh 交易编码权限上场指令添加
/////////////////////////////////////////////////////////////////////////

#include "CInitServiceCheckImpl.h"
//#include "databaseData.h"
//#include "tradingTools.h"
//#include "monitorIndex.h"

CInitServiceCheckImpl::CInitServiceCheckImpl(CMemoryDB *pDB, CErrorEngine *pErrorEngine, CConfig *pConfig,CHandleNotify *pHandleNotify)
	:CInitServiceImpl(pDB,pErrorEngine,pConfig,pHandleNotify)
{
	m_Config=pConfig;

}

void CInitServiceCheckImpl::afterDataSync(CTransaction *pTransaction)
{
	///先叫用父类的数据方法
	CInitServiceImpl::afterDataSync(pTransaction);
}
