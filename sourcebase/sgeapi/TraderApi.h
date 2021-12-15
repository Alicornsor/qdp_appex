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
	
	/**��ʼ��
	* @return 0��ʾ�ɹ���-1��ʾʧ��
	*/
	int init(void);
	
	/**����ǰ�û���IP�Ͷ˿�
	* @param sIp ǰ�û���IP
	* @param nPort ǰ�û��Ķ˿�
	*/
	void SetService(char *sIp, int nPort);
	
	/**��ȡ��ǰ�Ľ�������
	* @param tradeDate ������������ص�ǰ�Ľ�������
	*/
	void GetTradeDate(TDate &tradeDate);
	
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
	
	/**����IC���Ŀ���Ͷ�ȡ��ʽ
	* @param passwd IC���Ŀ���
	* @param inputType ��ȡ��ʽ 0���ļ���ȡ��1��IC����ȡ
	* @param comID ���ں�
	*/
	void SetIcCardPwd(const char *passwd,short inputType,short comID);
	
	/**�ı��ȡ����
	* @param userID ����ԱID
	* @param oldpassword �ɵĿ���
	* @param newpassword �¿���
	* @param inputType 0���ļ���ȡ��1��IC����ȡ
	*/
	int  ChgICPasswd(TTraderID &traderID,const char *oldpassword, const char *newpassword,short inputType);
	
	
	/**����Ա��¼����
	* @param pReqTraderLogin �������������Ա��¼������Ϣ
	* @param RootID  ����������������Ψһ��ʾ
	* @return 0 : �ɹ� 
	*         -1:����ǰ��ʧ��
	*         -2:�ظ���¼
	*         -3:������֤����ʧ��
	*/
	int ReqTraderLogin(TReqTraderLogin *pReqTraderLogin,char *RootID=NULL);
   	/**����Ա��¼Ӧ��
   	* @param pReqTraderLogin �������������Ա��¼������Ϣ
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspTraderLogin(TReqTraderLogin *pReqTraderLogin,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**����Ա�˳�����
   	* @param pReqTraderLogout �������������Ա�˳�������Ϣ
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqTraderLogout( TReqTraderLogout *pReqTraderLogout,char *RootID=NULL);
   	/**����Ա�˳�Ӧ��
   	* @param pReqTraderLogout �������������Ա�˳�������Ϣ
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspTraderLogout(TReqTraderLogout *pReqTraderLogout,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ���������
   	* @param pSpotOrder ����������ֻ�������Ϣ
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqSpotOrder( TSpotOrder *pSpotOrder,char *RootID=NULL);
   	/**�ֻ���������(V2)
   	* @param pSpotOrder ����������ֻ�������Ϣ
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqSpotOrderEx( TSpotOrderEx *pSpotOrder,char *RootID=NULL);
   	/**�ֻ�����Ӧ��
   	* @param pSpotOrder ����������ֻ�������Ϣ
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspSpotOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ���������
   	* @param pSpotOrderCancel ����������ֻ���������
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqSpotOrderCancel( TSpotOrderCancel *pSpotOrderCancel,char *RootID=NULL);
   	/**�ֻ�����Ӧ��
   	* @param pSpotOrderCancel ����������ֻ���������
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspSpotOrderCancel(TSpotOrderCancel *pSpotOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ����ڽ��ձ�������
   	* @param pDeferOrder ����������ֻ����ڽ��ձ���
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqDeferOrder( TDeferOrder *pDeferOrder,char *RootID=NULL);
   	/**�ֻ����ڽ��ձ�������(V2)
   	* @param pDeferOrder ����������ֻ����ڽ��ձ���
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqDeferOrderEx( TDeferOrderEx *pDeferOrder,char *RootID=NULL);
   	/**�ֻ����ڽ��ձ���Ӧ��
   	* @param pDeferOrder ����������ֻ����ڽ��ձ���
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspDeferOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ����ڽ��ճ�������
   	* @param pDeferOrderCancel ����������ֻ����ڽ��ճ�������
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqDeferOrderCancel( TDeferOrderCancel *pDeferOrderCancel,char *RootID=NULL);
   	/**�ֻ����ڽ��ճ���Ӧ��
   	* @param pDeferOrderCancel ����������ֻ����ڽ��ճ�������
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspDeferOrderCancel(TDeferOrderCancel *pDeferOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**�ֻ������ر�
   	* @param pSpotOrder ����������ֻ�������Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnSpotOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ����ڽ��ձ����ر�
   	* @param pDeferOrder ����������ֻ����ڽ��ձ���
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnDeferOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ������ر�
   	* @param pSpotOrder ����������ֻ�������Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnSpotOrderCancel(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ����ڽ��ճ����ر�
   	* @param pDeferOrder ����������ֻ����ڽ��ձ���
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnDeferOrderCancel(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**�ֻ����ڽ��ս����걨����
   	* @param pDeferDeliveryAppOrder ����������ֻ����ڽ��ս����걨����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqDeferDeliveryAppOrder( TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,char *RootID=NULL);
   	/**�ֻ����ڽ��ս����걨Ӧ��
   	* @param pDeferDeliveryAppOrder ����������ֻ����ڽ��ս����걨����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspDeferDeliveryAppOrder(TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ����ڽ��ս����걨��������
   	* @param pDeferDeliveryAppOrderCancel ����������ֻ����ڽ��ս����걨��������
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqDeferDeliveryAppOrderCancel( TDeferDeliveryAppOrderCancel *pDeferDeliveryAppOrderCancel,char *RootID=NULL);
   	/**�ֻ����ڽ��ս����걨����Ӧ��
   	* @param pDeferDeliveryAppOrderCancel ����������ֻ����ڽ��ս����걨��������
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspDeferDeliveryAppOrderCancel(TDeferDeliveryAppOrderCancel *pDeferDeliveryAppOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ����ڽ����������걨����
   	* @param pMiddleAppOrder ����������ֻ����ڽ����������걨����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqMiddleAppOrder( TMiddleAppOrder *pMiddleAppOrder,char *RootID=NULL);
   	/**�ֻ����ڽ����������걨Ӧ��
   	* @param pMiddleAppOrder ����������ֻ����ڽ����������걨����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspMiddleAppOrder(TMiddleAppOrder *pMiddleAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ����ڽ����������걨��������
   	* @param pMiddleAppOrderCancel ����������ֻ����ڽ����������걨��������
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqMiddleAppOrderCancel( TMiddleAppOrderCancel *pMiddleAppOrderCancel,char *RootID=NULL);
   	/**�ֻ����ڽ����������걨����Ӧ��
   	* @param pMiddleAppOrderCancel ����������ֻ����ڽ����������걨��������
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspMiddleAppOrderCancel(TMiddleAppOrderCancel *pMiddleAppOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**�ֻ����ڽ��ս����걨�ر�
   	* @param pDeferDeliveryAppOrder ����������ֻ����ڽ��ս����걨����
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnDeferDeliveryAppOrder(TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ����ڽ����������걨�ر�
   	* @param pMiddleAppOrder ����������ֻ����ڽ����������걨����
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnMiddleAppOrder(TMiddleAppOrder *pMiddleAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ����ڽ��ս����걨�����ر�
   	* @param pDeferDeliveryAppOrder ����������ֻ����ڽ��ս����걨����
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnDeferDeliveryAppOrderCancel(TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ����ڽ����������걨�����ر�
   	* @param pMiddleAppOrder ����������ֻ����ڽ����������걨����
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnMiddleAppOrderCancel(TMiddleAppOrder *pMiddleAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**�ڻ���������
   	* @param pFuturesOrder ����������ڻ�����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqFuturesOrder( TFuturesOrder *pFuturesOrder,char *RootID=NULL);
   	/**�ڻ�����Ӧ��
   	* @param pFuturesOrder ����������ڻ�����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspFuturesOrder(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ڻ���������
   	* @param pFuturesOrderCancel ����������ڻ���������
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqFuturesOrderCancel( TFuturesOrderCancel *pFuturesOrderCancel,char *RootID=NULL);
   	/**�ڻ�����Ӧ��
   	* @param pFuturesOrderCancel ����������ڻ���������
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspFuturesOrderCancel(TFuturesOrderCancel *pFuturesOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ�T+N��������
   	* @param pForwardOrder ����������ֻ�T+N����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqForwardOrder( TForwardOrder *pForwardOrder,char *RootID=NULL);
   	/**�ֻ�T+N��������(V2)
   	* @param pForwardOrder ����������ֻ�T+N����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqForwardOrderEx( TForwardOrderEx *pForwardOrder,char *RootID=NULL);
   	/**�ֻ�T+N����Ӧ��
   	* @param pForwardOrder ����������ֻ�T+N����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspForwardOrder(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ�T+N��������
   	* @param pForwardOrderCancel ����������ֻ�T+N��������
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqForwardOrderCancel( TForwardOrderCancel *pForwardOrderCancel,char *RootID=NULL);
   	/**�ֻ�T+N����Ӧ��
   	* @param pForwardOrderCancel ����������ֻ�T+N��������
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspForwardOrderCancel(TForwardOrderCancel *pForwardOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ�T+N����ת�ñ�������
   	* @param pSpotOrder ����������ֻ�������Ϣ
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqForwardEndorseOrder( TSpotOrder *pSpotOrder,char *RootID=NULL);
   	/**�ֻ�T+N����ת�ñ���Ӧ��
   	* @param pSpotOrder ����������ֻ�������Ϣ
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspForwardEndorseOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ�T+N����ת�ó�������
   	* @param pForwardEndorseOrderCancel ����������ֻ�T+N����ת�ó�������
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqForwardEndorseOrderCancel( TForwardEndorseOrderCancel *pForwardEndorseOrderCancel,char *RootID=NULL);
   	/**�ֻ�T+N����ת�ó���Ӧ��
   	* @param pForwardEndorseOrderCancel ����������ֻ�T+N����ת�ó�������
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspForwardEndorseOrderCancel(TForwardEndorseOrderCancel *pForwardEndorseOrderCancel,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**�ڻ������ر�
   	* @param pFuturesOrder ����������ڻ�����
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnFuturesOrder(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ�T+N�����ر�
   	* @param pForwardOrder ����������ֻ�T+N����
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnForwardOrder(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ڻ������ر�
   	* @param pFuturesOrder ����������ڻ�����
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnFuturesOrderCancel(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ�T+N�����ر�
   	* @param pForwardOrder ����������ֻ�T+N����
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnForwardOrderCancel(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ�T+N����ת�ñ����ر�
   	* @param pSpotOrder ����������ֻ�������Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnForwardEndorseOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ�T+N����ת�ó����ر�
   	* @param pSpotOrder ����������ֻ�������Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnForwardEndorseOrderCancel(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**����Ա�����޸�����
   	* @param pReqTraderPasswordUpdate �������������Ա�����޸�����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqTraderPasswordUpdate( TReqTraderPasswordUpdate *pReqTraderPasswordUpdate,char *RootID=NULL);
   	/**����Ա�����޸�Ӧ��
   	* @param pReqTraderPasswordUpdate �������������Ա�����޸�����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspTraderPasswordUpdate(TReqTraderPasswordUpdate *pReqTraderPasswordUpdate,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**��ԱӦ�������޸�����
   	* @param pReqMemberUrgentPasswordUpdate �����������ԱӦ�������޸�����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqMemberUrgentPasswordUpdate( TReqMemberUrgentPasswordUpdate *pReqMemberUrgentPasswordUpdate,char *RootID=NULL);
   	/**��ԱӦ�������޸�Ӧ��
   	* @param pReqMemberUrgentPasswordUpdate �����������ԱӦ�������޸�����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspMemberUrgentPasswordUpdate(TReqMemberUrgentPasswordUpdate *pReqMemberUrgentPasswordUpdate,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**��Ա�ʽ��ѯ����
   	* @param pReqQryMemberCapital �����������Ա�ʽ��ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
	int ReqQryMemberCapital( TReqQryMemberCapital *pReqQryMemberCapital,char *RootID=NULL);

   	/**��Ա�ʽ��ѯӦ��
   	* @param pMemberCapital �����������Ա�ʽ�
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
	virtual void onRecvRspQryMemberCapital(TMemberCapital *pMemberCapital,TTRspMsg *pRspMsg,char *RootID=NULL) {}

	// Added by qingquan.xue 20140310 begin
	/**��Ա�ʽ��ѯ���󣨳�֣�
   	* @param pReqQryMemberCapital �����������Ա�ʽ��ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
	int ReqQryMemberCapitalEx( TReqQryMemberCapital *pReqQryMemberCapital,char *RootID=NULL);

	/**��Ա�ʽ��ѯӦ�𣨳�֣�
   	* @param pMemberCapital �����������Ա�ʽ�
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
	virtual void onRecvRspQryMemberCapitalEx(TMemberCapitalEx *pMemberCapital,TTRspMsg *pRspMsg,char *RootID=NULL) {}
	// Added by qingquan.xue 20140310 end

   	/**�ͻ�����ѯ����
   	* @param pReqQryClientStorage ����������ͻ�����ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
	int ReqQryClientStorage( TReqQryClientStorage *pReqQryClientStorage,char *RootID=NULL);
	
   	/**�ͻ�����ѯӦ��
   	* @param pClientStorage ����������ͻ����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryClientStorage(TClientStorage *pClientStorage,TTRspMsg *pRspMsg,char *RootID=NULL) {}

	// Added by qingquan.xue 20140310 begin
	/**�ͻ�����ѯ���󣨳�֣�
   	* @param pReqQryClientStorage ����������ͻ�����ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
	int ReqQryClientStorageEx( TReqQryClientStorage *pReqQryClientStorage,char *RootID=NULL);

	/**�ͻ�����ѯӦ�𣨳�֣�
   	* @param pClientStorage ����������ͻ����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
	virtual void onRecvRspQryClientStorageEx(TClientStorageEx *pClientStorage,TTRspMsg *pRspMsg,char *RootID=NULL) {}
	// Added by qingquan.xue 20140310 end

   	/**�ֻ�������ѯ����
   	* @param pReqQryOrder ���������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQrySpotOrder( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**�ֻ�������ѯӦ��
   	* @param pSpotOrder ����������ֻ�������Ϣ
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQrySpotOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
    /**�ֻ�������ѯ����(V2)
   	* @param pReqQryOrder ���������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQrySpotOrderEx( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**�ֻ�������ѯӦ��(V2)
   	* @param pSpotOrder ����������ֻ�������Ϣ
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQrySpotOrderEx(TSpotOrderEx *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**�ֻ����ڽ��ձ�����ѯ����
   	* @param pReqQryOrder ���������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryDeferOrder( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**�ֻ����ڽ��ձ�����ѯӦ��
   	* @param pDeferOrder ����������ֻ����ڽ��ձ���
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryDeferOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**�ֻ����ڽ��ձ�����ѯ����(V2)
   	* @param pReqQryOrder ���������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryDeferOrderEx( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**�ֻ����ڽ��ձ�����ѯӦ��(V2)
   	* @param pDeferOrder ����������ֻ����ڽ��ձ���
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryDeferOrderEx(TDeferOrderEx *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ����ڽ��ս����걨������ѯ����
   	* @param pReqQryOrder ���������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryDeferDeliveryAppOrder( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**�ֻ����ڽ��ս����걨������ѯӦ��
   	* @param pDeferDeliveryAppOrder ����������ֻ����ڽ��ս����걨����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryDeferDeliveryAppOrder(TDeferDeliveryAppOrder *pDeferDeliveryAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ����ڽ����������걨������ѯ����
   	* @param pReqQryOrder ���������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryMiddleAppOrder( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**�ֻ����ڽ����������걨������ѯӦ��
   	* @param pMiddleAppOrder ����������ֻ����ڽ����������걨����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryMiddleAppOrder(TMiddleAppOrder *pMiddleAppOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ڻ�������ѯ����
   	* @param pReqQryOrder ���������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryFuturesOrder( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**�ڻ�������ѯӦ��
   	* @param pFuturesOrder ����������ڻ�����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryFuturesOrder(TFuturesOrder *pFuturesOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ�T+N������ѯ����
   	* @param pReqQryOrder ���������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryForwardOrder( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**�ֻ�T+N������ѯӦ��
   	* @param pForwardOrder ����������ֻ�T+N����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryForwardOrder(TForwardOrder *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ�T+N������ѯ����(V2)
   	* @param pReqQryOrder ���������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryForwardOrderEx( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**�ֻ�T+N������ѯӦ��(V2)
   	* @param pForwardOrder ����������ֻ�T+N����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryForwardOrderEx(TForwardOrderEx *pForwardOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ�T+N����ת�ñ�����ѯ����
   	* @param pReqQryOrder ���������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryForwardEndorseOrder( TReqQryOrder *pReqQryOrder,char *RootID=NULL);
   	/**�ֻ�T+N����ת�ñ�����ѯӦ��
   	* @param pSpotOrder ����������ֻ�������Ϣ
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryForwardEndorseOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ��ɽ�����ѯ����
   	* @param pReqQryMatch ����������ɽ���ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQrySpotMatch( TReqQryMatch *pReqQryMatch,char *RootID=NULL);
   	/**�ֻ��ɽ�����ѯӦ��
   	* @param pSpotMatch ����������ֻ��ɽ�����Ϣ
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQrySpotMatch(TSpotMatch *pSpotMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ����ڽ��ճɽ�����ѯ����
   	* @param pReqQryMatch ����������ɽ���ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryDeferMatch( TReqQryMatch *pReqQryMatch,char *RootID=NULL);
   	/**�ֻ����ڽ��ճɽ�����ѯӦ��
   	* @param pDeferMatch ����������ֻ����ڽ��ճɽ���
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryDeferMatch(TDeferMatch *pDeferMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ����ڽ��ս����걨�ɽ�����ѯ����
   	* @param pReqQryMatch ����������ɽ���ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryDeferDeliveryAppMatch( TReqQryMatch *pReqQryMatch,char *RootID=NULL);
   	/**�ֻ����ڽ��ս����걨�ɽ�����ѯӦ��
   	* @param pDeferDeliveryAppMatch ������������ӽ����걨�ɽ���
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryDeferDeliveryAppMatch(TDeferDeliveryAppMatch *pDeferDeliveryAppMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ڻ��ɽ�����ѯ����
   	* @param pReqQryMatch ����������ɽ���ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryFuturesMatch( TReqQryMatch *pReqQryMatch,char *RootID=NULL);
   	/**�ڻ��ɽ�����ѯӦ��
   	* @param pFuturesMatch ����������ڻ��ɽ���
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryFuturesMatch(TFuturesMatch *pFuturesMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ�T+N�ɽ�����ѯ����
   	* @param pReqQryMatch ����������ɽ���ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryForwardMatch( TReqQryMatch *pReqQryMatch,char *RootID=NULL);
   	/**�ֻ�T+N�ɽ�����ѯӦ��
   	* @param pForwardMatch ����������ֻ�T+N�ɽ���
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryForwardMatch(TForwardMatch *pForwardMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ�T+N����ת�óɽ�����ѯ����
   	* @param pReqQryMatch ����������ɽ���ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryForwardEndorseMatch( TReqQryMatch *pReqQryMatch,char *RootID=NULL);
   	/**�ֻ�T+N����ת�óɽ�����ѯӦ��
   	* @param pSpotMatch ����������ֻ��ɽ�����Ϣ
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryForwardEndorseMatch(TSpotMatch *pSpotMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**�ֻ��ɽ��ر�
   	* @param pSpotMatch ����������ֻ��ɽ�����Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnSpotMatch(TSpotMatch *pSpotMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ����ڽ��ճɽ��ر�
   	* @param pDeferMatch ����������ֻ����ڽ��ճɽ���
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnDeferMatch(TDeferMatch *pDeferMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ����ڽ��ս����걨�ɽ��ر�
   	* @param pDeferDeliveryAppMatch ������������ӽ����걨�ɽ���
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnDeferDeliveryAppMatch(TDeferDeliveryAppMatch *pDeferDeliveryAppMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ڻ��ɽ��ر�
   	* @param pFuturesMatch ����������ڻ��ɽ���
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnFuturesMatch(TFuturesMatch *pFuturesMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ�T+N�ɽ��ر�
   	* @param pForwardMatch ����������ֻ�T+N�ɽ���
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnForwardMatch(TForwardMatch *pForwardMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ�T+N����ת�óɽ��ر�
   	* @param pSpotMatch ����������ֻ��ɽ�����Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnForwardEndorseMatch(TSpotMatch *pSpotMatch,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**��Ա�ֻ����ڽ��ճֲֲ�ѯ����
   	* @param pReqQryMemberPosi �����������Ա�ֲֲ�ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryDeferMemberPosi( TReqQryMemberPosi *pReqQryMemberPosi,char *RootID=NULL);
   	/**��Ա�ֻ����ڽ��ճֲֲ�ѯӦ��
   	* @param pDeferMemberPosi �����������Ա�ֻ����ڽ��ճֲ�
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryDeferMemberPosi(TDeferMemberPosi *pDeferMemberPosi,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**��Ա�ڻ��ֲֲ�ѯ����
   	* @param pReqQryMemberPosi �����������Ա�ֲֲ�ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryFuturesMemberPosi( TReqQryMemberPosi *pReqQryMemberPosi,char *RootID=NULL);
   	/**��Ա�ڻ��ֲֲ�ѯӦ��
   	* @param pFuturesMemberPosi �����������Ա�ڻ��ֲ�
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryFuturesMemberPosi(TFuturesMemberPosi *pFuturesMemberPosi,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**��Ա�ֻ�T+N�ֲֲ�ѯ����
   	* @param pReqQryMemberPosi �����������Ա�ֲֲ�ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryForwardMemberPosi( TReqQryMemberPosi *pReqQryMemberPosi,char *RootID=NULL);
   	/**��Ա�ֻ�T+N�ֲֲ�ѯӦ��
   	* @param pForwardMemberPosi �����������Ա�ֻ�T+N�ֲ�
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryForwardMemberPosi(TForwardMemberPosi *pForwardMemberPosi,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ͻ��ֻ����ڽ��ճֲֲ�ѯ����
   	* @param pReqQryClientPosi ����������ͻ��ֲֲ�ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryDeferClientPosi( TReqQryClientPosi *pReqQryClientPosi,char *RootID=NULL);
   	/**�ͻ��ֻ����ڽ��ճֲֲ�ѯӦ��
   	* @param pDeferClientPosi ����������ͻ��ֻ����ڽ��ճֲ�
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryDeferClientPosi(TDeferClientPosi *pDeferClientPosi,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ͻ��ڻ��ֲֲ�ѯ����
   	* @param pReqQryClientPosi ����������ͻ��ֲֲ�ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryFuturesClientPosi( TReqQryClientPosi *pReqQryClientPosi,char *RootID=NULL);
   	/**�ͻ��ڻ��ֲֲ�ѯӦ��
   	* @param pFuturesClientPosi ����������ͻ��ڻ��ֲ�
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryFuturesClientPosi(TFuturesClientPosi *pFuturesClientPosi,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ͻ��ֻ�T+N�ֲֲ�ѯ����
   	* @param pReqQryClientPosi ����������ͻ��ֲֲ�ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryForwardClientPosi( TReqQryClientPosi *pReqQryClientPosi,char *RootID=NULL);
   	/**�ͻ��ֻ�T+N�ֲֲ�ѯӦ��
   	* @param pForwardClientPosi ����������ͻ��ֻ�T+N�ֲ�
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryForwardClientPosi(TForwardClientPosi *pForwardClientPosi,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ������ѯ����
   	* @param pReqQryQuotation ��������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQrySpotQuotation( TReqQryQuotation *pReqQryQuotation,char *RootID=NULL);
   	/**�ֻ������ѯӦ��
   	* @param pSpotQuotation ����������ֻ�����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQrySpotQuotation(TSpotQuotation *pSpotQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ����ڽ��������ѯ����
   	* @param pReqQryQuotation ��������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryDeferQuotation( TReqQryQuotation *pReqQryQuotation,char *RootID=NULL);
   	/**�ֻ����ڽ��������ѯӦ��
   	* @param pDeferQuotation ����������ֻ����ڽ�������
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryDeferQuotation(TDeferQuotation *pDeferQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ڻ������ѯ����
   	* @param pReqQryQuotation ��������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryFuturesQuotation( TReqQryQuotation *pReqQryQuotation,char *RootID=NULL);
   	/**�ڻ������ѯӦ��
   	* @param pFuturesQuotation ����������ڻ�����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryFuturesQuotation(TFuturesQuotation *pFuturesQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ�T+N�����ѯ����
   	* @param pReqQryQuotation ��������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryForwardQuotation( TReqQryQuotation *pReqQryQuotation,char *RootID=NULL);
   	/**�ֻ�T+N�����ѯӦ��
   	* @param pForwardQuotation ����������ֻ�T+N����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryForwardQuotation(TForwardQuotation *pForwardQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**�г���Ϣ�ر�
   	* @param pMarket ����������г���
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvMarketInfo(TMarket *pMarket,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ���Լ��Ϣ�ر�
   	* @param pSpotInst ����������ֻ���Լ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvSpotInstInfo(TSpotInst *pSpotInst,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**���Ӻ�Լ��Ϣ�ر�
   	* @param pDeferInst ����������ֻ����ڽ��պ�Լ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvDeferInstInfo(TDeferInst *pDeferInst,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ڻ���Լ��Ϣ�ر�
   	* @param pFuturesInst ����������ڻ���Լ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvFuturesInstInfo(TFuturesInst *pFuturesInst,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**Զ�ں�Լ��Ϣ�ر�
   	* @param pForwardInst ����������ֻ�T+N��Լ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvForwardInstInfo(TForwardInst *pForwardInst,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**���ӷ��ʲ�ѯ����
   	* @param pReqQryDeferFeeRate ������������ӷ��ʲ�ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryDeferFeeRate( TReqQryDeferFeeRate *pReqQryDeferFeeRate,char *RootID=NULL);
   	/**���ӷ��ʲ�ѯ����Ӧ��
   	* @param pDeferFeeRate ����������ֻ����ڽ��ղ���������Ϣ
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryDeferFeeRate(TDeferFeeRate *pDeferFeeRate,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**�ֻ���Լ����״̬�ı�ر�
   	* @param pInstState �����������Լ����״̬��Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnSpotInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ��г�����״̬�ı�ر�
   	* @param pMarketState ����������г�����״̬��Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnSpotMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**���Ӻ�Լ����״̬�ı�ر�
   	* @param pInstState �����������Լ����״̬��Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnDeferInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�����г�����״̬�ı�ر�
   	* @param pMarketState ����������г�����״̬��Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnDeferMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ڻ���Լ����״̬�ı�ر�
   	* @param pInstState �����������Լ����״̬��Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnFuturesInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ڻ��г�����״̬�ı�ر�
   	* @param pMarketState ����������г�����״̬��Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnFuturesMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**Զ�ں�Լ����״̬�ı�ر�
   	* @param pInstState �����������Լ����״̬��Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnForwardInstStateUpdate(TInstState *pInstState,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**Զ���г�����״̬�ı�ر�
   	* @param pMarketState ����������г�����״̬��Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnForwardMarketStateUpdate(TMarketState *pMarketState,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**�����������ѯ����
   	* @param pReqQryBulletinBoard ���������������������Ϣ��ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryBulletinBoard( TReqQryBulletinBoard *pReqQryBulletinBoard,char *RootID=NULL);
   	/**�����������ѯ����Ӧ��
   	* @param pBulletinBoard ���������������������Ϣ
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryBulletinBoard(TBulletinBoard *pBulletinBoard,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**����ر�
   	* @param pBulletinBoard ���������������������Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnBulletinBoard(TBulletinBoard *pBulletinBoard,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**��������ر�
   	* @param pInterQuotation �������������������Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvRtnInterQuotation(TInterQuotation *pInterQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**���������ѯ����
   	* @param pInterQuotation �������������������Ϣ
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryInterQuotation( TInterQuotation *pInterQuotation,char *RootID=NULL);
   	/**���������ѯ����Ӧ��
   	* @param pInterQuotation �������������������Ϣ
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryInterQuotation(TInterQuotation *pInterQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**�ֻ�����
   	* @param pSpotQuotation ����������ֻ�����
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvSpotQuotation(TSpotQuotation *pSpotQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ����ڽ�������
   	* @param pDeferQuotation ����������ֻ����ڽ�������
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvDeferQuotation(TDeferQuotation *pDeferQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ڻ�����
   	* @param pFuturesQuotation ����������ڻ�����
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvFuturesQuotation(TFuturesQuotation *pFuturesQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�ֻ�T+N����
   	* @param pForwardQuotation ����������ֻ�T+N����
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvForwardQuotation(TForwardQuotation *pForwardQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�����ֻ���������
   	* @param pMinsSpotQuotation ��������������ֻ���������
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvMinsSpotQuotation(TMinsSpotQuotation *pMinsSpotQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**�����ڻ���������
   	* @param pMinsFuturesQuotation ����������ڻ���������
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvMinsFuturesQuotation(TMinsFuturesQuotation *pMinsFuturesQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**����Զ�ڷ�������
   	* @param pMinsForwardQuotation ���������Զ�ڷ�������
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvMinsForwardQuotation(TMinsForwardQuotation *pMinsForwardQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**������ӷ�������
   	* @param pMinsDeferQuotation ������������ӷ�������
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvMinsDeferQuotation(TMinsDeferQuotation *pMinsDeferQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**�ֻ����������ѯ����
   	* @param pReqQryMinsQuotation ���������������Ӳ�ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQrySpotMinsQuotation( TReqQryMinsQuotation *pReqQryMinsQuotation,char *RootID=NULL);
   	/**�ֻ����������ѯӦ��
   	* @param pMinsSpotQuotation ��������������ֻ���������
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQrySpotMinsQuotation(TMinsSpotQuotation *pMinsSpotQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ����ڽ��շ��������ѯ����
   	* @param pReqQryMinsQuotation ���������������Ӳ�ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryDeferMinsQuotation( TReqQryMinsQuotation *pReqQryMinsQuotation,char *RootID=NULL);
   	/**�ֻ����ڽ��շ��������ѯӦ��
   	* @param pMinsDeferQuotation ������������ӷ�������
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryDeferMinsQuotation(TMinsDeferQuotation *pMinsDeferQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ڻ����������ѯ����
   	* @param pReqQryMinsQuotation ���������������Ӳ�ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryFuturesMinsQuotation( TReqQryMinsQuotation *pReqQryMinsQuotation,char *RootID=NULL);
   	/**�ڻ����������ѯӦ��
   	* @param pMinsFuturesQuotation ����������ڻ���������
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryFuturesMinsQuotation(TMinsFuturesQuotation *pMinsFuturesQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ�T+N���������ѯ����
   	* @param pReqQryMinsQuotation ���������������Ӳ�ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryForwardMinsQuotation( TReqQryMinsQuotation *pReqQryMinsQuotation,char *RootID=NULL);
   	/**�ֻ�T+N���������ѯӦ��
   	* @param pMinsForwardQuotation ���������Զ�ڷ�������
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryForwardMinsQuotation(TMinsForwardQuotation *pMinsForwardQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**�����ֻ����ڽ��ղ�������֪ͨ
   	* @param pDeferFeeRate ����������ֻ����ڽ��ղ���������Ϣ
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvDeferFeeRateUpdate(TDeferFeeRate *pDeferFeeRate,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
   	/**��Ա�ͻ���ѯ����
   	* @param pReqQryClient �����������Ա�ͻ���ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryClient( TReqQryClient *pReqQryClient,char *RootID=NULL);
   	/**��Ա�ͻ���ѯ��Ӧ
   	* @param pClient ����������ͻ���Ϣ
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryClient(TClient *pClient,TTRspMsg *pRspMsg,char *RootID=NULL) {}
  	/**���ӽ�������
   	* @param pDeferDeliveryQuotation ������������ӽ�������
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvDeferDeliveryQuotation(TDeferDeliveryQuotation *pDeferDeliveryQuotation,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
  	/**����Ʒ�ִ�����Ϣ
   	* @param pVariety �������������Ʒ�ִ���
   	* @param pRspMsg �����������������־
   	* @param RootID  ������δʹ��
  	*/
  	virtual void  onRecvVarietyInfo(TVariety *pVariety,TTRspMsg *pRspMsg,char *RootID=NULL) {}	
	/**�ֻ����ر����Ų�ѯ����
   	* @param pReqQryOrder ���������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQrySpotLocalOrder( TReqQryLocalOrder *pReqQryLocalOrder,char *RootID=NULL);
   	/**�ֻ����ر����Ų�ѯӦ��
   	* @param pSpotOrder ����������ֻ�������Ϣ
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQrySpotLocalOrder(TSpotOrder *pSpotOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
   	/**�ֻ����ڽ��ձ��ر����Ų�ѯ����
   	* @param pReqQryOrder ���������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryDeferLocalOrder( TReqQryLocalOrder *pReqQryLocalOrder,char *RootID=NULL);
   	/**�ֻ����ڽ��ձ��ر����Ų�ѯӦ��
   	* @param pDeferOrder ����������ֻ����ڽ��ձ���
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
  	*/
   	virtual void onRecvRspQryDeferLocalOrder(TDeferOrder *pDeferOrder,TTRspMsg *pRspMsg,char *RootID=NULL) {}
	/**�ֻ�T+N���ر����Ų�ѯ����
   	* @param pReqQryOrder ���������������ѯ����
   	* @param RootID  ����������������Ψһ��ʾ
   	* @return 0 : �ɹ� 
	*         -1: ����ʧ��
  	*/
  	int ReqQryForwardLocalOrder( TReqQryLocalOrder *pReqQryLocalOrder,char *RootID=NULL);
   	/**�ֻ�T+N���ر����Ų�ѯӦ��
   	* @param pForwardOrder ����������ֻ�T+N����
   	* @param pRspMsg �������������ִ�н������������־
   	* @param RootID  ������������������Ӧ��Ψһ��ʾ
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
