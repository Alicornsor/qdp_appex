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
	
	/**��ʼ��
	* @return 0��ʾ�ɹ���1��ʾʧ��
	*/
	int initApi(void);
	
	/**����ǰ�û���IP�Ͷ˿�
	* @param sIp ǰ�û���IP
	* @param nPort ǰ�û��Ķ˿�
	*/
	void SetService(char *sIp, int nPort);
	
	/**��ȡ��ǰ�Ľ�������
	* @param tradeDate ������������ص�ǰ�Ľ�������
	*/
	void GetTradeDate(char *tradeDate);
	
	/**������ǰ�����ӶϿ�ʱ�Ĵ�����Ϣ
	* @param ErrMsg ������������ش�����Ϣ
	*/
	virtual void  onChannelLost(char *ErrMsg) {}
	
	/**����Ӧ�õĴ�����Ϣ
	* @param ExceptionMsg ����������������������Ϣ
	*/
	virtual void  onException(char *ExceptionMsg) {}
	
	/**����ϵͳ����֪ͨ��Ϣ
	* @param pRspMsg ����������������������Ϣ
	*/
	virtual void onRecvSysErrorNtf(TTRspMsg *pRspMsg) {}
	
	/**�û�����
	*/
	virtual void onRecvIcCardPwd(TPassword &passwd,short inputType,short comID) {}
	
   	/**����Ա��¼Ӧ��
  	*/
  	virtual void onRecvRspTraderLogin(TReqTraderLogin *pReqTraderLogin,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**����Ա�˳�Ӧ��
  	*/
  	virtual void onRecvRspTraderLogout(TReqTraderLogout *pReqTraderLogout,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�����Ӧ��
  	*/
  	virtual void onRecvRspSpotOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�����Ӧ��
  	*/
  	virtual void onRecvRspSpotOrderCancel(TSpotOrderCancel *pSpotOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��ձ���Ӧ��
  	*/
  	virtual void onRecvRspDeferOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��ճ���Ӧ��
  	*/
  	virtual void onRecvRspDeferOrderCancel(TDeferOrderCancel *pDeferOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ������ر�
  	*/
  	virtual void onRecvRtnSpotOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��ձ����ر�
  	*/
  	virtual void onRecvRtnDeferOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ������ر�
  	*/
  	virtual void onRecvRtnSpotOrderCancel(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��ճ����ر�
  	*/
  	virtual void onRecvRtnDeferOrderCancel(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��ս����걨Ӧ��
  	*/
  	virtual void onRecvRspDeferDeliveryAppOrder(TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��ս����걨����Ӧ��
  	*/
  	virtual void onRecvRspDeferDeliveryAppOrderCancel(TDeferDeliveryAppOrderCancel *pDeferDeliveryAppOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ����������걨Ӧ��
  	*/
  	virtual void onRecvRspMiddleAppOrder(TMiddleAppOrder *pMiddleAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ����������걨����Ӧ��
  	*/
  	virtual void onRecvRspMiddleAppOrderCancel(TMiddleAppOrderCancel *pMiddleAppOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��ս����걨�ر�
  	*/
  	virtual void onRecvRtnDeferDeliveryAppOrder(TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ����������걨�ر�
  	*/
  	virtual void onRecvRtnMiddleAppOrder(TMiddleAppOrder *pMiddleAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��ս����걨�����ر�
  	*/
  	virtual void onRecvRtnDeferDeliveryAppOrderCancel(TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ����������걨�����ر�
  	*/
  	virtual void onRecvRtnMiddleAppOrderCancel(TMiddleAppOrder *pMiddleAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ�����Ӧ��
  	*/
  	virtual void onRecvRspFuturesOrder(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ�����Ӧ��
  	*/
  	virtual void onRecvRspFuturesOrderCancel(TFuturesOrderCancel *pFuturesOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N����Ӧ��
  	*/
  	virtual void onRecvRspForwardOrder(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N����Ӧ��
  	*/
  	virtual void onRecvRspForwardOrderCancel(TForwardOrderCancel *pForwardOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N����ת�ñ���Ӧ��
  	*/
  	virtual void onRecvRspForwardEndorseOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N����ת�ó���Ӧ��
  	*/
  	virtual void onRecvRspForwardEndorseOrderCancel(TForwardEndorseOrderCancel *pForwardEndorseOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ������ر�
  	*/
  	virtual void onRecvRtnFuturesOrder(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N�����ر�
  	*/
  	virtual void onRecvRtnForwardOrder(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ������ر�
  	*/
  	virtual void onRecvRtnFuturesOrderCancel(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N�����ر�
  	*/
  	virtual void onRecvRtnForwardOrderCancel(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N����ת�ñ����ر�
  	*/
  	virtual void onRecvRtnForwardEndorseOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N����ת�ó����ر�
  	*/
  	virtual void onRecvRtnForwardEndorseOrderCancel(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**����Ա�����޸�Ӧ��
  	*/
  	virtual void onRecvRspTraderPasswordUpdate(TReqTraderPasswordUpdate *pReqTraderPasswordUpdate,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**��ԱӦ�������޸�Ӧ��
  	*/
  	virtual void onRecvRspMemberUrgentPasswordUpdate(TReqMemberUrgentPasswordUpdate *pReqMemberUrgentPasswordUpdate,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	
	/**��Ա�ʽ��ѯӦ��
  	*/
  	virtual void onRecvRspQryMemberCapital(TMemberCapital *pMemberCapital,TTRspMsg *pRspMsg,char *RootID=NULL){}
	
   	/**�ͻ�����ѯӦ��
  	*/
  	virtual void onRecvRspQryClientStorage(TClientStorage *pClientStorage,TTRspMsg *pRspMsg,char *RootID=NULL){}

	// Added by qingquan.xue 20140310 begin
	/**��Ա�ʽ��ѯӦ�𣨳�֣�
  	*/
	virtual void onRecvRspQryClientStorageEx(TClientStorageEx *pClientStorage,TTRspMsg *pRspMsg,char *RootID=NULL){}

	/**�ͻ�����ѯӦ�𣨳�֣�
  	*/
	virtual void onRecvRspQryMemberCapitalEx(TMemberCapitalEx *pMemberCapital,TTRspMsg *pRspMsg,char *RootID=NULL){}
	// Added by qingquan.xue 20140310 end

   	/**�ֻ�������ѯӦ��
  	*/
  	virtual void onRecvRspQrySpotOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
    /**�ֻ�������ѯӦ��(V2)
  	*/
  	virtual void onRecvRspQrySpotOrderEx(TSpotOrderEx *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��ձ�����ѯӦ��
  	*/
  	virtual void onRecvRspQryDeferOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��ձ�����ѯӦ��(V2)
  	*/
  	virtual void onRecvRspQryDeferOrderEx(TDeferOrderEx *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��ս����걨������ѯӦ��
  	*/
  	virtual void onRecvRspQryDeferDeliveryAppOrder(TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ����������걨������ѯӦ��
  	*/
  	virtual void onRecvRspQryMiddleAppOrder(TMiddleAppOrder *pMiddleAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ�������ѯӦ��
  	*/
  	virtual void onRecvRspQryFuturesOrder(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N������ѯӦ��
  	*/
  	virtual void onRecvRspQryForwardOrder(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N������ѯӦ��(V2)
  	*/
  	virtual void onRecvRspQryForwardOrderEx(TForwardOrderEx *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N����ת�ñ�����ѯӦ��
  	*/
  	virtual void onRecvRspQryForwardEndorseOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ��ɽ�����ѯӦ��
  	*/
  	virtual void onRecvRspQrySpotMatch(TSpotMatch *pSpotMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��ճɽ�����ѯӦ��
  	*/
  	virtual void onRecvRspQryDeferMatch(TDeferMatch *pDeferMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��ս����걨�ɽ�����ѯӦ��
  	*/
  	virtual void onRecvRspQryDeferDeliveryAppMatch(TDeferDeliveryAppMatch *pDeferDeliveryAppMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ��ɽ�����ѯӦ��
  	*/
  	virtual void onRecvRspQryFuturesMatch(TFuturesMatch *pFuturesMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N�ɽ�����ѯӦ��
  	*/
  	virtual void onRecvRspQryForwardMatch(TForwardMatch *pForwardMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N����ת�óɽ�����ѯӦ��
  	*/
  	virtual void onRecvRspQryForwardEndorseMatch(TSpotMatch *pSpotMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ��ɽ��ر�
  	*/
  	virtual void onRecvRtnSpotMatch(TSpotMatch *pSpotMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��ճɽ��ر�
  	*/
  	virtual void onRecvRtnDeferMatch(TDeferMatch *pDeferMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��ս����걨�ɽ��ر�
  	*/
  	virtual void onRecvRtnDeferDeliveryAppMatch(TDeferDeliveryAppMatch *pDeferDeliveryAppMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ��ɽ��ر�
  	*/
  	virtual void onRecvRtnFuturesMatch(TFuturesMatch *pFuturesMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N�ɽ��ر�
  	*/
  	virtual void onRecvRtnForwardMatch(TForwardMatch *pForwardMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N����ת�óɽ��ر�
  	*/
  	virtual void onRecvRtnForwardEndorseMatch(TSpotMatch *pSpotMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**��Ա�ֻ����ڽ��ճֲֲ�ѯӦ��
  	*/
  	virtual void onRecvRspQryDeferMemberPosi(TDeferMemberPosi *pDeferMemberPosi,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**��Ա�ڻ��ֲֲ�ѯӦ��
  	*/
  	virtual void onRecvRspQryFuturesMemberPosi(TFuturesMemberPosi *pFuturesMemberPosi,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**��Ա�ֻ�T+N�ֲֲ�ѯӦ��
  	*/
  	virtual void onRecvRspQryForwardMemberPosi(TForwardMemberPosi *pForwardMemberPosi,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ͻ��ֻ����ڽ��ճֲֲ�ѯӦ��
  	*/
  	virtual void onRecvRspQryDeferClientPosi(TDeferClientPosi *pDeferClientPosi,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ͻ��ڻ��ֲֲ�ѯӦ��
  	*/
  	virtual void onRecvRspQryFuturesClientPosi(TFuturesClientPosi *pFuturesClientPosi,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ͻ��ֻ�T+N�ֲֲ�ѯӦ��
  	*/
  	virtual void onRecvRspQryForwardClientPosi(TForwardClientPosi *pForwardClientPosi,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ������ѯӦ��
  	*/
  	virtual void onRecvRspQrySpotQuotation(TSpotQuotation *pSpotQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��������ѯӦ��
  	*/
  	virtual void onRecvRspQryDeferQuotation(TDeferQuotation *pDeferQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ������ѯӦ��
  	*/
  	virtual void onRecvRspQryFuturesQuotation(TFuturesQuotation *pFuturesQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N�����ѯӦ��
  	*/
  	virtual void onRecvRspQryForwardQuotation(TForwardQuotation *pForwardQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�г���Ϣ�ر�
  	*/
  	virtual void onRecvMarketInfo(TMarket *pMarket,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ���Լ��Ϣ�ر�
  	*/
  	virtual void onRecvSpotInstInfo(TSpotInst *pSpotInst,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**���Ӻ�Լ��Ϣ�ر�
  	*/
  	virtual void onRecvDeferInstInfo(TDeferInst *pDeferInst,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ���Լ��Ϣ�ر�
  	*/
  	virtual void onRecvFuturesInstInfo(TFuturesInst *pFuturesInst,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**Զ�ں�Լ��Ϣ�ر�
  	*/
  	virtual void onRecvForwardInstInfo(TForwardInst *pForwardInst,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**���ӷ��ʲ�ѯ����Ӧ��
  	*/
  	virtual void onRecvRspQryDeferFeeRate(TDeferFeeRate *pDeferFeeRate,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ���Լ����״̬�ı�ر�
  	*/
  	virtual void onRecvRtnSpotInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ��г�����״̬�ı�ر�
  	*/
  	virtual void onRecvRtnSpotMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**���Ӻ�Լ����״̬�ı�ر�
  	*/
  	virtual void onRecvRtnDeferInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�����г�����״̬�ı�ر�
  	*/
  	virtual void onRecvRtnDeferMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ���Լ����״̬�ı�ر�
  	*/
  	virtual void onRecvRtnFuturesInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ��г�����״̬�ı�ر�
  	*/
  	virtual void onRecvRtnFuturesMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**Զ�ں�Լ����״̬�ı�ر�
  	*/
  	virtual void onRecvRtnForwardInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**Զ���г�����״̬�ı�ر�
  	*/
  	virtual void onRecvRtnForwardMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�����������ѯ����Ӧ��
  	*/
  	virtual void onRecvRspQryBulletinBoard(TBulletinBoard *pBulletinBoard,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**����ر�
  	*/
  	virtual void onRecvRtnBulletinBoard(TBulletinBoard *pBulletinBoard,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**��������ر�
  	*/
  	virtual void onRecvRtnInterQuotation(TInterQuotation *pInterQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**���������ѯ����Ӧ��
  	*/
  	virtual void onRecvRspQryInterQuotation(TInterQuotation *pInterQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�����
  	*/
  	virtual void onRecvSpotQuotation(TSpotQuotation *pSpotQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ�������
  	*/
  	virtual void onRecvDeferQuotation(TDeferQuotation *pDeferQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ�����
  	*/
  	virtual void onRecvFuturesQuotation(TFuturesQuotation *pFuturesQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N����
  	*/
  	virtual void onRecvForwardQuotation(TForwardQuotation *pForwardQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�����ֻ���������
  	*/
  	virtual void onRecvMinsSpotQuotation(TMinsSpotQuotation *pMinsSpotQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�����ڻ���������
  	*/
  	virtual void onRecvMinsFuturesQuotation(TMinsFuturesQuotation *pMinsFuturesQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**����Զ�ڷ�������
  	*/
  	virtual void onRecvMinsForwardQuotation(TMinsForwardQuotation *pMinsForwardQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**������ӷ�������
  	*/
  	virtual void onRecvMinsDeferQuotation(TMinsDeferQuotation *pMinsDeferQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����������ѯӦ��
  	*/
  	virtual void onRecvRspQrySpotMinsQuotation(TMinsSpotQuotation *pMinsSpotQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ��շ��������ѯӦ��
  	*/
  	virtual void onRecvRspQryDeferMinsQuotation(TMinsDeferQuotation *pMinsDeferQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ����������ѯӦ��
  	*/
  	virtual void onRecvRspQryFuturesMinsQuotation(TMinsFuturesQuotation *pMinsFuturesQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+N���������ѯӦ��
  	*/
  	virtual void onRecvRspQryForwardMinsQuotation(TMinsForwardQuotation *pMinsForwardQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�����ֻ����ڽ��ղ�������֪ͨ
  	*/
  	virtual void onRecvDeferFeeRateUpdate(TDeferFeeRate *pDeferFeeRate,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**��Ա�ͻ���ѯ��Ӧ
  	*/
  	virtual void onRecvRspQryClient(TClient *pClient,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**���ӽ�������
  	*/
  	virtual void onRecvDeferDeliveryQuotation(TDeferDeliveryQuotation *pDeferDeliveryQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**����Ʒ�ִ�����Ϣ
  	*/
  	virtual void onRecvVarietyInfo(TVariety *pVariety,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**���Ա��¼Ӧ��
  	*/
  	virtual void onRecvRspUserLogin(TReqUserLogin *pReqUserLogin,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**���Ա�˳�Ӧ��
  	*/
  	virtual void onRecvRspUserLogout(TReqUserLogout *pReqUserLogout,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ���Լ����״̬�ı�Ӧ��
  	*/
  	virtual void onRecvRspSpotInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ��г�����״̬�ı�Ӧ��
  	*/
  	virtual void onRecvRspSpotMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ���Լ����״̬��ѯӦ��
  	*/
  	virtual void onRecvRspQrySpotInstState(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ��г�����״̬��ѯӦ��
  	*/
  	virtual void onRecvRspQrySpotMarketState(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ���Լ����״̬�ı�Ӧ��
  	*/
  	virtual void onRecvRspFuturesInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ��г�����״̬�ı�Ӧ��
  	*/
  	virtual void onRecvRspFuturesMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ���Լ����״̬��ѯӦ��
  	*/
  	virtual void onRecvRspQryFuturesInstState(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ��г�����״̬��ѯӦ��
  	*/
  	virtual void onRecvRspQryFuturesMarketState(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**Զ�ں�Լ����״̬�ı�Ӧ��
  	*/
  	virtual void onRecvRspForwardInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**Զ���г�����״̬�ı�Ӧ��
  	*/
  	virtual void onRecvRspForwardMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**Զ�ں�Լ����״̬��ѯӦ��
  	*/
  	virtual void onRecvRspQryForwardInstState(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**Զ���г�����״̬��ѯӦ��
  	*/
  	virtual void onRecvRspQryForwardMarketState(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**���Ӻ�Լ����״̬�ı�Ӧ��
  	*/
  	virtual void onRecvRspDeferInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�����г�����״̬�ı�Ӧ��
  	*/
  	virtual void onRecvRspDeferMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**���Ӻ�Լ����״̬��ѯӦ��
  	*/
  	virtual void onRecvRspQryDeferInstState(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�����г�����״̬��ѯӦ��
  	*/
  	virtual void onRecvRspQryDeferMarketState(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�����ֻ����ڽ��ղ�������Ӧ��
  	*/
  	virtual void onRecvRspDeferFeeRateUpdate(TDeferFeeRate *pDeferFeeRate,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**����Ա���߲�ѯӦ��
  	*/
  	virtual void onRecvRspQryTrader(TTrader *pTrader,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**��������������Ӧ��
  	*/
  	virtual void onRecvRspBulletinBoard(TBulletinBoard *pBulletinBoard,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�Ӧ������Ӧ��
  	*/
  	virtual void onRecvRspUrgentSpotOrder(TUrgentSpotOrder *pUrgentSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ���Ӧ������Ӧ��
  	*/
  	virtual void onRecvRspUrgentDeferOrder(TUrgentDeferOrder *pUrgentDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ�Ӧ������Ӧ��
  	*/
  	virtual void onRecvRspUrgentFuturesOrder(TUrgentFuturesOrder *pUrgentFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+NӦ������Ӧ��
  	*/
  	virtual void onRecvRspUrgentForwardOrder(TUrgentForwardOrder *pUrgentForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�Ӧ��������ѯӦ��
  	*/
  	virtual void onRecvRspQryUrgentSpotOrder(TUrgentSpotOrder *pUrgentSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ���Ӧ��������ѯӦ��
  	*/
  	virtual void onRecvRspQryUrgentDeferOrder(TUrgentDeferOrder *pUrgentDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ�Ӧ��������ѯӦ��
  	*/
  	virtual void onRecvRspQryUrgentFuturesOrder(TUrgentFuturesOrder *pUrgentFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+NӦ��������ѯӦ��
  	*/
  	virtual void onRecvRspQryUrgentForwardOrder(TUrgentForwardOrder *pUrgentForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�Ӧ����������Ӧ��
  	*/
  	virtual void onRecvRspChkUrgentSpotOrder(TUrgentSpotOrder *pUrgentSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ���Ӧ����������Ӧ��
  	*/
  	virtual void onRecvRspChkUrgentDeferOrder(TUrgentDeferOrder *pUrgentDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ�Ӧ����������Ӧ��
  	*/
  	virtual void onRecvRspChkUrgentFuturesOrder(TUrgentFuturesOrder *pUrgentFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�T+NӦ����������Ӧ��
  	*/
  	virtual void onRecvRspChkUrgentForwardOrder(TUrgentForwardOrder *pUrgentForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ���ǿ��ƽ�ֱ���Ӧ��
  	*/
  	virtual void onRecvRspForceDeferOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ�ǿ��ƽ�ֱ���Ӧ��
  	*/
  	virtual void onRecvRspForceFuturesOrder(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ�ǿ��ƽ�ֳ���Ӧ��
  	*/
  	virtual void onRecvRspForceFuturesOrderCancel(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ����ڽ���ǿ��ƽ�ֳ���Ӧ��
  	*/
  	virtual void onRecvRspForceDeferOrderCancel(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**��Ա���ֲ�ѯ��Ӧ
  	*/
  	virtual void onRecvRspQryMemberPosiOver(TRspQryMemberPosiOver *pRspQryMemberPosiOver,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ͻ����ֲ�ѯ��Ӧ
  	*/
  	virtual void onRecvRspQryClientPosiOver(TRspQryClientPosiOver *pRspQryClientPosiOver,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ʽ����ѯ��Ӧ
  	*/
  	virtual void onRecvRspQryCapitalLack(TRspQryCapitalLack *pRspQryCapitalLack,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ�ǿƽ�ɽ�����ѯӦ��
  	*/
  	virtual void onRecvRspQryForceFuturesMatch(TFuturesMatch *pFuturesMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**����ǿƽ�ɽ�����ѯӦ��
  	*/
  	virtual void onRecvRspQryForceDeferMatch(TDeferMatch *pDeferMatch,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**������������Ӧ��
  	*/
  	virtual void onRecvRspInterQuotation(TInterQuotation *pInterQuotation,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**ǿ�ƽ���Ա�˳�Ӧ��
  	*/
  	virtual void onRecvRspForceTraderLogout(TReqForceTraderLogout *pReqForceTraderLogout,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ֻ�Ӧ����������Ӧ��
  	*/
  	virtual void onRecvRspUrgentSpotOrderCancel(TUrgentSpotOrderCancel *pUrgentSpotOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**����Ӧ����������Ӧ��
  	*/
  	virtual void onRecvRspUrgentDeferOrderCancel(TUrgentDeferOrderCancel *pUrgentDeferOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**�ڻ�Ӧ����������Ӧ��
  	*/
  	virtual void onRecvRspUrgentFuturesOrderCancel(TUrgentFuturesOrderCancel *pUrgentFuturesOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**Զ��Ӧ����������Ӧ��
  	*/
  	virtual void onRecvRspUrgentForwardOrderCancel(TUrgentForwardOrderCancel *pUrgentForwardOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
   	/**״̬ģʽ��Ӧ
  	*/
  	virtual void onRecvRspStateMode(TStateMode *pStateMode,TTRspMsg *pRspMsg,char *RootID=NULL){}
	/**�ֻ����ر����Ų�ѯӦ��
  	*/
   	virtual void onRecvRspQrySpotLocalOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}		
   	/**�ֻ����ڽ��ձ��ر����Ų�ѯӦ��
  	*/
   	virtual void onRecvRspQryDeferLocalOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}	
	/**�ֻ�T+N���ر����Ų�ѯӦ��
  	*/
   	virtual void onRecvRspQryForwardLocalOrder(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL){}
	/**�ֻ�����ǿ��Ӧ��
  	*/
   	virtual void onRecvRspSpotOrderForceCancel(TSpotOrderCancel *pSpotOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
	/**���ӱ���ǿ��Ӧ��
  	*/
   	virtual void onRecvRspDeferOrderForceCancel(TDeferOrderCancel *pSpotOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
	/**T+N����ǿ��Ӧ��
  	*/
   	virtual void onRecvRspForwardOrderForceCancel(TForwardOrderCancel *pSpotOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL){}
	/**��Ա�ʽ���ǿƽ��������Ӧ��
  	*/
   	virtual void onRecvRspCalcMemberOffsetAmount(TReqQryCapitalLack *pQryCapitalLack,TTRspMsg *pRspMsg,char *RootID=NULL){}

	/**��ȡ�汾��
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
	static const char *m_pVersionInfo;	/**< �汾��Ϣ **/
};
#endif
