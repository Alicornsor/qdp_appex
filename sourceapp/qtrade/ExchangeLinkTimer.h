//////////////////////////////////////////////////////////////////////////
// 文件: ExchangeLinkTimer.h
// 功能: 定义了报盘定时连接功能
// 历史: 20171225 chengm 
//////////////////////////////////////////////////////////////////////////
#if !defined(EXCHANGELINKTIMER_API_MANAGER_H_20121119)
#define EXCHANGELINKTIMER_API_MANAGER_H_20121119

#include "CachedFlow.h"
#include "platform.h"
#include "CConfig.h"
#include "XTPPackage.h"
#include "FlowReader.h"
#include "ReqFlow.h"
#include "monitorIndex.h"
#include "errorDefine.h"
#include "XtpData.h"
#include "BaseExchApi.h"
#include "ExchangeLinkManager.h"
#include "SelectReactor.h"

#define LINKTIMER_ID 3000

class CLinkReactor : public CSelectReactor
{
public:
	class CLinkTimer : public CEventHandler
	{
	public:
		CLinkTimer(CReactor *pReactor,CExchangeLinkManager *pLinkManger, CBaseExchApi **pExchApiArryMap,int loopInterval):CEventHandler(pReactor)
		{
			m_pLinkManger = pLinkManger;
			m_pExchApiArryMap = pExchApiArryMap;
			m_nLoopInterval = loopInterval;
//			SetTimer(LINKTIMER_ID, loopInterval);		
		}
		
		~CLinkTimer()
		{
			KillTimer(LINKTIMER_ID);
		}

		void EnableTimer()
		{
			SetTimer(LINKTIMER_ID, m_nLoopInterval);
		}
		
		virtual void OnTimer(int nIDEvent)
		{
			switch(nIDEvent)
			{
			case LINKTIMER_ID:
				{
					Run(); 
					break;
				}
			default:
				break;
			}
		}
		
		void Run()
		{
			for (int j=2; j<=m_pLinkManger->m_iMaxAPIID; j++)
			{
				CBaseExchApi *pBaseApi = m_pExchApiArryMap[j];
				if(pBaseApi == NULL || !pBaseApi->m_bCheckLinked || pBaseApi->GetStatus())
				{
					continue;
				}
				pBaseApi->StartWork();
			}
		}
		
	private:
		CExchangeLinkManager *m_pLinkManger;
		CBaseExchApi		 **m_pExchApiArryMap;
		int					  m_nLoopInterval;
	};
	
	CLinkReactor(CExchangeLinkManager *pLinkManger, CBaseExchApi **pExchApiArryMap,int interval):CSelectReactor()
	{
		m_pLinkTimer = new CLinkTimer(this,pLinkManger,pExchApiArryMap,interval);
	}
	
	~CLinkReactor()
	{
		delete m_pLinkTimer;
	}
	
	void PostLinkTimer()
	{
		PostEvent(NULL,LINKTIMER_ID,0,NULL);
	}
	
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam)
	{
		if (nEventID == LINKTIMER_ID && IsCurrentThread()) 
		{
			m_pLinkTimer->EnableTimer();
		}
		return CSelectReactor::HandleEvent(nEventID,dwParam,pParam);
	}
private:
	CLinkTimer *m_pLinkTimer;
	int    m_nInvteval;
};


#endif
