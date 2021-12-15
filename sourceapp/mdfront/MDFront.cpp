// MDFront.cpp: implementation of the CMDFront class.
//
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "MDFront.h"
#include "CachedFlow.h"
#include "FtdPackageDesc.h"
#include "errorDefine.h"
//#include "UFCopy.h"
#include "SelectReactor.h"

//#define _UNIT_TEST_

#define MSG_SSLERR_INVALID_USERID	0xB001
#define MSG_DUPLICATE_USERID		0xB101

class CMDSyncAutoPtr
{
public:
	CMDSyncAutoPtr(CMDServiceSynchronizer *pSynchronizer)
	{
		m_pSynchronizer = pSynchronizer;
		m_pSynchronizer->Wait();
	}
	~CMDSyncAutoPtr()
	{
		m_pSynchronizer->End();
	}
private:
	CMDServiceSynchronizer *m_pSynchronizer;
};
#define MDSERVICE_SYNC	CMDSyncAutoPtr __MDSyncAutoPtr(&m_Synchronizer);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMDFront::CMDFront(CReactor *pReactor, DWORD nFrontID, CMDFlowManager *pFlowManager,
				   CEventHandler *pFrontManager,CMarketDataHandler * pMarketDataHandler)
:CEventHandler(pReactor),m_Synchronizer(pFrontManager)
{
	m_nFrontID = nFrontID;
	m_pFlowManager = pFlowManager;
	m_pFrontManager = pFrontManager;
//	m_pInMemFlowManager = m_pFlowManager->SubscribeTopics();
//	m_pMDFrontServiceInterface = pMDFrontServiceInterface;
	m_marketDataHandler = pMarketDataHandler;
	m_rspPackage.ConstructAllocate(FTDC_PACKAGE_MAX_SIZE, 1000);
	m_pErrorEngine=new CErrorEngine;
	defineErrors(m_pErrorEngine);

#ifdef _UNIT_TEST_
	printf("timestart =%d\n",time(NULL));
	for (int i=0; i<10000; i++)
	{
		RspTopicMarketDataVersion(NULL, NULL, 1000, i*(12));
	}
	printf("timeend =%d\n",time(NULL));
#endif
}

CMDFront::~CMDFront()
{
	MDSERVICE_SYNC;
	DisconnectAll(0);
//	m_pInMemFlowManager->ReleaseRef();
	delete m_pErrorEngine;
}

void CMDFront::ClearAllMap()
{
	m_mapSessionInfo.Clear();
}

void CMDFront::OnCommPhaseChange(WORD nCommPhaseNo)
{
	MDSERVICE_SYNC;
	DisconnectAll(0);
//	m_pInMemFlowManager->ReleaseRef();
//	m_pInMemFlowManager = m_pFlowManager->SubscribeTopics();	
}

void CMDFront::DisconnectAll(int nReason)
{
	for (;;)
	{
		CSessionInfoMap::iterator itor = m_mapSessionInfo.Begin();
		if (itor.IsEnd())
		{
			break;
		}
//		(*itor).pSession->RegisterSessionCallback(NULL);
		(*itor).pSession->Disconnect(nReason);
	}
	ClearAllMap();
}
void CMDFront::ChangeDateDisconnectAll()
{
	DisconnectAll(0);
}
void CMDFront::SendToDialogFlow(CFTDCSession *pSession, CFTDCPackage *pPackage)
{
	TMDFrontSessionInfo *pSessionInfo = m_mapSessionInfo.Find(pSession->GetSessionID());
	if (pSessionInfo == NULL)
	{
		return;
	}
	TFTDCHeader  *pHeader = pPackage->GetFTDCHeader();
	pHeader->SequenceNumber = ++(pSessionInfo->nDialogFlowSeqNo);
	pHeader->SequenceSeries = TSS_DIALOG;
	pSession->SendRequestPackage(pPackage);
}

bool CMDFront::IsSessionLogin(DWORD nSessionID)
{
	TMDFrontSessionInfo *pFind = m_mapSessionInfo.Find(nSessionID);
	if (pFind == NULL)
	{
		//没找到这个会话的信息，返回false
		return false;
	}
	return pFind->bIsLogin;
}

bool CMDFront::GetSessionOwner(DWORD nSessionID, CUserIDType &userID, CParticipantIDType &participantID)
{
	TMDFrontSessionInfo *pSessionInfo = m_mapSessionInfo.Find(nSessionID);
	if (pSessionInfo == NULL)
	{
		return false;
	}
	userID = pSessionInfo->UserID;
	participantID = pSessionInfo->ParticipantID;
	return true;
}

void CMDFront::SetSessionOwner(DWORD nSessionID, CUserIDType &userID, CParticipantIDType &participantID)
{
	TMDFrontSessionInfo *pFind = m_mapSessionInfo.Find(nSessionID);
	if (pFind == NULL)
	{
		//不应出现，这个信息在连接建立后就应该存在了
		return;
	}
	pFind->bIsLogin = true;
	pFind->UserID =userID;
	pFind->ParticipantID = participantID;
}

void CMDFront::ClearSessionOwner(const DWORD nSessionID)
{
	TMDFrontSessionInfo *pFind = m_mapSessionInfo.Find(nSessionID);
	if (pFind == NULL)
	{
		//不应出现，这个信息在连接建立后就应该存在了
		return;
	}
	pFind->bIsLogin = false;
	pFind->UserID.clear();
	pFind->ParticipantID.clear();
}

void CMDFront::SetResumeInfo(DWORD nSessionID, const CDateType &TradingDay, 
							 const CDataCenterIDType &DataCenterID)
{
	TMDFrontSessionInfo *pFind = m_mapSessionInfo.Find(nSessionID);
	if (pFind == NULL)
	{
		//不应出现，这个信息在连接建立后就应该存在了
		return;
	}
	pFind->TradingDay = TradingDay;
	pFind->DataCenterID = DataCenterID;
}

void CMDFront::OnSessionConnected(CSession *pSession)
{
//	printf("%p CMDFront::OnSessionConnected\n", pSession);
	REPORT_EVENT(LOG_INFO, "Connect", "Session 0x%08x Connected, IP=%s",
		pSession->GetSessionID(), pSession->GetChannel()->GetRemoteName());
	TMDFrontSessionInfo sinfo;
	memset(&sinfo, 0, sizeof(sinfo));
	sinfo.nSessionID = pSession->GetSessionID();
	sinfo.pSession = pSession;
	sinfo.bIsLogin = false;
	sinfo.nConnectTime = m_pReactor->Time();
	m_mapSessionInfo.Insert(sinfo.nSessionID, sinfo);
}

