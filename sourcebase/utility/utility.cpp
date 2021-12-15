/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file utility.h
///@briefʵ������ϵͳ�����Եĺ���
///@history 
///20020214	xuzh		�������ļ�
///20020330  ��ҫ��		����DEBUG�õ�һЩ����
///20020409  ��ҫ��		�޸�trim , ���⵽�˵�һ���ַ����ǿո��޷�trim�������
/////////////////////////////////////////////////////////////////////////

#include "platform.h"
#include "utility.h"

//static FILE *fpDebugOutput=NULL; ///����DEBUG�����֮��,��ΪNULL,����Ϊ��stdout

char* trim(char *str)
{
    if (str == NULL)
    {
        return NULL;
    }
 
    while(IS_SPACE(*str)) str++;
    int len = strlen(str);
    if (len == 0)
    {
        return str;
    }
    char *end = str + len - 1;
    while(IS_SPACE(*end)) end--;
    *(++end) = '\0';
    return str;
}


char *getLongTime(void)
{
	time_t ltime;
	struct tm *now;
	static char timeBuffer[21];
	
	time(&ltime);
	now=localtime(&ltime);
	
	struct timeb tb;
	ftime(&tb);
	sprintf(timeBuffer,"%04d%02d%02d%02d%02d%02d%02d",
		now->tm_year+1900,
		now->tm_mon+1,
		now->tm_mday,
		now->tm_hour,
		now->tm_min,
		now->tm_sec,
		tb.millitm/10);
	return timeBuffer;
}

char *getShortTime(void)
{
	time_t ltime;
	struct tm *now;
	static char timeBuffer[21];
	
	time(&ltime);
	now=localtime(&ltime);
	sprintf(timeBuffer,"%04d%02d%02d%02d%02d%02d",
		now->tm_year+1900,
		now->tm_mon+1,
		now->tm_mday,
		now->tm_hour,
		now->tm_min,
		now->tm_sec);
	return timeBuffer;
}

/*
int dbgOpen(char *strFileName){
	fpDebugOutput = mfopen(strFileName,"a+b");
	return 0;	
}

int dbgPrint(char *strBuffer)
{

	FILE *fp;
	fp = fpDebugOutput==NULL?stdout:fpDebugOutput;	
	fprintf(fp,"%s", strBuffer);
	fflush(fp);
	return 0;
	
}

int dbgClose()
{
	if (fpDebugOutput!=NULL){
		fclose(fpDebugOutput);
		fpDebugOutput=NULL;
	}	
	return 0;
}	

FILE *getFpDebugOutput()
{
	return  fpDebugOutput==NULL?stdout:fpDebugOutput;	

}
*/

 
int isValidNumber(char *str1)
/*
���ܣ� ��������str�Ƿ��Ƿ������±�׼����ֵ��
    û��С���������
    �����һ��С����ĸ�����
    ������TRIM���ܣ�����пո񣬷��ط�
return 0: ��
rerurn 1: ��
*/
{   
	char str[100];
	strcpy(str,str1);
	trim(str);
	int length=strlen(str);
    int dotnumber = 0,digitnumber = 0;
///���length==0���ط�
    if(length == 0 )
         return 0;
///���ÿһ���ַ������ֻ���С���㣬������С����ĸ���,��������쳣�ַ����Ҳ��������ţ�ֱ�ӷ��ط�
    for (int i=0;i < length ;i ++)
    {   if( !isdigit(str[i]))
        {   if( str[i] == '.' )
                dotnumber++;
            else
            {   if((str[i] == '-' || str[i] == '+')&& i == 0 )
                          ;
                else
                    return 0;
            }
        }
        else
            digitnumber ++;
    }
///���û�����֣����ط�
    if(digitnumber == 0)
        return 0;
///���С����ĸ�������һ���ط�
    if( dotnumber > 1)
        return 0;
///������
    return 1;
}
 

