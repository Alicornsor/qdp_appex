#ifndef CONSTANT_H
#define CONSTANT_H


//账户类型 变量名:TAccountType
#define SELF		'0'     //自营
#define BROKER		'1'     //代理

//买卖方向标志 变量名:TBSFlag
#define BUY		'b'     //买
#define SELL		's'     //卖

//合约状态 变量名:TInstStateFlag
#define I_INITING		'0'     //初始化中
#define I_INIT		'1'     //初始化完成
#define I_BEGIN		'2'     //开盘
#define I_GRP_ORDER		'3'     //竞价报单
#define I_GRP_MATCH		'4'     //竞价撮合
#define I_NORMAL		'5'     //连续交易
#define I_PAUSE		'6'     //暂停
#define I_DERY_APP		'7'     //交割申报
#define I_DERY_MATCH		'8'     //交割申报结束
#define I_MID_APP		'9'     //中立仓申报
#define I_MID_MATCH		'A'     //交割申报撮合
#define I_END		'B'     //收盘

//交易所状态 变量名:TExchangeStateFlag
#define E_INITING		'0'     //初始化中
#define E_INIT		'1'     //初始化完成
#define E_OPEN		'2'     //开市
#define E_CLOSE		'3'     //收市
#define E_IN_SETTLE		'4'     //正在结算
#define E_SETTLED		'5'     //结算完成
#define E_T0		'6'     //T+0财务处理完成
#define E_UP		'7'     //日终登账完成

//注销标志 变量名:TDestroyFlag
#define VALID		'1'     //有效
#define DESTROY		'2'     //注销
#define SUSPENDED		'3'     //暂停

//出入金标志 变量名:TInOutFlag
#define DEPOSIT		'i'     //入金
#define DRAW		'o'     //出金

//市场状态 变量名:TMarketStateFlag
#define M_INITING		'0'     //初始化中
#define M_INIT		'1'     //初始化完成
#define M_OPEN		'2'     //开市
#define M_TRADE		'3'     //交易
#define M_PAUSE		'4'     //暂停
#define M_CLOSE		'5'     //收市

//开平仓标志 变量名:TOffsetFlag
#define P_OPEN		'0'     //开仓
#define p_OFFSET		'1'     //平仓
#define P_FORCE_OFFSET		'2'     //强行平仓

//是非标志 变量名:TOkFlag
#define NO		'0'     //否
#define YES		'1'     //是

//提货性质 变量名:TPickupType
#define SELF_PICK		'0'     //自提
#define TRADE_PICK		'1'     //交提

//比率类型 变量名:TRateType
#define FIXED		'0'     //固定值
#define RATIO		'1'     //比率

//现货交易权限 变量名:TSpotTradeRight
#define SR_NONE		'0'     //否
#define SR_NORMAL		'1'     //可买卖
#define SR_BUY		'3'     //可买
#define SR_SELL		'4'     //可卖

//交易权限 变量名:TTradeRight
#define TR_NONE		'0'     //不可交易
#define TR_NORMAL		'1'     //可以交易
#define TR_LONLY		'2'     //只可平仓
#define TR_FORBID_SOPEN		'3'		//禁止开空
#define TR_FORBID_LOPEN		'4'		//禁止开多
#define TR_SONLY		'5'		//只可卖出
#define TR_BONLY		'6'		//只可买入

//交易方式 变量名:TTradeType
#define TT_SPOT		's'     //现货
#define TT_DEFER		'd'     //递延
#define TT_FUTURES		'f'     //期货
#define TT_FORWARD		'w'     //远期

//会员类型 变量名:TMemberType
#define HEAD		'0'     //首饰类
#define CONSUMER		'1'     //工业类
#define TRADE		'2'     //贸易类
#define PRODUCER		'3'     //产金冶炼类
#define INVT		'4'     //金融投资类
#define OTHER		'5'     //其他

//活跃标志 变量名:TOpenFlag
#define ACTIVE		'1'     //活跃
#define DORMANT		'2'     //不活跃
#define OFFSET_ONLY		'3'     //只可平仓
#define OPEN_ONLY		'4'     //只可开仓

