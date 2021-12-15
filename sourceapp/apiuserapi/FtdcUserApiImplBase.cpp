/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file FtdcUserApiImpl.cpp
///@brief 实现了客户端接口
///@history 
///20060106	赵鸿昊  创建该文件
///20061012	赵鸿昊  增加对SSL身份校验的支持
///20070216	章捷    改变流控方法.userapi不做流控，tradeapi做流控。
///20070806	赵鸿昊  增加方法：
///                 SubscribeUserTopic 订阅交易员流。
///                 SetHeartbeatTimeout 设置心跳超时时间。
///                 OpenRequestLog 打开请求日志文件
///                 OpenResponseLog 打开应答日志文件
///20070921 赵鸿昊 将流文件由二进制改为文本
///20070924 赵鸿昊 调整继承关系，以支持nameserver
// 20080227 赵鸿昊 修正BUG：OnSessionWarning中，对警告原因的判断应为
//                 MSG_XMPWARNING_RECVHEARTBEAT,原误为MSG_XMPERR_BADPACKAGE
// 20080727 赵鸿昊 NT-0048:扩展CSessionFactory::CreateSession参数，便于创建
//                 会话时区分不同的连接
// 20090121 赵鸿昊 NT-0066:心跳超时时间缺省值改为30秒
// 20090213 赵鸿昊 NT-0067:修正OnPackageStart,OnPackageEnd回调参数错误问题
// 20090428 赵鸿昊 NT-0071:心跳超时时间缺省值改为10秒
// 20090504 赵鸿昊 NT-0072:修正UserAPI流控线程不安全问题
// 20090505 赵鸿昊 NT-0073:修正UserAPI数据流续传管理问题
//                         修正对话流缓冲区溢出问题
//                         版本信息中增加用日期时间表示的小版本号
/////////////////////////////////////////////////////////////////////////

#include "public.h"
#include "FtdcUserApiImplBase.h"
#include "CachedFileFlow.h"
#include "FileFlow.h"
#include "CDate.h"
#include "UFCopy.h"
#include "CSVParser.h"
#include "BaseFunction.h"
#ifdef WIN32
#include "Iphlpapi.h"
#include<stdio.h>
#pragma comment(lib,"Iphlpapi.lib")
#endif
/**CFtdcUserDialogFlow是线程安全的CCachedFlow
*对于会话流，应用程序线程和API线程会同时访问，必须加以保护
*/
class CFtdcUserDialogFlow : public CCachedFlow
{
public:
	CFtdcUserDialogFlow(bool bSyncFlag, int nMaxObjects, int nDataBlockSize)
		:CCachedFlow(bSyncFlag, nMaxObjects, nDataBlockSize)
	{
		m_nCount = CCachedFlow::GetCount();
	}
	
	virtual int GetCount(void)
	{
		return m_nCount;
	}
	
	virtual bool Truncate(int nCount)
	{
		m_lock.Lock();
		bool bRet = CCachedFlow::Truncate(nCount);
		m_nCount = CCachedFlow::GetCount();
		m_lock.UnLock();
		return bRet;
	}

	virtual int Append(void *pObject, int length)
	{
		m_lock.Lock();
		int nRet = -1;
		if( m_nMaxObjects<=0 || m_NodeQueue.size()-m_nFirstID<m_nMaxObjects)
		{
			nRet = CCachedFlow::Append(pObject, length);
			m_nCount = CCachedFlow::GetCount();
		}
		m_lock.UnLock();
		return nRet;
	}

 	virtual int Get(int id, void *pObject, int length)
	{
		m_lock.Lock();
		int nRet = CCachedFlow::Get(id, pObject, length);
		m_nCount = CCachedFlow::GetCount();
		PopFront();
		m_lock.UnLock();
		return nRet;
	}
	
private:
	int m_nCount;
	CMutex m_lock;
};
class CUserFlow : public CFlow
{
public:
	CUserFlow(const char *pszFlowName, const char *pszPath, bool bReuse)
	{
		m_nCount= 0;
		m_wCommPhaseNo = 0;
		m_fpContentFile=NULL;
		OpenFile(pszFlowName, pszPath, bReuse);
	}
	CUserFlow(int nFlowID, const char *pszPath, bool bReuse)
	{
		char szFlowName[20];
		sprintf(szFlowName, "%08x", nFlowID);
		new (this) CUserFlow(szFlowName, pszPath, bReuse);
	}

	virtual ~CUserFlow()
	{
		CloseFile();
	}

	virtual int GetCount(void)
	{
		return m_nCount;
	}
	
	virtual const int *GetCountPtr(void)
	{
		return reinterpret_cast<const int *>(&m_nCount);
	}
	
	void SetCount(int nCount)
	{
		m_nCount = nCount;
		WriteFile();
	}

	virtual WORD GetCommPhaseNo()
	{
		return m_wCommPhaseNo;
	}

	virtual void SetCommPhaseNo(WORD nCommPhaseNo)
	{
		if (nCommPhaseNo != m_wCommPhaseNo)
		{
			m_wCommPhaseNo = nCommPhaseNo;
			m_nCount= 0;
			WriteFile();
		}
	}

	virtual bool Truncate(int nCount)
	{
//		if (m_nCount <= nCount)
//		{
//			return true;
//		}
		m_nCount= nCount;
		return WriteFile();
	}
	
	virtual int Append(void *pObject, int length)
	{
		m_nCount++;
		WriteFile();
		return m_nCount-1;		
	}

 	virtual int Get(int id, void *pObject, int length)
	{
		RAISE_RUNTIME_ERROR("Can't use this function - CUserFlow::Get\n");
		return 0;
	}

protected:	
	bool WriteFile()
	{
		fseek(m_fpContentFile, 0, SEEK_SET);
		if(fprintf(m_fpContentFile, "%5d,%10d\n", m_wCommPhaseNo, m_nCount) <= 0)
		{
			return false;
		}
		//2014-06-25 longqy 不flush文件，提高性能
		//fflush(m_fpContentFile);
		return true;
	}
	void OpenFile(const char *pszFlowName, const char *pszPath, bool bReuse)
	{
		ASSERT(pszPath != NULL);
		m_nCount = 0;
		CloseFile();
		char szContentFilename[512];
		sprintf(szContentFilename, "%s%s.con", pszPath, pszFlowName);
		m_fpContentFile = mfopen(szContentFilename,"r+b");
		if (m_fpContentFile == NULL)
		{
			m_fpContentFile = mfopen(szContentFilename,"w+b");
			if(m_fpContentFile == NULL)
			{
				CloseFile();
				RAISE_RUNTIME_ERROR("can not open CFlow file");
			}			
		}
		
		fseek(m_fpContentFile, 0, SEEK_SET);
		if (!bReuse || fscanf(m_fpContentFile, "%d,%d\n", &m_wCommPhaseNo, &m_nCount)!=2)
		{
			if (!WriteFile())
			{
				CloseFile();
				RAISE_RUNTIME_ERROR("can not init CFlow file");
			}
		}
	}

