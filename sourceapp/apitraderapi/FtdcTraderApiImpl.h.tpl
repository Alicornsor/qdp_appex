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
!!function!!
#include <set>
using namespace std;

struct ltstr
{
	bool operator()(const char* s1, const char* s2) const
	{
		return strcmp(s1, s2) < 0;
	}
};

typedef set<char *, ltstr> CPackageSet;
CPackageSet g_setUsePackage;

bool InUse(char *name)
{
	return (g_setUsePackage.find(name)!=g_setUsePackage.end());
}

!!endfunction!!
!!enter traderapi!!
!!travel self!!	
!!command g_setUsePackage.insert(@name);!!
!!next!!
!!leave!!
/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file !!@functionid!!FtdcTraderApiImpl.h
///@brief �����˿ͻ��˽ӿ�ʵ��
///@history 
///20150522	���һ�		�������ļ�
/////////////////////////////////////////////////////////////////////////

#if !defined(_FTDCTRADERAPIIMPL_H)
#define _FTDCTRADERAPIIMPL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "!!@fileid!!FtdcUserApi.h"
#include "!!@fileid!!FtdcTraderApi.h"


!!enter FTD!!
///����API�ӿ�ʵ��
class CFtdcTraderApiImpl : public C!!@functionid!!FtdcTraderApi, public C!!@functionid!!FtdcUserSpi
{
public:	
	///���캯��
	CFtdcTraderApiImpl(const char *pszFlowPath);

	///ɾ���ӿڶ�����
	///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	virtual void Release();
	
	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	virtual void Init();
	
	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	virtual int Join();
	
	///��ȡ��ǰ������
	///@retrun ��ȡ���Ľ�����
	///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
	virtual const char *GetTradingDay();
	
	///ע��ǰ�û������ַ
	///@param pszFrontAddress��ǰ�û������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
	virtual void RegisterFront(char *pszFrontAddress);
	
	///ע�����ַ����������ַ
	///@param pszNsAddress�����ַ����������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����12001������������˿ںš�
	///@remark RegisterFront������RegisterNameServer
	virtual void RegisterNameServer(char *pszNsAddress);
	
	///ע��ص��ӿ�
	///@param pSpi �����Իص��ӿ����ʵ��
	virtual void RegisterSpi(C!!@functionid!!FtdcTraderSpi *pSpi);
	
	///����˽������
	///@param nResumeType ˽�����ش���ʽ  
	///        !!@macroid!!_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        !!@macroid!!_TERT_RESUME:���ϴ��յ�������
	///        !!@macroid!!_TERT_QUICK:ֻ���͵�¼��˽����������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�˽���������ݡ�
	virtual void SubscribePrivateTopic(!!@macroid!!_TE_RESUME_TYPE nResumeType);
	
	///���Ĺ�������
	///@param nResumeType �������ش���ʽ  
	///        !!@macroid!!_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        !!@macroid!!_TERT_RESUME:���ϴ��յ�������
	///        !!@macroid!!_TERT_QUICK:ֻ���͵�¼�󹫹���������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ������������ݡ�
	virtual void SubscribePublicTopic(!!@macroid!!_TE_RESUME_TYPE nResumeType);

	///���Ľ���Ա����
	///@param nResumeType ����Ա���ش���ʽ  
	///        !!@macroid!!_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        !!@macroid!!_TERT_RESUME:���ϴ��յ�������
	///        !!@macroid!!_TERT_QUICK:ֻ���͵�¼����Ա��������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�����Ա�������ݡ�
	virtual void SubscribeUserTopic(!!@macroid!!_TE_RESUME_TYPE nResumeType);

	///����������ʱʱ�䡣
	///@param timeout ������ʱʱ��(��)  
	virtual void SetHeartbeatTimeout(unsigned int timeout);
	
	///��������־�ļ�
	///@param pszReqLogFileName ������־�ļ���  
	///@return 0 �����ɹ�
	///@return -1 ����־�ļ�ʧ��
	virtual int OpenRequestLog(const char *pszReqLogFileName);

	///��Ӧ����־�ļ�
	///@param pszRspLogFileName Ӧ����־�ļ���  
	///@return 0 �����ɹ�
	///@return -1 ����־�ļ�ʧ��
	virtual int OpenResponseLog(const char *pszRspLogFileName);

!!travel packages!!
!!if InUse(@name)!!
!!if !strncmp(@name,"Req",3)!!

	///!!@comment!!
	virtual int !!@name!!(!!travel self!!!!if @pumpid==0!!C!!@functionid!!Ftdc!!@name!!Field *p!!@name!!!!endif!!!!next!!, int nRequestID);
!!endif!!
!!endif!!
!!next!!
private:
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();
	
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason);
		
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///���Ļص���ʼ֪ͨ����API�յ�һ�����ĺ����ȵ��ñ�������Ȼ���Ǹ�������Ļص�������Ǳ��Ļص�����֪ͨ��
	///@param nTopicID ������루��˽���������������������ȣ�
	///@param nSequenceNo �������
	virtual void OnPackageStart(int nTopicID, int nSequenceNo);
	
	///���Ļص�����֪ͨ����API�յ�һ�����ĺ����ȵ��ñ��Ļص���ʼ֪ͨ��Ȼ���Ǹ�������Ļص��������ñ�������
	///@param nTopicID ������루��˽���������������������ȣ�
	///@param nSequenceNo �������
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo);
	
!!travel packages!!
!!if InUse(@name)!!
!!if !strncmp(@name,"Rsp",3)!!

	///!!@comment!!
	virtual void On!!@name!!(!!travel self!!!!if @pumpid!=0!!, !!endif!!C!!@functionid!!Ftdc!!@name!!Field *p!!@name!!!!next!!, int nRequestID, bool bIsLast);
!!elseif !strncmp(@name,"Rtn",3)!!

	///!!@comment!!
	virtual void On!!@name!!(!!travel self!!!!if @pumpid!=0!!, !!endif!!C!!@functionid!!Ftdc!!@name!!Field *p!!@name!!!!next!!);
!!elseif !strncmp(@name,"ErrRtn",6)!!

	///!!@comment!!
	virtual void On!!@name!!(!!travel self!!!!if @pumpid!=0!!, !!endif!!C!!@functionid!!Ftdc!!@name!!Field *p!!@name!!!!next!!);
!!endif!!
!!endif!!
!!next!!
private:
	C!!@functionid!!FtdcUserApi *m_pUserApi;
	C!!@functionid!!FtdcTraderSpi *m_pSpi;
};

!!leave!!  

#endif
