///////////////////////////////////////////////////////////////////////////////////////
//slogparser.cpp
//
//20071226 hwp	����ʹ��-a���������OFP����������/Ӧ��ʱ��
//20080109 hwp	1.����-e������ָ����������ļ�
//					2.�޸�-a����������ָ�����RTT����Ҫ��ı�������/Ӧ��
//					3.��������Ӧ��ƥ���Ϊ�ĸ��ֶΣ�������LocalID��źͻỰ�ţ��Ա���
//					  LocalID�ظ������ڻ�Ա��MBack
//					4.�޸�Reactor������������ģʽ�����ٱ���IOList������CSlogConnection
//					  ֱ���������ٶȿ�����߼�ʮ��
//20080110 hwp	1.���Ӷ�FTDЭ���֧��
//					2.RTT����֧��-fģʽ
//20090323 hwp	-i����ʱ���������ʱ�䡢IP����Ϣ
//20130808 longqy@cffex.net	���һЩע��
//
#include "public.h"
#include "FTDCSession.h"
// ����Ҫ OFP Э��
//#include "OFPSession.h"
#include "FtdPackageDesc.h"
#include "FTDCPackage.h"
#include "CSVParser.h"
#include "Storage.h"
//#include "OfpData.h"
#include "FtdPackageDesc.h"
#include "CDate.h"
#include "version.h"
#include "FTDCRSession.h"

class CFileLogger :public CLogger
{
public:
	CFileLogger()
	{
		m_fpLogFile = NULL;
	}
	~CFileLogger()
	{
		if (m_fpLogFile != NULL)
		{
			fclose(m_fpLogFile);
		}
	}
	
	bool Open(const char *pszFileName)
	{
		m_fpLogFile = fopen(pszFileName, "wb");
		if (m_fpLogFile == NULL)
		{
			return false;
		}
		return true;
	}

	virtual void output(int level, char *format, ...)
	{
		va_list v;
		va_start(v,format);
		vfprintf(m_fpLogFile,format,v);
		va_end(v);

		fflush(m_fpLogFile);
	}
private:
	FILE *m_fpLogFile;
};

CLogger *g_pLoggerOutput = NULL;			/* �����־�ļ���ָ�� */
CLogger *g_pLoggerError = NULL;				/* ��������ļ���ָ�� */

/* g_szTimeBuffer ������ݰ���ʱ��� */
char g_szTimeBuffer[10];
time_t g_szUsTime;

bool g_bAnalysisRTT = false;
double g_nErrRTT = 0;

class COrderRttItem
{
public:
	COrderRttItem()
	{
		memset(this, 0, sizeof(COrderRttItem));
		RTT = -1;
	}
	void Output(CLogger *pLogger)
	{
		pLogger->output(LL_DEBUG, "%s,%s,%d,%s.%d,%s.%d,%f(ms)\n", 
			UserID.getValue(), OrderLocalID.getValue(), LocalIdSeq,
			OrderReqTime.getValue(),OrderUsReqTime, OrderRspTime.getValue(),OrderUsRspTime, RTT);
	}
	void OutputErr(CLogger *pLogger, const char *pszErrorInfo)
	{
		pLogger->output(LL_DEBUG, "%s,%s,%d,%s.%d,%s.%d,%f(ms),%s\n", 
			UserID.getValue(), OrderLocalID.getValue(), LocalIdSeq,
			OrderReqTime.getValue(),OrderUsReqTime, OrderRspTime.getValue(),OrderUsRspTime, RTT, pszErrorInfo);
	}
	void CalcRTT()
	{
		RTT = CTime::TimeToLong(OrderRspTime)-CTime::TimeToLong(OrderReqTime);
		RTT = RTT*1000 + (OrderUsRspTime - OrderUsReqTime)/1000.0;
	}
	CUserIDType UserID;
	int SessionID;
	COrderLocalIDType OrderLocalID;
	int LocalIdSeq;
	CTimeType OrderReqTime;
	int OrderUsReqTime;
	CTimeType OrderRspTime;
	int OrderUsRspTime;
	double RTT;
};

