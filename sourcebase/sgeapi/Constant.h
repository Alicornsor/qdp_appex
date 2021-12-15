#ifndef CONSTANT_H
#define CONSTANT_H


//�˻����� ������:TAccountType
#define SELF		'0'     //��Ӫ
#define BROKER		'1'     //����

//���������־ ������:TBSFlag
#define BUY		'b'     //��
#define SELL		's'     //��

//��Լ״̬ ������:TInstStateFlag
#define I_INITING		'0'     //��ʼ����
#define I_INIT		'1'     //��ʼ�����
#define I_BEGIN		'2'     //����
#define I_GRP_ORDER		'3'     //���۱���
#define I_GRP_MATCH		'4'     //���۴��
#define I_NORMAL		'5'     //��������
#define I_PAUSE		'6'     //��ͣ
#define I_DERY_APP		'7'     //�����걨
#define I_DERY_MATCH		'8'     //�����걨����
#define I_MID_APP		'9'     //�������걨
#define I_MID_MATCH		'A'     //�����걨���
#define I_END		'B'     //����

//������״̬ ������:TExchangeStateFlag
#define E_INITING		'0'     //��ʼ����
#define E_INIT		'1'     //��ʼ�����
#define E_OPEN		'2'     //����
#define E_CLOSE		'3'     //����
#define E_IN_SETTLE		'4'     //���ڽ���
#define E_SETTLED		'5'     //�������
#define E_T0		'6'     //T+0���������
#define E_UP		'7'     //���յ������

//ע����־ ������:TDestroyFlag
#define VALID		'1'     //��Ч
#define DESTROY		'2'     //ע��
#define SUSPENDED		'3'     //��ͣ

//������־ ������:TInOutFlag
#define DEPOSIT		'i'     //���
#define DRAW		'o'     //����

//�г�״̬ ������:TMarketStateFlag
#define M_INITING		'0'     //��ʼ����
#define M_INIT		'1'     //��ʼ�����
#define M_OPEN		'2'     //����
#define M_TRADE		'3'     //����
#define M_PAUSE		'4'     //��ͣ
#define M_CLOSE		'5'     //����

//��ƽ�ֱ�־ ������:TOffsetFlag
#define P_OPEN		'0'     //����
#define p_OFFSET		'1'     //ƽ��
#define P_FORCE_OFFSET		'2'     //ǿ��ƽ��

//�ǷǱ�־ ������:TOkFlag
#define NO		'0'     //��
#define YES		'1'     //��

//������� ������:TPickupType
#define SELF_PICK		'0'     //����
#define TRADE_PICK		'1'     //����

//�������� ������:TRateType
#define FIXED		'0'     //�̶�ֵ
#define RATIO		'1'     //����

//�ֻ�����Ȩ�� ������:TSpotTradeRight
#define SR_NONE		'0'     //��
#define SR_NORMAL		'1'     //������
#define SR_BUY		'3'     //����
#define SR_SELL		'4'     //����

//����Ȩ�� ������:TTradeRight
#define TR_NONE		'0'     //���ɽ���
#define TR_NORMAL		'1'     //���Խ���
#define TR_LONLY		'2'     //ֻ��ƽ��
#define TR_FORBID_SOPEN		'3'		//��ֹ����
#define TR_FORBID_LOPEN		'4'		//��ֹ����
#define TR_SONLY		'5'		//ֻ������
#define TR_BONLY		'6'		//ֻ������

//���׷�ʽ ������:TTradeType
#define TT_SPOT		's'     //�ֻ�
#define TT_DEFER		'd'     //����
#define TT_FUTURES		'f'     //�ڻ�
#define TT_FORWARD		'w'     //Զ��

//��Ա���� ������:TMemberType
#define HEAD		'0'     //������
#define CONSUMER		'1'     //��ҵ��
#define TRADE		'2'     //ó����
#define PRODUCER		'3'     //����ұ����
#define INVT		'4'     //����Ͷ����
#define OTHER		'5'     //����

//��Ծ��־ ������:TOpenFlag
#define ACTIVE		'1'     //��Ծ
#define DORMANT		'2'     //����Ծ
#define OFFSET_ONLY		'3'     //ֻ��ƽ��
#define OPEN_ONLY		'4'     //ֻ�ɿ���

