#include "FixValues.h"

//日期和时间类型(格式 yyyy-MM-dd hh:nn:ss)
typedef char					FixDateTimeType[21];
//日期类型(格式 yyyy-MM-dd)
typedef char					FixDateType[11];
//时间类型(格式 hh:nn:ss)
typedef char					FixTimeType[11];

///////////////////////////////////////////////////////////////////////////
//通知消息类型
typedef char					FIXTextType[80];

///////////////////////////////////////////////////////////////////////////
//RefMsgType
#define RefMsgType_L    "L" // Login message 
#define RefMsgType_D    "D" // New Order Single 
#define RefMsgType_F    "F" // Order Cancel Request 
#define RefMsgType_H    "H" // Order Status Request 
#define RefMsgType_PR   "PR" // Request for Position 
#define RefMsgType_AR   "AR" // Account Data Request 

///////////////////////////////////////////////////////////////////////////
//BusinessRejectReason
#define BusinessRejectReason_0    0  // Other 
#define BusinessRejectReason_1    1  // Unknown ID 
#define BusinessRejectReason_2    2  // Unknown Security 
#define BusinessRejectReason_3    3  // Unsupported Message Type 
#define BusinessRejectReason_4    4  // Application not available 
#define BusinessRejectReason_5    5  // Conditionally Required Field Missing



///////////////////////////////////////////////////////////////////////////
//订阅类型
typedef char FIXSubscriptionType;
#define SubscriptionRequestType_Snapshot    '0' //快照
#define SubscriptionRequestType_subscribe   '1' //订阅
#define SubscriptionRequestType_unsubscribe '2' //取消订阅

///////////////////////////////////////////////////////////////////////////
//账号
typedef char FIXAccountType[32];

///////////////////////////////////////////////////////////////////////////
//价格
typedef double FIXPriceType;

///////////////////////////////////////////////////////////////////////////
//持仓请求类型
typedef int FIXPosReqType;
#define PosReqType_Positions                0 //持仓 
#define PosReqType_Trades                   1 //成交
#define PosReqType_SOD                      4 //Start of Day
#define PosReqType_MF                       5 //Manual Fill
#define PosReqType_DSOD                     6 //Detailed Start of Day

///////////////////////////////////////////////////////////////////////////
//订单状态
typedef char FIXExecType;
#define ExecType_New                        '0'
#define ExecType_Partial_Fill               '1'
#define ExecType_Fill                       '2'
#define ExecType_Cancel                     '4'
#define ExecType_Replace                    '5'
#define ExecType_Pending_Cancel             '6'
#define ExecType_Rejected                   '8'
#define ExecType_Suspended                  '9'
#define ExecType_Expired                    'C'
#define ExecType_Restated                   'D'
#define ExecType_PendingReplace             'E'
#define ExecType_OrderStatus                'I'

///////////////////////////////////////////////////////////////////////////
//订单状态
typedef char FIXOrdStatusType;
#define OrdStatusType_New                   '0'
#define OrdStatusType_Partial_Fill          '1'
#define OrdStatusType_Fill                  '2'
#define OrdStatusType_Cancel                '4'
#define OrdStatusType_Replace               '5'
#define OrdStatusType_Pending_Cancel        '6'
#define OrdStatusType_Rejected              '8'
#define OrdStatusType_Suspended             '9'
#define OrdStatusType_PendingNew            'A'
#define OrdStatusType_Expired               'C'
#define OrdStatusType_PendingReplace        'E'
#define OrdStatusType_InsertSubmitted		'F'
#define OrdStatusType_CancelSubmitted		'G'
#define OrdStatusType_Unknown               'U'

///////////////////////////////////////////////////////////////////////////
//返回类型
typedef char FIXExecTransType;
#define ExecTransType_New                   '0'
#define ExecTransType_Cancel                '1'
#define ExecTransType_Correct               '2'
#define ExecTransType_Status                '3'

///////////////////////////////////////////////////////////////////////////
//交易所代码
typedef char FIXSecurityExchangeType[32];

///////////////////////////////////////////////////////////////////////////
//合约代码
typedef char FIXSecurityIDType[64];

///////////////////////////////////////////////////////////////////////////
//产品代码
typedef char FIXSymbolType[32];

///////////////////////////////////////////////////////////////////////////
//网关类型
typedef int FIXSubExchangeGatewayType;
#define SubExchangeGateway_Price            1
#define SubExchangeGateway_Order            2
#define SubExchangeGateway_Fill             3

///////////////////////////////////////////////////////////////////////////
//数量类型
typedef int FIXOrderQtyType;

///////////////////////////////////////////////////////////////////////////
//买卖方向类型
typedef char FIXSideType;
#define SideType_Buy                        '1'
#define SideType_Sell                       '2'

