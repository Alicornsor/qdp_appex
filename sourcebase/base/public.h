#ifndef _PUBLIC_H
#define _PUBLIC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include "CBaseObject.h"

typedef int FTRESUTLT;

const FTRESUTLT FR_OK		= 0;
const FTRESUTLT FR_ERROR	= -1;
#define MAX_CPU_COUNT		128		// 当服务器上的CPU数量大于这个数字时，必须修改这个值 2015-03-18
#define CPU_LOAD_100_THREADS 2		// 这些CPU核心，用来绑定负载达到100%的线程

#define USER_PRODUCT_INFO_DUMPTOOL      "DUMP_TOOL"       //dumptool工具“用户端产品信息”
#ifdef LINUX
extern int g_n_cpucount;
extern int g_n_cpuindx;
extern bool g_bBindThreadsToCPU;
extern bool g_bBinded[MAX_CPU_COUNT];

extern void BindThd2CPU(pthread_t thdid,int ncpuid=-1);
#endif

struct ltstr
{
	bool operator()(const char* s1, const char* s2) const
	{
		return strcmp(s1, s2) < 0;
	}
};
//加上调试所用的打印函数
// extern void printTime(char* FuncName);

#endif
