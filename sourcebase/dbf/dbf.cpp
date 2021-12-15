/////////////////////////////////////////////////////////////////////////
///@system QDP系统
///@company 上海量投网络科技有限公司
///@file dbf.cpp
///@brief实现了与DBF操作有关的类接口
///@history 
///20150625	徐忠华		创建该文件
/////////////////////////////////////////////////////////////////////////
#include "dbf.h"

#define UNKNOWN_ENDIAN 0
#define LITTLE_ENDIAN 1
#define BIG_ENDIAN 2

static int endian_type=UNKNOWN_ENDIAN;

static void check_endian(void)
{
	char *p_char;
	int check_int;
	p_char=(char *)&check_int;
	p_char[0]=1;
	p_char[1]=2;
	p_char[2]=3;
	p_char[3]=4;
	if (check_int==0x04030201)
		endian_type=LITTLE_ENDIAN;
	else if (check_int==0x01020304)
		endian_type=BIG_ENDIAN;
	else
	{
		return;
		/*printf("Unknown endian type\n");
		exit(1);*/
	}
}

static void normalize(char *s,int length)
{
	char *p;
	s[length]='\0';
	p=s+strlen(s)-1;
	while ((p>=s)&&(*p==' '))
	{
		*p='\0';
		p--;
	}
}

static void swap_short(short *p_short)
{
	char *p1,*p2,tmp;
	p1=(char *)p_short;
	p2=p1+1;
	tmp=*p1;
	*p1=*p2;
	*p2=tmp;
}

static void swap_int(int *p_int)
{
	char *p1,*p2,tmp;
	p1=(char *)p_int;
	p2=p1+3;
	tmp=*p1;
	*p1=*p2;
	*p2=tmp;
	p1++;
	p2--;
	tmp=*p1;
	*p1=*p2;
	*p2=tmp;
}


CDBF::CDBF(void)
{
	opened=false;
}

CDBF::~CDBF(void)
{
	close();
}


int CDBF::open(char *database)
{
	short i;
	int offset;
	char name_buffer[81];
	char buffer[0x20];
	
	close();
	if (endian_type==UNKNOWN_ENDIAN)
		check_endian();
	strcpy(name_buffer,database);
	//xuzh 20121115 增加文件名转换
	char actualName[MAX_PATH_LEN+1];
	convertPath(actualName,name_buffer);

	handle=::open(actualName,OPEN_FOR_READ);
	if (handle==-1)
	{
		return 0;
	}
	if (read(handle,buffer,0x20)!=0x20)
	{
		::close(handle);
		return 0;
	}
	id=buffer[0];
	year=buffer[1];
	month=buffer[2];
	day=buffer[3];
	memcpy(&recCount,buffer+4,sizeof(int));
	memcpy(&startPos,buffer+8,sizeof(short));
	memcpy(&recWidth,buffer+10,sizeof(int));
	if (endian_type==BIG_ENDIAN)
	{
		swap_int(&(recCount));
		swap_short(&(startPos));
		swap_int(&(recWidth));
	}
	if ((id!=0x03)&&(id!=0x30)&&(id!=0x83)&&(id!=0xf5))
	{
		::close(handle);
		return 0;
	}
	memoHandle=0;
	if (id==0x83)
		strcpy(name_buffer+strlen(name_buffer)-3,"dbt");
	else if (id==0xf5)
		strcpy(name_buffer+strlen(name_buffer)-3,"fpt");
	if ((id==0x83)||(id==0xf5))
	{
		convertPath(actualName,name_buffer);
		memoHandle=::open(actualName,OPEN_FOR_READ);
		if (memoHandle==-1)
		{
			printf("Can not open %s\n",name_buffer);
			::close(handle);
			return 0;
		}
		memoBuffer=(char *)malloc(MAX_MEMO_FIELD+1);
		if (memoBuffer==NULL)
		{
			::close(memoHandle);
			::close(handle);
			return 0;
		}
	}
	if (id==0x83)
		memoBlockLength=512;
	if (id==0xf5)
	{
		lseek(memoHandle,4,SEEK_SET);
		if (read(memoHandle,&(memoBlockLength),
			sizeof(int))!=sizeof(int))
		{
			free(memoBuffer);
			::close(memoHandle);
			::close(handle);
			return 0;
		}
		if (endian_type==LITTLE_ENDIAN)
			swap_int(&(memoBlockLength));
	}

    //0x30是Visual FoxPro，其头文件长度为32+32*n+263+1
    //其他的格式的头文件长度为32+32*n+1
	if(id==0x30)
		fieldCount=(startPos-264)/0x20-1;
    else
	    fieldCount = (startPos-1)/0x20-1;

	fieldDefines=(CFieldDefine *)malloc(sizeof(CFieldDefine)*fieldCount);
	if (fieldDefines==NULL)
	{
		if (memoHandle!=0)
		{
			free(memoBuffer);
			::close(memoHandle);
		}
		::close(handle);
		return 0;
	}
	offset=1;
	for (i=0;i<fieldCount;i++)
	{
		if (read(handle,buffer,0x20)!=0x20)
		{
			if (memoHandle!=0)
			{
				free(memoBuffer);
				::close(memoHandle);
			}
			free(fieldDefines);
			::close(handle);
			return 0;
		}
		memcpy(fieldDefines[i].name,buffer,11);
		fieldDefines[i].type=buffer[11];
		fieldDefines[i].length1=buffer[16];
		fieldDefines[i].length2=buffer[17];
		fieldDefines[i].offset=offset;
		if (fieldDefines[i].type=='C')
			fieldDefines[i].length=
				fieldDefines[i].length1+
				fieldDefines[i].length2*256;
		else
			fieldDefines[i].length=
				fieldDefines[i].length1;
		offset+=fieldDefines[i].length;
		normalize(fieldDefines[i].name,10);
	}
	recBuffer=(char *)malloc(recWidth+1);
	if ((recBuffer==NULL)||(offset!=recWidth))
	{
		if (memoHandle!=0)
		{
			free(memoBuffer);
			::close(memoHandle);
		}
		free(fieldDefines);
		::close(handle);
		return 0;
	}  
	opened=true;
	return 1;
}

