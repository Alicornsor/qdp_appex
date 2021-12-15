// TradingQueryServiceXTPLink.cpp: 
//
///20090118	xuzh		增加了查询的日志（NT-0065）
// 20121231 longqy@cffex.net  编写了函数 handleRequest 新的处理消息
//////////////////////////////////////////////////////////////////////
#include "TradingQueryServiceXTPLink.h"
#include "XtpPackageDesc.h"
#include "UFCopy.h"
#include "CDate.h"

// #include "tradingTools.h"

///-------
//	xuzh，20061115：修改了套保额度查询的结果，从手改为吨。但是，为了这个原因，我不得不将内存数据库传进来，
//  违反了当初的设计原则。迟早我还是要把这段代码改掉。
///-------

///------
///	xuzh，20061228：彻底修改了查询的实现方法，以便使程序更加美观
///------

extern char *INI_FILE_NAME;
CTradingQueryServiceXtpLink::CTradingQueryServiceXtpLink(CTradingQueryImpl *pService, CErrorEngine *pErrorEngine,
											IServiceResponser *pServiceResponser, CMemoryDB *pDB,bool verbose)
{
	m_pService=pService;
	m_pErrorEngine=pErrorEngine;
	m_pServiceResponser = pServiceResponser;
	m_pDB = pDB;
	m_verbose=verbose;
	m_pRspMessage = new CXTPPackage;
	m_pRspMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	
	if (! g_logMemoryDBTable.canLog())
	{
		g_logMemoryDBTable.init();
	}
}

CTradingQueryServiceXtpLink::~CTradingQueryServiceXtpLink()
{
	if(m_pRspMessage != NULL)
		m_pRspMessage->Release();
	delete m_pRspMessage;
	
	// 把Map中动态生成的Vector释放
	CExchangeInvestorID2ClientIDMap::iterator itor = m_mapClientID.begin();
	for(; itor != m_mapClientID.end(); itor++)
	{
		delete itor->second;
	}

}	
	

void CTradingQueryServiceXtpLink::FlushPackage(bool bLast, DWORD nSessionID)
{
	m_pRspMessage->GetXTPHeader()->Chain = bLast?CHAIN_LAST:CHAIN_CONTINUE;
	m_pServiceResponser->SendResponse(m_pRspMessage,nSessionID);
}

void CTradingQueryServiceXtpLink::ResponseErrorMsg(CXTPPackage *pPackage,DWORD rspTID,DWORD dwSessionID)
{
	CRspInfoField responseField;
	char* errMsg;
	int errorCode;
	m_pErrorEngine->getLastError(&errorCode,&errMsg);
	responseField.ErrorID = errorCode;
	responseField.ErrorMsg = errMsg;
	m_pRspMessage->PrepareResponse(pPackage, rspTID);
	XTP_ADD_FIELD(m_pRspMessage,&responseField);
	m_pServiceResponser->SendResponse(m_pRspMessage,dwSessionID);
}

void CTradingQueryServiceXtpLink::ResponseNullMsg(CXTPPackage *pPackage,DWORD rspTID,DWORD dwSessionID)
{
	CRspInfoField responseField;
	char* errMsg;
	int errorCode;
	m_pErrorEngine->getLastError(&errorCode,&errMsg);
	responseField.ErrorID = 0;
	responseField.ErrorMsg = "正确";
	m_pRspMessage->PrepareResponse(pPackage, rspTID);
	XTP_ADD_FIELD(m_pRspMessage,&responseField);
	m_pServiceResponser->SendResponse(m_pRspMessage,dwSessionID);
}