void CMDFront::OnSessionDisconnected(CSession *pSession, int nReason)
{
//	printf("%p CMDFront::OnSessionDisconnected\n", pSession);
	REPORT_EVENT(LOG_INFO, "Connect", 
		"Session 0x%08x Disconnected, reason = [0x%08x], IP=%s",
		pSession->GetSessionID(), nReason,
		pSession->GetChannel()->GetRemoteName());
	MDSERVICE_SYNC;
	CUserIDType userID;
	CParticipantIDType participantID;
	if (GetSessionOwner(pSession->GetSessionID(), userID, participantID))
	{
		//如果存在该会话的信息，则将其删除
		m_mapSessionInfo.Erase(pSession->GetSessionID());

		//先从Session中注销
		((CFTDCSession *)pSession)->UnPublish(TSS_DIALOG);

		MDTSessionRef sessionRef;
		sessionRef.frontID = m_nFrontID;
		sessionRef.sessionID = pSession->GetSessionID();
		
		//通知内存数据库，连接已中断
		if (!userID.isNull())
		{
			CTransaction transaction;
		//	bool bRet =m_pMDFrontServiceInterface->UserLogout(userID, participantID, 
		//		sessionRef, &transaction);
			bool bRet = true;
			if (bRet)
			{
				transaction.commit();
			}
			else
			{
				transaction.rollback();
			}
			CFTDRspInfoField ftdFtdcRspInfoField;
			SetErrorInfo(&ftdFtdcRspInfoField);
		
			if (ftdFtdcRspInfoField.ErrorID.getValue() == ERROR_NONE)
			{
				ClearSessionOwner(pSession->GetSessionID());
			}
			REPORT_EVENT(LOG_INFO, "MdLogout", "%s %s %s,front=%d,session=%d,message=%s",
				(ftdFtdcRspInfoField.ErrorID.getValue()==ERROR_NONE)?"Success":"Failure",
				pSession->GetChannel()->GetRemoteName(), userID.getValue(),
				sessionRef.frontID.getValue(),sessionRef.sessionID.getValue(),
				ftdFtdcRspInfoField.ErrorMsg.getValue());
		}
	}
}

void CMDFront::OnSessionWarning(CSession *pSession, int nReason, int nParam)
{
}

int CMDFront::HandlePackage(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession)
{
	m_pFlowManager->lock.Lock();
	NET_IO_LOG1("CFtdEngine::HandlePackage[%X]\n", pFTDCPackage->GetTID());
	FTDC_PACKAGE_DEBUG(pFTDCPackage);

	if (pFTDCPackage->GetTID() != FTD_TID_ReqUserLogin)
	{
		if (!IsSessionLogin(pSession->GetSessionID()))
		{
			SendErrorRsp(pSession, 1, "Not Login");
			m_pFlowManager->lock.UnLock();
			return 0;
		}
	}

	int nRet = 0;
	switch(pFTDCPackage->GetTID()) {
	case FTD_TID_ReqUserLogin:
		nRet = OnReqUserLogin(pFTDCPackage, (CFTDCSession *)pSession);
		break;
	case FTD_TID_ReqUserLogout:
		OnReqUserLogout(pFTDCPackage, (CFTDCSession *)pSession);
		break;
	case FTD_TID_ReqSubscribeTopic:
		OnReqSubscribeTopic(pFTDCPackage, (CFTDCSession *)pSession);
		break;	
	case FTD_TID_ReqQryTopic:
		OnReqQryTopic(pFTDCPackage, (CFTDCSession *)pSession);
		break;
	case FTD_TID_ReqSubMarketData:
		OnReqSubMarketData(pFTDCPackage, (CFTDCSession *)pSession);
		break;
	case FTD_TID_ReqUnSubMarketData:
		OnReqUnSubMarketData(pFTDCPackage, (CFTDCSession *)pSession);
		break;
	case FTD_TID_ReqTopicSearch:
		OnReqTopicSearch(pFTDCPackage, (CFTDCSession *)pSession);
		break;
	case FTD_TID_ReqQryDepthMarketData:
		OnRspQryDepthMarketData(pFTDCPackage, (CFTDCSession *)pSession);
		break;
	default:
		break;
	}
	m_pFlowManager->lock.UnLock();
	return nRet;
}

void CMDFront::SendErrorRsp(CFTDCSession *pSession, const int nErrorCode, const char *pszErrorMsg)
{
	CFTDRspInfoField ftdRspInfoField;
	ftdRspInfoField.ErrorID = nErrorCode;
	ftdRspInfoField.ErrorMsg = pszErrorMsg;
	m_rspPackage.PreparePackage(FTD_TID_RspError, FTDC_CHAIN_LAST, FTD_VERSION);
	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);
	SendToDialogFlow(pSession, &m_rspPackage);	
}

void CMDFront::SetErrorInfo(CFTDRspInfoField *pRspInfoField)
{
	pRspInfoField->ErrorID=0;
	pRspInfoField->ErrorMsg="正确";
}

struct CFTDDisseminationFieldExt
{
	WORD wSequenceSeries;
	int nSubStartId;
	int nPubStartId;
	CFlow *pFlow;
};

