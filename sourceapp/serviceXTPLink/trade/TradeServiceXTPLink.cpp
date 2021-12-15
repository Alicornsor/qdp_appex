  /////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file TradeServiceXTPLink.h
///@brief实现了类CTradeServiceXTPLink
///@history 
///20130703	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "TradeServiceXTPLink.h"
#include "XtpPackageDesc.h"
#include "UFCopy.h"
#include "FtdPackageDesc.h"
#include "public.h"
#include "BaseCheck.h"
#include "ExchangeLinkManager.h"
#include "BaseExchApi.h"
#include "CConfig.h"
#include "system.h"

extern CConfig	*g_pConfig; // 全局的配置文件对象指针 cgm 2015-08-20。

//复制sessionid等信息，便于回报给客户
#define COPY_XTP_HEADER_RSPINFO(target,source) \
	(target)->SessionID=(source)->SessionID; \
	(target)->FrontID=(source)->FrontID; \
	(target)->RequestID=(source)->RequestID; \

extern CExchangeLinkManager* g_pExchangeLinkManager;

CTradeServiceXTPLink::CTradeServiceXTPLink(CTradeServiceImpl *pTradeService,
										   CErrorEngine *pErrorEngine,IServiceResponser *pServiceResponser,CFlow* pTradeResult,bool verbose)
{
	m_pTradeService=pTradeService;
	m_pErrorEngine=pErrorEngine;
	m_pRspMessage = new CXTPPackage;
	m_pRspMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	m_pServiceResponser = pServiceResponser;
	m_verbose = verbose;
	m_pTradeResult = pTradeResult;
	m_SeatOrdActionLocalIDXTPMap.clear();
	m_DceOrderActionMap.clear();

	m_iActionNums = atoi(g_pConfig->getConfig("ActionWarnNums"));
	if (m_iActionNums<1)
	{
		m_iActionNums=100;
	} 
}

CTradeServiceXTPLink::~CTradeServiceXTPLink()
{
	if(m_pRspMessage != NULL)
		m_pRspMessage->Release();
	delete m_pRspMessage;
}

bool CTradeServiceXTPLink::handleRequest(CXTPPackage *pPackage, const TSessionRef &sessionRef,DWORD responseSession)
{
	return true;
}