class COrderRttManager : public CStorage<COrderRttItem>
{
public:
	static int CompareFuncByPrimaryKey(void *p1,void *p2)
	{
		int ret=Compare(((pointer)p1)->UserID,((pointer)p2)->UserID);
		if(ret!=0)return ret;
		ret=Compare(((pointer)p1)->SessionID,((pointer)p2)->SessionID);
		if(ret!=0)return ret;
		ret=Compare(((pointer)p1)->OrderLocalID,((pointer)p2)->OrderLocalID);
		if(ret!=0)return ret;
		return Compare(((pointer)p1)->LocalIdSeq,((pointer)p2)->LocalIdSeq);
	}
//	DEFINE_INDEX_FUNC_3(0, const char *, UserID, const char *, OrderLocalID, int, LocalIdSeq);
	COrderRttManager()
	{
		m_Index[m_nTotalIndex++] = new CIndex(CompareFuncByPrimaryKey);
	}
	
/*	
	void OnOFPPackage(COFPPackage *pOFPPackage, int nSessionID)
	{
		if (GetOFPVary(pOFPPackage->GetCommand())== OFP_VARY_OrderInsertRequest)
		{
			COFPOrderInsertRequestField *pReqOrderInsert = 
				(COFPOrderInsertRequestField *)pOFPPackage->Address();
			HandleOrderReq(pReqOrderInsert->Userid.getValue(),
				pReqOrderInsert->Lorderid.getValue(), nSessionID);
		}
		else if(pOFPPackage->GetCommandID() == OFP_VARY_OrderInsertResponse )
		{
			//OFP V1
			COFPOrderInsertResponseField *pRspOrderInsert = 
				(COFPOrderInsertResponseField *)pOFPPackage->Address();
			HandleOrderRsp(pRspOrderInsert->Userid.getValue(),
				pRspOrderInsert->Lorderid.getValue(), nSessionID);
		}
		else if(pOFPPackage->GetCommandID() == OFP_VARY_MBackOrder)
		{
			//OFP V2
			COFPMBackOrderField *pBackOrder = 
				(COFPMBackOrderField *)pOFPPackage->Address();
			WORD cmd = 0;
			memcpy(&cmd, &pBackOrder->cmd, 2);
			CHANGE_ENDIAN(cmd);
			if (cmd == OFP_VARY_OrderInsertResponse)
			{
				HandleOrderRsp(pBackOrder->Userid.getValue(),
					pBackOrder->Lorderid.getValue(), nSessionID);
			}
		}
	}
*/	
	void OnFTDCPackage(CFTDCPackage *pPackage, int nSessionID)
	{
		switch(pPackage->GetTID())
		{
		case FTD_TID_ReqOrderInsert:
			{
				//CFTDInputOrderField fieldInputOrder;
				CFTDInputOrderField fieldInputOrder;
				if(FTDC_GET_SINGLE_FIELD(pPackage, &fieldInputOrder) <= 0)
				{
					g_pLoggerError->output(LL_DEBUG, 
						"ReqOrderInsert missing CFTDInputOrderField[%s][%d]\n",
						g_szTimeBuffer, nSessionID);
				}
				else
				{
					HandleOrderReq(fieldInputOrder.UserID,
						//fieldInputOrder.OrderLocalID, nSessionID);
						fieldInputOrder.UserOrderLocalID, nSessionID);
				}

			}
			break;
		case FTD_TID_RspOrderInsert:
			{
				//CFTDInputOrderField fieldInputOrder;
				CFTDInputOrderField fieldInputOrder;
				if(FTDC_GET_SINGLE_FIELD(pPackage, &fieldInputOrder) <= 0)
				{
					g_pLoggerError->output(LL_DEBUG, 
						"RspOrderInsert missing CFTDInputOrderField[%s][%d]\n",
						g_szTimeBuffer, nSessionID);
				}
				else
				{
					HandleOrderRsp(fieldInputOrder.UserID,
						//fieldInputOrder.OrderLocalID, nSessionID);
						fieldInputOrder.UserOrderLocalID, nSessionID);
				}

			}
			break;	
		default:
			break;
		}
	}
	
	//void HandleOrderReq(const CUserIDType &UserID, const COrderLocalIDType &OrderLocalID, 
	void HandleOrderReq(const CUserIDType &UserID, const CUserOrderLocalIDType &OrderLocalID, 
		int nSessionID)
	{
		COrderRttItem item;
		item.OrderLocalID = OrderLocalID;
		item.UserID = UserID;
		item.OrderReqTime = g_szTimeBuffer;
		item.OrderUsReqTime  = g_szUsTime;
		item.SessionID = nSessionID;
		CIndex *pIndex = m_Index[0];
		CIndexNode *pIndexNode = pIndex->searchFirstGreatEqual(&item);
		for(; pIndexNode!=NULL ;item.LocalIdSeq++)
		{
			COrderRttItem *pFind = (COrderRttItem *)(pIndexNode->pObject);
			if (pFind->UserID != item.UserID ||pFind->OrderLocalID != item.OrderLocalID
				|| pFind->SessionID != item.SessionID)
			{
				break;
			}
			pIndexNode = pIndex->getNextNode(pIndexNode);
		}
		if (item.LocalIdSeq != 0)
		{
//			g_pLoggerError->output(LL_DEBUG, "Duplicate OrderLocalID[%s][%s][%s]\n", 
//				item.UserID.getValue(), item.OrderLocalID.getValue(),
//				item.OrderReqTime.getValue());
		}
		AppendData(item);
	}
	