int isValidDate(char *str1)
/*
���ܣ�����ַ����Ƿ�Ϸ������ڸ�ʽyyyymmdd
    ע���ȷ�ǺϷ������ڣ�����������229�Ŀ��ǣ�
���أ�
    return 0: ��
    rerurn 1: ��
 
*/
{   
	char str[100];
	strcpy(str,str1);
	trim(str);

	
	int length=strlen(str);
    char buffer[10];
    struct tm time_check;
    int year, month, day;
///����ַ������Ȳ���ȷ��ֱ�ӷ���
    if(length != 8)
       return 0;
///���ÿһ���ַ�������
    for (int i=0;i < length ;i ++)
    {   if( !isdigit(str[i]))
                return 0;
    }
 
///�ж��������ںϷ��ķ�Χ�� 9999 > year > 1900 12 >= month >= 1 31>=day>=1
    memset(buffer,0,sizeof(buffer));
    memcpy(buffer,str,4);
    year = atoi(buffer);
    memset(buffer,0,sizeof(buffer));
    buffer[0]=str[4];
    buffer[1]=str[5];
    month = atoi(buffer);
    memset(buffer,0,sizeof(buffer));
    buffer[0]=str[6];
    buffer[1]=str[7];
    day = atoi(buffer);
///������Ч
    time_check.tm_year = year - 1900;
    time_check.tm_mon  = month - 1;
    time_check.tm_mday = day;
    time_check.tm_hour = 0;
    time_check.tm_min  = 0;
    time_check.tm_sec  = 1;
    time_check.tm_isdst = -1;
    if ( mktime(&time_check) == -1)
       return 0;
///ת��������Ӧ����ԭ�����ַ���һ��
    memset(buffer,0,sizeof(buffer));
    strftime(buffer,sizeof(buffer) - 1,"%Y%m%d",&time_check);
    if(strcmp(buffer,str)!=0)
      return 0;
    return 1;
}
 

int isValidTime(char *str)
/*
���ܣ�����ַ����Ƿ�Ϸ���ʱ���ʽhhmmss
���أ�
    return 0: ��
    rerurn 1: ��
*/
{
    int length=strlen(str);
    int result;
    char buffer[10];
    if(length != 6)
       return 0;
///���ÿһ���ַ�������
    for (int i=0;i < length ;i ++)
    {   if( !isdigit(str[i]))
                return 0;
    }
///��� 0<=hh<=23 0<=mm<=59 0<=ss<=59
    memset(buffer,0,sizeof(buffer));
    buffer[0]=str[0];
    buffer[1]=str[1];
    result = atoi(buffer);
    if(!(result >= 0 && result <=23))
       return 0;
    memset(buffer,0,sizeof(buffer));
    buffer[0]=str[2];
    buffer[1]=str[3];
    result = atoi(buffer);
    if(!(result >= 0 && result <=59))
       return 0;
    memset(buffer,0,sizeof(buffer));
    buffer[0]=str[4];
    buffer[1]=str[5];
    result = atoi(buffer);
    if(!(result >= 0 && result <=59))
       return 0;
   return 1;
}

bool CheckIpAddressMatch(const char *pIpAddress, 
						 const char *pIpMatch, 
						 const char *pIpMask)
{
	return CheckIpAddressMatch(inet_addr(pIpAddress), 
		inet_addr(pIpMatch),
		inet_addr(pIpMask));
}

bool CheckIpAddressMatch(const unsigned long ulIpAddress, 
						 const unsigned long ulIpMatch, 
						 const unsigned long ulpMask)
{
	return (ulIpAddress&ulpMask) == (ulIpMatch&ulpMask);
}

bool isRecovery(int argc, char *argv[])
{
	if (!strcmp(argv[argc-1],"recovery"))
	{
		return true;
	}
	return false;
}

