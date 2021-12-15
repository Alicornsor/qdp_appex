!!let exchangeid=""!!
!!let functionid=""!!
!!let macroid=""!!
!!let fileid=""!!
!!enter exchangeinfo!!
!!travel self!!
!!if @pumpid==0!!
!!let exchangeid=@name!!
!!elseif @pumpid==1!!
!!let functionid=@name!!
!!elseif @pumpid==2!!
!!let macroid=@name!!
!!elseif @pumpid==3!!
!!let fileid=@name!!
!!endif!!
!!next!!
!!leave!!
/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company QuantDo
///@file !!@fileid!!FtdcUserApi.h
///@brief �����˿ͻ��˽ӿ�
///@history 
///20150520	���һ�	�������ļ�
/////////////////////////////////////////////////////////////////////////

#if !defined(!!@macroid!!_FTDCUSERAPI_H)
#define !!@macroid!!_FTDCUSERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "!!@fileid!!FtdcUserApiStruct.h"

#if defined(USERAPI_IS_LIB) && defined(WIN32)
#ifdef LIB_USER_API_EXPORT
#define USER_API_EXPORT __declspec(dllexport)
#else
#define USER_API_EXPORT __declspec(dllimport)
#endif
#else
#define USER_API_EXPORT 
#endif


!!enter FTD!!
class C!!@functionid!!FtdcUserSpi
{
public:
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected(){};
	
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason){};
		
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse){};
	
	///���Ļص���ʼ֪ͨ����API�յ�һ�����ĺ����ȵ��ñ�������Ȼ���Ǹ�������Ļص�������Ǳ��Ļص�����֪ͨ��
	///@param nTopicID ������루��˽���������������������ȣ�
	///@param nSequenceNo �������
	virtual void OnPackageStart(int nTopicID, int nSequenceNo){};
	
	///���Ļص�����֪ͨ����API�յ�һ�����ĺ����ȵ��ñ��Ļص���ʼ֪ͨ��Ȼ���Ǹ�������Ļص��������ñ�������
	///@param nTopicID ������루��˽���������������������ȣ�
	///@param nSequenceNo �������
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo){};

	///û��Ȩ�޵Ķಥ��������
	///@param nTopicID ���������
	virtual void OnStopMultiTopic(int nTopicID){};

	//�����ಥ�����ӿ� add by zbz 20150304
	virtual void OnMultiHeartbeat(char *CurrTime,char *MultiCastIP) {};
!!travel packages!!
!!if !strncmp(@name,"Rsp",3)!!

	///!!@comment!!
	virtual void On!!@name!!(!!travel self!!!!if @pumpid!=0!!, !!endif!!C!!@functionid!!Ftdc!!@name!!Field *p!!@name!!!!next!!, int nRequestID, bool bIsLast) {};
!!elseif !strncmp(@name,"Rtn",3)!!

	///!!@comment!!
	virtual void On!!@name!!(!!travel self!!!!if @pumpid==0!!C!!@functionid!!Ftdc!!@name!!Field *p!!@name!!!!endif!!!!next!!) {};
!!elseif !strncmp(@name,"ErrRtn",6)!!

	///!!@comment!!
	virtual void On!!@name!!(!!travel self!!!!if @pumpid!=0!!, !!endif!!C!!@functionid!!Ftdc!!@name!!Field *p!!@name!!!!next!!) {};
!!endif!!
!!next!!
};

class USER_API_EXPORT C!!@functionid!!FtdcUserApi
{
public:
	///����UserApi
	///@param pszFlowPath ����������Ϣ�ļ���Ŀ¼��Ĭ��Ϊ��ǰĿ¼
	///@param pszUserApiType UserAPI����
	///@return ��������UserApi
	static C!!@functionid!!FtdcUserApi *CreateFtdcUserApi(const char *pszFlowPath = "",
											const char *pszUserApiType = "");
	
	///��ȡϵͳ�汾��
	///@param nMajorVersion ���汾��
	///@param nMinorVersion �Ӱ汾��
	///@return ϵͳ��ʶ�ַ���
	static const char *GetVersion(int &nMajorVersion, int &nMinorVersion);
	
	///ɾ���ӿڶ�����
	///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	virtual void Release() = 0;

	//�ಥ���ÿ���
	virtual void SetMultiCast(bool bMultiCast=false) = 0;
	virtual void RegMultiTopicID(int TopicID)=0;
	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	virtual void Init(int nPrivatePort) = 0;
	
	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	virtual int Join() = 0;
	
