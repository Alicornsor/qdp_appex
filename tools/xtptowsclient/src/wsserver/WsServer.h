#ifndef WSSERVER_H_

#ifndef ASIO_STANDALONE
#define ASIO_STANDALONE
#define _WEBSOCKETPP_CPP11_RANDOM_DEVICE_
#define _WEBSOCKETPP_CPP11_TYPE_TRAITS_
#define _SCL_SECURE_NO_WARNINGS
#endif // !ASIO_STANDALONE

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/config/core.hpp>
#include <websocketpp/server.hpp>

#include "platform.h"
#include "monitorIndex.h"
#include "SelectReactor.h"
#include "CachedFileFlow.h"
#include "XTPPackage.h"
#include "FlowReader.h"
#include "XtpPackageDesc.h"

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

using server = websocketpp::server<websocketpp::config::asio>;
using Connections = std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>>;

class CReadFlowHandler;
class CWsServer
{
public:
	CWsServer(CFlow *pSerailFlow);
	~CWsServer();

	void run(uint16_t port);

	void on_open(connection_hdl hdl);

	void on_close(connection_hdl hdl);

	void on_message(connection_hdl hdl, server::message_ptr msg);

	void send_message_to_hdl(connection_hdl hdl, string strMessage);

	void send_messages_to_all(string strMessage);

	//void OnReadFlowProcess(connection_hdl hdl); //��ȡ���ļ�

private:
	server m_webSocketServer;
	Connections m_connections; //��ǰ���е�����
	
	CReadFlowHandler *m_pReadFlowHandler; //ÿ�������Ӷ���Ҫ���¶�ȡ���ļ�
	CFlowReader m_reader;
	CFlow *m_pSerialFlow; //�����
	CXTPPackage m_ReadPackage;
};

const int ON_READFLOW_GET_ALL_MESSAGE_EVENT = 12001;
//������ȡ���ļ����߳� ɸѡ�����͵�websocket�ͻ���
class CReadFlowHandler : public CEventHandler
{
public:
	CReadFlowHandler(CSelectReactor *pReactor, CWsServer *pWsServer, CFlow *pSerailFlow);

	~CReadFlowHandler();

	//�����߳�
	void Start();

	//ֹͣ�߳�
	void Stop();

	/**����һ���¼�
	* @param nEventID �¼�ID
	* @param dwParam ��һ������
	* @param pParam �ڶ�������
	* @return ������
	*/
	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam);

	void OnReadFlowProcess(connection_hdl hdl);

private:
	CSelectReactor *m_pConnReactor;
	CWsServer *m_pWsServer;
	CFlowReader m_reader;
	CFlow *m_pSerialFlow; //�����
	CXTPPackage m_ReadPackage;
};

//��Intת��String
string MyIntToString(int nNum);
//��Intת��ʮ������
template <class T>
string MyIntToHex(T i);

//��XTP package��Ϣת��String��
string ConvertXtpToStr(CXTPPackage *pPackage);

#endif // !WSSERVER_H_

