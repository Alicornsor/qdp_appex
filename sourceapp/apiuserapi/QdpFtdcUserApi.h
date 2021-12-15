/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company QuantDo
///@file QdpFtdcUserApi.h
///@brief 定义了客户端接口
///@history 
///20150520	徐忠华	创建该文件
/////////////////////////////////////////////////////////////////////////

#if !defined(QDP_FTDCUSERAPI_H)
#define QDP_FTDCUSERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QdpFtdcUserApiStruct.h"

#if defined(USERAPI_IS_LIB) && defined(WIN32)
#ifdef LIB_USER_API_EXPORT
#define USER_API_EXPORT __declspec(dllexport)
#else
#define USER_API_EXPORT __declspec(dllimport)
#endif
#else
#define USER_API_EXPORT 
#endif


class CQdpFtdcUserSpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason){};
		
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse){};
	
	///报文回调开始通知。当API收到一个报文后，首先调用本方法，然后是各数据域的回调，最后是报文回调结束通知。
	///@param nTopicID 主题代码（如私有流、公共流、行情流等）
	///@param nSequenceNo 报文序号
	virtual void OnPackageStart(int nTopicID, int nSequenceNo){};
	
	///报文回调结束通知。当API收到一个报文后，首先调用报文回调开始通知，然后是各数据域的回调，最后调用本方法。
	///@param nTopicID 主题代码（如私有流、公共流、行情流等）
	///@param nSequenceNo 报文序号
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo){};

	///没有权限的多播订阅主题
	///@param nTopicID 被主题代码
	virtual void OnStopMultiTopic(int nTopicID){};

	//新增多播心跳接口 add by zbz 20150304
	virtual void OnMultiHeartbeat(char *CurrTime,char *MultiCastIP) {};

	///错误应答
	virtual void OnRspError(CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户登录应答
	virtual void OnRspUserLogin(CQdpFtdcRspUserLoginField *pRspUserLogin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户退出应答
	virtual void OnRspUserLogout(CQdpFtdcRspUserLogoutField *pRspUserLogout, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户密码修改应答
	virtual void OnRspUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///强制用户退出应答
	virtual void OnRspForceUserExit(CQdpFtdcForceUserExitField *pForceUserExit, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户会话删除应答
	virtual void OnRspForceUserLogout(CQdpFtdcForceUserExitField *pForceUserExit, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单录入应答
	virtual void OnRspOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单操作应答
	virtual void OnRspOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者资金帐户出入金应答
	virtual void OnRspAccountDeposit(CQdpFtdcRspAccountDepositField *pRspAccountDeposit, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///数据流回退通知
	virtual void OnRtnFlowMessageCancel(CQdpFtdcFlowMessageCancelField *pFlowMessageCancel) {};

	///成交回报
	virtual void OnRtnTrade(CQdpFtdcTradeField *pTrade) {};

	///报单回报
	virtual void OnRtnOrder(CQdpFtdcOrderField *pOrder) {};

	///报单录入错误回报
	virtual void OnErrRtnOrderInsert(CQdpFtdcInputOrderField *pInputOrder, CQdpFtdcRspInfoField *pRspInfo) {};

	///报单操作错误回报
	virtual void OnErrRtnOrderAction(CQdpFtdcOrderActionField *pOrderAction, CQdpFtdcRspInfoField *pRspInfo) {};

	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(CQdpFtdcInstrumentStatusField *pInstrumentStatus) {};

	///账户出入金回报
	virtual void OnRtnInvestorAccountDeposit(CQdpFtdcInvestorAccountDepositResField *pInvestorAccountDepositRes) {};

	///QDP警告消息通知
	virtual void OnRtnMessageNotify(CQdpFtdcMessageNotifyInfoField *pMessageNotifyInfo) {};

	///金交所递延费率通知
	virtual void OnRtnSGEDeferRate(CQdpFtdcSGEDeferRateField *pSGEDeferRate) {};

	///郑州合约状态
	virtual void OnRtnQmdInstrumentStatu(CQdpFtdcQmdInstrumentStateField *pQmdInstrumentState) {};

	///报单查询应答
	virtual void OnRspQryOrder(CQdpFtdcOrderField *pOrder, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///成交单查询应答
	virtual void OnRspQryTrade(CQdpFtdcTradeField *pTrade, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///可用投资者账户查询应答
	virtual void OnRspQryUserInvestor(CQdpFtdcRspUserInvestorField *pRspUserInvestor, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///交易编码查询应答
	virtual void OnRspQryTradingCode(CQdpFtdcRspTradingCodeField *pRspTradingCode, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者资金账户查询应答
	virtual void OnRspQryInvestorAccount(CQdpFtdcRspInvestorAccountField *pRspInvestorAccount, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///合约查询应答
	virtual void OnRspQryInstrument(CQdpFtdcRspInstrumentField *pRspInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///交易所查询应答
	virtual void OnRspQryExchange(CQdpFtdcRspExchangeField *pRspExchange, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者持仓查询应答
	virtual void OnRspQryInvestorPosition(CQdpFtdcRspInvestorPositionField *pRspInvestorPosition, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅主题应答
	virtual void OnRspSubscribeTopic(CQdpFtdcDisseminationField *pDissemination, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///主题查询应答
	virtual void OnRspQryTopic(CQdpFtdcDisseminationField *pDissemination, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户查询应答
	virtual void OnRspQryUser(CQdpFtdcUserField *pUser, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者手续费率查询应答
	virtual void OnRspQryInvestorFee(CQdpFtdcInvestorFeeField *pInvestorFee, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者保证金率查询应答
	virtual void OnRspQryInvestorMargin(CQdpFtdcInvestorMarginField *pInvestorMargin, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///金交所递延费率查询应答
	virtual void OnRspQrySGEDeferRate(CQdpFtdcSGEDeferRateField *pSGEDeferRate, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///持仓明细查询应答
	virtual void OnRspQryInvestorPositionDetail(CQdpFtdcRspInvestorPositionDetailField *pRspInvestorPositionDetail, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者期权手续费率查询应答
	virtual void OnRspQryInvestorOptionFee(CQdpFtdcRspInvestorOptionFeeField *pRspInvestorOptionFee, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///深度行情通知
	virtual void OnRtnDepthMarketData(CQdpFtdcDepthMarketDataField *pDepthMarketData) {};

	///深度行情通知
	virtual void OnRtnMultiDepthMarketData(CQdpFtdcDepthMarketDataField *pDepthMarketData) {};

	///订阅合约的相关信息
	virtual void OnRspSubMarketData(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///退订合约的相关信息
	virtual void OnRspUnSubMarketData(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///实时行情查询应答
	virtual void OnRspQryMarketData(CQdpFtdcMarketDataField *pMarketData, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///行情查询应答
	virtual void OnRspQryDepthMarketData(CQdpFtdcRspMarketDataField *pRspMarketData, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///分价表查询应答
	virtual void OnRspQryMBLMarketData(CQdpFtdcMBLMarketDataField *pMBLMarketData, CQdpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
};

class USER_API_EXPORT CQdpFtdcUserApi
{
public:
	///创建UserApi
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
	///@param pszUserApiType UserAPI类型
	///@return 创建出的UserApi
	static CQdpFtdcUserApi *CreateFtdcUserApi(const char *pszFlowPath = "",
											const char *pszUserApiType = "");
	
	///获取系统版本号
	///@param nMajorVersion 主版本号
	///@param nMinorVersion 子版本号
	///@return 系统标识字符串
	static const char *GetVersion(int &nMajorVersion, int &nMinorVersion);
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;

	//多播设置开关
	virtual void SetMultiCast(bool bMultiCast=false) = 0;
	virtual void RegMultiTopicID(int TopicID)=0;
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init(int nPrivatePort) = 0;
	
	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join() = 0;
	
	///获取当前交易日
	///@retrun 获取到的交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	virtual const char *GetTradingDay() = 0;
	
	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///注册名字服务器网络地址
	///@param pszNsAddress：名字服务器网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
	///@remark RegisterFront优先于RegisterNameServer
	virtual void RegisterNameServer(char *pszNsAddress) = 0;
	
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CQdpFtdcUserSpi *pSpi) = 0;
	
	///订阅市场行情。
	///@param nTopicID 市场行情主题  
	///@param nResumeType 市场行情重传方式  
	///        QDP_TERT_RESTART:从本交易日开始重传
	///        QDP_TERT_RESUME:从上次收到的续传
	///        QDP_TERT_QUICK:先传送当前行情快照,再传送登录后市场行情的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
	virtual void SubscribeMarketDataTopic(int nTopicID, QDP_TE_RESUME_TYPE nResumeType) = 0;

	///订阅私有流。
	///@param nResumeType 私有流重传方式  
	///        QDP_TERT_RESTART:从本交易日开始重传
	///        QDP_TERT_RESUME:从上次收到的续传
	///        QDP_TERT_QUICK:只传送登录后私有流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
	virtual void SubscribePrivateTopic(QDP_TE_RESUME_TYPE nResumeType) = 0;
	
	///订阅公共流。
	///@param nResumeType 公共流重传方式  
	///        QDP_TERT_RESTART:从本交易日开始重传
	///        QDP_TERT_RESUME:从上次收到的续传
	///        QDP_TERT_QUICK:只传送登录后公共流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
	virtual void SubscribePublicTopic(QDP_TE_RESUME_TYPE nResumeType) = 0;
	
	///订阅交易员流。
	///@param nResumeType 交易员流重传方式  
	///        QDP_TERT_RESTART:从本交易日开始重传
	///        QDP_TERT_RESUME:从上次收到的续传
	///        QDP_TERT_QUICK:只传送登录后交易员流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到交易员流的数据。
	virtual void SubscribeUserTopic(QDP_TE_RESUME_TYPE nResumeType) = 0;
	
	///订阅合约行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int SubMarketData(char *ppInstrumentID[], int nCount)=0;

	///退订合约行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubMarketData(char *ppInstrumentID[], int nCount)=0;	
	
	///设置心跳超时时间。
	///@param timeout 心跳超时时间(秒)  
	virtual void SetHeartbeatTimeout(unsigned int timeout) = 0;
	
	///打开请求日志文件
	///@param pszReqLogFileName 请求日志文件名  
	///@return 0 操作成功
	///@return -1 打开日志文件失败
	virtual int OpenRequestLog(const char *pszReqLogFileName) = 0;

	///打开应答日志文件
	///@param pszRspLogFileName 应答日志文件名  
	///@return 0 操作成功
	///@return -1 打开日志文件失败
	virtual int OpenResponseLog(const char *pszRspLogFileName) = 0;
	
	///用户登录请求
	virtual int ReqUserLogin(CQdpFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;

	///用户退出请求
	virtual int ReqUserLogout(CQdpFtdcReqUserLogoutField *pReqUserLogout, int nRequestID) = 0;

	///用户密码修改请求
	virtual int ReqUserPasswordUpdate(CQdpFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) = 0;

	///强制用户退出请求
	virtual int ReqForceUserExit(CQdpFtdcForceUserExitField *pForceUserExit, int nRequestID) = 0;

	///用户会话删除请求
	virtual int ReqForceUserLogout(CQdpFtdcForceUserExitField *pForceUserExit, int nRequestID) = 0;

	///请求导出内存数据库
	virtual int ReqDumpMemDb(CQdpFtdcMemDbField *pMemDb, int nRequestID) = 0;

	///报单录入请求
	virtual int ReqOrderInsert(CQdpFtdcInputOrderField *pInputOrder, int nRequestID) = 0;

	///报单操作请求
	virtual int ReqOrderAction(CQdpFtdcOrderActionField *pOrderAction, int nRequestID) = 0;

	///投资者资金帐户出入金请求
	virtual int ReqAccountDeposit(CQdpFtdcReqAccountDepositField *pReqAccountDeposit, int nRequestID) = 0;

	///报单查询请求
	virtual int ReqQryOrder(CQdpFtdcQryOrderField *pQryOrder, int nRequestID) = 0;

	///成交单查询请求
	virtual int ReqQryTrade(CQdpFtdcQryTradeField *pQryTrade, int nRequestID) = 0;

	///可用投资者账户查询请求
	virtual int ReqQryUserInvestor(CQdpFtdcQryUserInvestorField *pQryUserInvestor, int nRequestID) = 0;

	///交易编码查询请求
	virtual int ReqQryTradingCode(CQdpFtdcQryTradingCodeField *pQryTradingCode, int nRequestID) = 0;

	///投资者资金账户查询请求
	virtual int ReqQryInvestorAccount(CQdpFtdcQryInvestorAccountField *pQryInvestorAccount, int nRequestID) = 0;

	///合约查询请求
	virtual int ReqQryInstrument(CQdpFtdcQryInstrumentField *pQryInstrument, int nRequestID) = 0;

	///交易所查询请求
	virtual int ReqQryExchange(CQdpFtdcQryExchangeField *pQryExchange, int nRequestID) = 0;

	///投资者持仓查询请求
	virtual int ReqQryInvestorPosition(CQdpFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID) = 0;

	///订阅主题请求
	virtual int ReqSubscribeTopic(CQdpFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///主题查询请求
	virtual int ReqQryTopic(CQdpFtdcDisseminationField *pDissemination, int nRequestID) = 0;

	///用户查询请求
	virtual int ReqQryUser(CQdpFtdcQryUserField *pQryUser, int nRequestID) = 0;

	///投资者手续费率查询请求
	virtual int ReqQryInvestorFee(CQdpFtdcQryInvestorFeeField *pQryInvestorFee, int nRequestID) = 0;

	///投资者保证金率查询请求
	virtual int ReqQryInvestorMargin(CQdpFtdcQryInvestorMarginField *pQryInvestorMargin, int nRequestID) = 0;

	///金交所递延费率查询请求
	virtual int ReqQrySGEDeferRate(CQdpFtdcQrySGEDeferRateField *pQrySGEDeferRate, int nRequestID) = 0;

	///持仓明细查询请求
	virtual int ReqQryInvestorPositionDetail(CQdpFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID) = 0;

	///投资者期权手续费率查询请求
	virtual int ReqQryInvestorOptionFee(CQdpFtdcQryInvestorOptionFeeField *pQryInvestorOptionFee, int nRequestID) = 0;

	///Topic查询
	virtual int ReqTopicSearch(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, int nRequestID) = 0;

	///订阅合约的相关信息
	virtual int ReqSubMarketData(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, int nRequestID) = 0;

	///退订合约的相关信息
	virtual int ReqUnSubMarketData(CQdpFtdcSpecificInstrumentField *pSpecificInstrument, int nRequestID) = 0;

	///实时行情查询请求
	virtual int ReqQryMarketData(CQdpFtdcQryMarketDataField *pQryMarketData, int nRequestID) = 0;

	///行情查询请求
	virtual int ReqQryDepthMarketData(CQdpFtdcQryMarketDataField *pQryMarketData, int nRequestID) = 0;

	///分价表查询请求
	virtual int ReqQryMBLMarketData(CQdpFtdcQryMBLMarketDataField *pQryMBLMarketData, int nRequestID) = 0;
protected:
	~CQdpFtdcUserApi(){};
};

#endif