int CMDFront::OnReqUserLogin(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession)
{
	MDSERVICE_SYNC;
	CFTDReqUserLoginField reqUserLoginField;
	if (FTDC_GET_SINGLE_FIELD(pFTDCPackage, &reqUserLoginField) <= 0)
	{
		REPORT_EVENT(LOG_CRITICAL, "ErrorPackage","CMDFront::OnReqUserLogin can't find CFTDReqUserLoginField");
		pSession->Disconnect(0);
		return -1;
	}
	char *pszCommonName = pSession->GetChannel()->GetRemoteCommonName();
	if (pszCommonName != NULL && strcmp(pszCommonName, reqUserLoginField.UserID) != 0)
	{
		//用户名和证书中的不一致
		pSession->Disconnect(MSG_SSLERR_INVALID_USERID);
		return -1;
	}

//	MDTSessionRef sessionRef;
//	sessionRef.frontID = m_nFrontID;
//	sessionRef.sessionID = pSession->GetSessionID();

	CIPAddressType IPAddress;
	IPAddress = pSession->GetChannel()->GetRemoteName();

	CFTDRspUserLoginField rspUserLoginField;
	memset(&rspUserLoginField, 0, sizeof(CFTDRspUserLoginField));
	rspUserLoginField.MaxOrderLocalID = 0;
	rspUserLoginField.BrokerID = reqUserLoginField.BrokerID;
	rspUserLoginField.UserID = reqUserLoginField.UserID;
	rspUserLoginField.TradingDay = m_pFlowManager->GetTradingDay();
	rspUserLoginField.TradingSystemName = "中金技术行情系统";
	//tradingday and logtime can't be init

	CSessionIDType DeletedSessionID = 0;
	CSessionIDType loginSessionID = pSession->GetSessionID();
	//判断用户名和密码是否一致	

	CFTDRspInfoField rspInfoField;
	SetErrorInfo(&rspInfoField);	

	//默认登录都成功，不检查
	bool bRet = true;
	
	rspInfoField.ErrorMsg = m_pErrorEngine->getErrorMsg(rspInfoField.ErrorID);

	//发送登陆应答
	m_rspPackage.PreparePackage(FTD_TID_RspUserLogin, FTDC_CHAIN_LAST, FTD_VERSION);
	FTDC_ADD_FIELD(&m_rspPackage, &rspUserLoginField);
	FTDC_ADD_FIELD(&m_rspPackage, &rspInfoField);
	pSession->SendRequestPackage(&m_rspPackage);

	//记录登陆日志，增加记录用户端产品信息
	REPORT_EVENT(LOG_INFO, "MdLogin", "%s, %s, %s, %s, %s,front=%d,session=%d,message=%s",
		(rspInfoField.ErrorID.getValue()==ERROR_NONE)?"Success":"Failure",
		pSession->GetChannel()->GetRemoteName(), reqUserLoginField.UserID.getValue(),
		reqUserLoginField.InterfaceProductInfo.getValue(), reqUserLoginField.UserProductInfo.getValue(),
		m_nFrontID,loginSessionID.getValue(),
		rspInfoField.ErrorMsg.getValue());
		
	if (rspInfoField.ErrorID.getValue() == ERROR_NONE)
	{
		SetSessionOwner(pSession->GetSessionID(), reqUserLoginField.UserID, reqUserLoginField.BrokerID);
		CDataCenterIDType DataCenterID = 0;
		if(pFTDCPackage->GetVersion() >= 4)
		{
			DataCenterID = reqUserLoginField.DataCenterID;
		}
			
		SetResumeInfo(pSession->GetSessionID(), reqUserLoginField.TradingDay, DataCenterID);
		//这里不发送流，等合约订阅完成之后再发送
		//PublishFlows(pFTDCPackage, pSession, NULL);
	}

	if (bRet && DeletedSessionID != 0)
	{
		REPORT_EVENT(LOG_INFO, "MdLogin", "Dup login, remove SessionID=%x", DeletedSessionID.getValue());
		m_pFrontManager->PostEvent(UM_MDFRONT_DEL_SESSION, DeletedSessionID, NULL);
		CSession *pDelSession =  GetSession((DWORD)DeletedSessionID);
		if (pDelSession != NULL)
		{
			REPORT_EVENT(LOG_INFO, "MdLogin", "Dup login, remove IP=%s SessionID=%x",
				pDelSession->GetChannel()->GetRemoteName(),
				pDelSession->GetSessionID());
			pDelSession->Disconnect(MSG_DUPLICATE_USERID);
		}
	}

	//郑州合约状态推送
	OnRtnMarketDataInstrumentState(pSession, &m_rspPackage, ZCETOPIC);
	return 0;
}

int CMDFront::OnReqTopicSearch(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession)
{

	CFTDRspInfoField rspInfoField;
	SetErrorInfo(&rspInfoField);
	//如果没有合约信息，订阅也没有用
	if(NULL == m_marketDataHandler)
	{
		return 0;
	}

	//只要选择调用这个借口，就说明有合约定制需求，创建一个合约类，可以选择发送合约
	pSession->CreatSubInstrument();
	int TopicID=0;
	map<int,int> m_topic;
	CFTDSpecificInstrumentField specificInstrumentField;
	CNamedFieldIterator itor = pFTDCPackage->GetNamedFieldIterator(&specificInstrumentField.m_Describe);
	m_rspPackage.PrepareResponse(pFTDCPackage, FTD_TID_IntlTopicSearch, FTDC_CHAIN_CONTINUE, FTD_VERSION);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&specificInstrumentField);
		//寻找合约的代号
		if(specificInstrumentField.InstrumentID=="*")
		{
			if (!m_marketDataHandler) return -1;
			CTopicMarketDataMap::iterator iterTopic = m_marketDataHandler->m_mapTopicMarketData.begin();
			for (iterTopic;iterTopic!=m_marketDataHandler->m_mapTopicMarketData.end();iterTopic++ )
			{
				TopicID=iterTopic->first;
				map<int,int>::iterator iter = m_topic.find(TopicID);
				if(iter == m_topic.end())
				{
					m_topic.insert(map<int,int>::value_type(TopicID,TopicID));
				}	
			}
		}
		else
		{
			CMarketDataMap * pMarketDataMap = NULL;
			CTopicMarketDataMap::iterator iterTopic = m_marketDataHandler->m_mapTopicMarketData.begin();
			for(iterTopic;iterTopic != m_marketDataHandler->m_mapTopicMarketData.end();iterTopic++)
			{	
				TopicID=iterTopic->first;
				pMarketDataMap=iterTopic->second;
				CMarketDataMap::iterator itorinstru=pMarketDataMap->find(specificInstrumentField.InstrumentID);
				if ( itorinstru != pMarketDataMap->end())
				{		
					map<int,int>::iterator iter = m_topic.find(TopicID);
					if(iter == m_topic.end())
					{
						m_topic.insert(map<int,int>::value_type(TopicID,TopicID));
					}
				}
			}	
		}
		itor.Next();
	}
	
	map<int,int>::iterator iter;
	for (iter=m_topic.begin();iter!=m_topic.end();iter++)
	{
		CFTDTopicSearchField ctopicfild;
		ctopicfild.TopicID=iter->first;
		FTDC_ADD_FIELD(&m_rspPackage, &ctopicfild);
		FTDC_ADD_FIELD(&m_rspPackage, &rspInfoField);
	}
	m_rspPackage.SetChain(FTDC_CHAIN_LAST);
	m_rspPackage.SetRequestId(TopicID);
	pSession->SendRequestPackage(&m_rspPackage);
	
	return 0;
}