	void CloseFile()
	{
		if(m_fpContentFile != NULL){
			fclose(m_fpContentFile);
			m_fpContentFile = NULL;
		}
	}

private:
	FILE *m_fpContentFile;			/**< 存储内容的文件 */
	DWORD m_nCount;					/**< 已经存在的包个数 */
	WORD m_wCommPhaseNo;			/**< 通讯阶段编号*/
};

class CFtdcUserFlowCtrlAutoPtr
{
public:
	CFtdcUserFlowCtrlAutoPtr(CMutex *pMutex)
	{
		m_pMutex = pMutex;
		m_pMutex->Lock();
	}
	~CFtdcUserFlowCtrlAutoPtr()
	{
		m_pMutex->UnLock();
	}
private:
	CMutex *m_pMutex;
};

#define FTDC_FLOWCTRL_SYNC		\
	CFtdcUserFlowCtrlAutoPtr __FtdcUserFlowCtrlAutoPtr(&m_mutexFlowControl);

/////////////////////////////////////////////////////////////////////////
class CFtdcUserSubscriber : public CFTDCSubscriber
{
public:
	CFtdcUserSubscriber(CFtdcUserApiImplBase *pUserApiImplBase,
		CFlow *pFlow, WORD wSequenceSeries);
	virtual ~CFtdcUserSubscriber();
	virtual void SetCommPhaseNo(WORD wCommPhaseNo);
	virtual WORD GetSequenceSeries();
	virtual DWORD GetReceivedCount();
	virtual void HandleMessage(CFTDCPackage *pMessage);
	TE_RESUME_TYPE GetResumeType();
	WORD GetCommPhaseNo();
	void SetResumeType(TE_RESUME_TYPE nResumeType);
	void MoveTo(int nOffset);

	void CleanControl(void);

	int AddOneToFlow(void);
	void DequeueRequest(CFTDCPackage *pResponse);

private:
	CFlow *m_pFlow;
	WORD m_wSequenceSeries;
	DWORD m_nCount;					/**< 已经存在的包个数 */
	WORD m_wCommPhaseNo;			/**< 通讯阶段编号*/
	CFtdcUserApiImplBase *m_pUserApiImplBase;
	TE_RESUME_TYPE m_nResumeType;

	// flow control by zhangjie
	unsigned int m_nMaxUnfinished;
	unsigned int m_nMaxPerSecond;
	unsigned int m_nTimeoutForQueryFlow;

	list<time_t> m_nUnfinished;
	unsigned int m_nCntPerSecond;
	time_t m_lastTime;
	CMutex m_mutexFlowControl;
};
/////////////////////////////////////////////////////////////////////////

CFtdcUserSubscriber::CFtdcUserSubscriber(CFtdcUserApiImplBase *pUserApiImplBase,
										 CFlow *pFlow, WORD wSequenceSeries)
{
	m_pUserApiImplBase = pUserApiImplBase;
	m_pFlow = pFlow;
	m_wSequenceSeries = wSequenceSeries;
	m_nCount = 0;
	m_wCommPhaseNo = 0;
	m_nResumeType = TERT_RESUME;

	if (wSequenceSeries == TSS_QUERY) {
#ifdef TRADEAPILIMIT
		m_nMaxUnfinished = MAXQUERYUNFINISHED;
		m_nMaxPerSecond  = MAXQUERYPERSECOND;
#else
		m_nMaxUnfinished = 0x7fffffff;
		m_nMaxPerSecond  = 0x7fffffff;
#endif
		m_nTimeoutForQueryFlow = 30;	// 单位：秒
		CleanControl();
	}
	
	if (wSequenceSeries == TSS_DIALOG) {
#ifdef TRADEAPILIMIT
		m_nMaxUnfinished = MAXDIALOGUNFINISHED;
		m_nMaxPerSecond  = MAXDIALOGPERSECOND;
#else
		m_nMaxUnfinished = 0x7fffffff;
		m_nMaxPerSecond  = 0x7fffffff;
#endif
		CleanControl();
	}
}

CFtdcUserSubscriber::~CFtdcUserSubscriber()
{
}

void CFtdcUserSubscriber::CleanControl(void)
{
	//add by wangwei , 20120315
	FTDC_FLOWCTRL_SYNC;
	m_nCntPerSecond = 0;
	m_lastTime = 0;
	m_nUnfinished.clear();
}

int CFtdcUserSubscriber::AddOneToFlow(void)
{
	FTDC_FLOWCTRL_SYNC;
	if (m_wSequenceSeries != TSS_QUERY && m_wSequenceSeries != TSS_DIALOG)
		return 0;

	time_t t = time(NULL);
	// check unfinished
	if (m_nUnfinished.size() >= m_nMaxUnfinished) {
		if (m_wSequenceSeries == TSS_DIALOG)
			return -2;
		
		// TSS_QUERY
		list<time_t>::iterator pos = m_nUnfinished.begin();
		if (pos != m_nUnfinished.end()) {
			time_t t2 = *pos;
			if (t - t2 > m_nTimeoutForQueryFlow) {
				m_nUnfinished.pop_front();
			} else {
				return -2;
			}
		}

	}

	// check pre-second
	if (t != m_lastTime) {
		m_nCntPerSecond = 1;
		m_lastTime = t;
	} else {
		if (m_nCntPerSecond >= m_nMaxPerSecond) {
			return -3;
		}
		++m_nCntPerSecond;
	}

	m_nUnfinished.push_back(t);
	return 0;
}

void CFtdcUserSubscriber::DequeueRequest(CFTDCPackage *pResponse)
{
	FTDC_FLOWCTRL_SYNC;

	if (m_wSequenceSeries == TSS_QUERY || m_wSequenceSeries == TSS_DIALOG) {
		if (pResponse->GetChain() == FTDC_CHAIN_LAST) {
			if (m_nUnfinished.size() > 0)
				m_nUnfinished.pop_front();
		}
	}
}

WORD CFtdcUserSubscriber::GetSequenceSeries()
{
	return m_wSequenceSeries;
}

DWORD CFtdcUserSubscriber::GetReceivedCount()
{
	if (m_pFlow == NULL)
	{
		return m_nCount;
	}
	return m_pFlow->GetCount();
}

void CFtdcUserSubscriber::SetCommPhaseNo(WORD wCommPhaseNo)
{
	if (m_pFlow != NULL)
	{
		m_pFlow->SetCommPhaseNo(wCommPhaseNo);
	}
	if (m_wCommPhaseNo != wCommPhaseNo)
	{
		m_nCount = 0;
		m_wCommPhaseNo = wCommPhaseNo;
	}
}

WORD CFtdcUserSubscriber::GetCommPhaseNo()
{
	if (m_pFlow != NULL)
	{
		return m_pFlow->GetCommPhaseNo();
	}
	return m_wCommPhaseNo;
}

