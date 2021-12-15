//////////////////////////////////////////////////////////////////////////
// 文件: ExchangeLinkManager.h
// 功能: 定义了报盘管理
// 历史: 20150525 huwp 
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
// 报盘管理线程
//////////////////////////////////////////////////

const int MAXEXCHID = 20;//支持最多交易所个数，实际上不仅仅是交易所，应该定义为输入流

class CExchangeLinkManager
{
public:
	///read request from pTReq,send response to pTSeries,read seat info from pConfig
	CExchangeLinkManager(char *pIniFileName,CConfig	*pConfig);
	virtual ~CExchangeLinkManager();

	virtual bool Init();

	//从一个席位信息初始化一个交易所链接
	void initLink(CSeatField *pSeatField);

	//初始化客户交易编码
	void initClientTradingID(CClientTradingIDField *pClientTradingIDField);

	CBaseExchApi *getExchangeLink(const char *pAPIID);
	CBaseExchApi *getExchangeLink(int apiID);
	//使用交易所和会员号找到通道，这里支持选择多个通道，按照平均分配的思想进行选择
	CBaseExchApi *getExchangeLink(CExchangeIDType Exchange,CParticipantIDType ParticipantID);

	CBaseExchApi *GetAPIIDByExchangIDUserID(CExchangeIDType exchangid,CUserIDType userid);

	void setBaseExchAPI(CBaseExchApi *baseExAPI,int apiID);

	int size(){return MAXEXCHID;};

	//启动各交易所报盘
	void StartWork();

	//20150620 xuzh 根据字符串得到api的号，这里是较为简单的算法，后续会使用复杂算法
	int GetAPIID(const char *pAPIID);

	int m_iMaxAPIID;
private:
	char m_pConfigFileName[128];
	CConfig *m_pConfig;
	vector<CSeatField *> m_InitSeatVec;//初始化席位的消息存储
	vector<int> m_IniSeatUsedVec;//Seat被选中次数的汇总
//	CBaseExchApi *m_ExchApiArryMap[MAXEXCHID];
	char tmpchar[512];
	bool m_bQueryBase;
	bool   m_bBase64;
};

#endif