bool CTradingQueryServiceXtpLink::handleRequest(CXTPPackage *pPackage, const TSessionRef &sessionRef,DWORD ResponseSessionID)
{
	REPORT_EVENT(LOG_CRITICAL,"CTradingQueryServiceXtpLink","收到查询请求 请求号%d !\n",pPackage->GetTid());
	bool success=false;
	char* errMsg;
	int errorCode = 0;
	switch (pPackage->GetTid())
	{
		case TID_ReqDumpMemDb:
		{
			//dump出数据库
			CConfig Config(INI_FILE_NAME);	
			m_pDB->save(&Config);
			break;
		}
		case TID_ReqQryOrder: 
		{ 
			char buffer[4000] = {0}; 
			long startTime,endTime; 
			GET_ACCURATE_USEC_TIME(startTime); 
			CQryOrderField field; 
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe); 
			while(!it.IsEnd()) 
			{ 
				it.Retrieve(&field); 
				if (g_logMemoryDBTable.canLog()) 
				{ 
					field.dumpLine(buffer,4000); 
				} 
				COrderIterator* pIt= NULL; 
				success = m_pService->QueryOrder( field.BrokerID, field.UserID, field.ExchangeID,  field.InvestorID,	field.OrderSysID, field.InstrumentID, field.LogBrokerID, field.LogUserID,&pIt,sessionRef,&m_Transaction); 
				if(!success) 
				{ 
					ResponseErrorMsg(pPackage,TID_RspQryOrder,ResponseSessionID); 
					return false; 
				} 
				CRspInfoField responseField; 
				m_pErrorEngine->getLastError(&errorCode,&errMsg); 
				responseField.ErrorID = errorCode; 
				responseField.ErrorMsg = errMsg; 
				m_pRspMessage->PrepareResponse(pPackage, TID_RspQryOrder); 
				COrderField rspField; 
				COrder * pData = pIt->next(); 
				bool bHasOrder = false;
				XTP_ADD_FIELD(m_pRspMessage,&responseField);

				map<string, int> investors;
				char userID[15]={0};
				if (!field.UserID.isNull())
				{
					strncpy(userID,field.UserID.getValue(),sizeof(userID));
				}
				else
				{
					strncpy(userID,field.LogUserID.getValue(),sizeof(userID));
				}
				CUserInvestorFactory *pUserInvestorFactory = m_pDB->m_UserInvestorFactory;
				CUserInvestor *pInvestor =pUserInvestorFactory->startFindAllByUserID(userID);
				while (pInvestor != NULL)
				{
					investors.insert(make_pair(pInvestor->InvestorID.getValue(),1));
					pInvestor = pUserInvestorFactory->findNextAllByUserID();
				}
				pUserInvestorFactory->endFindAllByUserID();
				
				int investor_cnt = investors.size();
				map<string, int>::iterator investor_iter;
				if (investor_cnt >=1)
				{
					while(pData) 
					{ 
						investor_iter = investors.find(pData->InvestorID.getValue());
						if (investor_iter == investors.end())
						{
							pData = pIt->next(); 
							continue;
						}
						bHasOrder=true;
						CopyOrderEntity(&rspField,pData); 
						g_logMemoryDBTable.logField(&rspField,"Order",LOG_QUERY);
						while(XTP_ADD_FIELD(m_pRspMessage,&rspField) < 0) 
						{   // 当一个XTP数据包不能装载这多条记录，再新生成数据包发送
							FlushPackage(false,ResponseSessionID); 
							m_pRspMessage->PrepareResponse(pPackage, TID_RspQryOrder,CHAIN_CONTINUE);
							// 新数据包，也重复用之前的 响应信息
							XTP_ADD_FIELD(m_pRspMessage,&responseField);						
						} 
						pData = pIt->next(); 
					} 
					
				}

				m_pRspMessage->SetChain(CHAIN_LAST);
				FlushPackage(true,ResponseSessionID); 
				delete pIt;	
				
				it.Next(); 
				//break; 
			} 
			GET_ACCURATE_USEC_TIME(endTime); 
			if( buffer[0]) 
			{
				g_logMemoryDBTable.logQuery(sessionRef,startTime,endTime,buffer);
			}
			break; 
		}
		case TID_ReqQryTrade: 
		{ 
			char buffer[4000] = {0}; 
			long startTime,endTime; 
			GET_ACCURATE_USEC_TIME(startTime); 
			CQryTradeField field; 
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe); 
			while(!it.IsEnd()) 
			{ 
				it.Retrieve(&field); 
				if (g_logMemoryDBTable.canLog()) 
				{ 
					field.dumpLine(buffer,4000); 
				} 
				CTradeIterator* pIt = NULL; 
				success = m_pService->QueryTrade(field.BrokerID,field.UserID,field.ExchangeID, field.InvestorID,field.TradeID, field.InstrumentID,field.LogBrokerID,field.LogUserID,&pIt,sessionRef,&m_Transaction); 
				if(!success) 
				{ 
					ResponseNullMsg(pPackage,TID_RspQryTrade,ResponseSessionID);
					//ResponseErrorMsg(pPackage,TID_RspQryTrade,ResponseSessionID); 
					return false; 
				} 
				CRspInfoField responseField;
				m_pErrorEngine->getLastError(&errorCode,&errMsg); 
				responseField.ErrorID = errorCode; 
				responseField.ErrorMsg = errMsg; 
				m_pRspMessage->PrepareResponse(pPackage, TID_RspQryTrade); 
				CTradeField rspField; 
				CTrade * pData = pIt->next(); 
				XTP_ADD_FIELD(m_pRspMessage,&responseField); 

				map<string, int> investors;
				char userID[15]={0};
				if (!field.UserID.isNull())
				{
					strncpy(userID,field.UserID.getValue(),sizeof(userID));
				}
				else
				{
					strncpy(userID,field.LogUserID.getValue(),sizeof(userID));
				}
				CUserInvestorFactory *pUserInvestorFactory = m_pDB->m_UserInvestorFactory;
				CUserInvestor *pInvestor =pUserInvestorFactory->startFindAllByUserID(userID);
				while (pInvestor != NULL)
				{
					investors.insert(make_pair(pInvestor->InvestorID.getValue(),1));
					pInvestor = pUserInvestorFactory->findNextAllByUserID();
				}
				pUserInvestorFactory->endFindAllByUserID();
				
				int investor_cnt = investors.size();
				map<string, int>::iterator investor_iter;
				if (investor_cnt >=1)
				{
					while(pData) 
					{ 
						investor_iter = investors.find(pData->InvestorID.getValue());
						if (investor_iter == investors.end())
						{
							pData = pIt->next();
							continue;
						}
						CopyTradeEntity(&rspField,pData); 
						g_logMemoryDBTable.logField(&rspField,"Trade",LOG_QUERY);
						while(XTP_ADD_FIELD(m_pRspMessage,&rspField) < 0) 
						{ 
							FlushPackage(false,ResponseSessionID); 
							m_pRspMessage->PrepareResponse(pPackage, TID_RspQryTrade,CHAIN_CONTINUE);
							XTP_ADD_FIELD(m_pRspMessage,&responseField);						
						} 
						pData = pIt->next(); 
					}
				}
				m_pRspMessage->SetChain(CHAIN_LAST);
				FlushPackage(true,ResponseSessionID); 
				delete pIt; 
				it.Next(); 
				//break; 
			} 
			GET_ACCURATE_USEC_TIME(endTime); 
			if( buffer[0]) 
			{
				g_logMemoryDBTable.logQuery(sessionRef,startTime,endTime,buffer);
			}
			break; 
		}
		 // 内存数据库中没有InvestorPosition表，把它当作 ClientPosition 来处理
		 case TID_ReqQryInvestorPosition: 
		 { 
			char buffer[4000] = {0}; 
			long startTime,endTime; 
			GET_ACCURATE_USEC_TIME(startTime);
			CQryInvestorPositionField field; 
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe); 
			while(!it.IsEnd()) 
			{ 
				it.Retrieve(&field); 
				if (g_logMemoryDBTable.canLog()) 
				{ 
					field.dumpLine(buffer,4000); 
				} 
								
				CInvestorPositionIterator* pIt = NULL;
				success = m_pService->QueryInvestorPosition(field.BrokerID,field.UserID,field.ExchangeID,field.InvestorID,field.InstrumentID,field.LogBrokerID,field.LogUserID,&pIt,sessionRef,&m_Transaction); 
				if(!success) 
				{ 
					ResponseErrorMsg(pPackage,TID_RspQryInvestorPosition,ResponseSessionID); 
					return false; 
				} 
				CRspInfoField responseField; 
				m_pErrorEngine->getLastError(&errorCode,&errMsg); 
				responseField.ErrorID = errorCode; 
				responseField.ErrorMsg = errMsg; 
				m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorPosition);	

				CInvestorPositionField rspField; 
				CInvestorPosition * pData = pIt->next(); 
				XTP_ADD_FIELD(m_pRspMessage,&responseField); 
				while(pData) 
				{ 				
					CopyInvestorPositionEntity(&rspField,pData);
					CInvestorPositionField	investorField;					
					//ClinetPosition与InvestorPosition数据结构体不一样，这里转换一下
					copyInvestorPositionField(&rspField,&investorField,field.InvestorID);	
					g_logMemoryDBTable.logField(&rspField,"InvestorPosition",LOG_QUERY);
					if (investorField.Direction == D_Net)
					{
						//需要拆开成2条持仓记录
						int i=pData->YdPosition.getValue() * pData->Position.getValue();
						if (i <0)
						{
							if (pData->Position >0)
							{
								investorField.Direction = D_Buy;
								investorField.Position = pData->Position;
							}
							else
							{
								investorField.Direction = D_Sell;
								investorField.Position = -1 * pData->Position;
							}
							investorField.YdPosition = 0;	
							investorField.YdPositionCost = 0.0;
							while(XTP_ADD_FIELD(m_pRspMessage,&investorField)<0) 
							{ 
								FlushPackage(false,ResponseSessionID); 
								m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorPosition,CHAIN_CONTINUE); 
								XTP_ADD_FIELD(m_pRspMessage,&responseField);
							}

							if (pData->YdPosition>0)
							{
								investorField.Direction = D_Buy;
								investorField.YdPosition = pData->YdPosition;
							}
							else
							{
								investorField.Direction = D_Sell;
								investorField.YdPosition = -1 * pData->YdPosition;
							}
							investorField.YdPositionCost = pData->YdPositionCost;
							investorField.Position = 0;
							investorField.PositionCost = 0.0;
							investorField.UsedMargin = 0.0;
							investorField.FrozenMargin =0.0;
							investorField.FrozenPosition =0;
							investorField.FrozenClosing = 0;
							while(XTP_ADD_FIELD(m_pRspMessage,&investorField)<0) 
							{ 
								FlushPackage(false,ResponseSessionID); 
								m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorPosition,CHAIN_CONTINUE); 
								XTP_ADD_FIELD(m_pRspMessage,&responseField);
							}
							

								
						}
						else if ( i==0)
						{
							if (pData->YdPosition >0 ||
								pData->Position >0)
							{							
								investorField.Direction = D_Buy;
								investorField.YdPosition = pData->YdPosition;
								investorField.Position = pData->Position;						
							}
							else
							{
								investorField.Direction = D_Sell;
								investorField.YdPosition = -1 * pData->YdPosition;
								investorField.Position = -1 *pData->Position;
							}
							while(XTP_ADD_FIELD(m_pRspMessage,&investorField)<0) 
							{ 
								FlushPackage(false,ResponseSessionID); 
								m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorPosition,CHAIN_CONTINUE); 
								XTP_ADD_FIELD(m_pRspMessage,&responseField);
							} 
						}
						else
						{
							if (pData->YdPosition >0)
							{
								investorField.Direction = D_Buy;
								investorField.YdPosition = pData->YdPosition;
								investorField.Position = pData->Position;
							}
							else
							{
								investorField.Direction = D_Sell;
								investorField.YdPosition = -1*pData->YdPosition;
								investorField.Position = -1*pData->Position;
							}
							while(XTP_ADD_FIELD(m_pRspMessage,&investorField)<0) 
							{ 
								FlushPackage(false,ResponseSessionID); 
								m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorPosition,CHAIN_CONTINUE); 
								XTP_ADD_FIELD(m_pRspMessage,&responseField);
							} 
						}
					}
					else
					{
						while(XTP_ADD_FIELD(m_pRspMessage,&investorField)<0) 
						{ 
							FlushPackage(false,ResponseSessionID); 
							m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorPosition,CHAIN_CONTINUE); 
							XTP_ADD_FIELD(m_pRspMessage,&responseField);
						} 
					}
					pData = pIt->next(); 
				}		
				m_pRspMessage->SetChain(CHAIN_LAST);
				FlushPackage(true,ResponseSessionID);
				delete pIt;

				it.Next();
			} 
			GET_ACCURATE_USEC_TIME(endTime); 
			if( buffer[0]) 
			{
				g_logMemoryDBTable.logQuery(sessionRef,startTime,endTime,buffer); 
			}
			break; 
		 }
		case TID_ReqQryInstrument: 
		 { 
			char buffer[4000] = {0}; 
			long startTime,endTime; 
			GET_ACCURATE_USEC_TIME(startTime); 
			CQryInstrumentField field; 
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe); 
			while(!it.IsEnd()) 
			{ 
				it.Retrieve(&field); 
				if (g_logMemoryDBTable.canLog()) 
				{ 
					field.dumpLine(buffer,4000); 
				} 
				CInstrumentIterator* pIt = NULL; 
				success = m_pService->QueryInstrument(field.ExchangeID,field.ProductID, field.InstrumentID, &pIt,sessionRef,&m_Transaction); 
				if(!success) 
				{ 
					ResponseErrorMsg(pPackage,TID_RspQryInstrument,ResponseSessionID); 
					return false; 
				} 
				CRspInfoField responseField; 
				m_pErrorEngine->getLastError(&errorCode,&errMsg); 
				responseField.ErrorID = errorCode; 
				responseField.ErrorMsg = errMsg; 
				m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInstrument); 
				CInstrumentField rspField; 
				CInstrument * pData = pIt->next(); 
				XTP_ADD_FIELD(m_pRspMessage,&responseField); 
				while(pData) 
				{ 
					CopyInstrumentEntity(&rspField,pData); 
		//			handleInstrument(m_pDB,&rspField,pData); 
					g_logMemoryDBTable.logField(&rspField,"Instrument",LOG_QUERY);
					while(XTP_ADD_FIELD(m_pRspMessage,&rspField) < 0) 
					{ 
						FlushPackage(false,ResponseSessionID); 
						m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInstrument,CHAIN_CONTINUE);
						XTP_ADD_FIELD(m_pRspMessage,&responseField); 
					} 
					pData = pIt->next(); 
				} 
				m_pRspMessage->SetChain(CHAIN_LAST);
				FlushPackage(true,ResponseSessionID); 
				delete pIt; 
				it.Next(); 
				//break; 
			} 
			GET_ACCURATE_USEC_TIME(endTime); 
			if( buffer[0]) 
			{
				g_logMemoryDBTable.logQuery(sessionRef,startTime,endTime,buffer);
			}
			break; 
		 }
		case TID_ReqQryMarketData: 
		 { 
			char buffer[4000] = {0}; 
			long startTime,endTime; 
			GET_ACCURATE_USEC_TIME(startTime); 
			CQryMarketDataField field; 
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe); 
			while(!it.IsEnd()) 
			{ 
				it.Retrieve(&field); 
				if (g_logMemoryDBTable.canLog()) 
				{ 
					field.dumpLine(buffer,4000); 
				} 
				CMarketDataIterator* pIt = NULL; 
				success = m_pService->QueryMarketData(field.ExchangeID, field.InstrumentID, &pIt,sessionRef,&m_Transaction); 
				if(!success) 
				{ 
					ResponseErrorMsg(pPackage,TID_RspQryInstrument,ResponseSessionID); 
					return false; 
				} 
				CRspInfoField responseField; 
				m_pErrorEngine->getLastError(&errorCode,&errMsg); 
				responseField.ErrorID = errorCode; 
				responseField.ErrorMsg = errMsg; 
				m_pRspMessage->PrepareResponse(pPackage, TID_RspQryMarketData); 
				CMarketDataField rspField; 
				CMarketData * pData = pIt->next(); 
				XTP_ADD_FIELD(m_pRspMessage,&responseField); 
				while(pData) 
				{ 
					CopyMarketDataEntity(&rspField,pData); 
					g_logMemoryDBTable.logField(&rspField,"MarketData",LOG_QUERY);
					while(XTP_ADD_FIELD(m_pRspMessage,&rspField) < 0) 
					{ 
						FlushPackage(false,ResponseSessionID); 
						m_pRspMessage->PrepareResponse(pPackage, TID_RspQryMarketData,CHAIN_CONTINUE);
						XTP_ADD_FIELD(m_pRspMessage,&responseField); 
					} 
					pData = pIt->next(); 
				} 
				m_pRspMessage->SetChain(CHAIN_LAST);
				FlushPackage(true,ResponseSessionID); 
				delete pIt; 
				it.Next(); 
			} 
			GET_ACCURATE_USEC_TIME(endTime); 
			if( buffer[0]) 
			{
				g_logMemoryDBTable.logQuery(sessionRef,startTime,endTime,buffer);
			}
			break; 
		 }
		 case TID_ReqQryUser: 
		 { 
			char buffer[4000] = {0}; 
			long startTime,endTime; 
			GET_ACCURATE_USEC_TIME(startTime); 
			CQryUserField field; 
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe); 
			
			while(!it.IsEnd()) 
			{ 
				it.Retrieve(&field); 
				if (g_logMemoryDBTable.canLog()) 
				{ 
					field.dumpLine(buffer,4000); 
				} 
				CUserIterator* pIt = NULL; 
				success = m_pService->QueryUser(field.StartUserID, field.EndUserID, &pIt,sessionRef,&m_Transaction); 
				
				if(!success) 
				{ 
					ResponseErrorMsg(pPackage,TID_RspQryUser,ResponseSessionID); 
					return false; 
				} 
				CRspInfoField responseField; 
				m_pErrorEngine->getLastError(&errorCode,&errMsg); 
				responseField.ErrorID = errorCode; 
				responseField.ErrorMsg = errMsg; 
				m_pRspMessage->PrepareResponse(pPackage, TID_RspQryUser); 
				CUserField rspField; 
				CUser * pData = pIt->next(); 
				XTP_ADD_FIELD(m_pRspMessage,&responseField); 
				while(pData) 
				{ 
					CopyUserEntity(&rspField,pData); ; 
					while(XTP_ADD_FIELD(m_pRspMessage,&rspField) < 0) 
					{ 
						FlushPackage(false,ResponseSessionID); 
						m_pRspMessage->PrepareResponse(pPackage, TID_RspQryUser,CHAIN_CONTINUE);
						XTP_ADD_FIELD(m_pRspMessage,&responseField);
					} 
					pData = pIt->next(); 
				} 
				m_pRspMessage->SetChain(CHAIN_LAST);
				FlushPackage(true,ResponseSessionID); 
				delete pIt; 
				it.Next(); 
				//break;
			} 
			GET_ACCURATE_USEC_TIME(endTime); 
			if( buffer[0]) 
			{
				g_logMemoryDBTable.logQuery(sessionRef,startTime,endTime,buffer);
			}
			break; 
		}										
		case TID_ReqQryExchange: 
		{ 
			char buffer[4000] = {0}; 
			long startTime,endTime; 
			GET_ACCURATE_USEC_TIME(startTime); 
			CQryExchangeField field; 
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe); 
			while(!it.IsEnd()) 
			{ 
				it.Retrieve(&field); 
				if (g_logMemoryDBTable.canLog()) 
				{ 
					field.dumpLine(buffer,4000); 
				} 
				CExchangeIterator* pIt = NULL; 
				success = m_pService->QueryExchange(field.ExchangeID, &pIt,sessionRef,&m_Transaction); 
				if(!success) 
				{ 
					ResponseErrorMsg(pPackage,TID_RspQryExchange,ResponseSessionID); 
					return false; 
				} 
				CRspInfoField responseField; 
				m_pErrorEngine->getLastError(&errorCode,&errMsg); 
				responseField.ErrorID = errorCode; 
				responseField.ErrorMsg = errMsg; 
				m_pRspMessage->PrepareResponse(pPackage, TID_RspQryExchange); 
				CRspExchangeField rspField; 
				CExchange * pData = pIt->next(); 
				XTP_ADD_FIELD(m_pRspMessage,&responseField); 
				while(pData) 
				{ 
					//CopyExchangeEntity(&rspField,pData); 
					rspField.ExchangeID = pData->ExchangeID;	
					rspField.ExchangeName = pData->ExchangeName;	
		//			rspField.ExchangeStatus=pData->ExchangeStatus; 
					g_logMemoryDBTable.logField((void *)pData,"Exchange",LOG_QUERY);
					while(XTP_ADD_FIELD(m_pRspMessage,&rspField) < 0) 
					{ 
						FlushPackage(false,ResponseSessionID); 
						m_pRspMessage->PrepareResponse(pPackage, TID_RspQryExchange,CHAIN_CONTINUE);
						XTP_ADD_FIELD(m_pRspMessage,&responseField);
					} 
					pData = pIt->next(); 
				} 
				m_pRspMessage->SetChain(CHAIN_LAST);
				FlushPackage(true,ResponseSessionID); 
				delete pIt; 
				it.Next(); 
				//break; 
			} 
			GET_ACCURATE_USEC_TIME(endTime); 
			if( buffer[0]) 
			{
				g_logMemoryDBTable.logQuery(sessionRef,startTime,endTime,buffer);
			}
			break; 
		}
		case TID_ReqQryInvestorAccount: 
		{ 
			char buffer[4000] = {0}; 
			long startTime,endTime; 
			GET_ACCURATE_USEC_TIME(startTime); 
			CQryInvestorAccountField field; 
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe); 
			while(!it.IsEnd()) 
			{ 
				it.Retrieve(&field); 
				if (g_logMemoryDBTable.canLog()) 
				{ 
					field.dumpLine(buffer,4000); 
				} 

				CInvestorAccountIterator* pIt = NULL; 
				success = m_pService->QueryInvestorAccount( field.BrokerID,field.UserID,field.InvestorID,field.LogBrokerID,field.LogUserID,&pIt,sessionRef,&m_Transaction); 
				if(!success) 
				{ 
					ResponseErrorMsg(pPackage,TID_RspQryInvestorAccount,ResponseSessionID); 
					return false; 
				} 
				CRspInfoField responseField; 
				m_pErrorEngine->getLastError(&errorCode,&errMsg); 
				responseField.ErrorID = errorCode; 
				responseField.ErrorMsg = errMsg;
				m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorAccount); 
				CInvestorAccountField rspField; 
				CInvestorAccount * pData = pIt->next(); 
				XTP_ADD_FIELD(m_pRspMessage,&responseField); 
				while(pData) 
				{ 
					CopyInvestorAccountEntity(&rspField,pData); ; 
					g_logMemoryDBTable.logField(&rspField,"InvestorAccount",LOG_QUERY);
					while(XTP_ADD_FIELD(m_pRspMessage,&rspField)<0) 
					{ 
						FlushPackage(false,ResponseSessionID); 
						m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorAccount,CHAIN_CONTINUE); 
						XTP_ADD_FIELD(m_pRspMessage,&responseField);
					} 
					pData = pIt->next(); 
				} 
				m_pRspMessage->SetChain(CHAIN_LAST);
				FlushPackage(true,ResponseSessionID); 
				delete pIt; 
				it.Next(); 
				//break; 
			} 
			GET_ACCURATE_USEC_TIME(endTime); 
			if( buffer[0]) 
			{
				g_logMemoryDBTable.logQuery(sessionRef,startTime,endTime,buffer);
			}
			break; 
		}

		case TID_ReqQryUserInvestor: 
		{ 
			char buffer[4000] = {0}; 
			long startTime,endTime; 
			GET_ACCURATE_USEC_TIME(startTime); 
			CQryUserInvestorField field; 
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe); 
			while(!it.IsEnd()) 
			{ 
				it.Retrieve(&field); 
				if (g_logMemoryDBTable.canLog()) 
				{ 
					field.dumpLine(buffer,4000); 
				} 
				CUserInvestorIterator* pIt = NULL;
				success = m_pService->QueryUserInvestor(field.BrokerID,field.UserID,field.LogBrokerID,field.LogUserID,&pIt,sessionRef,&m_Transaction); 
				if(!success) 
				{ 
					ResponseErrorMsg(pPackage,TID_RspQryUserInvestor,ResponseSessionID); 
					return false; 
				} 
				CRspInfoField responseField; 
				m_pErrorEngine->getLastError(&errorCode,&errMsg); 
				responseField.ErrorID = errorCode; 
				responseField.ErrorMsg = errMsg; 
				m_pRspMessage->PrepareResponse(pPackage, TID_RspQryUserInvestor); 
				CUserInvestorField rspField; 
				CUserInvestor * pData = pIt->next(); 
				XTP_ADD_FIELD(m_pRspMessage,&responseField); 
				while(pData) 
				{ 
					CopyUserInvestorEntity(&rspField,pData); ; 
					g_logMemoryDBTable.logField(&rspField,"UserInvestor",LOG_QUERY);
					while(XTP_ADD_FIELD(m_pRspMessage,&rspField) < 0) 
					{ 
						FlushPackage(false,ResponseSessionID); 
						m_pRspMessage->PrepareResponse(pPackage, TID_RspQryUserInvestor,CHAIN_CONTINUE); 
						XTP_ADD_FIELD(m_pRspMessage,&responseField); 
					} 
					pData = pIt->next(); 
				} 
				m_pRspMessage->SetChain(CHAIN_LAST);
				FlushPackage(true,ResponseSessionID); 
				delete pIt; 
				it.Next(); 
				//break; 
			} 
			GET_ACCURATE_USEC_TIME(endTime); 
			if( buffer[0]) 
			{
				g_logMemoryDBTable.logQuery(sessionRef,startTime,endTime,buffer);
			}
			break; 
		}
		// 
		case TID_ReqQryInvestorFee: 
		{ 
			char buffer[4000] = {0}; 
			long startTime,endTime; 
			GET_ACCURATE_USEC_TIME(startTime); 
			CQryInvestorFeeField field; 
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe); 
			while(!it.IsEnd()) 
			{ 
				it.Retrieve(&field); 
				if (g_logMemoryDBTable.canLog()) 
				{ 
					field.dumpLine(buffer,4000); 
				}
				if (field.HedgeFlag.isNull() ||
					!field.HedgeFlag.isValid())
				{
					field.HedgeFlag=CHF_Speculation;
				}
				QueryInvestorFee(pPackage,field,ResponseSessionID);
				it.Next();
			} 
			GET_ACCURATE_USEC_TIME(endTime); 
			if( buffer[0]) 
			{
				g_logMemoryDBTable.logQuery(sessionRef,startTime,endTime,buffer);
			}
			break; 
		}
		case TID_ReqQryInvestorMargin: 
		{ 
			char buffer[4000] = {0}; 
			long startTime,endTime; 
			GET_ACCURATE_USEC_TIME(startTime); 
			CQryInvestorMarginField field; 
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe); 
			while(!it.IsEnd()) 
			{ 
				it.Retrieve(&field); 
				if (g_logMemoryDBTable.canLog()) 
				{ 
					field.dumpLine(buffer,4000); 
				}
				if (field.HedgeFlag.isNull() ||
					!field.HedgeFlag.isValid())
				{
					field.HedgeFlag=CHF_Speculation;
				}
/*** SIR XLONG BEGIN ***/
				QueryInvestorMargin(pPackage,field,ResponseSessionID);
				it.Next();
/*** SIR XLONG END ***/
			} 
			GET_ACCURATE_USEC_TIME(endTime); 
			if( buffer[0]) 
			{
				g_logMemoryDBTable.logQuery(sessionRef,startTime,endTime,buffer);
			}
			break; 
		}
		case TID_ReqQrySGEDeferRate: 
			{ 
				char buffer[4000] = {0}; 
				long startTime,endTime; 
				GET_ACCURATE_USEC_TIME(startTime); 
				CQrySGEDeferRateField field; 
				CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe); 
				while(!it.IsEnd()) 
				{ 
					it.Retrieve(&field); 
					if (g_logMemoryDBTable.canLog()) 
					{ 
						field.dumpLine(buffer,4000); 
					} 
					CSGEDeferRateIterator* pIt = NULL; 
					success = m_pService->QuerySGEDeferRate(field.InstrumentID, &pIt, sessionRef, &m_Transaction); 
					if(!success) 
					{ 
						ResponseErrorMsg(pPackage,TID_RspQrySGEDeferRate,ResponseSessionID); 
						return false; 
					} 
					CRspInfoField responseField; 
					m_pErrorEngine->getLastError(&errorCode,&errMsg); 
					responseField.ErrorID = errorCode; 
					responseField.ErrorMsg = errMsg; 
					m_pRspMessage->PrepareResponse(pPackage, TID_RspQrySGEDeferRate); 
					CSGEDeferRateField rspField; 
					CSGEDeferRate * pData = pIt->next(); 
					XTP_ADD_FIELD(m_pRspMessage,&responseField); 
					while(pData) 
					{ 
						CopySGEDeferRateEntity(&rspField,pData); 
						g_logMemoryDBTable.logField((void *)pData,"SGEDeferRate",LOG_QUERY);
						while(XTP_ADD_FIELD(m_pRspMessage,&rspField) < 0) 
						{ 
							FlushPackage(false,ResponseSessionID); 
							m_pRspMessage->PrepareResponse(pPackage, TID_RspQrySGEDeferRate,CHAIN_CONTINUE);
							XTP_ADD_FIELD(m_pRspMessage,&responseField);
						} 
						pData = pIt->next(); 
					} 
					m_pRspMessage->SetChain(CHAIN_LAST);
					FlushPackage(true,ResponseSessionID); 
					delete pIt; 
					it.Next(); 
					//break; 
				} 
				GET_ACCURATE_USEC_TIME(endTime); 
				if( buffer[0]) 
				{
					g_logMemoryDBTable.logQuery(sessionRef,startTime,endTime,buffer);
				}
				break; 
		}
	case TID_ReqQryInvestorOptionFee: 
		{ 
			char buffer[4000] = {0}; 
			long startTime,endTime; 
			GET_ACCURATE_USEC_TIME(startTime); 
			CQryInvestorOptionFeeField field; 
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe); 
			while(!it.IsEnd()) 
			{ 
				it.Retrieve(&field); 
				if (g_logMemoryDBTable.canLog()) 
				{ 
					field.dumpLine(buffer,4000); 
				}
				QueryInvestorOptionFee(pPackage,field,ResponseSessionID);
				it.Next();
			} 
			GET_ACCURATE_USEC_TIME(endTime); 
			if( buffer[0]) 
			{
				g_logMemoryDBTable.logQuery(sessionRef,startTime,endTime,buffer);
			}
			break; 
		}
	case TID_ReqQryExchangeDiffTime: 
		{ 
			char buffer[4000] = {0}; 
			long startTime,endTime; 
			GET_ACCURATE_USEC_TIME(startTime); 
			DWORD locTime;
			GET_ACCURATE_SEC_TIME(locTime);
			
			CQryExchangeDiffTimeField field; 
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe); 
			while(!it.IsEnd()) 
			{ 
				it.Retrieve(&field); 
				if (g_logMemoryDBTable.canLog()) 
				{ 
					field.dumpLine(buffer,4000); 
				} 
				CExchTimeDiffIterator* pIt = NULL; 
				success = m_pService->QueryExchTimeDiff(field.ExchangeID, &pIt,sessionRef,&m_Transaction); 
				if(!success) 
				{
					ResponseErrorMsg(pPackage,TID_RspQryExchangeDiffTime,ResponseSessionID); 
					return false; 
				} 
				CRspInfoField responseField; 
				m_pErrorEngine->getLastError(&errorCode,&errMsg); 
				responseField.ErrorID = errorCode; 
				responseField.ErrorMsg = errMsg; 
				m_pRspMessage->PrepareResponse(pPackage, TID_RspQryExchangeDiffTime); 
				CRspExchangeDiffTimeField rspField; 
				CExchTimeDiff * pData = pIt->next(); 
				XTP_ADD_FIELD(m_pRspMessage,&responseField); 
				while(pData) 
				{ 
					rspField.ExchangeID = pData->ExchangeID;	
					rspField.TradingDay = pData->TradingDay;
					rspField.DiffSnd = pData->DiffSnd;
					CTime CLocTime(locTime+pData->DiffSnd);
					rspField.ExchangeTime = CLocTime.ToString();
					g_logMemoryDBTable.logField((void *)pData,"ExchTimeDiff",LOG_QUERY);
					while(XTP_ADD_FIELD(m_pRspMessage,&rspField) < 0) 
					{ 
						FlushPackage(false,ResponseSessionID); 
						m_pRspMessage->PrepareResponse(pPackage, TID_RspQryExchangeDiffTime,CHAIN_CONTINUE);
						XTP_ADD_FIELD(m_pRspMessage,&responseField);
					} 
					pData = pIt->next(); 
				} 
				m_pRspMessage->SetChain(CHAIN_LAST);
				FlushPackage(true,ResponseSessionID); 
				delete pIt; 
				it.Next(); 
				//break; 
			} 
			GET_ACCURATE_USEC_TIME(endTime); 
			if( buffer[0]) 
			{
				g_logMemoryDBTable.logQuery(sessionRef,startTime,endTime,buffer);
			}
			break; 
		}
	case TID_ReqQrySeatInfo: 
		{ 
			char buffer[4000] = {0}; 
			long startTime,endTime; 
			GET_ACCURATE_USEC_TIME(startTime); 
			CQrySeatInfoField field; 
			CNamedFieldIterator it = pPackage->GetNamedFieldIterator(&field.m_Describe); 
			while(!it.IsEnd()) 
			{ 
				it.Retrieve(&field); 
				if (g_logMemoryDBTable.canLog()) 
				{ 
					field.dumpLine(buffer,4000); 
				}
				QuerySeatInfo(pPackage,field,ResponseSessionID);
				it.Next();
			} 
			GET_ACCURATE_USEC_TIME(endTime); 
			if( buffer[0]) 
			{
				g_logMemoryDBTable.logQuery(sessionRef,startTime,endTime,buffer);
			}
			break; 
		}
	default:
		REPORT_EVENT(LOG_INFO,"CTradingQueryServiceXtpLink::handleRequest","Not defined TID: %d \n",pPackage->GetTid());
		return true;
	}
	
	if (success)
		m_Transaction.commit();
	else
		m_Transaction.rollback();
	return success;
}