int CMDFront::OnReqSubMarketData(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession)
{
	//如果没有合约信息，订阅也没有用
	if(NULL == m_marketDataHandler)
	{
		return 0;
	}
	//只要选择调用这个借口，就说明有合约定制需求，创建一个合约类，可以选择发送合约
	pSession->CreatSubInstrument();
	
	CFTDSpecificInstrumentField specificInstrumentField;
	CNamedFieldIterator itor = pFTDCPackage->GetNamedFieldIterator(&specificInstrumentField.m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&specificInstrumentField);
		//寻找合约的代号
		if(specificInstrumentField.InstrumentID=="*")
		{
			//如果是*号，表示订阅所有的合约
			CInstrumentMap *pInstrumentMap = m_marketDataHandler->GetInstrumentMap();
			CInstrumentMap::iterator iter = pInstrumentMap->Begin();		
			while (!iter.IsEnd())
			{
				
				CInstrumentIDType tempfeild;
				tempfeild=iter.GetKey();
				map<CInstrumentIDType,CInstrumentIDType>::iterator itor=n_newInstrument.find(tempfeild);
				if (itor==n_newInstrument.end())
				{
					n_newInstrument.insert(map<CInstrumentIDType,CInstrumentIDType>::value_type(tempfeild,tempfeild));
				}
				//pSession->InsertInstrumentID(*iter,iter.GetKey());
				//	printf("%s->%d",(*iter),iter.GetKey(),);
				//	printf("合约 %s 订阅成功\n",iter.GetKey().getValue());
				REPORT_EVENT(LOG_DEBUG, "InstrumentSub", "合约 %s 订阅成功\n",iter.GetKey().getValue());
				iter++;
			}
			pSession->InsertInstrumentID(0,"*");
		}
		else
		{
			DWORD instrumentCount = m_marketDataHandler->GetInstrumentIDCount(specificInstrumentField.InstrumentID);
			if(instrumentCount==-1)
			{
			//	printf("合约 %s 不在合约列表中! \n",specificInstrumentField.InstrumentID.getValue());
				REPORT_EVENT(LOG_ERROR, "InstrumentSub", "合约 %s 不在合约列表中! \n",specificInstrumentField.InstrumentID.getValue());
				itor.Next();
				continue;
			}
			map<CInstrumentIDType,CInstrumentIDType>::iterator itor=n_newInstrument.find(specificInstrumentField.InstrumentID);
			if (itor==n_newInstrument.end())
			{
				n_newInstrument.insert(map<CInstrumentIDType,CInstrumentIDType>::value_type(specificInstrumentField.InstrumentID,specificInstrumentField.InstrumentID));
			}
			pSession->InsertInstrumentID(instrumentCount,specificInstrumentField.InstrumentID);		
			//printf("合约 %s 订阅成功\n",specificInstrumentField.InstrumentID.getValue());
			REPORT_EVENT(LOG_DEBUG, "InstrumentSub", "合约 %s 订阅成功\n",specificInstrumentField.InstrumentID.getValue());
			//寻找合约对应的流如果已经存在就不挂
			/*
			pSession->Publish(pFieldDissExt->pFlow, pFieldDissExt->wSequenceSeries, 
			pFieldDissExt->nPubStartId);
			*/
		}
		itor.Next();
	}
	return 0;
}



int CMDFront::OnReqUnSubMarketData(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession)
{

	//如果没有合约信息，订阅也没有用
	if(NULL == m_marketDataHandler)
	{
		return 0;
	}
	//只要选择调用这个借口，就说明有合约定制需求，创建一个合约类，可以选择发送合约
	pSession->CreatSubInstrument();
	CFTDRspInfoField rspInfoField;
	SetErrorInfo(&rspInfoField);	
	
	CFTDSpecificInstrumentField specificInstrumentField;
	m_rspPackage.PreparePackage(FTD_TID_RspUnSubMarketData, FTDC_CHAIN_CONTINUE, FTD_VERSION);
	CNamedFieldIterator itor = pFTDCPackage->GetNamedFieldIterator(&specificInstrumentField.m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&specificInstrumentField);
		
		if ( specificInstrumentField.InstrumentID=="*" )
		{
			pSession->DeleteInstrumentID(0);
			continue;
		}

		DWORD instrumentCount = m_marketDataHandler->GetInstrumentIDCount(specificInstrumentField.InstrumentID);
		if(instrumentCount==-1)
		{
			//printf("合约 %s 不在合约列表中! \n",specificInstrumentField.InstrumentID.getValue());
			REPORT_EVENT(LOG_ERROR, "InstrumentSub", "合约 %s 不在合约列表中! \n",specificInstrumentField.InstrumentID.getValue());
			itor.Next();
			continue;
		}

		if(pSession->DeleteInstrumentID(instrumentCount))
		{
			//printf("合约 %s 取消订阅成功\n",specificInstrumentField.InstrumentID.getValue());
			REPORT_EVENT(LOG_DEBUG, "InstrumentSub", "合约 %s 取消订阅成功\n",specificInstrumentField.InstrumentID.getValue());
			rspInfoField.ErrorMsg = "合约取消订阅成功";
			CFTDSpecificInstrumentField ctempinstrument;
			ctempinstrument.InstrumentID=specificInstrumentField.InstrumentID;
			FTDC_ADD_FIELD(&m_rspPackage, &ctempinstrument);
			FTDC_ADD_FIELD(&m_rspPackage, &rspInfoField);
		}
		else
		{
			//printf("合约 %s 取消订阅失败\n",specificInstrumentField.InstrumentID.getValue());
			REPORT_EVENT(LOG_DEBUG, "InstrumentSub", "合约 %s 取消订阅失败\n",specificInstrumentField.InstrumentID.getValue());
			rspInfoField.ErrorMsg = "取消订阅失败";
			rspInfoField.ErrorID=-1;
			CFTDSpecificInstrumentField ctempinstrument;
			ctempinstrument.InstrumentID=specificInstrumentField.InstrumentID;
			FTDC_ADD_FIELD(&m_rspPackage, &ctempinstrument);
			FTDC_ADD_FIELD(&m_rspPackage, &rspInfoField);
		}
		itor.Next();
	}
	m_rspPackage.SetChain(FTDC_CHAIN_LAST);
	pSession->SendRequestPackage(&m_rspPackage);

	return 0;
}



void CMDFront::RspTopicMarketData(CFTDCSession *pSession, CFTDCPackage *pFTDCPackage,
								  CReadOnlyTopicIDType &TopicID)
{

	if (!m_marketDataHandler) return;
	CTopicMarketDataMap::iterator iterTopic = m_marketDataHandler->m_mapTopicMarketData.find(TopicID.getValue());
	if(iterTopic == m_marketDataHandler->m_mapTopicMarketData.end())
	{	
		//没有找到相应的topic,退出

		return;
	}

	CMarketDataMap * pMarketDataMap = iterTopic->second;
	m_rspPackage.PrepareResponse(pFTDCPackage, FTD_TID_RtnDepthMarketData, FTDC_CHAIN_CONTINUE, FTD_VERSION);

	CFTDDepthMarketDataField * p =NULL;

	map<CInstrumentIDType,CInstrumentIDType>::iterator itor=n_newInstrument.begin();
	for (;itor!=n_newInstrument.end();)
	{
		CInstrumentIDType cinstrument=itor->second;
		CMarketDataMap::iterator iter = pMarketDataMap->find(itor->second);
		if(iter!=pMarketDataMap->end())
		{
			p = iter->second;
			CFTDDepthMarketDataField fieldDepthMarketData;
			CopyDepthMarketDataEntity(&fieldDepthMarketData, p);
			while (FTDC_ADD_FIELD(&m_rspPackage, &fieldDepthMarketData) < 0)
			{
				m_rspPackage.SetRequestId(TopicID);
				pSession->SendRequestPackage(&m_rspPackage);
				m_rspPackage.PrepareResponse(pFTDCPackage, FTD_TID_RtnDepthMarketData, FTDC_CHAIN_CONTINUE, FTD_VERSION);
			}
			n_newInstrument.erase(itor++);
		}else{
			itor++;
		}
		
	}
	m_rspPackage.SetChain(FTDC_CHAIN_LAST);
	m_rspPackage.SetRequestId(TopicID);
	pSession->SendRequestPackage(&m_rspPackage);
	
	//需要发回查询深度行情应答
// 	CTopicMarketDataIterator *pIterator = 
// 		m_pMDFrontServiceInterface->QueryDepthMarketData(
// 		TopicID);
// 	if (pIterator == NULL)
// 	{
// 		return ;
// 	}
// 
// 	m_rspPackage.PrepareResponse(pFTDCPackage, FTD_TID_RtnDepthMarketData, FTDC_CHAIN_CONTINUE, FTD_VERSION);
// 	CTopicMarketData *pTopicMarketData = NULL;
// 	while ((pTopicMarketData = pIterator->next()) != NULL )
// 	{
// 		CFTDDepthMarketDataField fieldDepthMarketData;
// 		CopyDepthMarketDataEntity(&fieldDepthMarketData, pTopicMarketData);
// 		while (FTDC_ADD_FIELD(&m_rspPackage, &fieldDepthMarketData) < 0)
// 		{
// 			m_rspPackage.SetRequestId(TopicID);
// 			pSession->SendRequestPackage(&m_rspPackage);
// 			m_rspPackage.PrepareResponse(pFTDCPackage, FTD_TID_RtnDepthMarketData, FTDC_CHAIN_CONTINUE, FTD_VERSION);
// 		}
// 	}
// 
// 	m_rspPackage.SetChain(FTDC_CHAIN_LAST);
// 	m_rspPackage.SetRequestId(TopicID);
// 	pSession->SendRequestPackage(&m_rspPackage);
// 
// 	delete pIterator;
}

