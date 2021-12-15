/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CBaseObject.cpp
///@brief实现了抽象的对象基类CBaseObject
///@history 
///20020212	xuzh		创建该文件
///20020214	xuzh		修改此文件，使checkType包含了文件名和行号
/////////////////////////////////////////////////////////////////////////

#include "CBaseObject.h"
#include "CLogger.h"

FILE *errorOutput=stderr;
int runLevel=1;

CBaseObject::CBaseObject(void)
{
}

CBaseObject::~CBaseObject(void)
{
}

int CBaseObject::isA(char *objectType)
{
	if (!strcmp(objectType,"CBaseObject"))
		return 1;
	return 0;
}

char *CBaseObject::getType(void)
{
	return "CBaseObject";
}

void CBaseObject::checkType(char *objectType, char *filename, int line)
{
	if (!isA(objectType))
	{
		throw (new CDesignError("Invalid Object",filename,line));
	}
}
/*
void CBaseObject::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CBaseObject");
}
*/
