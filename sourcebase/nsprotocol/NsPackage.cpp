// NsPackage.cpp: implementation of the CNsPackage class.
//
// 20090803 hwp NT-0087:修正NsPackage报文长度错误导致的fens死机问题
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "NsPackage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNsPackage::CNsPackage()
{

}

CNsPackage::~CNsPackage()
{

}

DWORD CNsPackage::GetActiveID()
{
	return 0;
}

int CNsPackage::ValidPackage()
{
	if (Length() > NS_PACKAGE_MAX_SIZE)
	{
		return -2;
	}
	for (char *p=m_pHead; p<m_pTail; p++)
	{
		if (*p == '\0')
		{
			return p-m_pHead+1;
		}
	}
	return -1;
}
	
int CNsPackage::MakePackage()
{
	return 0;
}
