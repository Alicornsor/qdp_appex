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

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

using server = websocketpp::server<websocketpp::config::asio>;
using Connections = std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>>;
std::mutex conMutex;

class CWsServer
{
public:
	CWsServer();

	void run(uint16_t port);

	void on_open(connection_hdl hdl);

	void on_close(connection_hdl hdl);

	void on_message(connection_hdl hdl, server::message_ptr msg);

	void send_messages(string strMessage);

private:
	server m_webSocketServer;
	Connections m_connections; //当前所有的连接
};

#endif // !WSSERVER_H_
