// KernelFront.cpp: implementation of the CKernelWriteThread class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "KernelWriteThread.h"
#include "XtpPackageDesc.h"
#include "TcpChannel.h"

#ifdef LINUX
//这个头文件是为了用函数 sync() 20141031 longqy
#include <unistd.h>
#include "ShmChannel.h"
#endif

extern void * g_pBaseShm;

#define FTD_RSP_QRY(FtdTid, FtdFieldType, XtpFieldType, CopyField)			        \
	{																			    \
		m_rspPackage.PreparePackage(FtdTid, m_XtpPackage.GetChain(), FTD_VERSION);	\
		m_rspPackage.SetRequestId(m_XtpPackage.GetRequestID());						\
		/*先处理响应信息*/															\
		CRspInfoField rspInfoField;													\
		if (XTP_GET_SINGLE_FIELD(&m_XtpPackage, &rspInfoField) > 0)					\
		{																			\
			CFTDRspInfoField ftdRspInfoField;										\
			CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);					\
			FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);						\
		}																			\
		/*处理业务信息*/															\
		FtdFieldType ftdField;														\
		XtpFieldType xtpField;														\
		CNamedFieldIterator itor =													\
		m_XtpPackage.GetNamedFieldIterator(&XtpFieldType::m_Describe);					\
		while (!itor.IsEnd())														\
		{																			\
			itor.Retrieve(&xtpField);												\
			CopyField;																\
			FTDC_ADD_FIELD(&m_rspPackage, &ftdField);								\
			itor.Next();															\
		}																			\
		SendToQueryFlow(pSession, &m_rspPackage);									\
	}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const int SR_DEFAULT_SELECT_TIMEOUT = 60; //微秒
extern CCachedFlow *g_pQueryFlow;
extern bool    g_bLatencyOut;

CKernelWriteThread::CKernelWriteThread(CFlow* pTradeResult,CFlow* pSlogResult,DWORD FrontID,int nLifeCycleID,bool bBindThreadsToCPU/* =false */)
{
	m_pTradeResult=pTradeResult;
	m_pSlogResult=pSlogResult;
	m_bBindThreadsToCPU = bBindThreadsToCPU;
	m_dwFrontID = FrontID;
	m_nLifeCycleID = nLifeCycleID;

	m_XtpPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	m_ResultReader.AttachFlow(m_pTradeResult,0);
	m_QueryReader.AttachFlow(g_pQueryFlow,0);

	m_rspPackage.ConstructAllocate(FTDC_PACKAGE_MAX_SIZE, 1000);

	m_pPrivateFlow = new CCachedFlow(false, 10000000, 100000);
	m_pPublicFlow = new CCachedFlow(false, 100000, 100000);
	m_nRedoFlowCnt = 0;

#ifdef LINUX
	if(m_bBindThreadsToCPU){  // 线程绑定CPU
		BindThd2CPU(pthread_self());
	}
#endif
}

CKernelWriteThread::~CKernelWriteThread()
{
	CUserFlowMap::iterator pfitor = m_mapUserFlow.begin();
	while (pfitor != m_mapUserFlow.end())
	{
		delete pfitor->second;
		pfitor ++;
	}
	m_mapUserFlow.clear();
	m_InvestorUserMap.clear();
	m_SessionMap.clear();
}

CIndexPackageFlow * CKernelWriteThread::GetPrivateFlow(const CBrokerIDType &brokerID)
{
	CIndexPackageFlow *pFlow = NULL;
	CIndexPackageFlow **pFind = m_mapPrivateFlow.Find(brokerID);
	if (pFind == NULL)
	{
		pFlow = new CIndexPackageFlow();
		pFlow->AttachUnderFlow(m_pPrivateFlow);
		m_mapPrivateFlow.Insert(brokerID, pFlow);
	}
	else
	{
		pFlow = *pFind;
	}
	return pFlow;
}

void CKernelWriteThread::SendToPrivateFlow(const CBrokerIDType &brokerID, int nIndex)
{
	CIndexPackageFlow *pFlow = GetPrivateFlow(brokerID);
	pFlow->Append(nIndex);
}

void CKernelWriteThread::SendToPublicFlow(CPackage *pPackage)
{
	pPackage->MakePackage();
	CFlow *pFlow = GetPublicFlow();
	pFlow->Append(pPackage->Address(), pPackage->Length());
}

