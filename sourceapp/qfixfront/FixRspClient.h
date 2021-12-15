#include "FrontTerminalCallback.h"
#include "FixServerSession.h"
#include "XtpPackageDesc.h"
#include "XTPPackage.h"
#include "customDataType.h"
#include "IndexPackageFlow.h"
#include "FixEngine.h"

struct UserOrderMap {
	
};


class FixRspClient : public CFrontTerminalCallback
{
public:
	FixRspClient(CFixEngine * m_fixEngine);
	//FixRspClient(CReactor *pReactor, CSelectReactor* pConnReactor);
	virtual ~FixRspClient();
	virtual void HandleMessage(CXTPPackage *pMessage);
	virtual void OnResponse(CXTPPackage *pPackage);
	bool DispatcherEvent(int nEventID, DWORD dwParam, void *pParam);

public:
	void SendRtnTrade(CTradeField* pField);
	void SendRtnOrder(COrderField* pField);
	void OnRspFixUserLogin(CXTPPackage * pMessage);
	void OnRspFixOrderInsert(CXTPPackage *pMessage);
	void OnRspFixUserLogout(CXTPPackage * pMessage);
	void OnRspFixOrderAction(CXTPPackage * pMessage);
	void OnRspQryInstrument(CXTPPackage * pMessage);

	void OnRspFixUserMargin(CXTPPackage * pMessage);
	void OnRspFixUserPosition(CXTPPackage * pMessage);
	void OnRspFixAccountData(CXTPPackage * pMessage);
	void OnRspFixOrderMassStatus(CXTPPackage * pMessage);
	void OnRspFixUserPasswd(CXTPPackage * pMessage);
	void OnRspFixAvailableAccount(CXTPPackage * pMessage);
	void OnRspFixFee(CXTPPackage * pMessage);
	
	void OnRspFillOrder(CTradeField* pField, string& fixsession, CRspInfoField* rspInfoField);
	void OnRspOrder(COrderField* pField, string& fixsession, CRspInfoField* rspInfoField);

private:
	CFixEngine * m_fixEngine;

};