void CFtdcUserSubscriber::HandleMessage(CFTDCPackage *pMessage)
{
	NET_IO_LOG0("CFtdcUserSubscriber::HandleMessage\n");
	FTDC_PACKAGE_DEBUG(pMessage);

	DequeueRequest(pMessage);

	//提交给上层应用程序
	m_pUserApiImplBase->HandleResponse(pMessage, m_wSequenceSeries);

	if (m_pFlow != NULL)
	{
		//将报文加入流中
		pMessage->Push(FTDCHLEN);
		m_pFlow->Append(pMessage->Address(), pMessage->Length());
		pMessage->Pop(FTDCHLEN);
	}
	m_nCount++;
}

TE_RESUME_TYPE CFtdcUserSubscriber::GetResumeType()
{
	return m_nResumeType;
}

void CFtdcUserSubscriber::SetResumeType(TE_RESUME_TYPE nResumeType)
{
	m_nResumeType = nResumeType;
}

void CFtdcUserSubscriber::MoveTo(int nOffset)
{
	if (m_pFlow != NULL)
	{
		m_pFlow->Truncate(nOffset);
	}
	m_nCount = nOffset;
}

/////////////////////////////////////////////////////////////////////////
CMarketDataFlowManager::CMarketDataFlowManager(const char *pszFlowPath)
{
	m_strFlowPath = pszFlowPath;
}

CMarketDataFlowManager::~CMarketDataFlowManager()
{
	CFlowMap::iterator itor = m_mapFlow.Begin();
	while (!itor.IsEnd())
	{
		delete (*itor);
		itor++;
	}
}

CFlow *CMarketDataFlowManager::GetFlow(DWORD nTopicID)
{
	CFlow **pFind = m_mapFlow.Find(nTopicID);
	if (pFind == NULL)
	{
		return NULL;
	}
	return *pFind;
}

bool CMarketDataFlowManager::RegisterTopic(DWORD nTopicID)
{
	if (GetFlow(nTopicID) != NULL)
	{
		//已经注册过了
		return false;
	}
	CFlow *pFlow  = new CUserFlow(nTopicID, m_strFlowPath.c_str(), true);
	m_mapFlow.Insert(nTopicID, pFlow);
	return true;
}

/////////////////////////////////////////////////////////////////////////
CFtdcUserResumeInfo::CFtdcUserResumeInfo(const char *pszPath, const char *pszUserApiType, 
										 const char *pszFileName)
{
	InitResumeInfo();
	m_strFullFileName = pszPath;
	m_strFullFileName += pszUserApiType;
	m_strFullFileName +=  pszFileName;
	if(!SerializeLoad())
	{
		InitResumeInfo();
		SerializeStore();
	}
}

CFtdcUserResumeInfo::~CFtdcUserResumeInfo()
{
}
const CDateType &CFtdcUserResumeInfo::GetTradingDay()
{
	return m_TradingDay;
}

const CDataCenterIDType &CFtdcUserResumeInfo::GetDataCenterID()
{
	return m_DataCenterID;
}

bool CFtdcUserResumeInfo::Update(const CDateType &TradingDay, CDataCenterIDType &DataCenterID)
{
	m_TradingDay = TradingDay;
	m_DataCenterID = DataCenterID;
	return SerializeStore();
}

void CFtdcUserResumeInfo::InitResumeInfo()
{
	m_nFileVersion = CFtdcUserResumeInfo::FILE_VERSION;
	m_TradingDay = "";
	m_DataCenterID = 0;
}

bool CFtdcUserResumeInfo::SerializeLoad()
{
	bool bRet = false;
	FILE *fp = mfopen(m_strFullFileName.c_str(), "rb");
	if (fp == NULL)
	{
		return bRet;
	}

	char buf[100];
	memset(buf, 0, sizeof(buf));
	if (fread(buf, 1, sizeof(buf)-1, fp) > 0)
	{
		CCSVParser parser(buf);
		int nItem = 0;
		for (; ;nItem++)
		{
			char *pToken = parser.GetNextToken();
			if (pToken == NULL)
			{
				break;
			}
			switch(nItem) {
			case 0:
				m_nFileVersion = atoi(pToken);
				break;
			case 1:
				m_TradingDay = pToken;
				break;
			case 2:
				m_DataCenterID = atoi(pToken);
				break;
			default:
				break;
			}
		}
		if (nItem == 3 && m_nFileVersion == CFtdcUserResumeInfo::FILE_VERSION)
		{
			bRet = true;
		}
	}
	fclose(fp);

	return bRet;
}

bool CFtdcUserResumeInfo::SerializeStore()
{
	bool bRet = false;
	FILE *fp = mfopen(m_strFullFileName.c_str(), "wb");
	if (fp == NULL)
	{
		return bRet;
	}
	if (fprintf(fp, "%d,%s,%d\n", m_nFileVersion, m_TradingDay.getValue(), 
		m_DataCenterID.getValue()) >0)
	{
		bRet = true;
	}
	fclose(fp);
	return bRet;
}

/////////////////////////////////////////////////////////////////////////

CFtdcUserApiImplBase::CFtdcUserApiImplBase(const char *pszFlowPath,
										   const char *pszUserApiType,
										   CReactor *pReactor)
:CNsSessionFactory(pReactor, 1), 
m_ResumeInfo(pszFlowPath, pszUserApiType, "resume.con")
{
	m_pSpi = NULL;
	
	m_reqPackage.ConstructAllocate(FTDC_PACKAGE_MAX_SIZE, 1000);
	
	m_nSessionID = 0;
	m_dwHeartbeatTimeout = 30;		//心跳超时缺省为30秒
	
	m_pDialogReqFlow = NULL;
	m_pQueryReqFlow = NULL;
	m_pPrivateFlow = NULL;
	m_pUserFlow = NULL;
	m_pPublicFlow = NULL;	
	m_strFlowPath = pszFlowPath;
	m_strUserApiType = pszUserApiType;

	m_mapSubscriber[TSS_DIALOG] = new CFtdcUserSubscriber(this, NULL, TSS_DIALOG);
	m_mapSubscriber[TSS_QUERY] = new CFtdcUserSubscriber(this, NULL, TSS_QUERY);

	m_pMarketDataFlowManager = new CMarketDataFlowManager(pszFlowPath);
	
	m_fpRequstDump = NULL;
	m_fpResponseDump = NULL;

	m_bManagedResume = false;
	
	m_pPipeEventHandler=NULL;

	m_bMultiCastFlag=false;
	m_vMultiTopicID.clear();
}
	
CFtdcUserApiImplBase::~CFtdcUserApiImplBase()
{
	CNsSessionFactory::Stop();
	CUserSubscriberMap::iterator itor = m_mapSubscriber.begin();
	for (;itor!=m_mapSubscriber.end(); itor++)
	{
		delete (*itor).second;
	}
	RemoveDialogFlow();
	RemoveQueryFlow();
	delete m_pPrivateFlow;
	m_pPrivateFlow = NULL;
	delete m_pUserFlow;
	m_pUserFlow = NULL;
	delete m_pPublicFlow;
	m_pPublicFlow = NULL;
	delete m_pMarketDataFlowManager;
	m_pMarketDataFlowManager = NULL;

	if (m_fpRequstDump != NULL)
	{
		fclose(m_fpRequstDump);
	}
	if (m_fpResponseDump != NULL)
	{
		fclose(m_fpResponseDump);
	}

}