CIndexPackageFlow *CKernelWriteThread::GetUserFlow(const CBrokerIDType &brokerID,const CUserIDType &userID)
{	
	CIndexPackageFlow *pFlow = NULL;
	string brokerUserID = brokerID.getValue();
	brokerUserID += userID;
	CUserFlowMap::iterator iter = m_mapUserFlow.find(brokerUserID);
	if (iter == m_mapUserFlow.end())
	{
		pFlow = new CIndexPackageFlow();
		pFlow->AttachUnderFlow(m_pPrivateFlow);
		m_mapUserFlow.insert(CUserFlowMap::value_type(brokerUserID, pFlow));
	}
	else
	{
		pFlow = iter->second;
	}
	return pFlow;
}

void CKernelWriteThread::SendToUserFlow(const CBrokerIDType &brokerID,const CUserIDType &userID, int nIndex)
{
	CIndexPackageFlow *pFlow = GetUserFlow(brokerID,userID);
	pFlow->Append(nIndex);
}

TSessionInfo *CKernelWriteThread::GetSessionInfo(DWORD nSessionID)
{
	CSessionMap::iterator itor = m_SessionMap.find(nSessionID);
	if (itor != m_SessionMap.end())
	{
		return &(itor->second);
	}
	return NULL;
}

void CKernelWriteThread::SendToDialogFlow(CFTDCRSession *pSession, CFTDCPackage *pPackage)
{
	TSessionInfo *pSessionInfo = GetSessionInfo(pSession->GetSessionID());
	if (pSessionInfo == NULL)
	{
		return;
	}
	TFTDCHeader  *pHeader = pPackage->GetFTDCHeader();
	pHeader->SequenceNumber = ++(pSessionInfo->nDialogFlowSeqNo);
	pHeader->SequenceSeries = TSS_DIALOG;
	pSession->SendRequestPackage(pPackage);
}

void CKernelWriteThread::SendToQueryFlow(CFTDCRSession *pSession, CFTDCPackage *pPackage)
{
	TSessionInfo *pSessionInfo = GetSessionInfo(pSession->GetSessionID());
	if (pSessionInfo == NULL)
	{
		return;
	}
	TFTDCHeader  *pHeader = pPackage->GetFTDCHeader();
	pHeader->SequenceNumber = ++(pSessionInfo->nQueryFlowSeqNo);
	pHeader->SequenceSeries = TSS_QUERY;
	pSession->SendRequestPackage(pPackage);
}

int CKernelWriteThread::AppendToPrivateFlow(CPackage *pPackage)
{
	pPackage->MakePackage();
	return m_pPrivateFlow->Append(pPackage->Address(), pPackage->Length());
}

bool CKernelWriteThread::PublishFlow(CFTDCRSession *pSession, WORD wSequenceSeries, int nSubStartId,int &nPubStartId)
{
	TSessionInfo *pSessionInfo = GetSessionInfo(pSession->GetSessionID());
	if (pSessionInfo == NULL)
	{
		return false;
	}
	
	int nBorkenSeqNo = 0;	
	//交易流的清理通过中断会话完成，不要重新订阅
	//目前只有私有流和公共流
	CReadOnlyFlow *pFlow = NULL;
	switch (wSequenceSeries)
	{
	case TSS_PRIVATE:
		if (pSessionInfo->UserType == UT_Manager)
		{
			pFlow = GetPrivateFlow(pSessionInfo->BrokerID);
		}
		else
		{
			pFlow = GetUserFlow(pSessionInfo->BrokerID,pSessionInfo->UserID);
		}
		break;
	case TSS_PUBLIC:
		pFlow = GetPublicFlow();
		break;
	case TSS_USER:
		pFlow = GetUserFlow(pSessionInfo->BrokerID,pSessionInfo->UserID);
		break;
	default:
		break;
	}
	if (pFlow == NULL)
	{
		return false;
	}
	
	
	int nFlowCnt = pFlow->GetCount();
	if (nFlowCnt < nSubStartId)
	{
		nPubStartId = nFlowCnt;
	}
	else
	{
		nPubStartId = nSubStartId;
	}
	
	//增加起始序号有效性判断,如果起始序号小于0且非-1,则清零
	if (nSubStartId == -1)
	{
		nPubStartId = pFlow->GetCount();
	}
	else if (nSubStartId < 0)
	{
		nPubStartId = 0;
	}
	
	pSession->Publish(pFlow, wSequenceSeries, nPubStartId);
	return true;
}

bool CKernelWriteThread::InitInstance()
{
#ifdef LINUX
	REPORT_EVENT(LOG_CRITICAL,"qtrade api send thread", " [%ld]\n", gettid());
#endif
	Redo();

	return true;
}

void CKernelWriteThread::SetNoShmChannelFlag(bool bFlag)
{
	m_bNoShmChannelFlag = bFlag;
}

list<CUserIDType>* CKernelWriteThread::GetUsersByInvestorID(CInvestorIDType& InvestorID)
{
	if (InvestorID.isNull())
	{
		return NULL;
	}
	CInvestorUserMap::iterator it=m_InvestorUserMap.find(InvestorID);
	if (it==m_InvestorUserMap.end())
	{
		return NULL;
	}
	return it->second;
}

