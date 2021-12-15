/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file BaseEngine.cpp
///@brief	ʵ������CBaseEngine
///@history 
///20060118	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#include "BaseEngine.h"

#ifndef WIN32
#include <fcntl.h>
#include <sys/mman.h>
#endif

/////////////////////////////////////////////////////////////////////////
CBaseEngine::CBaseEngine(CConfig *pConfig, bool verbose)
{
	m_pProcess=NULL;//by wangwei
	m_verbose=verbose;
	m_pConfig=pConfig;
	currentConfig=pConfig;

	///��ʼ�����м���
	runLevel = atoi(pConfig->getConfig("RunLevel"));

	//��ʼ���ڴ����ݿ�
	if (m_verbose)
	{
		PROCESS_LOG0("init memory database\n");
	}
	m_pDB=new CMemoryDB;
	m_pDB->init(pConfig);

	//���ü��ָ��
//	new CIntPtrMonitorIndex("OrderSize",m_pDB->m_OrderFactory->getCountPtr(),1);
//	new CIntPtrMonitorIndex("TradeSize",m_pDB->m_TradeFactory->getCountPtr(),1);
//	new CIntPtrMonitorIndex("ClientSize",m_pDB->m_ClientFactory->getCountPtr(),60);
//	new CIntPtrMonitorIndex("PartClientSize",m_pDB->m_PartClientFactory->getCountPtr(),60);
//	new CIntPtrMonitorIndex("ClientPositionSize",m_pDB->m_ClientPositionFactory->getCountPtr(),10);
//	new CIntPtrMonitorIndex("UserSessionSize",m_pDB->m_UserSessionFactory->getCountPtr(),10);
	///-------
	//	xuzh��20061115���޸��˷���HandleInput��Ƶ�ʣ����ֺ�����������Ƶ����ͬ���Ա���ϵͳ�Ĵ���
	///-------
//	m_handleInputIndex=new CIntTotalMonitorIndex("HandleInput",20);
	
	//������������
	if (m_verbose)
	{
		PROCESS_LOG0("create error engine\n");
	}
	m_pErrorEngine=new CErrorEngine;
	defineErrors(m_pErrorEngine);
		
	//���������־ 
	if (m_verbose)
	{
		PROCESS_LOG0("start memory database log\n");
	}
	m_pDumpLog=new CDumpLog(m_pDB,pConfig);
	m_pDumpLog->start();

	//******//
	//	xuzh��20060929����process�ļ���λ�ø��������ļ�����
	//******//
	//�򿪴����ļ�
//	char *processFileName=m_pConfig->getConfig("ProcessPath");
//	if (processFileName[0]=='\0')
//	{
//		//û�ж��������ļ����ǾͲ���ʹ�ûָ���ʽ������
//		m_recovery=false;
//		m_processFile=NULL;
//		m_pProcess=NULL;
//		m_nextIgnoreID=0;
//	}
//	else
//	{
//		if (!m_recovery)
//		{
//			//�ǻָ�ģʽ���Ǿ�ֻҪ��¼����Ϳ�����
//			m_pProcess=initMmap(true,processFileName);
//			//m_processFile=mfopen(processFileName,"w+t");
//			if (m_pProcess==NULL)
//			{
//				RAISE_RUNTIME_ERROR("can not open process file for write");
//			}
//			m_CurrPos=0;
//			m_nextIgnoreID=0;
//		  printf("!!Normal m_nextIgnoreID=[%ld] m_CurrPos=%d\n",m_nextIgnoreID,m_CurrPos);fflush(stdout);
//		}
//		else
//		{
//			//�ָ�ģʽ���Ǿ���ҪѰ��ԭ���Ĵ����ļ�����Ϊ���Ե�����
//			//m_processFile=mfopen(processFileName,"r+t");
//			m_pProcess=initMmap(false,processFileName);
//			if (m_pProcess==NULL)
//			{
//				RAISE_RUNTIME_ERROR("can not find process file while recovery");
//			}
//			//feek(m_processFile,0,SEEK_SET);
//			m_CurrPos=0;
//			m_nextIgnoreID=getNextID();
//			printf("!!RESTore ::m_nextIgnoreID=[%ld] m_CurrPos=%d\n",m_nextIgnoreID,m_CurrPos);fflush(stdout);
//		}	
//
//	}
}
	
CBaseEngine::~CBaseEngine(void)
{
	if (m_processFile!=NULL)
	{
		fclose(m_processFile);
	}

	//���������־ 
	if (m_verbose)
	{
		PROCESS_LOG0("stop memory database log\n");
	}
	m_pDumpLog->stop();
	delete m_pDumpLog;
		
	//������������
	if (m_verbose)
	{
		PROCESS_LOG0("close error engine\n");
	}
	delete m_pErrorEngine;

	//����ڴ����ݿ�
	if (m_verbose)
	{
		PROCESS_LOG0("dump memory database\n");
	}
	m_pDB->save(m_pConfig);
		
	//�����ڴ����ݿ�
	if (m_verbose)
	{
		PROCESS_LOG0("destroy memory database\n");
	}
	delete m_pDB;
}
	