	//void HandleOrderRsp(const CUserIDType &UserID, const COrderLocalIDType &OrderLocalID,
	void HandleOrderRsp(const CUserIDType &UserID, const CUserOrderLocalIDType &OrderLocalID,
		int nSessionID)
	{
		COrderRttItem item;
		item.OrderLocalID = OrderLocalID;
		item.UserID = UserID;
		item.SessionID = nSessionID;
		CIndex *pIndex = m_Index[0];
		CIndexNode *pIndexNode = pIndex->searchFirstGreatEqual(&item);
		COrderRttItem *pLastFind = NULL;
		for(; pIndexNode!=NULL ;item.LocalIdSeq++)
		{
			COrderRttItem *pFind = (COrderRttItem *)(pIndexNode->pObject);
			if (pFind->UserID != item.UserID  || pFind->OrderLocalID != item.OrderLocalID
				|| pFind->SessionID != item.SessionID)
			{
				break;
			}
			pLastFind = pFind;
			if (pLastFind->OrderRspTime == "")
			{
				break;
			}
			pIndexNode = pIndex->getNextNode(pIndexNode);
		}
		if (pLastFind == NULL)
		{
//			g_pLoggerError->output(LL_DEBUG, "Missing order request[%s][%s][%s]\n", 
//				item.UserID.getValue(), item.OrderLocalID.getValue(),
//				g_szTimeBuffer);
		}
		else
		{
			pLastFind->OrderRspTime = g_szTimeBuffer;
			pLastFind->OrderUsRspTime = g_szUsTime;
			pLastFind->CalcRTT();
			pLastFind->Output(g_pLoggerOutput);
		}
	}
};

COrderRttManager g_OrderRttManager;

class CPackageFilter
{
public:
	CPackageFilter(){
		m_strEndTime = "23:59:59";
	};
	~CPackageFilter(){};
	void AddDesiredTid(DWORD dwTid)
	{
		m_DesiredTids.push_back(dwTid);
	}
	void SetStartTime(const char *pszStartTime)
	{
		m_strStartTime = pszStartTime;
	}
	void SetEndTime(const char *pszEndTime)
	{
		m_strEndTime = pszEndTime;
	}
	
	/* ���ָ���� TID �Ƿ�Ϊ��鿴�� TID? ���û��ָ�� TID �������е� TID ��Ҫ�鿴�� */
	bool CheckTid(DWORD dwTid)
	{
		if (m_DesiredTids.size() ==0  || 
			find(m_DesiredTids.begin(), m_DesiredTids.end(), dwTid) != m_DesiredTids.end())
		{
			return true;
		}
		return false;
	}
	
	/* ������ݰ���ʱ������Ƿ�������Ҫ�鿴�ķ�Χ�� */
	bool CheckTime()
	{
		if (m_strStartTime.compare(g_szTimeBuffer)>0 ||
			m_strEndTime.compare(g_szTimeBuffer)<0)
		{
			return false;
		}
		return true;
	}
	
	/* ��������¼������� */
	bool CheckEventOutput()
	{
		return (!g_bAnalysisRTT && CheckTime() && !IsTidFilter());
	}
	bool IsTidFilter()
	{
		return m_DesiredTids.size() > 0;
	}
private:
	vector<DWORD> m_DesiredTids;			/* �����Ҫ�������Щ TID */
	string m_strStartTime;
	string m_strEndTime;
};

CPackageFilter g_PackageFilter;