	///��ȡ��ǰ������
	///@retrun ��ȡ���Ľ�����
	///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
	virtual const char *GetTradingDay() = 0;
	
	///ע��ǰ�û������ַ
	///@param pszFrontAddress��ǰ�û������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///ע�����ַ����������ַ
	///@param pszNsAddress�����ַ����������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
	///@remark RegisterFront������RegisterNameServer
	virtual void RegisterNameServer(char *pszNsAddress) = 0;
	
	///ע��ص��ӿ�
	///@param pSpi �����Իص��ӿ����ʵ��
	virtual void RegisterSpi(C!!@functionid!!FtdcUserSpi *pSpi) = 0;
	
	///�����г����顣
	///@param nTopicID �г���������  
	///@param nResumeType �г������ش���ʽ  
	///        !!@macroid!!_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        !!@macroid!!_TERT_RESUME:���ϴ��յ�������
	///        !!@macroid!!_TERT_QUICK:�ȴ��͵�ǰ�������,�ٴ��͵�¼���г����������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�˽���������ݡ�
	virtual void SubscribeMarketDataTopic(int nTopicID, !!@macroid!!_TE_RESUME_TYPE nResumeType) = 0;

	///����˽������
	///@param nResumeType ˽�����ش���ʽ  
	///        !!@macroid!!_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        !!@macroid!!_TERT_RESUME:���ϴ��յ�������
	///        !!@macroid!!_TERT_QUICK:ֻ���͵�¼��˽����������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�˽���������ݡ�
	virtual void SubscribePrivateTopic(!!@macroid!!_TE_RESUME_TYPE nResumeType) = 0;
	
	///���Ĺ�������
	///@param nResumeType �������ش���ʽ  
	///        !!@macroid!!_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        !!@macroid!!_TERT_RESUME:���ϴ��յ�������
	///        !!@macroid!!_TERT_QUICK:ֻ���͵�¼�󹫹���������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ������������ݡ�
	virtual void SubscribePublicTopic(!!@macroid!!_TE_RESUME_TYPE nResumeType) = 0;
	
	///���Ľ���Ա����
	///@param nResumeType ����Ա���ش���ʽ  
	///        !!@macroid!!_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        !!@macroid!!_TERT_RESUME:���ϴ��յ�������
	///        !!@macroid!!_TERT_QUICK:ֻ���͵�¼����Ա��������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�����Ա�������ݡ�
	virtual void SubscribeUserTopic(!!@macroid!!_TE_RESUME_TYPE nResumeType) = 0;
	
	///���ĺ�Լ���顣
	///@param ppInstrumentID ��ԼID  
	///@param nCount Ҫ����/�˶�����ĺ�Լ����
	///@remark 
	virtual int SubMarketData(char *ppInstrumentID[], int nCount)=0;

	///�˶���Լ���顣
	///@param ppInstrumentID ��ԼID  
	///@param nCount Ҫ����/�˶�����ĺ�Լ����
	///@remark 
	virtual int UnSubMarketData(char *ppInstrumentID[], int nCount)=0;	
	
	///����������ʱʱ�䡣
	///@param timeout ������ʱʱ��(��)  
	virtual void SetHeartbeatTimeout(unsigned int timeout) = 0;
	
	///��������־�ļ�
	///@param pszReqLogFileName ������־�ļ���  
	///@return 0 �����ɹ�
	///@return -1 ����־�ļ�ʧ��
	virtual int OpenRequestLog(const char *pszReqLogFileName) = 0;

	///��Ӧ����־�ļ�
	///@param pszRspLogFileName Ӧ����־�ļ���  
	///@return 0 �����ɹ�
	///@return -1 ����־�ļ�ʧ��
	virtual int OpenResponseLog(const char *pszRspLogFileName) = 0;
	
	///�û���¼����
	virtual int ReqUserLogin(C!!@functionid!!FtdcReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;
!!travel packages!!
!!if !strncmp(@name,"Req",3) && strcmp(@name,"ReqUserLogin")!!

	///!!@comment!!
	virtual int !!@name!!(!!travel self!!!!if @pumpid!=0!!, !!endif!!C!!@functionid!!Ftdc!!@name!!Field *p!!@name!!!!next!!, int nRequestID) = 0;
!!endif!!
!!next!!
protected:
	~C!!@functionid!!FtdcUserApi(){};
};
!!leave!!  

#endif