#define GET_PART_MARKETDATA(name)											\
		case FTD_FID_##name:												\
			{																\
				CFTD##name##Field field##name;								\
				titor.Retrieve(&field##name.m_Describe, &field##name);		\
				Copy##name##Entity(pWriteableTopicMarketDataVersion, &field##name);	\
			}																\
			break;

void CMDFront::RspTopicMarketDataVersion(CFTDCSession *pSession, CFTDCPackage *pFTDCPackage, 
		CReadOnlyTopicIDType &TopicID, CReadOnlySequenceNoType &Version)
{
// 	CReadOnlyFlow *pFlow = m_pInMemFlowManager->GetFlow((WORD)TopicID);
// 	if (pFlow == NULL)
// 	{
// 		return;
// 	}
// 	int nSequenceNo = (int)Version;
// 	int nVersionNo = nSequenceNo/TOPIC_MARKETDATA_VERSION_INTERVAL*
// 		TOPIC_MARKETDATA_VERSION_INTERVAL;
// 
// 	typedef map<CInstrumentIDType, CWriteableTopicMarketDataVersion> CMarketDataVersionMap;
// 	CMarketDataVersionMap mapMarketDataVersion;
// 	CTopicMarketDataVersionIterator *pIterator = 
// 		m_pMDFrontServiceInterface->QueryTopicMarketDataVersion(
// 		TopicID, nVersionNo);
// 	CTopicMarketDataVersion *pTopicMarketDataVersion = NULL;
// 	while ((pTopicMarketDataVersion = pIterator->next())!=NULL)
// 	{
// 		mapMarketDataVersion[pTopicMarketDataVersion->InstrumentID] = 
// 			*pTopicMarketDataVersion;
// 	}
// 	delete pIterator;
// 	
// 	CFlowReader reader;
// 	reader.AttachFlow(pFlow, nVersionNo);
// 	while (reader.GetId() < nSequenceNo)
// 	{
// 		m_rspPackage.Allocate(FTDC_PACKAGE_MAX_SIZE+FTDCHLEN);
// 		if(!reader.GetNext(&m_rspPackage))
// 		{
// 			break;
// 		}
// 		CFTDMarketDataUpdateTimeField fieldMarketDataUpdateTime;
// 		if (FTDC_GET_SINGLE_FIELD(&m_rspPackage, &fieldMarketDataUpdateTime) <= 0)
// 		{
// 			//必须找到合约代码
// 			continue;
// 		}
// 		CWriteableTopicMarketDataVersion *pWriteableTopicMarketDataVersion =
// 			&mapMarketDataVersion[fieldMarketDataUpdateTime.InstrumentID];
// 		CopyMarketDataUpdateTimeEntity(pWriteableTopicMarketDataVersion, &fieldMarketDataUpdateTime);
// 
// 		TFieldHeader fieldHeader;
// 		CFieldTypeIterator titor = m_rspPackage.GetFieldTypeIterator();
// 		while (!titor.IsEnd())
// 		{
// 			titor.RetrieveHeader(fieldHeader);
// 			switch(fieldHeader.FieldID)
// 			{
// 			GET_PART_MARKETDATA(MarketDataBase);
// 			GET_PART_MARKETDATA(MarketDataStatic);
// 			GET_PART_MARKETDATA(MarketDataLastMatch);
// 			GET_PART_MARKETDATA(MarketDataBestPrice);
// 			GET_PART_MARKETDATA(MarketDataBid23);
// 			GET_PART_MARKETDATA(MarketDataAsk23);
// 			GET_PART_MARKETDATA(MarketDataBid45);
// 			GET_PART_MARKETDATA(MarketDataAsk45);
// 			default:
// 				break;
// 			}
// 			titor.Next();
// 		}
// 	}
// #ifndef _UNIT_TEST_
// 	m_rspPackage.PrepareResponse(pFTDCPackage, FTD_TID_RtnDepthMarketData, FTDC_CHAIN_CONTINUE, FTD_VERSION);
// #else
// 	m_rspPackage.PreparePackage(FTD_TID_RtnDepthMarketData, FTDC_CHAIN_CONTINUE, FTD_VERSION);
// #endif
// 	CMarketDataVersionMap::iterator mdvitor = mapMarketDataVersion.begin();
// 	for(;mdvitor != mapMarketDataVersion.end(); mdvitor++)
// 	{
// 		CFTDDepthMarketDataField fieldDepthMarketData;
// 		CopyDepthMarketDataEntity(&fieldDepthMarketData, &((*mdvitor).second));
// 		while (FTDC_ADD_FIELD(&m_rspPackage, &fieldDepthMarketData) < 0)
// 		{
// 			m_rspPackage.SetRequestId(TopicID);
// #ifndef _UNIT_TEST_
// 			pSession->SendRequestPackage(&m_rspPackage);
// 			m_rspPackage.PrepareResponse(pFTDCPackage, FTD_TID_RtnDepthMarketData, FTDC_CHAIN_CONTINUE, FTD_VERSION);
// #else
// 			m_rspPackage.PreparePackage(FTD_TID_RtnDepthMarketData, FTDC_CHAIN_CONTINUE, FTD_VERSION);
// #endif
// 		}
// 	}
// 
// 	m_rspPackage.SetChain(FTDC_CHAIN_LAST);
// 	m_rspPackage.SetRequestId(TopicID);
// #ifndef _UNIT_TEST_
// 	pSession->SendRequestPackage(&m_rspPackage);
// #endif
}

void CMDFront::OnReqUserLogout(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession)
{
	MDSERVICE_SYNC;
	if (pSession == NULL)
	{
		REPORT_EVENT(LOG_INFO, "Session", 
			"CMDFront::OnReqUserLogout NULL session"); 
		return;
	}

	CFTDReqUserLogoutField fieldFtdcReqUserLogout;
	if (FTDC_GET_SINGLE_FIELD(pFTDCPackage, &fieldFtdcReqUserLogout) <=0 )
	{
		REPORT_EVENT(LOG_CRITICAL, "ErrorPackage", 
			"CMDFront::OnReqUserLogout Can't find CFTDReqUserLogoutField, session [0x%08x]", 
			pSession->GetSessionID());
		return ;
	}

// 	MDTSessionRef sessionRef;
// 	sessionRef.frontID = m_nFrontID;
// 	sessionRef.sessionID = pSession->GetSessionID();
	CFTDRspInfoField rspInfoField;
	SetErrorInfo(&rspInfoField);
	CSessionIDType loginSessionID = pSession->GetSessionID();

	bool bRet = true;
	rspInfoField.ErrorMsg = m_pErrorEngine->getErrorMsg(rspInfoField.ErrorID);


	m_rspPackage.PreparePackage(FTD_TID_RspUserLogout, FTDC_CHAIN_LAST, FTD_VERSION);

	CFTDRspUserLogoutField fieldFtdcRspUserLogout;
	fieldFtdcRspUserLogout.BrokerID = fieldFtdcReqUserLogout.BrokerID;
	fieldFtdcRspUserLogout.UserID = fieldFtdcReqUserLogout.UserID;
	FTDC_ADD_FIELD(&m_rspPackage, &fieldFtdcRspUserLogout);
	FTDC_ADD_FIELD(&m_rspPackage, &rspInfoField);
	pSession->SendRequestPackage(&m_rspPackage);

	if (rspInfoField.ErrorID.getValue() == ERROR_NONE)
	{
		ClearSessionOwner(pSession->GetSessionID());
	}
	REPORT_EVENT(LOG_INFO, "MdLogout", "%s %s %s,front=%d,session=%d,message=%s",
		(rspInfoField.ErrorID.getValue()==ERROR_NONE)?"Success":"Failure",
		pSession->GetChannel()->GetRemoteName(), fieldFtdcRspUserLogout.UserID.getValue(),
		m_nFrontID,loginSessionID.getValue(),
		rspInfoField.ErrorMsg.getValue());
	SendToDialogFlow(pSession, &m_rspPackage);
}

void CMDFront::PublishFlows(CFTDCPackage *pSubscribePackage, CFTDCSession *pSession, 
							CFTDCPackage *pRspPackage)
{
//	CDateType TradingDay = "20121111";
	vector<CFTDDisseminationFieldExt> fieldDisseminations;
	CFTDDisseminationField disseminationField;
	CFTDDisseminationFieldExt fieldDisseminationExt;

	TMDFrontSessionInfo *pSessionInfo = m_mapSessionInfo.Find(pSession->GetSessionID());
	if (pSessionInfo == NULL)
	{
		return;
	}

	char buf[256];

	sprintf(buf, "User=%s,TradingDay=%s,DataCenterID=%d,subscribe:", pSessionInfo->UserID.getValue(),
		pSessionInfo->TradingDay.getValue(), pSessionInfo->DataCenterID.getValue());

	string strLogInfo = buf;
	
	CNamedFieldIterator itor = pSubscribePackage->GetNamedFieldIterator(&CFTDDisseminationField::m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&disseminationField);
		sprintf(buf, "[%d][%d],", disseminationField.SequenceSeries.getValue(),
			disseminationField.SequenceNo.getValue());
		strLogInfo += buf;
		memset(&fieldDisseminationExt, 0, sizeof(fieldDisseminationExt));
		fieldDisseminationExt.nSubStartId = disseminationField.SequenceNo;
		fieldDisseminationExt.wSequenceSeries = disseminationField.SequenceSeries;
		
		CTopicIDType TopicID = (int)disseminationField.SequenceSeries;
// 		if (!m_pMDFrontServiceInterface->CheckPartTopicSubscribe(
// 			pSessionInfo->ParticipantID, TopicID))
// 		{
// 			itor.Next();
// 			continue;
// 		}
		//如果客户端的交易日与交易引擎不符，则从0开始订阅
// 		if (pSessionInfo->TradingDay != TradingDay	&& fieldDisseminationExt.nSubStartId != -1)
// 		{
// 			fieldDisseminationExt.nSubStartId = 0;
// 		}
		//增加起始序号有效性判断,如果起始序号小于-1,则清零
		if (fieldDisseminationExt.nSubStartId < -1)
		{
			fieldDisseminationExt.nSubStartId = 0;
		}

		fieldDisseminationExt.pFlow = m_pFlowManager->GetFlow(fieldDisseminationExt.wSequenceSeries);
		
		if (fieldDisseminationExt.pFlow == NULL)
		{
			itor.Next();
			continue;
		}
		fieldDisseminations.push_back(fieldDisseminationExt);
		itor.Next();
	}

	strLogInfo += "publish:";
	
	CDataCenterIDType DataCenterID;
//	m_pMDFrontServiceInterface->GetDataCenterID(DataCenterID);

	DataCenterID = 1;
	bool bCheckDataCenter = pSessionInfo->DataCenterID != 0 && 
		pSessionInfo->DataCenterID != DataCenterID;
	
	int i=0;
	//构造登录应答报文的分发域，告知客户端每个流的订阅的起始位置
	m_rspPackage.PreparePackage(FTD_TID_IntlRtnDissemination, FTDC_CHAIN_LAST, FTD_VERSION);
	for (i=0; i<fieldDisseminations.size(); i++)
	{
		CFTDDisseminationFieldExt *pFieldDissExt = &fieldDisseminations[i];
		//int nBorkenSeqNo = m_pInMemFlowManager->GetFlowBroken(pFieldDissExt->wSequenceSeries);
		int nBorkenSeqNo = 0;
		if (bCheckDataCenter && nBorkenSeqNo < pFieldDissExt->nSubStartId)
		{
			pFieldDissExt->nPubStartId = nBorkenSeqNo;
		}
		else
		{
			pFieldDissExt->nPubStartId = pFieldDissExt->nSubStartId;
		}
		
		//增加起始序号有效性判断,如果起始序号小于0且非-1,则清零
		if (pFieldDissExt->nSubStartId == -1)
		{
			pFieldDissExt->nPubStartId = pFieldDissExt->pFlow->GetCount();
		}
		else if (pFieldDissExt->nSubStartId < 0)
		{
			pFieldDissExt->nPubStartId = 0;
		}
		disseminationField.SequenceSeries = pFieldDissExt->wSequenceSeries;
		disseminationField.SequenceNo = pFieldDissExt->nPubStartId;

		FTDC_ADD_FIELD(&m_rspPackage, &disseminationField);
		//m_rspPackage.AddField(&CFTDDisseminationField::m_Describe, &disseminationField);

	}
	if (pRspPackage != NULL)
	{
		CFTDRspInfoField ftdRspInfoField;
		ftdRspInfoField.ErrorID = 0;
		ftdRspInfoField.ErrorMsg = "正确";
		pRspPackage->BufAddRef(&m_rspPackage);
		FTDC_ADD_FIELD(pRspPackage, &ftdRspInfoField);
		pSession->SendRequestPackage(pRspPackage);
		pRspPackage->BufRelease();
	}
	//走对话流会导致登录应答后到，这里直接发送
	pSession->SendRequestPackage(&m_rspPackage);

// 	//发送数据流回退应答
// 	m_rspPackage.PreparePackage(FTD_TID_RtnFlowMessageCancel, FTDC_CHAIN_LAST, FTD_VERSION);
// 	CFTDFlowMessageCancelField fieldFlowMessageCancel;
// 	for (i=0; i<fieldDisseminations.size(); i++)
// 	{
// 		if (fieldDisseminations[i].nSubStartId > fieldDisseminations[i].nPubStartId)
// 		{
// 			//fieldFlowMessageCancel.DataCenterID = m_pInMemFlowManager->GetDataCenterBorken();
// 			fieldFlowMessageCancel.DataCenterID = 2;
// 			fieldFlowMessageCancel.StartSequenceNo = fieldDisseminations[i].nPubStartId;
// 			fieldFlowMessageCancel.EndSequenceNo = fieldDisseminations[i].nSubStartId;
// 			fieldFlowMessageCancel.SequenceSeries = fieldDisseminations[i].wSequenceSeries;
// 			fieldFlowMessageCancel.TradingDay = pSessionInfo->TradingDay;
// 			FTDC_ADD_FIELD(&m_rspPackage, &fieldFlowMessageCancel);
// 		}
// 	}
// 	if (m_rspPackage.Length() > 0)
// 	{
// 		pSession->SendRequestPackage(&m_rspPackage);
// 	}

	//对于客户端订阅的每一个流，若为快速恢复，则直接发送该主题的行情快照
	//重传也要发送快照
	for (i=0; i<fieldDisseminations.size(); i++)
	{
		CFTDDisseminationFieldExt *pFieldDissExt = &fieldDisseminations[i];
		CTopicIDType TopicID = (int)pFieldDissExt->wSequenceSeries;
		if (pFieldDissExt->nSubStartId == -1)
		{
			RspTopicMarketData(pSession, pSubscribePackage, TopicID);
		}
		else if(pFieldDissExt->nPubStartId > 0)
		{
			RspTopicMarketDataVersion(pSession, pSubscribePackage, TopicID, pFieldDissExt->nPubStartId);
		}
	
		sprintf(buf, "[%d][%d],", pFieldDissExt->wSequenceSeries,
			pFieldDissExt->nPubStartId);
		strLogInfo += buf;
		pSession->Publish(pFieldDissExt->pFlow, pFieldDissExt->wSequenceSeries, 
			pFieldDissExt->nPubStartId);
	}

	REPORT_EVENT(LOG_INFO, "MdSubscribe", strLogInfo.c_str());
}

