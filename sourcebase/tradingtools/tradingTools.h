/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file tradingTools.h
///@brief�������뽻���йص����ɹ��ߺ���
///@history 
///20050214	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef TRADING_TOOLS
#define TRADING_TOOLS

#include "errorDefine.h"
#include "CMemorySequence.h"
#include "CMemoryDB.h"

///���еĹ���Ա���ܶ���
#define FuncLead							"1010"
#define FuncOrderInsert						FuncLead "0001"
#define FuncOrderAction						FuncLead "0002"
#define FuncQuoteInsert						FuncLead "0003"
#define FuncQuoteAction						FuncLead "0004"
#define FuncOTCOrderInsert					FuncLead "0005"
#define FuncExecOrderInsert					FuncLead "0006"
#define FuncExecOrderAction					FuncLead "0007"
#define FuncAdminOrderInsert				FuncLead "0008"
#define FuncBulletin						FuncLead "0009"
#define FuncInstrumentStatusUpdate			FuncLead "0010"
#define FuncForceUserExit					FuncLead "0011"
#define FuncForceUserLogout					FuncLead "0012"
#define FuncExchangeDataSyncStatusUpdate	FuncLead "0013"
#define FuncSGDataSyncStatusUpdate			FuncLead "0014"
#define FuncInformation						FuncLead "0015"

///ȱʡ�Ŀͻ���
extern const CInvestorIDType defaultInvestorID;

///ȱʡ�Ļ�Ա��
extern const CParticipantIDType defaultParticipantID;

///ȱʡ�Ļ�Ա��
extern const CParticipantIDType defaultClearingParticipantID;

///ȱʡ�Ŀͻ���
extern const CClientIDType defaultClientID;

///ȱʡ�ĺ�Լ��
extern const CInstrumentIDType defaultInstrumentID;

///ȱʡ�Ĳ�Ʒ��
extern const CProductIDType defaultProductID;

///ȱʡ��Ͷ���ױ���־
extern const CHedgeFlagType defaultHedgeFlag;

///ȱʡ���û�����
extern const CUserIDType defaultUserID;

///ȱʡ�Ľ�����
extern const CExchangeIDType defaultExchangeID;

///����ϵͳ����
extern CTradingSystemNameType tradingSystemName;

///��ȡ����Ľ�������
///@param	pDB	ָ�����ڴ����ݿ�
///@return	����Ľ������ڣ����û�н�������ڣ��򷵻�ȱʡ����
CReadOnlyDateType getTradingDay(CMemoryDB *pDB);

///��ȡ����Ľ�������
///@param	pDB	ָ�����ڴ����ݿ�
///@param	pYear	���ص����
///@param	pMonth	���ص��·�
///@param	pDay	���ص�����
void getTradingDay(CMemoryDB *pDB,int *pYear,int *pMonth,int *pDay);

///��ȡ��ǰʱ��
///@param	pDB	ָ�����ڴ����ݿ⣬�����ָ������ʹ���ϴ�ָ�����ڴ����ݿ�
///@return	��ǰʱ��
CReadOnlyTimeType getCurrentTime(CMemoryDB *pDB=NULL);

///��ȡ�ϴ�ʱ��
///@param	pDB	ָ�����ڴ����ݿ�
///@return	�ϴ�ʱ��
CReadOnlyTimeType getOldTime(CMemoryDB *pDB);

//��ȡ��ǰ�ľ�ȷʱ��
///@param	pDB	ָ�����ڴ����ݿ�
///@param	pTime	���ڷ���ʱ�䣨��ȷ���룩
///@param	pMillisec	���ڷ���ʱ�䣨��ȷ�����룩
void getCurrentTime(CMemoryDB *pDB, CTimeType *pTime, CMillisecType *pMillisec);

///���õ�ǰʱ��
///@param	pDB	ָ�����ڴ����ݿ�
///@return	��ǰʱ��
void setCurrentTime(CMemoryDB *pDB, CWriteableCurrentTime *pTime, CTransaction *pTransaction);

///�õ�ָ��ʱ���е�������
///@param	theTime	ָ��ʱ��
///@return	������
int getSecond(CReadOnlyTimeType &theTime);

///�õ�ʱ���ʾ���ڽ����е�������������ʱ���ǽ���ĵڼ���
///@param	theTime	ָ��ʱ��
///@return	�����������
int getSecondOfDay(CReadOnlyTimeType &theTime);

///��ȡָ����Լ�Ľ���״̬
///@param	pInstrument	ָ���ĺ�Լ
///@return	�ú�Լ�Ľ���״̬
CInstrumentStatusType getInstrumentStatus(CInstrument *pInstrument);

///��ȡ����������ͬ��״̬
///@param	pDB	ָ�����ڴ����ݿ�
///@return	����������ͬ��״̬
CReadOnlyDataSyncStatusType getDataSyncStatus(CMemoryDB *pDB);

///��ȡ�෴����������
///@param	direction	ԭ��������
///@return	�෴����������
CDirectionType getReverseDirection(CReadOnlyDirectionType direction);

///���ú�Լ�Ƿ���Խ��׵ı�־
///@param	pOrder	Ҫ���ñ�־�ĺ�Լ
void setTradable(CWriteableOrder *pOrder);

///�ж�ֹ���Ƿ�Ӧ��������
///@param	pOrder	ָ����ֹ��
///@param	lastPrice	���¼�
///@return	true��ʾӦ�����false��ʾ��Ӧ������
bool needActiveStopOrder(COrder *pOrder, CReadOnlyPriceType &lastPrice);

///����ֹ��״̬
///@param	pOrder	ָ����ֹ��
///@param	pMarketData	��Ӧ������
//void setStopOrderStatus(CWriteableOrder *pOrder, CMarketData *pMarketData);

///���ñ�����ʣ��������״̬
///@param	pOrder	ָ���ı���
void setOrderStatus(CWriteableOrder *pOrder);


///��ȡĳ����Լ��ǰ�����
///@param	pInstrument	ָ���ĺ�Լ
CReadOnlyPriceType &getPreSettlementPrice(CInstrument *pInstrument);

///���ý���ϵͳ����
///@param	pConfig	ϵͳ����
void setTradingSystemName(CConfig *pConfig);

#endif