void CFtdcUserApiImplBase::Release()
{
	m_pReactor->Stop();
	Stop();
	//m_pReactor->Join();
	//CReactor *p = m_pReactor;
    // 修改API退出后，管道没有被关闭问题20140602
    //delete m_pPipeEventHandler;
	delete this;
	//delete p;
}
void CFtdcUserApiImplBase::SetMultiCast(bool bMultiCast)
{
	m_bMultiCastFlag=bMultiCast;
}

void CFtdcUserApiImplBase::RegMultiTopicID(int TopicID)
{
	m_vMultiTopicID.push_back(TopicID);
}
void CFtdcUserApiImplBase::Init(int nPrivatePort)
{
	//add by zbz
	m_pPipeEventHandler=new CPipeEventHandler((CSelectReactor*)m_pReactor,nPrivatePort);
	m_pReactor->Create();	
	Start();
}

int CFtdcUserApiImplBase::Join()
{
	return m_pReactor->Join();
}

const char *CFtdcUserApiImplBase::GetTradingDay()
{
	return m_ResumeInfo.GetTradingDay();
}

void CFtdcUserApiImplBase::RegisterFront(char *pszFrontAddress)
{
	if (strncmp(pszFrontAddress,"shm",3)==0)
	{
		((CSelectReactor *) m_pReactor)->SetNoShmChannelFlag(false);
	}
	
	RegisterConnecter(pszFrontAddress);
}

void CFtdcUserApiImplBase::RegisterNameServer(char *pszFrontAddress)
{
	CNsSessionFactory::RegisterNameServer(pszFrontAddress);
}

void CFtdcUserApiImplBase::RegisterSpi(FTDCUSERSPI *pSpi)
{
	m_pSpi = pSpi;	
}

void CFtdcUserApiImplBase::CreateSubscriber(int nTopicID, CFlow *pFlow, TE_RESUME_TYPE nResumeType)
{
	m_bManagedResume = true;

	CUserSubscriberMap::iterator itor = m_mapSubscriber.find(WORD(nTopicID));
	CFtdcUserSubscriber *pSubscriber = NULL;
	if (itor == m_mapSubscriber.end())
	{
		pSubscriber = new CFtdcUserSubscriber(this, pFlow, nTopicID);
		m_mapSubscriber[(WORD)nTopicID] = pSubscriber;
	}
	else
	{
		pSubscriber = (*itor).second;
	}
	pSubscriber->SetResumeType(nResumeType);
}

void CFtdcUserApiImplBase::SubscribeMarketDataTopic(int nTopicID, TE_RESUME_TYPE nResumeType)
{
	m_pMarketDataFlowManager->RegisterTopic(nTopicID);
	
	CreateSubscriber(nTopicID, (CUserFlow *)m_pMarketDataFlowManager->GetFlow((DWORD)nTopicID),
		nResumeType);
}

void CFtdcUserApiImplBase::SubscribePrivateTopic(TE_RESUME_TYPE nResumeType)
{
	if (m_pPrivateFlow == NULL)
	{
		m_pPrivateFlow = new CUserFlow("Private", m_strFlowPath.c_str(), true);
	}
	CreateSubscriber(TSS_PRIVATE, m_pPrivateFlow, nResumeType);
}

void CFtdcUserApiImplBase::SubscribePublicTopic(TE_RESUME_TYPE nResumeType)
{
	if (m_pPublicFlow == NULL)
	{
		m_pPublicFlow = new CUserFlow("Public",  m_strFlowPath.c_str(), true);
	}
	CreateSubscriber(TSS_PUBLIC, m_pPublicFlow, nResumeType);
}

void CFtdcUserApiImplBase::SubscribeUserTopic(TE_RESUME_TYPE nResumeType)
{
	if (m_pUserFlow == NULL)
	{
		m_pUserFlow = new CUserFlow("User", m_strFlowPath.c_str(), true);
	}
	CreateSubscriber(TSS_USER, m_pUserFlow, nResumeType);
}

int CFtdcUserApiImplBase::SubMarketData(char *ppInstrumentID[], int nCount)
{
	//b_ppInstrumentID=ppInstrumentID;
	
	i_count=nCount;
	m_mutexAction.Lock();
#ifdef LIB_MDUSER_API_EXPORT
	m_reqPackage.PreparePackage(FTD_TID_ReqTopicSearch, FTDC_CHAIN_CONTINUE, FTD_VERSION);
	int i =0;
	for(;i<nCount;i++)
	{
		CFTDSpecificInstrumentField specificInstrumentField;
		specificInstrumentField.InstrumentID = ppInstrumentID[i];
		m_instrumentid.push_back(specificInstrumentField.InstrumentID);
		int ret = FTDC_ADD_FIELD(&m_reqPackage, &specificInstrumentField);
		if(ret < 0)
		{
			int nRet = RequestToDialogFlow();
			m_reqPackage.PreparePackage(FTD_TID_ReqTopicSearch, FTDC_CHAIN_CONTINUE, FTD_VERSION);
			FTDC_ADD_FIELD(&m_reqPackage, &specificInstrumentField);
		}
	}
	m_reqPackage.SetChain(FTDC_CHAIN_LAST);

#else
	m_reqPackage.PreparePackage(FTD_TID_ReqSubMarketData, FTDC_CHAIN_CONTINUE, FTD_VERSION);
	int i =0;
	for(;i<i_count;i++)
	{
		CFTDSpecificInstrumentField specificInstrumentField;
		specificInstrumentField.InstrumentID = ppInstrumentID[i];
		int ret = FTDC_ADD_FIELD(&m_reqPackage, &specificInstrumentField);
		if(ret < 0)
		{
			int nRet = RequestToDialogFlow();
			m_reqPackage.PreparePackage(FTD_TID_ReqSubMarketData, FTDC_CHAIN_CONTINUE, FTD_VERSION);
			FTDC_ADD_FIELD(&m_reqPackage, &specificInstrumentField);
		}
		InstrumetIdMap::iterator  itertmp= instrumentidmap.find(specificInstrumentField.InstrumentID);
		if(itertmp != instrumentidmap.end())
		{
			itertmp->second=specificInstrumentField.InstrumentID;
		}else{
			instrumentidmap.insert(InstrumetIdMap::value_type(specificInstrumentField.InstrumentID,specificInstrumentField.InstrumentID));		
		}
	}
	
	RequestToDialogFlow();
	
	//最后发送一个包,说明已经结束，并将订阅的行情主题发送出去
	m_reqPackage.PreparePackage(FTD_TID_ReqSubscribeTopic, FTDC_CHAIN_LAST, FTD_VERSION);
	CFTDDisseminationField disseminationField;
	CUserSubscriberMap::iterator itor = m_mapSubscriber.begin();
	for (; itor!=m_mapSubscriber.end(); itor++)
	{
		CFtdcUserSubscriber *pSubscriber = (*itor).second;
		disseminationField.SequenceSeries = pSubscriber->GetSequenceSeries();
		switch(pSubscriber->GetResumeType())
		{
		case TERT_RESTART:
			disseminationField.SequenceNo = 0;
			break;
		case TERT_RESUME:
			disseminationField.SequenceNo = pSubscriber->GetReceivedCount();
			break;
		case TERT_QUICK:
			disseminationField.SequenceNo = -1;
			break;
		default:
			break;
		}
		FTDC_ADD_FIELD(&m_reqPackage, &disseminationField);
	}

#endif
	//最后发送一个包,说明已经结束，并将订阅的行情主题发送出去
	
	//if(m_reqPackage.Length() > 0)
	RequestToDialogFlow();

	m_mutexAction.UnLock();
	return 0;
}