//报单状态 变量名:TOrderStatus
#define OS_NOT_MATCH		'o'     //未成交
#define OS_PART_MATCH		'p'     //部分成交
#define OS_WHOLE_MATCH		'c'     //完全成交
#define OS_USER_DELETED		'd'     //用户删除
#define OS_SYS_DELETED		's'     //系统删除
#define OS_URGENT_DELETED	'u'     //应急撤单
#define OS_AUTO_DELETED		'a'     //自动撤单, FOK/FAK等

//指令类型 变量名:TOrderType
#define OT_NORMAL		'0'		//普通
#define OT_FOK			'1'		//FOK
#define OT_FAK			'2'		//FAK

//登记状态 变量名:TRegState
#define R_NO_CHECK		'1'     //未审批
#define R_APPROVE		'2'     //审批通过
#define R_NO_APPROVED		'3'     //审批未通过
#define R_DESTROY		'4'     //已注销

//IC卡状态 变量名:TICState
#define IC_ACTIVE		'1'     //激活
#define IC_DORMANT		'0'     //未激活

//操作类别 变量名:TOperateType
#define OP_ADD		'1'     //增加记录
#define OP_UPDATE		'2'     //修改
#define OP_DELETE		'3'     //删除
#define OP_QUERY		'4'     //查询
#define OP_LOGIN		'5'     //注册登录
#define OP_LOGOUT		'6'     //签退
#define OP_OVERTIME		'7'     //超时
#define OP_SINGLE		'8'     //单记录查询
#define OP_CHECK		'9'     //复核
#define OP_DESTROY		'0'     //注销

//品种类别 变量名:TVarietyType
#define V_GOLD		'1'     //黄金
#define V_PLATINUM		'2'     //白金
#define V_SILVER		'3'     //白银

//递延费支付方向 变量名:TPayDirection
#define PD_LONG		'1'     //多支付给空
#define PD_SHORT		'2'     //空支付给多
#define PD_NONE		'3'     //方向未定

//上网类型 变量名:TConnectType
#define CT_INNER		'C'     //场务
#define CT_DIAL		'D'     //拨号用户
#define CT_STAT		'S'     //静态

//费用类型 变量名:TFeeCode
#define FT_TIMES		'1'     //按笔数
#define FT_RATIO		'2'     //比率 
#define FT_FIXED		'3'     //固定

//违约方向 变量名:TBreachDirect
#define BD_BREACHER		'1'     //违约方(支付给会员)
#define BD_BREACHEE		'2'     //被违约方(收到会员违约金)
#define BD_BREACHEF		'3'     //违约方(支付给交易所)

//科目类别 变量名:TSubjectType
#define ST_ASSET		'1'     //资产类
#define ST_DEBT		'2'     //负债类
#define ST_PROFIT		'3'     //损益类

//余额性质 变量名:TAmountType
#define AT_BREACHER		'D'     //借方反映
#define AT_BREACHEE		'C'     //贷方反映

//帐户状态 变量名:TAccountState
#define AS_VALID		'1'     //活动状态
#define AS_SUSPENDED		'2'     //帐户冻结(停止交易)
#define AS_DESTROY		'3'     //销户

//透支标志 变量名:TOverDraftFlag
#define OD_NOT_OVERDRAFT		'1'     //不可透支
#define OD_OVERDRAFT		'2'     //可透支

//帐户性质 变量名:TAccountFtre
#define AF_NOT_INTEREST		'0'     //非计息户
#define AF_INTEREST		'1'     //计息户

//冲正标志 变量名:TOffFlag
#define OF_BLUE		'1'     //正常蓝字
#define OF_RED		'2'     //红字冲正

//凭证种类 变量名:TBillType
#define BT_BUY		'1'     //买入
#define BT_SELL		'2'     //卖出
#define BT_NORMAL		'3'     //一般记帐
#define BT_OFF		'4'     //销帐记帐
#define BT_TRADE		'5'     //买卖记帐

//传票类型 变量名:TCertType
#define CT_NORMAL		'1'     //一般传票
#define CT_FINANCE		'2'     //代收财务费用
#define CT_OTHER		'3'     //其他

