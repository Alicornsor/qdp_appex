// PublicFuncs.cpp: implementation of the PublicFuncs class.
//
//////////////////////////////////////////////////////////////////////

#include "PublicFuncs.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PublicFuncs::PublicFuncs()
{

}

PublicFuncs::~PublicFuncs()
{

}

typedef struct 
{
	int nordspeed;
	int nordloop;
} stordspeed;

/*---------------全局变量区---------------*/

const char* TEST_API_INI_NAME="testapi.ini";
char g_pFlowPath[BUFLEN];
char* g_pProductInfo="压力测试工具V1.0";
char* g_pProgramName="TestApi";

extern int g_nSwitch;
extern FILE * g_fpSend;

//1.登录信息
///交易用户代码
TQdpFtdcBrokerIDType	g_BrokerID;
TQdpFtdcUserIDType	g_UserID;
///密码
TQdpFtdcPasswordType	g_Password;

//2.地址信息
char g_frontaddr[BUFLEN];

//3.报单信息
int g_nOrdLocalID=0;
vector<CQdpFtdcInputOrderField*>* g_pOrd=NULL;
CQdpFtdcUserApi * g_puserapi=NULL;
bool g_bOrdCycle=true;//循环下单
int g_nSleepInterval=0;//报单间隔

int g_nOrdSpeed=0;//每秒钟下多少单
int g_nMode = 1;
vector<stordspeed*>* g_vOrdSpeed=NULL;
int g_nAutoOrdsize=0;
int g_nAutoLoopTime=0;
#ifdef WIN32
	map<DWORD,_timeb*>* g_mpOrdSndTm=NULL;
#else
	map<DWORD,timeval*>* g_mpOrdSndTm=NULL;
#endif
map<DWORD,int>* g_mpOrdLoopTm = NULL;
FILE* g_fpRspTm=NULL;
CMutex g_mux;

/*---------------全局函数区---------------*/

