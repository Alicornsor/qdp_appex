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

///上场指令
struct CFfexTBCmdField
{
	///指令编号
	char  sCmdNo[30];
	///指令类型
	char sCmdType[101];
	///字段名称
	char sCmdFieldName[601];
	///字段内容
	char sCmdFieldContent[601];
	///交易日期
	char sCmdTradingDay[9];		
};


typedef struct ST_INPUT_CMD
{
	char  sCmdNo[30];
	char  sCmdType[30];
	int	  sCmdTypeNum;//转化的数字的CmdType
	CQdpFtdcInputOrderField ReqField;

	CQdpFtdcRspInfoField pRspInfo;

	bool  bLocalIdFlag;
	int	  iRepeatNum;	//	重复发送的次数
	int	  iCount;
	int	  iCycleTimes;
	int	  iRowCount;	//	记录数
	double dFrozenMargin;
	double dCurrMargin;
	double dCurMoney;	//	发生额
	char  sNote[1024];	//  附件数据域

	CFfexTBCmdField tBCmdReqField;//will add by 2012/05/20
	///成交编号
	TQdpFtdcTradeIDType	TradeID;
	bool bReciveRsp;
}st_input_cmd;


//	定义全局宏
typedef struct ST_MARCO
{
	int		iType;			//  类型 0: 字符  1:整数  2: 浮点
	char	sMarcoId[30];	//	宏ID
	char	sMarcoValue[30];
	int		iMarcoValue;
	double	dMarcoValue;	//	宏值	
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