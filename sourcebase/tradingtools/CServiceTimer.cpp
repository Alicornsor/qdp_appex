/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CServiceTimer.cpp
///@brief实现了类CServiceTimer
///@history 
///20060213	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CServiceTimer.h"

CServiceTimer::CServiceTimer(int everyMillisec)
{
	m_everyMillisec=everyMillisec;
}
	
void CServiceTimer::commitUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pOldCurrentTime)
{
	int nNextClick = getMillisec(pOldCurrentTime->CurrTime,pOldCurrentTime->CurrMillisec)/
		m_everyMillisec+1;
	int nTargetClick = getMillisec(pCurrentTime->CurrTime,pCurrentTime->CurrMillisec)/
		m_everyMillisec;
	while (nNextClick <= nTargetClick)
	{
		CWriteableCurrentTime serviceTime;
		
		serviceTime.CurrDate=pCurrentTime->CurrDate;
		getTime(&serviceTime.CurrTime,&serviceTime.CurrMillisec,nNextClick*m_everyMillisec);
		
		onTime(&serviceTime);

		nNextClick++;
	}
}
	
int CServiceTimer::getMillisec(CReadOnlyTimeType &currTime, CReadOnlyMillisecType &currMillisec)
{
	const char *pTime=currTime;
	int hour=(pTime[0]-'0')*10+(pTime[1]-'0');
	int minute=(pTime[3]-'0')*10+(pTime[4]-'0');
	int second=(pTime[6]-'0')*10+(pTime[7]-'0');
	return ((hour*60+minute)*60+second)*1000+currMillisec;
}
	
void CServiceTimer::getTime(CTimeType *pCurrTime, CMillisecType *pMillisec, int millisec)
{
	int remain;
	char buffer[9];
	
	*pMillisec=millisec%1000;
	remain=millisec/1000;
	int second=remain%60;
	remain/=60;
	int minute=remain%60;
	int hour=remain/60;
	sprintf(buffer,"%02d:%02d:%02d",hour,minute,second);
	*pCurrTime=buffer;
}