bool CTradingQueryServiceXtpLink::handleMessage(CXTPPackage *pPackage, const TSessionRef &sessionRef)
{
	return true;
}

/* 表ClientPosition中并没有InvestorID这个字段，所以这里单独传其参数值进去。
// 如果将来表ClientPosition中新增加了字段，则这个函数可能也需要增加字段。
*/
bool CTradingQueryServiceXtpLink::copyInvestorPositionField(CInvestorPositionField *pClientField,CInvestorPositionField *pInvestorField,CInvestorIDType &investorID)
{
//	pInvestorField->InvestorID 			= pClientField->InvestorID;    修改它
	pInvestorField->InvestorID 			= investorID;
	CopyPositionEntity(pInvestorField,pClientField);
	return true;
}

bool CTradingQueryServiceXtpLink::QueryInvestorFee(CXTPPackage *pPackage,CQryInvestorFeeField &field,DWORD ResponseSessionID)
{
	m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorFee);
	CRspInfoField responseField;
	responseField.ErrorID=ERROR_NONE;
	responseField.ErrorMsg=m_pErrorEngine->getErrorMsg(ERROR_NONE);
	XTP_ADD_FIELD(m_pRspMessage,&responseField);

	//如果填写了investorid，就使用这个investorid，如果没有，就得自己找
	if(field.InvestorID.isNull())
	{
		InvestorIDVector vInvestorID;
		baseAlgorithm.fromUserGetInvestors(m_pDB,field.LogBrokerID,field.LogUserID,vInvestorID);
		for(int iCount=0;iCount<vInvestorID.size();iCount++)
		{
			QueryInvestorFeeEach(vInvestorID[iCount],pPackage,field,ResponseSessionID);	
		}
	}
	else
	{
		if (!baseAlgorithm.CheckUserInvestor(m_pDB,field.LogBrokerID,field.LogUserID,field.InvestorID))
		{
			m_pErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
			return false;
		}
		QueryInvestorFeeEach(field.InvestorID,pPackage,field,ResponseSessionID);
	}

	FlushPackage(true,ResponseSessionID);	
	return true;
}