//����״̬ ������:TOrderStatus
#define OS_NOT_MATCH		'o'     //δ�ɽ�
#define OS_PART_MATCH		'p'     //���ֳɽ�
#define OS_WHOLE_MATCH		'c'     //��ȫ�ɽ�
#define OS_USER_DELETED		'd'     //�û�ɾ��
#define OS_SYS_DELETED		's'     //ϵͳɾ��
#define OS_URGENT_DELETED	'u'     //Ӧ������
#define OS_AUTO_DELETED		'a'     //�Զ�����, FOK/FAK��

//ָ������ ������:TOrderType
#define OT_NORMAL		'0'		//��ͨ
#define OT_FOK			'1'		//FOK
#define OT_FAK			'2'		//FAK

//�Ǽ�״̬ ������:TRegState
#define R_NO_CHECK		'1'     //δ����
#define R_APPROVE		'2'     //����ͨ��
#define R_NO_APPROVED		'3'     //����δͨ��
#define R_DESTROY		'4'     //��ע��

//IC��״̬ ������:TICState
#define IC_ACTIVE		'1'     //����
#define IC_DORMANT		'0'     //δ����

//������� ������:TOperateType
#define OP_ADD		'1'     //���Ӽ�¼
#define OP_UPDATE		'2'     //�޸�
#define OP_DELETE		'3'     //ɾ��
#define OP_QUERY		'4'     //��ѯ
#define OP_LOGIN		'5'     //ע���¼
#define OP_LOGOUT		'6'     //ǩ��
#define OP_OVERTIME		'7'     //��ʱ
#define OP_SINGLE		'8'     //����¼��ѯ
#define OP_CHECK		'9'     //����
#define OP_DESTROY		'0'     //ע��

//Ʒ����� ������:TVarietyType
#define V_GOLD		'1'     //�ƽ�
#define V_PLATINUM		'2'     //�׽�
#define V_SILVER		'3'     //����

//���ӷ�֧������ ������:TPayDirection
#define PD_LONG		'1'     //��֧������
#define PD_SHORT		'2'     //��֧������
#define PD_NONE		'3'     //����δ��

//�������� ������:TConnectType
#define CT_INNER		'C'     //����
#define CT_DIAL		'D'     //�����û�
#define CT_STAT		'S'     //��̬

//�������� ������:TFeeCode
#define FT_TIMES		'1'     //������
#define FT_RATIO		'2'     //���� 
#define FT_FIXED		'3'     //�̶�

//ΥԼ���� ������:TBreachDirect
#define BD_BREACHER		'1'     //ΥԼ��(֧������Ա)
#define BD_BREACHEE		'2'     //��ΥԼ��(�յ���ԱΥԼ��)
#define BD_BREACHEF		'3'     //ΥԼ��(֧����������)

//��Ŀ��� ������:TSubjectType
#define ST_ASSET		'1'     //�ʲ���
#define ST_DEBT		'2'     //��ծ��
#define ST_PROFIT		'3'     //������

//������� ������:TAmountType
#define AT_BREACHER		'D'     //�跽��ӳ
#define AT_BREACHEE		'C'     //������ӳ

//�ʻ�״̬ ������:TAccountState
#define AS_VALID		'1'     //�״̬
#define AS_SUSPENDED		'2'     //�ʻ�����(ֹͣ����)
#define AS_DESTROY		'3'     //����

//͸֧��־ ������:TOverDraftFlag
#define OD_NOT_OVERDRAFT		'1'     //����͸֧
#define OD_OVERDRAFT		'2'     //��͸֧

//�ʻ����� ������:TAccountFtre
#define AF_NOT_INTEREST		'0'     //�Ǽ�Ϣ��
#define AF_INTEREST		'1'     //��Ϣ��

//������־ ������:TOffFlag
#define OF_BLUE		'1'     //��������
#define OF_RED		'2'     //���ֳ���

//ƾ֤���� ������:TBillType
#define BT_BUY		'1'     //����
#define BT_SELL		'2'     //����
#define BT_NORMAL		'3'     //һ�����
#define BT_OFF		'4'     //���ʼ���
#define BT_TRADE		'5'     //��������

//��Ʊ���� ������:TCertType
#define CT_NORMAL		'1'     //һ�㴫Ʊ
#define CT_FINANCE		'2'     //���ղ������
#define CT_OTHER		'3'     //����

//�ֻ��ʴ�ӡҳ���� ������:TPageType
#define PT_PAGE		'1'     //1 ����ҳ 2 ������ 3������
#define PT_MONTH		'2'     //���ղ������
#define PT_YEAR		'3'     //����

//������_�ո���־ ������:TPayFlag
#define PF_PAY		'1'     //����/��/�������������Ա�ʻ�
#define PF_RECEIVED		'2'     //����/��/��Ա�����뽻�����ʻ�
#define PF_DEDUCT		'3'     //��/�����������ۻ�Ա��

//��ƥ������ ������:TDiffType
#define DT_EXCHANGE		'1'     //����������,��������
#define DT_BANK		'2'     //����������,��������
#define DT_PAYFLAG		'3'     //�ո���־ͬ,����������������
#define DT_		'4'     //�ո���־ͬ,������С��������
#define DT_DIFF_PAY		'5'     //�ո���־��ͬ

//�ѷ����־ ������:TSentFlag
#define SF_NO_SEND		'1'     //δ����
#define SF_SEND_RETURN		'2'     //�����ѻ�ִ
#define SF_SENDING		'3'     //��;
#define SF_NO_NEED		'4'     //���ʲ��跢��
#define SF_SEND_FAIL		'5'     //����ʧ��
#define SF_MANUAL_SEND		'6'     //�ֹ�����
#define SF_REPEAT		'7'     //������ˮ������
#define SF_NO_ENOUGH		'8'     //����

//��Ϣ������� ������:TChangeType
#define CT_NEW		'1'     //�¿���
#define CT_ACCOUNT_UPDATE		'2'     //�ʺŵ���Ϣ���
#define CT_DELETE		'3'     //����
#define CT_BANK_UPDATE		'4'     //�����б��

//�����־ ������:THandleFlag
#define HF_NO_UESD		'1'     //δ��������
#define HF_UESD		'2'     //�ѷ�������
#define HF_NO_NEED		'3'     //���跢������

//ԭ�����д����־ ������:TOrigionalHandleFlag
#define OF_NO_SEND		'1'     //δ��������
#define OF_SEND		'2'     //�ѷ�������
#define OF_NO_NEED		'3'     //���跢������

//�����״̬ ������:TDrawSheetState
#define DS_APPLY		'1'     //�������
#define DS_DRAW		'2'     //�����
#define DS_CANCEL		'3'     //��Ա���ճ���
#define DS_NEXT_CANCEL		'4'     //��Ա���ճ���
#define DS_SYS_CANCEL		'5'     //ϵͳ����

//������� ������:TDrawType
#define DT_SELF		'1'     //����
#define DT_TRADE		'2'     //����
#define DT_PART_TRADE		'3'     //���ֽ���

//�����ƻ�״̬ ������:TTransSheetState
#define TS_MADE		'1'     //����
#define TS_TRANSOUT		'2'     //����
#define TS_TRANSIN		'3'     //����
#define TS_CANCEL		'4'     //����

//����ԭ�� ������:TTransferReason
#define TR_LACK		'1'     //��治��
#define TR_LOW		'2'     //��������޶�
#define TR_HIGH		'3'     //��������޶�

//������ʽ ������:TFrozenModel
#define FM_TEMP		'1'     //��ʱ
#define FM_EVER		'2'     //����

//�г����� ������:TMarketType
#define SPOT		's'     //�ֻ�
#define DEFER		'd'     //����
#define FUTURES		'f'     //�ڻ�
#define FORWARD		'w'     //Զ��

//������� ������:TAppType
#define AT_APPLY		'1'     //�����걨
#define AT_MIDDLE		'2'     //������

//��Ӫ���� ������:TBizType
#define BT_FINANCE		'1'     //������
#define BT_COMPERI		'2'     //�ۺ���
#define BT_SINGLE		'3'     //������

//��Ѻ\����걨״̬ ������:TAppState
#define AS_PUTIN		'1'     //��¼��
#define AS_CHECK		'2'     //�Ѹ���
#define AS_COMMIT		'3'     //���ύ
#define AS_CANCEL		'4'     //�ѳ���
#define AS_PARTNER		'5'     //�����
#define AS_APPROVE		'6'     //����ͨ��
#define AS_NO_PASS		'7'     //������ͨ��

//��Ѻ�걨����־ ������:TImpawnApp
#define IA_LOANEE		'1'     //���ʷ�
#define IA_LOANER		'2'     //��Ȩ��

//�ֻ��ɽ����� ������:TSpotMatchType
#define MT_NORMAL		'1'     //��ͨ
#define MT_URGENT		'2'     //Ӧ��
#define MT_LARGE		'3'     //����
#define MT_TPLUS5		'4'     //T+5
#define MT_IMPAWN		'5'     //��Ѻ

//�ͻ����仯���� ������:TTransType
#define TT_DEPOSIT		"1"     //���
#define TT_PICKUPAPP		"2"     //�������
#define TT_PICKUPDATE		"3"     //��������޸�
#define TT_PICKUPCANCEL		"4"     //������볷��
#define TT_SELFDRAW		"5"     //�������
#define TT_TRADEDRAW		"6"     //�������
#define TT_IMPAWNIN		"7"     //��Ѻ����Ȩ����
#define TT_IMPAWNOUT		"8"     //��Ѻ�����ʷ���
#define TT_IMPAWNCANCELIN		"9"     //��Ѻע������Ȩ����
#define TT_IMPAWNCANCELOUT		"A"     //��Ѻע�������ʷ���
#define TT_LEND		"B"     //��裨�����
#define TT_BORROW		"C"     //��裨���룩
#define TT_FROZEN		"D"     //���ɶ���
#define TT_MELT		"E"     //���ɶ���ⶳ
#define TT_BUY		"F"     //�ֻ�����
#define TT_SELL		"G"     //�ֻ�����
#define TT_HANDLE		"H"     //��������
#define TT_INDIFF		"I"     //������
#define TT_OUTDIFF		"J"     //�������
#define TT_DRAW		"K"     //����
#define TT_LARGEBUY		"M"     //���ڽ�������
#define TT_LARGESELL		"N"     //���ڽ�������
#define TT_SHIFTOUT		"O"     //�������
#define TT_SHIFTIN		"P"     //������
#define TT_ADD		"Q"     //���������͸֧
#define TT_REDUCE		"R"     //�������������
#define TT_NSELL		"S"     //�Ǽ�������
#define TT_NBUY		"T"     //�Ǽ�������
#define TT_MORROWCANCEL	"U"		//���ճ����������
#define TT_SYSCANCEL	"V"		//ϵͳ�����������
#define TT_TRANSIN		"X"		//��������
#define TT_TRANSOUT		"W"		//�������
#define TT_IQSELL		"0"		//ѯ������
#define TT_IQBUY		"L"		//ѯ������
#define TT_RETURN		"Y"		//���(����)
#define TT_RECEIVE		"Z"		//���(�ս�)
#define TT_INPAWNMOVE	"10"		//������ת��

//�������� ������:TSheetType
#define ST_DEPOSIT		'1'     //��ⵥ
#define ST_DRAW		'2'     //���ⵥ
#define ST_TRANSFEROUT		'3'     //�������ⵥ

//��Ա��־ ������:TMemberFlag
#define MF_NORMAL		'1'     //��ͨ��Ա
#define MF_SEPCIAL		'2'     //�����Ա

//��Ϣ���� ������:TSettleType
#define ST_SINGLE		'0'     //������Ϣ
#define ST_AMOUNT		'1'     //������Ϣ

//���״̬ ������:TDDstate
#define DD_DEPOSIT		'0'     //����
#define DD_DRAW		'1'     //���

//������λ ������:TUnitID
#define UI_G		"01"     //��
#define UI_KG		"02"     //ǧ��
#define UI_OUNCE		"03"     //��˾

//�ʺű�־ ������:TAccountFlag
#define AF_GO		'0'     //����ר����
#define AF_OTHER		'1'     //�����ʺ�

//��շ��� ������:TDirection
#define LS_LONG		'1'     //��
#define LS_SHORT		'0'     //��

//����״̬��־ ������:TCheckFlag
#define CF_UNCHECK		'1'     //δ����
#define CF_CHECKED		'2'     //�Ѹ���
#define CF_CANCEL		'3'     //��ע��
#define CF_NOPASS		'4'     //δͨ��

//֤������ ������:TCerType
#define CT_IDENTITY		'1'     //���֤
#define CT_PASSPORT		'2'     //����

//����ת���־ ������:TTurnInFlag
#define TF_MANU		"100"     //�ֹ�¼��
#define TF_AUTO		"200"     //�Զ�ת��

//¼���־ ������:TInputFlag
#define IF_BILL_MANU		"100"     //�ֹ�ƾ֤¼��
#define IF_INST_ACC_ADJST		"110"     //��Ϣ��������
#define IF_AUTO_TPLUS0		"210"     //�Զ�ת��:T+0����
#define IF_AUTO_TPLUS0_MKTMKR		"211"     //�Զ�ת��:T+0���������̱�֤����
#define IF_OVER_REFUND		"250"     //��ֵ�������׷�ӿۿ�
#define IF_STRM_CACUL_INST		"261"     //������Ϣ�뱣֤��
#define IF_SNGLE_CACUL_INST		"262"     //������Ϣ�뱣֤��
#define IF_DEPOSIT_ACCNT		"300"     //����/���� �뱣֤��
#define IF_DEPOSIT_PAY		"313"     //���ʱ�֤��ۻ�ԱӦ����
#define IF_CPTL_CLR		"350"     //�ʽ𻮳������㲿����
#define IF_CPTL_MEMBR		"351"     //�ʽ𻮳�����Ա�˷���

//�������� ������:TMisFeeCode
#define CO_DELRY		"1"     //�ִ���
#define CO_OVERDUE		"2"     //���ڲ�����
#define CO_DEFER		"3"     //���ӷ�
#define CO_TRANSPORT		"4"     //�˱���
#define CO_INSURANCE		"5"     //���շ�
#define CO_PAPER		"6"     //������
#define CO_BULLION_MARGIN		"7"     //��������ˮ
#define CO_DELIVERY		"8"     //����������
#define CO_BREACH_EX		"9"     //��������ȡ����ΥԼ��
#define CO_BREACH_MEMBER		"10"     //��Ա�յ�/֧���Ľ���ΥԼ��
#define CO_DELRY_DIFF		"11"     //���
#define CO_VARIETY_MARGIN		"12"     //Ʒ������ˮ
#define CO_IMPAWN_REG		"13"     //��Ѻ�ǼǷ�
#define CO_RENT_REG		"14"     //���ǼǷ�
#define CO_BREACH_OFF		"15"     //��Ա�յ�/֧����ƽ��ΥԼ��

//ҵ������ ������:TBizSort
#define BS_0		"00"     //�ֹ�ת���ʽ�
#define BS_1		"01"     //�ֹ�ת���ʽ�
#define BS_2		"02"     //�ֹ�����
#define BS_3		"03"     //�ֹ��ⶳ
#define BS_4		"04"     //���𶳽�
#define BS_5		"05"     //����ⶳ
#define BS_6		"06"     //�ֻ����뱨������
#define BS_7		"07"     //�ֻ��ֹ������ⶳ
#define BS_8		"08"     //�ֻ�ϵͳ�����ⶳ
#define BS_9		"09"     //T+N��������
#define BS_10		"10"     //T+N�ֹ������ⶳ
#define BS_11		"11"     //T+Nϵͳ�����ⶳ
#define BS_12		"12"     //���ڽ��ձ�������
#define BS_13		"13"     //���ڽ����ֹ������ⶳ
#define BS_14		"14"     //���ڽ���ϵͳ�����ⶳ
#define BS_15		"15"     //�ڻ���������
#define BS_16		"16"     //�ڻ��ֹ������ⶳ
#define BS_17		"17"     //�ڻ�ϵͳ�����ⶳ
#define BS_18		"18"     //�ֻ��ɽ���
#define BS_19		"19"     //T+N����ռ��
#define BS_20		"20"     //T+Nת���ͷ�
#define BS_21		"21"     //���ڽ��տ���ռ��
#define BS_22		"22"     //���ڽ���ƽ���ͷ�
#define BS_23		"23"     //�ڻ�����ռ��
#define BS_24		"24"     //�ڻ�ƽ���ͷ�
#define BS_25		"25"     //������֤������
#define BS_26		"26"     //������֤�����
#define BS_27		"27"     //�Զ�����
#define BS_28		"28"     //�ֹ�����(���㲿)
#define BS_29		"29"     //�ֹ�����
#define BS_30		"30"     //�ֹ�����(��Ա��)
#define BS_31		"31"     //���綳��
#define BS_32		"32"     //����ⶳ
#define BS_33		"33"     //��Ϣת��
#define BS_34		"34"     //���˵ֿ����ڿ�
#define BS_35		"35"     //���˵ֿ�Ӧ�տ�
#define BS_36		"36"     //T+Nǿƽ�ͷ�
#define BS_37		"37"     //���ڽ���ǿƽ�ͷ�
#define BS_38		"37"     //�ڻ�ǿƽ�ͷ�
#define BS_39		"39"     //�ֻ�Ӧ����������
#define BS_40		"40"     //�ֻ�Ӧ�������ⶳ
#define BS_41		"41"     //T+NӦ����������
#define BS_42		"42"     //T+NӦ�������ⶳ
#define BS_43		"43"     //���ڽ���Ӧ����������
#define BS_44		"44"     //���ڽ���Ӧ�������ⶳ
#define BS_45		"45"     //�ڻ�Ӧ����������
#define BS_46		"46"     //�ڻ�Ӧ�������ⶳ
#define BS_47		"47"     //T+0����
#define BS_48		"48"     //�����̻�ԱӦ����
#define BS_49		"49"     //�����̻�ԱӦ�տ�

