#include "WsServer.h"

CWsServer::CWsServer()
{
	// Initialize Asio Transport
	m_webSocketServer.init_asio();

	// Register handler callbacks
	m_webSocketServer.set_open_handler(bind(&CWsServer::on_open, this, ::_1));
	m_webSocketServer.set_close_handler(bind(&CWsServer::on_close, this, ::_1));
	m_webSocketServer.set_message_handler(bind(&CWsServer::on_message, this, ::_1, ::_2));
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


void CWsServer::send_messages(string strMessage)
{
	lock_guard<mutex> lock(conMutex);
	for (auto &con : m_connections) //循环所有的连接发送
	{
		m_webSocketServer.send(
			con, strMessage, websocketpp::frame::opcode::text);
	}
}

