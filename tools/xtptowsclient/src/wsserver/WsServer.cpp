#include "WsServer.h"

std::mutex conMutex;

CWsServer::CWsServer(CFlow *pSerailFlow)
{
	m_pSerialFlow = pSerailFlow;
	m_ReadPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE, 1000);

	// Initialize Asio Transport
	m_webSocketServer.init_asio();

	// Register handler callbacks
	m_webSocketServer.set_open_handler(bind(&CWsServer::on_open, this, ::_1));
	m_webSocketServer.set_close_handler(bind(&CWsServer::on_close, this, ::_1));
	m_webSocketServer.set_message_handler(bind(&CWsServer::on_message, this, ::_1, ::_2));

	//创建流文件读取的线程
	CSelectReactor *pReactor = new CSelectReactor();
	m_pReadFlowHandler = new CReadFlowHandler(pReactor, this, pSerailFlow);
	//启动该线程
	m_pReadFlowHandler->Start();
}

CWsServer::~CWsServer()
{
	if (NULL != m_pReadFlowHandler)
	{
		delete m_pReadFlowHandler;
		m_pReadFlowHandler = NULL;
	}
}

void CWsServer::run(uint16_t port)
{
	// listen on specified port
	m_webSocketServer.listen(port);

	// Start the server accept loop
	m_webSocketServer.start_accept();

	// Start the ASIO io_service run loop
	try
	{
		m_webSocketServer.run();
	}
	catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}

void CWsServer::on_open(connection_hdl hdl)
{
	cout << "on_open" << endl;
	lock_guard<mutex> lock(conMutex);
	m_connections.insert(hdl);

	//有连接，发送读取流文件的处理消息
	//m_pReadFlowHandler->PostEvent(ON_READFLOW_GET_ALL_MESSAGE_EVENT, 0, (void *)&hdl);
	send_message_to_hdl(hdl, "hello client");
}

void CWsServer::on_close(connection_hdl hdl)
{
	cout << "on_close" << endl;
	lock_guard<mutex> lock(conMutex);
	m_connections.erase(hdl);
}

void CWsServer::on_message(connection_hdl hdl, server::message_ptr msg)
{
	cout << "on_message" << endl;
	std::cout << "server received: " + msg->get_payload() << std::endl;
}

void CWsServer::send_message_to_hdl(connection_hdl hdl, string strMessage)
{
	lock_guard<mutex> lock(conMutex);
	m_webSocketServer.send(hdl, strMessage, websocketpp::frame::opcode::text);
}


void CWsServer::send_messages_to_all(string strMessage)
{
	lock_guard<mutex> lock(conMutex);
	for (auto &con : m_connections) //循环所有的连接发送
	{
		m_webSocketServer.send(
			con, strMessage, websocketpp::frame::opcode::text);
	}
}

//void CWsServer::OnReadFlowProcess(connection_hdl hdl)
//{
//	m_reader.AttachFlow(m_pSerialFlow, 0);
//	for (int i = 1;; ++i)
//	{
//		m_ReadPackage.Allocate(XTP_PACKAGE_MAX_SIZE + XTPHLEN);
//		if (!m_reader.GetNext(&m_ReadPackage))
//		{
//			REPORT_EVENT(LOG_CRITICAL, "CReadFlowHandler::OnReadFlowProcess", "no message in flow file");
//			break;
//		}
//
//		//将package转成特定格式并发送
//		string strMsg = ConvertXtpToStr(&m_ReadPackage);
//		if (strMsg.empty())
//		{
//			REPORT_EVENT(LOG_CRITICAL, "CReadFlowHandler::OnReadFlowProcess", "no message in package");
//			continue; //如果字符串为空则无需发送
//		}
//
//		//重新读流水，只会发送给当前连接的连接
//		send_message_to_hdl(hdl, strMsg);
//	}
//}


CReadFlowHandler::CReadFlowHandler(CSelectReactor *pReactor, CWsServer *pWsServer, CFlow *pSerailFlow)
	: CEventHandler(pReactor)
{
	m_pConnReactor = pReactor;
	m_pWsServer = pWsServer;
	m_pSerialFlow = pSerailFlow;
	m_ReadPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE, 1000);
}

CReadFlowHandler::~CReadFlowHandler()
{
}

void CReadFlowHandler::Start()
{
	m_pConnReactor->Create();
}

void CReadFlowHandler::Stop()
{
	m_pConnReactor->Stop();
	m_pConnReactor->Join();
}

int CReadFlowHandler::HandleEvent(int nEventID, DWORD dwParam, void *pParam)
{
	switch (nEventID)
	{
	case ON_READFLOW_GET_ALL_MESSAGE_EVENT:
	{
		connection_hdl hdl = *(connection_hdl*)pParam;
		OnReadFlowProcess(hdl);
		break;
	}
	default:
		break;
	}

	return 0;
}

void CReadFlowHandler::OnReadFlowProcess(connection_hdl hdl)
{
	m_reader.AttachFlow(m_pSerialFlow, 0);
	for (int i = 1;; ++i)
	{
		m_ReadPackage.Allocate(XTP_PACKAGE_MAX_SIZE + XTPHLEN);
		if (!m_reader.GetNext(&m_ReadPackage))
		{
			REPORT_EVENT(LOG_CRITICAL, "CReadFlowHandler::OnReadFlowProcess", "no message in flow file");
			break;
		}

		//将package转成特定格式并发送
		string strMsg = ConvertXtpToStr(&m_ReadPackage);
		if (strMsg.empty())
		{
			REPORT_EVENT(LOG_CRITICAL, "CReadFlowHandler::OnReadFlowProcess", "no message in package");
			continue; //如果字符串为空则无需发送
		}

		//重新读流水，只会发送给当前连接的连接
		m_pWsServer->send_message_to_hdl(hdl, strMsg);
	}
}

