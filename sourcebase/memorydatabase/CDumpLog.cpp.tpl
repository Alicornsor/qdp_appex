!!enter system!!
/////////////////////////////////////////////////////////////////////////
///@system 交易引擎系统
///@company 上海量投网络科技有限公司
///@file CDumpLog.cpp
///@brief实现了类CDumpLog
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CDumpLog.h"
#include "monitorIndex.h"

///本宏控制是否使用单行方式进行输出
#define SINGLE_LINE

!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
C!!@name!!DumpTrigger::C!!@name!!DumpTrigger(FILE *output, int flag)
{
	m_output=output;
	m_flag=flag;
}

C!!@name!!DumpTrigger::~C!!@name!!DumpTrigger(void)
{
}


void C!!@name!!DumpTrigger::output(CLogger *pLogger,int indent)
{
	//CHECK_TYPE("C!!@name!!DumpTrigger");
	pLogger->output(indent,0,"C!!@name!!DumpTrigger:flag=");
	if (m_flag&CREATE_ACTION)
		pLogger->output("CREATE ");
	if (m_flag&UPDATE_ACTION)
		pLogger->output("UPDATE ");
	if (m_flag&DELETE_ACTION)
		pLogger->output("DELETE ");
}

void C!!@name!!DumpTrigger::beforeAdd(CWriteable!!@name!! *p!!@name!!)
{
	if (m_flag&CREATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"!!@name!!,add");
		p!!@name!!->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Add !!@name!!\n");
		p!!@name!!->dump(m_output);
#endif
		fflush(m_output);
	}
}
	
void C!!@name!!DumpTrigger::beforeUpdate(C!!@name!! *p!!@name!!, CWriteable!!@name!! *pNew!!@name!!)
{
	if (m_flag&UPDATE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"!!@name!!,upd");
		pNew!!@name!!->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Update !!@name!!\n");
		pNew!!@name!!->dumpDiff(m_output,p!!@name!!);
#endif
		fflush(m_output);
	}
}
	
void C!!@name!!DumpTrigger::beforeRemove(C!!@name!! *p!!@name!!)
{
	if (m_flag&DELETE_ACTION)
	{
#ifdef SINGLE_LINE
		fprintf(m_output,"!!@name!!,del");
		p!!@name!!->dumpInLine(m_output);
		fprintf(m_output,"\n");
#else
		fprintf(m_output,"Remove !!@name!!\n");
		p!!@name!!->dump(m_output);
#endif
		fflush(m_output);
	}
}

!!endif!!
!!next!!
CDumpLog::CDumpLog(CMemoryDB *pDB, CConfig *pConfig)
{
	char *fileName=pConfig->getConfig("DumpOutput");

	// 2013-1-18 longqy 把下面这行提到前面来了。之前有可能会没有初始化就使用。
	m_Started=0;

	if (*fileName=='\0')
	{
		m_DumpOutput=NULL;
		return;
	}
	if (!strcmp(fileName,"stdout"))
	{
		m_DumpOutput=stdout;
	}
	else if (!strcmp(fileName,"stderr"))
	{
		m_DumpOutput=stderr;
	}
	else
	{
		m_DumpOutput=mfopen(fileName,"wt");
	}
	if (m_DumpOutput==NULL)
	{
		REPORT_EVENT(LOG_INFO,"EnvError","write dump file failed");
		return;
	}
	m_DB=pDB;
	// m_Started=0;

	!!travel tables!!
	!!if !strcmp(@hasTable,"yes")!!
	m_!!@name!!Trigger=new C!!@name!!DumpTrigger(m_DumpOutput,CREATE_ACTION|UPDATE_ACTION|DELETE_ACTION);
	!!endif!!
	!!next!!
}

CDumpLog::~CDumpLog(void)
{
	stop();
	if (m_DumpOutput==NULL)
	{
		return;
	}
	!!travel tables!!
	!!if !strcmp(@hasTable,"yes")!!
	delete m_!!@name!!Trigger;
	!!endif!!
	!!next!!
	if ((m_DumpOutput!=NULL)&&(m_DumpOutput!=stdout)&&(m_DumpOutput!=stderr))
	{
		fclose(m_DumpOutput);
	}
}

int CDumpLog::isStarted(void)
{
	return m_Started;
}

void CDumpLog::start(void)
{
	if (m_Started)
	{
		return;
	}
	if (m_DumpOutput==NULL)
	{
		return;
	}
	!!travel tables!!
	!!if !strcmp(@hasTable,"yes")!!
	m_DB->m_!!@name!!Factory->addActionTrigger(m_!!@name!!Trigger);
	!!endif!!
	!!next!!

	// 2013-1-18 longqy 添加下面一行，相当改变其状态后，给这个参数赋正确的值。
	m_Started=1;
}

void CDumpLog::stop()
{
	if (!m_Started)
	{
		return;
	}
	if (m_DumpOutput==NULL)
	{
		return;
	}
	!!travel tables!!
	!!if !strcmp(@hasTable,"yes")!!
	m_DB->m_!!@name!!Factory->removeActionTrigger(m_!!@name!!Trigger);
	!!endif!!
	!!next!!
	
	// 2013-1-18 longqy 添加下面一行，相当改变其状态后，给这个参数赋正确的值。
	m_Started=0;
}

void CDumpLog::dumpMsg(char *format,...)
{
	va_list v;
	
	if (!m_Started)
	{
		return;
	}
	
	va_start(v,format);
	vfprintf(m_DumpOutput,format,v);
	va_end(v);
	fflush(m_DumpOutput);
}

!!leave!!