int CFtdcUserApiImplBase::UnSubMarketData(char *ppInstrumentID[], int nCount)
{
	m_mutexAction.Lock();
	
	m_reqPackage.PreparePackage(FTD_TID_ReqUnSubMarketData, FTDC_CHAIN_CONTINUE, FTD_VERSION);
	
	int i =0;
	for(;i<nCount;i++)
	{
		CFTDSpecificInstrumentField specificInstrumentField;
		specificInstrumentField.InstrumentID = ppInstrumentID[i];
		int ret = FTDC_ADD_FIELD(&m_reqPackage, &specificInstrumentField);
		if(ret < 0)
		{
			int nRet = RequestToDialogFlow();
			m_reqPackage.PreparePackage(FTD_TID_ReqUnSubMarketData, FTDC_CHAIN_CONTINUE, FTD_VERSION);
			FTDC_ADD_FIELD(&m_reqPackage, &specificInstrumentField);
		}
		InstrumetIdMap::iterator  itertmp= instrumentidmap.find(specificInstrumentField.InstrumentID);
		if(itertmp != instrumentidmap.end())
		{
			instrumentidmap.erase(itertmp);
		}
	}	

 	m_reqPackage.SetChain(FTDC_CHAIN_LAST);
	RequestToDialogFlow();
	
//	if(m_reqPackage.Length() > 0)
//		int nRet = RequestToDialogFlow();

	m_mutexAction.UnLock();
	return 0;
}

void CFtdcUserApiImplBase::SetHeartbeatTimeout(unsigned int timeout)
{
	m_dwHeartbeatTimeout = timeout;
}

int CFtdcUserApiImplBase::OpenRequestLog(const char *pszReqLogFileName)
{
	if (m_fpRequstDump != NULL)
	{
		fclose(m_fpRequstDump);
		m_fpRequstDump = NULL;
	}
	m_fpRequstDump = fopen(pszReqLogFileName, "ab");
	if (m_fpRequstDump == NULL)
	{
		NET_EXCEPTION_LOG1("Can't open request log file [%s]\n", pszReqLogFileName);
		
		return -1;
	}
	return 0;
}

int CFtdcUserApiImplBase::OpenResponseLog(const char *pszRspLogFileName)
{
	if (m_fpResponseDump != NULL)
	{
		fclose(m_fpResponseDump);
		m_fpResponseDump = NULL;
	}
	m_fpResponseDump = fopen(pszRspLogFileName, "ab");
	if (m_fpResponseDump == NULL)
	{
		NET_EXCEPTION_LOG1("Can't open request log file [%s]\n", pszRspLogFileName);
		
		return -1;
	}
	return 0;
}

int CFtdcUserApiImplBase::ReqUserLogin(FTDCREQUSERLOGINFIELD *pReqUserLoginField, int nRequestID)
{
	m_mutexAction.Lock();
	CFTDReqUserLoginField reqUserloginField;
	memcpy(&reqUserloginField, pReqUserLoginField, sizeof(CFTDReqUserLoginField));
	if (m_bManagedResume)
	{
		reqUserloginField.TradingDay = m_ResumeInfo.GetTradingDay();
		reqUserloginField.DataCenterID = m_ResumeInfo.GetDataCenterID();
	}
		
	reqUserloginField.InterfaceProductInfo = INTERFACE_PRODUCT_INFO;

	//多播登录方式
	char buf[100];
	if (!m_bMultiCastFlag)
		sprintf(buf, "FTDC %d", (int)m_reqPackage.GetFTDCHeader()->Version);
	else
		strcpy(buf,"Multi");
	reqUserloginField.ProtocolInfo = buf;

    // 填入本机IP和MAC, 公网IP可以在服务端获取  -- lidp 20140715
	memset(buf,0x00,sizeof(buf));
    if (GetSessionLocalMac(buf) > 0){
        reqUserloginField.MacAddress = buf;
    }
  
    CFTDCSession *pSession = (CFTDCSession *)GetSession(m_nSessionID);
	if( pSession )
	{
		sprintf(buf, "%s", pSession->GetChannel()->GetLocalName());
	}else
	{
		buf[0]='\0';
	}
    reqUserloginField.IPAddress = buf;

	m_reqPackage.PreparePackage(FTD_TID_ReqUserLogin, FTDC_CHAIN_LAST, FTD_VERSION);
	m_reqPackage.SetRequestId(nRequestID);
	FTDC_ADD_FIELD(&m_reqPackage, &reqUserloginField);
	
	CFTDDisseminationField disseminationField;
	//多播登录方式,发送多播行情主题
	if (m_bMultiCastFlag)
	{
		for (int i=0;i<m_vMultiTopicID.size();i++)
		{
			disseminationField.SequenceSeries = m_vMultiTopicID[i];
			disseminationField.SequenceNo=0;
			FTDC_ADD_FIELD(&m_reqPackage, &disseminationField);
		}
	}
	else
	{
		CUserSubscriberMap::iterator itor = m_mapSubscriber.begin();
		for (; itor!=m_mapSubscriber.end(); itor++)
		{
			CFtdcUserSubscriber *pSubscriber = (*itor).second;
			disseminationField.SequenceSeries = pSubscriber->GetSequenceSeries();
			switch(pSubscriber->GetResumeType())
			{
			case TERT_RESTART:
				disseminationField.SequenceNo = 0;
				break;
			case TERT_RESUME:
				disseminationField.SequenceNo = pSubscriber->GetReceivedCount();
				break;
			case TERT_QUICK:
				disseminationField.SequenceNo = -1;
				break;
			default:
				break;
			}
			FTDC_ADD_FIELD(&m_reqPackage, &disseminationField);
		}
	}

	int nRet = RequestDirectly();
	
	m_mutexAction.UnLock();
	
	return nRet;
}