int CDBF::openForWrite(char *database)
{
	short i;
	int offset;
	char name_buffer[81];
	char buffer[0x20];
	
	close();
	if (endian_type==UNKNOWN_ENDIAN)
		check_endian();
	strcpy(name_buffer,database);

	char actualName[MAX_PATH_LEN+1];	
	convertPath(actualName,name_buffer);
	handle=::open(actualName,OPEN_FOR_WRITE);

	if (handle==-1)
	{
		return 0;
	}
	if (read(handle,buffer,0x20)!=0x20)
	{
		::close(handle);
		return 0;
	}
	id=buffer[0];
	year=buffer[1];
	month=buffer[2];
	day=buffer[3];
	memcpy(&recCount,buffer+4,sizeof(int));
	memcpy(&startPos,buffer+8,sizeof(short));
	memcpy(&recWidth,buffer+10,sizeof(int));
	if (endian_type==BIG_ENDIAN)
	{
		swap_int(&(recCount));
		swap_short(&(startPos));
		swap_int(&(recWidth));
	}
	if (id!=0x03)
	{
		::close(handle);
		return 0;
	}
	memoHandle=0;
	fieldCount=startPos/0x20-1;
	fieldDefines=(CFieldDefine *)malloc(sizeof(CFieldDefine)*fieldCount);
	if (fieldDefines==NULL)
	{
		::close(handle);
		return 0;
	}
	offset=1;
	for (i=0;i<fieldCount;i++)
	{
		if (read(handle,buffer,0x20)!=0x20)
		{
			free(fieldDefines);
			::close(handle);
			return 0;
		}
		memcpy(fieldDefines[i].name,buffer,11);
		fieldDefines[i].type=buffer[11];
		fieldDefines[i].length1=buffer[16];
		fieldDefines[i].length2=buffer[17];
		fieldDefines[i].offset=offset;
		if (fieldDefines[i].type=='C')
			fieldDefines[i].length=
				fieldDefines[i].length1+
				fieldDefines[i].length2*256;
		else
			fieldDefines[i].length=
				fieldDefines[i].length1;
		offset+=fieldDefines[i].length;
		normalize(fieldDefines[i].name,10);
	}
	recBuffer=(char *)malloc(recWidth+1);
	if ((recBuffer==NULL)||(offset!=recWidth))
	{
		free(fieldDefines);
		::close(handle);
		return 0;
	}
	opened=true;
	return 1;
}

void CDBF::close(void)
{
    //消除的是邋char*类型的指针
	if (!opened)
	{
		return;
	}
	opened=false;
	if (memoHandle!=0)
	{
		free(memoBuffer);
		::close(memoHandle);
	}

	free(recBuffer);
	free(fieldDefines);
	::close(handle);
}