//分户帐打印页类型 变量名:TPageType
#define PT_PAGE		'1'     //1 承上页 2 承上月 3承上年
#define PT_MONTH		'2'     //代收财务费用
#define PT_YEAR		'3'     //其他

//往来帐_收付标志 变量名:TPayFlag
#define PF_PAY		'1'     //往帐/付/交易所划款入会员帐户
#define PF_RECEIVED		'2'     //来帐/收/会员划款入交易所帐户
#define PF_DEDUCT		'3'     //扣/交易所主动扣会员帐

//不匹配类型 变量名:TDiffType
#define DT_EXCHANGE		'1'     //交易所端有,清算行无
#define DT_BANK		'2'     //交易所端无,清算行有
#define DT_PAYFLAG		'3'     //收付标志同,交易所大于清算行
#define DT_		'4'     //收付标志同,交易所小于清算行
#define DT_DIFF_PAY		'5'     //收付标志不同

//已发电标志 变量名:TSentFlag
#define SF_NO_SEND		'1'     //未发电
#define SF_SEND_RETURN		'2'     //发电已回执
#define SF_SENDING		'3'     //在途
#define SF_NO_NEED		'4'     //来帐不需发电
#define SF_SEND_FAIL		'5'     //发电失败
#define SF_MANUAL_SEND		'6'     //手工发电
#define SF_REPEAT		'7'     //往帐流水号重帐
#define SF_NO_ENOUGH		'8'     //余额不足

//信息变更类型 变量名:TChangeType
#define CT_NEW		'1'     //新开户
#define CT_ACCOUNT_UPDATE		'2'     //帐号等信息变更
#define CT_DELETE		'3'     //销户
#define CT_BANK_UPDATE		'4'     //清算行变更

//处理标志 变量名:THandleFlag
#define HF_NO_UESD		'1'     //未发电启用
#define HF_UESD		'2'     //已发电启用
#define HF_NO_NEED		'3'     //不需发电启用

//原清算行处理标志 变量名:TOrigionalHandleFlag
#define OF_NO_SEND		'1'     //未发电销户
#define OF_SEND		'2'     //已发电销户
#define OF_NO_NEED		'3'     //不需发电销户

//提货单状态 变量名:TDrawSheetState
#define DS_APPLY		'1'     //申请提货
#define DS_DRAW		'2'     //已提货
#define DS_CANCEL		'3'     //会员当日撤单
#define DS_NEXT_CANCEL		'4'     //会员次日撤单
#define DS_SYS_CANCEL		'5'     //系统撤单

//提货类型 变量名:TDrawType
#define DT_SELF		'1'     //自提
#define DT_TRADE		'2'     //交提
#define DT_PART_TRADE		'3'     //部分交提

//调拨计划状态 变量名:TTransSheetState
#define TS_MADE		'1'     //制作
#define TS_TRANSOUT		'2'     //调出
#define TS_TRANSIN		'3'     //调入
#define TS_CANCEL		'4'     //撤销

//调拨原因 变量名:TTransferReason
#define TR_LACK		'1'     //库存不足
#define TR_LOW		'2'     //低于最高限额
#define TR_HIGH		'3'     //超出最高限额

//冻结形式 变量名:TFrozenModel
#define FM_TEMP		'1'     //暂时
#define FM_EVER		'2'     //永久

//市场类型 变量名:TMarketType
#define SPOT		's'     //现货
#define DEFER		'd'     //递延
#define FUTURES		'f'     //期货
#define FORWARD		'w'     //远期

//交割单类型 变量名:TAppType
#define AT_APPLY		'1'     //交割申报
#define AT_MIDDLE		'2'     //中立仓

//经营性质 变量名:TBizType
#define BT_FINANCE		'1'     //金融类
#define BT_COMPERI		'2'     //综合类
#define BT_SINGLE		'3'     //单项类

//质押\租借申报状态 变量名:TAppState
#define AS_PUTIN		'1'     //已录入
#define AS_CHECK		'2'     //已复核
#define AS_COMMIT		'3'     //已提交
#define AS_CANCEL		'4'     //已撤销
#define AS_PARTNER		'5'     //已配对
#define AS_APPROVE		'6'     //审批通过
#define AS_NO_PASS		'7'     //审批不通过

