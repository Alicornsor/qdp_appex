#ifndef CTRADERAPI_H
#define CTRADERAPI_H

#include "APIStruct.h"
#include "Api.h"

#ifndef NO_LIB
#ifdef WIN32
#ifdef MEMAPI_EXPORTS
#define API_EXPORT __declspec(dllexport)
#else
#define API_EXPORT __declspec(dllimport)
#endif
#else
#define API_EXPORT 
#endif
#else
#define API_EXPORT 
#endif

class API_EXPORT CTraderApi:public CApi
{
public:
	CTraderApi(void) {}
	~CTraderApi(void ) {}
	
	/**初始化
	* @return 0表示成功，-1表示失败
	*/
	int init(void);
	
	/**设置前置机的IP和端口
	* @param sIp 前置机的IP
	* @param nPort 前置机的端口
	*/
	void SetService(char *sIp, int nPort);
	
	/**获取当前的交易日期
	* @param tradeDate 输出参数，返回当前的交易日期
	*/
	void GetTradeDate(TDate &tradeDate);
	
	/**返回与前置连接断开时的错误信息
	* @param ErrMsg 输出参数，返回错误信息
	*/
	virtual void  onChannelLost(char *ErrMsg) {}
	
	/**返回应用的错误信息
	* @param ExceptionMsg 输出参数，返回例外错误信息
	*/
	virtual void  onException(char *ExceptionMsg) {}
	
	/**返回系统错误通知信息
	* @param pRspMsg 输出参数，返回例外错误信息
	*/
	virtual void onRecvSysErrorNtf(TTRspMsg *pRspMsg) {}
	
	/**设置IC卡的口令和读取方式
	* @param passwd IC卡的口令
	* @param inputType 读取方式 0从文件读取，1从IC卡读取
	* @param comID 串口号
	*/
	void SetIcCardPwd(const char *passwd,short inputType,short comID);
	
