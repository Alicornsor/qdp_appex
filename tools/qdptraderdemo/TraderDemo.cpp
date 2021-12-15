// 一个简单的例子，介绍CQdpFtdcTraderApi和CQdpFtdcTraderSpi接口的使用。
// 本例将演示一个报单录入操作的过程
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
// 报单录入操作是否完成的标志
// 经纪公司代码
TQdpFtdcBrokerIDType g_chBrokerID;
// 交易用户代码
TQdpFtdcUserIDType g_chUserID;
//用户本地最大报单号
int g_UserOrderLocalID;


class  CThread  
{
public:
	/**构造函数
	*/
	CThread() 
	{
		m_hThread = (THREAD_HANDLE)0;
		m_IDThread = 0;
	}
	
	/**析构函数
	*/
	virtual ~CThread() {}
	
	/**创建一个线程
	* @return true:创建成功 false:创建失败
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
		
		//20140613 xuzh 如果设置为0，join部分就无法join了，导致资源无法释放
		//pThread->m_hThread = (THREAD_HANDLE)0;
		
		return NULL;
	}

	/**虚函数，子类可做一些实例化工作
	* @return true:创建成功 false:创建失败
	*/
	virtual bool InitInstance()
	{
		return true;
	}
	
	/**虚函数，子类清楚实例
	*/
	virtual void ExitInstance() {}
	
	/**线程开始运行，纯虚函数，子类必须继承实现
	*/
	virtual void Run() = 0;
	
private:
	 THREAD_HANDLE m_hThread;	/**< 线程句柄 */
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
		// 端登成功,发出报单录入请求
		CQdpFtdcInputOrderField ord;
		memset(&ord, 0, sizeof(ord));
		//经纪公司代码
		strcpy(ord.BrokerID, g_chBrokerID);
		//交易所
		strcpy(ord.ExchangeID,"SHFE");
		//投资者代码
		strcpy(ord.InvestorID , "guofu08000027");
		// 用户代码
		strcpy(ord.UserID, g_chUserID);
		// 合约代码
		strcpy(ord.InstrumentID, "rb1711");
		//本地报单号
		sprintf(ord.UserOrderLocalID,"%012d",g_UserOrderLocalID);
		//sprintf(ord.UserOrderLocalID,"%012d", 91000001);
		
		//报单类型
		ord.OrderPriceType = QDP_FTDC_OPT_LimitPrice;
		// 买卖方向
		//strcpy(&(ord.Direction) , "1");
		ord.Direction = QDP_FTDC_D_Buy;
		// 开平标志
		strcpy(&(ord.OffsetFlag), "0");
		// 投机套保标志
		strcpy(&(ord.HedgeFlag), "1");
		// 价格
		ord.LimitPrice = 3074;
		// 数量
		ord.Volume = 1;
		// 有效期类型
		//strcpy(&(ord.TimeCondition),"3" );
		ord.TimeCondition = QDP_FTDC_TC_GFD;
		//成交量类型
		ord.VolumeCondition = QDP_FTDC_VC_AV;
		//触发条件
		//ord = QDP_FTDC_CC_Immediately
		//强平原因
		ord.ForceCloseReason = QDP_FTDC_FCR_NotForceClose;
		
		// 自动挂起标志
		ord.IsAutoSuspend = 0;
		
		int ret = m_pUserApi->ReqOrderInsert(&ord, 0);
		return ret;
	}
	
	int SendOrderAction()
	{
		// 端登成功,发出报单录入请求
		CQdpFtdcOrderActionField ord;
		memset(&ord, 0, sizeof(ord));
		//经纪公司代码
		strcpy(ord.BrokerID, g_chBrokerID);
		//交易所
		strcpy(ord.ExchangeID,"SHFE");
		//投资者代码
		strcpy(ord.InvestorID , "guofu08000027");
		// 用户代码
		strcpy(ord.UserID, g_chUserID);
		ord.ActionFlag = '0';
		//本地报单号
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
	// 构造函数，需要一个有效的指向CQdpFtdcMduserApi实例的指针
	CSimpleHandler(CQdpFtdcTraderApi *pUserApi) :
	m_pUserApi (pUserApi) {}
	~CSimpleHandler () {}

	// 当客户端与量投科技建立起通信连接，客户端需要进行登录
	virtual void OnFrontConnected()
	{
		CQdpFtdcReqUserLoginField reqUserLogin;
		printf("OnFrontConnected\n");

		strcpy(g_chBrokerID, "guofu");
		strcpy(g_chUserID, "0001");

		strcpy(reqUserLogin.BrokerID, g_chBrokerID);
		strcpy(reqUserLogin.UserID, g_chUserID);
		strcpy(reqUserLogin.Password, "111111");
		// 发出登陆请求
		m_pUserApi->ReqUserLogin(&reqUserLogin, 0);
	}


	// 当客户端与量投科技通信连接断开时，该方法被调用
	virtual void OnFrontDisconnected(int nReason)
	{
		// 当发生这个情况后，API会自动重新连接，客户端可不做处理
		printf("OnFrontDisconnected.\n");
	}


	// 当客户端发出登录请求之后，该方法会被调用，通知客户端登录是否成功
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
			// 端登失败，客户端需进行错误处理
			printf("Failed to login, errorcode=%d errormsg=%s requestid=%d chain=%d",pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast);
			exit(-1);
		}


