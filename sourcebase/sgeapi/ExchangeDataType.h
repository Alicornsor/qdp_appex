/* Freemarker自动生成代码
 * 文件名：ExchangeDataType.h
 * 语言：C++
 * 更新日期：2014-10-16 10:53:53
 */
#ifndef __EXCHANGE_DATA_TYPE_H
#define __EXCHANGE_DATA_TYPE_H
#include "ByteArray.h"

#ifndef __XTP__STDTYPE__
#define __XTP__STDTYPE__
typedef unsigned char	BYTE;
typedef unsigned short	WORD;
typedef unsigned long	DWORD;
typedef char			INT1;
typedef short			INT2;
typedef int				INT4;
typedef unsigned int	UINT;
typedef float			REAL4;
typedef double			REAL8;
#endif

#define TRSPCODE_SIZE			20
typedef BYTEARRAY<20>			TRspCode;			//
#define TRSPMSG_SIZE			40
typedef BYTEARRAY<40>			TRspMsg;			//
#define TCOMMMODE_SIZE			4
typedef BYTEARRAY<4>			TCommMode;			//
#define TABBR_SIZE			20
typedef BYTEARRAY<20>			TAbbr;			//名称简称
typedef int			TMachineID;			//账户类型
typedef BYTE			TAccountType;			//账户类型
#define TACTORID_SIZE			3
typedef BYTEARRAY<3>			TActorID;			//角色代码
#define TADDRESS_SIZE			80
typedef BYTEARRAY<80>			TAddress;			//地址
typedef double			TAlloy;			//成色
#define TBANKACCOUNTID_SIZE			16
typedef BYTEARRAY<16>			TBankAccountID;			//银行帐号
#define TBANKID_SIZE			3
typedef BYTEARRAY<3>			TBankID;			//银行代码
#define TBANKTRANSSEQNO_SIZE			19
typedef BYTEARRAY<19>			TBankTransSeqNo;			//银行流水号
#define TBOXNO_SIZE			10
typedef BYTEARRAY<10>			TBoxNo;			//箱号
typedef BYTE			TBSFlag;			//买卖方向标志
#define TBULLIONNO_SIZE			12
typedef BYTEARRAY<12>			TBullionNo;			//黄金块号
#define TCERTIFICATENO_SIZE			20
typedef BYTEARRAY<20>			TCertificateNo;			//证件号码
#define TCIPHER_SIZE			20
typedef BYTEARRAY<20>			TCipher;			//密押
#define TCLIENTID_SIZE			12
typedef BYTEARRAY<12>			TClientID;			//客户代码
#define TCODE_SIZE			4
typedef BYTEARRAY<4>			TCode;			//公用代码类型
#define TINSTID_SIZE			8
typedef BYTEARRAY<8>			TInstID;			//合约代码
#define TINSTNAME_SIZE			12
typedef BYTEARRAY<12>			TInstName;			//合约名称
typedef BYTE			TInstStateFlag;			//合约状态
typedef int			TInstUnit;			//交易单位数量
#define TDATE_SIZE			8
typedef BYTEARRAY<8>			TDate;			//日期
#define TDEPOSITSHEETNO_SIZE			14
typedef BYTEARRAY<14>			TDepositSheetNo;			//入库单编号
typedef BYTE			TDirection;			//多空方向
#define TDRAWSHEETNO_SIZE			14
typedef BYTEARRAY<14>			TDrawSheetNo;			//出库单编号
#define TEXCHANGEID_SIZE			6
typedef BYTEARRAY<6>			TExchangeID;			//交易所代码
typedef BYTE			TExchangeStateFlag;			//交易所运行状态标志
typedef BYTE			TDestroyFlag;			//注销标志
#define TICCARDNO_SIZE			10
typedef BYTEARRAY<10>			TICCardNo;			//IC卡编号
typedef BYTE			TInOutFlag;			//出入金标志
#define TLOCALNO_SIZE			14
typedef BYTEARRAY<14>			TLocalNo;			//本地报单号
#define TMARKETID_SIZE			2
typedef BYTEARRAY<2>			TMarketID;			//市场代码
#define TMARKETNAME_SIZE			20
typedef BYTEARRAY<20>			TMarketName;			//市场名称
typedef BYTE			TMarketStateFlag;			//市场状态
#define TMATCHNO_SIZE			16
typedef BYTEARRAY<16>			TMatchNo;			//成交编号
#define TMEMBERID_SIZE			6
typedef BYTEARRAY<6>			TMemberID;			//会员代码
#define TMODULEID_SIZE			8
typedef BYTEARRAY<8>			TModuleID;			//模块代码
typedef double			TMoney;			//金额
#define TNAME_SIZE			40
typedef BYTEARRAY<40>			TName;			//名称
#define TLONGNAME_SIZE			80
typedef BYTEARRAY<80>			TLongName;			//长名称
typedef BYTE			TOffsetFlag;			//开平仓标志
typedef BYTE			TOkFlag;			//是非标志
#define TORDERNO_SIZE			16
typedef BYTEARRAY<16>			TOrderNo;			//报单号
#define TPASSWORD_SIZE			8
typedef BYTEARRAY<8>			TPassword;			//密码
#define TPHONEREGION_SIZE			10
typedef BYTEARRAY<10>			TPhoneRegion;			//单位电话区号
#define TPHONENO_SIZE			30
typedef BYTEARRAY<30>			TPhoneNo;			//电话
#define TPICKUPSHEETNO_SIZE			14
typedef BYTEARRAY<14>			TPickupSheetNo;			//提货单编号
typedef BYTE			TPickupType;			//提货性质
#define TPOSTCODE_SIZE			6
typedef BYTEARRAY<6>			TPostCode;			//邮政编码
typedef double			TPrice;			//价格
typedef double			TRate;			//比率
typedef BYTE			TRateType;			//比率类型
typedef int			TSequence;			//序列号
#define TSORT_SIZE			3
typedef BYTEARRAY<3>			TSort;			//公用代码类别
#define TSUBJECTID_SIZE			4
typedef BYTEARRAY<4>			TSubjectID;			//科目代码
#define TTIME_SIZE			8
typedef BYTEARRAY<8>			TTime;			//时间
#define TTRADERID_SIZE			10
typedef BYTEARRAY<10>			TTraderID;			//交易员代码
typedef BYTE			TTradeRight;			//交易权限
typedef BYTE			TMarketRight;			//市场交易权限
typedef BYTE			TSpotTradeRight;			//现货交易权限
typedef BYTE			TTradeType;			//交易方式
#define TTRANSNO_SIZE			16
typedef BYTEARRAY<16>			TTransNo;			//银行交易流水号
#define TUNITID_SIZE			2
typedef BYTEARRAY<2>			TUnitID;			//重量单位
#define TVARIETYID_SIZE			3
typedef BYTEARRAY<3>			TVarietyID;			//交割品种代码
typedef int			TVolume;			//数量
#define TWAREHOUSEID_SIZE			4
typedef BYTEARRAY<4>			TWarehouseID;			//仓库代码
typedef double			TWeight;			//重量
#define TMEMBERNAME_SIZE			40
typedef BYTEARRAY<40>			TMemberName;			//会员名称
#define TCLIENTNAME_SIZE			40
typedef BYTEARRAY<40>			TClientName;			//客户名称
#define TWAREHOUSENAME_SIZE			40
typedef BYTEARRAY<40>			TWarehouseName;			//仓库名称
#define TCERTAINMANID_SIZE			4
typedef BYTEARRAY<4>			TCertainManID;			//指定存货人员代码
#define TEMAIL_SIZE			50
typedef BYTEARRAY<50>			TEmail;			//电子邮件
#define TPERSONNAME_SIZE			20
typedef BYTEARRAY<20>			TPersonName;			//人名
#define TDEPTID_SIZE			4
typedef BYTEARRAY<4>			TDeptID;			//部门代码
#define TREGIONCODE_SIZE			6
typedef BYTEARRAY<6>			TRegionCode;			//地区代码
typedef BYTE			TMemberType;			//会员类型
typedef BYTE			TOpenFlag;			//活跃标志
typedef BYTE			TOrderStatus;			//报单状态
#define TPHONEREGIN_SIZE			10
typedef BYTEARRAY<10>			TPhoneRegin;			//电话区号
typedef BYTE			TClassID;			//会员级别代码
#define TACCOUNTCODE_SIZE			14
typedef BYTEARRAY<14>			TAccountCode;			//账号
#define TTRANSFERINSHEETNO_SIZE			16
typedef BYTEARRAY<16>			TTransferInSheetNo;			//调拨入库单编号
#define TTRANSFEROUTSHEETNO_SIZE			16
typedef BYTEARRAY<16>			TTransferOutSheetNo;			//调拨出库单编号
#define TTRANSFERSHEETNO_SIZE			14
typedef BYTEARRAY<14>			TTransferSheetNo;			//调拨单编号
#define TFROZENSHEETNO_SIZE			8
typedef BYTEARRAY<8>			TFrozenSheetNo;			//冻结单编号
#define TMELTSHEETNO_SIZE			8
typedef BYTEARRAY<8>			TMeltSheetNo;			//解冻单编号
typedef BYTE			TRegState;			//登记状态
#define TENTERPRISECODE_SIZE			1
typedef BYTEARRAY<1>			TEnterpriseCode;			//企业代码
#define TBULLIONWEIGHTID_SIZE			4
typedef BYTEARRAY<4>			TBullionWeightID;			//条块重量代码
#define TESCORTCOMPANYID_SIZE			6
typedef BYTEARRAY<6>			TEscortCompanyID;			//代理运输公司代码
#define TESCORTID_SIZE			6
typedef BYTEARRAY<6>			TEscortID;			//押运员代码
#define TLETTERPD_SIZE			17
typedef BYTEARRAY<17>			TLetterPd;			//密码信封序列号
typedef BYTE			TICState;			//IC卡状态
#define TWEBADDR_SIZE			254
typedef BYTEARRAY<254>			TWebAddr;			//Web地址
typedef double			TParaValue;			//参数值
#define TOPERATETYPE_SIZE			2
typedef BYTEARRAY<2>			TOperateType;			//操作类别
#define TABSTRACT_SIZE			254
typedef BYTEARRAY<254>			TAbstract;			//操作功能说明
#define TBIIZSORT_SIZE			8
typedef BYTEARRAY<8>			TBiizSort;			//业务类别
#define TBIZCODE_SIZE			10
typedef BYTEARRAY<10>			TBizCode;			//业务代码
typedef BYTE			TVarietyType;			//品种类别
typedef BYTE			TPayDirection;			//支付方向
typedef BYTE			TConnectType;			//上网类型
#define TIPADDRESS_SIZE			30
typedef BYTEARRAY<30>			TIpAddress;			//IP地址
typedef BYTE			TFeeCode;			//费用类型
#define TRETURNFLAG_SIZE			4
typedef BYTEARRAY<4>			TReturnFlag;			//回执标志
typedef BYTE			TBreachDirect;			//违约方向
typedef BYTE			TSubjectType;			//科目类别
typedef BYTE			TAmountType;			//余额性质
typedef BYTE			TAccountState;			//帐户状态
typedef BYTE			TOverDraftFlag;			//透支标志
typedef BYTE			TAccountFtre;			//帐户性质(计息类型)
typedef BYTE			TOffFlag;			//冲正标志
typedef BYTE			TBillType;			//凭证种类
#define TBILLNO_SIZE			10
typedef BYTEARRAY<10>			TBillNo;			//凭证号码
typedef BYTE			TCertType;			//传票类型
typedef BYTE			TPageType;			//分户帐打印页类型
typedef BYTE			TPayFlag;			//往来帐_收付标志
#define TTRANSPACKTYPE_SIZE			4
typedef BYTEARRAY<4>			TTransPackType;			//报文类型
#define TCHECKPACKTYPE_SIZE			4
typedef BYTEARRAY<4>			TCheckPackType;			//报文类型
#define TBANKACCOUNT_SIZE			30
typedef BYTEARRAY<30>			TBankAccount;			//银行专用帐号
typedef BYTE			TDiffType;			//不匹配类型
typedef BYTE			TSentFlag;			//已发电标志
#define TORGANIZATIONID_SIZE			18
typedef BYTEARRAY<18>			TOrganizationID;			//机构代码
#define TLINKBANKNO_SIZE			5
typedef BYTEARRAY<5>			TLinkBankNo;			//联行行号
#define TSUBACCOUNTNO_SIZE			3
typedef BYTEARRAY<3>			TSubAccountNo;			//会员清算帐号分签号
typedef BYTE			TChangeType;			//信息变更类型
typedef BYTE			THandleFlag;			//处理标志
typedef BYTE			TOrigionalHandleFlag;			//原清算行处理标志
#define TDRAWREASON_SIZE			20
typedef BYTEARRAY<20>			TDrawReason;			//提出原因
typedef BYTE			TDDstate;			//块号状态
typedef BYTE			TDrawSheetState;			//提货单状态
typedef BYTE			TDrawType;			//提货类型
typedef BYTE			TTransSheetState;			//调拨计划状态
typedef BYTE			TTransferReason;			//调拨原因
typedef BYTE			TFrozenReason;			//冻结原因
typedef BYTE			TFrozenModel;			//冻结形式
typedef BYTE			TMarketType;			//市场类型
typedef BYTE			TAppType;			//交割单类型
typedef BYTE			TBizType;			//经营性质
#define TFEEID_SIZE			4
typedef BYTEARRAY<4>			TFeeID;			//费用代码
#define TCONTRACTNO_SIZE			20
typedef BYTEARRAY<20>			TContractNo;			//质押合约编号
#define TLOANNO_SIZE			20
typedef BYTEARRAY<20>			TLoanNo;			//贷款合约编号
#define TIMPAWNAPPNO_SIZE			8
typedef BYTEARRAY<8>			TImpawnAppNo;			//质押申报编号
typedef BYTE			TAppState;			//质押\租借申报状态
typedef BYTE			TOrigApp;			//原始申报方标志
typedef BYTE			TSpotMatchType;			//现货成交类型
typedef BYTE			TMatchType;			//成交类型
typedef int			TSubstituteNo;			//替代序号
#define TMEMO_SIZE			1024
typedef BYTEARRAY<1024>			TMemo;			//备注
#define TLEASEAPPNO_SIZE			8
typedef BYTEARRAY<8>			TLeaseAppNo;			//租借申报编号
#define TIMPAWNREGNO_SIZE			10
typedef BYTEARRAY<10>			TImpawnRegNo;			//质押登记编号
#define TLEASEREGNO_SIZE			10
typedef BYTEARRAY<10>			TLeaseRegNo;			//租借登记编号
#define TREMINDCODE_SIZE			10
typedef BYTEARRAY<10>			TRemindCode;			//摘要助记代码
#define TSPECIALFLAG_SIZE			3
typedef BYTEARRAY<3>			TSpecialFlag;			//特殊会员标志
#define TTYPECODE_SIZE			10
typedef BYTEARRAY<10>			TTypeCode;			//分类码
typedef BYTE			TCodeFlag;			//代码标志
#define TFROZENTYPE_SIZE			2
typedef BYTEARRAY<2>			TFrozenType;			//冻结类型
#define TMELTTYPE_SIZE			2
typedef BYTEARRAY<2>			TMeltType;			//解冻类型
#define TSHEETNO_SIZE			16
typedef BYTEARRAY<16>			TSheetNo;			//单据编号
typedef BYTE			TTransType;			//库存变化类型
#define TMARKID_SIZE			4
typedef BYTEARRAY<4>			TMarkID;			//牌号代码
#define TBULLIONCODE_SIZE			4
typedef BYTEARRAY<4>			TBullionCode;			//条块代码
typedef BYTE			TSheetType;			//单据类型
typedef BYTE			TMemberFlag;			//会员标志
#define TINPUTFLAG_SIZE			3
typedef BYTEARRAY<3>			TInputFlag;			//录入标志
#define TOBVERSEID_SIZE			10
typedef BYTEARRAY<10>			TObverseID;			//标识代码
#define TCMDCODE_SIZE			10
typedef BYTEARRAY<10>			TCmdCode;			//命令代码
#define TCONTENT_SIZE			2000
typedef BYTEARRAY<2000>			TContent;			//命令代码
typedef BYTE			TSettleType;			//结息类型
typedef BYTE			TCheckFlag;			//复核状态标志
typedef BYTE			TAccountFlag;			//帐号标志
#define TBANKNO_SIZE			6
typedef BYTEARRAY<6>			TBankNo;			//对帐行号
#define TNODENO_SIZE			6
typedef BYTEARRAY<6>			TNodeNo;			//对帐站号
#define TBIZSORT_SIZE			2
typedef BYTEARRAY<2>			TBizSort;			//业务类型
#define TTURNINFLAG_SIZE			3
typedef BYTEARRAY<3>			TTurnInFlag;			//数据转入标志
#define TCERTYPE_SIZE			4
typedef BYTEARRAY<4>			TCerType;			//证件类型
typedef BYTE			TStopFlag;			//暂停标志
#define TIMPAWNLOGOUTAPPNO_SIZE			10
typedef BYTEARRAY<10>			TImpawnLogoutAppNo;			//质押注销申报编号
#define TTODOTXINPUTFLAG_SIZE			3
typedef BYTEARRAY<3>			TToDoTxInputFlag;			//录入标志
typedef BYTE			TDepositType;			//存款种类
#define TBASEFUNDTYPE_SIZE			2
typedef BYTEARRAY<2>			TBaseFundType;			//基础保证金分类表
typedef BYTE			TOperatorType;			//操作员类型
typedef BYTE			TLimitType;			//限额类型
#define TPERMISSIONID_SIZE			60
typedef BYTEARRAY<60>			TPermissionID;			//模块编号
#define TSUMMARY_SIZE			300
typedef BYTEARRAY<300>			TSummary;			//API安全认证域
#define TCERT_SIZE			1500
typedef BYTEARRAY<1500>			TCert;			//API安全认证域
#define TSINGNDATA_SIZE			300
typedef BYTEARRAY<300>			TSingnData;			//API安全认证域
#define TICSERIAL_SIZE			30
typedef BYTEARRAY<30>			TICSerial;			//API安全认证域
#define TRANDSERIAL_SIZE			20
typedef BYTEARRAY<20>			TRandSerial;			//API安全认证域
#define TICPASSWORD_SIZE			8
typedef BYTEARRAY<8>			TICPassword;			//API安全认证域
typedef BYTE			TMonitorType;			//监控员类型
#define TVERSIONINFO_SIZE			16
typedef BYTEARRAY<16>			TVersionInfo;			//版本号
typedef BYTE			TEffectState;			//生效状态
#define TENCRYPTPWD_SIZE			60
typedef BYTEARRAY<60>			TEncryptPwd;			//加密的密码
#define TSECURITYID_SIZE			10
typedef BYTEARRAY<10>			TSecurityID;			//投资者证券账户
#define TPBU_SIZE			6
typedef BYTEARRAY<6>			TPBU;			//投资者指定市场参与者代码
#define TINSTRUMENTID_SIZE			6
typedef BYTEARRAY<6>			TInstrumentId;			//黄金ETF产品代码
#define TETFSHARE_SIZE			16
typedef BYTEARRAY<16>			TEtfShare;			//黄金ETF份额
#define TETFTRADINGNO_SIZE			16
typedef BYTEARRAY<16>			TEtfTradingNo;			//金交所ETF交易编号
typedef BYTE			TIsOK;			//成功失败标志
#define TSSE_PROCESSINGRESULT_SIZE			5
typedef BYTEARRAY<5>			TSSE_ProcessingResult;			//上交所处理结果代码
#define TSSE_DESCRIPTION_SIZE			40
typedef BYTEARRAY<40>			TSSE_Description;			//上交所处理结果简要描述
#define TETFTRADETYPE_SIZE			3
typedef BYTEARRAY<3>			TETFTradeType;			//ETF交易类型
#define TTRANSFERNO_SIZE			16
typedef BYTEARRAY<16>			TTransferNo;			//过户单编号
typedef BYTE			TIsOK_GO;			//成功失败标志-拆借平台
typedef BYTE			TTransfertype;			//过户目的
typedef BYTE			TOrderType;			//指令类型



#endif