void CMDFront::OnReqSubscribeTopic(CFTDCPackage *pPackage, CFTDCSession *pSession)
{

	MDSERVICE_SYNC;
	CFTDCPackage pkgResponse;
	pkgResponse.PrepareResponse(pPackage, FTD_TID_RspSubscribeTopic, FTDC_CHAIN_LAST, FTD_VERSION);

	pSession->RspAllSubInstrumentID(FTD_TID_RspSubMarketData);
	//pSession->DisplayInstrumentID();
	//PublishFlows(pFTDCPackage, pSession, NULL);		

	PublishFlows(pPackage, pSession, &pkgResponse);

}

int CMDFront::OnReqQryTopic(CFTDCPackage *pPackage, CFTDCSession *pSession)
{
	MDSERVICE_SYNC;
	TMDFrontSessionInfo *pSessionInfo = m_mapSessionInfo.Find(pSession->GetSessionID());;
	if (pSessionInfo == NULL)
	{
		return 0;
	}
	
	CFTDRspInfoField ftdRspInfoField;
	ftdRspInfoField.ErrorID = 0;
	ftdRspInfoField.ErrorMsg = "正确";
	m_rspPackage.PrepareResponse(pPackage, FTD_TID_RspQryTopic,
		FTDC_CHAIN_LAST, FTD_VERSION);
	
	CFTDDisseminationField fieldDissemination;
	if (FTDC_GET_SINGLE_FIELD(pPackage, &fieldDissemination) <= 0)
	{
		return 0;
	}
	CReadOnlyFlow *pFlow = NULL;
	CTopicIDType TopicID = (int)fieldDissemination.SequenceSeries;
//	if (m_pMDFrontServiceInterface->CheckPartTopicSubscribe(
//		pSessionInfo->ParticipantID, TopicID))
//	{
	//	pFlow = m_pInMemFlowManager->GetFlow(fieldDissemination.SequenceSeries);
//	}

//	fieldDissemination.SequenceNo = (pFlow==NULL)?0:pFlow->GetCount();

	FTDC_ADD_FIELD(&m_rspPackage, &fieldDissemination);
	FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);

	//发送应答
	pSession->SendRequestPackage(&m_rspPackage);

	return 0;
}

