// FtdPackageDesc.h: 
//
//////////////////////////////////////////////////////////////////////

#if !defined(_FTDPACKAGEDESC_H)
#define _FTDPACKAGEDESC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FtdData.h"
#include "FieldSet.h"


#define FTD_VERSION 1

const WORD TSS_DIALOG = 1;		//�Ի���
const WORD TSS_PRIVATE = 2;		//�ͻ�˽����
const WORD TSS_PUBLIC = 3;		//������
const WORD TSS_QUERY = 4;		//��ѯ
const WORD TSS_USER = 5;		//�û�˽����


//����Ӧ��
const DWORD FTD_TID_RspError=0x00005000;
//�û���¼����
const DWORD FTD_TID_ReqUserLogin=0x00005001;
//�û���¼Ӧ��
const DWORD FTD_TID_RspUserLogin=0x00005002;
//�û��˳�����
const DWORD FTD_TID_ReqUserLogout=0x00005003;
//�û��˳�Ӧ��
const DWORD FTD_TID_RspUserLogout=0x00005004;
//�û������޸�����
const DWORD FTD_TID_ReqUserPasswordUpdate=0x00005005;
//�û������޸�Ӧ��
const DWORD FTD_TID_RspUserPasswordUpdate=0x00005006;
//ǿ���û��˳�����
const DWORD FTD_TID_ReqForceUserExit=0x00005007;
//ǿ���û��˳�Ӧ��
const DWORD FTD_TID_RspForceUserExit=0x00005008;
//�û��Ựɾ������
const DWORD FTD_TID_ReqForceUserLogout=0x00005009;
//�û��Ựɾ��Ӧ��
const DWORD FTD_TID_RspForceUserLogout=0x0000500A;
//���󵼳��ڴ����ݿ�
const DWORD FTD_TID_ReqDumpMemDb=0x0000501B;
//����¼������
const DWORD FTD_TID_ReqOrderInsert=0x00005020;
//����¼��Ӧ��
const DWORD FTD_TID_RspOrderInsert=0x00005021;
//������������
const DWORD FTD_TID_ReqOrderAction=0x00005022;
//��������Ӧ��
const DWORD FTD_TID_RspOrderAction=0x00005023;
//Ͷ�����ʽ��ʻ����������
const DWORD FTD_TID_ReqAccountDeposit=0x00005024;
//Ͷ�����ʽ��ʻ������Ӧ��
const DWORD FTD_TID_RspAccountDeposit=0x00005025;
//����������֪ͨ
const DWORD FTD_TID_RtnFlowMessageCancel=0x00005030;
//�ڲ��ַ���Ϣ֪ͨ
const DWORD FTD_TID_IntlRtnDissemination=0x00005031;
//�ɽ��ر�
const DWORD FTD_TID_RtnTrade=0x00005032;
//�����ر�
const DWORD FTD_TID_RtnOrder=0x00005033;
//����¼�����ر�
const DWORD FTD_TID_ErrRtnOrderInsert=0x00005034;
//������������ر�
const DWORD FTD_TID_ErrRtnOrderAction=0x00005035;
//��Լ����״̬֪ͨ
const DWORD FTD_TID_RtnInstrumentStatus=0x00005036;
//�˻������ر�
const DWORD FTD_TID_RtnInvestorAccountDeposit=0x00005037;
//QDP������Ϣ֪ͨ
const DWORD FTD_TID_RtnMessageNotify=0x00005038;
//�������ӷ���֪ͨ
const DWORD FTD_TID_RtnSGEDeferRate=0x0000503F;
//֣�ݺ�Լ״̬
const DWORD FTD_TID_RtnQmdInstrumentStatu=0x00005040;
//������ѯ����
const DWORD FTD_TID_ReqQryOrder=0x00005041;
//������ѯӦ��
const DWORD FTD_TID_RspQryOrder=0x00005042;
//�ɽ�����ѯ����
const DWORD FTD_TID_ReqQryTrade=0x00005043;
//�ɽ�����ѯӦ��
const DWORD FTD_TID_RspQryTrade=0x00005044;
//����Ͷ�����˻���ѯ����
const DWORD FTD_TID_ReqQryUserInvestor=0x00005045;
//����Ͷ�����˻���ѯӦ��
const DWORD FTD_TID_RspQryUserInvestor=0x00005046;
//���ױ����ѯ����
const DWORD FTD_TID_ReqQryTradingCode=0x00005047;
//���ױ����ѯӦ��
const DWORD FTD_TID_RspQryTradingCode=0x00005048;
//Ͷ�����ʽ��˻���ѯ����
const DWORD FTD_TID_ReqQryInvestorAccount=0x00005049;
//Ͷ�����ʽ��˻���ѯӦ��
const DWORD FTD_TID_RspQryInvestorAccount=0x0000504A;
//��Լ��ѯ����
const DWORD FTD_TID_ReqQryInstrument=0x0000504B;
//��Լ��ѯӦ��
const DWORD FTD_TID_RspQryInstrument=0x0000504C;
//��������ѯ����
const DWORD FTD_TID_ReqQryExchange=0x0000504D;
//��������ѯӦ��
const DWORD FTD_TID_RspQryExchange=0x0000504E;
//Ͷ���ֲֲ߳�ѯ����
const DWORD FTD_TID_ReqQryInvestorPosition=0x0000504F;
//Ͷ���ֲֲ߳�ѯӦ��
const DWORD FTD_TID_RspQryInvestorPosition=0x00005050;
//������������
const DWORD FTD_TID_ReqSubscribeTopic=0x00005051;
//��������Ӧ��
const DWORD FTD_TID_RspSubscribeTopic=0x00005052;
//�����ѯ����
const DWORD FTD_TID_ReqQryTopic=0x00005055;
//�����ѯӦ��
const DWORD FTD_TID_RspQryTopic=0x00005056;
//�û���ѯ����
const DWORD FTD_TID_ReqQryUser=0x00005057;
//�û���ѯӦ��
const DWORD FTD_TID_RspQryUser=0x00005058;
//Ͷ�����������ʲ�ѯ����
const DWORD FTD_TID_ReqQryInvestorFee=0x00005059;
//Ͷ�����������ʲ�ѯӦ��
const DWORD FTD_TID_RspQryInvestorFee=0x00005060;
//Ͷ���߱�֤���ʲ�ѯ����
const DWORD FTD_TID_ReqQryInvestorMargin=0x00005061;
//Ͷ���߱�֤���ʲ�ѯӦ��
const DWORD FTD_TID_RspQryInvestorMargin=0x00005062;
//�������ӷ��ʲ�ѯ����
const DWORD FTD_TID_ReqQrySGEDeferRate=0x00005088;
//�������ӷ��ʲ�ѯӦ��
const DWORD FTD_TID_RspQrySGEDeferRate=0x00005089;
//�ֲ���ϸ��ѯ����
const DWORD FTD_TID_ReqQryInvestorPositionDetail=0x00005098;
//�ֲ���ϸ��ѯӦ��
const DWORD FTD_TID_RspQryInvestorPositionDetail=0x00005099;
//Ͷ������Ȩ�������ʲ�ѯ����
const DWORD FTD_TID_ReqQryInvestorOptionFee=0x00005102;
//Ͷ������Ȩ�������ʲ�ѯӦ��
const DWORD FTD_TID_RspQryInvestorOptionFee=0x00005103;
//�ڲ��������֪ͨ
const DWORD FTD_TID_IntlRtnDepthMarketData=0x00005070;
//Topic��ѯӦ��
const DWORD FTD_TID_IntlTopicSearch=0x00005080;
//Topic��ѯ
const DWORD FTD_TID_ReqTopicSearch=0x00005081;
//�������֪ͨ
const DWORD FTD_TID_RtnDepthMarketData=0x00005071;
//�������֪ͨ
const DWORD FTD_TID_RtnMultiDepthMarketData=0x00005072;
//���ĺ�Լ�������Ϣ
const DWORD FTD_TID_ReqSubMarketData=0x00005073;
//���ĺ�Լ�������Ϣ
const DWORD FTD_TID_RspSubMarketData=0x00005074;
//�˶���Լ�������Ϣ
const DWORD FTD_TID_ReqUnSubMarketData=0x00005075;
//�˶���Լ�������Ϣ
const DWORD FTD_TID_RspUnSubMarketData=0x00005076;
//ʵʱ�����ѯ����
const DWORD FTD_TID_ReqQryMarketData=0x00005078;
//ʵʱ�����ѯӦ��
const DWORD FTD_TID_RspQryMarketData=0x00005079;
//�����ѯ����
const DWORD FTD_TID_ReqQryDepthMarketData=0x00005082;
//�����ѯӦ��
const DWORD FTD_TID_RspQryDepthMarketData=0x00005083;
//�ּ۱��ѯ����
const DWORD FTD_TID_ReqQryMBLMarketData=0x00005084;
//�ּ۱��ѯӦ��
const DWORD FTD_TID_RspQryMBLMarketData=0x00005085;

#ifndef FIELD_USE_DEFINE
#define FIELD_USE_DEFINE

#define UNLIMITED_FIELD_OCCUR 1000

typedef struct
{
	DWORD fid;
	CFieldDescribe *pFieldDescribe;
	int minOccur;
	int maxOccur;
}	TFieldUse;

typedef struct
{
	DWORD tid;
	int fieldUseCount;
	TFieldUse *fieldUse;
}	TPackageDefine;

#endif

extern TPackageDefine FTDPackageDefines[];

void FTDC_DEBUG_BODY(DWORD tid, CFieldSet *pPackage, CLogger *pLogger);

#endif