void CKernelWriteThread::DispatchIOs()
{
	HandleOtherTask();
	for(CSessionMap::iterator Itor = m_SessionMap.begin();
			Itor != m_SessionMap.end();)
	{
		if (Itor->second.pSession == NULL)
		{
			m_SessionMap.erase(Itor++);
			continue;
		}
		int nReadID=0;
		int nWriteID=0;
		if (Itor->second.Logined)
		{
			Itor->second.pSession->GetIds(&nReadID,&nWriteID);//放入tcpchanel的cachelist中
		}
		Itor++;
	}
	SyncTime();
	for(CSessionMap::iterator sessionItor = m_SessionMap.begin();
		sessionItor != m_SessionMap.end();sessionItor++)
	{
		int ret =1;
		if (!sessionItor->second.WriteError)
		{
			ret =sessionItor->second.pSession->HandleOutput();
		}

		if (ret <0)
		{
			sessionItor->second.WriteError =true;
			//REPORT_EVENT(LOG_INFO,"DispatchIOs","write error ret=%d",ret);
		}
		
		if (sessionItor->second.Disconected && sessionItor->second.pSession != NULL)
		{
			if (sessionItor->second.WriteError)
			{
			   sessionItor->second.pSession->Closeconnect(sessionItor->second.nReason);
			   //REPORT_EVENT(LOG_INFO,"pSession->Closeconnect","write error");
			}
			else
			{
			   sessionItor->second.pSession->Disconnect(sessionItor->second.nReason);
			   //REPORT_EVENT(LOG_INFO,"pSession->Disconnect","write error");
			}
			sessionItor->second.pSession = NULL;
		}
	}
	HandleRspQuery();
}

void CKernelWriteThread::HandleRspQuery()
{
	int i=0;
	for (i=0; i<100; i++)
	{
		m_XtpPackage.Allocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN);
		if(!m_QueryReader.GetNext(&m_XtpPackage))
		{
			break;
		}
		
		CFTDCRSession *pSession = NULL;
		
		if (m_XtpPackage.GetFrontID() == m_dwFrontID)
		{
			TSessionInfo *sessionInfo = GetSessionInfo(m_XtpPackage.GetSessionID());
			if (sessionInfo == NULL)
			{
				continue;
			}
			pSession = (CFTDCRSession *)(sessionInfo->pSession);
		}
		if (pSession == NULL)
		{
			continue;
		}

		switch(m_XtpPackage.GetTid()) 
		{
		case TID_RspQryOrder:
			FTD_RSP_QRY(FTD_TID_RspQryOrder, CFTDOrderField, COrderField,
			{
				CopyAPIOrderEntity(&ftdField, &xtpField);
			});
			break;
		case TID_RspQryTrade:
			FTD_RSP_QRY(FTD_TID_RspQryTrade, CFTDTradeField, CTradeField,
			{
				CopyAPITradeEntity(&ftdField, &xtpField);
			});
			break;
		//可用投资者应答
		case TID_RspQryUserInvestor:
			FTD_RSP_QRY(FTD_TID_RspQryUserInvestor, CFTDRspUserInvestorField, CUserInvestorField,
			{
				CopyAPIUserInvestorEntity(&ftdField, &xtpField);
			});
			break;
		//投资者账户查询
		case TID_RspQryInvestorAccount:
			FTD_RSP_QRY(FTD_TID_RspQryInvestorAccount, CFTDRspInvestorAccountField, CInvestorAccountField,
			{
				CopyAPIInvestorAccountEntity(&ftdField, &xtpField);
			});
			break;	
		case TID_RspQryInstrument:
			FTD_RSP_QRY(FTD_TID_RspQryInstrument, CFTDRspInstrumentField, CInstrumentField,
			{
				CopyAPIInstrumentEntity(&ftdField, &xtpField);
			});
			break;

		case TID_RspQryMarketData:
			FTD_RSP_QRY(FTD_TID_RspQryMarketData, CFTDMarketDataField, CMarketDataField,
			{
				CopyMarketDataEntity(&ftdField, &xtpField);
			});
			break;			
		//交易所查询
		case TID_RspQryExchange:
			FTD_RSP_QRY(FTD_TID_RspQryExchange, CFTDRspExchangeField, CRspExchangeField,
			{
				CopyAPIExchangeEntity(&ftdField, &xtpField);
			});
			break;			
		//投资者持仓查询
		case TID_RspQryInvestorPosition:
			FTD_RSP_QRY(FTD_TID_RspQryInvestorPosition, CFTDRspInvestorPositionField, CInvestorPositionField,
			{
				CopyAPIInvestorPositionEntity(&ftdField, &xtpField);
			});
			break;		
		//手续费率查询
		case TID_RspQryInvestorFee:
			FTD_RSP_QRY(FTD_TID_RspQryInvestorFee, CFTDInvestorFeeField, CInvestorFeeField,
			{
				CopyAPIInvestorFeeEntity(&ftdField, &xtpField);
			});
			break;			
		//保证金率查询
		case TID_RspQryInvestorMargin:
			FTD_RSP_QRY(FTD_TID_RspQryInvestorMargin, CFTDInvestorMarginField, CInvestorMarginField,
			{
				CopyAPIInvestorMarginEntity(&ftdField, &xtpField);
			});
			break;
			//金交所递延费率查询
		case TID_RspQrySGEDeferRate:
			FTD_RSP_QRY(FTD_TID_RspQrySGEDeferRate, CFTDSGEDeferRateField, CSGEDeferRateField,
			{
				CopySGEDeferRateEntity(&ftdField, &xtpField);
			});
			break;
			//客户期权手续费率查询应答
		case TID_RspQryInvestorOptionFee:
			FTD_RSP_QRY(FTD_TID_RspQryInvestorOptionFee, CFTDRspInvestorOptionFeeField, CInvestorOptionFeeField,
			{
				CopyInvestorOptionFeeEntity(&ftdField, &xtpField);
			});
			break;
		default:
			break;
		}		
	}
}

