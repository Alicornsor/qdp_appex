#ifndef CAPI_H
#define CAPI_H
#include "APIStruct.h"
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

#define NULL 0

struct FService
{
	char m_Ip[50];
	int  m_Port;
};
class API_EXPORT CApi
{
public:
	CApi(void);
	~CApi(void) {}
	
	/**初始化
	* @return 0表示成功，1表示失败
	*/
	int initApi(void);
	
	/**设置前置机的IP和端口
	* @param sIp 前置机的IP
	* @param nPort 前置机的端口
	*/
	void SetService(char *sIp, int nPort);
	
	/**获取当前的交易日期
	* @param tradeDate 输出参数，返回当前的交易日期
	*/
	void GetTradeDate(char *tradeDate);
	
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
	
	/**用户输入
	*/
	virtual void onRecvIcCardPwd(TPassword &passwd,short inputType,short comID) {}
	
   	/**交易员登录应答
  	*/
  	virtual void onRecvRspTraderLogin(TReqTraderLogin *pReqTraderLogin,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**交易员退出应答
  	*/
  	virtual void onRecvRspTraderLogout(TReqTraderLogout *pReqTraderLogout,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货报单应答
  	*/
  	virtual void onRecvRspSpotOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货撤单应答
  	*/
  	virtual void onRecvRspSpotOrderCancel(TSpotOrderCancel *pSpotOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收报单应答
  	*/
  	virtual void onRecvRspDeferOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收撤单应答
  	*/
  	virtual void onRecvRspDeferOrderCancel(TDeferOrderCancel *pDeferOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货报单回报
  	*/
  	virtual void onRecvRtnSpotOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收报单回报
  	*/
  	virtual void onRecvRtnDeferOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货撤单回报
  	*/
  	virtual void onRecvRtnSpotOrderCancel(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收撤单回报
  	*/
  	virtual void onRecvRtnDeferOrderCancel(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收交割申报应答
  	*/
  	virtual void onRecvRspDeferDeliveryAppOrder(TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收交割申报撤消应答
  	*/
  	virtual void onRecvRspDeferDeliveryAppOrderCancel(TDeferDeliveryAppOrderCancel *pDeferDeliveryAppOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收中立仓申报应答
  	*/
  	virtual void onRecvRspMiddleAppOrder(TMiddleAppOrder *pMiddleAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收中立仓申报撤单应答
  	*/
  	virtual void onRecvRspMiddleAppOrderCancel(TMiddleAppOrderCancel *pMiddleAppOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收交割申报回报
  	*/
  	virtual void onRecvRtnDeferDeliveryAppOrder(TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收中立仓申报回报
  	*/
  	virtual void onRecvRtnMiddleAppOrder(TMiddleAppOrder *pMiddleAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收交割申报撤消回报
  	*/
  	virtual void onRecvRtnDeferDeliveryAppOrderCancel(TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收中立仓申报撤单回报
  	*/
  	virtual void onRecvRtnMiddleAppOrderCancel(TMiddleAppOrder *pMiddleAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货报单应答
  	*/
  	virtual void onRecvRspFuturesOrder(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货撤单应答
  	*/
  	virtual void onRecvRspFuturesOrderCancel(TFuturesOrderCancel *pFuturesOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N报单应答
  	*/
  	virtual void onRecvRspForwardOrder(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N撤单应答
  	*/
  	virtual void onRecvRspForwardOrderCancel(TForwardOrderCancel *pForwardOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N到期转让报单应答
  	*/
  	virtual void onRecvRspForwardEndorseOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N到期转让撤单应答
  	*/
  	virtual void onRecvRspForwardEndorseOrderCancel(TForwardEndorseOrderCancel *pForwardEndorseOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货报单回报
  	*/
  	virtual void onRecvRtnFuturesOrder(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N报单回报
  	*/
  	virtual void onRecvRtnForwardOrder(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货撤单回报
  	*/
  	virtual void onRecvRtnFuturesOrderCancel(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N撤单回报
  	*/
  	virtual void onRecvRtnForwardOrderCancel(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N到期转让报单回报
  	*/
  	virtual void onRecvRtnForwardEndorseOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N到期转让撤单回报
  	*/
  	virtual void onRecvRtnForwardEndorseOrderCancel(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**交易员密码修改应答
  	*/
  	virtual void onRecvRspTraderPasswordUpdate(TReqTraderPasswordUpdate *pReqTraderPasswordUpdate,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**会员应急密码修改应答
  	*/
  	virtual void onRecvRspMemberUrgentPasswordUpdate(TReqMemberUrgentPasswordUpdate *pReqMemberUrgentPasswordUpdate,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	
	/**会员资金查询应答
  	*/
  	virtual void onRecvRspQryMemberCapital(TMemberCapital *pMemberCapital,TTRspMsg *pRspMsg,char *RootID=NULL){}
	
   	/**客户库存查询应答
  	*/
  	virtual void onRecvRspQryClientStorage(TClientStorage *pClientStorage,TTRspMsg *pRspMsg,char *RootID=NULL){}

	// Added by qingquan.xue 20140310 begin
	/**会员资金查询应答（充抵）
  	*/
	virtual void onRecvRspQryClientStorageEx(TClientStorageEx *pClientStorage,TTRspMsg *pRspMsg,char *RootID=NULL){}

	/**客户库存查询应答（充抵）
  	*/
	virtual void onRecvRspQryMemberCapitalEx(TMemberCapitalEx *pMemberCapital,TTRspMsg *pRspMsg,char *RootID=NULL){}
	// Added by qingquan.xue 20140310 end

   	/**现货报单查询应答
  	*/
  	virtual void onRecvRspQrySpotOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
    /**现货报单查询应答(V2)
  	*/
  	virtual void onRecvRspQrySpotOrderEx(TSpotOrderEx *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收报单查询应答
  	*/
  	virtual void onRecvRspQryDeferOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收报单查询应答(V2)
  	*/
  	virtual void onRecvRspQryDeferOrderEx(TDeferOrderEx *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收交割申报报单查询应答
  	*/
  	virtual void onRecvRspQryDeferDeliveryAppOrder(TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收中立仓申报报单查询应答
  	*/
  	virtual void onRecvRspQryMiddleAppOrder(TMiddleAppOrder *pMiddleAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货报单查询应答
  	*/
  	virtual void onRecvRspQryFuturesOrder(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N报单查询应答
  	*/
  	virtual void onRecvRspQryForwardOrder(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N报单查询应答(V2)
  	*/
  	virtual void onRecvRspQryForwardOrderEx(TForwardOrderEx *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N到期转让报单查询应答
  	*/
  	virtual void onRecvRspQryForwardEndorseOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货成交单查询应答
  	*/
  	virtual void onRecvRspQrySpotMatch(TSpotMatch *pSpotMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收成交单查询应答
  	*/
  	virtual void onRecvRspQryDeferMatch(TDeferMatch *pDeferMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收交割申报成交单查询应答
  	*/
  	virtual void onRecvRspQryDeferDeliveryAppMatch(TDeferDeliveryAppMatch *pDeferDeliveryAppMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货成交单查询应答
  	*/
  	virtual void onRecvRspQryFuturesMatch(TFuturesMatch *pFuturesMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N成交单查询应答
  	*/
  	virtual void onRecvRspQryForwardMatch(TForwardMatch *pForwardMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N到期转让成交单查询应答
  	*/
  	virtual void onRecvRspQryForwardEndorseMatch(TSpotMatch *pSpotMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货成交回报
  	*/
  	virtual void onRecvRtnSpotMatch(TSpotMatch *pSpotMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收成交回报
  	*/
  	virtual void onRecvRtnDeferMatch(TDeferMatch *pDeferMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收交割申报成交回报
  	*/
  	virtual void onRecvRtnDeferDeliveryAppMatch(TDeferDeliveryAppMatch *pDeferDeliveryAppMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货成交回报
  	*/
  	virtual void onRecvRtnFuturesMatch(TFuturesMatch *pFuturesMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N成交回报
  	*/
  	virtual void onRecvRtnForwardMatch(TForwardMatch *pForwardMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N到期转让成交回报
  	*/
  	virtual void onRecvRtnForwardEndorseMatch(TSpotMatch *pSpotMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**会员现货延期交收持仓查询应答
  	*/
  	virtual void onRecvRspQryDeferMemberPosi(TDeferMemberPosi *pDeferMemberPosi,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**会员期货持仓查询应答
  	*/
  	virtual void onRecvRspQryFuturesMemberPosi(TFuturesMemberPosi *pFuturesMemberPosi,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**会员现货T+N持仓查询应答
  	*/
  	virtual void onRecvRspQryForwardMemberPosi(TForwardMemberPosi *pForwardMemberPosi,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**客户现货延期交收持仓查询应答
  	*/
  	virtual void onRecvRspQryDeferClientPosi(TDeferClientPosi *pDeferClientPosi,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**客户期货持仓查询应答
  	*/
  	virtual void onRecvRspQryFuturesClientPosi(TFuturesClientPosi *pFuturesClientPosi,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**客户现货T+N持仓查询应答
  	*/
  	virtual void onRecvRspQryForwardClientPosi(TForwardClientPosi *pForwardClientPosi,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货行情查询应答
  	*/
  	virtual void onRecvRspQrySpotQuotation(TSpotQuotation *pSpotQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收行情查询应答
  	*/
  	virtual void onRecvRspQryDeferQuotation(TDeferQuotation *pDeferQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货行情查询应答
  	*/
  	virtual void onRecvRspQryFuturesQuotation(TFuturesQuotation *pFuturesQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N行情查询应答
  	*/
  	virtual void onRecvRspQryForwardQuotation(TForwardQuotation *pForwardQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**市场信息回报
  	*/
  	virtual void onRecvMarketInfo(TMarket *pMarket,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货合约信息回报
  	*/
  	virtual void onRecvSpotInstInfo(TSpotInst *pSpotInst,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**递延合约信息回报
  	*/
  	virtual void onRecvDeferInstInfo(TDeferInst *pDeferInst,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货合约信息回报
  	*/
  	virtual void onRecvFuturesInstInfo(TFuturesInst *pFuturesInst,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**远期合约信息回报
  	*/
  	virtual void onRecvForwardInstInfo(TForwardInst *pForwardInst,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**递延费率查询请求应答
  	*/
  	virtual void onRecvRspQryDeferFeeRate(TDeferFeeRate *pDeferFeeRate,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货合约交易状态改变回报
  	*/
  	virtual void onRecvRtnSpotInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货市场交易状态改变回报
  	*/
  	virtual void onRecvRtnSpotMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**递延合约交易状态改变回报
  	*/
  	virtual void onRecvRtnDeferInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**递延市场交易状态改变回报
  	*/
  	virtual void onRecvRtnDeferMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货合约交易状态改变回报
  	*/
  	virtual void onRecvRtnFuturesInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货市场交易状态改变回报
  	*/
  	virtual void onRecvRtnFuturesMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**远期合约交易状态改变回报
  	*/
  	virtual void onRecvRtnForwardInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**远期市场交易状态改变回报
  	*/
  	virtual void onRecvRtnForwardMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**交易所公告查询请求应答
  	*/
  	virtual void onRecvRspQryBulletinBoard(TBulletinBoard *pBulletinBoard,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**公告回报
  	*/
  	virtual void onRecvRtnBulletinBoard(TBulletinBoard *pBulletinBoard,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**国际行情回报
  	*/
  	virtual void onRecvRtnInterQuotation(TInterQuotation *pInterQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**国际行情查询请求应答
  	*/
  	virtual void onRecvRspQryInterQuotation(TInterQuotation *pInterQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货行情
  	*/
  	virtual void onRecvSpotQuotation(TSpotQuotation *pSpotQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收行情
  	*/
  	virtual void onRecvDeferQuotation(TDeferQuotation *pDeferQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货行情
  	*/
  	virtual void onRecvFuturesQuotation(TFuturesQuotation *pFuturesQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N行情
  	*/
  	virtual void onRecvForwardQuotation(TForwardQuotation *pForwardQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**当天现货分钟行情
  	*/
  	virtual void onRecvMinsSpotQuotation(TMinsSpotQuotation *pMinsSpotQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**当天期货分钟行情
  	*/
  	virtual void onRecvMinsFuturesQuotation(TMinsFuturesQuotation *pMinsFuturesQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**当天远期分钟行情
  	*/
  	virtual void onRecvMinsForwardQuotation(TMinsForwardQuotation *pMinsForwardQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**当天递延分钟行情
  	*/
  	virtual void onRecvMinsDeferQuotation(TMinsDeferQuotation *pMinsDeferQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货分钟行情查询应答
  	*/
  	virtual void onRecvRspQrySpotMinsQuotation(TMinsSpotQuotation *pMinsSpotQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收分钟行情查询应答
  	*/
  	virtual void onRecvRspQryDeferMinsQuotation(TMinsDeferQuotation *pMinsDeferQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货分钟行情查询应答
  	*/
  	virtual void onRecvRspQryFuturesMinsQuotation(TMinsFuturesQuotation *pMinsFuturesQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N分钟行情查询应答
  	*/
  	virtual void onRecvRspQryForwardMinsQuotation(TMinsForwardQuotation *pMinsForwardQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**发布现货延期交收补偿费率通知
  	*/
  	virtual void onRecvDeferFeeRateUpdate(TDeferFeeRate *pDeferFeeRate,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**会员客户查询响应
  	*/
  	virtual void onRecvRspQryClient(TClient *pClient,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**递延交收行情
  	*/
  	virtual void onRecvDeferDeliveryQuotation(TDeferDeliveryQuotation *pDeferDeliveryQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**交割品种代码信息
  	*/
  	virtual void onRecvVarietyInfo(TVariety *pVariety,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**监控员登录应答
  	*/
  	virtual void onRecvRspUserLogin(TReqUserLogin *pReqUserLogin,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**监控员退出应答
  	*/
  	virtual void onRecvRspUserLogout(TReqUserLogout *pReqUserLogout,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货合约交易状态改变应答
  	*/
  	virtual void onRecvRspSpotInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货市场交易状态改变应答
  	*/
  	virtual void onRecvRspSpotMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货合约交易状态查询应答
  	*/
  	virtual void onRecvRspQrySpotInstState(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货市场交易状态查询应答
  	*/
  	virtual void onRecvRspQrySpotMarketState(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货合约交易状态改变应答
  	*/
  	virtual void onRecvRspFuturesInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货市场交易状态改变应答
  	*/
  	virtual void onRecvRspFuturesMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货合约交易状态查询应答
  	*/
  	virtual void onRecvRspQryFuturesInstState(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货市场交易状态查询应答
  	*/
  	virtual void onRecvRspQryFuturesMarketState(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**远期合约交易状态改变应答
  	*/
  	virtual void onRecvRspForwardInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**远期市场交易状态改变应答
  	*/
  	virtual void onRecvRspForwardMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**远期合约交易状态查询应答
  	*/
  	virtual void onRecvRspQryForwardInstState(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**远期市场交易状态查询应答
  	*/
  	virtual void onRecvRspQryForwardMarketState(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**递延合约交易状态改变应答
  	*/
  	virtual void onRecvRspDeferInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**递延市场交易状态改变应答
  	*/
  	virtual void onRecvRspDeferMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**递延合约交易状态查询应答
  	*/
  	virtual void onRecvRspQryDeferInstState(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**递延市场交易状态查询应答
  	*/
  	virtual void onRecvRspQryDeferMarketState(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**发布现货延期交收补偿费率应答
  	*/
  	virtual void onRecvRspDeferFeeRateUpdate(TDeferFeeRate *pDeferFeeRate,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**交易员在线查询应答
  	*/
  	virtual void onRecvRspQryTrader(TTrader *pTrader,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**交易所公告请求应答
  	*/
  	virtual void onRecvRspBulletinBoard(TBulletinBoard *pBulletinBoard,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货应急报单应答
  	*/
  	virtual void onRecvRspUrgentSpotOrder(TUrgentSpotOrder *pUrgentSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收应急报单应答
  	*/
  	virtual void onRecvRspUrgentDeferOrder(TUrgentDeferOrder *pUrgentDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货应急报单应答
  	*/
  	virtual void onRecvRspUrgentFuturesOrder(TUrgentFuturesOrder *pUrgentFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N应急报单应答
  	*/
  	virtual void onRecvRspUrgentForwardOrder(TUrgentForwardOrder *pUrgentForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货应急报单查询应答
  	*/
  	virtual void onRecvRspQryUrgentSpotOrder(TUrgentSpotOrder *pUrgentSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收应急报单查询应答
  	*/
  	virtual void onRecvRspQryUrgentDeferOrder(TUrgentDeferOrder *pUrgentDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货应急报单查询应答
  	*/
  	virtual void onRecvRspQryUrgentFuturesOrder(TUrgentFuturesOrder *pUrgentFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N应急报单查询应答
  	*/
  	virtual void onRecvRspQryUrgentForwardOrder(TUrgentForwardOrder *pUrgentForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货应急报单复核应答
  	*/
  	virtual void onRecvRspChkUrgentSpotOrder(TUrgentSpotOrder *pUrgentSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收应急报单复核应答
  	*/
  	virtual void onRecvRspChkUrgentDeferOrder(TUrgentDeferOrder *pUrgentDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货应急报单复核应答
  	*/
  	virtual void onRecvRspChkUrgentFuturesOrder(TUrgentFuturesOrder *pUrgentFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货T+N应急报单复核应答
  	*/
  	virtual void onRecvRspChkUrgentForwardOrder(TUrgentForwardOrder *pUrgentForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收强行平仓报单应答
  	*/
  	virtual void onRecvRspForceDeferOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货强行平仓报单应答
  	*/
  	virtual void onRecvRspForceFuturesOrder(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货强行平仓撤单应答
  	*/
  	virtual void onRecvRspForceFuturesOrderCancel(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货延期交收强行平仓撤单应答
  	*/
  	virtual void onRecvRspForceDeferOrderCancel(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**会员超仓查询响应
  	*/
  	virtual void onRecvRspQryMemberPosiOver(TRspQryMemberPosiOver *pRspQryMemberPosiOver,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**客户超仓查询响应
  	*/
  	virtual void onRecvRspQryClientPosiOver(TRspQryClientPosiOver *pRspQryClientPosiOver,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**资金不足查询响应
  	*/
  	virtual void onRecvRspQryCapitalLack(TRspQryCapitalLack *pRspQryCapitalLack,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货强平成交单查询应答
  	*/
  	virtual void onRecvRspQryForceFuturesMatch(TFuturesMatch *pFuturesMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**递延强平成交单查询应答
  	*/
  	virtual void onRecvRspQryForceDeferMatch(TDeferMatch *pDeferMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**发布国际行情应答
  	*/
  	virtual void onRecvRspInterQuotation(TInterQuotation *pInterQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**强制交易员退出应答
  	*/
  	virtual void onRecvRspForceTraderLogout(TReqForceTraderLogout *pReqForceTraderLogout,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**现货应急报单撤单应答
  	*/
  	virtual void onRecvRspUrgentSpotOrderCancel(TUrgentSpotOrderCancel *pUrgentSpotOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**递延应急报单撤单应答
  	*/
  	virtual void onRecvRspUrgentDeferOrderCancel(TUrgentDeferOrderCancel *pUrgentDeferOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**期货应急报单撤单应答
  	*/
  	virtual void onRecvRspUrgentFuturesOrderCancel(TUrgentFuturesOrderCancel *pUrgentFuturesOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**远期应急报单撤单应答
  	*/
  	virtual void onRecvRspUrgentForwardOrderCancel(TUrgentForwardOrderCancel *pUrgentForwardOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**状态模式响应
  	*/
  	virtual void onRecvRspStateMode(TStateMode *pStateMode,TTRspMsg *pRspMsg,char *RootID=NULL){}
	/**现货本地报单号查询应答
  	*/
   	virtual void onRecvRspQrySpotLocalOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}		
   	/**现货延期交收本地报单号查询应答
  	*/
   	virtual void onRecvRspQryDeferLocalOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}	
	/**现货T+N本地报单号查询应答
  	*/
   	virtual void onRecvRspQryForwardLocalOrder(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
	/**现货报单强撤应答
  	*/
   	virtual void onRecvRspSpotOrderForceCancel(TSpotOrderCancel *pSpotOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
	/**递延报单强撤应答
  	*/
   	virtual void onRecvRspDeferOrderForceCancel(TDeferOrderCancel *pSpotOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
	/**T+N报单强撤应答
  	*/
   	virtual void onRecvRspForwardOrderForceCancel(TForwardOrderCancel *pSpotOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
	/**会员资金不足强平手数计算应答
  	*/
   	virtual void onRecvRspCalcMemberOffsetAmount(TReqQryCapitalLack *pQryCapitalLack,TTRspMsg *pRspMsg,char *RootID=NULL){}

	/**获取版本号
  	*/
	const char *GetVersionInfo() {return m_pVersionInfo;}

	void onRecvSafeOpError(void *pRtn);
	void GetLastService(FService &AService);

	UINT GetTimeMark();//added by qingquan.xue 20130902

protected:
	FService m_Service[100];
	int      m_FCount;
	void AdjustService(int pos);

private:
	static const char *m_pVersionInfo;	/**< 版本信息 **/
};
#endif