int CMDFront::AddSession(CFTDCSession *pSession)
{
	OnSessionConnected(pSession);
	m_pReactor->RegisterIO(pSession);
	pSession->RegisterPackageHandler(this);
	pSession->RegisterSessionCallback(this);
	return 0;
}

int CMDFront::DelSession(DWORD dwSessionID, int nErrorCode)
{
	TMDFrontSessionInfo *pSessionInfo = m_mapSessionInfo.Find(dwSessionID);
	if (pSessionInfo == NULL)
	{
		return -1;
	}
	pSessionInfo->pSession->Disconnect(nErrorCode);
	return 0;
}

CFTDCSession * CMDFront::GetSession(DWORD dwSessionID)
{
	TMDFrontSessionInfo *pSessionInfo = m_mapSessionInfo.Find(dwSessionID);
	if (pSessionInfo == NULL)
	{
		return NULL;
	}
	return (CFTDCSession *)pSessionInfo->pSession;
}

int CMDFront::HandleEvent(int nEventID, DWORD dwParam, void *pParam)
{
	switch(nEventID) {
	case UM_MDFRONT_ADD_SESSION:
		return AddSession((CFTDCSession *)pParam);
	case UM_MDFRONT_DEL_SESSION:
		return DelSession(dwParam, 0);
	case UM_MDFRONT_COMMPHASE_CHANGE:
		OnCommPhaseChange((WORD)dwParam);
		break;
	default:
		break;
	}
	return 0;
}