string MyIntToString(int nNum)
{
	ostringstream stream;
	stream << nNum;
	return stream.str();
}

template<typename T>
string MyIntToHex(T i)
{
	std::stringstream stream;
	stream << "0X"
		<< std::setfill('0') << std::setw(sizeof(T) * 2)
		<< std::hex << i;
	return stream.str();
}


string ConvertXtpToStr(CXTPPackage *pPackage)
{
	string strMsg = "";
	TXTPHeader *pHeader = pPackage->GetXTPHeader();
	if (NULL == pHeader)
	{
		return "";
	}
	strMsg = strMsg + "{\"Tid\":\"" + MyIntToHex(pHeader->Tid) + "\",\"SequenceNo\":\"" + MyIntToString(pHeader->SequenceNo) + "\",";

	int nTid = pPackage->GetTid();
	TPackageDefine **pFind = g_XTPPackageDefineMap.Find(nTid);
	if (pFind == NULL)
	{
		REPORT_EVENT(LOG_CRITICAL, "CReadFlowHandler::ConvertXtpToStr", "Can't find package define [%08x]", nTid);
		return "";
	}
	char buf[10000];
	TPackageDefine *pPackageDefine = *pFind;
	CFieldTypeIterator itor = pPackage->GetFieldTypeIterator();
	string strStructs = ""; //结构体消息
	string strTempFieldName = "";
	while (!itor.IsEnd()) //循环所有的消息（消息中可能包含多个结构体）
	{
		TFieldHeader fieldHeader;
		itor.RetrieveHeader(fieldHeader);
		TFieldUse *pFieldUse = pPackageDefine->fieldUse;
		
		for (int i = 0; i < pPackageDefine->fieldUseCount; i++) //循环不同的结构体
		{
			if (pFieldUse->fid == fieldHeader.FieldID)
			{
				itor.Retrieve(pFieldUse->pFieldDescribe, buf);
				CFieldDescribe *pFieldDescribe = pFieldUse->pFieldDescribe;
				string strFieldName = string(pFieldDescribe->GetFieldName());
				if (strTempFieldName != strFieldName)
				{
					if (strTempFieldName.empty()) //首次无需添加"],"
					{
						strStructs = strStructs + "\"" + strFieldName + "\":[{";
					}
					else
					{
						strStructs = strStructs + "]," + "\"" + strFieldName + "\":[{";
					}
					strTempFieldName = strFieldName;
				}
				else
				{
					strStructs += ",{";
				}
				for (int i = 0; i < pFieldDescribe->GetMemberCount(); i++) //循环Field的所有字段
				{
					TMemberDesc *pMemberDesc = pFieldDescribe->GetMemberDesc(i);
					strStructs = strStructs + "\"" + string(pMemberDesc->szName) + "\":";
					char *pMember = buf + pMemberDesc->nStructOffset;
					switch (pMemberDesc->nType)
					{
					case FT_WORD:
					{
						strStructs = strStructs + "\"" + MyIntToString(*((WORD *)pMember) & 0xFFFF) + "\"";
						break;
					}
					case FT_DWORD:
					{
						strStructs = strStructs + "\"" + MyIntToString(*((DWORD *)pMember)) + "\"";
						break;
					}
					case FT_BYTE:
					{
						if (pMemberDesc->nSize == 1)
						{
							strStructs = strStructs + "\"" + MyIntToString(*pMember & 0xFF) + "\""; //这里将char型数据
						}
						else
						{
							strStructs = strStructs + "\"" + string(pMember) + "\"";
						}
						break;
					}
					case FT_REAL4:
					{
						char strTemp[1024];
						memset(&strTemp, 0, sizeof(strTemp));
						sprintf(strTemp, "%f", *((REAL4 *)pMember));
						strStructs = strStructs + "\"" + strTemp + "\"";
						break;
					}
					case FT_REAL8:
					{
						double d;
						memcpy(&d, pMember, sizeof(REAL8));
						if (d == DOUBLE_NaN)
						{
							strStructs += "\"\"";
						}
						else
						{
							char strTemp[1024];
							memset(&strTemp, 0, sizeof(strTemp));
							sprintf(strTemp, "%lf", d);
							strStructs = strStructs + "\"" + strTemp + "\"";
						}
						break;
					}
					default:
						break;
					}
					//判断是否为最后一个字段，如果不是需要加逗号
					if (i != (pFieldDescribe->GetMemberCount() - 1))
					{
						strStructs += ",";
					}
				}
				strStructs += "}";
				break;
			}
			pFieldUse++;
		}
		itor.Next();
		//判断是否为最后一条字段消息, 如果不是需要加'],' 否则加']'
		if (itor.IsEnd())
		{
			strStructs += "]";
		}
	}
	strMsg = strMsg + strStructs + "}";
	//REPORT_EVENT(LOG_CRITICAL, "CReadFlowHandler::ConvertXtpToStr", "Msg: %s", strMsg.c_str());
	printf("Msg:%s\n", strMsg.c_str());
	return strMsg;
}
