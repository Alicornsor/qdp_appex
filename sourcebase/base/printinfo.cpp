#include "printinfo.h"

int loglevel;
bool printstd;

char * getCurrTime(void)
{
	time_t ltime;
	struct tm *now;
	static char timeBuffer1[21];
	
	time(&ltime);
	now=localtime(&ltime);
	sprintf(timeBuffer1,"%04d%02d%02d-%02d:%02d:%02d",
		now->tm_year+1900,
		now->tm_mon+1,
		now->tm_mday,
		now->tm_hour,
		now->tm_min,
		now->tm_sec);
	return timeBuffer1;
}

char* getMachineName(void)
{
#ifdef WIN32
	static char nn[100];
	//gethostname(nn,100);
	//return nn;
	return "WIN32";
#else
	static char nn[100];
	gethostname(nn,100);
	return nn;
#endif
}

char * getCurrDate(void)
{
	time_t ltime;
	struct tm *now;
	static char timeBuffer1[21];
	
	time(&ltime);
	now=localtime(&ltime);
	sprintf(timeBuffer1,"%04d%02d%02d",
		now->tm_year+1900,
		now->tm_mon+1,
		now->tm_mday);
	return timeBuffer1;
}


char * getTime(void)
{
	time_t ltime;
	struct tm *now;
	static char timeBuffer2[21];
	
	time(&ltime);
	now=localtime(&ltime);
	sprintf(timeBuffer2,"%02d:%02d:%02d",
		now->tm_hour,
		now->tm_min,
		now->tm_sec);
	return timeBuffer2;
}

void printInfo(int level,char *sCppName,char* pFormat, ...)
{
	if (level < loglevel)
	{
		return;
	}

	char chMsg[32*1024];
	va_list pArg;
	
	static FILE *g_logfp=NULL;
	if (g_logfp==NULL)
	{
		g_logfp=mfopen("Syslog.log","at");	
		if (!g_logfp)
		{
			printf("not open %s.log\n");
			exit(0);
		}
		fprintf(g_logfp,"%s begin start\n",getCurrTime());
		fflush(g_logfp);
	}
	
	memset(chMsg,0,sizeof(chMsg));
	va_start(pArg, pFormat);
	vsprintf(chMsg+strlen(chMsg), pFormat, pArg);
	va_end(pArg);
	
	if(printstd)
		printf("%s",chMsg);	
	fprintf(g_logfp,"%s%c%s%c%s%c%02d%c%s: %s",getCurrDate(),\
		SEP_CHAR,getTime(),SEP_CHAR,getMachineName(),SEP_CHAR,level,SEP_CHAR,sCppName,chMsg);
	
	fflush(g_logfp);
}

// Ìæ»»×Ö·û´®ÖÐÌØÕ÷×Ö·û´®ÎªÖ¸¶¨×Ö·û´®
int ReplaceStr(char *sSrc, char *sMatchStr, char *sReplaceStr)
{
	int  StringLen;
	char caNewString[2000];
	
	char *FindPos = strstr(sSrc, sMatchStr);
	if( (!FindPos) || (!sMatchStr) )
		return -1;
	
	while( FindPos )
	{
		memset(caNewString, 0, sizeof(caNewString));
		StringLen = FindPos - sSrc;
		strncpy(caNewString, sSrc, StringLen);
		strcat(caNewString, sReplaceStr);
		strcat(caNewString, FindPos + strlen(sMatchStr));
		strcpy(sSrc, caNewString);
		
		FindPos = strstr(sSrc, sMatchStr);
	}
	
	return 0;
}

int CheckTime(char* localtime, char *sTime)
{
	int lTime1,lTime2;
    char strTime[20];
	
	sprintf(strTime,"%c%c%c%c%c%c",localtime[0],localtime[1],localtime[3],localtime[4],localtime[6],localtime[7]);
	lTime1 = atol(strTime);

	sprintf(strTime,"%c%c%c%c%c%c",sTime[0],sTime[1],sTime[3],sTime[4],sTime[6],sTime[7]);

	lTime2 = atol(strTime);
	
	if(lTime1 < lTime2) return -1;
	if(lTime1 == lTime2) return 0;
	if(lTime1 > lTime2) return 1;
	
	return 0;
}
