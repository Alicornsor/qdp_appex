// FTDCPubEndPoint.cpp: implementation of the CFTDCPubEndPoint class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "FTDCPubEndPoint.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#ifdef PERFORMTEST
	#ifndef WIN32
	struct timeval m_nBeginTime; 
	#else
	struct _timeb  m_nBeginTime;
	#endif
	bool bLOOPTIMEOUT;
#endif

CFTDCPubEndPoint::CFTDCPubEndPoint(CReadOnlyFlow *pFlow, WORD nSequenceSeries, int nStartId,
								 CProtocol *pSendProtocol,CSubInstrumentMap * pmapSubInstrument)
{
	m_pFlow = pFlow;
	m_nSequenceSeries = nSequenceSeries;
	m_pSendProtocol = pSendProtocol;
	//by caojl 20140409 解决合约订阅超过113程序崩溃缺陷 API需要重新编译
	m_SendPackage.ConstructAllocate(FTDC_PACKAGE_MAX_SIZE+FTDCHLEN, 1000);
	m_flowReader.AttachFlow(pFlow, nStartId);
	m_mapSubInstrument = pmapSubInstrument;
}

CFTDCPubEndPoint::~CFTDCPubEndPoint()
{
}

CPackage *CFTDCPubEndPoint::GetNextDataPackage()
{
	m_SendPackage.AllocateMax();
	if(m_flowReader.GetNext(&m_SendPackage))
	{
		//需要将包头解出来
		TFTDCHeader  *pHeader = m_SendPackage.GetFTDCHeader();
//		printf("%d \n",m_SendPackage.GetInstrumentIDCount());
		
		if(m_mapSubInstrument!=NULL)
		{
// 			CSubInstrumentMap::iterator iterj = m_mapSubInstrument->Begin();		
// 			while (!iterj.IsEnd())
// 			{
// 				printf("%s->%d",iterj.GetKey(),(*iterj).InstrumentID.getValue());
// 				iterj++;
// 			}
			//如果找到合约，则发送包，如果没有，不发送
			CInstrumentIDType *iter1=m_mapSubInstrument->Find(0);
			if (  iter1 == NULL )
			{
				if (INT_MAX == m_SendPackage.GetInstrumentIDCount())
				{
				} 
				else
				{
					CInstrumentIDType *iter = m_mapSubInstrument->Find(m_SendPackage.GetInstrumentIDCount());
					if(iter == NULL)
					{
						//printf("%d 不发送! \n ",m_SendPackage.GetInstrumentIDCount());
						return NULL;
					}
				}
				
			}
			//printf("%d -> %s发送! \n ",m_SendPackage.GetInstrumentIDCount(),iter->getValue());
		}

// 		#ifndef LIB_MDUSER_API_EXPORT
// 			if(bLOOPTIMEOUT)
// 			{
// 				REPORT_EVENT(LOG_WARNING, "LoopTime", "InstrumentIDCount=%d",m_SendPackage.GetInstrumentIDCount());
// 			}
// 		#endif

		pHeader->SequenceNumber = m_flowReader.GetId();
		pHeader->SequenceSeries = m_nSequenceSeries;
		return &m_SendPackage;
	}
	return NULL;
}

int CFTDCPubEndPoint::PublishSend()
{
	int nCount = 0;
	for(; nCount<40; nCount++)
	{
		CPackage *pPackage = GetNextDataPackage();	
		if (pPackage == NULL)
		{
			break;
		}
		if (m_pSendProtocol->Send(pPackage) != 0)
		{
			break;
		}
		//20130812 xuzh log before send
		else
		{
			#ifdef PERFORMTEST
			if(bLOOPTIMEOUT)
			{
				long nPackageEndTime=0;
				long m_CostTime=0;
				#ifndef  WIN32
					//计算响应时间
					struct timeval timeout;
					memset(&timeout,0,sizeof(timeout));
					gettimeofday(&timeout, NULL);
					m_CostTime=(timeout.tv_sec-m_nBeginTime.tv_sec)*1000000+timeout.tv_usec-m_nBeginTime.tv_usec;
					//nPackageEndTime=(timeout.tv_sec)*1000000+timeout.tv_usec;
				#else
					struct _timeb timeout;
					_ftime( &timeout );
					m_CostTime=(timeout.time-m_nBeginTime.time)*1000+timeout.millitm-m_nBeginTime.millitm;
					//nPackageEndTime=(timeout.time)*1000+timeout.millitm;
				#endif
				//输出订单响应日志
				//REPORT_EVENT(LOG_WARNING, "LoopTime", "PackageSendTime=%ld us, InnerLoopTime=%ld us",nPackageEndTime,m_CostTime);
				REPORT_EVENT(LOG_WARNING, "LoopTime", "InnerLoopTime=%ld us",m_CostTime);
			}
			#endif
		}
	}
	return nCount;
}

void CFTDCPubEndPoint::MoveTo(int nOffset)
{
	if (m_flowReader.GetId() == nOffset)
	{
		return;
	}
	m_flowReader.SetId(nOffset);
}