char *CDBF::getField(char *fieldName,int recno,short *pLength)
{
	short i;
	char *pBuffer;
	if (!opened)
	{
		//没有打开文件
		return NULL;
	}
	if ((recno<1)||(recno>recCount))
	{
		//记录号越界
		return NULL;
	}
	for (i=0;i<fieldCount;i++)
	{
		if (!strcmp(fieldDefines[i].name,fieldName))
			break;
	}
	if (i==fieldCount)
	{
		//字段没有找到
		return NULL;
	}
	if (lseek(handle,startPos+recWidth*(recno-1),SEEK_SET)==-1)
	{
		//找不到DBF文件中的位置
		return NULL;
	}
	if (read(handle,recBuffer,recWidth)!=recWidth)
	{
		//数据读不出来
		return NULL;
	}
	if (recBuffer[0]=='*')
	{
		//已经删除的记录
		*pLength=0;
		return "";
	}
	
	//已经找到该字段了
	pBuffer=recBuffer+(fieldDefines[i].offset);
	*pLength=fieldDefines[i].length;
	pBuffer[*pLength]='\0';

	//如果是memo字段，那还需要找到相应的文件
	if (fieldDefines[i].type=='M')
	{
		int pos;
		pos=atol(pBuffer);
		if (pos==0)
		{
			//memo字段中没有
			*pLength=0;
			return "";
		}
		if (lseek(memoHandle,pos*memoBlockLength,SEEK_SET)==-1)
		{
			//找不到在memo文件中的位置
			return NULL;
		}
		if (id==0x83)
		{
			char *endPtr;
			if (read(memoHandle,memoBuffer,MAX_MEMO_FIELD)==0)
			{
				//读不出memo字段内容
				return NULL;
			}
			memoBuffer[MAX_MEMO_FIELD]='\0';
			endPtr=strchr(memoBuffer,0x1a);
			if (endPtr!=NULL)
			{
				*endPtr='\0';
				*pLength=endPtr-memoBuffer;
				return memoBuffer;
			}
			*pLength=MAX_MEMO_FIELD;
			//printf("\nMemo filed exceed, Please adjust MAX_MEMO_FIELD in dbf.h\n");
			return memoBuffer;
		}
		if (id==0xf5)
		{
			int value[2];
			if (read(memoHandle,value,sizeof(int)*2)!=sizeof(int)*2)
			{
				//无法读出标记和长度
				return NULL;
			}
			swap_int(value);
			swap_int(value+1);
			if (value[0]!=1)
			{
				//标记不对
				return NULL;
			}
			if (value[1]>MAX_MEMO_FIELD)
			{
				//printf("\nMemo filed exceed, Please adjust MAX_MEMO_FIELD in dbf.h\n");
				value[1]=MAX_MEMO_FIELD;
			}
			if (read(memoHandle,memoBuffer,value[1])!=value[1])
			{
				//读出内容
				return NULL;
			}
			memoBuffer[value[1]]='\0';
			*pLength=value[1];
			return memoBuffer;
		}
		return NULL;
	}
	else
	{
		return pBuffer;
	}
}

char *CDBF::getField(int fieldno,int recno,short *pLength)
{
	char *pBuffer;
	if (!opened)
	{
		//没有打开文件
		return NULL;
	}
	if ((recno<1)||(recno>recCount))
	{
		//记录号越界
		return NULL;
	}
	if (lseek(handle,startPos+recWidth*(recno-1),SEEK_SET)==-1)
	{
		//找不到DBF文件中的位置
		return NULL;
	}
	if (read(handle,recBuffer,recWidth)!=recWidth)
	{
		//数据读不出来
		return NULL;
	}
	if (recBuffer[0]=='*')
	{
		//已经删除的记录
		*pLength=0;
		return "";
	}
	
	//已经找到该字段了
	pBuffer=recBuffer+(fieldDefines[fieldno].offset);
	*pLength=fieldDefines[fieldno].length;
	pBuffer[*pLength]='\0';

	//消除两边的空格字符
	pBuffer=rTrim(pBuffer);
	pBuffer=lTrim(pBuffer);
	
	return pBuffer;
}

