#include "TBCommandFile.h"
#define GETCMD(VAL,CMD) if(!strncmp(buffer,CMD,strlen(CMD))){itcnt++;RTrim(buffer);VAL=buffer+strlen(CMD);FZero(buffer);}

CTBCommandFile::CTBCommandFile(const char *dataFile)
{
	strcpy(m_sDataFile,dataFile);
}

CTBCommandFile::~CTBCommandFile()
{
}

void CTBCommandFile::Lock()
{
#ifdef UNIX
	int fildes;

	if((fildes=open(m_sDataFile,O_APPEND))<0)
	{
		return ;
	}

	struct flock fl;
	fl.l_type = F_WRLCK ;
	fl.l_start = 0 ;
	fl.l_whence = SEEK_END ;
	fl.l_len = 0 ;
	fl.l_pid = getpid() ;

	fcntl(fildes, F_SETLK, &fl);
#endif
}

void CTBCommandFile::UnLock()
{
#ifdef UNIX
	int fildes;

	if((fildes=open(m_sDataFile,O_APPEND))<0)
	{
		return ;
	}

	struct flock fl;
	fl.l_type = F_WRLCK ;
	fl.l_start = 0 ;
	fl.l_whence = SEEK_END ;
	fl.l_len = 0 ;
	fl.l_pid = getpid() ;

	fcntl(fildes, F_UNLCK, &fl);
#endif
}

int CTBCommandFile::Gets(FILE *fp,char *buffer)
{
	int i;
	for(i=0;!feof(fp);i++)
	{
		if(!fread(buffer+i,1,1,fp))
		{
			return 0;
		}
		if(i==MAXLINELENGTH||*(buffer+i)=='\n'||*(buffer+i)==13)
		{
			*(buffer+i)=0;
			if(i==0)
			{
				continue;
			}
			return i;
		}
	}
	*(buffer+i)=0;
	return i;
}

bool CTBCommandFile::ReadCommand(struct sTBCMD &CMDPackage)
{
	static long offset=0;
	FILE *fp;

	CTradingDayType TradingDay;
	CCommandNoType CommandNo;
	CCommandTypeType CommandType;
	CFieldNameType FieldName;
	CFieldContentType FieldContent;

	if((fp=fopen(m_sDataFile,"r"))==NULL)
	{
		return false;
	}

	fseek(fp,offset,SEEK_SET);	
	
	int ret=0;
	char buffer[MAXLINELENGTH+1];
	
	memset(buffer,0,MAXLINELENGTH);
	for(int itcnt=0;ret=Gets(fp,buffer);)
	{
		GETCMD(TradingDay,"TradingDay:");
		GETCMD(CommandNo,"CommandNo:");
		GETCMD(CommandType,"CommandType:");
		GETCMD(FieldName,"FieldName:");
		GETCMD(FieldContent,"FieldContent:");

		if(!strncmp(buffer,"TradingDay:",strlen("TradingDay:")))
		{
			itcnt=1;
		}
		if (itcnt==5)
		{
			CMDPackage.TradingDay=TradingDay;
			CMDPackage.CommandNo=CommandNo;
			CMDPackage.CommandType=CommandType;
			CMDPackage.FieldName=FieldName;
			CMDPackage.FieldContent=FieldContent;
			offset=ftell(fp);
			fclose(fp);
			return true;
		}
	}
	fclose(fp);
	return false;
}

CCommandNoType CTBCommandFile::GetLastCommandNo()
{
	static CCommandNoType lastCMDNo=-1; 
	struct sTBCMD pkg;
	while(ReadCommand(pkg))
	{
		if (pkg.CommandNo>lastCMDNo)
		{
			lastCMDNo = pkg.CommandNo;
		}		
	}
	return lastCMDNo;
}

bool CTBCommandFile::AppendCommand(const struct sTBCMD &CMDPackage)
{
	FILE *fp;
	CCommandNoType lastCMDNo;

	Lock();
	if((fp=fopen(m_sDataFile,"a+"))==NULL)
	{
		return false;
	}
	
	lastCMDNo=GetLastCommandNo();
	if (lastCMDNo<0)
	{
		lastCMDNo=1;
	}
	else
	{
		lastCMDNo=lastCMDNo+1;
	}
	fseek(fp,0,SEEK_END);

	fprintf(fp,"#######################################\n");
	fprintf(fp,"TradingDay:%1s\n",CMDPackage.TradingDay.getValue());
	fprintf(fp,"CommandNo:%1d\n",lastCMDNo.getValue());
	fprintf(fp,"CommandType:%1s\n",CMDPackage.CommandType.getValue());
	fprintf(fp,"FieldName:%1s\n",CMDPackage.FieldName.getValue());
	fprintf(fp,"FieldContent:%1s\n",CMDPackage.FieldContent.getValue());

	fclose(fp);
	UnLock();
	return true;
}
