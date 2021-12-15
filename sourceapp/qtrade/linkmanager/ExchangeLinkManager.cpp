//////////////////////////////////////////////////////////////////////////
// 文件: ExchangeApiManager.cpp
// 功能: 实现了报盘管理线程接口
// 历史: created by 姜源 20121120
//////////////////////////////////////////////////////////////////////////
#include "public.h"
#include "LockFileFlow.h"
#include "ExchangeLinkManager.h"
#include "XtpData.h"
#include "XtpPackageDesc.h"
#include "customDataType.h"
#include "FieldDescribe.h"
#include "UFCopy.h"
#include "FileFlow.h"
#include "Config.h"
#ifdef LINUX
#include <poll.h>
#endif
#include "BaseFunction.h"
#include "InnerTradeLink.h"
#include "QTestTradeLink.h"
#include "ApexTradeLink.h"
#ifdef APP_QQUERY
#include "QdpMDLink.h"
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern const char *APP_NAME;
extern const int MAXEXCHID;
extern CBaseExchApi *g_pExchApiArryMap[];//各交易所APImap
//extern CHashMap<DWORD, CBaseExchApi *, HashInt> m_ExchApiArryMap;
extern char *INI_FILE_NAME;
//extern vector<CSeatField *> m_InitSeatVec;//链接各个交易所的用户名和密码
//extern vector<CClientTradingIDField *> m_InitClientTradingIDVec;

// 下面这个版本号，不要轻易修改。 修改后，要把qdp这个版本到交易系统那边报备！ 通过适应性测试。2014-10-27


CExchangeLinkManager::CExchangeLinkManager(char *pIniFileName,CConfig *pConfig)
{	
	m_pConfig = pConfig;
	memset(m_pConfigFileName,0,sizeof(m_pConfigFileName));
	strncpy(m_pConfigFileName,pIniFileName,sizeof(m_pConfigFileName)-1);
//	memset(m_ExchApiArryMap,0,sizeof(m_ExchApiArryMap));
	memset(tmpchar,0,sizeof(tmpchar));
	m_iMaxAPIID = EX_PFRONT;
	m_bBase64 = false;
	if (!strcmp(m_pConfig->getConfig("Base64"),"yes"))
	{
		m_bBase64=true;
	}
}

CExchangeLinkManager::~CExchangeLinkManager()
{

}

bool CExchangeLinkManager::Init()
{
	return true;
}

void CExchangeLinkManager::initLink(CSeatField *pSeatField)
{
	//如果不活跃，则表示不连接
	if(pSeatField->IsActive == false)
	{
		return;
	}

	char * flowpathtmp = m_pConfig->getConfig("FlowPath");
	char flowpath[200]={0};
	strcpy(flowpath,flowpathtmp);	
	char linkflowpath[256]={0};
	sprintf(linkflowpath,"%s%s_%d",flowpath,pSeatField->ExchangeID.getValue(),pSeatField->APIID.getValue());

	if (m_bBase64)
	{
		int len = strlen(pSeatField->SeatPassword);
		pSeatField->SeatPassword = base64_decode(pSeatField->SeatPassword.getValue(), len);
	}
	switch(pSeatField->ApiLinkType)
	{
	case ALT_APEX:
	case ALT_QDPTEST:
		{
			CBaseExchApi *pTradeLink = NULL;
			if(pSeatField->ApiLinkType == ALT_APEX)
			{
				pTradeLink = new CApexTradeLink(linkflowpath);
			}
			else
			{
				pTradeLink = new CQTestTradeLink(linkflowpath);
			}
			//解析格式为: f=tcp://192.168.1.3:7200,f=tcp://192.168.1.3:7200,e=tcp://192.168.1.3:7200,e=tcp://192.168.1.3:7200

			vector<string> addrs=Txtsplit(pSeatField->FrontAddr.getValue(),",");

			for(int i=0;i<addrs.size();i++)
			{
				char eachAddr[512]={0};
				strncpy(eachAddr,addrs[i].c_str(),addrs[i].size());
				if(eachAddr[0]=='f')
				{
					pTradeLink->SetFrontIp(eachAddr+2);
				}
				if(eachAddr[0]=='e')
				{
					pTradeLink->SetFensIp(eachAddr+2);
				}
			}

			pTradeLink->InitSeatInfo(pSeatField);
			g_pExchApiArryMap[pSeatField->APIID] = pTradeLink;			
			break;
		}
#ifdef APP_QQUERY
	case ALT_QDPMD:
	{
		CQdpMDLink *pQdpMDLink = new CQdpMDLink(linkflowpath);
		pQdpMDLink->SetFrontIp(pSeatField->FrontAddr);	
		pQdpMDLink->InitSeatInfo(pSeatField);
		g_pExchApiArryMap[pSeatField->APIID] = pQdpMDLink;			
		break;
	}
#endif
	default:
		{
			REPORT_EVENT(LOG_CRITICAL,"Seat's ExchangeID error:[%s]",pSeatField->ExchangeID.getValue());
			break;
		}
	}

	CSeatField *pField = new CSeatField;
	memcpy(pField,pSeatField,sizeof(CSeatField));
	m_InitSeatVec.push_back(pField);
	m_IniSeatUsedVec.push_back(0);
	if (pField->APIID > m_iMaxAPIID)
	{
		m_iMaxAPIID = pField->APIID.getValue();
	}
}