char *CDBF::getField(int fieldno,int recno)
{
	char *pBuffer;
	if (!opened)
	{
		//没有打开文件
		return NULL;
	}
	if ((recno<1)||(recno>recCount))
	{
		//记录号越界
		return NULL;
	}
	if (lseek(handle,startPos+recWidth*(recno-1),SEEK_SET)==-1)
	{
		//找不到DBF文件中的位置
		return NULL;
	}
	if (read(handle,recBuffer,recWidth)!=recWidth)
	{
		//数据读不出来
		return NULL;
	}
	if (recBuffer[0]=='*')
	{
		//已经删除的记录
		return "";
	}
	
	//已经找到该字段了
	pBuffer=recBuffer+(fieldDefines[fieldno].offset);
	pBuffer[fieldDefines[fieldno].length]='\0';

	//消除两边的空格字符
	pBuffer=rTrim(pBuffer);
	pBuffer=lTrim(pBuffer);
	
	return pBuffer;
}

char* CDBF::getFieldName(int recno)
{
   if(recno > fieldCount-1)
   	return NULL;
   return fieldDefines[recno].name;
}
unsigned char CDBF::getFieldLength1(int recno)
{
   if(recno > fieldCount-1)
   	return NULL;
   return fieldDefines[recno].length1;
}
unsigned char CDBF::getFieldLength2(int recno)
{
   if(recno > fieldCount-1)
   	return NULL;
   return fieldDefines[recno].length2;
}

short CDBF::getFieldLength(int recno)
{
   if(recno > fieldCount-1)
   	return NULL;
   return fieldDefines[recno].length;
}
int CDBF::setField(char *fieldName,int recno,char *value,short length)
{
	short i;
	if (!opened)
	{
		//没有打开文件
		return 0;
	}
	if ((recno<1)||(recno>recCount))
	{
		//记录号越界
		return 0;
	}
	for (i=0;i<fieldCount;i++)
	{
		if (!strcmp(fieldDefines[i].name,fieldName))
			break;
	}
	if (i==fieldCount)
	{
		//字段没有找到
		return 0;
	}
	if (lseek(handle,startPos+recWidth*(recno-1)+fieldDefines[i].offset,SEEK_SET)==-1)
	{
		//找不到DBF文件中的位置
		return 0;
	}
	if (length==0)
	{
		length=fieldDefines[i].length;
	}
	if (write(handle,value,length)!=length)
	{
		//无法写入
		return 0;
	}
	return 1;
}

int CDBF::deleteRecord(int recno)
{
	if (!opened)
	{
		//没有打开文件
		return 0;
	}
	if ((recno<1)||(recno>recCount))
	{
		//记录号越界
		return 0;
	}
	if (lseek(handle,startPos+recWidth*(recno-1),SEEK_SET)==-1)
	{
		//找不到DBF文件中的位置
		return 0;
	}
	if (write(handle,"*",1)!=1)
	{
		//无法写入标记
		return 0;
	}
	return 1;
}

int CDBF::isDeletedRecord(int recno)
{
	char mark;
	if (!opened)
	{
		//没有打开文件
		return -1;
	}
	if ((recno<1)||(recno>recCount))
	{
		//记录号越界
		return -1;
	}
	if (lseek(handle,startPos+recWidth*(recno-1),SEEK_SET)==-1)
	{
		//找不到DBF文件中的位置
		return -1;
	}
	if (read(handle,&mark,1)!=1)
	{
		//读不出标记
		return -1;
	}
	if (mark=='*')
	{
		return 1;
	}
	return 0;
}

int CDBF::recallRecord(int recno)
{
	if (!opened)
	{
		//没有打开文件
		return -1;
	}
	if ((recno<1)||(recno>recCount))
	{
		//记录号越界
		return -1;
	}
	if (lseek(handle,startPos+recWidth*(recno-1),SEEK_SET)==-1)
	{
		//找不到DBF文件中的位置
		return -1;
	}
	if (write(handle," ",1)!=1)
	{
		//无法清除标记
		return 0;
	}
	return 1;
}

static int compare_string(char *s1,char *s2,int length)
{
	int result=strncmp(s1,s2,length);
	if (result>0)
		return 1;
	else if (result<0)
		return -1;
	return 0;
}

int CDBF::locateField(char *fieldName,int startRecno,char *value,short length)
{
	int recno=startRecno;
	if (!opened)
	{
		//没有打开文件
		return 0;
	}
	if ((startRecno<1)||(startRecno>recCount))
	{
		//记录号越界
		return 0;
	}
	while (recno<=recCount)
	{
		char *theFieldValue;
		short valueLength;
		theFieldValue=getField(fieldName,recno,&valueLength);
		if (!compare_string(value,theFieldValue,length))
		{
			return recno;
		}
		recno++;
	}
	return 0;
}