///////////////////////////////////////////////////////////////////////////
//订单类型类型
typedef char FIXOrdTypeType;
#define OrdType_Market                      '1'
#define OrdType_Limit                       '2'
#define OrdType_Stop                        '3'
#define OrdType_StopL                       '4'
#define OrdType_MOC                         '5'
#define OrdType_LOC                         'B'
#define OrdType_MIT                         'J'
#define OrdType_LSM                         'O'
#define OrdType_MIL                         'Q'
#define OrdType_MOL                         'R'
#define OrdType_SMIL                        'S'
#define OrdType_MMOL                        'T'
#define OrdType_BL                          'U'
#define OrdType_SB                          'V'
#define OrdType_LIT                         'W'
#define OrdType_BLIT                        'X'

///////////////////////////////////////////////////////////////////////////
//开平标志类型
typedef char FIXOpenCloseType;
#define OpenCloseType_Open                  'O'
#define OpenCloseType_Close                 'C'
#define OpenCloseType_FIFO                  'F'

///////////////////////////////////////////////////////////////////////////
//本地报单编号类型
typedef char FIXOrderLocalIDType[32];

///////////////////////////////////////////////////////////////////////////
//本地报单编号类型
typedef char FIXMDEntryType;
#define MDEntryType_Bid                     '0'
#define MDEntryType_Ask                     '1'
#define MDEntryType_Trade                   '2'
#define MDEntryType_OpeningPrice            '4'
#define MDEntryType_ClosingPrice            '5'
#define MDEntryType_SettlementPrice         '6'
#define MDEntryType_HighPrice               '7'
#define MDEntryType_LowPrice                '8'
#define MDEntryType_Imbalance               'A'
#define MDEntryType_WorkupState             'P'
#define MDEntryType_ImpliedBid              'Y'
#define MDEntryType_ImpliedAsk              'Z'
#define MDEntryType_MarketBid               'n'
#define MDEntryType_MarketAsk               'o'
#define MDEntryType_IndicativeOpen          'p'
#define MDEntryType_IndicativeClose         'q'
#define MDEntryType_IndicativeBid           'r'
#define MDEntryType_IndicativeAsk           's'
#define MDEntryType_IndicativeSettlement    't'
#define MDEntryType_LocalBid                'u'
#define MDEntryType_LocalOffer              'v'
#define MDEntryType_DealableRegularBid      'w'
#define MDEntryType_DealableRegularOffer    'x'
#define MDEntryType_NonCreditScreenedBid    'y'
#define MDEntryType_NonCreditScreenedOffer  'z'

///////////////////////////////////////////////////////////////////////////
//行情深度类型
typedef int FIXMarketDepthType;
#define MarketDepthType_FullBook            0
#define MarketDepthType_TopOfBook           1

///////////////////////////////////////////////////////////////////////////
//行情更新类型
typedef int FIXMDUpdateType;//行情更新类型：0-全量行情，1-增量行情			
#define MDUpdateType_FullRefresh            0
#define MDUpdateType_IncrementalRefresh     1

///////////////////////////////////////////////////////////////////////////
//fix子类型类型
typedef char FIXSenderSubIDType[32];
#define SenderSubID_abc                     "abc"

///////////////////////////////////////////////////////////////////////////
//fix Unique Trader ID
typedef char FIXOnBehalfOfSubIDType[32];
#define OnBehalfOfSubID_xyz                 "xyz"

///////////////////////////////////////////////////////////////////////////
//订单手动发送类型：Y-手动	N-自动
typedef char FIXManualOrderIndicatorType;
#define ManualOrderIndicatorManual_Y        'Y'

///////////////////////////////////////////////////////////////////////////
//订单发起人的地址
typedef char FIXManualOrderIndicatorType;
#define OrderOriginationID_CN_SH            "CN_SH" //中国上海


///////////////////////////////////////////////////////////////////////////
//合约类型
typedef char FIXSecurityType[32];
//1、合约类型：
// CS: common stock
// FOR: foreign exchange
// FXNDF: foreign exchange non-deliverable forward
// FUT: future
// GOVT: sovereign debt
// IDX: equity index (valid for market data purposes only)
// MLEG: multi-leg
// NRG: energy
// OPT: option
#define SecurityType_CS              "CS"
#define SecurityType_FOR             "FOR"
#define SecurityType_FXNDF           "FXNDF"
#define SecurityType_FUT             "FUT"
#define SecurityType_GOVT            "GOVT"
#define SecurityType_IDX             "IDX"
#define SecurityType_NRG             "NRG"
#define SecurityType_OPT             "OPT"

///////////////////////////////////////////////////////////////////////////
//机构
typedef char FIXExecBroker[32];

/*********************************************************************************************************/

/*** SIR XXXXX BEGIN ***/
//日志等级
const int Log_Level_None      = 0;
const int Log_Level_Emergency = 1;
const int Log_Level_Critical  = 2;
const int Log_Level_Error     = 3;
const int Log_Level_Warning   = 4;
const int Log_Level_Info      = 5;
const int Log_Level_Debug     = 6;
/*** SIR XXXXX END ***/