void CKernelWriteThread::HandleMessage(CXTPPackage *pMessage)
{
	CFTDCRSession *pSession = NULL;		
	if (pMessage->GetFrontID() == m_dwFrontID && pMessage->GetTid() != TID_RspUserLogin)
	{
		TSessionInfo *sessionInfo = GetSessionInfo(pMessage->GetSessionID());
		if (sessionInfo == NULL)
		{
			return;
		}
		pSession = sessionInfo->pSession;
	}

	switch(pMessage->GetTid())
	{
	case TID_RspUserLogin:
		OnUserLoginRsp(pMessage);
		break;
	case TID_RspUserLogout:
		OnUserLogoutRsp(pMessage,pSession);
		break;
	case TID_RspOrderInsert:
		{
			if(pSession == NULL || !pMessage->GetNoReplayFlag())						
			{																		
				break;																
			}	

			CRspInfoField rspInfoField;												
			XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField);																																								
			CInputOrderField xtpField;													
			XTP_GET_SINGLE_FIELD(pMessage, &xtpField);					
																	
			CFTDRspInfoField ftdRspInfoField;										
			CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);					
			CFTDInputOrderField ftdField;													
			CopyAPIInputOrderEntity(&ftdField,&xtpField);																
			if (pSession != NULL)													
			{																		
				m_rspPackage.PreparePackage(FTD_TID_RspOrderInsert, FTDC_CHAIN_LAST, FTD_VERSION);	
				m_rspPackage.SetRequestId(pMessage->GetRequestID());				
				FTDC_ADD_FIELD(&m_rspPackage, &ftdField);							
				FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);					
				SendToDialogFlow(pSession, &m_rspPackage);
			}
			if (rspInfoField.ErrorID != 0)											
			{																		
				m_rspPackage.PreparePackage(FTD_TID_ErrRtnOrderInsert, FTDC_CHAIN_LAST, FTD_VERSION);
				FTDC_ADD_FIELD(&m_rspPackage, &ftdField);					
				FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);				
				int nIndex = AppendToPrivateFlow(&m_rspPackage);				
				SendToPrivateFlow(xtpField.BrokerID, nIndex);		
				SendToUserFlow(xtpField.BrokerID,xtpField.UserID, nIndex);
			}
			PrintDelayLog(xtpField);
		}
		break;
	case TID_RspOrderAction:
		{
			if(pSession == NULL || !pMessage->GetNoReplayFlag())						
			{																		
				break;																
			}	
			
			CRspInfoField rspInfoField;												
			XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField);																																								
			COrderActionField xtpField;													
			XTP_GET_SINGLE_FIELD(pMessage, &xtpField);					
			
			CFTDRspInfoField ftdRspInfoField;										
			CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);					
			CFTDOrderActionField ftdField;													
			CopyAPIOrderActionEntity(&ftdField,&xtpField);																
			if (pSession != NULL)													
			{																		
				m_rspPackage.PreparePackage(FTD_TID_RspOrderAction, FTDC_CHAIN_LAST, FTD_VERSION);	
				m_rspPackage.SetRequestId(pMessage->GetRequestID());				
				FTDC_ADD_FIELD(&m_rspPackage, &ftdField);							
				FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);					
				SendToDialogFlow(pSession, &m_rspPackage);
			}
			if (rspInfoField.ErrorID != 0)											
			{																		
				m_rspPackage.PreparePackage(FTD_TID_ErrRtnOrderAction, FTDC_CHAIN_LAST, FTD_VERSION);
				FTDC_ADD_FIELD(&m_rspPackage, &ftdField);					
				FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);				
				int nIndex = AppendToPrivateFlow(&m_rspPackage);				
				SendToPrivateFlow(xtpField.BrokerID, nIndex);		
				SendToUserFlow(xtpField.BrokerID,xtpField.UserID, nIndex);
			}
		}
		break;
	case TID_NtfOrder:
		{
			COrderField xtpField;													
			CFTDOrderField ftdField;									
			pMessage->GetSingleField(&(COrderField::m_Describe),&xtpField);												
			CopyAPIOrderEntity(&ftdField, &xtpField);															
			m_rspPackage.PreparePackage(FTD_TID_RtnOrder, FTDC_CHAIN_LAST, FTD_VERSION);	
			FTDC_ADD_FIELD(&m_rspPackage, &ftdField);							
			int nIndex = AppendToPrivateFlow(&m_rspPackage);					
			SendToPrivateFlow(xtpField.BrokerID, nIndex);						
			list<CUserIDType>* pListUsers=GetUsersByInvestorID(ftdField.InvestorID); 
			if (pListUsers!=NULL)												
			{																	
				list<CUserIDType>::iterator it=pListUsers->begin();				
				while(it!=pListUsers->end())									
				{																
					SendToUserFlow(xtpField.BrokerID,*it, nIndex);								
					it++;														
				}																
			}
		}
		break;
	case TID_NtfTrade:
		{
			CTradeField xtpField;													
			CFTDTradeField ftdField;									
			pMessage->GetSingleField(&(CTradeField::m_Describe),&xtpField);												
			CopyAPITradeEntity(&ftdField, &xtpField);															
			m_rspPackage.PreparePackage(FTD_TID_RtnTrade, FTDC_CHAIN_LAST, FTD_VERSION);	
			FTDC_ADD_FIELD(&m_rspPackage, &ftdField);							
			int nIndex = AppendToPrivateFlow(&m_rspPackage);					
			SendToPrivateFlow(xtpField.BrokerID, nIndex);						
			list<CUserIDType>* pListUsers=GetUsersByInvestorID(ftdField.InvestorID); 
			if (pListUsers!=NULL)												
			{																	
				list<CUserIDType>::iterator it=pListUsers->begin();				
				while(it!=pListUsers->end())									
				{																
					SendToUserFlow(xtpField.BrokerID,*it, nIndex);								
					it++;														
				}																
			}
		}
		break;
		//add by jinpc 20170112
	case TID_RspQryMBLMarketData:
		{
			if(pSession == NULL || !pMessage->GetNoReplayFlag())						
			{																		
				break;																
			}	
			
			CRspInfoField rspInfoField;												
			XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField);																																								
			CMBLMarketDataField xtpField;													
			XTP_GET_SINGLE_FIELD(pMessage, &xtpField);					
			
			CFTDRspInfoField ftdRspInfoField;										
			CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);					
			CFTDMBLMarketDataField ftdField;													
			CopyMBLMarketDataEntity(&ftdField,&xtpField);																
			if (pSession != NULL)													
			{																		
				m_rspPackage.PreparePackage(FTD_TID_RspQryMBLMarketData, pMessage->GetChain(), FTD_VERSION);	
				m_rspPackage.SetRequestId(pMessage->GetRequestID());				
				FTDC_ADD_FIELD(&m_rspPackage, &ftdField);							
				FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);					
				SendToDialogFlow(pSession, &m_rspPackage);
			}
		}
		break;
	case TID_InitUserInvestor:
		{
			CUserInvestorField field;
			CNamedFieldIterator it = pMessage->GetNamedFieldIterator(&field.m_Describe);
			while(!it.IsEnd())
			{			
				it.Retrieve(&field);
				CInvestorUserMap::iterator iter=m_InvestorUserMap.find(field.InvestorID);
				if (iter!=m_InvestorUserMap.end())
				{
					typedef list<CUserIDType> CUserList;
					bool bExists=false;
					for (CUserList::iterator user=iter->second->begin();user!=iter->second->end();user++)
					{
						if ( (*user) == field.UserID) 
						{
							bExists = true;
							break;
						}
					}
					if (!bExists)
					{
						iter->second->push_back(field.UserID);
					}
				}
				else
				{
					list<CUserIDType>* pList=new list<CUserIDType>();
					pList->push_back(field.UserID);
					m_InvestorUserMap.insert(CInvestorUserMap::value_type(field.InvestorID,pList));
				}
				it.Next();
			}	
		}
		break; 
	case TID_NtfInstrumentStatusUpdate:
		{
			CInstrumentStatusField xtpField;													
			CFTDInstrumentStatusField ftdField;									
			pMessage->GetSingleField(&(CInstrumentStatusField::m_Describe),&xtpField);												
			CopyAPIInstrumentEntity(&ftdField, &xtpField);															
			m_rspPackage.PreparePackage(FTD_TID_RtnInstrumentStatus, FTDC_CHAIN_LAST, FTD_VERSION);	
			FTDC_ADD_FIELD(&m_rspPackage, &ftdField);										
			SendToPublicFlow(&m_rspPackage);
		}
		break;
	case  TID_RspError:
		{
			if (pSession == NULL || !pMessage->GetNoReplayFlag())
			{
				break;
			}

			CRspInfoField rspInfoField;												
			XTP_GET_SINGLE_FIELD(&m_XtpPackage, &rspInfoField);	
			if (rspInfoField.ErrorID ==0)
			{
				DumpDelayLog();
			}
			m_rspPackage.PreparePackage(FTD_TID_RspError, FTDC_CHAIN_LAST, FTD_VERSION);	
			m_rspPackage.SetRequestId(m_XtpPackage.GetRequestID());				
			CFTDRspInfoField ftdRspInfoField;										
			CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);							
			FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);					
			SendToDialogFlow(pSession, &m_rspPackage);
		}
		break;
	default:
		break;
	}	
}