//质押申报方标志 变量名:TImpawnApp
#define IA_LOANEE		'1'     //出质方
#define IA_LOANER		'2'     //质权方

//现货成交类型 变量名:TSpotMatchType
#define MT_NORMAL		'1'     //普通
#define MT_URGENT		'2'     //应急
#define MT_LARGE		'3'     //大宗
#define MT_TPLUS5		'4'     //T+5
#define MT_IMPAWN		'5'     //质押

//客户库存变化类型 变量名:TTransType
#define TT_DEPOSIT		"1"     //入库
#define TT_PICKUPAPP		"2"     //提货申请
#define TT_PICKUPDATE		"3"     //提货申请修改
#define TT_PICKUPCANCEL		"4"     //提货申请撤销
#define TT_SELFDRAW		"5"     //自提出库
#define TT_TRADEDRAW		"6"     //交提出库
#define TT_IMPAWNIN		"7"     //质押（质权方）
#define TT_IMPAWNOUT		"8"     //质押（出质方）
#define TT_IMPAWNCANCELIN		"9"     //质押注销（质权方）
#define TT_IMPAWNCANCELOUT		"A"     //质押注销（出质方）
#define TT_LEND		"B"     //租借（借出）
#define TT_BORROW		"C"     //租借（借入）
#define TT_FROZEN		"D"     //法律冻结
#define TT_MELT		"E"     //法律冻结解冻
#define TT_BUY		"F"     //现货买入
#define TT_SELL		"G"     //现货卖出
#define TT_HANDLE		"H"     //处置质物
#define TT_INDIFF		"I"     //入库溢短
#define TT_OUTDIFF		"J"     //出库溢短
#define TT_DRAW		"K"     //出库
#define TT_LARGEBUY		"M"     //大宗交易买入
#define TT_LARGESELL		"N"     //大宗交易卖出
#define TT_SHIFTOUT		"O"     //划出库存
#define TT_SHIFTIN		"P"     //划入库存
#define TT_ADD		"Q"     //充抵做市商透支
#define TT_REDUCE		"R"     //减做市商入库库存
#define TT_NSELL		"S"     //非即期卖出
#define TT_NBUY		"T"     //非即期买入
#define TT_MORROWCANCEL	"U"		//次日撤销提货申请
#define TT_SYSCANCEL	"V"		//系统撤销提货申请
#define TT_TRANSIN		"X"		//调拨出库
#define TT_TRANSOUT		"W"		//调拨入库
#define TT_IQSELL		"0"		//询价卖出
#define TT_IQBUY		"L"		//询价买入
#define TT_RETURN		"Y"		//租借(还金)
#define TT_RECEIVE		"Z"		//租借(收金)
#define TT_INPAWNMOVE	"10"		//质物库存转移

//单据类型 变量名:TSheetType
#define ST_DEPOSIT		'1'     //入库单
#define ST_DRAW		'2'     //出库单
#define ST_TRANSFEROUT		'3'     //调拨出库单

//会员标志 变量名:TMemberFlag
#define MF_NORMAL		'1'     //普通会员
#define MF_SEPCIAL		'2'     //特殊会员

//结息类型 变量名:TSettleType
#define ST_SINGLE		'0'     //单户结息
#define ST_AMOUNT		'1'     //批量结息

//块号状态 变量名:TDDstate
#define DD_DEPOSIT		'0'     //存入
#define DD_DRAW		'1'     //提出

//重量单位 变量名:TUnitID
#define UI_G		"01"     //克
#define UI_KG		"02"     //千克
#define UI_OUNCE		"03"     //盎司

//帐号标志 变量名:TAccountFlag
#define AF_GO		'0'     //往账专用帐
#define AF_OTHER		'1'     //其他帐号

//多空方向 变量名:TDirection
#define LS_LONG		'1'     //多
#define LS_SHORT		'0'     //空

//复核状态标志 变量名:TCheckFlag
#define CF_UNCHECK		'1'     //未复核
#define CF_CHECKED		'2'     //已复核
#define CF_CANCEL		'3'     //已注销
#define CF_NOPASS		'4'     //未通过

