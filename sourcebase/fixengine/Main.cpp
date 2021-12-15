#include <IOSTREAM>
#include "Message.h"
#include "SessionSettings.h"

#include "Utility.h"

#include <winsock.h>

int TestConnect( const std::string& address, int port)
{
	WORD wVersionRequested;  
    WSADATA wsaData;  
    int err;  
      
    wVersionRequested = MAKEWORD( 1, 1 );  
	
    err = WSAStartup( wVersionRequested, &wsaData );  
    if ( err != 0 ) {  
        return -1;  
    }  
	
    if ( LOBYTE( wsaData.wVersion ) != 1 ||  
        HIBYTE( wsaData.wVersion ) != 1 ) {  
        WSACleanup( );  
        return -1;   
    }  

	SOCKET m_socket=socket(AF_INET,SOCK_STREAM,0);
	if (m_socket == INVALID_SOCKET) 
	{
		return -1;
	}

	SOCKADDR_IN addrSrv;  
    addrSrv.sin_addr.S_un.S_addr=inet_addr(address.c_str());//服务器端的地址  
    addrSrv.sin_family=AF_INET;  
    addrSrv.sin_port=htons(port);  

    //先建立连接
	int nRet = connect(m_socket,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR)); 
	if (nRet==SOCKET_ERROR)
	{
		return -1;
	}
	return m_socket;
}

int main(int argc, char *argv[])
{
	FIX::Message msg;
	int socketid;
	
	msg.getHeader().setField( FIX::MsgSeqNum(1) );
	msg.getHeader().setField( FIX::BeginString("FIX.4.2") );
	msg.getHeader().setField( FIX::SenderCompID("quantdoFC") );
	msg.getHeader().setField( FIX::TargetCompID("CQG_Gateway") );
	msg.getHeader().setField( FIX::MsgType(FIX::MsgType_Logon) );
	msg.setField(FIX::ResetSeqNumFlag(true));


	FIX::UtcTimeStamp now;
	msg.getHeader().setField(FIX::SendingTime(now, false));

	msg.setField(FIX::RawData("quantdo_pass"));
	msg.setField(FIX::SenderSubID("TestFIXMarketData"));
	msg.setField(FIX::EncryptMethod(0));
	msg.setField(FIX::HeartBtInt(30));


	std::cout << msg << std::endl;

	FIX::SessionSettings m_settings("..\\conf\\tradeclient.cfg");
	socketid = TestConnect( "208.48.16.202",6912 );
	if (socketid == -1)
	{
		printf("[ERR]Connect to CQG error\n");
	}
	else
	{
		printf("[OK]Connect to CQG success\n");
	}
	
	//
	std::string messageString;
	msg.toString( messageString );
	send(socketid,messageString.c_str(),messageString.size(),0);

	char recvBuf[1024]={0};  
    recv(socketid,recvBuf, sizeof(recvBuf),0);  
    printf("%s\n",recvBuf); 



	closesocket(socketid);
	printf("Hello world\n");
	return 0;
}