bool CTradeServiceXTPLink::handleMessage(CXTPPackage *pPackage, const TSessionRef &sessionRef)
{
	//默认为true
	bool bSuccess=true;
	char* errMsg;
	int errorCode;
	switch (pPackage->GetTid())
	{
		case TID_ReqOrderAction:
		{			
			COrderActionField field;
			if (!XTP_GET_SINGLE_FIELD(pPackage,&field))
			{
				bSuccess=false;
				break;
			}

			//业务处理
			CWriteableOrderAction theOrderAction;
			theOrderAction.init();
			CopyOrderActionEntity(&theOrderAction,&field);
			bSuccess=m_pTradeService->ReqOrderAction(&theOrderAction ,sessionRef,&m_Transaction);	
			CopyOrderActionEntity(&field, &theOrderAction);
			//一定要在这里加上这一句，ReportError必须与getLastError成对出现
			m_pErrorEngine->getLastError(&errorCode,&errMsg);	

			//发送
			if (bSuccess)
			{
				CBaseExchApi *pBaseExchApi = g_pExchangeLinkManager->getExchangeLink(field.APIID);
				if(pBaseExchApi == NULL || !pBaseExchApi->GetStatus())
				{
					bSuccess=false;					
				}
				else
				{	
					//撤单通过检查，直接发送给交易
					int ret = pBaseExchApi->ReqOrderAction(field);
					if(ret!=0)				
					{
						bSuccess=false;	
						if (ret == -2)
						{
							m_pErrorEngine->reportError(ERROR_FLOWCONTROL_TOOLARGE_UNFINISHED_ORDERS);
						}
						else if (ret == -3)
						{
							m_pErrorEngine->reportError(ERROR_FLOWCONTROL_TOOQUICK_ORDERSPEED_FORORDER);
						}
						else
						{
							m_pErrorEngine->reportError(ERROR_NO_AVAIL_EXCHANGE_SEAT);
						}
						
						m_pErrorEngine->getLastError(&errorCode,&errMsg);
					}
					else
					{
						//通过一切检查，发包成功，把请求存储起来
						SaveReqHdrAndWtOrdAct(theOrderAction.SeatID,theOrderAction.ActionLocalID,pPackage->GetXTPHeader(),&theOrderAction);	
						if (theOrderAction.ExchangeID == EXID_DCE)
						{
							UINT4 OrderSysID = atoi(theOrderAction.OrderSysID.getValue());
							CDCEActionMap::iterator iter = m_DceOrderActionMap.find(OrderSysID);
							if (iter != m_DceOrderActionMap.end())
							{
								iter->second.ActionIdVec.push_back(atoi(theOrderAction.ActionLocalID.getValue()));
								iter->second.size += 1;
							}
							else
							{
								TActionInfo info;
								memset(&info,0,sizeof(TActionInfo));
								info.ActionIdVec.push_back(atoi(theOrderAction.ActionLocalID.getValue()));
								info.size=1;
								info.cur_posi=0;
								m_DceOrderActionMap.insert(CDCEActionMap::value_type(OrderSysID,info));
							}
						}
					}	
				}			
			}
			
			//结果处理，如果是反演，不处理结果
			if (pPackage->GetNoReplayFlag())
			{
				if (!bSuccess)
				{
					//撤单检查失败，直接给客户应答
					m_pRspMessage->PrepareResponse(pPackage,TID_RspOrderAction);
					CRspInfoField responseField;

					responseField.ErrorID = errorCode;
					responseField.ErrorMsg = errMsg;
					REPORT_EVENT(LOG_CRITICAL,"CTradeServiceXTPLink", "撤单错误，原因=[%s]",responseField.ErrorMsg.getValue());
					XTP_ADD_FIELD(m_pRspMessage,&field);
					XTP_ADD_FIELD(m_pRspMessage,&responseField);
					m_pRspMessage->MakePackage();
					if(m_pTradeResult->Append(m_pRspMessage->Address(), m_pRspMessage->Length())<0)
					{
						bSuccess=false;				
					}
				}

			/*	pPackage->MakeNoBufPackage();
				m_pTradeResult->Append(pPackage->Address(), pPackage->Length());
				pPackage->Pop(XTPHLEN);*/
			}

			break;
		}
	case TID_RspOrderAction:
		{
			CRspInfoField exRspInfoField;
			COrderActionField orderActionField;
			XTP_GET_SINGLE_FIELD(pPackage,&exRspInfoField);
			XTP_GET_SINGLE_FIELD(pPackage,&orderActionField);
			CXTPHdrOrderAction *pHdrOrd=GetReqHdrAndOrdAct(orderActionField.SeatID,orderActionField.ActionLocalID);
			if (pHdrOrd == NULL && orderActionField.ExchangeID == EXID_DCE)
			{
				CDCEActionMap::iterator iter = m_DceOrderActionMap.find(atoi(orderActionField.OrderSysID.getValue()));
				if (iter != m_DceOrderActionMap.end() &&
					iter->second.cur_posi <iter->second.size &&
					iter->second.ActionIdVec[iter->second.cur_posi] >0)
				{
					memset(tmp,0,sizeof(tmp));
					sprintf(tmp,"%012u",iter->second.ActionIdVec[iter->second.cur_posi++]);
					orderActionField.ActionLocalID = tmp;
					pHdrOrd=GetReqHdrAndOrdAct(orderActionField.SeatID,orderActionField.ActionLocalID);
				}
			}
			
			//准备报文
			m_pRspMessage->PreparePublish(TID_RspOrderAction);
			TXTPHeader * pRspHdr=m_pRspMessage->GetXTPHeader();			

			COrderField order;
			if(pHdrOrd!=NULL)
			{
				bSuccess=m_pTradeService->RspOrderAction(&order,pHdrOrd->m_pWritableOrderAction,&orderActionField,&exRspInfoField,sessionRef,&m_Transaction);
				orderActionField.UserOrderActionLocalID = pHdrOrd->m_pWritableOrderAction->UserOrderActionLocalID;
				orderActionField.UserOrderLocalID = pHdrOrd->m_pWritableOrderAction->UserOrderLocalID;
				orderActionField.BrokerID = pHdrOrd->m_pWritableOrderAction->BrokerID;
				orderActionField.UserID = pHdrOrd->m_pWritableOrderAction->UserID;
				orderActionField.InvestorID = pHdrOrd->m_pWritableOrderAction->InvestorID;
				COPY_XTP_HEADER_RSPINFO(pRspHdr,pHdrOrd->m_pXtpHdr);
			}
			else
			{
				//如果pHdrOrd为NULL,说明没有之前的撤单保留，反演会出现这种情况
				//还有一种情况是：从rtnOrder过来的，报盘伪造了一个rspOrderAction
				CWriteableOrderAction theOrderAction;
				theOrderAction.init();
				bSuccess=m_pTradeService->RspOrderAction(&order,&theOrderAction,&orderActionField,&exRspInfoField,sessionRef,&m_Transaction);
				orderActionField.UserOrderActionLocalID = theOrderAction.UserOrderActionLocalID;
				orderActionField.UserOrderLocalID = theOrderAction.UserOrderLocalID;
				orderActionField.BrokerID = theOrderAction.BrokerID;
				orderActionField.UserID = theOrderAction.UserID;
				orderActionField.InvestorID = theOrderAction.InvestorID;
				COPY_XTP_HEADER_RSPINFO(pRspHdr,pPackage->GetXTPHeader());			
			}

			//向客户发送应答，保存到流文件	
			if (pPackage->GetNoReplayFlag())
			{
				CRspInfoField usRspInfoField;//本系统应答信息
				CRspInfoField clntInfoField;//客户应答信息
				
				m_pRspMessage->SetSubjectID(pPackage->GetSubjectID());
				XTP_ADD_FIELD(m_pRspMessage, &orderActionField);
				m_pErrorEngine->getLastError(&errorCode,&errMsg);
				usRspInfoField.ErrorID = errorCode;
				usRspInfoField.ErrorMsg = errMsg;

				MergeErrorMsg(&exRspInfoField,&usRspInfoField,clntInfoField);
				XTP_ADD_FIELD(m_pRspMessage,&clntInfoField);
				m_pRspMessage->MakePackage();
				m_pTradeResult->Append(m_pRspMessage->Address(), m_pRspMessage->Length());
				
				//伪造rtn
				if (bSuccess && 0==errorCode &&  exRspInfoField.ErrorID ==0 &&
					orderActionField.IsForgeRtn)
				{
					m_pRspMessage->PreparePublish(TID_NtfOrder);
					XTP_ADD_FIELD(m_pRspMessage, &order);
					m_pRspMessage->MakePackage();
					m_pTradeResult->Append(m_pRspMessage->Address(), m_pRspMessage->Length());
				}
			}
	
			break;
		}
	case TID_InitClientTradingID:
		{
			CClientTradingIDField field;			
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
			while(!it.IsEnd())
			{
				it.Retrieve(&field);

				//CClientTradingIDField *pCTIDField = new CClientTradingIDField;
				//memcpy(pCTIDField,&field,sizeof(CClientTradingIDField));
				//m_InitClientTradingIDVec.push_back(pCTIDField);


				CPartExClntIndx idx;
				idx.ClientID=field.ClientID;
				idx.ExchangeID=field.ExchangeID;
				idx.PartID=field.ParticipantID;
				idx.HedgeFlag=field.ClientHedgeFlag;

				g_pExchangeLinkManager->initClientTradingID(&field);		
				
				CPartExClntInvBrkMp::iterator iter=m_PartExClntInvBrkMp.find(idx);
				stBrokerAndInvestorID* pstBrokerAndInvestorID=new stBrokerAndInvestorID();
				pstBrokerAndInvestorID->BrokerID=field.BrokerID;
				pstBrokerAndInvestorID->InvestorID=field.InvestorID;
				if (iter==m_PartExClntInvBrkMp.end())
				{
					m_PartExClntInvBrkMp.insert(CPartExClntInvBrkMp::value_type(idx,pstBrokerAndInvestorID));
				}
				else
				{
					//暂时不处理
					REPORT_EVENT(LOG_CRITICAL,"CTradeServiceXTPLink", "InitErr:ClientTradingID表出现了重复记录");
				}
				it.Next();
			}
			bSuccess=true;
		break;
		}
	//新增指令，用于导出内存表，供测试使用 by wangwei,20130114
	case TID_ReqDumpMemDb:
		{
			REPORT_EVENT(LOG_CRITICAL,"CTradeServiceXTPLink", "dumped memdb");
			m_pTradeService->DumpDebugInfo(sessionRef,&m_Transaction);
			break;
		}
	//这了的改变主要是合约下场成功之后，后续动作的完善
	case TID_UpdateSystemStatus:
		{
			CSystemStatusField field;
			XTP_GET_SINGLE_FIELD(pPackage,&field);

			//入库
			m_pTradeService->UpdateSystemStatus(&field,sessionRef,&m_Transaction);

			//写入流水，这个消息很特殊，不是从流里面来的，是一个报文生成的，和其他的打包方式不一样
			if (pPackage->GetNoReplayFlag())
			{
				m_pRspMessage->PreparePublish(TID_UpdateSystemStatus);
				XTP_ADD_FIELD(m_pRspMessage, &field);
				m_pRspMessage->MakePackage();
				m_pTradeResult->Append(m_pRspMessage->Address(), m_pRspMessage->Length());
			}
			break;
		}
	case TID_QueryBaseFinish:
		{
			CQueryFinishNotifyField field;
			XTP_GET_SINGLE_FIELD(pPackage,&field);
			//计算占用保证金
			m_pTradeService->BuildInsGroupPosition(field.ExchangeID);
			CBaseExchApi *pExchApi = g_pExchangeLinkManager->getExchangeLink(field.APIID.getValue());
			if (pExchApi != NULL)
			{
				pExchApi->SetMaxLocalID(atoi(field.MaxOrderLocalID));
			}
			if (pPackage->GetNoReplayFlag())
			{
				pPackage->MakeNoBufPackage();
				m_pTradeResult->Append(pPackage->Address(), pPackage->Length());
				pPackage->Pop(XTPHLEN);
			}

			break;
		}
    case  TID_NtfInstrumentStatusUpdate:
		{			
			CInstrumentStatusField field;			
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
			while(!it.IsEnd())
			{
				it.Retrieve(&field);
				bSuccess = m_pTradeService->NtfInstrumentStatusUpdate(&field,pPackage->GetNoReplayFlag(),sessionRef,&m_Transaction);
				it.Next();
			}		
			break;
		}
	//把席位的信息存储起来，等到上场结束时候传给ReqFlow，否则报盘机没有登录信息
	case TID_InitSeat:
		{
			CSeatField field;			
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
			while(!it.IsEnd())
			{				
				it.Retrieve(&field);
				//xuzh 20160923 如果反演的时候不查询，看似正确，但是存在问题
				//上期、大商、郑州有夜盘，早上2:30停止，早上7:00反演启动，此时中金所认为是反演
				//中金所就不会查询了，没有合约信息，无法交易
				field.TradingDay = m_pTradeService->GetTradingDay();
				g_pExchangeLinkManager->initLink(&field);
				it.Next();
			}
			break;
		}
	case TID_DbUpdUser:
		{
	
			CDbmtUserField field;
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe);
			
			while(!it.IsEnd())
			{
				CUserField tmpfield;		
				it.Retrieve(&field);
				CopyUserEntity(&tmpfield,&field);

				if (  tmpfield.IsActive == UIA_NoActive)
				{
					//删除该用户session
					bSuccess=m_pTradeService->DelUserSession(&tmpfield,&m_Transaction);
				}else{
					//更新用户
					bSuccess=m_pTradeService->UserUpdate(&tmpfield,&m_Transaction);
				}
				it.Next();
			}
		
			break;
		}
	case TID_NtfSGEDeferRate:
		{
			CSGEDeferRateField field;
			XTP_GET_SINGLE_FIELD(pPackage,&field);
			
			//业务处理
			bSuccess=m_pTradeService->NtfSGEDeferRate(&field,sessionRef,&m_Transaction);

			if (pPackage->GetNoReplayFlag())
			{
				m_pRspMessage->PreparePublish(TID_NtfSGEDeferRate);
				XTP_ADD_FIELD(m_pRspMessage, &field);
				m_pRspMessage->MakePackage();
				m_pTradeResult->Append(m_pRspMessage->Address(), m_pRspMessage->Length());	
			}
			break;
		}
	case TID_ReqQryMBLMarketData:
		{
			//调用报盘接口
			CQryMBLMarketDataField field;
			CInvestor* pInvestor = NULL;
			XTP_GET_SINGLE_FIELD(pPackage,&field);
			bSuccess = m_pTradeService->ReqMBLMarketData(field,sessionRef);
			break;
		}
	case TID_ExQryMBLMarketData:
		{
			CMBLMarketDataField	 field;
			CRspInfoField		rspfield;
			XTP_GET_SINGLE_FIELD(pPackage,&field);
			XTP_GET_SINGLE_FIELD(pPackage,&rspfield);
			
			if (pPackage->GetNoReplayFlag())
			{
				m_pRspMessage->PreparePublish(TID_RspQryMBLMarketData,pPackage->GetChain());
				COPY_SESSIONREF_INFO(m_pRspMessage->GetXTPHeader(),&sessionRef);
				if (!field.InstrumentID.isNull())
				{
					XTP_ADD_FIELD(m_pRspMessage, &field);
				}	
				XTP_ADD_FIELD(m_pRspMessage,&rspfield);	
				m_pRspMessage->MakePackage();
				m_pTradeResult->Append(m_pRspMessage->Address(), m_pRspMessage->Length());
			}
			
			break;
		}
	default:
		break;
	}
	
	///成功，则commit
	if (bSuccess)
	{
		m_Transaction.commit();
	}
	else
	{
        m_Transaction.rollback();
	}
	
    return bSuccess;
}

