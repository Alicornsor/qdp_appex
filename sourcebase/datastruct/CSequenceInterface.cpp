/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CSequenceInterface.cpp
///@briefʵ������CSequenceInterface
///@history 
///20041001	xuzh		�������ļ�
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
