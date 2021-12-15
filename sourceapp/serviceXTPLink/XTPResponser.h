#ifndef XTPRESPONSER_H
#define XTPRESPONSER_H
#include "ServiceXTPLink.h"
#include "Flow.h"
#include "FibServerApi.h"

class CXTPResponser:public IServiceResponser
{
public:
	CXTPResponser(CFlow *pFlow);
	virtual ~CXTPResponser(){};
	virtual void SendResponse(CXTPPackage *pPackage,DWORD dwSessionID = 0);
private:
	CFlow *m_pFlow;
};

class CXTPRequestResponser:public IServiceResponser
{
public:
	CXTPRequestResponser(CFibServerApi *pApi);
	virtual ~CXTPRequestResponser(){};
	virtual void SendResponse(CXTPPackage *pPackage,DWORD dwSessionID);
private:
	CFibServerApi *m_pServerApi;

};
#endif