/*
class COfpDumpSession : public COFPSession
{
public:
	COfpDumpSession(CReactor *pReactor, CChannel *pChannel)
		:	COFPSession(pReactor, pChannel, OFP_VERSION_1)
	{
		m_pOFPProtocol->RegisterUpperHandler(this);
		m_nSessionID = (pChannel->GetId()<<16)|CTime::TimeToLong(g_szTimeBuffer);
	}

	virtual int HandlePackage(CPackage *pPackage,CProtocol *pProtocol)
	{
		if (pProtocol == m_pOFPProtocol)
		{
			COFPPackage *pOFPPackage = (COFPPackage *)pPackage;
			if (g_PackageFilter.CheckTid(pOFPPackage->GetCommandID()) &&
				g_PackageFilter.CheckTime())
			{
				if (g_bAnalysisRTT)
				{
					g_OrderRttManager.OnOFPPackage(pOFPPackage, GetSessionID());
				}
				else
				{
					if (g_PackageFilter.IsTidFilter())
					{
						g_pLoggerOutput->output(LL_DEBUG, "\n[%s]:[%s][%08X][%s]\n", 
							"PACKAGE", g_szTimeBuffer, GetChannel()->GetId(),
							GetChannel()->GetRemoteName());						
					}
					pOFPPackage->DebugOutput(g_pLoggerOutput);
				}
			}
		}
		else
		{
			printf("error package received\n");
		}

		return 0;
	}
	virtual void OnChannelLost(int nErrorCode)
	{
		printf("Channel lost , error code = [%x]\n", nErrorCode);
		COFPSession::OnChannelLost(nErrorCode);
	}
};
*/

class CFtdcDumpSession : public CFTDCRSession
{
public:
	CFtdcDumpSession(CReactor *pReactor,CChannel *pChannel)
		:CFTDCRSession(pReactor, pChannel)
	{
		m_pExXMPProtocol->EnableHeartbeat(false);
		m_pExXMPProtocol->RegisterUpperHandler(this);
//		m_pCRPProtocol->RegisterUpperHandler(this);
		
//		SetCompressMethod(CRPCM_ZERO);		//����ѹ���㷨
		
		/* ����ID ���ŵ��� ID */
		m_nSessionID = (pChannel->GetId()<<16)|CTime::TimeToLong(g_szTimeBuffer);
	}

	/* �������ݰ������ѷ������������ݰ����ڴ�������ļ���ȥ */
	virtual int HandlePackage(CPackage *pPackage,CProtocol *pProtocol)
	{
		if (pProtocol == m_pExXMPProtocol)
		{
			printf("XMP package received\n");
		}
		else if (pProtocol == m_pCRPProtocol)
		{
			printf("CRP package received\n");
		}
		else if (pProtocol == m_pFTDCProtocol)
		{
			CFTDCPackage *pFTDCPackage = (CFTDCPackage *)pPackage;
			if (g_PackageFilter.CheckTid(pFTDCPackage->GetTID()) &&
				g_PackageFilter.CheckTime())
			{
				if (g_bAnalysisRTT)
				{
					g_OrderRttManager.OnFTDCPackage(pFTDCPackage, GetSessionID());
				}
				else
				{
					if (g_PackageFilter.IsTidFilter())
					{
						g_pLoggerOutput->output(LL_DEBUG, "\n[%s]:[%s][%08X][%s]\n", 
							"PACKAGE", g_szTimeBuffer, GetChannel()->GetId(),
							GetChannel()->GetRemoteName());						
					}
					/* ������ݰ�ͷ��������ļ��� */
					pFTDCPackage->OutputHeader(g_pLoggerOutput);
					/* ������ݰ������ݣ�������ļ��� */
					FTDC_DEBUG_BODY(pFTDCPackage->GetTID(), pFTDCPackage, 
						g_pLoggerOutput);
				}
			}
		}
		else
		{
			printf("error package received\n");
		}

		return 0;
	}

	virtual void OnChannelLost(int nErrorCode)
	{
		printf("Channel lost , error code = [%x]\n", nErrorCode);
		CFTDCRSession::OnChannelLost(nErrorCode);
	}
};

#define MAX_SLOG_REC_LEN	10000

class CSlogConnection ;
class CSlogChannel: public CChannel
{
public:
	CSlogChannel(int nID, CCacheList *pCacheList, const char *pszRemoteName)
		:CChannel(CT_STREAM, nID)			// ���������͵��ŵ�
	{
		m_pCacheList = pCacheList;
		m_strRemoteName = pszRemoteName;	// ͨ�ŶԷ�һ�˵����֣�ʵ���Ͽ����� IP ��ַ
	}

protected:
	/* ���ŵ��ж�����Ϊ number �ֽڵ����ݣ��������� buffer ��ȥ */
	virtual int ReadImp(int number, char *buffer)
	{
		char *pData=(char *)m_pCacheList->GetData(number);		
		if(pData==NULL)
		{
			return 0;
		}

		memcpy(buffer, pData, number);
		m_pCacheList->PopFront(number);
		return number;
	}
	