int CFtdcUserApiImplBase::HandlePackage(CFTDCPackage *pFTDCPackage, CFTDCSession *pSession)
{
	NET_IO_LOG0("CFtdcUserApiImplBase::HandlePackage\n");
	FTDC_PACKAGE_DEBUG(pFTDCPackage);
	if (pFTDCPackage->GetTID() == FTD_TID_RspUserLogin)
	{
		CFTDRspUserLoginField rspUserLoginField;
		if (FTDC_GET_SINGLE_FIELD(pFTDCPackage, &rspUserLoginField) <= 0)
		{
			return 0;
		}
		CFTDRspInfoField rspInfoField;
		if (FTDC_GET_SINGLE_FIELD(pFTDCPackage, &rspInfoField) <= 0)
		{
			return 0;
		}
		if (rspInfoField.ErrorID == 0)
		{
			m_ResumeInfo.Update(rspUserLoginField.TradingDay, 
				rspUserLoginField.DataCenterID);
			CUserSubscriberMap::iterator itor = m_mapSubscriber.begin();
			for (; itor!=m_mapSubscriber.end(); itor++)
			{
				CFtdcUserSubscriber *pSubscriber = (*itor).second;
				if (pSubscriber->GetSequenceSeries() == TSS_DIALOG ||
					pSubscriber->GetSequenceSeries() == TSS_QUERY )
				{
					//对话流和查询流的清理依靠连接中断、重连完成
					continue;
				}
				
				pSubscriber->SetCommPhaseNo(CDate::DateToLong(m_ResumeInfo.GetTradingDay()));
			}
		}
	}
	else if(pFTDCPackage->GetTID() == FTD_TID_RtnDepthMarketData) 
	{
		HandleResponse(pFTDCPackage, pFTDCPackage->GetRequestId());
		return 0;
	}
	
	HandleResponse(pFTDCPackage, pFTDCPackage->GetFTDCHeader()->SequenceSeries);
	return 0;
}
	
CSession *CFtdcUserApiImplBase::CreateSession(CChannel *pChannel, DWORD)
{
	CFTDCSession *pSession = new CFTDCSession(m_pReactor, pChannel);
	CreateDialogFlow();
	pSession->Publish(m_pDialogReqFlow, TSS_DIALOG, 0);
	CreateQueryFlow();
	pSession->Publish(m_pQueryReqFlow, TSS_QUERY, 0);

	CUserSubscriberMap::iterator itor = m_mapSubscriber.begin();
	for (;itor!=m_mapSubscriber.end(); itor++)
	{
		pSession->RegisterSubscriber((*itor).second);
	}

	pSession->RegisterPackageHandler(this);
	
	if(m_dwHeartbeatTimeout != 0)
	{
		pSession->SetHeartbeatTimeout(m_dwHeartbeatTimeout);
	}
	return pSession;
}

void CFtdcUserApiImplBase::OnSessionConnected(CSession *pSession)
{
	// flow control added by zhangjie
	m_mapSubscriber[TSS_DIALOG]->CleanControl();
	m_mapSubscriber[TSS_QUERY]->CleanControl();
	m_mapSubscriber[TSS_DIALOG]->MoveTo(0);
	m_mapSubscriber[TSS_QUERY]->MoveTo(0);

	m_nSessionID = pSession->GetSessionID();
	CNsSessionFactory::OnSessionConnected(pSession);
	if (m_pSpi != NULL)
	{
		m_pSpi->OnFrontConnected();
	}
}

void CFtdcUserApiImplBase::OnSessionDisconnected(CSession *pSession, int nReason)
{
	m_mutexAction.Lock();
	CNsSessionFactory::OnSessionDisconnected(pSession, nReason);
	
	m_nSessionID = 0;
	
	if (m_pSpi != NULL)
	{
		m_pSpi->OnFrontDisconnected(nReason);
	}
	RemoveDialogFlow();
	RemoveQueryFlow();
	m_storageTopicDepthMarketData.Clear();
	instrumentidmap.clear();
	m_mutexAction.UnLock();
}

void CFtdcUserApiImplBase::OnSessionWarning(CSession *pSession, int nReason, int nParam)
{
	if (nReason == MSG_XMPWARNING_RECVHEARTBEAT)
	{
		if (m_pSpi != NULL)
		{
			m_pSpi->OnHeartBeatWarning(nParam);
		}
	}
}

int CFtdcUserApiImplBase::RequestToDialogFlow()
{
	if (m_pDialogReqFlow == NULL)
	{
		return -1;
	}

	// flow control added by zhangjie
	int rtn = m_mapSubscriber[TSS_DIALOG]->AddOneToFlow();
	if (rtn)
		return rtn;

	m_reqPackage.MakePackage();
	rtn = m_pDialogReqFlow->Append(m_reqPackage.Address(), m_reqPackage.Length());
	if (rtn < 0)
	{
		return -1;
	}
	return 0;
}

void CFtdcUserApiImplBase::CreateDialogFlow()
{
	RemoveDialogFlow();
	m_pDialogReqFlow = new CFtdcUserDialogFlow(false, 10000, 10000);
	
	//add by zbz
	((CFtdcUserDialogFlow *)m_pDialogReqFlow)->AttachObserver(m_pPipeEventHandler);
}

void CFtdcUserApiImplBase::RemoveDialogFlow()
{
	delete m_pDialogReqFlow;
	m_pDialogReqFlow = NULL;
}

int CFtdcUserApiImplBase::RequestToQueryFlow()
{
	if (m_pQueryReqFlow == NULL)
	{
		return -1;
	}

	// flow control added by zhangjie
	int rtn = m_mapSubscriber[TSS_QUERY]->AddOneToFlow();
	if (rtn)
		return rtn;

	m_reqPackage.MakePackage();
	rtn = m_pQueryReqFlow->Append(m_reqPackage.Address(), m_reqPackage.Length());
	if (rtn < 0)
	{
		return -1;
	}
	return 0;
}

void CFtdcUserApiImplBase::CreateQueryFlow()
{
	RemoveQueryFlow();
	m_pQueryReqFlow = new CFtdcUserDialogFlow(false, 10000, 10000);
}

void CFtdcUserApiImplBase::RemoveQueryFlow()
{
	delete m_pQueryReqFlow;
	m_pQueryReqFlow = NULL;
}

int CFtdcUserApiImplBase::RequestDirectly()
{
	NET_IO_LOG1("CFtdcUserApiImplBase::RequestDirectly SessionID=%d\n", m_nSessionID);
	CFTDCSession *pSession = (CFTDCSession *)GetSession(m_nSessionID);
	if (pSession == NULL)
	{
		return -1;
	}
	
	NET_IO_LOG0("CFtdcUserApiImplBase::RequestDirectly Send\n");
	pSession->SendRequestPackage(&m_reqPackage);
	
	return 0;
}