//证件类型 变量名:TCerType
#define CT_IDENTITY		'1'     //身份证
#define CT_PASSPORT		'2'     //护照

//数据转入标志 变量名:TTurnInFlag
#define TF_MANU		"100"     //手工录入
#define TF_AUTO		"200"     //自动转入

//录入标志 变量名:TInputFlag
#define IF_BILL_MANU		"100"     //手工凭证录入
#define IF_INST_ACC_ADJST		"110"     //利息积数调整
#define IF_AUTO_TPLUS0		"210"     //自动转帐:T+0处理
#define IF_AUTO_TPLUS0_MKTMKR		"211"     //自动转帐:T+0处理做市商保证金处理
#define IF_OVER_REFUND		"250"     //市值计算亏损追加扣款
#define IF_STRM_CACUL_INST		"261"     //批量结息入保证金
#define IF_SNGLE_CACUL_INST		"262"     //单户结息入保证金
#define IF_DEPOSIT_ACCNT		"300"     //来帐/到帐 入保证金
#define IF_DEPOSIT_PAY		"313"     //来帐保证金扣会员应付款
#define IF_CPTL_CLR		"350"     //资金划出：清算部发起
#define IF_CPTL_MEMBR		"351"     //资金划出：会员端发起

//费用类型 变量名:TMisFeeCode
#define CO_DELRY		"1"     //仓储费
#define CO_OVERDUE		"2"     //超期补偿费
#define CO_DEFER		"3"     //递延费
#define CO_TRANSPORT		"4"     //运保费
#define CO_INSURANCE		"5"     //保险费
#define CO_PAPER		"6"     //手续费
#define CO_BULLION_MARGIN		"7"     //条块升贴水
#define CO_DELIVERY		"8"     //交割手续费
#define CO_BREACH_EX		"9"     //交易所收取交割违约金
#define CO_BREACH_MEMBER		"10"     //会员收到/支付的交割违约金
#define CO_DELRY_DIFF		"11"     //溢短
#define CO_VARIETY_MARGIN		"12"     //品种升贴水
#define CO_IMPAWN_REG		"13"     //质押登记费
#define CO_RENT_REG		"14"     //租借登记费
#define CO_BREACH_OFF		"15"     //会员收到/支付的平仓违约金

//业务类型 变量名:TBizSort
#define BS_0		"00"     //手工转出资金
#define BS_1		"01"     //手工转入资金
#define BS_2		"02"     //手工冻结
#define BS_3		"03"     //手工解冻
#define BS_4		"04"     //铂金冻结
#define BS_5		"05"     //铂金解冻
#define BS_6		"06"     //现货买入报单冻结
#define BS_7		"07"     //现货手工撤单解冻
#define BS_8		"08"     //现货系统撤单解冻
#define BS_9		"09"     //T+N报单冻结
#define BS_10		"10"     //T+N手工撤单解冻
#define BS_11		"11"     //T+N系统撤单解冻
#define BS_12		"12"     //延期交收报单冻结
#define BS_13		"13"     //延期交收手工撤单解冻
#define BS_14		"14"     //延期交收系统撤单解冻
#define BS_15		"15"     //期货报单冻结
#define BS_16		"16"     //期货手工撤单解冻
#define BS_17		"17"     //期货系统撤单解冻
#define BS_18		"18"     //现货成交款
#define BS_19		"19"     //T+N开仓占用
#define BS_20		"20"     //T+N转让释放
#define BS_21		"21"     //延期交收开仓占用
#define BS_22		"22"     //延期交收平仓释放
#define BS_23		"23"     //期货开仓占用
#define BS_24		"24"     //期货平仓释放
#define BS_25		"25"     //基础保证金增加
#define BS_26		"26"     //基础保证金减少
#define BS_27		"27"     //自动来账
#define BS_28		"28"     //手工往账(结算部)
#define BS_29		"29"     //手工来账
#define BS_30		"30"     //手工往账(会员端)
#define BS_31		"31"     //发电冻结
#define BS_32		"32"     //发电解冻
#define BS_33		"33"     //利息转入
#define BS_34		"34"     //来账抵扣逾期款
#define BS_35		"35"     //来账抵扣应收款
#define BS_36		"36"     //T+N强平释放
#define BS_37		"37"     //延期交收强平释放
#define BS_38		"37"     //期货强平释放
#define BS_39		"39"     //现货应急报单冻结
#define BS_40		"40"     //现货应急撤单解冻
#define BS_41		"41"     //T+N应急报单冻结
#define BS_42		"42"     //T+N应急撤单解冻
#define BS_43		"43"     //延期交收应急报单冻结
#define BS_44		"44"     //延期交收应急撤单解冻
#define BS_45		"45"     //期货应急报单冻结
#define BS_46		"46"     //期货应急撤单解冻
#define BS_47		"47"     //T+0处理
#define BS_48		"48"     //做市商会员应付款
#define BS_49		"49"     //做市商会员应收款