CXTPHdrOrderAction* CTradeServiceXTPLink::GetReqHdrAndOrdAct(CSeatIDType& SeatID,COrderLocalIDType& OrderActionLocalID)
{
	CXTPHdrOrderAction* pRet=NULL;
	if (SeatID.isNull() || OrderActionLocalID.isNull())
	{
		return NULL;
	}
	CSeatOrdActionLocalIDIndex indx;
	indx.OrderActionLocalID=OrderActionLocalID;//注意这里是撤单号
	indx.SeatID=SeatID;
	CSeatOrdActionLocalIDXTPMap::iterator iter= m_SeatOrdActionLocalIDXTPMap.find(indx);
	
	if(iter == m_SeatOrdActionLocalIDXTPMap.end())
	{	
		return NULL;
	}
	else
	{
		CXTPHdrOrderAction* pHdrOrd=iter->second;
		pRet=new CXTPHdrOrderAction(pHdrOrd);		
		m_SeatOrdActionLocalIDXTPMap.erase(indx);
		delete pHdrOrd;
	}
	return pRet;
}

void CTradeServiceXTPLink::MergeErrorMsg(CRspInfoField* pExInfo,CRspInfoField* pUsInfo,CRspInfoField& outInfo)
{
	const int EBUFSIZ=1024;
	char errBuf[EBUFSIZ];
	memset(errBuf,0,EBUFSIZ);
	
	//errorid以本系统为主,实际上本系统错误定义应该涵括交易所的错误
	if (pExInfo->ErrorID!=0)
	{
		if (pUsInfo->ErrorID!=0)
		{
			outInfo.ErrorID=pUsInfo->ErrorID;
			sprintf(errBuf,"交易所返回:[%s],qdp返回:[%s]",pExInfo->ErrorMsg.getValue(),pUsInfo->ErrorMsg.getValue());
		}
		else
		{
			outInfo.ErrorID=pExInfo->ErrorID;
			sprintf(errBuf,"交易所返回:[%s]",pExInfo->ErrorMsg.getValue());
		}
	}
	else
	{
		if (pUsInfo->ErrorID!=0)
		{
			outInfo.ErrorID=pUsInfo->ErrorID;
			sprintf(errBuf,"qdp返回:[%s]",pUsInfo->ErrorMsg.getValue());
		}
		else
		{
			outInfo.ErrorID=0;
			sprintf(errBuf,"%s","正确");
		}
	}
	outInfo.ErrorMsg=errBuf;
}