bool transstr2order(char* porder,CQdpFtdcInputOrderField& ord)
{
	if (porder==NULL)
	{
		return false;
	}
	memset(&ord,0,sizeof(CQdpFtdcInputOrderField));

	char seps[]   = " ,\n";
	char *token;
	token = strtok( porder, seps ); 
	if (token==NULL)
	{
		return false;
	}
	strcpy(ord.BrokerID,token);
	int index=0;

	while( token != NULL )
	{
		index++;
		token = strtok( NULL, seps );		
		if (token==NULL||!strcmp(token,"null"))
		{
			continue;
		}
		switch (index)
		{
		case 1:
			strcpy(ord.InvestorID,token);
			break;
		case 2:
			strcpy(ord.InstrumentID,token);
			break;
		case 3:
			ord.Direction=token[0];
			break;
		case 4:
			ord.OffsetFlag=token[0];
			break;
		case 5:
			//strcpy(ord.HedgeFlag,token);
			ord.HedgeFlag=token[0];
			break;
		case 6:
			ord.OrderPriceType=token[0];
			break;
		case 7:
		{
			switch(g_nSwitch)
			{
				case 1://NAN
				{
					double d1 = 0.0;
					double d2 = 0.0;
					ord.LimitPrice=d1/d2;
					break;
				}
				case 2://INF
				{
					double d1 = 1.0;
					double d2 = 0.0;
					ord.LimitPrice=d1/d2;
					break;
				}
				case 3://3500.5999999999999999
				{
					//ord.LimitPrice=3500.5999999999999999;
					ord.LimitPrice=2300;
					break;
				}
				default:
					ord.LimitPrice=atof(token);
					break;
			}
			break;
		}
		case 8:
			ord.Volume=atoi(token);
			break;
		case 9:
			ord.TimeCondition=token[0];
			break;
		case 10:
// 			strcpy(ord.GTDDate,token);
			break;
		case 11:
			ord.VolumeCondition=token[0];
			break;
		case 12:
// 			ord.MinVolume=atoi(token);
			break;
		case 13:
			//ord.ContingentCondition=token[0];
			break;
		case 14:
			ord.StopPrice=atof(token);
			break;
		case 15:
			//ord.IsAutoSuspend=atoi(token);
			break;
		case 16:
			strcpy(ord.ExchangeID,token);
			break;
		case 17:
		//	strcpy(ord.SeatID,token);
			break;
		case 18:
			strcpy(ord.BusinessUnit,token);
			break;
		}
	}
	ord.ForceCloseReason='0';
//	ord.IsAutoSuspend=0;
//	ord.ContingentCondition=FFEX_FTDC_CC_Immediately;
//	ord.MinVolume=0;

	strcpy(ord.UserID,g_UserID);

	return true;
}

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
/*读配置文件*/
bool readconfig()
{
	//init
	memset(g_UserID,0,sizeof(TQdpFtdcUserIDType));
	memset(g_BrokerID,0,sizeof(TQdpFtdcBrokerIDType));
	memset(g_Password,0,sizeof(TQdpFtdcPasswordType));
	memset(g_frontaddr,0,BUFLEN);

	//read config
	CConfig * pconfig = new CConfig(TEST_API_INI_NAME);
	g_pConfig = pconfig;
	char* puserid=pconfig->getConfig("UserID");
	if (puserid==NULL)
	{
		return false;
	}
	strcpy(g_UserID,puserid);

	char* pbrokerid=pconfig->getConfig("BrokerID");
	if (pbrokerid==NULL)
	{
		return false;
	}
	strcpy(g_BrokerID,pbrokerid);

	char* pPasswd=pconfig->getConfig("PassWd");
	if (pPasswd==NULL)
	{
		return false;
	}
	strcpy(g_Password,pPasswd);

	char* pFrontAddr=pconfig->getConfig("FrontAddr");
	if (pFrontAddr==NULL)
	{
		return false;
	}
	strcpy(g_frontaddr,pFrontAddr);

	char* pFlowPath=pconfig->getConfig("FlowPath");
	if (pFlowPath==NULL)
	{
		return false;
	}
	strcpy(g_pFlowPath,pFlowPath);

	char *syslogFileName=pconfig->getConfig("SyslogPath");
	CMonitorIndex::init(CFilelogService::CreateInstance(1,&g_pProgramName,syslogFileName),pconfig);

	//报单信息
	char *pOrdCsv=pconfig->getConfig("OrderCsv");

	FILE* fpOrd=mfopen(pOrdCsv,"r");
	
	if (fpOrd==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"EnvError","can not open config file %s",pOrdCsv);
		return false;
	}
	char buffer[BUFLEN];
	int row =  0;
	if (g_pOrd==NULL)
	{
		g_pOrd = new vector<CQdpFtdcInputOrderField*>();
	}	

	while (fgets(buffer,BUFLEN,fpOrd)!=NULL)
	{
		if (row++==0)
		{
			continue;
		}
		CQdpFtdcInputOrderField* pord=new CQdpFtdcInputOrderField();
		bool btrans=transstr2order(buffer,*pord);
		if (!btrans)
		{
			REPORT_EVENT(LOG_CRITICAL,"config err","order file error:%s",pOrdCsv);
			return false;
		}
		g_pOrd->push_back(pord);
	}
	fclose(fpOrd);

	char * pordcycle=pconfig->getConfig("OrderCycle");
	if (strcmp(pordcycle,"yes"))
	{
		g_bOrdCycle=false;
	}

	char * psleepinterval=pconfig->getConfig("SleepInterval");
	if (psleepinterval==NULL)
	{
		return false;
	}
	g_nSleepInterval=atoi(psleepinterval);

	char * porderspeed=pconfig->getConfig("OrderSpeed");
	if (porderspeed==NULL)
	{
		return false;
	}
	g_nOrdSpeed=atoi(porderspeed);

	if (g_nOrdSpeed<=0)
	{
		REPORT_EVENT(LOG_CRITICAL,"config err","order speed err:%d",g_nOrdSpeed);
		return false;
	}

	char * pordmode = pconfig->getConfig("Mode");
	if (pordmode==NULL)
	{
		return false;
	}
	g_nMode=atoi(pordmode);
	if(g_nMode!=1&&g_nMode!=2)
	{
		REPORT_EVENT(LOG_CRITICAL,"config err","invalide order mode err:%d",g_nMode);
		return false;
	}

	//auto mode
	if(g_nMode == 2)
	{
	char * pautoloop=pconfig->getConfig("AutoLoopTimes");
	if(pautoloop==NULL)
	{
		return false;
	}
	g_nAutoLoopTime = atoi(pautoloop);
	if(g_nAutoLoopTime<=-2)
	{
		REPORT_EVENT(LOG_CRITICAL,"config err","invalide AutoLoopTimes");
		return false;
	}

	char * pautospeed=pconfig->getConfig("AutoSpeed");
	if (pautospeed==NULL)
	{
		return false;
	}
	if(g_vOrdSpeed==NULL)
	{
		g_vOrdSpeed = new vector<stordspeed*>();
	}
	vector<std::string> vect;
	splitstr(pautospeed,";",vect);

	vector<std::string>::iterator it=vect.begin();
	for(;it!=vect.end();it++)
	{
		vector<std::string> vectmp;
		splitstr(it->data(),",",vectmp);
		if(vectmp.size()!=2)
		{
			REPORT_EVENT(LOG_CRITICAL,"config err","invalide autospeed");
			return false;
		}
		int nordspeed=atoi(vectmp[0].data());
		int nordloop=atoi(vectmp[1].data());

		if(nordspeed<=0||nordloop<=0)
		{
			REPORT_EVENT(LOG_CRITICAL,"config err","invalide autospeed");
			return false;
		}
		stordspeed * pos = new stordspeed();
		pos->nordspeed=nordspeed;
		pos->nordloop=nordloop;
		g_vOrdSpeed->push_back(pos);
		g_nAutoOrdsize+=nordloop*nordspeed;
	}

	}

	return true;
}

