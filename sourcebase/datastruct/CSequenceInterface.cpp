/////////////////////////////////////////////////////////////////////////
///@system 量投系统基础库
///@company 上海量投网络科技有限公司
///@file CSequenceInterface.cpp
///@brief实现了类CSequenceInterface
///@history 
///20041001	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CSequenceInterface.h"

CSequenceInterface::CSequenceInterface()
{
}

CSequenceInterface::~CSequenceInterface(void)
{
	CHECK_TYPE("CSequenceInterface");
}

int CSequenceInterface::isA(char *objectType)
{
	if (!strcmp(objectType,"CSequenceInterface"))
		return 1;
	return CSequenceInterface::isA(objectType);
}

char *CSequenceInterface::getType(void)
{
	return "CSequenceInterface";
}