bool CTradeServiceXTPLink::SaveReqHdrAndWtOrdAct(CSeatIDType& SeatID,COrderLocalIDType& OrderActionLocalID,TXTPHeader* pHdr,CWriteableOrderAction* pOrdAct)
{
	if (SeatID.isNull() || OrderActionLocalID.isNull() || pOrdAct==NULL || pHdr==NULL)
	{
		return false;
	}
	CSeatOrdActionLocalIDIndex idx;
	idx.OrderActionLocalID=OrderActionLocalID;
	idx.SeatID=SeatID;
	CSeatOrdActionLocalIDXTPMap::iterator it=m_SeatOrdActionLocalIDXTPMap.find(idx);
	if (it!=m_SeatOrdActionLocalIDXTPMap.end())
	{
		memcpy(it->second->m_pXtpHdr,pHdr,sizeof(struct TXTPHeader));
		CopyOrderActionEntity(it->second->m_pWritableOrderAction,pOrdAct);
		it->second->m_pWritableOrderAction->linkOrder(pOrdAct->getOrder());
	}
	else
	{
		CXTPHdrOrderAction* pHdrOrd=new CXTPHdrOrderAction(pHdr,pOrdAct);
		m_SeatOrdActionLocalIDXTPMap.insert(CSeatOrdActionLocalIDXTPMap::value_type(idx,pHdrOrd));
	}
	return true;
}