void CFtdcUserApiImplBase::OnIntlRtnDepthMarketData(CFTDCPackage *pMessage, WORD wSequenceSeries,bool bDoodle)
{
	CFTDMarketDataUpdateTimeField fieldMarketDataUpdateTime;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &fieldMarketDataUpdateTime) <= 0)
	{
		//必须找到合约代码
		return;
	}
	CTopicDepthMarketDataField *pTopicDepthMarketData = m_storageTopicDepthMarketData.GetBySequenceSeriesInstrumentID(
		wSequenceSeries, fieldMarketDataUpdateTime.InstrumentID);
	if (pTopicDepthMarketData == NULL)
	{
		CTopicDepthMarketDataField fieldTopicDepthMarketDataField;
		memset(&fieldTopicDepthMarketDataField, 0, sizeof(fieldTopicDepthMarketDataField));
		fieldTopicDepthMarketDataField.InstrumentID = fieldMarketDataUpdateTime.InstrumentID;
		fieldTopicDepthMarketDataField.SequenceSeries = wSequenceSeries;
		pTopicDepthMarketData = m_storageTopicDepthMarketData.
			AppendData(fieldTopicDepthMarketDataField);
	}
	CopyMarketDataUpdateTimeEntity(pTopicDepthMarketData, &fieldMarketDataUpdateTime);

	TFieldHeader fieldHeader;
	CFieldTypeIterator titor = pMessage->GetFieldTypeIterator();
	while (!titor.IsEnd())
	{
		titor.RetrieveHeader(fieldHeader);
		switch(fieldHeader.FieldID)
		{
		GET_PART_MARKETDATA(MarketDataBase);
		GET_PART_MARKETDATA(MarketDataStatic);
		GET_PART_MARKETDATA(MarketDataLastMatch);	
		GET_PART_MARKETDATA(MarketDataBestPrice);
		GET_PART_MARKETDATA(MarketDataBid23);
		GET_PART_MARKETDATA(MarketDataAsk23);
		GET_PART_MARKETDATA(MarketDataBid45);
		GET_PART_MARKETDATA(MarketDataAsk45);
		GET_PART_MARKETDATA(MarketDataExchangeID);
		default:
			break;
		}
		titor.Next();
	}
	
	if (m_pSpi != NULL)
	{
		m_pSpi->OnPackageStart((int)wSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
		m_pSpi->OnRtnDepthMarketData((FTDCDEPTHMARKETDATAFIELD*)pTopicDepthMarketData);
		m_pSpi->OnPackageEnd((int)wSequenceSeries, pMessage->GetFTDCHeader()->SequenceNumber);
	}
}

void CFtdcUserApiImplBase::OnIntlRtnDissemination(CFTDCPackage *pMessage, WORD wSequenceSeries)
{
	if (m_bMultiCastFlag)
	{
		CFTDDisseminationField disseminationField;
		CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDDisseminationField::m_Describe);
		while (!itor.IsEnd())
		{
			itor.Retrieve(&disseminationField);
			if (disseminationField.SequenceNo.getValue()==0)
			{
				if (m_pSpi != NULL)
					m_pSpi->OnStopMultiTopic((int)disseminationField.SequenceSeries.getValue());
			}
			itor.Next();
		}
	}
	else
	{	
		CFTDDisseminationField disseminationField;
		CNamedFieldIterator itor = pMessage->GetNamedFieldIterator(&CFTDDisseminationField::m_Describe);
		while (!itor.IsEnd())
		{
			itor.Retrieve(&disseminationField);
			CUserSubscriberMap::iterator i = m_mapSubscriber.find(
				disseminationField.SequenceSeries);
			if (i != m_mapSubscriber.end())
			{
				(*i).second->MoveTo(disseminationField.SequenceNo);
			}
			itor.Next();
		}
	}
}

void CFtdcUserApiImplBase::OnRtnDepthMarketData(CFTDDepthMarketDataField *pMarketData, WORD wSequenceSeries)
{
	CTopicDepthMarketDataField *pTopicDepthMarketData = m_storageTopicDepthMarketData.GetBySequenceSeriesInstrumentID(
		wSequenceSeries, pMarketData->InstrumentID);
	if (pTopicDepthMarketData == NULL)
	{
		CTopicDepthMarketDataField fieldTopicDepthMarketDataField;
		memset(&fieldTopicDepthMarketDataField, 0, sizeof(fieldTopicDepthMarketDataField));
		fieldTopicDepthMarketDataField.InstrumentID = pMarketData->InstrumentID;
		fieldTopicDepthMarketDataField.SequenceSeries = wSequenceSeries;
		pTopicDepthMarketData = m_storageTopicDepthMarketData.AppendData(fieldTopicDepthMarketDataField);
	}
	CopyDepthMarketDataEntity(pTopicDepthMarketData, pMarketData);
}

//接受topic查询
void CFtdcUserApiImplBase::OnIntlTopicSearch(CFTDCPackage *pMessage, WORD wSequenceSeries,bool bDoodle)
{
	
	CFTDRspInfoField rspInfoField;
	if (FTDC_GET_SINGLE_FIELD(pMessage, &rspInfoField) <= 0)
	{
		return;
	}
	CFTDTopicSearchField Specifictopic;
	CNamedFieldIterator itor_topic = pMessage->GetNamedFieldIterator(&CFTDTopicSearchField::m_Describe);
	while (!itor_topic.IsEnd())
	{
		itor_topic.Retrieve(&Specifictopic);
		itor_topic.Next();
		SubscribeMarketDataTopic(Specifictopic.TopicID.getValue(), TERT_QUICK);
	}
	
	m_mutexAction.Lock();

	m_reqPackage.PreparePackage(FTD_TID_ReqSubMarketData, FTDC_CHAIN_CONTINUE, FTD_VERSION);
	vector<CInstrumentIDType>::iterator iterinstr;
	for(iterinstr=m_instrumentid.begin();iterinstr!=m_instrumentid.end();iterinstr++)
	{
		CFTDSpecificInstrumentField specificInstrumentField;
		specificInstrumentField.InstrumentID = *iterinstr;
		InstrumetIdMap::iterator  itertmp= instrumentidmap.find(specificInstrumentField.InstrumentID);
		if(itertmp != instrumentidmap.end())
		{
			itertmp->second=specificInstrumentField.InstrumentID;
		}else{
			
			int ret = FTDC_ADD_FIELD(&m_reqPackage, &specificInstrumentField);
			if(ret < 0)
			{
				int nRet = RequestToDialogFlow();
				m_reqPackage.PreparePackage(FTD_TID_ReqSubMarketData, FTDC_CHAIN_CONTINUE, FTD_VERSION);
				FTDC_ADD_FIELD(&m_reqPackage, &specificInstrumentField);
			}
			instrumentidmap.insert(InstrumetIdMap::value_type(specificInstrumentField.InstrumentID,specificInstrumentField.InstrumentID));		
		}
	}
	m_instrumentid.clear();
	RequestToDialogFlow();

	//最后发送一个包,说明已经结束，并将订阅的行情主题发送出去
	m_reqPackage.PreparePackage(FTD_TID_ReqSubscribeTopic, FTDC_CHAIN_LAST, FTD_VERSION);
	CFTDDisseminationField disseminationField;
	CUserSubscriberMap::iterator itor = m_mapSubscriber.begin();
	for (; itor!=m_mapSubscriber.end(); itor++)
	{
		CFtdcUserSubscriber *pSubscriber = (*itor).second;
		disseminationField.SequenceSeries = pSubscriber->GetSequenceSeries();
		switch(pSubscriber->GetResumeType())
		{
		case TERT_RESTART:
			disseminationField.SequenceNo = 0;
			break;
		case TERT_RESUME:
			disseminationField.SequenceNo = pSubscriber->GetReceivedCount();
			break;
		case TERT_QUICK:
			disseminationField.SequenceNo = -1;
			break;
		default:
			break;
		}
		FTDC_ADD_FIELD(&m_reqPackage, &disseminationField);
	}
	int nRet = RequestToDialogFlow();

	m_mutexAction.UnLock();

}

