#if !defined(KERNEL_FRONT_H_20121119)
#define KERNEL_FRONT_H_20121119

#include "ExCachedFlow.h"
#include "LockFileFlow.h"
#include "FtdEngine.h"
#include "FrontTerminal.h"
#include "FrontForwarder.h"
#include "SelectReactor.h"
#include "CConfig.h"
#include "BaseExchApi.h"
#include "XtpPackageDesc.h"


const int FRONT_TIME_SYNC_TIMER_ID=0x000009600;//ǰ�ö�ʱ��
const int FRONT_TIME_SYNC_TIMER_FREQUENCY=1000;//����

class CFrontTimeSyncTimer : public CEventHandler
{
public:
	CFrontTimeSyncTimer(CReactor *pReactor,CFlow* pFlow):CEventHandler(pReactor)
	{
		m_pLockFlow=pFlow;
		m_pNotifyPackage = CXTPPackage::CreatePackage(1000);
		this->SetTimer(FRONT_TIME_SYNC_TIMER_ID,FRONT_TIME_SYNC_TIMER_FREQUENCY);
	}
protected:
	virtual void OnTimer(int nIDEvent)
	{
//		printf("OnTimer\n");
		switch(nIDEvent)
		{
			//��ʱ��Ϣ���ӵ�kernel��������
			case FRONT_TIME_SYNC_TIMER_ID:
			{
				SyncTime();
				CCurrentTimeField timeField;
				timeField.CurrDate = "20150508";//������ʱ��
				time_t dwCurrTime = (time_t)m_nCurrTime;
				strftime(m_timeBuffer, sizeof(timeField.CurrTime),"%H:%M:%S",localtime(&dwCurrTime));
				timeField.CurrTime=m_timeBuffer;
				timeField.CurrMillisec = m_nCurrMilTime;

				m_pNotifyPackage->PreparePublish(TID_NtfTimeSync);
				XTP_ADD_FIELD(m_pNotifyPackage, &timeField);
				m_pNotifyPackage->MakePackage();				
				m_pLockFlow->Append(m_pNotifyPackage->Address(), m_pNotifyPackage->Length());	
				break;
			}	
		}
	}	
private:
	void SyncTime()
	{
#ifdef WIN32	
		struct _timeb timebuffer;
		_ftime( &timebuffer );
		m_nCurrTime = (DWORD)timebuffer.time;	
		m_nCurrMilTime = timebuffer.millitm;
		m_nCurrClock = m_nCurrTime*1000 + timebuffer.millitm;
#else
		struct timeval timeout;
		gettimeofday(&timeout, 0);
		m_nCurrTime = timeout.tv_sec;	
		m_nCurrMilTime = timeout.tv_usec/1000;
		m_nCurrClock = m_nCurrTime*1000 + timeout.tv_usec/1000;
#endif
	}
private:
	CXTPPackage *m_pNotifyPackage;//ʱ�Ӱ�
	char m_timeBuffer[20];//��ŵ�ǰʱ��	
	CFlow* m_pLockFlow;//���ļ�
	DWORD m_nCurrTime;//��ǰϵͳʱ����
	DWORD m_nCurrMilTime;//��ǰϵͳʱ�����
	DWORD m_nCurrClock;//��ǰ�δ���
};


class CKernelFront:public CBaseExchApi,public CSelectReactor
{
public:
	//pTradeResult��ǰ�õ�����,pTSeries��ǰ�õ����
	CKernelFront(CFlow* pTradeResult,CFlow* pSlogResult, int nLifeCycleID,CConfig * pConfig);	
	virtual ~CKernelFront();
	virtual bool InitInstance();
	void FrontStartWork();
	bool Init();
	virtual bool HandleOtherTask();
	virtual void StartTimer();	
	void InitFront(vector<char *> pFrontAddressVect,vector<char *> pQueryAddressVect,char *pFlowPath);
private:
	CFlow* m_pTradeResult;
	CFlow* m_pSlogResult;
	int m_nLifeCycleID;//�������ں�	
	CConfig	*m_pConfig;	//�����ļ�

	CXTPPackage m_rspPackage;
	vector<CFibClientApi *> m_pClientApiVect;
	
	CFrontTerminal *m_pFrontTerminal;
	

	vector<CFrontForwarder *> m_pFrontForwarderVect;
	vector<CFtdEngine * > m_pFtdEngineVect;	
	vector<CReactor *> m_ReactorVect;
	
	CFrontTimeSyncTimer* m_pFrontTimeSyncTimer;//��ʱ���������pTSeries
	DWORD m_dwFrontID;
	CFlowReader m_ResultReader;
	int m_nOpenFront_Count;//�򿪶˿ڵĴ���,wangwei,20121230

	//ǰ�ù���ģʽ,shepf,20130520
	bool m_bSingleFrontMode;
	char m_shmAddr[200];
	vector<char *> m_pFrontAddressVect;
};

#endif