bool CTradeServiceXTPLink::GetInvBrkByPartExClnt(CParticipantIDType& PartID,CExchangeIDType& ExchangeID,CClientIDType& ClientID,CInvestorIDType &InvestorID,CBrokerIDType &BrokerID)
{
	if (PartID.isNull()||ExchangeID.isNull()||ClientID.isNull())
	{
		return false;
	}
	CPartExClntIndx idx;
	idx.ExchangeID=ExchangeID;
	idx.ClientID=ClientID;
	idx.PartID=PartID;
	CPartExClntInvBrkMp::iterator it=m_PartExClntInvBrkMp.find(idx);
	if (it==m_PartExClntInvBrkMp.end())
	{
		//找不到对应的InvestorID
		return false;
	}	
	if (it->second==NULL||it->second->BrokerID.isNull()||it->second->InvestorID.isNull())
	{
		return false;
	}
	InvestorID=it->second->InvestorID;
	BrokerID=it->second->BrokerID;
	return true;
}

bool CTradeServiceXTPLink::SaveReqOrdHdr(CSeatIDType& SeatID,COrderLocalIDType& OrderLocalID,TXTPHeader* pHdr)
{
	if (SeatID.isNull() || OrderLocalID.isNull() || pHdr==NULL)
	{
		return false;
	}
	CSeatOrdLocalIDIndex idx;
	idx.OrderLocalID=OrderLocalID;
	idx.SeatID=SeatID;
	CSeatOrdLocalIDXTPMap::iterator it=m_SeatOrdLocalIDXTPMap.find(idx);
	if (it!=m_SeatOrdLocalIDXTPMap.end())
	{
		memcpy(it->second,pHdr,sizeof(struct TXTPHeader));
	}
	else
	{
		TXTPHeader* pXtpHdr=new TXTPHeader();
		memcpy(pXtpHdr,pHdr,sizeof(struct TXTPHeader));
		m_SeatOrdLocalIDXTPMap.insert(CSeatOrdLocalIDXTPMap::value_type(idx,pXtpHdr));
	}
	return true;
}