//��ͣ��־ ������:TStopFlag
#define SF_START		'1'     //����
#define SF_PAUSE		'2'     //��ͣ

//�����Ա��־ ������:TSpecialFlag
#define SF_MKTMKR		"002"     //������
#define SF_BANK		"003"     //���л�Ա
#define SF_PRODUCER		"004"     //����λ
#define SF_COMSUMER		"005"     //�ý�λ
#define SF_PRODUCT		"006"     //ұ����
#define SF_CNTBANK		"001"     //������������
#define SF_HCBC		"102"     //�������й���
#define SF_ABC		"103"     //��������ũ��
#define SF_BOC		"104"     //������������
#define SF_PCBC		"105"     //�������н���
#define SF_EXCHANGE		"999"     //������
#define SF_WAREHOUSE		"200"     //�ֿ�

//�ɽ����� ������:TMatchType
#define MT_NORMAL		'1'     //��ͨ
#define MT_URGENT		'2'     //Ӧ��
#define MT_MORT		'3'     //������Ѻ

//����ⶳ��־ ������:TFrozenFlag
#define FF_FROZEN		'0'     //����
#define FF_MELT		'1'     //�ⶳ

//������ˮ¼���־ ������:TToDoTxInputFlag
#define TODO_MANU_INPUT		"100"     //���㲿�ֹ�¼��
#define TODO_AUTO_INSERT		"200"     //�����Զ�����
#define TODO_MEM_INSERT		"300"     //��Ա���ֹ�¼��

//�����˱������� ������:TTransPackType
#define QD01		"QD01"     //ǩ��
#define QD11		"QD11"     //ǩ��
#define QD02		"QD02"     //ǩ��
#define QD12		"QD12"     //ǩ��
#define HZ01		"HZ01"     //����(����)
#define HZ11		"HZ11"     //����(����)
#define HZ02		"HZ02"     //����(����)
#define HZ12		"HZ12"     //����(����)
#define HZ03		"HZ03"     //�ۿ�
#define HZ13		"HZ13"     //�ۿ�
#define CX01		"CX01"     //����
#define CX11		"CX11"     //����
#define KH01		"KH01"     //��ԱǩԼ������Ϣ�Ǽ�
#define KH11		"KH11"     //��ԱǩԼ������Ϣ�Ǽ�
#define KH02		"KH02"     //��Ա����
#define KH12		"KH12"     //��Ա����
#define KH03		"KH03"     //�ɻ�Ա�����Ϣ����
#define KH13		"KH13"     //�ɻ�Ա�����Ϣ����
#define TZ01		"TZ01"     //֪ͨ
#define TZ11		"TZ11"     //֪ͨ
#define CX02		"CX02"     //���ʽ��
#define CX12		"CX12"     //���ʽ��

//���˱������� ������:TCheckPackType
#define DZSJ		"DZSJ"     //��������
#define DZHZ		"DZHZ"     //���ʻ�ִ

//�ƽ�ⶳ��־ ������:TMeltFlag
#define MF_FROST		'1'     //����
#define MF_PARTMELT		'2'     //���ֽⶳ
#define MF_ALLMELT		'3'     //ȫ���ⶳ

//����걨����־ ������:TLeaseApp
#define LA_LENDER		'1'     //�����
#define LA_BORROWER		'2'     //���뷽

//������� ������:TDepositType
#define DT_NONE		'0'     //�Ǽ�Ϣ��
#define DT_CURRENT		'1'     //���ڴ��
#define DT_SAME		'2'     //���ͬҵ

