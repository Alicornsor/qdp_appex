// XtpPackageDesc.h: 
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XTPPACKAGEDESC_H__EA501ADE_818C_4F9A_8738_AC9CCAF0B941__INCLUDED_)
#define AFX_XTPPACKAGEDESC_H__EA501ADE_818C_4F9A_8738_AC9CCAF0B941__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XtpData.h"
#include "HashMap.h"
#include "FieldSet.h"

//�ղ���
const DWORD TID_Nop=0x00009000;
//����Ӧ��
const DWORD TID_RspError=0x00009001;
//�û���¼����
const DWORD TID_ReqUserLogin=0x00009002;
//�û���¼Ӧ��
const DWORD TID_RspUserLogin=0x00009003;
//�û��˳�����
const DWORD TID_ReqUserLogout=0x00009004;
//�û��˳�Ӧ��
const DWORD TID_RspUserLogout=0x00009005;
//����¼������
const DWORD TID_ReqOrderInsert=0x00009006;
//����¼��Ӧ��
const DWORD TID_RspOrderInsert=0x00009007;
//������������
const DWORD TID_ReqOrderAction=0x00009008;
//��������Ӧ��
const DWORD TID_RspOrderAction=0x00009009;
//�û������޸�����
const DWORD TID_ReqUserPasswordUpdate=0x0000900A;
//�û������޸�Ӧ��
const DWORD TID_RspUserPasswordUpdate=0x0000900B;
//ǿ���û��˳�����
const DWORD TID_ReqForceUserExit=0x0000900C;
//ǿ���û��˳�Ӧ��
const DWORD TID_RspForceUserExit=0x0000900D;
//�û��Ựɾ������
const DWORD TID_ReqForceUserLogout=0x0000900E;
//�û��Ựɾ��Ӧ��
const DWORD TID_RspForceUserLogout=0x0000900F;
//���󵼳��ڴ����ݿ�
const DWORD TID_ReqDumpMemDb=0x00009010;
//����ϵͳ״̬
const DWORD TID_UpdateSystemStatus=0x00009011;
//Ͷ�����ʽ��ʻ����������
const DWORD TID_ReqAccountDeposit=0x00009012;
//Ͷ�����ʽ��ʻ������Ӧ��
const DWORD TID_RspAccountDeposit=0x00009013;
//Ͷ�����ʽ��ѯ����
const DWORD TID_ReqQryInvestorAccount=0x00009020;
//Ͷ�����ʽ��ѯӦ��
const DWORD TID_RspQryInvestorAccount=0x00009021;
//������ѯ����
const DWORD TID_ReqQryOrder=0x00009022;
//������ѯӦ��
const DWORD TID_RspQryOrder=0x00009023;
//�ɽ�����ѯ����
const DWORD TID_ReqQryTrade=0x00009024;
//�ɽ�����ѯӦ��
const DWORD TID_RspQryTrade=0x00009025;
//Ͷ���߲�ѯ����
const DWORD TID_ReqQryInvestor=0x00009026;
//Ͷ���߲�ѯӦ��
const DWORD TID_RspQryInvestor=0x00009027;
//������ѯ����
const DWORD TID_ReqQryOrderInsertFailed=0x0000902A;
//��Լ��ѯ����
const DWORD TID_ReqQryInstrument=0x0000902B;
//��Լ��ѯӦ��
const DWORD TID_RspQryInstrument=0x0000902C;
//�û���ѯ����
const DWORD TID_ReqQryUser=0x0000902D;
//�û���ѯӦ��
const DWORD TID_RspQryUser=0x0000902E;
//��������ѯ����
const DWORD TID_ReqQryExchange=0x00009031;
//��������ѯӦ��
const DWORD TID_RspQryExchange=0x00009032;
//����Ͷ�����˻���ѯ����
const DWORD TID_ReqQryUserInvestor=0x00009033;
//����Ͷ�����˻���ѯӦ��
const DWORD TID_RspQryUserInvestor=0x00009034;
//Ͷ���ֲֲ߳�ѯ����
const DWORD TID_ReqQryInvestorPosition=0x00009035;
//Ͷ���ֲֲ߳�ѯӦ��
const DWORD TID_RspQryInvestorPosition=0x00009036;
//��ͨ�����ѯ����
const DWORD TID_ReqQryMarketData=0x0000903D;
//��ͨ�����ѯӦ��
const DWORD TID_RspQryMarketData=0x0000903E;
//Ͷ�����������ʲ�ѯ����
const DWORD TID_ReqQryInvestorFee=0x0000903F;
//Ͷ�����������ʲ�ѯӦ��
const DWORD TID_RspQryInvestorFee=0x00009040;
//Ͷ���߱�֤���ʲ�ѯ����
const DWORD TID_ReqQryInvestorMargin=0x00009041;
//Ͷ���߱�֤���ʲ�ѯӦ��
const DWORD TID_RspQryInvestorMargin=0x00009042;
//�����ѯ����
const DWORD TID_ReqQryDepthMarketData=0x00009045;
//�����ѯӦ��
const DWORD TID_RspQryDepthMarketData=0x00009046;
//�������ӷ��ʲ�ѯ����
const DWORD TID_ReqQrySGEDeferRate=0x00009049;
//�������ӷ��ʲ�ѯӦ��
const DWORD TID_RspQrySGEDeferRate=0x0000904A;
//�ֲ���ϸ��ѯ����
const DWORD TID_ReqQryInvestorPositionDetail=0x0000904B;
//�ֲ���ϸ��ѯӦ��
const DWORD TID_RspQryInvestorPositionDetail=0x0000904C;
//�ֲ���ϸ��
const DWORD TID_ExInvestorPositionDetail=0x0000904D;
//Ͷ������Ȩ�������ʲ�ѯ����
const DWORD TID_ReqQryInvestorOptionFee=0x00009204;
//Ͷ������Ȩ�������ʲ�ѯӦ��
const DWORD TID_RspQryInvestorOptionFee=0x00009205;
//����ͬ����ʼ
const DWORD TID_DataSyncStart=0x00009050;
//����ͬ������
const DWORD TID_DataSyncEnd=0x00009051;
//������
const DWORD TID_InitExchange=0x00009052;
//ϯλ
const DWORD TID_InitSeat=0x00009054;
//�û�
const DWORD TID_InitUser=0x00009055;
//Ͷ����
const DWORD TID_InitInvestor=0x00009056;
//���ױ���
const DWORD TID_InitClientTradingID=0x00009057;
//�û�Ͷ���߹�ϵ
const DWORD TID_InitUserInvestor=0x00009058;
//�û�����Ȩ��
const DWORD TID_InitUserTradingRight=0x00009059;
//Ͷ�����ʽ��˻�
const DWORD TID_InitInvestorAccount=0x0000905A;
//��Լ
const DWORD TID_InitInstrument=0x0000905B;
//Ͷ���߱�֤����
const DWORD TID_InitInvestorMargin=0x0000905D;
//Ͷ����������
const DWORD TID_InitInvestorFee=0x0000905E;
//Ͷ���ֲ߳�
const DWORD TID_InitInvestorPosition=0x0000905F;
//�ͻ��ʽ��ʻ������
const DWORD TID_DbInvestorAccountDeposit=0x00009061;
//���ӽ����û�
const DWORD TID_DbInsUser=0x00009062;
//�޸Ľ����û�
const DWORD TID_DbUpdUser=0x00009063;
//ϵͳ״̬
const DWORD TID_InitSystemStatus=0x00009064;
//��Լ�ͺ�Լ���ϵ
const DWORD TID_InitInstrumentGroup=0x00009065;
//���ױ�����ϱ�֤������
const DWORD TID_InitClientMarginCombType=0x00009066;
//�������ӷ�����Ϣ��
const DWORD TID_InitSGEDeferRate=0x00009102;
//�ͻ��ʽ��ʻ������
const DWORD TID_DbClientTradingID=0x00009100;
//��Ϻ�Լ��ϸӦ��
const DWORD TID_InitCmbInstrumentDetail=0x00009098;
//Ͷ���߽���Ȩ��
const DWORD TID_InitInvestorTradingRight=0x00009101;
//�޸�Ͷ����Ȩ��
const DWORD TID_DbUpdInvestorTradingRight=0x00009103;
//����Ͷ����Ȩ��
const DWORD TID_DbInsInvestorTradingRight=0x00009104;
//ɾ��Ͷ����Ȩ��
const DWORD TID_DbDelInvestorTradingRight=0x00009105;
//����ԱIP
const DWORD TID_DbUpdUserIP=0x00009106;
//����ԱIP
const DWORD TID_DbInsUserIP=0x00009107;
//����ԱIP
const DWORD TID_DbDelUserIP=0x00009108;
//����ԱIP
const DWORD TID_InitUserIP=0x00009109;
//Ͷ������Ȩ������
const DWORD TID_InitInvestorOptionFee=0x00009112;
//QDPϵͳ��Ϣ��
const DWORD TID_InitSystemInfo=0x00009113;
//ʱ��ͬ��
const DWORD TID_NtfTimeSync=0x00009070;
//ͨѶ�׶��л�֪ͨ
const DWORD TID_NtfCommPhaseChange=0x00009071;
//����֪ͨ
const DWORD TID_NtfOrder=0x00009072;
//�ɽ�֪ͨ
const DWORD TID_NtfTrade=0x00009073;
//��Լ����״̬�ı�֪ͨ
const DWORD TID_NtfInstrumentStatusUpdate=0x00009074;
//�Ựɾ��֪ͨ
const DWORD TID_NtfDelUserSession=0x00009075;
//��ͨ����֪ͨ
const DWORD TID_NtfMarketData=0x00009076;
//֪ͨ�������ں�
const DWORD TID_NtfLifeCycle=0x00009079;
//����¼�����֪ͨ
const DWORD TID_NtfErrorOrderInsert=0x0000907A;
//������������֪ͨ
const DWORD TID_NtfErrorOrderAction=0x0000907B;
//�ڴ��仯֪ͨ
const DWORD TID_NtfMemtableChange=0x0000907E;
//֪ͨ���̻���ѯ��Լ����
const DWORD TID_ReqQueryExInstrument=0x00009081;
//���̻���ѯ��ԼӦ��
const DWORD TID_RspQueryExInstrument=0x00009082;
//���̻���ѯ������Ӧ��
const DWORD TID_RspQueryExTradingDay=0x00009083;
//���̻���ѯ�ͻ��ֲ�Ӧ��
const DWORD TID_RspQueryExInvestorPosition=0x00009084;
//���̻���ѯ����Ӧ��
const DWORD TID_RspQueryExMarketData=0x00009085;
//�ⶳInnerLinkδ���뽻�׵ı���
const DWORD TID_ReqRollbakPreOrder=0x0000909D;
//�����ر�֪ͨ
const DWORD TID_NtfInvestorAccountDeposit=0x00009086;
//���̻���ѯ����
const DWORD TID_QueryBaseFinish=0x00009087;
//���̻���ѯ�ʽ�Ӧ��
const DWORD TID_RspQueryExCapitalData=0x00009088;
//���̻���ѯ��Ϻ�Լ��ϸӦ��
const DWORD TID_RspQueryExCmbInstrumentDetail=0x00009090;
//�������ӷ���֪ͨ
const DWORD TID_NtfSGEDeferRate=0x0000909E;
//�ɹ���½֪ͨ
const DWORD TID_InterLoginInfo=0x00009095;
//QDP������Ϣ֪ͨ
const DWORD TID_NtfMessageNotify=0x00009096;
//�ڲ���¼����
const DWORD TID_InnerLogin=0x00009415;
//�ڲ��ּ۱��ѯӦ��
const DWORD TID_ExQryMBLMarketData=0x00009416;
//�ּ۱��ѯ����
const DWORD TID_ReqQryMBLMarketData=0x00009417;
//�ּ۱��ѯӦ��
const DWORD TID_RspQryMBLMarketData=0x00009418;
//�ڴ��仯֪ͨ
const DWORD TID_NtfPositionProfit=0x00009419;

///��ȡ����������
///@param	tid	�������
///@return	��������
const char *getPackageName(DWORD tid);

#ifndef FIELD_USE_DEFINE
#define FIELD_USE_DEFINE

#define UNLIMITED_FIELD_OCCUR 1000
#define MAX_PACKAGE_NAME_LEN		100
#define MAX_COMMENT_LEN		100
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
	char packageName[MAX_PACKAGE_NAME_LEN];
	char comment[MAX_COMMENT_LEN];
}	TPackageDefine;

#endif

extern TPackageDefine XTPPackageDefines[];

class CXTPPackageDefineMap: public CHashMap<DWORD, TPackageDefine *, HashInt>
{
public:
	CXTPPackageDefineMap(TPackageDefine *pXTPPackageDefines, int nDefineCount)
	{
		for(int i=0; i<nDefineCount; i++)
		{
			Insert(pXTPPackageDefines->tid, pXTPPackageDefines);
			pXTPPackageDefines++;
		}
	}
};

extern CXTPPackageDefineMap g_XTPPackageDefineMap;
void XTP_DEBUG_BODY(DWORD tid, CFieldSet *pPackage, CLogger *pLogger);
#endif