TXTPHeader* CTradeServiceXTPLink::GetReqOrdHdr(CSeatIDType& SeatID,COrderLocalIDType& OrderLocalID)
{
	TXTPHeader* pRet=NULL;
	if (SeatID.isNull() || OrderLocalID.isNull())
	{
		return NULL;
	}
	CSeatOrdLocalIDIndex indx;
	indx.OrderLocalID=OrderLocalID;//注意这里是撤单号
	indx.SeatID=SeatID;
	CSeatOrdLocalIDXTPMap::iterator iter= m_SeatOrdLocalIDXTPMap.find(indx);
	
	if(iter == m_SeatOrdLocalIDXTPMap.end())
	{	
		return NULL;
	}
	else
	{
		pRet=new TXTPHeader();
		TXTPHeader* pHdrOrd=iter->second;		
		memcpy(pRet,pHdrOrd,sizeof(struct TXTPHeader));
		m_SeatOrdLocalIDXTPMap.erase(indx);
		delete pHdrOrd;		
	}
	return pRet;
}
void CTradeServiceXTPLink::DumpMemDb()
{
	//m_pTradeService->DumpDebugInfo();
}

bool CTradeServiceXTPLink::SaveFakOrdHdr(CSeatIDType& SeatID,COrderLocalIDType& OrderLocalID,TFakOrderHeaderInfo* pHdr)
{
	if (SeatID.isNull() || OrderLocalID.isNull() || pHdr==NULL)
	{
		return false;
	}
	CSeatOrdLocalIDIndex idx;
	idx.OrderLocalID=OrderLocalID;
	idx.SeatID=SeatID;
	CFakOrderHeaderXTPMap::iterator it=m_FakOrderHeaderMap.find(idx);
	if (it!=m_FakOrderHeaderMap.end())
	{
		memcpy(it->second,pHdr,sizeof(struct TXTPHeader));
	}
	else
	{
		TFakOrderHeaderInfo* pXtpHdr=new TFakOrderHeaderInfo();
		memcpy(pXtpHdr,pHdr,sizeof(struct TFakOrderHeaderInfo));
		m_FakOrderHeaderMap.insert(CFakOrderHeaderXTPMap::value_type(idx,pXtpHdr));
	}
	return true;
}

