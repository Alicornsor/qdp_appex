// TestApi.cpp : Defines the entry point for the console application.
//
#include "public.h"
#include "platform.h"
#include "FtdcUserApiImpl.h"
#include "CConfig.h"
#include "QdpFtdcUserApiStruct.h"
#include "QdpFtdcUserApi.h"
#include <iostream>

#define PORT_ID_API 12345

//2.��ַ��Ϣ
const int BUFLEN=512;
char g_frontaddr[BUFLEN];
const char* TEST_API_INI_NAME="./dumptool.ini";
CQdpFtdcUserApi * g_puserapi=NULL;
///�����û�����
TQdpFtdcUserIDType	g_UserID;
///����
TQdpFtdcPasswordType	g_Password;
//�����̱��
TQdpFtdcBrokerIDType g_BrokerID;
int g_nOrdLocalID=0;

/*---------------ȫ�ֺ�����---------------*/


void splitstr(const char* content, const char* token, vector<std::string>& vect)    
{    
	if(content == NULL)    
		return;    
	int len = strlen(content);    
	if(len <= 0)    
		return;    
	char* pBuf =(char*)malloc(len+1);    
	strcpy(pBuf , content);    
	char* str = strtok(pBuf , token);    
	while(str != NULL)    
	{    
		vect.push_back(str);    
		str = strtok(NULL, token);    
	}    
	free(pBuf);    
}

CConfig * g_pConfig=NULL;
/*�������ļ�*/
bool readconfig()
{
	//init
	memset(g_frontaddr,0,BUFLEN);
	memset(g_UserID,0,sizeof(TQdpFtdcUserIDType));
	memset(g_Password,0,sizeof(TQdpFtdcPasswordType));
	memset(g_BrokerID,0,sizeof(TQdpFtdcBrokerIDType));
	
	//read config
	g_pConfig = new CConfig(TEST_API_INI_NAME);	
	char* pFrontAddr=g_pConfig->getConfig("FrontAddr");
	if (pFrontAddr==NULL)
	{
		printf("û������ǰ�õ�ַ FrontAddr\n");
		return false;
	}
	strcpy(g_frontaddr,pFrontAddr);
	char* puserid=g_pConfig->getConfig("UserID");
	if (puserid==NULL)
	{
		printf("û�������û�ID UserID\n");
		return false;
	}
	strcpy(g_UserID,puserid);
	
	char* pPasswd=g_pConfig->getConfig("PassWd");
	if (pPasswd==NULL)
	{
		printf("û���������� PassWd\n");
		return false;
	}
	strcpy(g_Password,pPasswd);

	char* pBrokerID=g_pConfig->getConfig("BrokerID");
	if (pBrokerID==NULL)
	{
		printf("û�����þ����̱�� BrokerID\n");
		return false;
	}
	strcpy(g_BrokerID,pBrokerID);
	
	return true;
}

class CTraderSpi : public CQdpFtdcUserSpi  
{
public:
	CTraderSpi(CQdpFtdcUserApi *pTrader);
	virtual ~CTraderSpi();
	
	virtual void OnFrontConnected();
	virtual void OnHeartBeatWarning(int nTimeLapse);
	virtual void OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	virtual void OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
private:	
	CQdpFtdcUserApi *m_pUserApi;
};

CTraderSpi::CTraderSpi(CQdpFtdcUserApi *pTrader):m_pUserApi(pTrader)
{
	
}

CTraderSpi::~CTraderSpi()
{
	
}
void CTraderSpi::OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("Login Failed, Reason = [%s]\n",pRspInfo->ErrorMsg);
		return;
	}
	g_nOrdLocalID=atoi(pRspUserLogin->MaxOrderLocalID)+1;	
	printf("��¼�ɹ�����󱾵ر�����:%d\n",g_nOrdLocalID);
	CQdpFtdcMemDbField fld;
	strcpy(fld.MemTableName,"");
	m_pUserApi->ReqDumpMemDb(&fld,g_nOrdLocalID);
}

void CTraderSpi::OnFrontConnected()
{	
	CQdpFtdcReqUserLoginField reqUserLogin;
	memset(&reqUserLogin,0,sizeof(CQdpFtdcReqUserLoginField));		
	strcpy(reqUserLogin.UserID, g_UserID);
	
	strcpy(reqUserLogin.Password, g_Password);	
	strcpy(reqUserLogin.BrokerID,g_BrokerID);
	strcpy(reqUserLogin.UserProductInfo,USER_PRODUCT_INFO_DUMPTOOL);		
	m_pUserApi->ReqUserLogin(&reqUserLogin, g_nOrdLocalID);	
	
	printf("�����¼��ϯλ:%s\n",g_UserID);
}

void CTraderSpi::OnHeartBeatWarning(int nTimeLapse)
{
	printf("dump �ɹ������������˳�\n");
	exit(-1);
};

void CTraderSpi::OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	printf("dump �ɹ������������˳�\n");
	exit(-1);
}

int main(int argc, char* argv[])
{
	readconfig();
	CQdpFtdcUserApi *pTrader = CQdpFtdcUserApi::CreateFtdcUserApi("./");	
	g_puserapi=pTrader;

 	CTraderSpi spi(pTrader);
 	pTrader->RegisterFront(g_frontaddr);
	pTrader->RegisterSpi(&spi);
	pTrader->Init(PORT_ID_API);

	pTrader->Join();
	pTrader->Release();

	return 0;
}