CReactor *CFtdcUserApiImplBase::GetReactor()
{
	return m_pReactor;
}

void  CFtdcUserApiImplBase::OnMultiHeartbeat(char *CurrTime,char *MultiCastIP)
{
	if (m_pSpi != NULL)
		m_pSpi->OnMultiHeartbeat(CurrTime,MultiCastIP);
}

///获得Session所使用的本地IPv4地址对应的MAC
///@param	ipAddressBuffer 存储MAC地址的buffer, buffer的长度不小于18
///@return	写入buffer的数据长度，小于等于0表示获取MAC错误；获得MAC地址格式为00:0C:29:F1:07:B5
///@author  lidp 20140716
int CFtdcUserApiImplBase::GetSessionLocalMac(char * macAddressBuffer)
{
    // 由于inet_ntoa调用会覆盖前一次的返回值，所以需要每次调用都保存其返回值
	char sessionIpAddrBuf[50];
    memset(sessionIpAddrBuf, 0, sizeof(sessionIpAddrBuf));
    
    CFTDCSession *pSession = (CFTDCSession *)GetSession(m_nSessionID);
    if (pSession == NULL)
    {
        return -1;
    }
    // 获得session的本地IP
    int sessionfd = pSession->GetChannel()->GetId();    char * sessionIP = pSession->GetChannel()->GetLocalName();
    memcpy(sessionIpAddrBuf, sessionIP, sizeof(sessionIpAddrBuf));

#ifdef WIN32
	
	GetMacByCmd(macAddressBuffer);
	
    ULONG ulOutBufLen = (unsigned long)sizeof(IP_ADAPTER_INFO);
	
    PIP_ADAPTER_INFO pAdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) { // 分配内存失败
        return -1;
    }
	
    // 第一次调用，获得pAdapterInfo的必要大小，存储在ulOutBufLen，防止分配的内存过小
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
        if (pAdapterInfo == NULL) { // 分配内存失败
            return -1;
        }
    }
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR) {
        PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
        while (pAdapter) {
            if (strncmp(sessionIpAddrBuf, pAdapter->IpAddressList.IpAddress.String, 16) != 0){
                pAdapter = pAdapter->Next;
                continue;
            }
            // 找到了session local IP对应的MAC
            for (UINT i = 0; i < pAdapter->AddressLength; i++)
            {
                sprintf(macAddressBuffer+i*3, "%02X%c", pAdapter->Address[i], i == pAdapter->AddressLength - 1 ? '\0' : ':');
            }
			//printf("Ipsession= %s, pAdapter ip%s,mac %s\n",sessionIpAddrBuf,pAdapter->IpAddressList.IpAddress.String,macAddressBuffer);
            break;
        }
    }
	if (pAdapterInfo)
	{
		free(pAdapterInfo);
	}
	
#else
    char localIpAddrBuf[50];
    memset(localIpAddrBuf, 0x00, sizeof(localIpAddrBuf));
    // 根据IP获得interface name
    struct ifaddrs *ifaddrHeader, *ifaddrItor;
	
    if(getifaddrs(&ifaddrHeader) == -1) {
        return -1;
    }
	
    for(ifaddrItor = ifaddrHeader; ifaddrItor != NULL; ifaddrItor = ifaddrItor->ifa_next) {
        if (ifaddrItor->ifa_addr == NULL)
            continue;
		
        if(ifaddrItor->ifa_addr->sa_family != AF_INET) // 只获取TCP/IP网卡的信息
            continue;
		
        
        struct sockaddr_in *sin = NULL;
        sin = (struct sockaddr_in *)ifaddrItor->ifa_addr;
        char * localIPAddr = inet_ntoa(sin->sin_addr);
		
        memcpy(localIpAddrBuf, localIPAddr, strlen(localIPAddr));
		int i=strncmp(localIpAddrBuf,sessionIpAddrBuf,strlen(localIpAddrBuf));
		
        // 192.168.223.123 最多16位 
        if( i == 0 ){
            // 使用ioctl，根据interface name获得MAC地址
            struct ifreq ifr;
            sprintf(ifr.ifr_name, "%s", ifaddrItor->ifa_name);
			
            if(ioctl(sessionfd, SIOCGIFHWADDR, (char *)&ifr) < 0)
            {
                freeifaddrs(ifaddrHeader);
                continue;
            }
			
            sprintf(macAddressBuffer, "%02X:%02X:%02X:%02X:%02X:%02X",
                (unsigned char)ifr.ifr_ifru.ifru_hwaddr.sa_data[0],
                (unsigned char)ifr.ifr_ifru.ifru_hwaddr.sa_data[1],
                (unsigned char)ifr.ifr_ifru.ifru_hwaddr.sa_data[2],
                (unsigned char)ifr.ifr_ifru.ifru_hwaddr.sa_data[3],
                (unsigned char)ifr.ifr_ifru.ifru_hwaddr.sa_data[4],
                (unsigned char)ifr.ifr_ifru.ifru_hwaddr.sa_data[5]
                );
			break;
        }
    }
    freeifaddrs(ifaddrHeader); // 释放存储NIC信息的链表结构
#endif

    return sizeof(macAddressBuffer);
}

////////////////////////////////////////////////////////////////////////////////////////////
//apithread
CApiWorkThread::CApiWorkThread()
{
	m_pApiSession = NULL;
}

CApiWorkThread::~CApiWorkThread()
{
	
}

void CApiWorkThread::RegisterIO(CEventHandler *pEventHandler)
{
	if (pEventHandler != NULL)
	{
		m_pApiSession = pEventHandler;
	}
}

void CApiWorkThread::RemoveIO(CEventHandler *pEventHandler)
{
	if (m_pApiSession == pEventHandler)
	{
		m_pApiSession = NULL;
	}
}

void CApiWorkThread::DispatchIOs()
{
	int nWriteID=0;
	int nReadID=0;
	if (m_pApiSession != NULL)
	{
		m_pApiSession->GetIds(&nReadID,&nWriteID);
	}
	SyncTime();
	if (m_pApiSession != NULL)
	{
		m_pApiSession->HandleInput();
	}
	if (m_pApiSession != NULL)
	{
		m_pApiSession->HandleOutput();
	}
}

