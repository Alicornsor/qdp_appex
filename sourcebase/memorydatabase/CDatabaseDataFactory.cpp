/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file CDatabaseDataFactory.cpp
///@brief实现了类CDatabaseDataFactory
///@history 
///20020214	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CDatabaseDataFactory.h"


CDatabaseDataFactory::CDatabaseDataFactory(int unitSize, int maxUnit,IMemoryAllocator *pAllocator,bool reuse, int reuseID, int readOnly)
{
	if(maxUnit == 0)	///如果为0，则认为是缺省值
		maxUnit = MDB_DEFAULT_BLOCK_SIZE;
	pMem=new CFixMem(unitSize,maxUnit,pAllocator,reuse,reuseID,readOnly);
	if (pMem==NULL)
		RAISE_RUNTIME_ERROR("Insufficient memory space");
	this->maxUnit=maxUnit;
}

CDatabaseDataFactory::~CDatabaseDataFactory(void)
{
	CHECK_TYPE("CDatabaseDataFactory");
	delete pMem;
}

int CDatabaseDataFactory::isA(char *objectType)
{
	if (!strcmp(objectType,"CDatabaseDataFactory"))
		return 1;
	return CBaseObject::isA(objectType);
}

char *CDatabaseDataFactory::getType(void)
{
	return "CDatabaseDataFactory";
}

void CDatabaseDataFactory::output(CLogger *pLogger,int indent)
{
	CHECK_TYPE("CDatabaseDataFactory");
	pLogger->output(indent,0,"CDatabaseDataFactory:max_unit=%d",maxUnit);
	pMem->output(pLogger,indent+1);
}

void CDatabaseDataFactory::clearAll(void)
{
	pMem->freeAll();
}

int	CDatabaseDataFactory::getReuseID()
{
	return pMem->GetReuseID();
}
