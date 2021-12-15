/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CInitServiceCheckImpl.h
///@brief	��������CInitServiceCheckImpl
///@history 
///20060313	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CINITSERVICECHECKIMPL_H
#define CINITSERVICECHECKIMPL_H

#include "CInitServiceImpl.h"

/////////////////////////////////////////////////////////////////////////
///CInitServiceCheckImpl��һ������һ���Լ������ݳ�ʼ����ʵ��
///@author	���һ�
///@version	1.0, 20130122
/////////////////////////////////////////////////////////////////////////
class CInitServiceCheckImpl: public CInitServiceImpl
{
public:
	///���캯��
	///@param	pDB	��ʵ��ʹ�õ��ڴ����ݿ�
	///@param	pErrorEngine	���ڱ���Ĵ�������
	///@param	pConfig	ʹ�õ������ļ�
	CInitServiceCheckImpl(CMemoryDB *pDB, CErrorEngine *pErrorEngine, CConfig *pConfig,CHandleNotify *pHandleNotify);

protected:
	///����������ͬ������
	///@param	pTransaction	���������ڵ�����
	virtual void afterDataSync(CTransaction *pTransaction);
	
	int errorCount;
	CConfig *m_Config;
	FILE *output;
};

#endif