bool CTradingQueryServiceXtpLink::QueryInvestorFeeEach(CInvestorIDType &InvestorID,CXTPPackage *pPackage,CQryInvestorFeeField &field,DWORD ResponseSessionID)
{
	CRspInfoField responseField;
	responseField.ErrorID=ERROR_NONE;
	responseField.ErrorMsg=m_pErrorEngine->getErrorMsg(ERROR_NONE);

	//如果没有填写合约号，按照产品返回所有的合约
	if(field.InstrumentID.isNull())
	{
		m_ExchangeMap.clear();
		CClientTradingID *pClientTradingID =m_pDB->m_ClientTradingIDFactory->startFindByBrokerIDInvestorID(field.LogBrokerID, InvestorID);
		while(NULL !=pClientTradingID)
		{
			m_ExchangeMap.insert(CExchangeMap::value_type(pClientTradingID->ExchangeID,1));
			pClientTradingID = m_pDB->m_ClientTradingIDFactory->findNextByBrokerIDInvestorID();
		}
		m_pDB->m_ClientTradingIDFactory->endFindByBrokerIDInvestorID();
		if (m_ExchangeMap.empty())
		{
			return true;
		}
		//这里有两种算法，一个是直接取表里面的数据，另外一个就是按照合约帮助客户全部拿到合约级别的数据
		CInstrument *pInstrument = m_pDB->m_InstrumentFactory->getFirst();
		for(;pInstrument!=NULL;pInstrument=m_pDB->m_InstrumentFactory->getNext())
		{
			if (m_ExchangeMap.find(pInstrument->ExchangeID) ==m_ExchangeMap.end())
			{
				continue;
			}
			CInvestorFee * pResult = baseAlgorithm.getInvestorFee(m_pDB,pInstrument,field.LogBrokerID,InvestorID,field.HedgeFlag);
			if(pResult != NULL)
			{
				CInvestorFeeField rspField; 
				CopyInvestorFeeEntity(&rspField,pResult); 
				rspField.ExchangeID = pInstrument->ExchangeID;
				rspField.InstrumentID = pInstrument->InstrumentID;
				rspField.InvestorID = InvestorID;
				while(XTP_ADD_FIELD(m_pRspMessage,&rspField) < 0) 
				{ 
					FlushPackage(false,ResponseSessionID); 
					m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorFee,CHAIN_CONTINUE); 
					XTP_ADD_FIELD(m_pRspMessage,&responseField); 
				}
			}			
		}
		m_pDB->m_InstrumentFactory->endGet();
	}
	else //如果合约，直接查找返回
	{
		CInstrument *pInstrument = m_pDB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(field.ExchangeID,field.InstrumentID);
		if(NULL!=pInstrument)
		{
			CInvestorFee * pResult = baseAlgorithm.getInvestorFee(m_pDB,pInstrument,field.LogBrokerID,InvestorID,field.HedgeFlag);
			if(pResult == NULL)
			{
				m_pErrorEngine->reportError(ERROR_ERROR);
				ResponseErrorMsg(pPackage,TID_RspQryInvestorFee,ResponseSessionID);
				return false;
			}
			CInvestorFeeField rspField; 
			CopyInvestorFeeEntity(&rspField,pResult); 
			rspField.ExchangeID = pInstrument->ExchangeID;
			rspField.InstrumentID = field.InstrumentID;
			rspField.InvestorID = InvestorID;
			while(XTP_ADD_FIELD(m_pRspMessage,&rspField) < 0) 
			{ 
				FlushPackage(false,ResponseSessionID); 
				m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorFee,CHAIN_CONTINUE); 
				XTP_ADD_FIELD(m_pRspMessage,&responseField); 
			}
		}
	}

	return true;
}


