/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file HandleFutureOrder.h
///@brief�������� CHandleFutureOrder �����ദ���ڻ�����Ķ���
///@history 
///20130502	longqy@cffex.net		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CHandleFutureOrder_H
#define CHandleFutureOrder_H

#include "HandleOrder.h"


/////////////////////////////////////////////////////////////////////////
///CHandleFutureOrder ��һ�������ڻ��ཻ�׶������࣬�Ǵ������������
///@author	xuzh
///@version	1.0,20130502
/////////////////////////////////////////////////////////////////////////
class CHandleFutureOrder : public CHandleOrder
{
public:
	///���캯��
	///@param	pDB	��ʵ��ʹ�õ��ڴ����ݿ�
	///@param	pErrorEngine	���ڱ���Ĵ�������
	CHandleFutureOrder(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult);
   ~CHandleFutureOrder();

protected:
	
};

#endif
