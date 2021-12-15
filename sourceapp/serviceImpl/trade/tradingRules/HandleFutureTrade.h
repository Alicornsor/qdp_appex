/////////////////////////////////////////////////////////////////////////
///@system ǰ�÷��ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file HandleFutureTrade.h
///@brief�������� CHandleFutureTrade
///@history 
///20130503	longqy@cffex.net		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CHandleFutureTrade_H
#define CHandleFutureTrade_H

#include "HandleTrade.h"
#include "baseAlgorithms.h"

/////////////////////////////////////////////////////////////////////////
///CHandleFutureTrade ��һ�������ָ�ڻ������ɽ�����
///@author	xuzh
///@version	1.0,20130503
/////////////////////////////////////////////////////////////////////////
class CHandleFutureTrade : public CHandleTrade
{
public:
	///���캯��
	///@param	pDB	��ʵ��ʹ�õ��ڴ����ݿ�
	///@param	pErrorEngine	���ڱ���Ĵ�������
	CHandleFutureTrade(CMemoryDB *pDB, CErrorEngine *pErrorEngine,CConfig *pConfig,CFlow* pTradeResult);
   ~CHandleFutureTrade();
protected:

	CBaseAlgorithms baseAlgorithms;
};
#endif