int getspeed(int sendsize)
{
	if(g_nAutoLoopTime!=-1&&((sendsize/g_nAutoOrdsize)>=g_nAutoLoopTime))
	{
		return g_nOrdSpeed;
	}
	int nsize = sendsize % g_nAutoOrdsize;
	for(vector<stordspeed*>::iterator it=g_vOrdSpeed->begin();it!=g_vOrdSpeed->end();it++)
	{
		int speed=(*it)->nordspeed;
		nsize -= ((*it)->nordloop)*((*it)->nordspeed);
		if(nsize <0)
			return speed;
	}
	return 0;
}

#ifdef WIN32
DWORD WINAPI OrderFunc(LPVOID pParam)
#else
void * OrderFunc(void *pParam)
#endif
{
	if (g_pOrd->empty())
	{
		REPORT_EVENT(LOG_CRITICAL,"OrderFunc","无有效订单");
		return NULL; 
	}
	if (g_puserapi==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"OrderFunc"," USERAPI未创建");
		return NULL;
	}
	if(g_mpOrdSndTm==NULL)
	{
#ifdef WIN32
		g_mpOrdSndTm=new map<DWORD,_timeb*>();
#else
		g_mpOrdSndTm=new map<DWORD,timeval*>();
#endif
	}

	int nsnd = 0;
	time_t ttLast = 0;
	long lLastMicroSec = 0;

	int nOrdIndx = 0;
	int nOrdSize = g_pOrd->size();
	int nSndOrdPerSec=0;
	int nSndSize=0;
	
	//上一次sleep的时间
#ifdef WIN32
   struct _timeb tvLast;
   _ftime( &tvLast );
//         return (DWORD)timebuffer.time*1000 + timebuffer.millitm;
#else
        struct timeval tvLast;
		gettimeofday(&tvLast, 0);
