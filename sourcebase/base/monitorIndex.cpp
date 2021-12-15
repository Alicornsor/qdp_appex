/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file monitorIndex.cpp
///@brief	ʵ�������йص�����ָ��
///@history 
///20060716	xuzh		�������ļ�
///20070828	hwp		(1)�����ļ���probelogger����base
///						(2)CMonitorIndex::initʹ��CConfig�ӿڸ�Ϊ�����
///						   CParameterMap,����ʵ���������CProbeLogger,��
///						   ���ɲ�������
/////////////////////////////////////////////////////////////////////////

#include "monitorIndex.h"
#include "mpath.h"

time_t CMonitorIndex::m_minNextTime=0;
vector<CMonitorIndex *>	*CMonitorIndex::m_indexList;
CProbeLogger *CMonitorIndex::m_probeLogger=NULL;
int CMonitorIndex::m_handleCountWait=1;
int CMonitorIndex::m_handleCountCheckFrequncy=1;
CRITICAL_VAR CMonitorIndex::m_criticalVar;
bool CMonitorIndex::m_inited=0;
int CMonitorIndex::m_logLevel=0;

void CMonitorIndex::setProbeLogger(CProbeLogger *pProbeLogger)
{
	// ����Ĵ����߼��д��޸�Ϊ��ȷ�ġ� longqy 20130902
	//if (m_probeLogger==NULL)
	if (m_probeLogger != NULL)
	{
		delete m_probeLogger;	// ����û�����������ĵط����٣�Ҫ���ġ� longqy
	}
	m_probeLogger = pProbeLogger;
}

///------
//	xuzh��20070114���޸��˳�ʼ���Ĺ��̣��������û������Syslog������£�һЩ�������ܲ���ʹ�õ�����
///======