/* */ 
static char find_pos(char ch)   
{ 
	const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="; 
    char *ptr = (char*)strrchr(base, ch);//the last position (the only) in base[] 
    return (ptr - base); 
} 
/* */ 

/* */ 
char *base64_decode(const char *data, int data_len) 
{ 
    int ret_len = (data_len / 4) * 3; 
    int equal_count = 0; 
    char *ret = NULL; 
    char *f = NULL; 
    int tmp = 0; 
    int temp = 0; 
    char need[3]; 
    int prepare = 0; 
    int i = 0; 
    if (*(data + data_len - 1) == '=') 
    { 
        equal_count += 1; 
    } 
    if (*(data + data_len - 2) == '=') 
    { 
        equal_count += 1; 
    } 
    if (*(data + data_len - 3) == '=') 
    {//seems impossible 
        equal_count += 1; 
    } 
    switch (equal_count) 
    { 
    case 0: 
        ret_len += 4;//3 + 1 [1 for NULL] 
        break; 
    case 1: 
        ret_len += 4;//Ceil((6*3)/8)+1 
        break; 
    case 2: 
        ret_len += 3;//Ceil((6*2)/8)+1 
        break; 
    case 3: 
        ret_len += 2;//Ceil((6*1)/8)+1 
        break; 
    } 
    ret = (char *)malloc(ret_len); 
    if (ret == NULL) 
    { 
        printf("No enough memory.\n"); 
        exit(0); 
    } 
    memset(ret, 0, ret_len); 
    f = ret; 
    while (tmp < (data_len - equal_count)) 
    { 
        temp = 0; 
        prepare = 0; 
        memset(need, 0, 4); 
        while (temp < 4) 
        { 
            if (tmp >= (data_len - equal_count)) 
            { 
                break; 
            } 
            prepare = (prepare << 6) | (find_pos(data[tmp])); 
            temp++; 
            tmp++; 
        } 
        prepare = prepare << ((4-temp) * 6); 
        for (i=0; i<3 ;i++ ) 
        { 
            if (i == temp) 
            { 
                break; 
            } 
            *f = (char)((prepare>>((2-i)*8)) & 0xFF); 
            f++; 
        } 
    } 
    *f = '\0'; 
    return ret; 
}


char *base64_encode(const char* data, int data_len) 
{ 
	const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="; 
    //int data_len = strlen(data); 
    int prepare = 0; 
    int ret_len; 
    int temp = 0; 
    char *ret = NULL; 
    char *f = NULL; 
    int tmp = 0; 
    char changed[4]; 
    int i = 0; 
    ret_len = data_len / 3; 
    temp = data_len % 3; 
    if (temp > 0) 
    { 
        ret_len += 1; 
    } 
    ret_len = ret_len*4 + 1; 
    ret = (char *)malloc(ret_len); 
	
    if ( ret == NULL) 
    { 
        printf("No enough memory.\n"); 
        exit(0); 
    } 
    memset(ret, 0, ret_len); 
    f = ret; 
    while (tmp < data_len) 
    { 
        temp = 0; 
        prepare = 0; 
        memset(changed, '\0', 4); 
        while (temp < 3) 
        { 
            //printf("tmp = %d\n", tmp); 
            if (tmp >= data_len) 
            { 
                break; 
            } 
            prepare = ((prepare << 8) | (data[tmp] & 0xFF)); 
            tmp++; 
            temp++; 
        } 
        prepare = (prepare<<((3-temp)*8)); 
        //printf("before for : temp = %d, prepare = %d\n", temp, prepare); 
        for (i = 0; i < 4 ;i++ ) 
        { 
            if (temp < i) 
            { 
                changed[i] = 0x40; 
            } 
            else 
            { 
                changed[i] = (prepare>>((3-i)*6)) & 0x3F; 
            } 
            *f = base[changed[i]]; 
            //printf("%.2X", changed[i]); 
            f++; 
        } 
    } 
    *f = '\0'; 
	
    return ret; 
	
} 