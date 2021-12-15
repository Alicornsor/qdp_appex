#ifndef NULLRESPONSER_H
#define NULLRESPONSER_H
#include "ServiceXTPLink.h"
#include "Flow.h"

class CNullResponser:public IServiceResponser
{
public:
	CNullResponser(CFlow *pFlow);
	virtual ~CNullResponser(){};
	virtual void SendResponse(CXTPPackage *pPackage,DWORD dwSession);
};
#endif

