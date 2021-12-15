
#include "public.h"
#include "PipeEventHandler.h"
#include "SelectReactor.h"
#include "ServiceName.h"
#include "TcpServer.h"

//产生通知的超时时间，毫秒
#define NOTIFY_TIMEOUT  1
#define WIN_FOR_PIPE_SVC "tcp://127.0.0.1:63578"

#define FlUX_GENE   40       //流控因子
#define FlUX_CTL_INTER   15  //流控时间粒度 毫秒，表示检查流控的时间间隔。

//extern void prob(int no,int maxp);

CPipeEventHandler::CPipeEventHandler(CReactor *pReactor,int nLocalPivatePort)
:CEventHandler(pReactor)
{
	m_nLocalPivatePort=nLocalPivatePort;

	//INIT_CRITICAL_VAR(m_OpCritical);
	m_pDestReactor=pReactor;
	
	m_nPreClock=m_pDestReactor->GetClock();
	m_nPerCnt=0;
	m_SendFlag=false;
	m_nWriteCnt=0;
	m_nReadCnt=0;
	
	//创建通知管道
	m_nReadPipe=0;
	m_nWritePipe=0;
	CreatePipe(m_nReadPipe,m_nWritePipe);
	
	//注册
	m_pDestReactor->RegisterIO(this);
	
	// 2013-2-5 longqy 初始化缓存区
	memset(m_buffer,0,sizeof(m_buffer));
}

CPipeEventHandler::~CPipeEventHandler()
{
	close(m_nWritePipe);
	close(m_nReadPipe);
}

void CPipeEventHandler::GetIds(int *pReadId, int *pWriteId)
{
	*pReadId = m_nReadPipe;
	*pWriteId = 0;
}

/*	从管道中读取数据。实际上只读一个字节。
//	longqy 20130910
*/
int CPipeEventHandler::HandleInput()
{
#ifdef WIN32
	int ret=::recv(m_nReadPipe,m_buffer,1,0);
#else
	int ret=::read(m_nReadPipe,m_buffer,1);
#endif

	if (ret!=1)
	{
		REPORT_EVENT(LOG_ERROR, "Pipe", "read notify error from pipe ret=%d last error=%d",ret,GET_LAST_SOCK_ERROR());
		perror("READ::");
		return 0;
	}
	m_nReadCnt++;
	
	return 0;
}

/*	获取系统的当前时间，以毫秒为单位。从 1970-1-1 0:0:0 开始到现在的时间的毫秒数。
//	longqy 20130910
*/
DWORD CPipeEventHandler::GettMilSec()
{
#ifdef WIN32	
   struct _timeb timebuffer;
   _ftime( &timebuffer );
	 return (DWORD)timebuffer.time*1000 + timebuffer.millitm;
#else
	struct timeval timeout;
  gettimeofday(&timeout, 0);
	return timeout.tv_sec*1000 + timeout.tv_usec/1000;
#endif
}

/*	检查流控的时间间隔是 FlUX_CTL_INTER 毫秒。如果在时间间隔内，触发次数过多，则关闭发送开关。
//	每次流控检查，触发次数的计数都重新清零。
//	1、只有在发送开关打开的时候才发送通知 2、只有上次发送的通知已经被读取，才发送通知
//	longqy 20130910
*/
void CPipeEventHandler::Notify()
{	
	m_pDestReactor->SetSpeciaFlag(true);
	
	//流控策略1:应对高速时情况，根据触发次数确定是否打开发送开关
	//每个流控周期的计数
	m_nPerCnt++;
	int inter=m_pDestReactor->GetClock()-m_nPreClock;
	if (inter > FlUX_CTL_INTER)
	{		
		m_nPreClock=m_pDestReactor->GetClock();	
		//如果每毫秒超过10笔，则不发送通知
		if (m_nPerCnt > inter * FlUX_GENE)
		{
			//关闭通知发送
			m_SendFlag=false;		
			m_nPerCnt=0;
			return;
		}
		else
		{
			//打开通知发送
			m_SendFlag=true;		
			m_nPerCnt=0;
		}
	}
	//如果不超过流控阀值，维持原来状态	
	if (!m_SendFlag)
	{
		return;
	}
	
	//流控策略2:应对中低速情况，如果有尚未处理的通知信号，则不再发送信号
	if (m_nWriteCnt>m_nReadCnt)
		return;
	
#ifdef WIN32
	int ret=::send(m_nWritePipe,m_buffer,1,0);
#else
	int ret=::write(m_nWritePipe,m_buffer,1);
#endif
	if (ret!=1)
	{
		REPORT_EVENT(LOG_ERROR, "Pipe", "write notify error to pipe ret=%d last error=%d",ret,GET_LAST_SOCK_ERROR());
		perror("write::");
		return;
	}
	m_nWriteCnt++;
	return ;
}

