#ifndef _TypeDefine_H_
#define _TypeDefine_H_

#include "platform.h"
#include "QdpFtdcUserApiDataType.h"
#include "QdpFtdcUserApiStruct.h"

typedef map<string,CQdpFtdcInstrumentStatusField> CInstrumentStatusMap;

#ifndef CORRECT
#define CORRECT 0;
#endif

#ifndef CORRECT
#define CORRECT 0;
#endif

#ifndef ERROR
#define ERROR   1;
#endif

#ifndef FAILURE
#define FAILURE 2;
#endif

///�ϳ�ָ��
struct CFfexTBCmdField
{
	///ָ����
	char  sCmdNo[30];
	///ָ������
	char sCmdType[101];
	///�ֶ�����
	char sCmdFieldName[601];
	///�ֶ�����
	char sCmdFieldContent[601];
	///��������
	char sCmdTradingDay[9];		
};


typedef struct ST_INPUT_CMD
{
	char  sCmdNo[30];
	char  sCmdType[30];
	int	  sCmdTypeNum;//ת�������ֵ�CmdType
	CQdpFtdcInputOrderField ReqField;

	CQdpFtdcRspInfoField pRspInfo;

	bool  bLocalIdFlag;
	int	  iRepeatNum;	//	�ظ����͵Ĵ���
	int	  iCount;
	int	  iCycleTimes;
	int	  iRowCount;	//	��¼��
	double dFrozenMargin;
	double dCurrMargin;
	double dCurMoney;	//	������
	char  sNote[1024];	//  ����������

	CFfexTBCmdField tBCmdReqField;//will add by 2012/05/20
	///�ɽ����
	TQdpFtdcTradeIDType	TradeID;
	bool bReciveRsp;
}st_input_cmd;


//	����ȫ�ֺ�
typedef struct ST_MARCO
{
	int		iType;			//  ���� 0: �ַ�  1:����  2: ����
	char	sMarcoId[30];	//	��ID
	char	sMarcoValue[30];
	int		iMarcoValue;
	double	dMarcoValue;	//	��ֵ	
}st_marco;


//const char *GetInstrumentStatus(char chUserType);
//const char *GetAdminOrder(char chUserType);
// const char *GetOpFlag(char chUserType);
// const char *GetBsFlag(char chUserType);
// const char *GetHedgeFlag(char chUserType);
// const char *GetPosiDirection(char chUserType);
// const char *GetBsflag(char chUserType);
// const char *GetOffsetFlag(char chUserType);
//const char *GetOrderStatus(char chUserType);


void delFrontCh( char *p, char ch );
void ShowMsg(const char *msg,...);


void ReplaceMarcoStr(CQdpFtdcInputOrderField *sCmd);
void ReplaceSpChar(char *str, char ch_in, char ch_rp);

bool CheckCondition(int iLast);

#endif