bool CTradingQueryServiceXtpLink::QueryInvestorOptionFee(CXTPPackage *pPackage,CQryInvestorOptionFeeField &field,DWORD ResponseSessionID)
{
	m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorOptionFee);
	CRspInfoField responseField;
	responseField.ErrorID=ERROR_NONE;
	responseField.ErrorMsg=m_pErrorEngine->getErrorMsg(ERROR_NONE);
	XTP_ADD_FIELD(m_pRspMessage,&responseField);

	//如果填写了investorid，就使用这个investorid，如果没有，就得自己找
	if(field.InvestorID.isNull())
	{
		InvestorIDVector vInvestorID;
		baseAlgorithm.fromUserGetInvestors(m_pDB,field.LogBrokerID,field.LogUserID,vInvestorID);
		for(int iCount=0;iCount<vInvestorID.size();iCount++)
		{
			QueryInvestorOptionFeeEach(vInvestorID[iCount],pPackage,field,ResponseSessionID);	
		}
	}
	else
	{
		if (!baseAlgorithm.CheckUserInvestor(m_pDB,field.LogBrokerID,field.LogUserID,field.InvestorID))
		{
			m_pErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
			return false;
		}
		QueryInvestorOptionFeeEach(field.InvestorID,pPackage,field,ResponseSessionID);
	}

	FlushPackage(true,ResponseSessionID);	
	return true;
}

