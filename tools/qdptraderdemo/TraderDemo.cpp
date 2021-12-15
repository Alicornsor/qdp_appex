// һ���򵥵����ӣ�����CQdpFtdcTraderApi��CQdpFtdcTraderSpi�ӿڵ�ʹ�á�
// ��������ʾһ������¼������Ĺ���
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>
#include <stdio.h>
#include <cstdlib>
#include "QdpFtdcTraderApi.h"

#ifdef WIN32
#define WINDOWS
#endif


#ifdef WINDOWS
#include <windows.h>
typedef HANDLE THREAD_HANDLE ;
#define SLEEP(ms) Sleep(ms)
#else
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
typedef pthread_t THREAD_HANDLE ;
#define SLEEP(ms) sleep((ms)/1000)
typedef unsigned int	DWORD;
#endif
// ����¼������Ƿ���ɵı�־
// ���͹�˾����
TQdpFtdcBrokerIDType g_chBrokerID;
// �����û�����
TQdpFtdcUserIDType g_chUserID;
//�û�������󱨵���
int g_UserOrderLocalID;


class  CThread  
{
public:
	/**���캯��
	*/
	CThread() 
	{
		m_hThread = (THREAD_HANDLE)0;
		m_IDThread = 0;
	}
	
	/**��������
	*/
	virtual ~CThread() {}
	
	/**����һ���߳�
	* @return true:�����ɹ� false:����ʧ��
	*/
	virtual bool Create()
	{
		if (m_hThread != (THREAD_HANDLE)0)
		{
			return true;
		}
		bool ret = true;
#ifdef WIN32
		m_hThread = ::CreateThread(NULL,0,_ThreadEntry,this,0,&m_IDThread);
		if(m_hThread==NULL)
		{
			ret = false;
		}
#else
		ret = (::pthread_create(&m_hThread,NULL,&_ThreadEntry , this) == 0);
#endif
	return ret;
	}

	void ExitThread()
	{
#ifdef WIN32
		::ExitThread(0);
#endif
	}

private:	
#ifdef WIN32
	static DWORD WINAPI _ThreadEntry(LPVOID pParam)
#else
	static void * _ThreadEntry(void *pParam)
#endif
	{
		CThread *pThread = (CThread *)pParam;
		if(pThread->InitInstance())
		{
			pThread->Run();
		}
		
		pThread->ExitInstance();
		
		//20140613 xuzh �������Ϊ0��join���־��޷�join�ˣ�������Դ�޷��ͷ�
		//pThread->m_hThread = (THREAD_HANDLE)0;
		
		return NULL;
	}

	/**�麯�����������һЩʵ��������
	* @return true:�����ɹ� false:����ʧ��
	*/
	virtual bool InitInstance()
	{
		return true;
	}
	
	/**�麯�����������ʵ��
	*/
	virtual void ExitInstance() {}
	
	/**�߳̿�ʼ���У����麯�����������̳�ʵ��
	*/
	virtual void Run() = 0;
	
private:
	 THREAD_HANDLE m_hThread;	/**< �߳̾�� */
	 DWORD m_IDThread;

};

class COrderTestThread : public CThread
{
public:

	COrderTestThread(CQdpFtdcTraderApi *pUserApi,TQdpFtdcFrontIDType frontid,TQdpFtdcSessionIDType sessionid)
		:m_pUserApi(pUserApi),m_FrontID(frontid),m_SessionID(sessionid),i(0)
	{}
	~COrderTestThread() {}

	virtual void Run()
	{
        while(true)
        {
		    SendOrder();
            SendOrderAction();
		    SLEEP(3000);
		    i++;
		    printf("order:%d \n",i);
        }
	}
protected:

	int SendOrder()
	{
		// �˵ǳɹ�,��������¼������
		CQdpFtdcInputOrderField ord;
		memset(&ord, 0, sizeof(ord));
		//���͹�˾����
		strcpy(ord.BrokerID, g_chBrokerID);
		//������
		strcpy(ord.ExchangeID,"SHFE");
		//Ͷ���ߴ���
		strcpy(ord.InvestorID , "guofu08000027");
		// �û�����
		strcpy(ord.UserID, g_chUserID);
		// ��Լ����
		strcpy(ord.InstrumentID, "rb1711");
		//���ر�����
		sprintf(ord.UserOrderLocalID,"%012d",g_UserOrderLocalID);
		//sprintf(ord.UserOrderLocalID,"%012d", 91000001);
		
		//��������
		ord.OrderPriceType = QDP_FTDC_OPT_LimitPrice;
		// ��������
		//strcpy(&(ord.Direction) , "1");
		ord.Direction = QDP_FTDC_D_Buy;
		// ��ƽ��־
		strcpy(&(ord.OffsetFlag), "0");
		// Ͷ���ױ���־
		strcpy(&(ord.HedgeFlag), "1");
		// �۸�
		ord.LimitPrice = 3074;
		// ����
		ord.Volume = 1;
		// ��Ч������
		//strcpy(&(ord.TimeCondition),"3" );
		ord.TimeCondition = QDP_FTDC_TC_GFD;
		//�ɽ�������
		ord.VolumeCondition = QDP_FTDC_VC_AV;
		//��������
		//ord = QDP_FTDC_CC_Immediately
		//ǿƽԭ��
		ord.ForceCloseReason = QDP_FTDC_FCR_NotForceClose;
		
		// �Զ������־
		ord.IsAutoSuspend = 0;
		
		int ret = m_pUserApi->ReqOrderInsert(&ord, 0);
		return ret;
	}
	
	int SendOrderAction()
	{
		// �˵ǳɹ�,��������¼������
		CQdpFtdcOrderActionField ord;
		memset(&ord, 0, sizeof(ord));
		//���͹�˾����
		strcpy(ord.BrokerID, g_chBrokerID);
		//������
		strcpy(ord.ExchangeID,"SHFE");
		//Ͷ���ߴ���
		strcpy(ord.InvestorID , "guofu08000027");
		// �û�����
		strcpy(ord.UserID, g_chUserID);
		ord.ActionFlag = '0';
		//���ر�����
		sprintf(ord.UserOrderLocalID,"%012d",g_UserOrderLocalID++);
		//sprintf(ord.UserOrderLocalID,"%012d", 91000001);
		
		ord.FrontID = m_FrontID;
		ord.SessionID = m_SessionID;
			
		int ret = m_pUserApi->ReqOrderAction(&ord, 0);
		return ret;
	}

private:
	CQdpFtdcTraderApi *m_pUserApi;

	TQdpFtdcFrontIDType m_FrontID;
	TQdpFtdcSessionIDType m_SessionID;
    int i;
};

COrderTestThread * TestThread = NULL;

/////////////////////////////////////////////////////////////

class CSimpleHandler : public CQdpFtdcTraderSpi
{
public:
	// ���캯������Ҫһ����Ч��ָ��CQdpFtdcMduserApiʵ����ָ��
	CSimpleHandler(CQdpFtdcTraderApi *pUserApi) :
	m_pUserApi (pUserApi) {}
	~CSimpleHandler () {}

	// ���ͻ�������Ͷ�Ƽ�������ͨ�����ӣ��ͻ�����Ҫ���е�¼
	virtual void OnFrontConnected()
	{
		CQdpFtdcReqUserLoginField reqUserLogin;
		printf("OnFrontConnected\n");

		strcpy(g_chBrokerID, "guofu");
		strcpy(g_chUserID, "0001");

		strcpy(reqUserLogin.BrokerID, g_chBrokerID);
		strcpy(reqUserLogin.UserID, g_chUserID);
		strcpy(reqUserLogin.Password, "111111");
		// ������½����
		m_pUserApi->ReqUserLogin(&reqUserLogin, 0);
	}


	// ���ͻ�������Ͷ�Ƽ�ͨ�����ӶϿ�ʱ���÷���������
	virtual void OnFrontDisconnected(int nReason)
	{
		// ��������������API���Զ��������ӣ��ͻ��˿ɲ�������
		printf("OnFrontDisconnected.\n");
	}