int CDBF::seekField(char *fieldName,int startRecno,int endRecno,char *value,short length)
{
	int left,right,mid;
	if (!opened)
	{
		//没有打开文件
		return 0;
	}
	if (startRecno==0)
		startRecno=1;
	if (endRecno==0)
		endRecno=recCount;
	if ((startRecno<1)||(startRecno>recCount))
	{
		//记录号越界
		return 0;
	}
	if ((endRecno<1)||(endRecno>recCount))
	{
		//记录号越界
		return 0;
	}
	left=startRecno;
	right=endRecno;
	while (left<=right)
	{
		char *theFieldValue;
		short valueLength;
		mid=(left+right)/2;
		theFieldValue=getField(fieldName,mid,&valueLength);
		switch (compare_string(value,theFieldValue,length))
		{
			case -1:
			case 0:
				right=mid-1;
				break;
			case 1:
				left=mid+1;
				break;
			default:
				return 0;
		}
	}
	if (left>endRecno)
		return 0;
	return left;
}

int CDBF::appendRecord(void)
{
	int recCountBuffer;
	int length;
	if (!opened)
	{
		//没有打开文件
		return 0;
	}
	if (lseek(handle,startPos+recWidth*(recCount),SEEK_SET)==-1)
	{
		//找不到DBF文件中的位置
		return 0;
	}
	length=recWidth;
	memset(recBuffer,' ',length);
	if (write(handle,recBuffer,length)!=length)
	{
		//无法写入文件
		return 0;
	}
	recCount++;
	recCountBuffer=recCount;
	if (endian_type==BIG_ENDIAN)
	{
		swap_int(&recCountBuffer);
	}
	if (lseek(handle,4,SEEK_SET)==-1)
	{
		//找不到DBF文件中的位置
		return 0;
	}
	if (write(handle,&recCountBuffer,4)!=4)
	{
		//无法写入文件
		return 0;
	}
	return 1;
}


CFieldDefine *CDBF::getFieldDefine(char *fieldName)
{
	int i;
	if (!opened)
	{
		//没有打开文件
		return 0;
	}
	for (i=0;i<fieldCount;i++)
	{
		if (!strcmp(fieldDefines[i].name,fieldName))
			break;
	}
	if (i==fieldCount)
	{
		//找不到字段
		return NULL;
	}
	return &(fieldDefines[i]);
}

int CDBF::setCharacterField(char *fieldName,int recno,char *value)
{
	int length;
	CFieldDefine *pFieldDefine;
	if (!opened)
	{
		//没有打开文件
		return 0;
	}
	pFieldDefine=getFieldDefine(fieldName);
	if (pFieldDefine==NULL)
	{
		//找不到字段定义
		return 0;
	}
	if (pFieldDefine->type!='C')
	{
		//不是字符类型
		return 0;
	}
	length=pFieldDefine->length;
	sprintf(recBuffer,"%-*.*s",length,length,value);
	return setField(fieldName,recno,recBuffer,0);
}

int CDBF::setIntField(char *fieldName,int recno,int value)
{
	int length;
	CFieldDefine *pFieldDefine;
	if (!opened)
	{
		//没有打开文件
		return 0;
	}
	pFieldDefine=getFieldDefine(fieldName);
	if (pFieldDefine==NULL)
	{
		//找不到字段定义
		return 0;
	}
	if (pFieldDefine->type!='N')
	{
		//不是数值类型
		return 0;
	}
	if (pFieldDefine->length2!=0)
	{
		//有小数部分
		return 0;
	}
	length=pFieldDefine->length1;
	sprintf(recBuffer,"%*ld",length,value);
	return setField(fieldName,recno,recBuffer,0);
}

int CDBF::setDoubleField(char *fieldName,int recno,double value)
{
	int length;
	CFieldDefine *pFieldDefine;
	if (!opened)
	{
		//没有打开文件
		return 0;
	}
	pFieldDefine=getFieldDefine(fieldName);
	if (pFieldDefine==NULL)
	{
		//找不到字段定义
		return 0;
	}
	if (pFieldDefine->type!='N')
	{
		//不是数值类型
		return 0;
	}
	length=pFieldDefine->length1;
	if(value >= DOUBLE_NaN)
	{
		sprintf(recBuffer,"%*s",length,"");
	}
	else
	{
		sprintf(recBuffer,"%*.*lf",length,pFieldDefine->length2,value);
	}
	
	return setField(fieldName,recno,recBuffer,0);
}