void CKernelWriteThread::SetRedoFlowCnt(int cnt)
{
	m_nRedoFlowCnt = cnt;
}

void CKernelWriteThread::Redo()
{
	for(int i=1;i<=m_nRedoFlowCnt;i++)
	{
		m_XtpPackage.Allocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN);
		if(!m_ResultReader.GetNext(&m_XtpPackage))
		{
			break;
		}
		
		m_XtpPackage.SetNoReplayFlag(false);		
		HandleMessage(&m_XtpPackage);	
	}
}

	
bool CKernelWriteThread::HandleOtherTask()
{
	int i=0;
	for (i=0; i<100; i++)
	{
		m_XtpPackage.Allocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN);
		if(!m_ResultReader.GetNext(&m_XtpPackage))
		{
			break;
		}
		m_XtpPackage.SetNoReplayFlag(true);
		HandleMessage(&m_XtpPackage);
	}

	return CReactor::HandleOtherTask();
}

void CKernelWriteThread::OnSessionDisconnected(CSession *pSession, int nReason)
{
	REPORT_EVENT(LOG_DEBUG, "Connect", 
		"Session 0x%08x Disconnected, reason = [0x%08x], IP=%s",
		pSession->GetSessionID(), nReason,
		pSession->GetChannel()->GetRemoteName());
}