//���ʱ�־ ������:TToDoTxEnrolFlag
#define EF_NONE		'1'     //δ����
#define EF_FROZEN_SUCC		'2'     //����ǰ����ɹ�
#define EF_ENROL_SUCC		'3'     //����ɹ����ʳɹ�
#define EF_ENROL_FAIL		'4'     //����ɹ�����ʧ��
#define EF_UN_SUCC		'5'     //����ʧ�ܽⶳ�ɹ�
#define EF_UN_FAIL		'6'     //����ʧ�ܽⶳʧ��
#define EF_REPEAT		'7'     //����

//����Ա���� ������:TOperatorType
#define ADMIN		'1'     //����Ա
#define MONITOR		'2'     //���Ա

//�������� ������:TStoreBillType
#define OUT_BILL		'0'     //���ⵥ
#define IN_BILL		'1'     //��ⵥ
#define TRANS_BILL		'2'     //�������ⵥ

//�ͻ���� ������:TClientSort
#define LAWMAN		'1'     //����
#define NATUREMAN		'2'     //��Ȼ��

//���������� ������:TSubFeeCode
#define TRADE_STORE		"11"     //�����Ȩ
#define WH_STORE		"12"     //ʣ����
#define OUT_STORE		"13"     //����
#define TP_IN		"41"     //���(���ڽ���)
#define TP_OUT_TX		"42"     //����
#define TP_SYS_CANCEL		"43"     //ϵͳ����
#define TP_MEM_CANCEL		"44"     //��Ա���ճ���
#define TP_IN_OTHER		"45"     //���(�Ǽ��ڽ���)
#define IN_DIFF		"B1"     //������(���ڽ���)
#define OUT_DIFF		"B2"     //�������(����ǰ)
#define IN_DIFF_OTHER		"B3"     //������(�Ǽ��ڽ���)
#define OUT_DIFF_AFT		"B4"     //�������(���պ�)

//�������޶����� ������:TLimitType
#define LM_NUM		'0'     //����
#define LM_AMT		'1'     //���

//�������� ������:TReportType
#define RPT_QS		"QS"     //���㱨��
#define RPT_CP		"CP"     //��Ʊ
#define RPT_KJ		"KJ"     //���
#define RPT_TJ		"TJ"     //ͳ�Ʊ���

//����Ƶ�� ������:TReportPeriod
#define PD_NO		"00"     //����
#define PD_DAY		"01"     //�ձ�
#define PD_MONTH		"02"     //�±�
#define PD_YEAR		"03"     //�걨

//���ó��� ������:TCommon
#define CM_UNIVERSAL_CODE		"$"     //ͨ���

//���������˱�־ ������:TEnrolFlag
#define EF_SUCCESS		'1'     //�ɹ�
#define EF_NOT		'2'     //δ����
#define EF_FAIL		'3'     //����ʧ��

//������� ������:TRateDepositType
#define RDT_CURRENT		'1'     //���ڴ��
#define RDT_SAME		'2'     //���ͬҵ

//�ֿ���仯���� ������:TWarehouseTransType
#define TW_DEPOSIT		'1'     //���
#define TW_PICKUPAPP		'2'     //�������
#define TW_PICKUPDATE		'3'     //��������޸�
#define TW_PICKUPCANCEL		'4'     //������볷��
#define TW_DRAW		'5'     //����
#define TW_TRANSFEROUT		'6'     //��������
#define TW_TRANSFERIN		'7'     //�������

//����������״̬ ������:TBankComeGoStatus
#define STATUS_COMPLETE		'1'     //���
#define STATUS_DOING		'2'     //������
#define STATUS_UNDO		'3'     //δ��ʼ

//���շ��� ������:TGRFlag
#define GIVE		'b'     //��
#define RECV		's'     //��

//�г�����Ȩ�� ������:TMarketRight
#define MR_NONE		'0'     //���ɽ���
#define MR_NORMAL		'1'     //���Խ���

//�ͻ���� ������:TCode
#define ST_CORP		'1'		//����
#define ST_PERSON	'2'		//��Ȼ��

//���Ա���� ������:TMonitorType
#define MT_TRADE	'1'		//���׼��
#define MT_TECH		'2'		//������ѯ
#define MT_LEAD		'3'		//�쵼��ѯ

#endif
