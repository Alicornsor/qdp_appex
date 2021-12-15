/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file platform.cpp
///@brief实现跨平台需要的函数
///@history 
///20080603 hwp		创建，增加WIN32下的getopt函数
#include "platform.h"

#ifdef WIN32
char	*optarg;		// global argument pointer
int		optind = 0; 	// global argv index

int getopt(int argc, char *argv[], char *optstring)
{
	static char *next = NULL;
	if (optind == 0)
		next = NULL;

	optarg = NULL;

	if (next == NULL || *next == ('\0'))
	{
		if (optind == 0)
			optind++;

		if (optind >= argc || argv[optind][0] != ('-') || argv[optind][1] == ('\0'))
		{
			optarg = NULL;
			if (optind < argc)
				optarg = argv[optind];
			return EOF;
		}

		if (strcmp(argv[optind], ("--")) == 0)
		{
			optind++;
			optarg = NULL;
			if (optind < argc)
				optarg = argv[optind];
			return EOF;
		}

		next = argv[optind];
		next++;		// skip past -
		optind++;
	}

	char c = *next++;
	char *cp = strchr(optstring, c);

	if (cp == NULL || c == (':'))
		return ('?');

	cp++;
	if (*cp == (':'))
	{
		if (*next != ('\0'))
		{
			optarg = next;
			next = NULL;
		}
		else if (optind < argc)
		{
			optarg = argv[optind];
			optind++;
		}
		else
		{
			return ('?');
		}
	}

	return c;
}

#else

void strupr(char   *pcSrc)   
{   
	int i;   
	for(i=0; i<strlen(pcSrc);i++)   
	{   
	  if(pcSrc[i]   >=   'a'   &&   pcSrc[i]   <=   'z')
	  {
		 pcSrc[i]   -=   32;   
	  }
	}   
}

#endif

static unsigned char source8[8]={12,1,5,13,7,2,9,11};
static unsigned char source4[4]={9,1,3,7};
static unsigned char gene8[8];
static unsigned char gene4[4];

void init_gene(long gene)
{
	if (gene<=0)
		return;
	int i;
	for (i=0;i<8;i++)
	{			
		gene8[i]=source8[i];
	}

	for (i=0;i<4;i++)
	{			
		gene4[i]=source4[i];
	}
	
	int g1=gene%8;
	int g2=gene%4;
	
	gene8[0]=source8[g1];
	gene8[g1]=source8[0];
	
	gene4[0]=source4[g2];
	gene4[g2]=source4[0];
}

void doodle8(unsigned char *p)
{
	for (int i=0;i<8;i++)
	{
#ifndef _BIG_ENDIAN_
		p[i]=p[i]+gene8[i];
#else
		p[i]=p[i]+gene8[7-i];
#endif
	}
}
void undoodle8(unsigned char *p)
{
	for (int i=0;i<8;i++)
	{
#ifndef _BIG_ENDIAN_
		p[i]=p[i]-gene8[i];
#else
		p[i]=p[i]-gene8[7-i];
#endif
	}
}

void doodle4(unsigned char *p)
{
	for (int i=0;i<4;i++)
	{	
#ifndef _BIG_ENDIAN_
		p[i]=p[i]+gene4[i];
#else
		p[i]=p[i]+gene4[3-i];
#endif
	}
}
void undoodle4(unsigned char *p)
{
	for (int i=0;i<4;i++)
	{
#ifndef _BIG_ENDIAN_
		p[i]=p[i]-gene4[i];
#else
		p[i]=p[i]-gene4[3-i];
#endif
	}
}

#ifdef LINUX
long int gettid()
{
	return syscall(__NR_gettid);
}
#endif