bool CBaseEngine::startProcess(int seqID)
{
	///����Ҫ������
	setNextID(seqID);
	return true;
}
	
bool CBaseEngine::endProcess(int seqID)
{
	return true;
}

int CBaseEngine::getNextID(void)
{
	//******//
	//	xuzh��20060929����process�ļ���λ�ø��������ļ�����
	//******//
	if (m_pProcess==NULL)
	{
		return 0;
	}
	
	char  buffer[11];
printf("getNextID m_pProcess=%p m_CurrPos=%d\n",m_pProcess,m_CurrPos);fflush(stdout);
	memcpy(buffer,m_pProcess+m_CurrPos,10);
	m_CurrPos=m_CurrPos+11;
	buffer[10]='\0';
	return atoi(buffer);
	/*
	long pos=ftell(m_processFile);
	char buffer[9];
	if (fread(buffer,1,8,m_processFile)!=8)
	{
		///û�ж���ɹ���ָ��ص�ԭλ
		fseek(m_processFile,pos,SEEK_SET);
		return 0;
	}
	buffer[8]='\0';
	return atoi(buffer);
	*/
}

void CBaseEngine::setNextID(int nextID)
{
	
	if (m_pProcess==NULL)
	{
		return;
	}
	sprintf(m_pProcess+m_CurrPos,"%010d",nextID);
	
	/*
	long pos=ftell(m_processFile);
	fprintf(m_processFile,"%08d",nextID);
	fflush(m_processFile);
	fseek(m_processFile,pos,SEEK_SET);
	*/
}

void CBaseEngine::handleEmerge(int seqID)
{
//	///Ŀǰ�Ľ������������ǽ����к�Լ�л����ǽ���״̬
//	CInstrumentStatus *pInstrumentStatus;
//	CWriteableInstrumentStatus theInstrumentStatus;
//
//	for (pInstrumentStatus=m_pDB->m_InstrumentStatusFactory->getFirst();
//		pInstrumentStatus!=NULL;
//		pInstrumentStatus=m_pDB->m_InstrumentStatusFactory->getNext())
//	{
//		if (pInstrumentStatus->InstrumentStatus==IS_Closed)
//		{
//			///�Ѿ����̵ģ��Ͳ��ô�����
//			continue;
//		}
//		///����״̬�����г��ֶ��ķǽ���״̬���׶α�Ų���
//		m_pDB->m_InstrumentStatusFactory->retrieve(pInstrumentStatus,&theInstrumentStatus);
//		theInstrumentStatus.InstrumentStatus=IS_NoTrading;
//		theInstrumentStatus.EnterReason=IER_Manual;
//		m_pDB->m_InstrumentStatusFactory->update(pInstrumentStatus,&theInstrumentStatus);
//	}
//	m_pDB->m_InstrumentStatusFactory->endGet();
}

char *CBaseEngine::initMmap(bool isInit,char *processFileName)
{
	char actualName[MAX_PATH_LEN+1];
	convertPath(actualName,processFileName);
	char buff[11*100];
	memset(buff,0,sizeof(buff));

	FILE *fp;
	if ((fp=fopen(actualName,"r"))==NULL)
	{
		fp=fopen(actualName,"w+b");
		if (fp==NULL)
			return NULL;
		fwrite(buff,sizeof(buff),1,fp);
	}
	fclose(fp);
	
#ifdef WIN32
		HANDLE	hMemShare = OpenFileMapping(FILE_MAP_WRITE,FALSE,"process");
       if(hMemShare == NULL)
       {
		   OFSTRUCT m_of;
		   HFILE hFile;
		   hFile = ::OpenFile(actualName,&m_of,OF_READWRITE | OF_SHARE_DENY_NONE);
		   if (hFile == NULL)
		   {
			   printf("Can not open file\n");
			   return NULL;
		   }
		   hMemShare = CreateFileMapping((HANDLE)hFile,NULL,PAGE_READWRITE,0,1100,"process");
		   if (hMemShare == NULL)
		   {
			   printf("Can not create shmem\n");
				return NULL;
		   }
       }
	   m_pProcess = (char *)MapViewOfFile(hMemShare, FILE_MAP_WRITE,0,0,sizeof(buff));
       if(m_pProcess == NULL)
       {
			return NULL;
       }
		if (isInit)
			memcpy(m_pProcess,buff,sizeof(buff));
#endif

#ifndef WIN32
	int fd=open(actualName,O_RDWR,0);
	if (fd<0)
		return NULL;

	//��ʼ����ʽ
	if (isInit)
		write(fd,buff,sizeof(buff));
	
	m_pProcess=(char *)mmap(0,sizeof(buff),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if (m_pProcess == (char *)-1)
	{
		return NULL;
	}
#endif
	return m_pProcess;
}