void CKernelWriteThread::OnUserLoginRsp(CXTPPackage *pMessage)
{
	if (!pMessage->GetNoReplayFlag()) return;
	m_rspPackage.PreparePackage(FTD_TID_RspUserLogin, FTDC_CHAIN_LAST, FTD_VERSION);
	m_rspPackage.SetRequestId(pMessage->GetRequestID());
	
	CRspInfoField rspInfoField;
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		//没有取到响应信息
		return ;
	}
	CFTDRspInfoField ftdRspInfoField;
	CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);
	
	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);
	
	CUserLoginField userLoginField;
	if(XTP_GET_SINGLE_FIELD(pMessage, &userLoginField) <= 0)
	{
		//没有取到登录域
		return ;
	}
	if (userLoginField.LifeCycleID != m_nLifeCycleID)
	{
		return;
	}
	//组织FTDC报文的登录应答域
	
	CFTDRspUserLoginField ftdRspUserLoginField;
	memset(&ftdRspUserLoginField, 0, sizeof(CFTDRspUserLoginField));
	ftdRspUserLoginField.MaxOrderLocalID = userLoginField.MaxOrderLocalID;
	ftdRspUserLoginField.TradingDay = userLoginField.TradingDay;
	ftdRspUserLoginField.LoginTime = userLoginField.LoginTime;
	ftdRspUserLoginField.UserID = userLoginField.UserID;
	ftdRspUserLoginField.TradingSystemName = userLoginField.TradingSystemName;
	ftdRspUserLoginField.BrokerID=userLoginField.BrokerID;
	ftdRspUserLoginField.SessionID=userLoginField.SessionID;
	ftdRspUserLoginField.FrontID=userLoginField.FrontID;
	//	ftdRspUserLoginField.DataCenterID = m_DataCenterID;
	if (rspInfoField.ErrorID == 0)		//登录成功
	{
		CReadOnlyFlow *pPrivateFlow =  GetPrivateFlow(userLoginField.BrokerID);
		CReadOnlyFlow *pUserFlow = GetUserFlow(userLoginField.BrokerID,userLoginField.UserID);
		ftdRspUserLoginField.PrivateFlowSize = pPrivateFlow->GetCount();
		ftdRspUserLoginField.UserFlowSize = pUserFlow->GetCount();
	}
	
	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspUserLoginField);
	
	//走对话流会导致登录应答后到，这里直接发送
	CFTDCRSession *pSession=NULL;
	CSessionMap::iterator iter = m_SessionMap.find(pMessage->GetSessionID());
	if (iter == m_SessionMap.end())
	{
		CChannel *pChannel =NULL;
		if (userLoginField.SockID.getValue() >0)
		{
			pChannel = new CTcpChannel(userLoginField.SockID.getValue(),true); 
		}
		else 
		{
#ifdef LINUX
			struct ConnectStruct * pConnectAddr2 =  (struct ConnectStruct*)(g_pBaseShm + sizeof(ConnectStruct)*userLoginField.SockID.getValue()*-1);
			pChannel = new CShmChannel(pConnectAddr2);
#else
			RAISE_RUNTIME_ERROR("can not support shmchannel on windows");
#endif
		}
		pSession = new CFTDCRSession(this,pChannel, XMP_WRITE);
		pSession->ResetSession(pMessage->GetSessionID());
		TSessionInfo sessionInfo;
		memset(&sessionInfo,0,sizeof(TSessionInfo));
		sessionInfo.pSession = pSession;
		sessionInfo.BrokerID = userLoginField.BrokerID;
		sessionInfo.UserID = userLoginField.UserID;
		sessionInfo.UserType = userLoginField.UserType;
		sessionInfo.WriteError = false;
		sessionInfo.Disconected = false;
		if (rspInfoField.ErrorID == 0)		//登录不成功
		{
			sessionInfo.Logined	= true;
		}
		else
		{
			sessionInfo.Logined = false;
		}
		m_SessionMap.insert(CSessionMap::value_type(pMessage->GetSessionID(),sessionInfo));
	}
	else
	{
		if (rspInfoField.ErrorID == 0)		//登录不成功
		{
			iter->second.Logined	= true;
		}
		else
		{
			iter->second.Logined = false;
		}
		pSession = iter->second.pSession;
	}

	pSession->SendRequestPackage(&m_rspPackage);
	if (rspInfoField.ErrorID != 0)		//登录不成功
	{
		return;
	}
	
	
	pSession->SetHeartbeatTimeout(userLoginField.Heartbeat);
	pSession->EnableHeartbeat(true);
	pSession->RegisterSessionCallback(this);
	pSession->GetChannel()->SetLogFlow(m_pSlogResult);

	TFtdeDisseminationInfo DisseminationInfo;
	memset(&DisseminationInfo, 0, sizeof(DisseminationInfo));
	DisseminationInfo.nSessionID = pSession->GetSessionID();
	DisseminationInfo.TradingDay = userLoginField.ClientTradingDay;

	//对话流
	DisseminationInfo.Fields[DisseminationInfo.nFieldCount].nSubStartId = 
		userLoginField.DialogSeqno;
	DisseminationInfo.Fields[DisseminationInfo.nFieldCount].wSequenceSeries = 
		TSS_DIALOG;
	DisseminationInfo.nFieldCount++;
	//私有流
	if (userLoginField.PrivateSeqno != NO_SUBSCRIBE)
	{
		DisseminationInfo.Fields[DisseminationInfo.nFieldCount].nSubStartId = 
			userLoginField.PrivateSeqno;
		DisseminationInfo.Fields[DisseminationInfo.nFieldCount].wSequenceSeries = 
			TSS_PRIVATE;
		DisseminationInfo.nFieldCount++;
	}

	//公有流
	if (userLoginField.PublicSeqno != NO_SUBSCRIBE)
	{
		DisseminationInfo.Fields[DisseminationInfo.nFieldCount].nSubStartId = 
			userLoginField.PublicSeqno;
		DisseminationInfo.Fields[DisseminationInfo.nFieldCount].wSequenceSeries = 
			TSS_PUBLIC;
		DisseminationInfo.nFieldCount++;
	}
	
	CFTDDisseminationField fieldDissemination;
	m_rspPackage.PreparePackage(FTD_TID_IntlRtnDissemination, FTDC_CHAIN_LAST, FTD_VERSION);
	if (userLoginField.TradingDay != userLoginField.ClientTradingDay)
	{
		if (userLoginField.DialogSeqno !=-1)
		{
			fieldDissemination.SequenceSeries = TSS_DIALOG;
			fieldDissemination.SequenceNo = 0;
		}
	}

	int nSubStartId=0;
	for (int i=0; i<DisseminationInfo.nFieldCount; i++)
	{
		//如果客户端的交易日与交易引擎不符，则从0开始订阅
		if (DisseminationInfo.TradingDay != userLoginField.TradingDay && 
			DisseminationInfo.Fields[i].nSubStartId != -1)
		{
			DisseminationInfo.Fields[i].nSubStartId = 0;
		}
		
		//by wangwei, 20121221
		PublishFlow(pSession,  DisseminationInfo.Fields[i].wSequenceSeries,DisseminationInfo.Fields[i].nSubStartId, DisseminationInfo.Fields[i].nPubStartId);
		
		fieldDissemination.SequenceNo = DisseminationInfo.Fields[i].nPubStartId;
		fieldDissemination.SequenceSeries = DisseminationInfo.Fields[i].wSequenceSeries;
		FTDC_ADD_FIELD(&m_rspPackage, &fieldDissemination);
	}
	//直接发送分发信息通知
	pSession->SendRequestPackage(&m_rspPackage);
}

