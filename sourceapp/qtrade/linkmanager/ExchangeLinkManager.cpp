//////////////////////////////////////////////////////////////////////////
// �ļ�: ExchangeApiManager.cpp
// ����: ʵ���˱��̹����߳̽ӿ�
// ��ʷ: created by ��Դ 20121120
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
extern CBaseExchApi *g_pExchApiArryMap[];//��������APImap
//extern CHashMap<DWORD, CBaseExchApi *, HashInt> m_ExchApiArryMap;
extern char *INI_FILE_NAME;
//extern vector<CSeatField *> m_InitSeatVec;//���Ӹ������������û���������
//extern vector<CClientTradingIDField *> m_InitClientTradingIDVec;

// ��������汾�ţ���Ҫ�����޸ġ� �޸ĺ�Ҫ��qdp����汾������ϵͳ�Ǳ߱����� ͨ����Ӧ�Բ��ԡ�2014-10-27


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
	//�������Ծ�����ʾ������
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
			//������ʽΪ: f=tcp://192.168.1.3:7200,f=tcp://192.168.1.3:7200,e=tcp://192.168.1.3:7200,e=tcp://192.168.1.3:7200

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
	//��2��ʼ���������Ľ�����ϯλ��ʼ
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

		//������ǲ�ѯϯλ������ClientTradingID
		//modifed by chengm InnerLink��Ҫ����ClientTradingID
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
	//�����ѡ����ʹ��ƽ���㷨��ʹ��ϯλ��ʹ�õĴ�����������
	//�㷨�ǣ�ÿѡ��һ�Σ��ͻ�����ʹ�ô���һ�Σ��´�ѡ��ʱ��ʹ�ô������ٵ���Ϊѡ����
	
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
	
	//��ѡ�е�ϯλ��ʹ�ô�������
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

//����������������
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

//20150620 xuzh �����ַ����õ�api�ĺţ������ǽ�Ϊ�򵥵��㷨��������ʹ�ø����㷨
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

//��exchangid��useridƥ�䵽���ʵ�apiid
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