#ifndef __PRINTINFO_H_
#define __PRINTINFO_H_

#include "platform.h"

#define  SEP_CHAR ','
#define MSG_INFO	1
#define MSG_WARN	2
#define MSG_ERROR	3
#define MSG_FATAL	4


char *getTime(void);
char *getCurrDate(void);
char *getMachineName(void);
char *getCurrTime(void);
void printInfo(int level,char *sCppName,char* pFormat, ...);
int CheckTime(char* localtime, char *sTime);
int ReplaceStr(char *sSrc, char *sMatchStr, char *sReplaceStr);
#endif