bool CTradingQueryServiceXtpLink::QueryInvestorOptionFeeEach(CInvestorIDType &InvestorID,CXTPPackage *pPackage,CQryInvestorOptionFeeField &field,DWORD ResponseSessionID)
{
	CRspInfoField responseField;
	responseField.ErrorID=ERROR_NONE;
	responseField.ErrorMsg=m_pErrorEngine->getErrorMsg(ERROR_NONE);

	//如果没有填写合约号，按照产品返回所有的合约
	if(field.InstrumentID.isNull())
	{
		m_ExchangeMap.clear();
		CClientTradingID *pClientTradingID =m_pDB->m_ClientTradingIDFactory->startFindByBrokerIDInvestorID(field.LogBrokerID, InvestorID);
		while(NULL !=pClientTradingID)
		{
			m_ExchangeMap.insert(CExchangeMap::value_type(pClientTradingID->ExchangeID,1));
			pClientTradingID = m_pDB->m_ClientTradingIDFactory->findNextByBrokerIDInvestorID();
		}
		m_pDB->m_ClientTradingIDFactory->endFindByBrokerIDInvestorID();
		if (m_ExchangeMap.empty())
		{
			return true;
		}
		//这里有两种算法，一个是直接取表里面的数据，另外一个就是按照合约帮助客户全部拿到合约级别的数据
		CInstrument *pInstrument = m_pDB->m_InstrumentFactory->getFirst();
		for(;pInstrument!=NULL;pInstrument=m_pDB->m_InstrumentFactory->getNext())
		{
			if (m_ExchangeMap.find(pInstrument->ExchangeID) ==m_ExchangeMap.end())
			{
				continue;
			}
			CInvestorOptionFee * pResult = baseAlgorithm.getInvestorOptionFee(m_pDB,pInstrument,field.LogBrokerID,InvestorID);
			if(pResult != NULL)
			{
				CInvestorOptionFeeField rspField; 
				CopyInvestorOptionFeeEntity(&rspField,pResult); 
				rspField.ExchangeID = pInstrument->ExchangeID;
				rspField.InstrumentID = pInstrument->InstrumentID;
				rspField.InvestorID = InvestorID;
				while(XTP_ADD_FIELD(m_pRspMessage,&rspField) < 0) 
				{ 
					FlushPackage(false,ResponseSessionID); 
					m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorOptionFee,CHAIN_CONTINUE); 
					XTP_ADD_FIELD(m_pRspMessage,&responseField); 
				}
			}			
		}
		m_pDB->m_InstrumentFactory->endGet();
	}
	else //如果合约，直接查找返回
	{
		CInstrument *pInstrument = m_pDB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(field.ExchangeID,field.InstrumentID);
		if(NULL!=pInstrument)
		{
			CInvestorOptionFee * pResult = baseAlgorithm.getInvestorOptionFee(m_pDB,pInstrument,field.LogBrokerID,InvestorID);
			if(pResult == NULL)
			{
				m_pErrorEngine->reportError(ERROR_ERROR);
				ResponseErrorMsg(pPackage,TID_RspQryInvestorOptionFee,ResponseSessionID);
				return false;
			}
			CInvestorOptionFeeField rspField; 
			CopyInvestorOptionFeeEntity(&rspField,pResult); 
			rspField.ExchangeID = pInstrument->ExchangeID;
			rspField.InstrumentID = field.InstrumentID;
			rspField.InvestorID = InvestorID;
			while(XTP_ADD_FIELD(m_pRspMessage,&rspField) < 0) 
			{ 
				FlushPackage(false,ResponseSessionID); 
				m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorOptionFee,CHAIN_CONTINUE); 
				XTP_ADD_FIELD(m_pRspMessage,&responseField); 
			}
		}
	}

	return true;
}


