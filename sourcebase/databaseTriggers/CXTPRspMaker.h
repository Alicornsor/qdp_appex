#ifndef XTPRSPMAKER_H
#define XTPRSPMAKER_H
#include "XTPPackage.h"

class CXTPRspMaker
{
public:
	CXTPRspMaker(){
		m_pRspMessage = new CXTPPackage;
		m_pRspMessage->ConstructAllocate(XTP_PACKAGE_MAX_SIZE,1000);
	}

	virtual ~CXTPRspMaker(){
		delete m_pRspMessage;	
	}
protected:
	CXTPPackage	 *m_pRspMessage;
};

#endif