TXTPHeader* CTradeServiceXTPLink::GetFakOrdHdr(CSeatIDType& SeatID,COrderLocalIDType& OrderLocalID,int tradeVolume/* =0 */)
{
	TXTPHeader* pRet=NULL;
	if (SeatID.isNull() || OrderLocalID.isNull())
	{
		return NULL;
	}
	CSeatOrdLocalIDIndex indx;
	indx.OrderLocalID=OrderLocalID;
	indx.SeatID=SeatID;
	CFakOrderHeaderXTPMap::iterator iter= m_FakOrderHeaderMap.find(indx);
	
	if(iter == m_FakOrderHeaderMap.end())
	{	
		return NULL;
	}
	else
	{
		TFakOrderHeaderInfo* pHdrOrd=iter->second;	
		if (tradeVolume>0 && pHdrOrd->OrderVolume == tradeVolume) //FAK全部成交
		{
			m_FakOrderHeaderMap.erase(indx);
			delete pHdrOrd;	
		}
		else if (tradeVolume ==0)//FAK撤单回报
		{
			pRet=new TXTPHeader();			
			memcpy(pRet,&pHdrOrd->header,sizeof(struct TXTPHeader));
			m_FakOrderHeaderMap.erase(indx);					
			delete pHdrOrd;
		}	
	}
	return pRet;
}


//性能调优使用的函数
// #ifdef PERFORM_TEST
// 
// timeval tvLast;//上次的时间
// bool g_bFirst=true;
// 
// void printTime(char* FuncName)
// {
// 	if (g_bFirst)
// 	{
// 		gettimeofday(&tvLast,NULL);
// 		g_bFirst=false;
// 	}
// 	timeval tvNow;
// 	gettimeofday(&tvNow,NULL);
// 	printf("Func=[%s],%d,%d,%d,%d\n",FuncName,tvNow.tv_sec-tvLast.tv_sec,tvNow.tv_usec-tvLast.tv_usec,tvNow.tv_sec,tvNow.tv_usec);
// 	memcpy(&tvLast,&tvNow,sizeof(timeval));
// }
// 
// #else
// 
// void printTime(char* FuncName)
// {
// 	
// }
// #endif