	/**改变读取口令
	* @param userID 交易员ID
	* @param oldpassword 旧的口令
	* @param newpassword 新口令
	* @param inputType 0从文件读取，1从IC卡读取
	*/
	int  ChgICPasswd(TTraderID &traderID,const char *oldpassword, const char *newpassword,short inputType);
	
	
	/**交易员登录请求
	* @param pReqTraderLogin 输入参数，交易员登录请求信息
	* @param RootID  输入参数，请求包的唯一标示
	* @return 0 : 成功 
	*         -1:连接前置失败
	*         -2:重复登录
	*         -3:加密认证操作失败
	*/
	int ReqTraderLogin(TReqTraderLogin *pReqTraderLogin,char *RootID=NULL);
   	/**交易员登录应答
   	* @param pReqTraderLogin 输出参数，交易员登录请求信息
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspTraderLogin(TReqTraderLogin *pReqTraderLogin,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**交易员退出请求
   	* @param pReqTraderLogout 输入参数，交易员退出请求信息
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqTraderLogout( TReqTraderLogout *pReqTraderLogout,char *RootID=NULL);
   	/**交易员退出应答
   	* @param pReqTraderLogout 输出参数，交易员退出请求信息
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspTraderLogout(TReqTraderLogout *pReqTraderLogout,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货报单请求
   	* @param pSpotOrder 输入参数，现货报单信息
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqSpotOrder( TSpotOrder *pSpotOrder,char *RootID=NULL);
   	/**现货报单请求(V2)
   	* @param pSpotOrder 输入参数，现货报单信息
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqSpotOrderEx( TSpotOrderEx *pSpotOrder,char *RootID=NULL);
   	/**现货报单应答
   	* @param pSpotOrder 输出参数，现货报单信息
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspSpotOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货撤单请求
   	* @param pSpotOrderCancel 输入参数，现货撤单请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqSpotOrderCancel( TSpotOrderCancel *pSpotOrderCancel,char *RootID=NULL);
   	/**现货撤单应答
   	* @param pSpotOrderCancel 输出参数，现货撤单请求
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspSpotOrderCancel(TSpotOrderCancel *pSpotOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货延期交收报单请求
   	* @param pDeferOrder 输入参数，现货延期交收报单
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqDeferOrder( TDeferOrder *pDeferOrder,char *RootID=NULL);
   	/**现货延期交收报单请求(V2)
   	* @param pDeferOrder 输入参数，现货延期交收报单
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqDeferOrderEx( TDeferOrderEx *pDeferOrder,char *RootID=NULL);
   	/**现货延期交收报单应答
   	* @param pDeferOrder 输出参数，现货延期交收报单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspDeferOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货延期交收撤单请求
   	* @param pDeferOrderCancel 输入参数，现货延期交收撤单请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqDeferOrderCancel( TDeferOrderCancel *pDeferOrderCancel,char *RootID=NULL);
   	/**现货延期交收撤单应答
   	* @param pDeferOrderCancel 输出参数，现货延期交收撤单请求
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspDeferOrderCancel(TDeferOrderCancel *pDeferOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**现货报单回报
   	* @param pSpotOrder 输出参数，现货报单信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnSpotOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货延期交收报单回报
   	* @param pDeferOrder 输出参数，现货延期交收报单
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnDeferOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货撤单回报
   	* @param pSpotOrder 输出参数，现货报单信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnSpotOrderCancel(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货延期交收撤单回报
   	* @param pDeferOrder 输出参数，现货延期交收报单
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnDeferOrderCancel(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**现货延期交收交割申报请求
   	* @param pDeferDeliveryAppOrder 输入参数，现货延期交收交割申报报单
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqDeferDeliveryAppOrder( TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,char *RootID=NULL);
   	/**现货延期交收交割申报应答
   	* @param pDeferDeliveryAppOrder 输出参数，现货延期交收交割申报报单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspDeferDeliveryAppOrder(TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货延期交收交割申报撤消请求
   	* @param pDeferDeliveryAppOrderCancel 输入参数，现货延期交收交割申报撤单请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqDeferDeliveryAppOrderCancel( TDeferDeliveryAppOrderCancel *pDeferDeliveryAppOrderCancel,char *RootID=NULL);
   	/**现货延期交收交割申报撤消应答
   	* @param pDeferDeliveryAppOrderCancel 输出参数，现货延期交收交割申报撤单请求
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspDeferDeliveryAppOrderCancel(TDeferDeliveryAppOrderCancel *pDeferDeliveryAppOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货延期交收中立仓申报请求
   	* @param pMiddleAppOrder 输入参数，现货延期交收中立仓申报报单
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqMiddleAppOrder( TMiddleAppOrder *pMiddleAppOrder,char *RootID=NULL);
   	/**现货延期交收中立仓申报应答
   	* @param pMiddleAppOrder 输出参数，现货延期交收中立仓申报报单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspMiddleAppOrder(TMiddleAppOrder *pMiddleAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货延期交收中立仓申报撤单请求
   	* @param pMiddleAppOrderCancel 输入参数，现货延期交收中立仓申报撤单请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqMiddleAppOrderCancel( TMiddleAppOrderCancel *pMiddleAppOrderCancel,char *RootID=NULL);
   	/**现货延期交收中立仓申报撤单应答
   	* @param pMiddleAppOrderCancel 输出参数，现货延期交收中立仓申报撤单请求
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspMiddleAppOrderCancel(TMiddleAppOrderCancel *pMiddleAppOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**现货延期交收交割申报回报
   	* @param pDeferDeliveryAppOrder 输出参数，现货延期交收交割申报报单
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnDeferDeliveryAppOrder(TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货延期交收中立仓申报回报
   	* @param pMiddleAppOrder 输出参数，现货延期交收中立仓申报报单
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnMiddleAppOrder(TMiddleAppOrder *pMiddleAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货延期交收交割申报撤消回报
   	* @param pDeferDeliveryAppOrder 输出参数，现货延期交收交割申报报单
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnDeferDeliveryAppOrderCancel(TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货延期交收中立仓申报撤单回报
   	* @param pMiddleAppOrder 输出参数，现货延期交收中立仓申报报单
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnMiddleAppOrderCancel(TMiddleAppOrder *pMiddleAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**期货报单请求
   	* @param pFuturesOrder 输入参数，期货报单
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqFuturesOrder( TFuturesOrder *pFuturesOrder,char *RootID=NULL);
   	/**期货报单应答
   	* @param pFuturesOrder 输出参数，期货报单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspFuturesOrder(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**期货撤单请求
   	* @param pFuturesOrderCancel 输入参数，期货撤单请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqFuturesOrderCancel( TFuturesOrderCancel *pFuturesOrderCancel,char *RootID=NULL);
   	/**期货撤单应答
   	* @param pFuturesOrderCancel 输出参数，期货撤单请求
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspFuturesOrderCancel(TFuturesOrderCancel *pFuturesOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货T+N报单请求
   	* @param pForwardOrder 输入参数，现货T+N报单
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqForwardOrder( TForwardOrder *pForwardOrder,char *RootID=NULL);
   	/**现货T+N报单请求(V2)
   	* @param pForwardOrder 输入参数，现货T+N报单
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqForwardOrderEx( TForwardOrderEx *pForwardOrder,char *RootID=NULL);
   	/**现货T+N报单应答
   	* @param pForwardOrder 输出参数，现货T+N报单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspForwardOrder(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货T+N撤单请求
   	* @param pForwardOrderCancel 输入参数，现货T+N撤单请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqForwardOrderCancel( TForwardOrderCancel *pForwardOrderCancel,char *RootID=NULL);
   	/**现货T+N撤单应答
   	* @param pForwardOrderCancel 输出参数，现货T+N撤单请求
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspForwardOrderCancel(TForwardOrderCancel *pForwardOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货T+N到期转让报单请求
   	* @param pSpotOrder 输入参数，现货报单信息
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqForwardEndorseOrder( TSpotOrder *pSpotOrder,char *RootID=NULL);
   	/**现货T+N到期转让报单应答
   	* @param pSpotOrder 输出参数，现货报单信息
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspForwardEndorseOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货T+N到期转让撤单请求
   	* @param pForwardEndorseOrderCancel 输入参数，现货T+N到期转让撤单请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqForwardEndorseOrderCancel( TForwardEndorseOrderCancel *pForwardEndorseOrderCancel,char *RootID=NULL);
   	/**现货T+N到期转让撤单应答
   	* @param pForwardEndorseOrderCancel 输出参数，现货T+N到期转让撤单请求
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspForwardEndorseOrderCancel(TForwardEndorseOrderCancel *pForwardEndorseOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**期货报单回报
   	* @param pFuturesOrder 输出参数，期货报单
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnFuturesOrder(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货T+N报单回报
   	* @param pForwardOrder 输出参数，现货T+N报单
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnForwardOrder(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**期货撤单回报
   	* @param pFuturesOrder 输出参数，期货报单
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnFuturesOrderCancel(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货T+N撤单回报
   	* @param pForwardOrder 输出参数，现货T+N报单
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnForwardOrderCancel(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货T+N到期转让报单回报
   	* @param pSpotOrder 输出参数，现货报单信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnForwardEndorseOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货T+N到期转让撤单回报
   	* @param pSpotOrder 输出参数，现货报单信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnForwardEndorseOrderCancel(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**交易员密码修改请求
   	* @param pReqTraderPasswordUpdate 输入参数，交易员密码修改请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqTraderPasswordUpdate( TReqTraderPasswordUpdate *pReqTraderPasswordUpdate,char *RootID=NULL);
   	/**交易员密码修改应答
   	* @param pReqTraderPasswordUpdate 输出参数，交易员密码修改请求
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspTraderPasswordUpdate(TReqTraderPasswordUpdate *pReqTraderPasswordUpdate,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**会员应急密码修改请求
   	* @param pReqMemberUrgentPasswordUpdate 输入参数，会员应急密码修改请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqMemberUrgentPasswordUpdate( TReqMemberUrgentPasswordUpdate *pReqMemberUrgentPasswordUpdate,char *RootID=NULL);
   	/**会员应急密码修改应答
   	* @param pReqMemberUrgentPasswordUpdate 输出参数，会员应急密码修改请求
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspMemberUrgentPasswordUpdate(TReqMemberUrgentPasswordUpdate *pReqMemberUrgentPasswordUpdate,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**会员资金查询请求
   	* @param pReqQryMemberCapital 输入参数，会员资金查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
	int ReqQryMemberCapital( TReqQryMemberCapital *pReqQryMemberCapital,char *RootID=NULL);

   	/**会员资金查询应答
   	* @param pMemberCapital 输出参数，会员资金
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
	virtual void onRecvRspQryMemberCapital(TMemberCapital *pMemberCapital,TTRspMsg *pRspMsg,char *RootID=NULL) {}

	// Added by qingquan.xue 20140310 begin
	/**会员资金查询请求（充抵）
   	* @param pReqQryMemberCapital 输入参数，会员资金查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
	int ReqQryMemberCapitalEx( TReqQryMemberCapital *pReqQryMemberCapital,char *RootID=NULL);

	/**会员资金查询应答（充抵）
   	* @param pMemberCapital 输出参数，会员资金
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
	virtual void onRecvRspQryMemberCapitalEx(TMemberCapitalEx *pMemberCapital,TTRspMsg *pRspMsg,char *RootID=NULL) {}
	// Added by qingquan.xue 20140310 end

   	/**客户库存查询请求
   	* @param pReqQryClientStorage 输入参数，客户库存查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
	int ReqQryClientStorage( TReqQryClientStorage *pReqQryClientStorage,char *RootID=NULL);
	
   	/**客户库存查询应答
   	* @param pClientStorage 输出参数，客户库存
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryClientStorage(TClientStorage *pClientStorage,TTRspMsg *pRspMsg,char *RootID=NULL) {}

	// Added by qingquan.xue 20140310 begin
	/**客户库存查询请求（充抵）
   	* @param pReqQryClientStorage 输入参数，客户库存查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
	int ReqQryClientStorageEx( TReqQryClientStorage *pReqQryClientStorage,char *RootID=NULL);

	/**客户库存查询应答（充抵）
   	* @param pClientStorage 输出参数，客户库存
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
	virtual void onRecvRspQryClientStorageEx(TClientStorageEx *pClientStorage,TTRspMsg *pRspMsg,char *RootID=NULL) {}
	// Added by qingquan.xue 20140310 end

   	/**现货报单查询请求
   	* @param pReqQryOrder 输入参数，报单查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQrySpotOrder( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**现货报单查询应答
   	* @param pSpotOrder 输出参数，现货报单信息
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQrySpotOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
    /**现货报单查询请求(V2)
   	* @param pReqQryOrder 输入参数，报单查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQrySpotOrderEx( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**现货报单查询应答(V2)
   	* @param pSpotOrder 输出参数，现货报单信息
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQrySpotOrderEx(TSpotOrderEx *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**现货延期交收报单查询请求
   	* @param pReqQryOrder 输入参数，报单查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryDeferOrder( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**现货延期交收报单查询应答
   	* @param pDeferOrder 输出参数，现货延期交收报单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryDeferOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**现货延期交收报单查询请求(V2)
   	* @param pReqQryOrder 输入参数，报单查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryDeferOrderEx( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**现货延期交收报单查询应答(V2)
   	* @param pDeferOrder 输出参数，现货延期交收报单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryDeferOrderEx(TDeferOrderEx *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货延期交收交割申报报单查询请求
   	* @param pReqQryOrder 输入参数，报单查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryDeferDeliveryAppOrder( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**现货延期交收交割申报报单查询应答
   	* @param pDeferDeliveryAppOrder 输出参数，现货延期交收交割申报报单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryDeferDeliveryAppOrder(TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货延期交收中立仓申报报单查询请求
   	* @param pReqQryOrder 输入参数，报单查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryMiddleAppOrder( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**现货延期交收中立仓申报报单查询应答
   	* @param pMiddleAppOrder 输出参数，现货延期交收中立仓申报报单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryMiddleAppOrder(TMiddleAppOrder *pMiddleAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**期货报单查询请求
   	* @param pReqQryOrder 输入参数，报单查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryFuturesOrder( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**期货报单查询应答
   	* @param pFuturesOrder 输出参数，期货报单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryFuturesOrder(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货T+N报单查询请求
   	* @param pReqQryOrder 输入参数，报单查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryForwardOrder( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**现货T+N报单查询应答
   	* @param pForwardOrder 输出参数，现货T+N报单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryForwardOrder(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货T+N报单查询请求(V2)
   	* @param pReqQryOrder 输入参数，报单查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryForwardOrderEx( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**现货T+N报单查询应答(V2)
   	* @param pForwardOrder 输出参数，现货T+N报单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryForwardOrderEx(TForwardOrderEx *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货T+N到期转让报单查询请求
   	* @param pReqQryOrder 输入参数，报单查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryForwardEndorseOrder( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**现货T+N到期转让报单查询应答
   	* @param pSpotOrder 输出参数，现货报单信息
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryForwardEndorseOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货成交单查询请求
   	* @param pReqQryMatch 输入参数，成交查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQrySpotMatch( TReqQryMatch *pReqQryMatch,char *RootID=NULL);
   	/**现货成交单查询应答
   	* @param pSpotMatch 输出参数，现货成交单信息
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQrySpotMatch(TSpotMatch *pSpotMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货延期交收成交单查询请求
   	* @param pReqQryMatch 输入参数，成交查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryDeferMatch( TReqQryMatch *pReqQryMatch,char *RootID=NULL);
   	/**现货延期交收成交单查询应答
   	* @param pDeferMatch 输出参数，现货延期交收成交单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryDeferMatch(TDeferMatch *pDeferMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货延期交收交割申报成交单查询请求
   	* @param pReqQryMatch 输入参数，成交查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryDeferDeliveryAppMatch( TReqQryMatch *pReqQryMatch,char *RootID=NULL);
   	/**现货延期交收交割申报成交单查询应答
   	* @param pDeferDeliveryAppMatch 输出参数，递延交割申报成交单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryDeferDeliveryAppMatch(TDeferDeliveryAppMatch *pDeferDeliveryAppMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**期货成交单查询请求
   	* @param pReqQryMatch 输入参数，成交查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryFuturesMatch( TReqQryMatch *pReqQryMatch,char *RootID=NULL);
   	/**期货成交单查询应答
   	* @param pFuturesMatch 输出参数，期货成交单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryFuturesMatch(TFuturesMatch *pFuturesMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货T+N成交单查询请求
   	* @param pReqQryMatch 输入参数，成交查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryForwardMatch( TReqQryMatch *pReqQryMatch,char *RootID=NULL);
   	/**现货T+N成交单查询应答
   	* @param pForwardMatch 输出参数，现货T+N成交单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryForwardMatch(TForwardMatch *pForwardMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货T+N到期转让成交单查询请求
   	* @param pReqQryMatch 输入参数，成交查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryForwardEndorseMatch( TReqQryMatch *pReqQryMatch,char *RootID=NULL);
   	/**现货T+N到期转让成交单查询应答
   	* @param pSpotMatch 输出参数，现货成交单信息
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryForwardEndorseMatch(TSpotMatch *pSpotMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**现货成交回报
   	* @param pSpotMatch 输出参数，现货成交单信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnSpotMatch(TSpotMatch *pSpotMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货延期交收成交回报
   	* @param pDeferMatch 输出参数，现货延期交收成交单
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnDeferMatch(TDeferMatch *pDeferMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货延期交收交割申报成交回报
   	* @param pDeferDeliveryAppMatch 输出参数，递延交割申报成交单
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnDeferDeliveryAppMatch(TDeferDeliveryAppMatch *pDeferDeliveryAppMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**期货成交回报
   	* @param pFuturesMatch 输出参数，期货成交单
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnFuturesMatch(TFuturesMatch *pFuturesMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货T+N成交回报
   	* @param pForwardMatch 输出参数，现货T+N成交单
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnForwardMatch(TForwardMatch *pForwardMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货T+N到期转让成交回报
   	* @param pSpotMatch 输出参数，现货成交单信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnForwardEndorseMatch(TSpotMatch *pSpotMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**会员现货延期交收持仓查询请求
   	* @param pReqQryMemberPosi 输入参数，会员持仓查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryDeferMemberPosi( TReqQryMemberPosi *pReqQryMemberPosi,char *RootID=NULL);
   	/**会员现货延期交收持仓查询应答
   	* @param pDeferMemberPosi 输出参数，会员现货延期交收持仓
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryDeferMemberPosi(TDeferMemberPosi *pDeferMemberPosi,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**会员期货持仓查询请求
   	* @param pReqQryMemberPosi 输入参数，会员持仓查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryFuturesMemberPosi( TReqQryMemberPosi *pReqQryMemberPosi,char *RootID=NULL);
   	/**会员期货持仓查询应答
   	* @param pFuturesMemberPosi 输出参数，会员期货持仓
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryFuturesMemberPosi(TFuturesMemberPosi *pFuturesMemberPosi,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**会员现货T+N持仓查询请求
   	* @param pReqQryMemberPosi 输入参数，会员持仓查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryForwardMemberPosi( TReqQryMemberPosi *pReqQryMemberPosi,char *RootID=NULL);
   	/**会员现货T+N持仓查询应答
   	* @param pForwardMemberPosi 输出参数，会员现货T+N持仓
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryForwardMemberPosi(TForwardMemberPosi *pForwardMemberPosi,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**客户现货延期交收持仓查询请求
   	* @param pReqQryClientPosi 输入参数，客户持仓查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryDeferClientPosi( TReqQryClientPosi *pReqQryClientPosi,char *RootID=NULL);
   	/**客户现货延期交收持仓查询应答
   	* @param pDeferClientPosi 输出参数，客户现货延期交收持仓
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryDeferClientPosi(TDeferClientPosi *pDeferClientPosi,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**客户期货持仓查询请求
   	* @param pReqQryClientPosi 输入参数，客户持仓查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryFuturesClientPosi( TReqQryClientPosi *pReqQryClientPosi,char *RootID=NULL);
   	/**客户期货持仓查询应答
   	* @param pFuturesClientPosi 输出参数，客户期货持仓
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryFuturesClientPosi(TFuturesClientPosi *pFuturesClientPosi,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**客户现货T+N持仓查询请求
   	* @param pReqQryClientPosi 输入参数，客户持仓查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryForwardClientPosi( TReqQryClientPosi *pReqQryClientPosi,char *RootID=NULL);
   	/**客户现货T+N持仓查询应答
   	* @param pForwardClientPosi 输出参数，客户现货T+N持仓
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryForwardClientPosi(TForwardClientPosi *pForwardClientPosi,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货行情查询请求
   	* @param pReqQryQuotation 输入参数，行情查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQrySpotQuotation( TReqQryQuotation *pReqQryQuotation,char *RootID=NULL);
   	/**现货行情查询应答
   	* @param pSpotQuotation 输出参数，现货行情
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQrySpotQuotation(TSpotQuotation *pSpotQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货延期交收行情查询请求
   	* @param pReqQryQuotation 输入参数，行情查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryDeferQuotation( TReqQryQuotation *pReqQryQuotation,char *RootID=NULL);
   	/**现货延期交收行情查询应答
   	* @param pDeferQuotation 输出参数，现货延期交收行情
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryDeferQuotation(TDeferQuotation *pDeferQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**期货行情查询请求
   	* @param pReqQryQuotation 输入参数，行情查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryFuturesQuotation( TReqQryQuotation *pReqQryQuotation,char *RootID=NULL);
   	/**期货行情查询应答
   	* @param pFuturesQuotation 输出参数，期货行情
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryFuturesQuotation(TFuturesQuotation *pFuturesQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货T+N行情查询请求
   	* @param pReqQryQuotation 输入参数，行情查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryForwardQuotation( TReqQryQuotation *pReqQryQuotation,char *RootID=NULL);
   	/**现货T+N行情查询应答
   	* @param pForwardQuotation 输出参数，现货T+N行情
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryForwardQuotation(TForwardQuotation *pForwardQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**市场信息回报
   	* @param pMarket 输出参数，市场表
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvMarketInfo(TMarket *pMarket,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货合约信息回报
   	* @param pSpotInst 输出参数，现货合约
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvSpotInstInfo(TSpotInst *pSpotInst,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**递延合约信息回报
   	* @param pDeferInst 输出参数，现货延期交收合约
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvDeferInstInfo(TDeferInst *pDeferInst,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**期货合约信息回报
   	* @param pFuturesInst 输出参数，期货合约
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvFuturesInstInfo(TFuturesInst *pFuturesInst,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**远期合约信息回报
   	* @param pForwardInst 输出参数，现货T+N合约
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvForwardInstInfo(TForwardInst *pForwardInst,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**递延费率查询请求
   	* @param pReqQryDeferFeeRate 输入参数，递延费率查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryDeferFeeRate( TReqQryDeferFeeRate *pReqQryDeferFeeRate,char *RootID=NULL);
   	/**递延费率查询请求应答
   	* @param pDeferFeeRate 输出参数，现货延期交收补偿费率信息
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryDeferFeeRate(TDeferFeeRate *pDeferFeeRate,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**现货合约交易状态改变回报
   	* @param pInstState 输出参数，合约交易状态信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnSpotInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货市场交易状态改变回报
   	* @param pMarketState 输出参数，市场交易状态信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnSpotMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**递延合约交易状态改变回报
   	* @param pInstState 输出参数，合约交易状态信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnDeferInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**递延市场交易状态改变回报
   	* @param pMarketState 输出参数，市场交易状态信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnDeferMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**期货合约交易状态改变回报
   	* @param pInstState 输出参数，合约交易状态信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnFuturesInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**期货市场交易状态改变回报
   	* @param pMarketState 输出参数，市场交易状态信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnFuturesMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**远期合约交易状态改变回报
   	* @param pInstState 输出参数，合约交易状态信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnForwardInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**远期市场交易状态改变回报
   	* @param pMarketState 输出参数，市场交易状态信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnForwardMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**交易所公告查询请求
   	* @param pReqQryBulletinBoard 输入参数，交易所公告信息查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryBulletinBoard( TReqQryBulletinBoard *pReqQryBulletinBoard,char *RootID=NULL);
   	/**交易所公告查询请求应答
   	* @param pBulletinBoard 输出参数，交易所公告信息
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryBulletinBoard(TBulletinBoard *pBulletinBoard,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**公告回报
   	* @param pBulletinBoard 输出参数，交易所公告信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnBulletinBoard(TBulletinBoard *pBulletinBoard,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**国际行情回报
   	* @param pInterQuotation 输出参数，国际行情信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvRtnInterQuotation(TInterQuotation *pInterQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**国际行情查询请求
   	* @param pInterQuotation 输入参数，国际行情信息
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryInterQuotation( TInterQuotation *pInterQuotation,char *RootID=NULL);
   	/**国际行情查询请求应答
   	* @param pInterQuotation 输出参数，国际行情信息
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryInterQuotation(TInterQuotation *pInterQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**现货行情
   	* @param pSpotQuotation 输出参数，现货行情
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvSpotQuotation(TSpotQuotation *pSpotQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货延期交收行情
   	* @param pDeferQuotation 输出参数，现货延期交收行情
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvDeferQuotation(TDeferQuotation *pDeferQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**期货行情
   	* @param pFuturesQuotation 输出参数，期货行情
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvFuturesQuotation(TFuturesQuotation *pFuturesQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**现货T+N行情
   	* @param pForwardQuotation 输出参数，现货T+N行情
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvForwardQuotation(TForwardQuotation *pForwardQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**当天现货分钟行情
   	* @param pMinsSpotQuotation 输出参数，当天现货分钟行情
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvMinsSpotQuotation(TMinsSpotQuotation *pMinsSpotQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**当天期货分钟行情
   	* @param pMinsFuturesQuotation 输出参数，期货分钟行情
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvMinsFuturesQuotation(TMinsFuturesQuotation *pMinsFuturesQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**当天远期分钟行情
   	* @param pMinsForwardQuotation 输出参数，远期分钟行情
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvMinsForwardQuotation(TMinsForwardQuotation *pMinsForwardQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**当天递延分钟行情
   	* @param pMinsDeferQuotation 输出参数，递延分钟行情
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvMinsDeferQuotation(TMinsDeferQuotation *pMinsDeferQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**现货分钟行情查询请求
   	* @param pReqQryMinsQuotation 输入参数，行情分钟查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQrySpotMinsQuotation( TReqQryMinsQuotation *pReqQryMinsQuotation,char *RootID=NULL);
   	/**现货分钟行情查询应答
   	* @param pMinsSpotQuotation 输出参数，当天现货分钟行情
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQrySpotMinsQuotation(TMinsSpotQuotation *pMinsSpotQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货延期交收分钟行情查询请求
   	* @param pReqQryMinsQuotation 输入参数，行情分钟查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryDeferMinsQuotation( TReqQryMinsQuotation *pReqQryMinsQuotation,char *RootID=NULL);
   	/**现货延期交收分钟行情查询应答
   	* @param pMinsDeferQuotation 输出参数，递延分钟行情
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryDeferMinsQuotation(TMinsDeferQuotation *pMinsDeferQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**期货分钟行情查询请求
   	* @param pReqQryMinsQuotation 输入参数，行情分钟查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryFuturesMinsQuotation( TReqQryMinsQuotation *pReqQryMinsQuotation,char *RootID=NULL);
   	/**期货分钟行情查询应答
   	* @param pMinsFuturesQuotation 输出参数，期货分钟行情
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryFuturesMinsQuotation(TMinsFuturesQuotation *pMinsFuturesQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货T+N分钟行情查询请求
   	* @param pReqQryMinsQuotation 输入参数，行情分钟查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryForwardMinsQuotation( TReqQryMinsQuotation *pReqQryMinsQuotation,char *RootID=NULL);
   	/**现货T+N分钟行情查询应答
   	* @param pMinsForwardQuotation 输出参数，远期分钟行情
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryForwardMinsQuotation(TMinsForwardQuotation *pMinsForwardQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**发布现货延期交收补偿费率通知
   	* @param pDeferFeeRate 输出参数，现货延期交收补偿费率信息
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvDeferFeeRateUpdate(TDeferFeeRate *pDeferFeeRate,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**会员客户查询请求
   	* @param pReqQryClient 输入参数，会员客户查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryClient( TReqQryClient *pReqQryClient,char *RootID=NULL);
   	/**会员客户查询响应
   	* @param pClient 输出参数，客户信息
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryClient(TClient *pClient,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**递延交收行情
   	* @param pDeferDeliveryQuotation 输出参数，递延交收行情
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvDeferDeliveryQuotation(TDeferDeliveryQuotation *pDeferDeliveryQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**交割品种代码信息
   	* @param pVariety 输出参数，交割品种代码
   	* @param pRspMsg 输出参数，连续包标志
   	* @param RootID  保留，未使用
  	*/
  	virtual void  onRecvVarietyInfo(TVariety *pVariety,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
	/**现货本地报单号查询请求
   	* @param pReqQryOrder 输入参数，报单查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQrySpotLocalOrder( TReqQryLocalOrder *pReqQryLocalOrder,char *RootID=NULL);
   	/**现货本地报单号查询应答
   	* @param pSpotOrder 输出参数，现货报单信息
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQrySpotLocalOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**现货延期交收本地报单号查询请求
   	* @param pReqQryOrder 输入参数，报单查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryDeferLocalOrder( TReqQryLocalOrder *pReqQryLocalOrder,char *RootID=NULL);
   	/**现货延期交收本地报单号查询应答
   	* @param pDeferOrder 输出参数，现货延期交收报单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryDeferLocalOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
	/**现货T+N本地报单号查询请求
   	* @param pReqQryOrder 输入参数，报单查询请求
   	* @param RootID  输入参数，请求包的唯一标示
   	* @return 0 : 成功 
	*         -1: 发送失败
  	*/
  	int ReqQryForwardLocalOrder( TReqQryLocalOrder *pReqQryLocalOrder,char *RootID=NULL);
   	/**现货T+N本地报单号查询应答
   	* @param pForwardOrder 输出参数，现货T+N报单
   	* @param pRspMsg 输出参数，请求执行结果和连续包标志
   	* @param RootID  输出参数，与请求包对应的唯一标示
  	*/
   	virtual void onRecvRspQryForwardLocalOrder(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}

private:
	int  loginReq(TReqTraderLogin *pTLoginReq,char *RootID=NULL);
	int  PutSafeAck(void *pTSafeAck,void *pTLoginReqField);

	char m_Passwd[9];
	short m_InputType;
	short m_ComID;
};
#endif
