!!include function.tpl!!
!!enter system!!
/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file BaseDataStruct.cpp
///@brief实现了内存数据库用的基本数据结构类，以及iterator、trigger的基类
///@history 
///20121227	hwp		创建该文件
///		为了NT-0058的需要，增加了读入CSV时自动识别双引号的功能
/////////////////////////////////////////////////////////////////////////

#include "BaseDataStruct.h"
#include "databaseFactories.h"

int compare(const char *s1, const char *s2)
{
	int result=strcmp(s1,s2);
	if (result>0)
		return 1;
	else if (result<0)
		return -1;
	return 0;
}

int compare(const int v1,const int v2)
{
	if (v1>v2)
		return 1;
	if (v1<v2)
		return -1;
	return 0;
}

int compare(const long v1,const long v2)
{
	if (v1>v2)
		return 1;
	if (v1<v2)
		return -1;
	return 0;
}

int compare(const double v1,const double v2)
{
	if (v1>v2+SMALL_DOUBLE)
		return 1;
	if (v1<v2-SMALL_DOUBLE)
		return -1;
	return 0;
}

char *getNextToken(char *buffer)
{
	static char *last;
	char *from, *to;
	
	if (buffer==NULL)
	{
		from=last;
		if (from==NULL)
		{
			return NULL;
		}
	}
	else
	{
		from=buffer;
	}
	
	bool hasQuote=false;
	if (*from=='"')
	{
		from++;
		hasQuote=true;
	}
	to=from;
	while ((*to!='\0')&&(*to!=',')&&(*to!='\n'))
	{
		if (hasQuote && (*to=='"'))
		{
			to++;
			break;
		}
		to++;
	}
	if (*to!=',')
	{
		last=NULL;
	}
	else
	{
		last=to+1;
	}
	if (!hasQuote)
	{
		*to='\0';
	}
	else
	{
		*(to-1)='\0';
	}
	return from;
}

!!travel tables!!
!!command resetEntityMap();!!
!!travel fields!!
!!command addEntity(@name,@type)!!
!!next!!

void CWriteable!!@name!!::writeCSVHead(FILE *output)
{
	fprintf(output,"!!travel fields!!!!if @pumpid!=0!!,!!endif!!!!@name!!!!next!!\n");
}
	
void CWriteable!!@name!!::init(void)
{
	!!travel fields!!
	!!@name!!.clear();
	!!next!!
	!!travel foreigns!!
	p!!@name!!=NULL;
	!!next!!
}

int CWriteable!!@name!!::read(FILE *input) 
{
	if (fread(this,1,sizeof(CWriteable!!@name!!),input)!=sizeof(CWriteable!!@name!!))
		return 0;
	else
		return 1;
}
	
int CWriteable!!@name!!::readCSV(FILE *input,vector<char *> *pNames)
{
	char buffer[1025];
	char *token;
	if (fgets(buffer,1024,input)==NULL)
		return 0;
	if (pNames==NULL)
	{
		!!travel fields!!
		!!if @pumpid==0!!
		token=getNextToken(buffer);
		!!else!!
		token=getNextToken(NULL);
		!!endif!!
		if (token!=NULL)
		{
			!!@name!!=token;
		}
		else
		{
			!!@name!!="";
		}
		!!next!!
	}
	else
	{
		init();
		token=getNextToken(buffer);
		int i=0;
		while (token!=NULL)
		{
			char *fieldName;
			fieldName=pNames->at(i);
			if (fieldName==NULL)
			{
				break;
			}
			!!travel fields!!
			!!if @pumpid==0!!
			if (!strcmp(fieldName,"!!@name!!"))
			!!else!!
			else if (!strcmp(fieldName,"!!@name!!"))
			!!endif!!
			{
				!!@name!!=token;
			}
			!!next!!
			i++;
			token=getNextToken(NULL);
		}
	}
	return 1;
}
	
int CWriteable!!@name!!::write(FILE *output) const
{
	if (fwrite(this,1,sizeof(CWriteable!!@name!!),output)!=sizeof(CWriteable!!@name!!))
		return 0;
	else
		return 1;
}