//        return tvLast.tv_sec*1000 + tvLast.tv_usec/1000;
#endif
	
	//修改20110407，不再每一笔都匀速发单，而采用将1s分割成10块，每一块内匀速发单的状态
	//反弹速度/10=100ms内应该发完的订单，发完后检查100ms还剩多少时间,sleep
	
	int nsleep = 1000000/(g_nOrdSpeed);		
	int i=0;
	while (1)
	{

			
		CQdpFtdcInputOrderField* pord=g_pOrd->at(nOrdIndx);
		sprintf(pord->UserOrderLocalID,"%08d",g_nOrdLocalID);
		
		#ifdef PERFORM_TEST
					long ltm;
					GET_ACCURATE_USEC_TIME(ltm);
					printf("sedorder,%ld,",ltm);	
		#endif
		int nreq=g_puserapi->ReqOrderInsert(pord,g_nOrdLocalID);
		while (nreq!=0)
		{
			REPORT_EVENT(LOG_CRITICAL,"sleep 1s:","retcode:%d",nreq);
			SLEEP(1000);
			nreq=g_puserapi->ReqOrderInsert(pord,g_nOrdLocalID);
		}
		//printf("ReqOrderInsert SECCUSS \n");
		//写入发单时间
//		timeval *tv=new timeval();
//		gettimeofday(tv,NULL);
#ifdef WIN32
   struct _timeb tv ;
   _ftime( &tv );
//         return (DWORD)timebuffer.time*1000 + timebuffer.millitm;
#else
        struct timeval tv;
		gettimeofday(&tv, 0);
//        return tvLast.tv_sec*1000 + tvLast.tv_usec/1000;
#endif


		g_mux.Lock();
#ifdef WIN32
		g_mpOrdSndTm->insert(pair<DWORD,_timeb*>(g_nOrdLocalID,&tv));
#else
		g_mpOrdSndTm->insert(pair<DWORD,timeval*>(g_nOrdLocalID,&tv));
#endif
		g_mux.UnLock();
		
		if (!g_bOrdCycle&&(nOrdIndx==nOrdSize-1))
		{
			break;
		}

		nOrdIndx=++nOrdIndx%nOrdSize;
		g_nOrdLocalID++;

		//计算出每秒报送了多少订单，写日志
		nSndSize++;

		if(g_nMode==2)//auto mode
		{
			int nspeed = getspeed(nSndSize);
			if(nspeed!=g_nOrdSpeed)
			{
				REPORT_EVENT(LOG_CRITICAL,"testapi:","changespeed to %d",nspeed);
				g_nOrdSpeed=nspeed;
			}
		}
#ifdef WIN32
        ::Sleep(nsleep/1000);
#else
        ::usleep(nsleep);
#endif
		i++;
	}

	return 0;
}

void * ChangeSpeedFunc(void *pParam)
{
	CConfig * pconfig = g_pConfig;
	if(pconfig==NULL)
		REPORT_EVENT(LOG_CRITICAL,"testapi","Change Order Speed Fail, Reason : cannot get config");

	char * psleepinterval=pconfig->getConfig("ChangeSpeedSleepInterval");
	if (psleepinterval==NULL)
	{
		REPORT_EVENT(LOG_CRITICAL,"testapi","Change Order Speed Fail, Reason : cannot get sleepinterval config");
		return NULL;
	}
	int scaninterval=atoi(psleepinterval);

	if(scaninterval<=0)
		REPORT_EVENT(LOG_CRITICAL,"changespeed fail","Reason:sleep interval invalid");

	while(1)
	{
		pconfig = new CConfig(TEST_API_INI_NAME);
		if(pconfig==NULL)
		{
			REPORT_EVENT(LOG_CRITICAL,"testapi","Change Order Speed Fail, Reason : cannot get config");
			break;
		}
		char * pordspeed=pconfig->getConfig("OrderSpeed");
		if (pordspeed==NULL)
		{
			REPORT_EVENT(LOG_CRITICAL,"testapi","Change Order Speed Fail, Reason : cannot get orderspeed config");
			break;
		}
		int nspeed = atoi(pordspeed);
		if(nspeed<=0)
			REPORT_EVENT(LOG_CRITICAL,"changespeed fail","Reason:speed invalid");
		g_nOrdSpeed=nspeed;
		SLEEP(scaninterval*1000);
		delete pconfig;
	}
	return NULL;
}

bool StartAutoOrder()
{	
	DWORD dwIDThread;
	THREAD_HANDLE hThread;	/**< 线程句柄 */
	bool ret = true;
#ifdef WIN32
	hThread = ::CreateThread(NULL,0,OrderFunc,NULL,0,&dwIDThread);
	if(hThread==NULL)
	{
		ret = false;
	}
	SetThreadPriority(hThread,THREAD_PRIORITY_TIME_CRITICAL);
	ResumeThread(hThread);
#else
	ret = (::pthread_create(&hThread,NULL,&OrderFunc , NULL) == 0);
	if(g_nMode == 1)
	{
		ret = (::pthread_create(&hThread,NULL,&ChangeSpeedFunc , NULL) == 0);
	}
#endif
	return ret;
}
