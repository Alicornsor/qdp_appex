/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CServiceTimer.h
///@brief��������CServiceTimer
///@history 
///20060213	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CSERVICETIMER_H
#define CSERVICETIMER_H

#include "databaseData.h"

/////////////////////////////////////////////////////////////////////////
///CServiceTimer��һ���ṩϵͳ����Ķ�ʱ��������ʱ��ͬ�������������ǡ��
///��׼���ʱ���źţ���ҵ��ϵͳʹ��
///@author	xuzh
///@version	1.0,20060114
/////////////////////////////////////////////////////////////////////////
class CServiceTimer: public CCurrentTimeCommitTrigger
{
public:
	///���캯��
	///@param	everyMillisec	ÿ�����ٺ��뷢��һ������ʱ�䴥��
	CServiceTimer(int everyMillisec);
	
	///ȷ�ϸ��º󴥷�
	///@param	pCurrentTime	��ˢ�µ�CCurrentTime
	///@param	poldCurrentTime	ԭ����ֵ
	virtual void commitUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pOldCurrentTime);
	
	///�������ʱ�䴥�����¼�
	///@param	pServiceTime	����ķ���ʱ��
	virtual void onTime(CWriteableCurrentTime *pServiceTime)=0;
private:
	///��һ���ڵ�ʱ������Ϊ������
	///@param	currTime	��ǰʱ��
	///@param	currMillisec	��ǰ����
	///@param	����Ϊ�ĺ�����
	int getMillisec(CReadOnlyTimeType &currTime, CReadOnlyMillisecType &currMillisec);
	
	///������ĺ�����ת��Ϊʱ��
	///@param	pCurrTime	���صĵ�ǰʱ��
	///@param	pMillisec	���صĵ�ǰ����
	///@param	Ҫ����ĺ�����
	void getTime(CTimeType *pCurrTime, CMillisecType *pMillisec, int millisec);

	///ÿ�����ٺ��뷢��һ������ʱ�䴥��
	int m_everyMillisec;
};

#endif