void CExchangeLinkManager::initClientTradingID(CClientTradingIDField *pClientTradingIDField)
{
	//从2开始，从真正的交易所席位开始
	for (int i=2;i<MAXEXCHID;i++)
	{
		CBaseExchApi *pBaseExchApi = g_pExchApiArryMap[i];
		if(pBaseExchApi == NULL )
		{
			continue;
		}
		
		if(pBaseExchApi->m_Seat.ExchangeID!=pClientTradingIDField->ExchangeID)
		{
			continue;
		}

		if (!pBaseExchApi->InitClientIDSet(pClientTradingIDField->ClientID.getValue()))
		{
			continue;
		}

		//如果不是查询席位，无需ClientTradingID
		//modifed by chengm InnerLink需要推送ClientTradingID
		if(pBaseExchApi->m_Seat.ApiLinkType != ALT_INNER &&
			 !pBaseExchApi->m_Seat.QueryBase)
		{
			continue;
		}
		pBaseExchApi->InitClientTradingID(pClientTradingIDField);
	}
}

CBaseExchApi *CExchangeLinkManager::getExchangeLink(const char *pAPIID)
{
	int apiID=GetAPIID(pAPIID);
	if(apiID < 0)
	{
		return NULL;
	}
	CBaseExchApi *pBaseExchApi = g_pExchApiArryMap[apiID];
	return pBaseExchApi;
}

CBaseExchApi *CExchangeLinkManager::getExchangeLink(int apiID)
{
	if (apiID<0 || apiID>=MAXEXCHID)
	{
		return NULL;
	}
	CBaseExchApi *pBaseExchApi = g_pExchApiArryMap[apiID];
	return pBaseExchApi;
}

CBaseExchApi *CExchangeLinkManager::getExchangeLink(CExchangeIDType Exchange,CParticipantIDType ParticipantID)
{
	//这里的选择是使用平均算法，使得席位被使用的次数基本均等
	//算法是：每选择一次，就会增加使用次数一次，下次选择时，使用次数最少的作为选择结果
	
	int MinUsed = INT_MAX;
	CBaseExchApi *pBaseExchApi = NULL;
	int ChosedSeat = -1;
	for(int i=0;i<m_InitSeatVec.size();i++)
	{
		CSeatField *pSeatField = m_InitSeatVec[i];
		if(pSeatField->ExchangeID == Exchange && pSeatField->ParticipantID== ParticipantID)
		{
			CBaseExchApi *pTmpBaseExchApi = getExchangeLink(pSeatField->APIID.getValue());
			if(pTmpBaseExchApi!=NULL)
			{
				if(m_IniSeatUsedVec[i] < MinUsed)
				{
					MinUsed = m_IniSeatUsedVec[i];
					ChosedSeat = i;
					pBaseExchApi = pTmpBaseExchApi;
				}
			}
		}
	}
	
	//将选中的席位的使用次数增加
	if(ChosedSeat>=0)
	{
		m_IniSeatUsedVec[ChosedSeat]++;
	}
	
	return pBaseExchApi;
}

void CExchangeLinkManager::setBaseExchAPI(CBaseExchApi *baseExAPI,int apiID)
{
	g_pExchApiArryMap[apiID]=baseExAPI;
}

//启动各交易所报盘
void CExchangeLinkManager::StartWork()
{
	int i=0;
	for(i = 2;i<MAXEXCHID;i++)
	{
		CBaseExchApi *pBaseExchApi = g_pExchApiArryMap[i];
		if(pBaseExchApi != NULL && !pBaseExchApi->m_bCheckLinked)
		{	
			pBaseExchApi->StartWork();			
		}		
	}
}

//20150620 xuzh 根据字符串得到api的号，这里是较为简单的算法，后续会使用复杂算法
int CExchangeLinkManager::GetAPIID(const char *pAPIID)
{
	int i=0;
	for(i=0;i<m_InitSeatVec.size();i++)
	{
		CSeatField *pSeatField = m_InitSeatVec[i];
		if(pSeatField->ExchangeID == pAPIID)
		{
			return m_InitSeatVec[i]->APIID;
		}
	}
	return -1;
}

//由exchangid和userid匹配到合适的apiid
CBaseExchApi *CExchangeLinkManager::GetAPIIDByExchangIDUserID(CExchangeIDType exchangid,CUserIDType userid)
{
	int i=0;
	for(i=0;i<m_InitSeatVec.size();i++)
	{
		CSeatField *pSeatField = m_InitSeatVec[i];
		if( pSeatField->ExchangeID == exchangid && strstr(pSeatField->Custom.getValue(),userid.getValue()) != NULL )
		{
			CBaseExchApi *pTmpBaseExchApi = getExchangeLink(pSeatField->APIID.getValue());
			if(pTmpBaseExchApi!=NULL)
			{
				return pTmpBaseExchApi;
			}
		}
	}
	return NULL;
}