	virtual int WriteImp(int number, char *buffer){	return -1;}
	virtual bool AvailableImp(void){	return 0;}
	virtual bool DisconnectImp(void){	return false;}
	virtual bool CheckConnectionImp(void){	return true;}
	virtual char *GetRemoteName(void)
	{
		return (char *)(m_strRemoteName.c_str());
	}
private:
	CCacheList *m_pCacheList;
	string m_strRemoteName;
};

class CSlogConnection
{
public:
	CSlogConnection(int nID, const char *pszIPAddress)
		:m_cacheRead(64*1024), m_cacheWrite(64*1024)
	{
		m_nID = nID;
		m_strIPAddress = pszIPAddress;
		m_pReadSession = NULL;
		m_pWriteSession = NULL;
	}
	virtual ~CSlogConnection()
	{
//		delete m_pReadSession;
//		delete m_pWriteSession;
	}
	
	bool CreateSession(CReactor *pReactor, const char *pszSessionType)
	{
		if (strstr(pszSessionType, "ftd"))
		{	// "ftd" ��ʾǰ���������ݰ�
			m_pReadSession = new CFtdcDumpSession(pReactor,
				new CSlogChannel(m_nID, &m_cacheRead, m_strIPAddress.c_str()));
			m_pWriteSession = new CFtdcDumpSession(pReactor,
				new CSlogChannel(m_nID, &m_cacheWrite, m_strIPAddress.c_str()));
		}
		else if (strstr(pszSessionType, "ofp"))
		{
/*
		m_pReadSession = new COfpDumpSession(pReactor,
				new CSlogChannel(m_nID, &m_cacheRead, m_strIPAddress.c_str()));
			m_pWriteSession = new COfpDumpSession(pReactor,
				new CSlogChannel(m_nID, &m_cacheWrite, m_strIPAddress.c_str()));
*/
		}
		else
		{
			return false;
		}
//		pReactor->RegisterIO(m_pReadSession);
//		pReactor->RegisterIO(m_pWriteSession);
		return true;
	}

	/* ���ӽ���ʱ�����������ʱ�䡢�Է���IP ��ַ */
	void OnConnected(const char *pszTime)
	{
		if (g_PackageFilter.CheckEventOutput())
		{
			g_pLoggerOutput->output(LL_DEBUG, "\n[%s]:[%s][%08X][%s]\n", 
				"CONNECTED", pszTime, m_nID, m_strIPAddress.c_str());
		}
	}
	
	void OnChannelRead(const char *pszTime, const char *pData, const int nDataLen)
	{
		if (g_PackageFilter.CheckEventOutput())
		{
			g_pLoggerOutput->output(LL_DEBUG, "\n[%s]:[%s.%06d][%08X][%d][%s]\n", 
				"READ", pszTime,g_szUsTime, m_nID, nDataLen, m_strIPAddress.c_str());
		}
		m_cacheRead.PushBack((void *)pData, nDataLen);
		m_pReadSession->HandleInput();
	}

	void OnChannelWrite(const char *pszTime, const char *pData, const int nDataLen)
	{
		if (g_PackageFilter.CheckEventOutput())
		{
			g_pLoggerOutput->output(LL_DEBUG, "\n[%s]:[%s.%06d][%08X][%d][%s]\n", 
				"WRITE", pszTime,g_szUsTime, m_nID, nDataLen, m_strIPAddress.c_str());
		}
		m_cacheWrite.PushBack((void *)pData, nDataLen);
		m_pWriteSession->HandleInput();
	}
	
	void OnReadError(const char *pszTime)
	{
		Output("READ_ERROR", pszTime);
	}

	void OnWriteError(const char *pszTime)
	{
		Output("WRIT_EERROR", pszTime);
	}

	void OnDisconnected(const char *pszTime)
	{
		Output("DISCONNECT", pszTime);
	}

	void OnDisconnectedRead(const char *pszTime)
	{
		Output("DISCONNECTED_READ", pszTime);
	}

	void OnDisconnectedWrite(const char *pszTime)
	{
		Output("DISCONNECTED_WRITE", pszTime);
	}

	void OnDupSocketID(const char *pszTime)
	{
		Output("DUP_SOCKET_ID", pszTime);
	}

	void Output(const char *pszEventStr, const char *pszTime)
	{
		if (g_PackageFilter.CheckEventOutput())
		{
			g_pLoggerOutput->output(LL_DEBUG, "\n[%s]:[%s][%08X][%s]\n", 
				pszEventStr, pszTime, m_nID, m_strIPAddress.c_str());
		}
	}
	