void CMonitorIndex::init(CProbeLogger *pProbeLogger, CParameterMap *pConfig)
{
///------
///	xuzh��20070727�������˰�����־����ķ�ʽ��������־����Ĺ���
///------
	char *logLevelString;
	logLevelString=pConfig->getConfig("LogLevel");
	if (*logLevelString)
	{
		int logLevel;
		if (!strcmp(logLevelString,"debug"))
		{
			logLevel=LOG_DEBUG;
		}
		else if (!strcmp(logLevelString,"info"))
		{
			logLevel=LOG_INFO;
		}
		else if (!strcmp(logLevelString,"critical"))
		{
			logLevel=LOG_CRITICAL;
		}
		else if (!strcmp(logLevelString,"none"))
		{
			logLevel=LOG_NONE;
		}
		else if (isdigit(*logLevelString))
		{
			logLevel=atoi(logLevelString);
		}
		else
		{
			logLevel=LOG_DEBUG;
		}
		if (logLevel>LOG_DEBUG)
		{
			logLevel=LOG_DEBUG;
		}
		else if (logLevel<LOG_NONE)
		{
			logLevel=LOG_NONE;
		}
		UseBizStatusLog=false;
		UseBizOperationLog=false;
		UseBizExceptionLog=false;
		UseNetStatusLog=false;
		UseNetConnectLog=false;
		UseNetIOLog=false;
		UseNetPackageLog=false;
		UseNetCompressLog=false;
		UseNetExceptionLog=false;
		UseProcessLog=false;
			
		if (logLevel>=LOG_DEBUG)
		{
			UseNetPackageLog=true;
			UseNetCompressLog=true;
		}
		
		if (logLevel>=LOG_INFO)
		{
			UseBizStatusLog=true;
			UseBizOperationLog=true;
			UseNetStatusLog=true;
			UseNetConnectLog=true;
			UseNetIOLog=true;
			UseProcessLog=true;
		}
		
		if (logLevel>=LOG_CRITICAL)
		{
			UseBizExceptionLog=true;
			UseNetExceptionLog=true;
		}
		
		m_logLevel=logLevel;
	}
	else
	{
		m_logLevel=LOG_DEBUG;
	}

#define GET_CONFIG(name)								\
	{													\
		if (!strcmp(pConfig->getConfig(#name),"yes"))	\
		{												\
			name=true;									\
		}												\
		if (!strcmp(pConfig->getConfig(#name),"no"))	\
		{												\
			name=false;									\
		}												\
	}

	GET_CONFIG(UseBizStatusLog);
	GET_CONFIG(UseBizOperationLog);
	GET_CONFIG(UseBizExceptionLog);
	GET_CONFIG(UseNetStatusLog);
	GET_CONFIG(UseNetConnectLog);
	GET_CONFIG(UseNetIOLog);
	GET_CONFIG(UseNetPackageLog);
	GET_CONFIG(UseNetCompressLog);
	GET_CONFIG(UseNetExceptionLog);
	GET_CONFIG(UseProcessLog);
	
	if (pProbeLogger==NULL)
	{
		return;
	}

	setProbeLogger(pProbeLogger);
//	CBoolMonitorIndex *pIsActiveIndex=new CBoolMonitorIndex("IsActive",20);
//	pIsActiveIndex->setValue(true);
}

void CMonitorIndex::handleOne(void)
{
	m_handleCountWait--;
	if (m_handleCountWait>0)
	{
		///������û�е�����
		return;
	}
	///�Ѿ����˼����ˣ��������������´μ����Ҫ�ȴ��Ĵ���
	m_handleCountWait=m_handleCountCheckFrequncy;

	if (m_probeLogger==NULL)
	{
		///��û������̽�룬�ǾͲ�����
		return;
	}

	///Ȼ����ݵ�ǰ���¼����ж��Ƿ���Ҫ����
	time_t now;
	time(&now);
	if (now<m_minNextTime)
	{
		///��С���´�ʱ�䶼û�е����ǾͲ��ø���
		return;
	}

	vector<CMonitorIndex *>::iterator it;
	for (it=m_indexList->begin();it<m_indexList->end();it++)
	{
		if ((*it)->m_nextTime<=now)
		{
			///��ָ���ʱ�䵽�ˣ��ǾͶ�����б���
			(*it)->report(m_probeLogger);
			///�����´�ʱ��
			if ((*it)->m_frequncy<=60)
			{
				(*it)->m_nextTime=(now/((*it)->m_frequncy)+1)*((*it)->m_frequncy);
			}
			else
			{
				(*it)->m_nextTime=now+(*it)->m_frequncy;
			}
		}
		if (it==m_indexList->begin())
		{
			m_minNextTime=(*it)->m_nextTime;
		}
		else
		{
			if ((*it)->m_nextTime<m_minNextTime)
			{
				m_minNextTime=(*it)->m_nextTime;
			}
		}
	}
}

void CMonitorIndex::setHandleCountCheckFrequncy(int newFrequncy)
{
	m_handleCountCheckFrequncy=newFrequncy;
}

void CMonitorIndex::reportAll(void)
{
	if (m_probeLogger==NULL)
	{
		///��û������̽�룬�ǾͲ�����
		return;
	}
	
	vector<CMonitorIndex *>::iterator it;
	for (it=m_indexList->begin();it<m_indexList->end();it++)
	{
		(*it)->report(m_probeLogger);
	}
}

void CIntMonitorIndex::report(CProbeLogger *pProbeLogger)
{
	pProbeLogger->SendProbeMessage(m_name,m_value);
}

void CIntUsageMonitorIndex::report(CProbeLogger *pProbeLogger)
{
	pProbeLogger->SendProbeMessage(m_name,m_value);
	pProbeLogger->SendPercentageProbeMessage(m_usageName,((double)m_value)/m_totalValue);
}

void CIntPtrMonitorIndex::report(CProbeLogger *pProbeLogger)
{
	if (m_Total>0)
	{
		double per=(*m_ptr);
		pProbeLogger->SendPercentageProbeMessage(m_name,(per/m_Total));
	}
	else
		pProbeLogger->SendProbeMessage(m_name,*m_ptr);
}

void CPerIntPtrMonitorIndex::report(CProbeLogger *pProbeLogger)
{
	if (m_per>0 && (*m_ptr)>m_per)
	{
		m_per=(*m_ptr)-m_per;
	}
	else
		m_per=0;
	
	char nameBuffer[MAX_PARAMETER_NAME];
	sprintf(nameBuffer,"Tatal%s",m_name);
	pProbeLogger->SendProbeMessage(nameBuffer,*m_ptr);
	sprintf(nameBuffer,"Increase%s",m_name);
	pProbeLogger->SendProbeMessage(nameBuffer,m_per);
	m_per=*m_ptr;
}

void CBoolMonitorIndex::report(CProbeLogger *pProbeLogger)
{
	pProbeLogger->SendProbeMessage(m_name,(int)m_value);
}

void CStringMonitorIndex::report(CProbeLogger *pProbeLogger)
{
	pProbeLogger->SendProbeMessage(m_name,m_value);
}

void CIntTotalMonitorIndex::report(CProbeLogger *pProbeLogger)
{
	pProbeLogger->SendProbeMessage(m_name,m_value);
	m_totalValue+=m_value;
	pProbeLogger->SendProbeMessage(m_totalName,m_totalValue);
	m_value=0;
}

void CStringBufferMonitorIndex::report(CProbeLogger *pProbeLogger)
{
	pProbeLogger->SendProbeMessage(m_name,m_value);
}

void CStringBufferArrayMonitorIndex::report(CProbeLogger *pProbeLogger)
{
	for (int i=0;i<m_size;i++)
	{
		if (m_value[i][0]!='\0')
		{
			char nameBuffer[MAX_PARAMETER_NAME];
			sprintf(nameBuffer,"%s.%d",m_name,i+1);
			pProbeLogger->SendProbeMessage(nameBuffer,m_value[i]);
		}
	}
}

void CFloatMonitorIndex::report(CProbeLogger *pProbeLogger)
{
	pProbeLogger->SendProbeMessage(m_name,m_value);
}

void CEventMonitor::report(const char *detail)
{
	if (m_probeLogger==NULL)
	{
		return;
	}
	char buffer[4096];
	sprintf(buffer,"%s %s %s %s",m_type,m_ipAdr,m_user,detail);
	m_probeLogger->SendProbeMessage("event",buffer);
}

void CEventMonitor::report(const char *type, const char *detail)
{
	if (m_probeLogger==NULL)
	{
		return;
	}
	char buffer[4096];
	sprintf(buffer,"%s %s %s %s",type,m_ipAdr,m_user,detail);
	m_probeLogger->SendProbeMessage("event",buffer);
}

void CEventMonitor::report(const char *type, const char *ipAdr, const char *user, const char *detail)
{
	if (m_probeLogger==NULL)
	{
		return;
	}
	char buffer[4096];
	sprintf(buffer,"%s %s %s %s",type,ipAdr,user,detail);
	m_probeLogger->SendProbeMessage("event",buffer);
}

void CEventMonitor::report(CProbeLogger *pProbeLogger)
{
}

void CEventMonitor::report(int level, const char *type, const char *format, ...)
{
	if (m_probeLogger==NULL)
	{
		return;
	}
	if (level>m_logLevel)
	{
		return;
	}
	char buffer[4096];

	/// longqy 2013-12-18 �����ֹؼ�������Ϣ������־����ӵ��� Critical��������������־���ҵ�
// 	if(LOG_CRITICAL <= level)
// 	{
// 		sprintf(buffer,"Critical %s %d ",type,level);
// 	}
// 	else
// 	{
// 		sprintf(buffer,"%s %d ",type,level);
//	}

	sprintf(buffer,"%s %d ",type,level);
	va_list v;
	va_start(v,format);
	vsprintf(buffer+strlen(buffer),format,v);
	m_probeLogger->SendProbeMessage("event",buffer);
	
	/// xuzh ���ؼ�������ڱ�׼����������
	if(LOG_CRITICAL >= level)
	{
		printf("%s \n",buffer);
	}	
	va_end(v);
}

CEventMonitor stdEventMonitor;