//合约查询应答
int CMDFront::OnRspQryDepthMarketData(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession)
{
	//如果没有合约信息，订阅也没有用
	if(NULL == m_marketDataHandler)
	{
		return 0;
	}
	
	m_rspPackage.PrepareResponse(pFTDCPackage, FTD_TID_RspQryDepthMarketData, FTDC_CHAIN_LAST, FTD_VERSION);
	
	//返回行情应答
	CFTDRspInfoField ftdRspInfoField;
	ftdRspInfoField.ErrorID = 0;
	ftdRspInfoField.ErrorMsg = "正确";
	
	CFTDQryMarketDataField QryMarketDataField;
	CNamedFieldIterator itor = pFTDCPackage->GetNamedFieldIterator(&QryMarketDataField.m_Describe);
	while (!itor.IsEnd())
	{
		itor.Retrieve(&QryMarketDataField);
		if(QryMarketDataField.InstrumentID.isValid()&&QryMarketDataField.ExchangeID.isValid())
		{			
			CFTDRspMarketDataField QspMarketDataField;
			CFTDDepthMarketDataField *pFTDDepthMarketDataField = m_marketDataHandler->GetMaraketData(QryMarketDataField.ExchangeID,QryMarketDataField.InstrumentID);
			if(NULL!=pFTDDepthMarketDataField)
			{
				CopyRspMarketDataEntity(&QspMarketDataField,pFTDDepthMarketDataField);
				FTDC_ADD_FIELD(&m_rspPackage, &QspMarketDataField);
				FTDC_ADD_FIELD(&m_rspPackage, &ftdRspInfoField);
				pSession->SendRequestPackage(&m_rspPackage);
			}
		}
		itor.Next();
	}
	return 0;
}



void CMDFront::OnRtnMarketDataInstrumentState(CFTDCSession *pSession, CFTDCPackage *pFTDCPackage,
											  CReadOnlyTopicIDType &TopicID)
{
	
	if (!m_marketDataHandler) return;
	
	m_rspPackage.PrepareResponse(pFTDCPackage, FTD_TID_RtnQmdInstrumentStatu, FTDC_CHAIN_CONTINUE, FTD_VERSION);
	
	CMdInstrumentStateMap::iterator itor= m_marketDataHandler->m_instrumetstate->begin();
	for (;itor!=m_marketDataHandler->m_instrumetstate->end();)
	{
		CFTDQmdInstrumentStateField *cinstrument=itor->second;
		
		while (FTDC_ADD_FIELD(&m_rspPackage, cinstrument) < 0)
		{
			m_rspPackage.SetRequestId(TopicID);
			pSession->SendRequestPackage(&m_rspPackage);
			m_rspPackage.PrepareResponse(pFTDCPackage, FTD_TID_RtnQmdInstrumentStatu, FTDC_CHAIN_CONTINUE, FTD_VERSION);
		}
		itor++;
	}	
	
	m_rspPackage.SetChain(FTDC_CHAIN_LAST);
	m_rspPackage.SetRequestId(TopicID);
	pSession->SendRequestPackage(&m_rspPackage);
	
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMDFrontManager::CMDFrontManager(CReactor *pReactor, DWORD nFrontID, 
								 CMDFlowManager *pFlowManager,CMarketDataHandler * pMarketDataHandler)
:CSessionFactory(pReactor, 1000)
{
	m_nNextFront = 0;
	m_nFrontID = nFrontID;
	m_pFlowManager = pFlowManager;
	m_pMarketDataHandler = pMarketDataHandler;
}

CMDFrontManager::~CMDFrontManager()
{
	int nFrontCount = m_Reactors.size();
	for (int i=0; i<nFrontCount; i++)
	{
		CSelectReactor *pReactor = (CSelectReactor *)m_Reactors[i];
		CMDFront *pMDFront = m_Fronts[i];
		pReactor->Stop();
		delete pMDFront;
		delete pReactor;
	}
}

CSession *CMDFrontManager::CreateSession(CChannel *pChannel, DWORD dwMark)
{

	if (m_nNextFront >= m_Reactors.size())
	{
		m_nNextFront = 0;
	}
	CFTDCSession *pSession =  new CFTDCSession(m_Reactors[m_nNextFront], pChannel);
	m_Fronts[m_nNextFront]->PostEvent(UM_MDFRONT_ADD_SESSION, 0, pSession);
	
	pSession->SetHeartbeatMode(XMPHBT_SLAVE_MODE);

	m_nNextFront++;

	return NULL;//一定要返回NULL
}

int CMDFrontManager::HandleEvent(int nEventID, DWORD dwParam, void *pParam)
{
	if (nEventID == UM_MDFRONT_SERVICE_SYNC)
	{
//		printf("%p %d CMDFrontManager::HandleEvent UM_MDFRONT_SERVICE_SYNC\n", this, dwParam);
		CMDServiceSynchronizer *pSynchronizer = (CMDServiceSynchronizer *)pParam;
		pSynchronizer->Start();
		return 0;
	}
	else if (nEventID == UM_MDFRONT_DEL_SESSION)
	{
		for (int i=0; i<m_Fronts.size(); i++)
		{
			m_Fronts[i]->PostEvent(UM_MDFRONT_DEL_SESSION, dwParam, NULL);
		}
	}
	return CSessionFactory::HandleEvent(nEventID, dwParam, pParam);
}

void CMDFrontManager::OnCommPhaseChange(WORD nCommPhaseNo)
{
	for (int i=0; i<m_Fronts.size(); i++)
	{
		m_Fronts[i]->PostEvent(UM_MDFRONT_COMMPHASE_CHANGE,
			(DWORD)nCommPhaseNo, NULL);
	}
}

CSelectReactor * CMDFrontManager::CreateFront(int nFrontCount)
{
	
// 	for (int i=0; i<nFrontCount; i++)
// 	{
// 		CSelectReactor *pReactor = new CSelectReactor;
// 		CMDFront *pMDFront = new CMDFront(m_pReactor, m_nFrontID, m_pFlowManager, this,m_pUserCheck,m_pMarketDataHandler);
// 		m_Reactors.push_back(m_pReactor);
// 		m_Fronts.push_back(pMDFront);
// 		pReactor->Create();
// 	}

	//20130814 由于AttachObserver只能通知一个线程，所以front只允许一个线程

	CSelectReactor *pReactor = new CSelectReactor;
	CMDFront *pMDFront = new CMDFront(pReactor, m_nFrontID, m_pFlowManager, this, m_pMarketDataHandler);
	m_Reactors.push_back(pReactor);
	m_Fronts.push_back(pMDFront);
	pReactor->Create();
	return pReactor;
}


void CMDFrontManager::DisconnectFronts()
{
	for (int i=0; i<m_Fronts.size(); i++)
	{
		CMDFront *cmd=m_Fronts[i];
		cmd->ChangeDateDisconnectAll();
	}
}