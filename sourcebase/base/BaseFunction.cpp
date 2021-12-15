#include "BaseFunction.h"
#ifdef WIN32
#include "Iphlpapi.h"
#include<stdio.h>
#pragma comment(lib,"Iphlpapi.lib")
#endif

string& Txttrim(string &s) 
{
    if (s.empty()) 
    {
        return s;
    }
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

vector<string> Txtsplit(const string& str, string separate_character)
{
    vector<string> vestr;
	int separate_characterLen = separate_character.size();
    int lastPosition = 0;
	int index = -1;
    while (-1 != (index = str.find(separate_character,lastPosition)))
    {

        vestr.push_back(str.substr(lastPosition,index - lastPosition));
        lastPosition = index + separate_characterLen;
    }
    string lastString = str.substr(lastPosition);
    if (!lastString.empty())
	{
        vestr.push_back(lastString);
	}
    return vestr;
}

#ifdef WIN32
bool GetMacByCmd(char *lpszMac)
{
	//命令行输出缓冲大小
	const long MAX_COMMAND_SIZE = 10000;
	//获取MAC命令行
	char szFetCmd[] = "ipconfig /all";
	//网卡MAC地址的前导信息
	const string str4Search = "Physical Address. . . . . . . . . : ";
	//初始化返回MAC地址缓冲区
	memset(lpszMac, 0x00, sizeof(lpszMac));
	BOOL bret; 
	SECURITY_ATTRIBUTES sa; 
	HANDLE hReadPipe,hWritePipe;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
	sa.lpSecurityDescriptor = NULL; 
	sa.bInheritHandle = true; 

	 //创建管道
	bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
	if(!bret)
	{
		return false;
	}
	//控制命令行窗口信息
	STARTUPINFO si; 
	//返回进程信息
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO); 
	GetStartupInfo(&si); 
	si.hStdError = hWritePipe; 
	si.hStdOutput = hWritePipe; 
	si.wShowWindow = SW_HIDE; //隐藏命令行窗口
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	//创建获取命令行进程
	bret = CreateProcess (NULL, szFetCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi ); 
	if(!bret)
	{
		return false;
	}
	char szBuffer[MAX_COMMAND_SIZE+1]; //放置命令行输出缓冲区
	string strBuffer;

	//使用上面的win7会造成假死情况
	//WaitForSingleObject (pi.hProcess, INFINITE);
	WaitForSingleObject(pi.hProcess, 300);
	unsigned long count;
	memset(szBuffer, 0x00, sizeof(szBuffer));
	bret  =  ReadFile(hReadPipe,szBuffer,MAX_COMMAND_SIZE,&count,0);

	//关闭所有的句柄
	CloseHandle(hWritePipe);
	CloseHandle(pi.hProcess); 
	CloseHandle(pi.hThread); 
	CloseHandle(hReadPipe);		
	
	if(!bret)
	{
		return false;
	}

	return true;
}
#endif

bool GetIPAddress(vector<string> *pIPVec)
{
#ifdef WIN32
    ULONG ulOutBufLen = (unsigned long)sizeof(IP_ADAPTER_INFO);
	
    PIP_ADAPTER_INFO pAdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) { // 分配内存失败
        return false;
    }
	
    // 第一次调用，获得pAdapterInfo的必要大小，存储在ulOutBufLen，防止分配的内存过小
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
        if (pAdapterInfo == NULL) { // 分配内存失败
            return false;
        }
    }
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR) {
        PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
        while (pAdapter) {
            pIPVec->push_back(pAdapter->IpAddressList.IpAddress.String);
            pAdapter = pAdapter->Next;
        }
    }
	if (pAdapterInfo)
	{
		free(pAdapterInfo);
	}
	
#else
    char localIpAddrBuf[50];
    memset(localIpAddrBuf, 0x00, sizeof(localIpAddrBuf));
    // 根据IP获得interface name
    struct ifaddrs *ifaddrHeader, *ifaddrItor;
	
    if(getifaddrs(&ifaddrHeader) == -1) {
        return false;
    }
	
    for(ifaddrItor = ifaddrHeader; ifaddrItor != NULL; ifaddrItor = ifaddrItor->ifa_next) {
        if (ifaddrItor->ifa_addr == NULL)
            continue;
		
        if(ifaddrItor->ifa_addr->sa_family != AF_INET) // 只获取TCP/IP网卡的信息
            continue;
		
        
        struct sockaddr_in *sin = NULL;
        sin = (struct sockaddr_in *)ifaddrItor->ifa_addr;
        pIPVec->push_back(inet_ntoa(sin->sin_addr));       
    }
    freeifaddrs(ifaddrHeader); // 释放存储NIC信息的链表结构
#endif
	return true;
}