// Flow.cpp: implementation of the CFlow class.
//
//////////////////////////////////////////////////////////////////////

#include "public.h"
#include "Flow.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CFlow::CFlow()
{
}

CFlow::~CFlow()
{
}

/*
int CFlow::AppendPackage(CPackage *pPackage)
{
	return Append(pPackage->Address(), pPackage->Length());
}

int CFlow::GetPackage(int id, CPackage *pPackage)
{
	if(id<0 || id >= GetCount()){	//下标越界，无法取出对象
		return -1;
	}
	int len = Get(id, pPackage->Address(), pPackage->Length());

	if(len >= 0){
		pPackage->Truncate(len);
		return len;
	}

	return -1;
}

*/