void CKernelWriteThread::OnUserLogoutRsp(CXTPPackage *pMessage, CFTDCRSession *pSession)
{
	if (pSession == NULL || !pMessage->GetNoReplayFlag())
	{
		return;
	}
	m_rspPackage.PreparePackage(FTD_TID_RspUserLogout, FTDC_CHAIN_LAST, FTD_VERSION);
	m_rspPackage.SetRequestId(pMessage->GetRequestID());
	
	CRspInfoField rspInfoField;
	if (XTP_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		//没有取到响应信息
		return ;
	}
	CFTDRspInfoField ftdRspInfoField;
	CopyErrorTypeEntity(&ftdRspInfoField, &rspInfoField);
	
	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);
	
	CUserLogoutField userLogoutField;
	if (rspInfoField.ErrorID == 0)		//登出成功
	{
		if(XTP_GET_SINGLE_FIELD(pMessage, &userLogoutField) <= 0)
		{
			//没有取到登出域
			return ;
		}
		//组织FTDC报文的登出应答域
		CFTDRspUserLogoutField ftdRspUserLogoutField;
		ftdRspUserLogoutField.BrokerID = userLogoutField.BrokerID;
		ftdRspUserLogoutField.UserID = userLogoutField.UserID;
		ftdRspUserLogoutField.LogoutReason = userLogoutField.LogoutReason;

		
		FTDC_ADD_FIELD(&m_rspPackage, &ftdRspUserLogoutField);
	}
	
	//向客户端出出应答
	SendToDialogFlow(pSession, &m_rspPackage);
	TSessionInfo *sessionInfo = GetSessionInfo(pMessage->GetSessionID());
	if (sessionInfo != NULL)
	{
		sessionInfo->Disconected = true;
		sessionInfo->nReason = userLogoutField.LogoutReason.getValue();
	}