//暂停标志 变量名:TStopFlag
#define SF_START		'1'     //启用
#define SF_PAUSE		'2'     //暂停

//特殊会员标志 变量名:TSpecialFlag
#define SF_MKTMKR		"002"     //做市商
#define SF_BANK		"003"     //银行会员
#define SF_PRODUCER		"004"     //产金单位
#define SF_COMSUMER		"005"     //用金单位
#define SF_PRODUCT		"006"     //冶炼厂
#define SF_CNTBANK		"001"     //电子联行央行
#define SF_HCBC		"102"     //电子联行工行
#define SF_ABC		"103"     //电子联行农行
#define SF_BOC		"104"     //电子联行中行
#define SF_PCBC		"105"     //电子联行建行
#define SF_EXCHANGE		"999"     //交易所
#define SF_WAREHOUSE		"200"     //仓库

//成交类型 变量名:TMatchType
#define MT_NORMAL		'1'     //普通
#define MT_URGENT		'2'     //应急
#define MT_MORT		'3'     //处置质押

//冻结解冻标志 变量名:TFrozenFlag
#define FF_FROZEN		'0'     //冻结
#define FF_MELT		'1'     //解冻

//发电流水录入标志 变量名:TToDoTxInputFlag
#define TODO_MANU_INPUT		"100"     //清算部手工录入
#define TODO_AUTO_INSERT		"200"     //开工自动插入
#define TODO_MEM_INSERT		"300"     //会员端手工录入

//往来账报文类型 变量名:TTransPackType
#define QD01		"QD01"     //签到
#define QD11		"QD11"     //签到
#define QD02		"QD02"     //签退
#define QD12		"QD12"     //签退
#define HZ01		"HZ01"     //往帐(付款)
#define HZ11		"HZ11"     //往帐(付款)
#define HZ02		"HZ02"     //来帐(到帐)
#define HZ12		"HZ12"     //来帐(到帐)
#define HZ03		"HZ03"     //扣款
#define HZ13		"HZ13"     //扣款
#define CX01		"CX01"     //对帐
#define CX11		"CX11"     //对帐
#define KH01		"KH01"     //会员签约开户信息登记
#define KH11		"KH11"     //会员签约开户信息登记
#define KH02		"KH02"     //会员销户
#define KH12		"KH12"     //会员销户
#define KH03		"KH03"     //旧会员变更信息启用
#define KH13		"KH13"     //旧会员变更信息启用
#define TZ01		"TZ01"     //通知
#define TZ11		"TZ11"     //通知
#define CX02		"CX02"     //对帐结果
#define CX12		"CX12"     //对帐结果

//对账报文类型 变量名:TCheckPackType
#define DZSJ		"DZSJ"     //对帐数据
#define DZHZ		"DZHZ"     //对帐回执

//黄金解冻标志 变量名:TMeltFlag
#define MF_FROST		'1'     //冻结
#define MF_PARTMELT		'2'     //部分解冻
#define MF_ALLMELT		'3'     //全部解冻

//租借申报方标志 变量名:TLeaseApp
#define LA_LENDER		'1'     //借出方
#define LA_BORROWER		'2'     //借入方

//存款种类 变量名:TDepositType
#define DT_NONE		'0'     //非计息户
#define DT_CURRENT		'1'     //活期存款
#define DT_SAME		'2'     //存放同业