int CDBF::setDateField(char *fieldName,int recno,char *value)
{
	CFieldDefine *pFieldDefine;
	if (!opened)
	{
		//没有打开文件
		return 0;
	}
	pFieldDefine=getFieldDefine(fieldName);
	if (pFieldDefine==NULL)
	{
		//找不到字段定义
		return 0;
	}
	if (pFieldDefine->type!='D')
	{
		//不是日期类型
		return 0;
	}
	sprintf(recBuffer,"%8.8s",value);
	return setField(fieldName,recno,recBuffer,0);
}

int CDBF::setAnyField(char *fieldName,int recno,char *value)
{
	CFieldDefine *pFieldDefine;
	if (!opened)
	{
		//没有打开文件
		return 0;
	}
	pFieldDefine=getFieldDefine(fieldName);
	if (pFieldDefine==NULL)
	{
		//找不到字段定义
		return 0;
	}
	switch (pFieldDefine->type)
	{
		case 'C':
			return setCharacterField(fieldName,recno,value);
		case 'N':
			return setIntField(fieldName,recno,atol(value));
		case 'D':
			return setDateField(fieldName,recno,value);
		default:
			return 0;
	}
}

int CDBF::getRecCount(void)
{
	return recCount;
}

int CDBF::getYear(void)
{
	//return year+2000;
	int iyear;
	if (year<70) 
		iyear = 100+year;
	else
		iyear = year;
    return (iyear+1900);
}
	
char CDBF::getMonth(void)
{
	return month;
}
	
char CDBF::getDay(void)
{
	return day;
}

int CDBF::getDate()
{
	int iyear;
	if (year<70) 
		iyear = 100+year;
	else
		iyear = year;
	return(10000*(iyear+1900)+100*month+day);
}

	
int CDBF::getRecWidth(void)
{
	return recWidth;
}

int CDBF::getFieldCount(void)
{
	return fieldCount;
}
	
CFieldDefine *CDBF::getFieldDefines(short *pFieldCount)
{
	if (pFieldCount!=NULL)
	{
		*pFieldCount=fieldCount;
	}
	return fieldDefines;
}

int CDBF::getReccount()
{
	return recCount;
}

int CDBF::readRecords(DWORD from,int records,void *buf)
{
	int begin = startPos + (from-1)*recWidth;
	int offset = records * recWidth;
	lseek(handle,begin,SEEK_SET);
	if(read(handle,buf,offset)!=offset)
		return 0;
	return records;
}

char* CDBF::rTrim(char * pstring)
{
	int pstrLen = strlen(pstring);
	while(pstrLen > 0)
	{ 
		if(pstring[pstrLen-1]==0x20)
			pstrLen--;
		else
		{
			pstring[pstrLen]='\0';
			break;
		}	 
	}
	return pstring;
}

char* CDBF::lTrim(char * pstring)
{
	//由于消除时候是已经malloc的字符串，
	//其free不用pstring，所以利用将pstring 头向后移动的方法消除更为高效
	while(pstring[0]!='\0')
	{ 
		if(pstring[0]==0x20)
		{
			pstring = pstring + 1;
		}
		else
			break;
	}  
	return pstring;
}

void CDBF::printAll(void)
{
   printf("字段个数为:%d\n",getFieldCount());	
   printf("记录个数为:%d\n",getRecCount()); 
   printf("记录宽度为:%d\n",getRecWidth());
   printf("year:%d\n",getYear());
   printf("month:%c\n",getMonth());
   printf("day:%c\n",getDay());	
	
   printf("属性信息:\n");
   int fieldi=0;
   for(fieldi=0;fieldi<getFieldCount();fieldi++)
   {
     printf("%d=%s,%c,",fieldi+1,fieldDefines[fieldi].name,fieldDefines[fieldi].type);
	 printf("offset:%d, ",fieldDefines[fieldi].offset);
	 printf("length:%d   ",fieldDefines[fieldi].length);
   }
   printf("\n");
   for(int recordi=0;recordi<getRecCount();recordi++)
   {
     printf("第%d条记录:\n",recordi+1);
     for(int fieldi=0;fieldi<getFieldCount();fieldi++)
     	{
     	   short* shortp= new short;
		   char * field = getField(fieldDefines[fieldi].name,recordi+1,shortp);
     	   printf("%d=%s\n",fieldi+1,field);
     	}
	 printf("\n");
   }   
}