//	pSession->Disconnect(userLogoutField.LogoutReason.getValue());
}

void CKernelWriteThread::PrintDelayLog(CInputOrderField &field)
{
	if (g_bLatencyOut)
	{
		InputLocalTime(field.FTdSendDown);
		memset(tmp,0,sizeof(tmp));
		sprintf(tmp,"%s,%s,%s,%d,%d,%d,%d,%d,%d,%d",field.BrokerID.getValue(),field.UserID.getValue(),field.UserOrderLocalID.getValue(),\
			field.FrontID.getValue(),field.SessionID.getValue(),field.APIID.getValue(),field.RequestID.getValue(),\
			field.FTdRecvDown.getValue(),field.FTdSendDown.getValue(),field.FTdSendDown.getValue()-field.FTdRecvDown.getValue());
		if (field.DealFlag != DF_Wait)
		{
			m_Delay.push_back(tmp);
		}
		else
		{
			m_QdpDelay.push_back(tmp);
		}

	}
}

void CKernelWriteThread::DumpDelayLog()
{
	FILE *output;
	output=mfopen("FtdOrderDelay.csv","wt");
	if (output!=NULL)
	{
		fprintf(output,"BrokerID,UserID,UserOrderLocalID,FrontID,SessionID,APIID,RequestID,FTdRecvDown,FTdSendDown,Delay\n");
		for (CDelayVector::iterator itor=m_Delay.begin(); itor!=m_Delay.end(); itor++)
		{
			fprintf(output,"%s\n",itor->c_str());
		}

		fprintf(output,"\n");
		for (CDelayVector::iterator iter=m_QdpDelay.begin(); iter!=m_QdpDelay.end(); iter++)
		{
			fprintf(output,"%s\n",iter->c_str());
		}
		fclose(output);
	}
}