	// ���ͻ��˷�����¼����֮�󣬸÷����ᱻ���ã�֪ͨ�ͻ��˵�¼�Ƿ�ɹ�
	virtual void OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, 
								CQdpFtdcRspInfoField  *pRspInfo, 
								int nRequestID, 
								bool bIsLast)
	{
		printf("OnRspUserLogin:\n");
		printf("ErrorCode=[%d], ErrorMsg=[%s]\n",
		pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		printf("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast);
		printf("maxlocalid=[%s]\n",pRspUserLogin->MaxOrderLocalID);
		if (pRspInfo->ErrorID != 0) 
		{
			// �˵�ʧ�ܣ��ͻ�������д�����
			printf("Failed to login, errorcode=%d errormsg=%s requestid=%d chain=%d",pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast);
			exit(-1);
		}


// 		CQdpFtdcQryInstrumentField a;
// 		memset(&a,0,sizeof(CQdpFtdcQryInstrumentField));
// 		m_pUserApi->ReqQryInstrument(&a, 0);
// 		return;

		//�û���󱾵ر�����
		g_UserOrderLocalID=atoi(pRspUserLogin->MaxOrderLocalID)+1; 

		printf("maxlocalid = [%s]\n",pRspUserLogin->MaxOrderLocalID);
		printf("g_UserOrderLocalID = [%d]\n",g_UserOrderLocalID);

	//	TestThread = new COrderTestThread(m_pUserApi,pRspUserLogin->FrontID,pRspUserLogin->SessionID);
	//	TestThread->Create();
	}

	// ����¼��Ӧ��
	virtual void OnRspOrderInsert(	CQdpFtdcInputOrderField  *pInputOrder, 
									CQdpFtdcRspInfoField  *pRspInfo, 
									int nRequestID, 
									bool bIsLast)
	{
		// �������¼����
	    if(pRspInfo->ErrorID !=0)
        {
    	  printf("OnRspOrderInsert ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        }
	}

	///�����ر�
	virtual void OnRtnOrder(CQdpFtdcOrderField  *pOrder)
	{
		printf("OnRtnOrder->OrderSysID=[%s], OrderStatus=[%c]\n", pOrder->OrderSysID, pOrder->OrderStatus);
	}

	// ����û�����ĳ���֪ͨ
	virtual void OnRspError(CQdpFtdcRspInfoField  *pRspInfo, 
							int	nRequestID, 
							bool bIsLast) 
	{
		printf("OnRspError:\n");
		printf("ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		printf("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast);
		// �ͻ�������д�����
		{
			//�ͻ��˵Ĵ�����
		}
	}

	virtual void OnRspQryInstrument(CQdpFtdcRspInstrumentField *pRspInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		printf("InstrumentID: %s \n",pRspInstrument->InstrumentID);
	}

private:
	// ָ��CQdpFtdcMduserApiʵ����ָ��
	CQdpFtdcTraderApi *m_pUserApi;
};


int main()
{
	// ����һ��CQdpFtdcTraderApiʵ��
	CQdpFtdcTraderApi *pUserApi = CQdpFtdcTraderApi::CreateFtdcTraderApi();

	// ����һ���¼������ʵ��
	CSimpleHandler sh(pUserApi);

	// ע��һ�¼������ʵ��	
	pUserApi->RegisterSpi(&sh);

	// ����˽����
	// Qdp_TERT_RESTART:�ӱ������տ�ʼ�ش�
	// Qdp_TERT_RESUME:���ϴ��յ�������
	// Qdp_TERT_QUICK:ֻ���͵�¼��˽����������
	pUserApi->SubscribePrivateTopic(QDP_TERT_QUICK);

	// ���Ĺ�����
	// Qdp_TERT_RESTART:�ӱ������տ�ʼ�ش�
	// Qdp_TERT_RESUME:���ϴ��յ�������
	// Qdp_TERT_QUICK:ֻ���͵�¼�󹫹���������
	pUserApi->SubscribePublicTopic(QDP_TERT_QUICK);

	// ������Ͷ�Ƽ�����ĵ�ַ������ע������ַ����
	pUserApi->RegisterFront("tcp://192.168.92.79:30005");
	//pUserApi->RegisterFront("tcp://10.47.55.82:30015");

//	pUserApi->SetHeartbeatTimeout(240);
	// ʹ�ͻ��˿�ʼ���̨����������
	pUserApi->Init();

   // printf("the value is char:%s\n",'c');

	pUserApi->Join();
	// �ͷ�APIʵ��
	pUserApi->Release();
	return 0;
}
