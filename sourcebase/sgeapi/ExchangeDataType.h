/* Freemarker�Զ����ɴ���
 * �ļ�����ExchangeDataType.h
 * ���ԣ�C++
 * �������ڣ�2014-10-16 10:53:53
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
typedef BYTEARRAY<20>			TAbbr;			//���Ƽ��
typedef int			TMachineID;			//�˻�����
typedef BYTE			TAccountType;			//�˻�����
#define TACTORID_SIZE			3
typedef BYTEARRAY<3>			TActorID;			//��ɫ����
#define TADDRESS_SIZE			80
typedef BYTEARRAY<80>			TAddress;			//��ַ
typedef double			TAlloy;			//��ɫ
#define TBANKACCOUNTID_SIZE			16
typedef BYTEARRAY<16>			TBankAccountID;			//�����ʺ�
#define TBANKID_SIZE			3
typedef BYTEARRAY<3>			TBankID;			//���д���
#define TBANKTRANSSEQNO_SIZE			19
typedef BYTEARRAY<19>			TBankTransSeqNo;			//������ˮ��
#define TBOXNO_SIZE			10
typedef BYTEARRAY<10>			TBoxNo;			//���
typedef BYTE			TBSFlag;			//���������־
#define TBULLIONNO_SIZE			12
typedef BYTEARRAY<12>			TBullionNo;			//�ƽ���
#define TCERTIFICATENO_SIZE			20
typedef BYTEARRAY<20>			TCertificateNo;			//֤������
#define TCIPHER_SIZE			20
typedef BYTEARRAY<20>			TCipher;			//��Ѻ
#define TCLIENTID_SIZE			12
typedef BYTEARRAY<12>			TClientID;			//�ͻ�����
#define TCODE_SIZE			4
typedef BYTEARRAY<4>			TCode;			//���ô�������
#define TINSTID_SIZE			8
typedef BYTEARRAY<8>			TInstID;			//��Լ����
#define TINSTNAME_SIZE			12
typedef BYTEARRAY<12>			TInstName;			//��Լ����
typedef BYTE			TInstStateFlag;			//��Լ״̬
typedef int			TInstUnit;			//���׵�λ����
#define TDATE_SIZE			8
typedef BYTEARRAY<8>			TDate;			//����
#define TDEPOSITSHEETNO_SIZE			14
typedef BYTEARRAY<14>			TDepositSheetNo;			//��ⵥ���
typedef BYTE			TDirection;			//��շ���
#define TDRAWSHEETNO_SIZE			14
typedef BYTEARRAY<14>			TDrawSheetNo;			//���ⵥ���
#define TEXCHANGEID_SIZE			6
typedef BYTEARRAY<6>			TExchangeID;			//����������
typedef BYTE			TExchangeStateFlag;			//����������״̬��־
typedef BYTE			TDestroyFlag;			//ע����־
#define TICCARDNO_SIZE			10
typedef BYTEARRAY<10>			TICCardNo;			//IC�����
typedef BYTE			TInOutFlag;			//������־
#define TLOCALNO_SIZE			14
typedef BYTEARRAY<14>			TLocalNo;			//���ر�����
#define TMARKETID_SIZE			2
typedef BYTEARRAY<2>			TMarketID;			//�г�����
#define TMARKETNAME_SIZE			20
typedef BYTEARRAY<20>			TMarketName;			//�г�����
typedef BYTE			TMarketStateFlag;			//�г�״̬
#define TMATCHNO_SIZE			16
typedef BYTEARRAY<16>			TMatchNo;			//�ɽ����
#define TMEMBERID_SIZE			6
typedef BYTEARRAY<6>			TMemberID;			//��Ա����
#define TMODULEID_SIZE			8
typedef BYTEARRAY<8>			TModuleID;			//ģ�����
typedef double			TMoney;			//���
#define TNAME_SIZE			40
typedef BYTEARRAY<40>			TName;			//����
#define TLONGNAME_SIZE			80
typedef BYTEARRAY<80>			TLongName;			//������
typedef BYTE			TOffsetFlag;			//��ƽ�ֱ�־
typedef BYTE			TOkFlag;			//�ǷǱ�־
#define TORDERNO_SIZE			16
typedef BYTEARRAY<16>			TOrderNo;			//������
#define TPASSWORD_SIZE			8
typedef BYTEARRAY<8>			TPassword;			//����
#define TPHONEREGION_SIZE			10
typedef BYTEARRAY<10>			TPhoneRegion;			//��λ�绰����
#define TPHONENO_SIZE			30
typedef BYTEARRAY<30>			TPhoneNo;			//�绰
#define TPICKUPSHEETNO_SIZE			14
typedef BYTEARRAY<14>			TPickupSheetNo;			//��������
typedef BYTE			TPickupType;			//�������
#define TPOSTCODE_SIZE			6
typedef BYTEARRAY<6>			TPostCode;			//��������
typedef double			TPrice;			//�۸�
typedef double			TRate;			//����
typedef BYTE			TRateType;			//��������
typedef int			TSequence;			//���к�
#define TSORT_SIZE			3
typedef BYTEARRAY<3>			TSort;			//���ô������
#define TSUBJECTID_SIZE			4
typedef BYTEARRAY<4>			TSubjectID;			//��Ŀ����
#define TTIME_SIZE			8
typedef BYTEARRAY<8>			TTime;			//ʱ��
#define TTRADERID_SIZE			10
typedef BYTEARRAY<10>			TTraderID;			//����Ա����
typedef BYTE			TTradeRight;			//����Ȩ��
typedef BYTE			TMarketRight;			//�г�����Ȩ��
typedef BYTE			TSpotTradeRight;			//�ֻ�����Ȩ��
typedef BYTE			TTradeType;			//���׷�ʽ
#define TTRANSNO_SIZE			16
typedef BYTEARRAY<16>			TTransNo;			//���н�����ˮ��
#define TUNITID_SIZE			2
typedef BYTEARRAY<2>			TUnitID;			//������λ
#define TVARIETYID_SIZE			3
typedef BYTEARRAY<3>			TVarietyID;			//����Ʒ�ִ���
typedef int			TVolume;			//����
#define TWAREHOUSEID_SIZE			4
typedef BYTEARRAY<4>			TWarehouseID;			//�ֿ����
typedef double			TWeight;			//����
#define TMEMBERNAME_SIZE			40
typedef BYTEARRAY<40>			TMemberName;			//��Ա����
#define TCLIENTNAME_SIZE			40
typedef BYTEARRAY<40>			TClientName;			//�ͻ�����
#define TWAREHOUSENAME_SIZE			40
typedef BYTEARRAY<40>			TWarehouseName;			//�ֿ�����
#define TCERTAINMANID_SIZE			4
typedef BYTEARRAY<4>			TCertainManID;			//ָ�������Ա����
#define TEMAIL_SIZE			50
typedef BYTEARRAY<50>			TEmail;			//�����ʼ�
#define TPERSONNAME_SIZE			20
typedef BYTEARRAY<20>			TPersonName;			//����
#define TDEPTID_SIZE			4
typedef BYTEARRAY<4>			TDeptID;			//���Ŵ���
#define TREGIONCODE_SIZE			6
typedef BYTEARRAY<6>			TRegionCode;			//��������
typedef BYTE			TMemberType;			//��Ա����
typedef BYTE			TOpenFlag;			//��Ծ��־
typedef BYTE			TOrderStatus;			//����״̬
#define TPHONEREGIN_SIZE			10
typedef BYTEARRAY<10>			TPhoneRegin;			//�绰����
typedef BYTE			TClassID;			//��Ա�������
#define TACCOUNTCODE_SIZE			14
typedef BYTEARRAY<14>			TAccountCode;			//�˺�
#define TTRANSFERINSHEETNO_SIZE			16
typedef BYTEARRAY<16>			TTransferInSheetNo;			//������ⵥ���
#define TTRANSFEROUTSHEETNO_SIZE			16
typedef BYTEARRAY<16>			TTransferOutSheetNo;			//�������ⵥ���
#define TTRANSFERSHEETNO_SIZE			14
typedef BYTEARRAY<14>			TTransferSheetNo;			//���������
#define TFROZENSHEETNO_SIZE			8
typedef BYTEARRAY<8>			TFrozenSheetNo;			//���ᵥ���
#define TMELTSHEETNO_SIZE			8
typedef BYTEARRAY<8>			TMeltSheetNo;			//�ⶳ�����
typedef BYTE			TRegState;			//�Ǽ�״̬
#define TENTERPRISECODE_SIZE			1
typedef BYTEARRAY<1>			TEnterpriseCode;			//��ҵ����
#define TBULLIONWEIGHTID_SIZE			4
typedef BYTEARRAY<4>			TBullionWeightID;			//������������
#define TESCORTCOMPANYID_SIZE			6
typedef BYTEARRAY<6>			TEscortCompanyID;			//�������乫˾����
#define TESCORTID_SIZE			6
typedef BYTEARRAY<6>			TEscortID;			//Ѻ��Ա����
#define TLETTERPD_SIZE			17
typedef BYTEARRAY<17>			TLetterPd;			//�����ŷ����к�
typedef BYTE			TICState;			//IC��״̬
#define TWEBADDR_SIZE			254
typedef BYTEARRAY<254>			TWebAddr;			//Web��ַ
typedef double			TParaValue;			//����ֵ
#define TOPERATETYPE_SIZE			2
typedef BYTEARRAY<2>			TOperateType;			//�������
#define TABSTRACT_SIZE			254
typedef BYTEARRAY<254>			TAbstract;			//��������˵��
#define TBIIZSORT_SIZE			8
typedef BYTEARRAY<8>			TBiizSort;			//ҵ�����
#define TBIZCODE_SIZE			10
typedef BYTEARRAY<10>			TBizCode;			//ҵ�����
typedef BYTE			TVarietyType;			//Ʒ�����
typedef BYTE			TPayDirection;			//֧������
typedef BYTE			TConnectType;			//��������
#define TIPADDRESS_SIZE			30
typedef BYTEARRAY<30>			TIpAddress;			//IP��ַ
typedef BYTE			TFeeCode;			//��������
#define TRETURNFLAG_SIZE			4
typedef BYTEARRAY<4>			TReturnFlag;			//��ִ��־
typedef BYTE			TBreachDirect;			//ΥԼ����
typedef BYTE			TSubjectType;			//��Ŀ���
typedef BYTE			TAmountType;			//�������
typedef BYTE			TAccountState;			//�ʻ�״̬
typedef BYTE			TOverDraftFlag;			//͸֧��־
typedef BYTE			TAccountFtre;			//�ʻ�����(��Ϣ����)
typedef BYTE			TOffFlag;			//������־
typedef BYTE			TBillType;			//ƾ֤����
#define TBILLNO_SIZE			10
typedef BYTEARRAY<10>			TBillNo;			//ƾ֤����
typedef BYTE			TCertType;			//��Ʊ����
typedef BYTE			TPageType;			//�ֻ��ʴ�ӡҳ����
typedef BYTE			TPayFlag;			//������_�ո���־
#define TTRANSPACKTYPE_SIZE			4
typedef BYTEARRAY<4>			TTransPackType;			//��������
#define TCHECKPACKTYPE_SIZE			4
typedef BYTEARRAY<4>			TCheckPackType;			//��������
#define TBANKACCOUNT_SIZE			30
typedef BYTEARRAY<30>			TBankAccount;			//����ר���ʺ�
typedef BYTE			TDiffType;			//��ƥ������
typedef BYTE			TSentFlag;			//�ѷ����־
#define TORGANIZATIONID_SIZE			18
typedef BYTEARRAY<18>			TOrganizationID;			//��������
#define TLINKBANKNO_SIZE			5
typedef BYTEARRAY<5>			TLinkBankNo;			//�����к�
#define TSUBACCOUNTNO_SIZE			3
typedef BYTEARRAY<3>			TSubAccountNo;			//��Ա�����ʺŷ�ǩ��
typedef BYTE			TChangeType;			//��Ϣ�������
typedef BYTE			THandleFlag;			//�����־
typedef BYTE			TOrigionalHandleFlag;			//ԭ�����д����־
#define TDRAWREASON_SIZE			20
typedef BYTEARRAY<20>			TDrawReason;			//���ԭ��
typedef BYTE			TDDstate;			//���״̬
typedef BYTE			TDrawSheetState;			//�����״̬
typedef BYTE			TDrawType;			//�������
typedef BYTE			TTransSheetState;			//�����ƻ�״̬
typedef BYTE			TTransferReason;			//����ԭ��
typedef BYTE			TFrozenReason;			//����ԭ��
typedef BYTE			TFrozenModel;			//������ʽ
typedef BYTE			TMarketType;			//�г�����
typedef BYTE			TAppType;			//�������
typedef BYTE			TBizType;			//��Ӫ����
#define TFEEID_SIZE			4
typedef BYTEARRAY<4>			TFeeID;			//���ô���
#define TCONTRACTNO_SIZE			20
typedef BYTEARRAY<20>			TContractNo;			//��Ѻ��Լ���
#define TLOANNO_SIZE			20
typedef BYTEARRAY<20>			TLoanNo;			//�����Լ���
#define TIMPAWNAPPNO_SIZE			8
typedef BYTEARRAY<8>			TImpawnAppNo;			//��Ѻ�걨���
typedef BYTE			TAppState;			//��Ѻ\����걨״̬
typedef BYTE			TOrigApp;			//ԭʼ�걨����־
typedef BYTE			TSpotMatchType;			//�ֻ��ɽ�����
typedef BYTE			TMatchType;			//�ɽ�����
typedef int			TSubstituteNo;			//������
#define TMEMO_SIZE			1024
typedef BYTEARRAY<1024>			TMemo;			//��ע
#define TLEASEAPPNO_SIZE			8
typedef BYTEARRAY<8>			TLeaseAppNo;			//����걨���
#define TIMPAWNREGNO_SIZE			10
typedef BYTEARRAY<10>			TImpawnRegNo;			//��Ѻ�ǼǱ��
#define TLEASEREGNO_SIZE			10
typedef BYTEARRAY<10>			TLeaseRegNo;			//���ǼǱ��
#define TREMINDCODE_SIZE			10
typedef BYTEARRAY<10>			TRemindCode;			//ժҪ���Ǵ���
#define TSPECIALFLAG_SIZE			3
typedef BYTEARRAY<3>			TSpecialFlag;			//�����Ա��־
#define TTYPECODE_SIZE			10
typedef BYTEARRAY<10>			TTypeCode;			//������
typedef BYTE			TCodeFlag;			//�����־
#define TFROZENTYPE_SIZE			2
typedef BYTEARRAY<2>			TFrozenType;			//��������
#define TMELTTYPE_SIZE			2
typedef BYTEARRAY<2>			TMeltType;			//�ⶳ����
#define TSHEETNO_SIZE			16
typedef BYTEARRAY<16>			TSheetNo;			//���ݱ��
typedef BYTE			TTransType;			//���仯����
#define TMARKID_SIZE			4
typedef BYTEARRAY<4>			TMarkID;			//�ƺŴ���
#define TBULLIONCODE_SIZE			4
typedef BYTEARRAY<4>			TBullionCode;			//�������
typedef BYTE			TSheetType;			//��������
typedef BYTE			TMemberFlag;			//��Ա��־
#define TINPUTFLAG_SIZE			3
typedef BYTEARRAY<3>			TInputFlag;			//¼���־
#define TOBVERSEID_SIZE			10
typedef BYTEARRAY<10>			TObverseID;			//��ʶ����
#define TCMDCODE_SIZE			10
typedef BYTEARRAY<10>			TCmdCode;			//�������
#define TCONTENT_SIZE			2000
typedef BYTEARRAY<2000>			TContent;			//�������
typedef BYTE			TSettleType;			//��Ϣ����
typedef BYTE			TCheckFlag;			//����״̬��־
typedef BYTE			TAccountFlag;			//�ʺű�־
#define TBANKNO_SIZE			6
typedef BYTEARRAY<6>			TBankNo;			//�����к�
#define TNODENO_SIZE			6
typedef BYTEARRAY<6>			TNodeNo;			//����վ��
#define TBIZSORT_SIZE			2
typedef BYTEARRAY<2>			TBizSort;			//ҵ������
#define TTURNINFLAG_SIZE			3
typedef BYTEARRAY<3>			TTurnInFlag;			//����ת���־
#define TCERTYPE_SIZE			4
typedef BYTEARRAY<4>			TCerType;			//֤������
typedef BYTE			TStopFlag;			//��ͣ��־
#define TIMPAWNLOGOUTAPPNO_SIZE			10
typedef BYTEARRAY<10>			TImpawnLogoutAppNo;			//��Ѻע���걨���
#define TTODOTXINPUTFLAG_SIZE			3
typedef BYTEARRAY<3>			TToDoTxInputFlag;			//¼���־
typedef BYTE			TDepositType;			//�������
#define TBASEFUNDTYPE_SIZE			2
typedef BYTEARRAY<2>			TBaseFundType;			//������֤������
typedef BYTE			TOperatorType;			//����Ա����
typedef BYTE			TLimitType;			//�޶�����
#define TPERMISSIONID_SIZE			60
typedef BYTEARRAY<60>			TPermissionID;			//ģ����
#define TSUMMARY_SIZE			300
typedef BYTEARRAY<300>			TSummary;			//API��ȫ��֤��
#define TCERT_SIZE			1500
typedef BYTEARRAY<1500>			TCert;			//API��ȫ��֤��
#define TSINGNDATA_SIZE			300
typedef BYTEARRAY<300>			TSingnData;			//API��ȫ��֤��
#define TICSERIAL_SIZE			30
typedef BYTEARRAY<30>			TICSerial;			//API��ȫ��֤��
#define TRANDSERIAL_SIZE			20
typedef BYTEARRAY<20>			TRandSerial;			//API��ȫ��֤��
#define TICPASSWORD_SIZE			8
typedef BYTEARRAY<8>			TICPassword;			//API��ȫ��֤��
typedef BYTE			TMonitorType;			//���Ա����
#define TVERSIONINFO_SIZE			16
typedef BYTEARRAY<16>			TVersionInfo;			//�汾��
typedef BYTE			TEffectState;			//��Ч״̬
#define TENCRYPTPWD_SIZE			60
typedef BYTEARRAY<60>			TEncryptPwd;			//���ܵ�����
#define TSECURITYID_SIZE			10
typedef BYTEARRAY<10>			TSecurityID;			//Ͷ����֤ȯ�˻�
#define TPBU_SIZE			6
typedef BYTEARRAY<6>			TPBU;			//Ͷ����ָ���г������ߴ���
#define TINSTRUMENTID_SIZE			6
typedef BYTEARRAY<6>			TInstrumentId;			//�ƽ�ETF��Ʒ����
#define TETFSHARE_SIZE			16
typedef BYTEARRAY<16>			TEtfShare;			//�ƽ�ETF�ݶ�
#define TETFTRADINGNO_SIZE			16
typedef BYTEARRAY<16>			TEtfTradingNo;			//����ETF���ױ��
typedef BYTE			TIsOK;			//�ɹ�ʧ�ܱ�־
#define TSSE_PROCESSINGRESULT_SIZE			5
typedef BYTEARRAY<5>			TSSE_ProcessingResult;			//�Ͻ�������������
#define TSSE_DESCRIPTION_SIZE			40
typedef BYTEARRAY<40>			TSSE_Description;			//�Ͻ�����������Ҫ����
#define TETFTRADETYPE_SIZE			3
typedef BYTEARRAY<3>			TETFTradeType;			//ETF��������
#define TTRANSFERNO_SIZE			16
typedef BYTEARRAY<16>			TTransferNo;			//���������
typedef BYTE			TIsOK_GO;			//�ɹ�ʧ�ܱ�־-���ƽ̨
typedef BYTE			TTransfertype;			//����Ŀ��
typedef BYTE			TOrderType;			//ָ������



#endif
