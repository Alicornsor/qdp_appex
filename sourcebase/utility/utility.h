/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file utility.h
///@brief��������ϵͳ�����Եĺ���
///@history 
///20020214	 xuzh		�������ļ�
///20020330  xuzh		����DEBUG�õ�һЩ����
///20020411  xuzh		����һЩ�ж�����,����,ʱ��Ϸ���ʽ�ĺ���
/////////////////////////////////////////////////////////////////////////

#ifndef UTILITY_H
#define UTILITY_H

#include "platform.h"

#define IS_LESS_EQUAL_ZERO(a)		((a)<0.00000001)
#define IS_GREATER_EQUAL_ZERO(a) 	((a)>-0.00000001)
#define IS_LESS_ZERO(a) 			((a)<-0.00000001)
#define IS_GREATER_ZERO(a) 			((a)>0.00000001)
#define IS_EQUAL_ZERO(a)			((a)<0.00000001&&(a)>-0.00000001)
#define IS_NOTEQUAL_ZERO(a) 		((a)>0.00000001||(a)<-0.00000001)

#define IS_EQUAL_T(a,b) 	 		IS_EQUAL_ZERO(a-(b))
#define IS_GREATER_T(a,b) 			IS_GREATER_ZERO(a-(b))
#define IS_GREATER_EQUAL_T(a,b) 	IS_GREATER_EQUAL_ZERO(a-(b))
#define IS_LESS_T(a,b) 				IS_LESS_ZERO(a-(b))
#define IS_LESS_EQUAL_T(a,b) 		IS_LESS_EQUAL_ZERO(a-(b))
#define IS_NOTEQUAL_T(a,b) 			IS_NOTEQUAL_ZERO(a-(b))

///���һ���ַ�������Ŀո�
///@param	s	Ҫ����ո���ַ������ᱻ�ƻ�
///@return	�����ո���ַ�����һ���ַ����s
#define IS_SPACE(c)  ((c) == ' ' || (c) == '\t')
char *trim(char *s);

///��ȡ��ǰ��ϵͳʱ�䣬�Գ���ʽ��ʽ����
///@return	�Գ���ʽ��ʽ�����ĵ�ǰʱ��
char *getLongTime(void);

///��ȡ��ǰ��ϵͳʱ�䣬�Զ̸�ʽ��ʽ����
///@return	�Զ̸�ʽ��ʽ�����ĵ�ǰʱ��
char *getShortTime(void);

/*
///�����ǹ�ҫ������

///��filename,��ΪDEBUG�ļ����
///����0:�ɹ�
///����:ʧ��
int dbgOpen(char *strFileName); 

///���strBuffer��Ϣ��DEBUG�ļ���
int dbgPrint(char *strBuffer);

///�ر�debug�ļ�
int dbgClose();

///�õ�debug���ļ�
FILE *getFpDebugOutput();


///�ڶ���DEBUG_LOG������¶������з��� ,������ΪNULL
#ifdef DEBUG_LOG
#define DBG_OPEN(s)     dbgOpen(s)
#define DBG_STRING(s)	\
	{					\
		FILE *fp = getFpDebugOutput();\
		fprintf(fp, "[%s]:%s:%d\n", getLongTime(),__FILE__,__LINE__);\
		fprintf(fp,"%s",s!=NULL?s:"The String is NULL, Please check your program\n");\
		fflush(fp);\
	}	
				
#define DBG_CLASS(p) 	\
	{					\
		FILE *fp = getFpDebugOutput();\
		fprintf(fp, "[%s]:%s:%d\n", getLongTime(),__FILE__,__LINE__);\
		if(p!=NULL)   \
			(p)->dump(fp);\
		else \
			fprintf(fp,"The Class Pointer is NULL, Please check your program\n");	\
		fflush(fp);\
	}	
#define DBG_CLOSE	dbgClose	
#else
#define DBG_OPEN(s)		NULL
#define DBG_STRING(s)	NULL				
#define DBG_CLASS(p) 	NULL
#define DGB_CLOSE		NULL
#endif

#ifdef _DEBUG
#define TRACE0(sz)				{printf("[%s][%d] ",__FILE__,__LINE__);printf("%s",sz);}
#define TRACE1(sz, p1)          {printf("[%s][%d] ",__FILE__,__LINE__);printf(sz, p1);}
#define TRACE2(sz, p1, p2)      {printf("[%s][%d] ",__FILE__,__LINE__);printf(sz, p1, p2);}
#define TRACE3(sz, p1, p2, p3)  {printf("[%s][%d] ",__FILE__,__LINE__);printf(sz, p1, p2, p3);}
#else
#define TRACE0(sz)
#define TRACE1(sz, p1)
#define TRACE2(sz, p1, p2)
#define TRACE3(sz, p1, p2, p3)
#endif

#define TRACE	TRACE0
*/

/*
���ܣ� ��������str�Ƿ��Ƿ������±�׼����ֵ��
    û��С���������
    �����һ��С����ĸ�����
    ������TRIM���ܣ�����пո񣬷��ط�
return 0: ��
rerurn 1: ��
*/
int isValidNumber(char *s);

/*
���ܣ�����ַ����Ƿ�Ϸ������ڸ�ʽyyyymmdd
    ע���ȷ�ǺϷ������ڣ�����������229�Ŀ��ǣ�
���أ�
    return 0: ��
    rerurn 1: ��
 
*/
int isValidDate(char *s);

/*
���ܣ�����ַ����Ƿ�Ϸ���ʱ���ʽhhmmss
���أ�
    return 0: ��
    rerurn 1: ��
*/
int isValidTime(char *s);

/**���һ��IP��ַ�Ƿ���ָ��IP��ַƥ��
*@param pIpAddress �ַ�����ʾ��IP��ַ("xxx.xxx.xxx.xxx")
*@param pIpMatch �ַ�����ʾ��Ҫƥ���IP��ַ("xxx.xxx.xxx.xxx")
*@param pIpMask �ַ�����ʾ������("xxx.xxx.xxx.xxx")
*@return true ��ַƥ�� false ��ַ��ƥ��
*@remark
*/
bool CheckIpAddressMatch(const char *pIpAddress, 
						 const char *pIpMatch, 
						 const char *pIpMask);

/**���һ��IP��ַ�Ƿ���ָ��IP��ַƥ��
*@param pIpAddress ������ʾ��IP��ַ
*@param pIpMatch ������ʾ��Ҫƥ���IP��ַ
*@param pIpMask ������ʾ������
*@return true ��ַƥ�� false ��ַ��ƥ��
*@remark
*/
bool CheckIpAddressMatch(const unsigned long ulIpAddress, 
						 const unsigned long ulIpMatch, 
						 const unsigned long ulpMask);

///�ж������в����Ƿ�˵��Ӧ�����ûָ�ģʽ
///@param	argc	��������
///@param	argv	����ֵ��
///@return	true��ʾ�ǻָ�ģʽ��false��ʾ���ǻָ�ģʽ
bool isRecovery(int argc, char *argv[]);


char *base64_decode(const char *data, int data_len);
char *base64_encode(const char* data, int data_len);
#endif