/*	创建管道。参数 p0 为读管道文件符， p1 为写管道文件符。
//	longqy 20130910
*/
void CPipeEventHandler::CreatePipe(int &p0, int &p1)
{
#ifndef WIN32
	//创建通知管道
	int pipefd[2];
	if (pipe(pipefd)<0)
	{
		RAISE_RUNTIME_ERROR("Can not create pipe");
	}
	p0=pipefd[0];
	p1=pipefd[1];
	m_nReadPipe=pipefd[0];
	m_nWritePipe=pipefd[1];
	
	//修改管道属性
	int on=1;
	for(;;)
	{
		if (fcntl(m_nReadPipe, F_SETFL,  O_NONBLOCK) < 0)
		//if (ioctlsocket(m_nReadPipe, FIONBIO, (char *)&on) < 0)
		{
			//if (GET_LAST_SOCK_ERROR() == -1)
			//if (GET_LAST_SOCK_ERROR() == EINTR)
			//	continue;
			RAISE_RUNTIME_ERROR("Can not set FIONBIO\n");
		}
		else
			break;
	}
	on=1;
	for(;;)
	{
		if (fcntl(m_nWritePipe, F_SETFL,  O_NONBLOCK) < 0)
		//if (ioctlsocket(m_nWritePipe, FIONBIO, (char *)&on) < 0)
		{
			//if (GET_LAST_SOCK_ERROR() == -1)
			//if (GET_LAST_SOCK_ERROR() == EINTR)
			//	continue;
			RAISE_RUNTIME_ERROR("Can not set FIONBIO\n");
		}
		else
			break;
	}
	p0=pipefd[0];
	p1=pipefd[1];
	return;
#else
	//初始化
	p0=0;
	p1=0;

	//unsigned long tmpvar;
	//void *pThis=this;
	//memcpy(&tmpvar,pThis,sizeof(pThis));
	//tmpvar>>8;
	//printf("tmpvar=[%08x]\n",tmpvar);
	//int port=40000+tmpvar%10000;
	//static int port=4000;
	//port++;

	
	m_nLocalPivatePort=m_nLocalPivatePort+(getpid()%50);

	char *pSvc=new char[100];
	sprintf(pSvc,"tcp://127.0.0.1:%d",m_nLocalPivatePort);

	printf("pSvc=%s getpid=%d\n",pSvc,getpid());

	CServiceName svc(pSvc);
	CTcpServer TmpServer(&svc);		
	struct sockaddr_in dest;
	char *hostname;
	
	int ClntId=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClntId<0)
	{
		RAISE_DESIGN_ERROR("Can not create socket for Pipe");
	}
	

	int on=1;
	setsockopt(ClntId, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
	for (;;)
	{	
		unsigned long on_windows=1;
		if (ioctlsocket(ClntId, FIONBIO, &on_windows) < 0)
		{
			if (GET_LAST_SOCK_ERROR() == EINTR)
				continue;
			RAISE_RUNTIME_ERROR("Can not set FIONBIO\n");
		}
		else
			break;
	}

	dest.sin_family = AF_INET;
	dest.sin_port = htons(svc.GetPort());
	hostname = "127.0.0.1";
	dest.sin_addr.s_addr=inet_addr(hostname); 
	int ret=::connect(ClntId,(struct sockaddr  *)&dest,sizeof(dest));
	if (ret==0)
	{
		//已经创建管道一端
		p1=ClntId;
	}
	
	//适当等待
	Sleep(100);

	int newId;
	struct sockaddr_in it;
	SOCKADDRLEN nameLen=sizeof(it);
	newId = ::accept(TmpServer.GetId(), (struct sockaddr *)&it, &nameLen);
	if (newId < 0)
	{
		RAISE_DESIGN_ERROR("create pipe_server failed!!");
	}
	else
		p0=newId;
	
	//检查客户端是否创建成功
	if (p1>0)
		return;

	//检查是否创建完成
	fd_set writefds;
	FD_ZERO(&writefds);
	FD_SET(ClntId,&writefds);
	struct timeval timeout;
	timeout.tv_sec=5;
	timeout.tv_usec=0;
	ret=select(ClntId+1,NULL,&writefds,NULL,&timeout);
	if (ret==0)
	{
		RAISE_DESIGN_ERROR("create pipe_client failed!!");
		return;
	}

	struct sockaddr name;
	if ((ret>0)&&FD_ISSET(ClntId,&writefds))
	{
		SOCKADDRLEN nameLen=sizeof(name);
		if (getpeername(ClntId,&name,&nameLen)==0)
		{
			p1=ClntId;
			return;
		}
	}

	closesocket(ClntId);
	RAISE_DESIGN_ERROR("create Pipe_client failed!!");
#endif
}