int CWriteable!!@name!!::writeCSV(FILE *output) const
{
	char buffer[1025];
	!!travel fields!!
	!!if @pumpid!=0!!
	fprintf(output,",");
	!!endif!!
	!!@name!!.getString(buffer);
	fprintf(output,"%s",buffer);
	!!next!!
	fprintf(output,"\n");
	return 1;
}
!!++!!
int CWriteable!!@name!!::isValid(void) const
{
	!!travel fields!!
	if (! !!@name!!.isValid())
		return 0;
	!!next!!
	return 1;
}
!!--!!
void CWriteable!!@name!!::dump(FILE *fp,int index) const
{
	char index_buf[20];
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	if (index>=0)
		sprintf(index_buf,"[%d]",index);
	else
		index_buf[0]='\0';
	fprintf(fp, "\tC!!@name!!%s = {\n", index_buf);
	!!travel fields!!
	!!@name!!.getString(buf);
	fprintf(fp,"\t\t!!@name!! = %s    [!!@comment!!]\n",buf);	
	!!next!!	
	fprintf(fp,"\t}\n");
}

void CWriteable!!@name!!::dumpDiff(FILE *fp, const CWriteable!!@name!! *pOriginal) const
{
	char buf[4000],bufOriginal[4000];
	if(fp==NULL)
	{
		fp=stdout;
	}
	fprintf(fp, "\tC!!@name!! = {\n");
	!!travel fields!!
	!!@name!!.getString(buf);
	if (compare(!!@name!!.getValue(),pOriginal->!!@name!!.getValue())!=0)
	{
		pOriginal->!!@name!!.getString(bufOriginal);
		fprintf(fp,"\t\t!!@name!! = %s -> %s    [!!@comment!!]\n",bufOriginal,buf);
	}
	else
	{
		fprintf(fp,"\t\t!!@name!! = %s    [!!@comment!!]\n",buf);
	}
	!!next!!	
	fprintf(fp,"\t}\n");
}

void CWriteable!!@name!!::dumpInLine(FILE *fp) const
{
	char buf[4000];///存放每个成员的字符串值	
	if(fp==NULL)
	{
		fp=stdout;
	}
	!!travel fields!!
	!!@name!!.getString(buf);
	fprintf(fp,",!!@name!!,%s",buf);	
	!!next!!	
}

void CWriteable!!@name!!::dumpString(char *target) const
{
	char *p=target;
	char buf[4000];///存放每个成员的字符串值	
	!!travel fields!!
	!!@name!!.getString(buf);
	sprintf(p,"!!@name!!=%s,",buf);
	p+=strlen(p);
	!!next!!
	p--;
	*p='\0';
}

void CWriteable!!@name!!::output(CLogger *pLogger,int indent)
{
	char buf[1024];
	pLogger->output(indent,0,"C!!@name!!");
	pLogger->output(indent,0,"{");
	!!travel fields!!
	!!@name!!.getString(buf);
	pLogger->output(indent+1,0,"!!@name!!=%s !!@comment!!",buf);
	!!next!!
	pLogger->output(indent,0,"}");
}

!!if !strcmp(@hasTable,"yes")!!
!!++!!
C!!@name!!Iterator::C!!@name!!Iterator(C!!@name!!Factory *pFactory)
{
	m_Factory=pFactory;
}
!!--!!
C!!@name!!Iterator::~C!!@name!!Iterator(void)
{
}

!!++!!
C!!@name!!Factory *C!!@name!!Iterator::getFactory(void)
{
	return m_Factory;
}
!!--!!

void C!!@name!!Iterator::dump(FILE *output)
{
	C!!@name!! *p!!@name!!;
	
	while ((p!!@name!!=next())!=NULL)
	{
		p!!@name!!->dump(output);
	}
}
!!endif!!

!!++!!
!!let tableName=@name!!
!!travel foreigns!!
const CWriteable!!@factory!! *CWriteable!!@tableName!!::link!!@name!!(C!!@factory!!Factory *pFactory) const
{
	void *target=(void *)(&p!!@name!!);
	*((const CWriteable!!@factory!! **)target)=pFactory->find!!@method!!(!!@key!!);
	!!if !strcmp(@foreignStrick,"yes")!!
	if (p!!@name!!==NULL)
	{
		RAISE_RUNTIME_ERROR("can not link !!@name!! in !!@tableName!!");
	}
	!!endif!!
	return p!!@name!!;
}

const CWriteable!!@factory!! *CWriteable!!@tableName!!::link!!@name!!(const CWriteable!!@factory!! *p!!@factory!!) const
{
	void *target=(void *)(&(this->p!!@name!!));
	*((const CWriteable!!@factory!! **)target)=p!!@factory!!;
	return p!!@factory!!;
}

const CWriteable!!@factory!! *CWriteable!!@tableName!!::get!!@name!!(void) const
{
	!!if !strcmp(@foreignStrick,"yes")!!
	if (p!!@name!!==NULL)
	{
		RAISE_RUNTIME_ERROR("!!@name!! in !!@tableName!! not linked");
	}
	!!endif!!
	return p!!@name!!;
}
!!next!!
!!--!!

!!next!!
!!leave!!