	const char * GetIPAddress()
	{
		return m_strIPAddress.c_str();
	}
protected:
	string m_strIPAddress;			// �����Ự���ӵĶԷ�һ�˵�IP��ַ
	int m_nID;
	CCacheList m_cacheRead;
	CCacheList m_cacheWrite;
	CSession *m_pReadSession;
	CSession *m_pWriteSession;
};

class CSlogReactor : public CReactor
{
public:
	CSlogReactor(const char *pszSlogFileName, const char *pszDesiredIpAddress,
		bool bFollow)
	{
		m_fpSlog = NULL;
		m_strSlogFileName = pszSlogFileName;			// �������ļ������� 
		m_strDesiredIpAddress = pszDesiredIpAddress;
		memset(&m_header, 0, sizeof(m_header));			// �ŵ���channel����־ͷ������Ϊ16���ֽ�
		m_nReadLen = 0;
		m_bFollow = bFollow;
		FPOS_SET(m_fposLog, 0);
		m_tLastTime = 0;
	}
	~CSlogReactor()
	{
		CSlogConnectionMap::iterator itor = m_mapSlogConnection.Begin();
		while (!itor.IsEnd())
		{
			delete (*itor);
			itor++;
		}
		m_mapSlogConnection.Clear();
		if (m_fpSlog != NULL)
		{
			fclose(m_fpSlog);
		}
	}

protected:
	CSlogConnection *CreateSlogConnection(int nID, const char *pszIPAddress)
	{
		if (m_strDesiredIpAddress.compare("all") == 0 ||
			m_strDesiredIpAddress.compare(pszIPAddress) == 0)
		{
			CSlogConnection *pSlogConnection = new CSlogConnection(nID, pszIPAddress);
			if (!pSlogConnection->CreateSession(this, /*m_strSlogFileName.c_str()*/"ftd"))
			{
				delete pSlogConnection;
				return NULL;
			}
			m_mapSlogConnection.Insert(nID, pSlogConnection);
			return pSlogConnection;
		}
		return NULL;
	}
	
	CSlogConnection *GetSlogConnection(int nID)
	{
		CSlogConnection **pFind = m_mapSlogConnection.Find(nID);
		if (pFind == NULL)
		{
			return NULL;
		}
		return *pFind;
	}

	bool DelSlogConnection(int nID)
	{
		CSlogConnection **pFind = m_mapSlogConnection.Find(nID);
		if (pFind == NULL)
		{
			return false;
		}
		delete *pFind;
		m_mapSlogConnection.Erase(nID);
		return true;
	}

	bool ReadOne()
	{
		int n = 0;
		if (m_nReadLen < sizeof(TChannelLogHeader))
		{	// ���ŵ���־���ݰ���ͷ
			n = fread(((char *)&m_header)+m_nReadLen, 1, 
				sizeof(TChannelLogHeader)-m_nReadLen, m_fpSlog);
			FPOS_SET(m_fposLog, FPOS_GET(m_fposLog) + n);
			m_nReadLen += n;
			if (m_nReadLen >= sizeof(TChannelLogHeader))
			{
				m_header.ChangeEndian();
			}
		}
		if (m_nReadLen < sizeof(TChannelLogHeader))
		{
			return false;
		}
		if (m_header.wLength > 0)
		{
			int n = fread(m_buffer+m_nReadLen-sizeof(TChannelLogHeader), 1, 
				m_header.wLength-m_nReadLen+sizeof(TChannelLogHeader), m_fpSlog);
			FPOS_SET(m_fposLog, FPOS_GET(m_fposLog) + n);
			m_nReadLen += n;
			if ( m_nReadLen != m_header.wLength+sizeof(TChannelLogHeader))
			{
				return false;
			}
		}

		m_nReadLen = 0;
		time_t tCurrTime = m_header.dwTime;
		g_szUsTime = m_header.dwMsTime;
		strftime(g_szTimeBuffer, sizeof(g_szTimeBuffer), "%H:%M:%S",
			localtime(&tCurrTime));
		if (m_tLastTime != tCurrTime)
		{
			printf("current log time : %s %06d\n", g_szTimeBuffer,g_szUsTime);
			m_tLastTime = tCurrTime;					/* ָ���¼�������ʱ�� */
		}
		CSlogConnection *pSlogConnection = NULL;
		if (m_header.wType == CLRT_CONNECTED)
		{
			pSlogConnection = GetSlogConnection(m_header.dwId);
			if (pSlogConnection != NULL)
			{
				pSlogConnection->OnDupSocketID(g_szTimeBuffer);
				DelSlogConnection(m_header.dwId);
			}
			/* �ڽ������ӵ�ʱ��m_buffer �д�ŵ���IP ��ַ */
			pSlogConnection = CreateSlogConnection(m_header.dwId, m_buffer);
		}
		else
		{
			pSlogConnection = GetSlogConnection(m_header.dwId);
		}
		if (pSlogConnection == NULL)
		{
			if (m_header.wType == CLRT_WRITE)
			{
				pSlogConnection = CreateSlogConnection(m_header.dwId,"0.0.0.0");
			}
			else
			{
				return true;
			}
		}
		switch(m_header.wType) {
		case CLRT_CONNECTED:
			pSlogConnection->OnConnected(g_szTimeBuffer);
			break;
		case CLRT_READ:
			pSlogConnection->OnChannelRead(g_szTimeBuffer, m_buffer, m_header.wLength);
			break;
		case CLRT_WRITE:
			pSlogConnection->OnChannelWrite(g_szTimeBuffer, m_buffer, m_header.wLength);
			break;
		case CLRT_DISCONNECT:
			pSlogConnection->OnDisconnected(g_szTimeBuffer);
			DelSlogConnection(m_header.dwId);
			break;
		case CLRT_READ_ERROR:
			pSlogConnection->OnReadError(g_szTimeBuffer);
			break;
		case CLRT_WRITE_ERROR:
			pSlogConnection->OnWriteError(g_szTimeBuffer);
			break;
		case CLRT_DISCONNECTED_READ:
			pSlogConnection->OnDisconnectedRead(g_szTimeBuffer);
			break;
		case CLRT_DISCONNECTED_WRITE:
			pSlogConnection->OnDisconnectedWrite(g_szTimeBuffer);
			break;
		default:
			printf("header type error :[%d]\n", m_header.wType);
			return false;
		}
		return true;
	}
	