// 		CQdpFtdcQryInstrumentField a;
// 		memset(&a,0,sizeof(CQdpFtdcQryInstrumentField));
// 		m_pUserApi->ReqQryInstrument(&a, 0);
// 		return;

		//用户最大本地报单号
		g_UserOrderLocalID=atoi(pRspUserLogin->MaxOrderLocalID)+1; 

		printf("maxlocalid = [%s]\n",pRspUserLogin->MaxOrderLocalID);
		printf("g_UserOrderLocalID = [%d]\n",g_UserOrderLocalID);

	//	TestThread = new COrderTestThread(m_pUserApi,pRspUserLogin->FrontID,pRspUserLogin->SessionID);
	//	TestThread->Create();
	}

	// 报单录入应答
	virtual void OnRspOrderInsert(	CQdpFtdcInputOrderField  *pInputOrder, 
									CQdpFtdcRspInfoField  *pRspInfo, 
									int nRequestID, 
									bool bIsLast)
	{
		// 输出报单录入结果
	    if(pRspInfo->ErrorID !=0)
        {
    	  printf("OnRspOrderInsert ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        }
	}

	///报单回报
	virtual void OnRtnOrder(CQdpFtdcOrderField  *pOrder)
	{
		printf("OnRtnOrder->OrderSysID=[%s], OrderStatus=[%c]\n", pOrder->OrderSysID, pOrder->OrderStatus);
	}

	// 针对用户请求的出错通知
	virtual void OnRspError(CQdpFtdcRspInfoField  *pRspInfo, 
							int	nRequestID, 
							bool bIsLast) 
	{
		printf("OnRspError:\n");
		printf("ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
		printf("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast);
		// 客户端需进行错误处理
		{
			//客户端的错误处理
		}
	}

	virtual void OnRspQryInstrument(CQdpFtdcRspInstrumentField *pRspInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
	{
		printf("InstrumentID: %s \n",pRspInstrument->InstrumentID);
	}

private:
	// 指向CQdpFtdcMduserApi实例的指针
	CQdpFtdcTraderApi *m_pUserApi;
};


int main()
{
	// 产生一个CQdpFtdcTraderApi实例
	CQdpFtdcTraderApi *pUserApi = CQdpFtdcTraderApi::CreateFtdcTraderApi();

	// 产生一个事件处理的实例
	CSimpleHandler sh(pUserApi);

	// 注册一事件处理的实例	
	pUserApi->RegisterSpi(&sh);

	// 订阅私有流
	// Qdp_TERT_RESTART:从本交易日开始重传
	// Qdp_TERT_RESUME:从上次收到的续传
	// Qdp_TERT_QUICK:只传送登录后私有流的内容
	pUserApi->SubscribePrivateTopic(QDP_TERT_QUICK);

	// 订阅公共流
	// Qdp_TERT_RESTART:从本交易日开始重传
	// Qdp_TERT_RESUME:从上次收到的续传
	// Qdp_TERT_QUICK:只传送登录后公共流的内容
	pUserApi->SubscribePublicTopic(QDP_TERT_QUICK);

	// 设置量投科技服务的地址，可以注册多个地址备用
	pUserApi->RegisterFront("tcp://192.168.92.79:30005");
	//pUserApi->RegisterFront("tcp://10.47.55.82:30015");

//	pUserApi->SetHeartbeatTimeout(240);
	// 使客户端开始与后台服务建立连接
	pUserApi->Init();

   // printf("the value is char:%s\n",'c');

	pUserApi->Join();
	// 释放API实例
	pUserApi->Release();
	return 0;
}
