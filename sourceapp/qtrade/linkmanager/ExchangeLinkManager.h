//////////////////////////////////////////////////////////////////////////
// �ļ�: ExchangeLinkManager.h
// ����: �����˱��̹���
// ��ʷ: 20150525 huwp 
//////////////////////////////////////////////////////////////////////////
#if !defined(EXCHANGE_API_MANAGER_H_20121119)
#define EXCHANGE_API_MANAGER_H_20121119

#include "CachedFlow.h"
#include "platform.h"
#include "CConfig.h"
#include "XTPPackage.h"
#include "FlowReader.h"
#include "ReqFlow.h"
#include "monitorIndex.h"
#include "errorDefine.h"
#include "XtpData.h"
#include "BaseExchApi.h"
#include "SelectReactor.h"

//////////////////////////////////////////////////
// ���̹����߳�
//////////////////////////////////////////////////

const int MAXEXCHID = 20;//֧����ཻ����������ʵ���ϲ������ǽ�������Ӧ�ö���Ϊ������

class CExchangeLinkManager
{
public:
	///read request from pTReq,send response to pTSeries,read seat info from pConfig
	CExchangeLinkManager(char *pIniFileName,CConfig	*pConfig);
	virtual ~CExchangeLinkManager();

	virtual bool Init();

	//��һ��ϯλ��Ϣ��ʼ��һ������������
	void initLink(CSeatField *pSeatField);

	//��ʼ���ͻ����ױ���
	void initClientTradingID(CClientTradingIDField *pClientTradingIDField);

	CBaseExchApi *getExchangeLink(const char *pAPIID);
	CBaseExchApi *getExchangeLink(int apiID);
	//ʹ�ý������ͻ�Ա���ҵ�ͨ��������֧��ѡ����ͨ��������ƽ�������˼�����ѡ��
	CBaseExchApi *getExchangeLink(CExchangeIDType Exchange,CParticipantIDType ParticipantID);

	CBaseExchApi *GetAPIIDByExchangIDUserID(CExchangeIDType exchangid,CUserIDType userid);

	void setBaseExchAPI(CBaseExchApi *baseExAPI,int apiID);

	int size(){return MAXEXCHID;};

	//����������������
	void StartWork();

	//20150620 xuzh �����ַ����õ�api�ĺţ������ǽ�Ϊ�򵥵��㷨��������ʹ�ø����㷨
	int GetAPIID(const char *pAPIID);

	int m_iMaxAPIID;
private:
	char m_pConfigFileName[128];
	CConfig *m_pConfig;
	vector<CSeatField *> m_InitSeatVec;//��ʼ��ϯλ����Ϣ�洢
	vector<int> m_IniSeatUsedVec;//Seat��ѡ�д����Ļ���
//	CBaseExchApi *m_ExchApiArryMap[MAXEXCHID];
	char tmpchar[512];
	bool m_bQueryBase;
	bool   m_bBase64;
};

#endif
