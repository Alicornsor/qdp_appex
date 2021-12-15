#ifndef _Processor_H
#define _Processor_H

#include "QdpFtdcUserApi.h"
#include "QdpFtdcUserApiStruct.h"
#include "platform.h"
#include "Semaphore.h"
#include "Mutex.h"
#include "CConfig.h"
#include "TypeDefine.h"

#ifdef WINDOWS
#pragma warning(disable:4786)
#endif
using namespace std;

class CProcessor:public CQdpFtdcUserSpi  
{
public:
	CProcessor(int iId);
	CProcessor(int iId,char *BrokerID,char *pUserID,char *pPassword,FILE* fOut,bool bUserType = false);
	~CProcessor();
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();
	
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason);
		
	virtual void OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�û���¼Ӧ��
	virtual void OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�û��˳�Ӧ��
	virtual void OnRspUserLogout(CQdpFtdcRspUserLogoutField *pRspUserLogout, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�û������޸�Ӧ��
	virtual void OnRspUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ǿ���û��˳�Ӧ��
//	virtual void OnRspForceUserExit(CQdpFtdcForceUserExitField *pForceUserExit, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�û��Ựɾ��Ӧ��
//	virtual void OnRspForceUserLogout(CQdpFtdcForceUserExitField *pForceUserExit, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����¼��Ӧ��
	virtual void OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��������Ӧ��
	virtual void OnRspOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ͷ�����ʽ��ʻ������Ӧ��
	virtual void OnRspAccountDeposit(CQdpFtdcRspAccountDepositField *pRspAccountDeposit, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����������֪ͨ
//	virtual void OnRtnFlowMessageCancel(CQdpFtdcFlowMessageCancelField *pFlowMessageCancel);

	///�ɽ��ر�
	virtual void OnRtnTrade(CQdpFtdcTradeField *pTrade);

	///�����ر�
	virtual void OnRtnOrder(CQdpFtdcOrderField *pOrder);

	///����¼�����ر�
//	virtual void OnErrRtnOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo);

	///������������ر�
//	virtual void OnErrRtnOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo);

	///��Լ����״̬֪ͨ
	virtual void OnRtnInstrumentStatus(CQdpFtdcInstrumentStatusField *pInstrumentStatus);

	///�˻������ر�
	virtual void OnRtnInvestorAccountDeposit(CQdpFtdcInvestorAccountDepositResField *pInvestorAccountDepositRes);

	///QDP������Ϣ֪ͨ
	virtual void OnRtnMessageNotify(CQdpFtdcMessageNotifyInfoField *pMessageNotifyInfo);

	///������ѯӦ��
	virtual void OnRspQryOrder(CQdpFtdcOrderField *pOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�ɽ�����ѯӦ��
	virtual void OnRspQryTrade(CQdpFtdcTradeField *pTrade, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����Ͷ�����˻���ѯӦ��
//	virtual void OnRspQryUserInvestor(CQdpFtdcRspUserInvestorField *pRspUserInvestor, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///���ױ����ѯӦ��
//	virtual void OnRspQryTradingCode(CQdpFtdcRspTradingCodeField *pRspTradingCode, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ͷ�����ʽ��˻���ѯӦ��
	virtual void OnRspQryInvestorAccount(CQdpFtdcRspInvestorAccountField *pRspInvestorAccount, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��Լ��ѯӦ��
	virtual void OnRspQryInstrument(CQdpFtdcRspInstrumentField *pRspInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��������ѯӦ��
//	virtual void OnRspQryExchange(CQdpFtdcRspExchangeField *pRspExchange, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ͷ���ֲֲ߳�ѯӦ��
	virtual void OnRspQryInvestorPosition(CQdpFtdcRspInvestorPositionField *pRspInvestorPosition, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�û���ѯӦ��
//	virtual void OnRspQryUser(CQdpFtdcUserField *pUser, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ͷ�����������ʲ�ѯӦ��
//	virtual void OnRspQryInvestorFee(CQdpFtdcInvestorFeeField *pInvestorFee, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ͷ���߱�֤���ʲ�ѯӦ��
//	virtual void OnRspQryInvestorMargin(CQdpFtdcInvestorMarginField *pInvestorMargin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///ѯ��¼��Ӧ��
// 	virtual void OnRspForQuoteInsert(CQdpFtdcInputForQuoteField *pInputForQuote, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
// 	
// 	///ѯ�۲�ѯӦ��
// 	virtual void OnRspQryForQuote(CQdpFtdcForQuoteField *pForQuote, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
// 	
// 	///ִ������¼��Ӧ��
// 	virtual void OnRspExecOrderInsert(CQdpFtdcInputExecOrderField *pInputExecOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
// 	
// 	///ִ���������Ӧ��
// 	virtual void OnRspExecOrderAction(CQdpFtdcExecOrderActionField *pExecOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
// 	
// 	///ִ������ر�
// 	virtual void OnRtnExecOrder(CQdpFtdcExecOrderField *pExecOrder);
// 	
// 	///ִ�������ѯӦ��
// 	virtual void OnRspQryExecOrder(CQdpFtdcExecOrderField *pExecOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

public:
	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	virtual void Init() ;
	virtual int Join();
	///��ȡ��ǰ������
	///@retrun ��ȡ���Ľ�����
	///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
	const char *GetTradingDay();
	///�û���¼����
	int ReqUserLogin(char *pBrokerID,char *pUser,char *pPassword);
	
	///ע��api

	int getApi();

	//����������ҵ������ͻر������ͽ�����û��ҵ�����ֱ��ʹ����
	void WaitAction(int nTimeOut);
	void EndAction();

	void Release();

	int  DealBusinessCmd(char *pOutFile,int argc,char **argv,int iStart,const int iTimeOut,bool bNoOut,int iTestValue);
	int  DealBusinessFile(char *pInFile,char *pOutFile,bool bNoOut);
	int  DealBusinessConsole(char *pConsoleStr,char *pOutFile,const int iTimeOut,bool bNoOut);
	void Output(const char *msg,...);

public:
	CQdpFtdcUserApi *m_pFfexFtdcUserApi;
	char m_sTradeRUL[50];
	int  m_iOrderResumeType;
	bool m_bTradeIsLogin;

	char m_sBrokerID[20];
	char m_sUserID[20];
	char m_sPassword[20];
//	char m_sParticipantID[20];

	int	 m_iLocalNo;
	int  m_nRequestID;
	int  m_nRecvCount;
	char *m_pInFile;
	CSemaphore m_semAction;
	FILE *m_fOutFile;
	int  m_iTotalRecordCnt;
	bool m_bFirstPackage;
	bool m_bNoOut;
	bool m_bConnected;
	CInstrumentStatusMap	m_InstrumentStatusMap;
	int m_iId;
	fpos_t m_fpsize;

	time_t m_lastTime;
//	CMutex m_mutexFlowControl;
	char  m_sLastOrderSysID[13];
	int   m_iRspValue;
	int   m_iCheckValue;
	bool  m_bWaitResult;
	//xuzh ÿ��req֮��sleep�ĺ�����
	int m_nSleepControl;
	//������������frontdisconnect���µ���Ҫ���µ�¼�����
	bool  m_bReLogin;
	//�Ƿ������ڷ���ʧ�����·��͵�ָ������
	bool  m_bResend;
	CConfig *m_pConfig;

	FILE	*m_fp_out;
};
#endif