	/* CSlogReactor �࣬���᲻�ϵص����������������־�ļ��е����� */
	virtual void DispatchIOs()
	{
		
		if (m_fpSlog == NULL)
		{
			m_fpSlog = fopen(m_strSlogFileName.c_str(), "rb");
			if (m_fpSlog == NULL)
			{
				printf("open file [%s] error[%d]\n", m_strSlogFileName.c_str(), errno);
				Stop();
				return;
			}
			if (fsetpos(m_fpSlog, &m_fposLog) != 0)
			{
				printf("fsetpos file [%s] error[%d]\n", m_strSlogFileName.c_str(), errno);
				fclose(m_fpSlog);
				m_fpSlog = NULL;
				Stop();
				return;
			}
		}
		if(!ReadOne())
		{
			if (m_bFollow)
			{
				fclose(m_fpSlog);
				m_fpSlog = NULL;
				OSSleep(2);
				// ���ļ������ʱ�򣬾�Ӧ���˳���������ܻ���� 2015-02-16 longqy
				Stop();
			}
			else
			{
				printf("end of input file\n");
				Stop();
			}
		}
	}
private:
	FILE *m_fpSlog;
	TChannelLogHeader m_header;
	char m_buffer[MAX_SLOG_REC_LEN];
	int m_nReadLen;
	bool m_bFollow;
	string m_strSlogFileName;
	string m_strDesiredIpAddress;
	fpos_t m_fposLog;
	typedef CHashMap<int, CSlogConnection *, HashInt> CSlogConnectionMap;
	CSlogConnectionMap m_mapSlogConnection;								/* TID �� CSlogConnection ��ӳ�� Map */
	time_t m_tLastTime;													/* ���һ�����ݰ���ʱ��� */
};

/*	
//	-d ipaddress				ֻ����ָ����IP��ַ��Ĭ��Ϊ���е� IP ��ַ
//	-o outputfile				�������������ļ�
//	-e errorfile				�����ļ�
//	-t starttime[,endtime]]		ָ�������Ŀ�ʼʱ�䣬����ʱ��
//	-i tid1,tid2,...			����ָ����TID
*/
void Usage()
{
	printf("Usage: slogparser [-f]\n");
	printf("                  [-d ipaddress]\n"); 
	printf("                  [-o outputfile]\n");
	printf("                  [-e errorfile]\n");
	printf("                  [-t starttime[,endtime]]\n");
	printf("                  [-i tid1,tid2,...]\n");
	printf("                  [-a elapse]\n");
	printf("                  logfilename\n");
}

#if 1

