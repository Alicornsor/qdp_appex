#ifndef _TmdbEngine_H__
#define _TmdbEngine_H__

#include "TMDBScheduler.h"
#include "XTPPackage.h"
#include "XTPPackage.h"
#include "XtpData.h"
#include "XtpPackageDesc.h"

class CTMDBEngine
{
public:
	CTMDBEngine(CTMDBScheduler *pTMDBSchulder,const char * pBrokers,const char * pExchanges);
	void handleMessage(CXTPPackage *pPackage);
	void ProcField(WORD fid,CFieldTypeIterator &itor,TTmdbActionType actType);
	void handleMemDBMsg(CXTPPackage *pPackage);
	bool BrokerCheck(CBrokerIDType brokerID);
	bool ExchangeCheck(CExchangeIDType exchangeID);
private:
    CTMDBScheduler	*m_pTMDBSchulder;
	DWORD			m_CurrTranID;
	vector<string> m_Exchanges;
	vector<string> m_Brokers;

	CSystemIDType m_SystemID;
};
#endif