bool CTradingQueryServiceXtpLink::QueryInvestorMargin(CXTPPackage *pPackage,CQryInvestorMarginField &field,DWORD ResponseSessionID)
{
	m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorMargin);
	CRspInfoField responseField;
	responseField.ErrorID=ERROR_NONE;
	responseField.ErrorMsg=m_pErrorEngine->getErrorMsg(ERROR_NONE);
	XTP_ADD_FIELD(m_pRspMessage,&responseField);

	//如果填写了investorid，就使用这个investorid，如果没有，就得自己找
	if(field.InvestorID.isNull())
	{
		InvestorIDVector vInvestorID;
		baseAlgorithm.fromUserGetInvestors(m_pDB,field.LogBrokerID,field.LogUserID,vInvestorID);
		for(int iCount=0;iCount<vInvestorID.size();iCount++)
		{
			QueryInvestorMarginEach(vInvestorID[iCount],pPackage,field,ResponseSessionID);	
		}
	}
	else
	{
		if (!baseAlgorithm.CheckUserInvestor(m_pDB,field.LogBrokerID,field.LogUserID,field.InvestorID))
		{
			m_pErrorEngine->reportError(ERROR_QUERY_USERID_INVESTORID_INVALID);
			return false;
		}
		QueryInvestorMarginEach(field.InvestorID,pPackage,field,ResponseSessionID);
	}

	FlushPackage(true,ResponseSessionID);	
	return true;
}