int main(int argc, char *argv[])
{
	showVersion(argc, argv);

	time_t timeStart = time(NULL);
	UseBizStatusLog=UseBizOperationLog=UseBizExceptionLog = false;
	UseNetStatusLog=UseNetConnectLog=UseNetIOLog=UseNetPackageLog = false,
	UseNetCompressLog=UseProcessLog = false;
//	UseNetExceptionLog;

	bool bFollow = false;
	string strDesiredIpAddress = "all";
	string strOutputFile = "slog.out";
	string strErrorFile = "slog.err";
	string strDesiredTid;
	CCSVParser csvParser;

	int c = 0;	
	while ((c = getopt(argc, argv, "fo:d:t:i:a:e:")) != EOF)
	{
		switch (c)
		{
		case ('d'):
			if (optarg != NULL)
			{
				strDesiredIpAddress = optarg;
			}
			break;	
		case ('o'):
			if (optarg != NULL)
			{
				strOutputFile = optarg;
			}
			break;	
		case ('e'):
			if (optarg != NULL)
			{
				strErrorFile = optarg;
			}
			break;	
		case ('f'):
			bFollow = true;
			break;
		case ('i'):
			{
				csvParser.Parse(optarg);
				char *endptr = NULL;
				char *pszToken = NULL;
				while ((pszToken=csvParser.GetNextToken()) != NULL)
				{
					g_PackageFilter.AddDesiredTid(strtoul(pszToken, &endptr, 16));	
				}
				strDesiredTid = optarg;
			}
			break;
		case ('t'):
			{
				csvParser.Parse(optarg);
				for(int i=0; i<2 ;i++)
				{
					char *pszToken = csvParser.GetNextToken();
					if (pszToken == NULL)
					{
						break;
					}
					if (i==0)
					{
						g_PackageFilter.SetStartTime(pszToken);
					}
					else
					{
						g_PackageFilter.SetEndTime(pszToken);
					}
				};
				strDesiredTid = optarg;
			}
			break;
		case 'a':
			g_bAnalysisRTT = true;
			g_nErrRTT = atof(optarg);
			break;
		default:
			Usage();
			return -1;
		}
	}

	if (optind >= argc)
	{
		Usage();
		return -1;
	}
	printf("input file : [%s]\n", argv[optind]);
	printf("follow mode %s\n", bFollow?"on":"off");
	printf("desired IP address:[%s]\n", strDesiredIpAddress.c_str());
	printf("desired TID  : [%s]\n", strDesiredTid.c_str());
	printf("output file : [%s]\n", strOutputFile.c_str());

	g_pLoggerOutput = new CFileLogger();
	/*	������ļ� */
	if(!((CFileLogger *)g_pLoggerOutput)->Open(strOutputFile.c_str()))
	{
		printf("can't open output file %s\n",strOutputFile.c_str());
		return -3;
	}

	g_pLoggerError = new CFileLogger();
	if(!((CFileLogger *)g_pLoggerError)->Open(strErrorFile.c_str()))
	{
		printf("can't open error file %s\n",strErrorFile.c_str());
		return -3;
	}

	CSlogReactor reactor(argv[optind], strDesiredIpAddress.c_str(), bFollow);
	reactor.Create();
	reactor.Join();

	double lfTotalRTT = 0;
	if (g_bAnalysisRTT)
	{
		for (int i=0; i<g_OrderRttManager.GetCount(); i++)
		{
			COrderRttItem *pItem = g_OrderRttManager.Get(i);
//			g_pLoggerOutput->output(LL_DEBUG, "%s,%s,%d,%s,%s\n", 
//				pItem->UserID.getValue(), pItem->OrderLocalID.getValue(), pItem->LocalIdSeq,
//				pItem->OrderReqTime.getValue(), pItem->OrderRspTime.getValue());
			if (pItem->RTT < 0)
			{
				pItem->Output(g_pLoggerOutput);
				pItem->OutputErr(g_pLoggerError, "Missing order response");
			}
			else
			{
				if (pItem->RTT > g_nErrRTT)
				{
					pItem->OutputErr(g_pLoggerError, "Error RTT");
				}
				lfTotalRTT += pItem->RTT;
			}
		}
		if (g_OrderRttManager.GetCount() > 0)
		{
			printf("Analysis RTT: average-[%lf]\n", 
				lfTotalRTT/g_OrderRttManager.GetCount());
		}
	}


	delete ((CFileLogger *)g_pLoggerOutput);
	delete ((CFileLogger *)g_pLoggerError);

	time_t timeEnd = time(NULL);
	printf("time: start=%u end=%u elapse=%u\n", timeStart, timeEnd, timeEnd-timeStart);
	//add by cc
	char ch;
	scanf("%c",&ch);
	return 0;
}

#endif