//入帐标志 变量名:TToDoTxEnrolFlag
#define EF_NONE		'1'     //未处理
#define EF_FROZEN_SUCC		'2'     //发电前冻结成功
#define EF_ENROL_SUCC		'3'     //发电成功入帐成功
#define EF_ENROL_FAIL		'4'     //发电成功入帐失败
#define EF_UN_SUCC		'5'     //发电失败解冻成功
#define EF_UN_FAIL		'6'     //发电失败解冻失败
#define EF_REPEAT		'7'     //重帐

//操作员类型 变量名:TOperatorType
#define ADMIN		'1'     //管理员
#define MONITOR		'2'     //监控员

//单据类型 变量名:TStoreBillType
#define OUT_BILL		'0'     //出库单
#define IN_BILL		'1'     //入库单
#define TRANS_BILL		'2'     //调拨出库单

//客户类别 变量名:TClientSort
#define LAWMAN		'1'     //法人
#define NATUREMAN		'2'     //自然人

//费用子类型 变量名:TSubFeeCode
#define TRADE_STORE		"11"     //买入货权
#define WH_STORE		"12"     //剩余库存
#define OUT_STORE		"13"     //出库
#define TP_IN		"41"     //入库(即期交易)
#define TP_OUT_TX		"42"     //出库
#define TP_SYS_CANCEL		"43"     //系统撤单
#define TP_MEM_CANCEL		"44"     //会员次日撤单
#define TP_IN_OTHER		"45"     //入库(非即期交易)
#define IN_DIFF		"B1"     //入库溢短(即期交易)
#define OUT_DIFF		"B2"     //出库溢短(日终前)
#define IN_DIFF_OTHER		"B3"     //入库溢短(非即期交易)
#define OUT_DIFF_AFT		"B4"     //出库溢短(日终后)

//做市商限额类型 变量名:TLimitType
#define LM_NUM		'0'     //数量
#define LM_AMT		'1'     //金额

//报表类型 变量名:TReportType
#define RPT_QS		"QS"     //清算报表
#define RPT_CP		"CP"     //传票
#define RPT_KJ		"KJ"     //会计
#define RPT_TJ		"TJ"     //统计报表

//报表频度 变量名:TReportPeriod
#define PD_NO		"00"     //不限
#define PD_DAY		"01"     //日报
#define PD_MONTH		"02"     //月报
#define PD_YEAR		"03"     //年报

//共用常量 变量名:TCommon
#define CM_UNIVERSAL_CODE		"$"     //通配符

//往来帐入账标志 变量名:TEnrolFlag
#define EF_SUCCESS		'1'     //成功
#define EF_NOT		'2'     //未入帐
#define EF_FAIL		'3'     //入账失败

//存款种类 变量名:TRateDepositType
#define RDT_CURRENT		'1'     //活期存款
#define RDT_SAME		'2'     //存放同业

//仓库库存变化类型 变量名:TWarehouseTransType
#define TW_DEPOSIT		'1'     //入库
#define TW_PICKUPAPP		'2'     //提货申请
#define TW_PICKUPDATE		'3'     //提货申请修改
#define TW_PICKUPCANCEL		'4'     //提货申请撤销
#define TW_DRAW		'5'     //出库
#define TW_TRANSFEROUT		'6'     //调拨出库
#define TW_TRANSFERIN		'7'     //调拨入库

//清算行往来状态 变量名:TBankComeGoStatus
#define STATUS_COMPLETE		'1'     //完成
#define STATUS_DOING		'2'     //进行中
#define STATUS_UNDO		'3'     //未开始

//交收方向 变量名:TGRFlag
#define GIVE		'b'     //交
#define RECV		's'     //收

//市场交易权限 变量名:TMarketRight
#define MR_NONE		'0'     //不可交易
#define MR_NORMAL		'1'     //可以交易

//客户类别 变量名:TCode
#define ST_CORP		'1'		//法人
#define ST_PERSON	'2'		//自然人

//监控员类型 变量名:TMonitorType
#define MT_TRADE	'1'		//交易监控
#define MT_TECH		'2'		//技术查询
#define MT_LEAD		'3'		//领导查询

#endif