bool CTradingQueryServiceXtpLink::QueryInvestorMarginEach(CInvestorIDType &InvestorID,CXTPPackage *pPackage,CQryInvestorMarginField &field,DWORD ResponseSessionID)
{
	CRspInfoField responseField;
	responseField.ErrorID=ERROR_NONE;
	responseField.ErrorMsg=m_pErrorEngine->getErrorMsg(ERROR_NONE);

	//如果没有填写合约号，按照产品返回所有的合约
	if(field.InstrumentID.isNull())
	{
		CInstrument *pInstrument = m_pDB->m_InstrumentFactory->getFirst();
		for(;pInstrument!=NULL;pInstrument=m_pDB->m_InstrumentFactory->getNext())
		{
			vector<CInvestorMargin*> Result = baseAlgorithm.getInvestorMargin(m_pDB,pInstrument->ExchangeID,pInstrument->ProductID,pInstrument->InstrumentID,field.LogBrokerID,InvestorID);
			for(int count=0;count<Result.size();count++)
			{
				CInvestorMarginField rspField; 
				CopyInvestorMarginEntity(&rspField,Result[count]); 
				rspField.ExchangeID = pInstrument->ExchangeID;
				rspField.InstrumentID = pInstrument->InstrumentID;
				rspField.InvestorID = InvestorID;
				while(XTP_ADD_FIELD(m_pRspMessage,&rspField) < 0) 
				{ 
					FlushPackage(false,ResponseSessionID); 
					m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorMargin, CHAIN_CONTINUE); 
					XTP_ADD_FIELD(m_pRspMessage,&responseField); 
				}
			}		
		}
		m_pDB->m_InstrumentFactory->endGet();
	}
	else //如果合约，直接查找返回
	{
		CInstrument *pInstrument = m_pDB->m_InstrumentFactory->findByExchangeIDAndInstrumentID(field.ExchangeID,field.InstrumentID);
		if(NULL!=pInstrument)
		{
			vector<CInvestorMargin*> Result = baseAlgorithm.getInvestorMargin(m_pDB,pInstrument->ExchangeID,pInstrument->ProductID,pInstrument->InstrumentID,field.LogBrokerID,InvestorID);
			for(int count=0;count<Result.size();count++)
			{
				CInvestorMarginField rspField; 
				CopyInvestorMarginEntity(&rspField,Result[count]);
				rspField.ExchangeID = pInstrument->ExchangeID;
				rspField.InstrumentID = field.InstrumentID;
				rspField.InvestorID = InvestorID;
				while(XTP_ADD_FIELD(m_pRspMessage,&rspField) < 0) 
				{ 
					FlushPackage(false,ResponseSessionID); 
					m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorMargin,CHAIN_CONTINUE); 
					XTP_ADD_FIELD(m_pRspMessage,&responseField); 
				}
			}
		}
	}

	return true;
}

bool CTradingQueryServiceXtpLink::QuerySeatInfo(CXTPPackage *pPackage,CQrySeatInfoField &field,DWORD ResponseSessionID)
{
	m_pRspMessage->PrepareResponse(pPackage, TID_RspQrySeatInfo);
	CRspInfoField responseField;
	responseField.ErrorID=ERROR_NONE;
	responseField.ErrorMsg=m_pErrorEngine->getErrorMsg(ERROR_NONE);
	XTP_ADD_FIELD(m_pRspMessage,&responseField);
	
	CSeat *pIter = m_pDB->m_SeatFactory->getFirst();
	while(pIter!=NULL)
	{
		if (!pIter->IsActive ||
			!field.ExchangeID.isNull() && pIter->ExchangeID != field.ExchangeID )
		{
			pIter = m_pDB->m_SeatFactory->getNext();
			continue;
		}
		CSeatInfoField rspField; 
		memset(tmp,0,sizeof(tmp));
		sprintf(tmp,"%d",pIter->APIID.getValue());
		rspField.BranchID = tmp;
		rspField.BrokerID = pIter->BrokerID;
		rspField.ExchangeID = pIter->ExchangeID;
		rspField.ParticipantID = pIter->ParticipantID;
		rspField.SeatID = pIter->SeatID;
		while(XTP_ADD_FIELD(m_pRspMessage,&rspField) < 0) 
		{ 
			FlushPackage(false,ResponseSessionID); 
			m_pRspMessage->PrepareResponse(pPackage, TID_RspQryInvestorMargin,CHAIN_CONTINUE); 
			XTP_ADD_FIELD(m_pRspMessage,&responseField); 
		}
		pIter = m_pDB->m_SeatFactory->getNext();
	}
	m_pDB->m_SeatFactory->endGet();
	
	FlushPackage(true,ResponseSessionID);	
	return true;
}