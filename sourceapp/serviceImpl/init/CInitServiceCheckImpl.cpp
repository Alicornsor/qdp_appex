/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CInitServiceCheckImpl.h
///@brief	ʵ������CInitServiceCheckImpl
///@history 
///20060313	xuzh		�������ļ�
///20081028	xuzh		�����˶Գ�ʼ�������м۸�󶨵ļ�飨NT-0053��
///20081203	xuzh		�����ճ����ʱ�Ի�Ա�ͻ���ļ�鷽����NT-0057��
///20081205	xuzh		check�������˶Ի�Աû�ж�������ļ�飨NT-0059��
///20090118	xuzh		�����ճ����ݼ��ʱ���Ӷ������۵ļ�飨NT-0064��
///20091203	xuzh		�ı䳤�����Ĵ���ģʽ��NT-0091��
// 20110725 xuzh    ��֤�����õ��ͻ���֧��Ͷ���ױ�
// 20110922 xuzh    687�ͻ��޲���ϸ������HedgeFlag
///20120420 xuzh ���ױ���Ȩ���ϳ�ָ�����
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
	///�Ƚ��ø�������ݷ���
	CInitServiceImpl::afterDataSync(pTransaction);
}
