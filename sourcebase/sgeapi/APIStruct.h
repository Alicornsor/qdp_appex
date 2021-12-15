#ifndef APISTRUCT_H
#define APISTRUCT_H
#include "ExchangeDataType.h"

#define	CONTINUE_PACKAGE	'C'
#define	LAST_PACKAGE		'L'
#define	OVER_PACKAGE		'O'

//������Ӧ��Ϣ
struct TTRspMsg
{
	char      Flag;		//������¼��־
				//   CONTINUE_PACKAGE���к�����¼
				//   LAST_PACKAGE�����һ����¼����¼���ݷǿ�
				//   OVER_PACKAGE�����һ����¼����¼���ݿ�
 	TRspCode  RspCode;	// ��Ӧ����
 				//   RSP000000�����׳ɹ�
 				//   ���������������ײ��ɹ�
	TRspMsg  RspMsg; //��Ӧ��Ϣ
};

struct TDissemination
{
	WORD  sequenceSeries;				//��ʾXTP���Ĵ���Э��ID
	UINT  sequenceNo;				//��ǰXTP�������
};

//����Ա��Ϣ  
struct TTrader
{
	TTraderID  traderID;				//����Ա����
	TPersonName  traderName;				//����Ա����
	TMemberID  memberID;				//��Ա����
	TEncryptPwd  password;				//����
	TOkFlag  isLogin;				//��¼��־
	TDestroyFlag  state;				//״̬��־
	TLocalNo  localOrderNo;				//��󱾵ر�����
	TMachineID  machineID;				//ǰ�û����
	TCertificateNo  certificateNo;			//֤�����
};

//����Ա��¼������Ϣ  
struct TReqTraderLogin
{
	TTraderID  traderID;				//����Ա����   (not null)
	TMemberID  memberID;				//��Ա����	(not null)
	TPassword  password;				//����          (not null)
	TDate  tradeDate;				//��������      (not null)
	TIpAddress  ipAddress;				//IP��ַ
	TLocalNo  localOrderNo;				//��󱾵ر�����  (not null)
	TMachineID  machineID;				//ǰ�û����
};

//����Ա�˳�������Ϣ  
struct TReqTraderLogout
{
	TTraderID  traderID;				//����Ա����     (not null)
	TMemberID  memberID;				//��Ա����         (not null)
};                                                                        

//�ֻ�������Ϣ  
struct TSpotOrder
{
	TOrderNo  orderNo;				//������	
	TInstID  instID;				//��Լ����       (not null)
	TClientID  clientID;				//�ͻ�����       (not null)
	TMemberID  memberID;				//��Ա����       (not null)
	TBSFlag  buyOrSell;				//��������       (not null)
	TDate  applyDate;				//�걨����
	TTime  applyTime;				//�걨ʱ��
	TTraderID  traderID;				//����Ա����   	(not null)
	TPrice  price;					//�۸�          (not null)
	TVolume  amount;				//����        	(not null)
	TVolume  remainAmount;				//ʣ������
	TTime  cancelTime;				//����ʱ��
	TTraderID  cancelID;				//����Ա����
	TOrderStatus  status;				//״̬
	TSpotMatchType  matchType;			//���� 		(not null)
	TInstID  endorseInstID;				//ת�ú�Լ����  (not null)
	TLocalNo  localOrderNo;				//���ر�����    (not null)
};

//�ֻ�������Ϣ(V2)
struct TSpotOrderEx
{
	TOrderNo  orderNo;				//������	
	TInstID  instID;				//��Լ����       (not null)
	TClientID  clientID;				//�ͻ�����       (not null)
	TMemberID  memberID;				//��Ա����       (not null)
	TBSFlag  buyOrSell;				//��������       (not null)
	TDate  applyDate;				//�걨����
	TTime  applyTime;				//�걨ʱ��
	TTraderID  traderID;				//����Ա����   	(not null)
	TPrice  price;					//�۸�          (not null)
	TVolume  amount;				//����        	(not null)
	TVolume  remainAmount;				//ʣ������
	TTime  cancelTime;				//����ʱ��
	TTraderID  cancelID;				//����Ա����
	TOrderStatus  status;				//״̬
	TSpotMatchType  matchType;			//���� 		(not null)
	TInstID  endorseInstID;				//ת�ú�Լ����  (not null)
	TLocalNo  localOrderNo;				//���ر�����    (not null)
	TOrderType  orderType;				//ָ������    (not null)
};

//�ֻ��ɽ�����Ϣ  
struct TSpotMatch
{
	TMatchNo  matchNo;				//�ɽ����
	TBSFlag  buyOrSell;				//��������
	TClientID  clientID;				//�ͻ�����
	TAccountType  clientType;				//�ͻ�����
	TMemberID  memberID;				//��Ա����
	TInstID  instID;				//��Լ����
	TDate  matchDate;				//�ɽ�����
	TTime  matchTime;				//�ɽ�ʱ��
	TPrice  price;				//�۸�
	TVolume  volume;				//����
	TOrderNo  orderNo;				//ϵͳ������
	TLocalNo  localOrderNo;				//�������ر��
	TSpotMatchType  matchType;				//����
};

//�ֻ�����  
struct TSpotQuotation
{
	TInstID  instID;				//��Լ����
	TInstName  name;				//��Լ����
	TPrice  lastClose;				//������
	TPrice  open;				//���̼�
	TPrice  high;				//��߼�
	TPrice  low;				//��ͼ�
	TPrice  last;				//���¼�
	TPrice  close;				//���̼�
	TPrice  bid1;				//���1
	TVolume  bidLot1;				//����1
	TPrice  bid2;				//���2
	TVolume  bidLot2;				//����2
	TPrice  bid3;				//���3
	TVolume  bidLot3;				//����3
	TPrice  bid4;				//���4
	TVolume  bidLot4;				//����4
	TPrice  bid5;				//���5
	TVolume  bidLot5;				//����5
	TPrice  ask1;				//����1
	TVolume  askLot1;				//����1
	TPrice  ask2;				//����2
	TVolume  askLot2;				//����2
	TPrice  ask3;				//����3
	TVolume  askLot3;				//����3
	TPrice  ask4;				//����4
	TVolume  askLot4;				//����4
	TPrice  ask5;				//����5
	TVolume  askLot5;				//����5
	TVolume  volume;				//�ɽ�����˫�ߣ�
	TWeight  weight;				//�ɽ���˫�ߣ�����
	TPrice  highLimit;				//��ͣ��
	TPrice  lowLimit;				//��ͣ��
	TPrice  upDown;				//�ǵ�
	TRate  upDownRate;				//�ǵ�����
	TMoney  turnOver;				//�ɽ���
	TPrice  average;				//����
	TDate  quoteDate;				//��������
	TDate  quoteTime;				//����ʱ��
	TSequence  sequenceNo;				//�������,ÿ���1��ʼ����
};

//�ֻ����ڽ��ձ���  
struct TDeferOrder
{
	TOrderNo  orderNo;				//������        (not null)
	TClientID  clientID;				//�ͻ�����       (not null)
	TInstID  instID;				//��Լ����       (not null)
	TMemberID  memberID;				//��Ա����       (not null)
	TBSFlag  buyOrSell;				//��������       (not null)
	TDate  applyDate;				//�걨����
	TTime  applyTime;				//�걨ʱ��
	TOffsetFlag  offSetFlag;				//��ƽ�ֱ�־      (not null)
	TPrice  price;				//�۸�                       (not null)
	TVolume  amount;				//����            (not null)
	TVolume  remainAmount;				//ʣ������
	TTime  cancelTime;				//����ʱ��
	TOrderStatus  status;				//״̬
	TLocalNo  localOrderNo;				//���ر�����          (not null)
	TRate  margin;				//��֤����
	TRateType  marginType;				//��֤������           (not null)
	TTraderID  traderID;				//����Ա����          (not null)
	TTraderID  cancelID;				//����Ա����
	TMatchType  matchType;				//����                (not null)
};

//�ֻ����ڽ��ձ���(V2)
struct TDeferOrderEx
{
	TOrderNo  orderNo;				//������        (not null)
	TClientID  clientID;				//�ͻ�����       (not null)
	TInstID  instID;				//��Լ����       (not null)
	TMemberID  memberID;				//��Ա����       (not null)
	TBSFlag  buyOrSell;				//��������       (not null)
	TDate  applyDate;				//�걨����
	TTime  applyTime;				//�걨ʱ��
	TOffsetFlag  offSetFlag;				//��ƽ�ֱ�־      (not null)
	TPrice  price;				//�۸�                       (not null)
	TVolume  amount;				//����            (not null)
	TVolume  remainAmount;				//ʣ������
	TTime  cancelTime;				//����ʱ��
	TOrderStatus  status;				//״̬
	TLocalNo  localOrderNo;				//���ر�����          (not null)
	TRate  margin;				//��֤����
	TRateType  marginType;				//��֤������           (not null)
	TTraderID  traderID;				//����Ա����          (not null)
	TTraderID  cancelID;				//����Ա����
	TMatchType  matchType;				//����                (not null)
	TOrderType  orderType;				//ָ������    (not null)
};

//�ֻ����ڽ��ս����걨����  
struct TDeferDeliveryAppOrder
{
	TOrderNo  orderNo;				//�������
	TClientID  clientID;				//�ͻ�����           (not null)
	TInstID  instID;				//��Լ����            (not null)
	TBSFlag  buyOrSell;				//��������          (not null)
	TDate  applyDate;				//��������
	TTime  applyTime;				//����ʱ��
	TVolume  amount;				//����             (not null)
	TTime  cancelTime;				//����ʱ��
	TOrderStatus  status;				//����״̬
	TLocalNo  localOrderID;				//���ر������     (not null)
	TMemberID  memberID;				//��Ա����           (not null)
	TTraderID  traderID;				//����Ա����         (not null)
	TTraderID  cancelID;				//����Ա����
	TVolume  remainAmount;				//ʣ������
};

//�ֻ����ڽ����������걨����  
struct TMiddleAppOrder
{
	TOrderNo  orderNo;				//�������
	TClientID  clientID;				//�ͻ�����        (not null)
	TInstID  instID;				//��Լ����        (not null)
	TMemberID  memberID;				//��Ա����          (not null)
	TBSFlag  buyOrSell;				//��������          (not null)
	TDate  applyDate;				//��������
	TTime  applyTime;				//����ʱ��
	TVolume  amount;				//����              (not null)
	TTime  cancelTime;				//����ʱ��
	TOrderStatus  status;				//����״̬
	TLocalNo  localOrderID;				//���ر������       (not null)
	TTraderID  traderID;				//����Ա����         (not null)
	TTraderID  cancelID;				//����Ա����
	TVolume  remainAmount;				//ʣ������
};

//�ֻ����ڽ��ճɽ���  
struct TDeferMatch
{
	TMatchNo  matchNo;				//�ɽ����
	TBSFlag  buyOrSell;				//��������
	TClientID  clientID;				//�ͻ�����
	TAccountType  clientType;				//�ͻ�����
	TInstID  instID;				//��Լ����
	TMemberID  memberID;				//��Ա����
	TDate  matchDate;				//�ɽ�����
	TTime  matchTime;				//�ɽ�ʱ��
	TPrice  price;				//�۸�
	TVolume  volume;				//����
	TOffsetFlag  offsetFlag;				//��ƽ��־
	TOrderNo  orderNo;				//ϵͳ������
	TLocalNo  localOrderNo;				//�������ر��
};

//�ֻ����ڽ�������  
struct TDeferQuotation
{
	TInstID  instID;				//��Լ����
	TInstName  name;				//��Լ����
	TPrice  lastSettle;				//�����
	TPrice  lastClose;				//������
	TPrice  open;				//���̼�
	TPrice  high;				//��߼�
	TPrice  low;				//��ͼ�
	TPrice  last;				//���¼�
	TPrice  close;				//���̼�
	TPrice  settle;				//�����
	TPrice  bid1;				//���1
	TVolume  bidLot1;				//����1
	TPrice  bid2;				//���2
	TVolume  bidLot2;				//����2
	TPrice  bid3;				//���3
	TVolume  bidLot3;				//����3
	TPrice  bid4;				//���4
	TVolume  bidLot4;				//����4
	TPrice  bid5;				//���5
	TVolume  bidLot5;				//����5
	TPrice  ask1;				//����1
	TVolume  askLot1;				//����1
	TPrice  ask2;				//����2
	TVolume  askLot2;				//����2
	TPrice  ask3;				//����>3
	TVolume  askLot3;				//����3
	TPrice  ask4;				//����4
	TVolume  askLot4;				//����4
	TPrice  ask5;				//����5
	TVolume  askLot5;				//����5
	TVolume  volume;				//�ɽ���
	TWeight  weight;				//�ɽ���˫�ߣ�����
	TPrice  highLimit;				//��ͣ��
	TPrice  lowLimit;				//��ͣ��
	TVolume  Posi;				//�ֲ���
	TPrice  upDown;				//�ǵ�
	TRate  upDownRate;				//�ǵ�����
	TMoney  turnOver;				//�ɽ���
	TPrice  average;				//����
	TDate  quoteDate;				//��������
	TTime  quoteTime;				//����ʱ��
	TSequence  sequenceNo;				//�������
};

//�ڻ�����  
struct TFuturesOrder
{
	TOrderNo  orderNo;				//������
	TClientID  clientID;				//�ͻ�����               (not null)
	TInstID  instID;				//��Լ����                (not null)
	TMemberID  memberID;				//��Ա����               (not null)
	TBSFlag  buyOrSell;				//��������               (not null)
	TDate  applyDate;				//�걨����
	TTime  applyTime;				//�걨ʱ��
	TOffsetFlag  offsetFlag;				//��ƽ�ֱ�־      (not null)
	TPrice  price;				//�۸�                            (not null)
	TVolume  amount;				//����                      (not null)
	TVolume  remainAmount;				//ʣ������
	TTime  cancelTime;				//����ʱ��
	TOrderStatus  status;				//״̬
	TLocalNo  localOrderNo;				//���ر�����               (not null)
	TRate  margin;				//��֤����
	TRateType  marginType;				//��֤������               (not null)
	TTraderID  traderID;				//����Ա����                 (not null)
	TTraderID  cancelID;				//����Ա����
	TMatchType  matchType;				//����                         (not null)
};

//���ӽ����걨�ɽ���  
struct TDeferDeliveryAppMatch
{
	TMatchNo  matchNo;				//�ɽ����
	TClientID  clientID;				//�ͻ�����
	TInstID  instID;				//��Լ����
	TMemberID  memberID;				//��Ա����
	TBSFlag  buyOrSell;				//��������
	TVolume  volume;				//����
	TDate  matchDate;				//�ɽ�����
	TTime  matchTime;				//�ɽ�ʱ��
	TOrderNo  orderNo;				//������
	TLocalNo  LocalOrderNo;				//�������ر��
	TOkFlag  middleFlag;				//�Ƿ�Ϊ������
};

//�ڻ��ɽ���  
struct TFuturesMatch
{
	TMatchNo  matchNo;				//�ɽ����
	TBSFlag  buyOrSell;				//��������
	TClientID  clientID;				//�ͻ�����
	TAccountType  clientType;				//�ͻ�����
	TInstID  instID;				//��Լ����
	TMemberID  memberID;				//��Ա����
	TDate  matchDate;				//�ɽ�����
	TTime  matchTime;				//�ɽ�ʱ��
	TPrice  price;				//�۸�
	TVolume  volume;				//����
	TRate  marginRate;				//��֤����
	TRateType  rateType;				//��֤������
	TOffsetFlag  offsetFlag;				//��ƽ��־
	TOrderNo  orderNo;				//ϵͳ������
	TLocalNo  localOrderNo;				//�������ر��
};

//�ڻ�����  
struct TFuturesQuotation
{
	TInstID  instID;				//��Լ����
	TInstName  name;				//��Լ����
	TPrice  lastSettle;				//�����
	TPrice  lastClose;				//������
	TPrice  open;				//���̼�
	TPrice  high;				//��߼�
	TPrice  low;				//��ͼ�
	TPrice  last;				//���¼�
	TPrice  close;				//���̼�
	TPrice  settle;				//�����
	TPrice  bid1;				//���1
	TVolume  bidLot1;				//����1
	TPrice  bid2;				//���2
	TVolume  bidLot2;				//����2
	TPrice  bid3;				//���3
	TVolume  bidLot3;				//����3
	TPrice  bid4;				//���4
	TVolume  bidLot4;				//����4
	TPrice  bid5;				//���5
	TVolume  bidLot5;				//����5
	TPrice  ask1;				//����1
	TVolume  askLot1;				//����1
	TPrice  ask2;				//����2
	TVolume  askLot2;				//����2
	TPrice  ask3;				//����>3
	TVolume  askLot3;				//����3
	TPrice  ask4;				//����4
	TVolume  askLot4;				//����4
	TPrice  ask5;				//����5
	TVolume  askLot5;				//����5
	TVolume  volume;				//�ɽ���
	TWeight  weight;				//�ɽ���˫�ߣ�����
	TPrice  highLimit;				//��ͣ��
	TPrice  lowLimit;				//��ͣ��
	TVolume  Posi;				//�ֲ���
	TPrice  upDown;				//�ǵ�
	TRate  upDownRate;				//�ǵ�����
	TMoney  turnOver;				//�ɽ���
	TPrice  average;				//����
	TDate  quoteDate;				//��������
	TTime  quoteTime;				//����ʱ��
	TSequence  sequenceNo;				//�������
};

//�ֻ�T+N����  
struct TForwardOrder
{
	TOrderNo  orderNo;				//������             
	TInstID  instID;				//��Լ����           (not null)
	TClientID  clientID;				//�ͻ�����            (not null)
	TMemberID  memberID;				//��Ա����          (not null)
	TBSFlag  buyOrSell;				//��������          (not null)
	TDate  applyDate;				//�걨����
	TTime  applyTime;				//�걨ʱ��
	TTraderID  traderID;				//����Ա����        (not null)
	TPrice  price;				//�۸�                      (not null)
	TVolume  amount;				//����               (not null)
	TVolume  remainAmount;				//ʣ������
	TTime  cancelTime;				//����ʱ��
	TTraderID  cancelID;				//����Ա����
	TOrderStatus  status;				//״̬
	TLocalNo  localOrderNo;				//���ر�����         (not null)
	TMatchType  matchType;				//����			(not null)
};

//�ֻ�T+N����(V2)
struct TForwardOrderEx
{
	TOrderNo  orderNo;				//������             
	TInstID  instID;				//��Լ����           (not null)
	TClientID  clientID;				//�ͻ�����            (not null)
	TMemberID  memberID;				//��Ա����          (not null)
	TBSFlag  buyOrSell;				//��������          (not null)
	TDate  applyDate;				//�걨����
	TTime  applyTime;				//�걨ʱ��
	TTraderID  traderID;				//����Ա����        (not null)
	TPrice  price;				//�۸�                      (not null)
	TVolume  amount;				//����               (not null)
	TVolume  remainAmount;				//ʣ������
	TTime  cancelTime;				//����ʱ��
	TTraderID  cancelID;				//����Ա����
	TOrderStatus  status;				//״̬
	TLocalNo  localOrderNo;				//���ر�����         (not null)
	TMatchType  matchType;				//����			(not null)
	TOrderType  orderType;				//ָ������    (not null)
};

//�ֻ�T+N�ɽ���  
struct TForwardMatch
{
	TMatchNo  matchNo;				//�ɽ����
	TBSFlag  buyOrSell;				//��������
	TClientID  clientID;				//�ͻ�����
	TAccountType  clientType;				//�ͻ�����
	TInstID  instID;				//��Լ����
	TMemberID  memberID;				//��Ա����
	TDate  matchDate;				//�ɽ�����
	TTime  matchTime;				//�ɽ�ʱ��
	TPrice  price;				//�۸�
	TVolume  volume;				//����
	TRate  marginRate;				//��֤����
	TRateType  rateType;				//��֤������
	TOrderNo  orderNo;				//ϵͳ������
	TLocalNo  localOrderNo;				//�������ر��
};

//�ֻ�T+N����  
struct TForwardQuotation
{
	TInstID  instID;				//��Լ����
	TInstName  name;				//��Լ����
	TPrice  lastSettle;				//�����
	TPrice  lastClose;				//������
	TPrice  open;				//���̼�
	TPrice  high;				//��߼�
	TPrice  low;				//��ͼ�
	TPrice  last;				//���¼�
	TPrice  close;				//���̼�
	TPrice  settle;				//�����
	TPrice  bid1;				//���1
	TVolume  bidLot1;				//����1
	TPrice  bid2;				//���2
	TVolume  bidLot2;				//����2
	TPrice  bid3;				//���3
	TVolume  bidLot3;				//����3
	TPrice  bid4;				//���4
	TVolume  bidLot4;				//����4
	TPrice  bid5;				//���5
	TVolume  bidLot5;				//����5
	TPrice  ask1;				//����1
	TVolume  askLot1;				//����1
	TPrice  ask2;				//����2
	TVolume  askLot2;				//����2
	TPrice  ask3;				//����>3
	TVolume  askLot3;				//����3
	TPrice  ask4;				//����4
	TVolume  askLot4;				//����4
	TPrice  ask5;				//����5
	TVolume  askLot5;				//����5
	TVolume  volume;				//�ɽ���
	TWeight  weight;				//�ɽ���˫�ߣ�����
	TPrice  highLimit;				//��ͣ��
	TPrice  lowLimit;				//��ͣ��
	TVolume  Posi;				//�ֲ���
	TPrice  upDown;				//�ǵ�
	TRate  upDownRate;				//�ǵ�����
	TMoney  turnOver;				//�ɽ���
	TPrice  average;				//����
	TDate  quoteDate;				//��������
	TTime  quoteTime;				//����ʱ��
	TSequence  sequenceNo;				//�������
};

//����Ա�����޸�����  
struct TReqTraderPasswordUpdate
{
	TTraderID  traderID;				//����Ա����(not null)
	TMemberID  memberID;				//��Ա����       (not null)
	TPassword  oldPassword;				//������       (not null)
	TPassword  newPassword;				//������      (not null)
};

//��ԱӦ�������޸�����  
struct TReqMemberUrgentPasswordUpdate
{
	TMemberID  memberID;				//��Ա����      (not null)
	TPassword  oldPassword;				//������         (not null)
	TPassword  newPassword;				//������         (not null)
};

//��Ա�ʽ��ѯ����  
struct TReqQryMemberCapital
{
	TMemberID  memberID;				//��Ա����          (not null)
	TAccountType  accountType;				//�ʻ�����
};

//��Ա�ʽ�  
struct TMemberCapital
{
	TMemberID  memberID;				//��Ա����
	TAccountType  accountType;				//�ʻ�����
	TMoney  available;				//�����ʽ�
	TMoney  lastBalance;				//���ս���׼�������
	TMoney  lastOccupied;				//����ռ�ñ�֤��
	TMoney  todayBalance;				//���ս���׼�������
	TMoney  todayOccupied;				//����ռ�ñ�֤��
	TMoney  profit;				//����ӯ��
	TMoney  todayIn;				//�������
	TMoney  todayOut;				//���ճ���
	TMoney  Payment;				//֧���Ļ����
	TMoney  Received;				//�յ��Ļ����
	TMoney  miscFee;				//����
	TMoney  frozen;				//���ᱣ֤�� 
	TMoney  basefund;				//������֤��
};

//Added by qingquan.xue 20140310 begin
struct TMemberCapitalEx
{
	TMemberID		memberID;				// ��Ա���� 
	TAccountType	accountType;			// �ʻ����� 
	//TMoney			totalRights;		// ��Ȩ�� 
	//TMoney			cash;				// ʵ�л����ʽ� 
	TMoney			offsetOutLimit;			// ��ֳ������ƽ��  
	TMoney			lastAvailable;			// ���տ����ʽ�
	TMoney			todayAvailable;			// ���տ����ʽ� 
	TMoney			lastCashBalance;		// ���ջ��ҽ��׿ɱ������ 
	TMoney			todayCashBalance;		// ���ջ��ҽ��׿ɱ������ 
	TMoney			lastQuotaBalance;		// ���ն�Ƚ��׿ɱ������ 
	TMoney			todayQuotaBalance;		// ���ն�Ƚ��׿ɱ������ 
	TMoney			todayOffsetQuota;		// ʵ�ʳ�ֶ�� 
	TMoney			lastUsedOffsetQuota;	// �������ó�ֶ�� 
	TMoney			todayUsedOffsetQuota;	// �������ó�ֶ�� 
	TMoney			availOffsetQuota;		// ���ó�ֶ�� 
	TMoney			lastCashOccupied;		// ���ջ��ҽ��ױ�֤��ռ�� 
	TMoney			todayCashOccupied;		// ���ջ��ҽ��ױ�֤��ռ�� 
	TMoney			lastQuotaOccupied;		// ���ն�Ƚ��ױ�֤��ռ�� 
	TMoney			todayQuotaOccupied;		// ���ն�Ƚ��ױ�֤��ռ�� 
	TMoney			cashFrozen;				// ���ҽ��׶��ᱣ֤�� 
	TMoney			quotaFrozen;			// ��Ƚ��׶��ᱣ֤�� 
	TMoney			profit;					// ����ӯ�� 
	TMoney			todayIn;				// ������� 
	TMoney			todayOut;				// ���ճ��� 
	TMoney			Payment;				// ֧���Ļ���� 
	TMoney			Received;				// �յ��Ļ���� 
	TMoney			miscFee;				// ���� 
	TMoney			basefund;				// ������֤�� 
};
// Added by qingquan.xue 20140310 end

//�ͻ�����ѯ����  
struct TReqQryClientStorage
{
	TClientID  clientID;				//�ͻ�����     (not null)
	TMemberID  memberID;				//��Ա����       (not null)
};

//�ͻ����  
struct TClientStorage
{
	TClientID  clientID;				//�ͻ�����
	TMemberID  memberID;				//��Ա����
	TVarietyID  varietyID;				//����Ʒ�ִ���
	TWeight  totalStorage;				//�������
	TWeight  availableStorage;				//���ÿ��
	TWeight  frozenStorage;				//�ֻ�������
	TWeight  pendStorage;				//������
	TWeight  impawnStorage;				//��Ѻ���
	TWeight  lawFrozen;				//���ɶ�����
	TWeight  todayBuy;				//��������
	TWeight  todaySell;				//��������
	TWeight  todayDeposit;				//���մ���
	TWeight  todayDraw;				//�������
	TWeight  todayLend;				//���ս��
	TWeight  todayBorrow;				//���ս���
	TWeight  todayShiftOut;				//����ת��
	TWeight  todayShiftIn;				//����ת��
};

// Added by qingquan.xue 20140310 begin
struct TClientStorageEx
{
	TClientID	clientID;				//�ͻ�����
	TMemberID	memberID;				//��Ա����
	TVarietyID  varietyID;				//����Ʒ�ִ���
	TWeight		totalStorage;			//�������
	TWeight		availableStorage;		//���ÿ��
	TWeight		frozenStorage;			//�ֻ�������
	TWeight		pendStorage;			//������
	TWeight		impawnStorage;			//��Ѻ���
	TWeight		lawFrozen;				//���ɶ�����
	TWeight		todayBuy;				//��������
	TWeight		todaySell;				//��������
	TWeight		todayDeposit;			//���մ���
	TWeight		todayDraw;				//�������
	TWeight		todayLend;				//���ս��
	TWeight		todayBorrow;			//���ս���
	TWeight		todayShiftOut;			//����ת��
	TWeight		todayShiftIn;			//����ת��
	TWeight		offsetStorage;			//��ֿ��
};
// Added by qingquan.xue 20140310 end

//������ѯ����  
struct TReqQryOrder
{
	TInstID  instID;				//��Լ����
	TMarketID  marketID;				//�г�����         (not null)
	TOrderNo  orderNo;				//������
	TClientID  clientID;				//�ͻ�����
	TMemberID  memberID;				//��Ա����
	TOffsetFlag  offsetFlag;				//��ƽ��־
};

//���ر����Ų�ѯ����
struct TReqQryLocalOrder
{
	TMemberID  memberID;				//��Ա����		(not null)
	TClientID  clientID;				//��Ա����      (not null)
	TLocalNo  localOrderNo;				//���ر�����    (not null)
};

//�ɽ���ѯ����  
struct TReqQryMatch
{
	TInstID  instID;				//��Լ����
	TMarketID  marketID;				//�г�����      (not null)
	TOrderNo  orderNo;				//������
	TClientID  clientID;				//�ͻ�����
	TMemberID  memberID;				//��Ա����
	TMatchNo  matchNo;				//�ɽ����
};

//�����ѯ����  
struct TReqQryQuotation
{
	TInstID  instID;				//��Լ����
	TMarketID  marketID;				//�г�����        (not null)
};

//��Ա�ֲֲ�ѯ����  
struct TReqQryMemberPosi
{
	TMemberID  memberID;				//��Ա����
	TMarketID  marketID;				//�г�����         (not null)
	TInstID  instID;				//��Լ����
};

//��Ա�ֻ����ڽ��ճֲ�  
struct TDeferMemberPosi
{
	TMemberID  memberID;				//��Ա����
	TInstID  instID;				//��Լ����
	TVolume  longPosi;				//��ͷ�ֲ���
	TVolume  shortPosi;				//��ͷ�ֲ���
	TVolume  lastLong;				//���ն�ͷ�ֲ�
	TVolume  lastShort;				//���տ�ͷ�ֲ�
	TVolume  todayLong;				//���ն�ͷ����
	TVolume  todayShort;				//���տ�ͷ����
	TVolume  todayOffsetLong;				//���ն�ͷƽ����
	TVolume  todayOffsetShort;				//���տ�ͷƽ����
	TMoney  longTurnOver;				//��ͷ�ֲֽ��
	TMoney  shortTurnOver;				//��ͷ�ֲֽ��
	TVolume  deliveryApplyLongFrozen;				//�����걨��ͷ����
	TVolume  deliveryApplyShortFrozen;				//�����걨��ͷ����
	TVolume  deliveryApplyLong;				//�����걨ʹ�ö�ͷ�ֲ�
	TVolume  deliveryApplyShort;				//�����걨ʹ�ÿ�ͷ�ֲ�
	TVolume  longLimitFrozen;				//��ͷ���ֶ����޶�
	TVolume  shortLimitFrozen;				//��ͷ���ֶ����޶�
	TVolume  offsetLongFrozen;				//��ͷƽ�ֶ���
	TVolume  offsetShortFrozen;				//��ͷƽ�ֶ���
};

//��Ա�ڻ��ֲ�  
struct TFuturesMemberPosi
{
	TMemberID  memberID;				//��Ա����
	TInstID  instID;				//��Լ����
	TVolume  longPosi;				//��ͷ�ֲ���
	TVolume  shortPosi;				//��ͷ�ֲ���
	TVolume  lastLong;				//���ն�ͷ�ֲ�
	TVolume  lastShort;				//���տ�ͷ�ֲ�
	TVolume  todayLong;				//���ն�ͷ����
	TVolume  todayShort;				//���տ�ͷ����
	TVolume  todayOffsetLong;				//���ն�ͷƽ����
	TVolume  todayOffsetShort;				//���տ�ͷƽ����
	TMoney  longTurnOver;				//��ͷ�ֲֽ��
	TMoney  shortTurnOver;				//��ͷ�ֲֽ��
	TVolume  longLimitFrozen;				//��ͷ���ֶ����޶�
	TVolume  shortLimitFrozen;				//��ͷ���ֶ����޶�
	TVolume  offsetLongFrozen;				//��ͷƽ�ֶ���
	TVolume  offsetShortFrozen;				//��ͷƽ�ֶ���
};

//��Ա�ֻ�T+N�ֲ�  
struct TForwardMemberPosi
{
	TMemberID  memberID;				//��Ա����
	TInstID  instID;				//��Լ����
	TDate  dueDate;				//������
	TVolume  longPosi;				//��ͷ�ֲ���
	TVolume  shortPosi;				//��ͷ�ֲ���
	TVolume  lastLong;				//���ն�ͷ�ֲ�
	TVolume  lastShort;				//���տ�ͷ�ֲ�
	TVolume  todayLong;				//���ն�ͷ����
	TVolume  todayShort;				//���տ�ͷ����
	TVolume  todayOffsetLong;				//���ն�ͷƽ����
	TVolume  todayOffsetShort;				//���տ�ͷƽ����
	TMoney  longTurnOver;				//��ͷ�ֲֽ��
	TMoney  shortTurnOver;				//��ͷ�ֲֽ��
	TVolume  longLimitFrozen;				//��ͷ���ֶ����޶�
	TVolume  shortLimitFrozen;				//��ͷ���ֶ����޶�
	TVolume  offsetLongFrozen;				//��ͷƽ�ֶ���
	TVolume  offsetShortFrozen;				//��ͷƽ�ֶ���
};

//�ͻ��ֲֲ�ѯ����  
struct TReqQryClientPosi
{
	TClientID  clientID;				//�ͻ�����
	TMemberID  memberID;				//��Ա����    (not null)
	TMarketID  marketID;				//�г�����      (not null)
	TInstID  instID;				//��Լ����
};

//�ͻ��ֻ����ڽ��ճֲ�  
struct TDeferClientPosi
{
	TInstID  instID;				//��Լ����
	TClientID  clientID;				//�ͻ�����
	TMemberID  memberID;				//��Ա����
	TVolume  longPosi;				//��ͷ�ֲ���
	TVolume  shortPosi;				//��ͷ�ֲ���
	TVolume  lastLong;				//���ն�ͷ�ֲ�
	TVolume  lastShort;				//���տ�ͷ�ֲ�
	TVolume  todayLong;				//���ն�ͷ����
	TVolume  todayShort;				//���տ�ͷ����
	TVolume  todayOffsetLong;				//���ն�ͷƽ����
	TVolume  todayOffsetShort;				//���տ�ͷƽ����
	TMoney  longTurnOver;				//��ͷ�ֲֽ��
	TMoney  shortTurnOver;				//��ͷ�ֲֽ��
	TVolume  deliveryApplyLongFrozen;				//�����걨��ͷ����
	TVolume  deliveryApplyShortFrozen;				//�����걨��ͷ����
	TVolume  deliveryApplyLong;				//�����걨ʹ�ö�ͷ�ֲ�
	TVolume  deliveryApplyShort;				//�����걨ʹ�ÿ�ͷ
	TVolume  longLimitFrozen;				//�ֲֶ�ͷ���ֶ����޶�
	TVolume  shortLimitFrozen;				//��ͷ���ֶ����޶�
	TVolume  offsetLongFrozen;				//��ͷƽ�ֶ���
	TVolume  offsetShortFrozen;				//��ͷƽ�ֶ���
};

//�ͻ��ڻ��ֲ�  
struct TFuturesClientPosi
{
	TInstID  instID;				//��Լ����
	TClientID  clientID;				//�ͻ�����
	TMemberID  memberID;				//��Ա����
	TVolume  longPosi;				//��ͷ�ֲ���
	TVolume  shortPosi;				//��ͷ�ֲ���
	TVolume  lastLong;				//���ն�ͷ�ֲ�
	TVolume  lastShort;				//���տ�ͷ�ֲ�
	TVolume  todayLong;				//���ն�ͷ����
	TVolume  todayShort;				//���տ�ͷ����
	TVolume  todayOffsetLong;				//���ն�ͷƽ����
	TVolume  todayOffsetShort;				//���տ�ͷƽ����
	TMoney  longTurnOver;				//��ͷ�ֲֽ��
	TMoney  shortTurnOver;				//��ͷ�ֲֽ��
	TVolume  longLimitFrozen;				//�ֲֶ�ͷ���ֶ����޶�
	TVolume  shortLimitFrozen;				//��ͷ���ֶ����޶�
	TVolume  offsetLongFrozen;				//��ͷƽ�ֶ���
	TVolume  offsetShortFrozen;				//��ͷƽ�ֶ���
};

//�ͻ��ֻ�T+N�ֲ�  
struct TForwardClientPosi
{
	TInstID  instID;				//��Լ����
	TClientID  clientID;				//�ͻ�����
	TMemberID  memberID;				//��Ա����
	TDate  dueDate;				//������
	TVolume  longPosi;				//��ͷ�ֲ���
	TVolume  shortPosi;				//��ͷ�ֲ���
	TVolume  lastLong;				//���ն�ͷ�ֲ�
	TVolume  lastShort;				//���տ�ͷ�ֲ�
	TVolume  todayLong;				//���ն�ͷ����
	TVolume  todayShort;				//���տ�ͷ����
	TVolume  todayOffsetLong;				//���ն�ͷƽ����
	TVolume  todayOffsetShort;				//���տ�ͷƽ����
	TMoney  longTurnOver;				//��ͷ�ֲֽ��
	TMoney  shortTurnOver;				//��ͷ�ֲֽ��
	TVolume  longLimitFrozen;				//�ֲֶ�ͷ���ֶ����޶�
	TVolume  shortLimitFrozen;				//��ͷ���ֶ����޶�
	TVolume  offsetLongFrozen;				//��ͷƽ�ֶ���
	TVolume  offsetShortFrozen;				//��ͷƽ�ֶ���
};

//���Ա��¼����  
struct TReqUserLogin
{
	TTraderID  userID;				//����Ա����          (not null)
	TPassword  password;				//����                   (not null)
	TDate  tradeDate;				//��������
	TLocalNo  localOrderNo;				//��󱾵ر�����       (not null)
	TMachineID  machineID;				//ǰ�û����
	TOperatorType  operatorType;				//����Ա����      (not null)
	TMonitorType monitorType;			//���Ա����
};

//����Ա��Ϣ  
struct TUser
{
	TTraderID  userID;				//����Ա����
	TPersonName  userName;				//����Ա����
	TEncryptPwd  password;				//����
	TOkFlag  isLogin;				//��¼��־
	TDestroyFlag  state;				//״̬��־
	TDeptID  deptID;				//���Ŵ���
	TLocalNo  localOrderNo;				//��󱾵ر�����
	TMachineID  machineID;				//ǰ�û����
	TMonitorType monitorType;			//���Ա����
};

//���Ա�˳�����  
struct TReqUserLogout
{
	TTraderID  userID;				//����Ա����          (not null)
};

//��Լ����״̬��Ϣ  
struct TInstState
{
	TInstID  instID;				//��Լ����
	TInstStateFlag  tradeState;				//��Լ����״̬
};

//��Լ����״̬��ѯ����  
struct TReqQryInstState
{
	TInstID  instID;				//��Լ����
	TMarketID  marketID;				//�г�����       (not null)
};

//�г�����״̬��Ϣ  
struct TMarketState
{
	TMarketID  marketID;				//�г�����           
	TMarketStateFlag  marketState;				//�г�����״̬
};

//�г�����״̬��ѯ����  
struct TReqQryMarketState
{
	TMarketID  marketID;				//�г�����           (not null)
};

//�ֻ����ڽ��ղ���������Ϣ  
struct TDeferFeeRate
{
	TDate  effectDate;				//����
	TInstID  instID;				//��Լ����
	TPayDirection  payDirection;				//֧������
	TRate  feeRate;				//���ӷ���
};

//����Ա���߲�ѯ����  
struct TReqQryTrader
{
	TTraderID  traderID;				//����Ա����          
};

//������������Ϣ  
struct TBulletinBoard
{
	TMemberID  memberID;				//��Ա����
	TSequence  seqNo;				//���
	TDate  announceDate;				//��������
	TTime  announceTime;				//����ʱ��
	TDeptID  deptID;				//���Ŵ���
	TName  title;				//����
	TMemo  content;				//����
	TTraderID  announcer;				//������
};

//��Ա��Ϣ  
struct TMember
{
	TMemberID  memberID;				//��Ա����
	TAbbr  abbr;				//���
	TTradeRight  tradeRight;				//����Ȩ��
	TClassID  classID;				//��Ա����
	TBizType  bizType;				//��Ӫ����
	TMemberType  memberType;				//��Ա����
	TDestroyFlag  destroyFlag;				//ע��״̬
	TDate  destroyDate;				//ע������
	TOkFlag  urgentTradeFlag;				//Ӧ�����ױ�־
	TEncryptPwd  urgentPassword;				//Ӧ����������
	TVolume  urgentNumber;				//Ӧ�����״���
	TVolume  traderNumber;				//����¼����Ա��
};

//�ͻ���Ϣ  
struct TClient
{
	TClientID  clientID;				//�ͻ�����
	TMemberID  memberID;				//��Ա����
	TTradeRight  tradeRight;				//����Ȩ��
	TAccountType  clientType;				//�ͻ�����
	TDestroyFlag  destroyFlag;				//ע��״̬
	TCode	clientSort;					//�ͻ����
};

//�����ַ����  
struct TNetworkAddressLimit
{
	TMemberID  memberID;				//��Ա����
	TConnectType  connectType;				//��������
	TIpAddress  ipAddress;				//IP��ַ
	TVolume  portNumber;				//�˿ں�
	TOpenFlag  openFlag;				//��Ծ��־
};

//��Ա�г�Ȩ����Ϣ  
struct TMemberMarketRight
{
	TMarketID  marketID;				//�г�����
	TMemberID  memberID;				//��Ա����
	TTradeRight  tradeRight;				//����Ȩ������
};

//��Ա�ֻ���ԼȨ����Ϣ  
struct TMemberSpotInstRight
{
	TInstID  instID;				//��Լ����
	TMemberID  memberID;				//��Ա����
	TTradeRight  tradeRight;				//����Ȩ������
	TAccountType  accountType;				//�ʻ�����
};

//��Ա��Լ�ֲ��޶�  
struct TMemberInstPosiLimit
{
	TMarketID  marketID;				//�г�����
	TMemberID  memberID;				//��Ա����
	TInstID  instID;				//��Լ����
	TDirection  direction;				//��շ���
	TVolume  limit;				//����
};

//�ͻ���Լ�ֲ��޶�  
struct TClientInstPosiLimit
{
	TMarketID  marketID;				//�г�����
	TClientID  clientID;				//�ͻ�����
	TMemberID  memberID;				//��Ա����
	TInstID  instID;				//��Լ����
	TDirection  direction;				//��շ���
	TVolume  limit;				//����
};

//�ֻ�T+Nǿƽ�ɽ���  
struct TForwardForceMatch
{
	TMatchNo  matchNo;				//�ɽ����
	TBSFlag  buyOrSell;				//��������
	TDate  matchDate;				//�ɽ�����
	TTime  matchTime;				//�ɽ�ʱ��
	TClientID  clientID;				//�ͻ�����
	TAccountType  clientType;				//�ͻ�����
	TMemberID  memberID;				//��Ա����
	TInstID  instID;				//��Լ����
	TPrice  price;				//�۸�
	TVolume  volume;				//����
	TMatchNo  orignalMatchNo;				//ԭ���ɽ����
	TTraderID  operatorID;				//����Ա����
};

//�ֻ���������  
struct TSpotOrderCancel
{
	TOrderNo  orderNo;				//������         (not null)
	TInstID  instID;				//��Լ����        (not null)
	TClientID  clientID;				//�ͻ�����       (not null)
	TMemberID  memberID;				//��Ա����         (not null)
	TTraderID  traderID;				//����Ա����      (not null)
};

//�ֻ����ڽ��ճ�������  
struct TDeferOrderCancel
{
	TOrderNo  orderNo;				//������             (not null)
	TInstID  instID;				//��Լ����             (not null)
	TClientID  clientID;				//�ͻ�����           (not null)
	TMemberID  memberID;				//��Ա����            (not null)
	TTraderID  traderID;				//����Ա����           (not null)
};

//�ڻ���������  
struct TFuturesOrderCancel
{
	TOrderNo  orderNo;				//������               (not null)
	TInstID  instID;				//��Լ����              (not null)
	TClientID  clientID;				//�ͻ�����              (not null)
	TMemberID  memberID;				//��Ա����              (not null)
	TTraderID  traderID;				//����Ա����          (not null)
};

//�ֻ�T+N��������  
struct TForwardOrderCancel
{                                                                           
	TOrderNo  orderNo;				//������            (not null)
	TInstID  instID;				//��Լ����           (not null)
	TClientID  clientID;				//�ͻ�����          (not null)
	TMemberID  memberID;				//��Ա����          (not null)
	TTraderID  traderID;				//����Ա����        (not null)
};

//�ֻ����ڽ��ս����걨��������  
struct TDeferDeliveryAppOrderCancel
{
	TOrderNo  orderNo;				//������               (not null)
	TInstID  instID;				//��Լ����              (not null)
	TClientID  clientID;				//�ͻ�����             (not null)
	TMemberID  memberID;				//��Ա����		(not null)
	TTraderID  traderID;				//����Ա����       (not null)
};

//�ֻ����ڽ����������걨��������  
struct TMiddleAppOrderCancel
{
	TOrderNo  orderNo;				//������          (not null)
	TInstID  instID;				//��Լ����         (not null)
	TClientID  clientID;				//�ͻ�����        (not null)
	TMemberID  memberID;				//��Ա����        (not null)
	TTraderID  traderID;				//����Ա����      (not null)
};

//�ֻ�T+N����ת�ó�������  
struct TForwardEndorseOrderCancel
{
	TOrderNo  orderNo;				//������        (not null)
	TInstID  instID;				//��Լ����       (not null)
	TClientID  clientID;				//�ͻ�����      (not null)
	TMemberID  memberID;				//��Ա����      (not null)
	TTraderID  traderID;				//����Ա����     (not null)
};

//�ֻ���Լ��֤����  
struct TSpotInstMarginRate
{
	TInstID  instID;				//��Լ����
	TMemberID  memberID;				//��Ա����
	TAccountType  accountType;				//�ʻ�����
	TRate  marginRate;				//��֤����
	TRateType  rateType;				//��֤������
};

//���Ӻ�Լ��֤����  
struct TDeferInstMarginRate
{
	TInstID  instID;				//��Լ����
	TMemberID  memberID;				//��Ա����
	TAccountType  accountType;				//�ʻ�����
	TRate  marginRate;				//��֤����
	TRateType  rateType;				//��֤������
	TDirection direction;			//��շ���
};

//�ڻ���Լ��֤����  
struct TFuturesInstMarginRate
{
	TInstID  instID;				//��Լ����
	TMemberID  memberID;				//��Ա����
	TAccountType  accountType;				//�ʻ�����
	TRate  marginRate;				//��֤����
	TRateType  rateType;				//��֤������
};

//Զ�ں�Լ��֤����  
struct TForwardInstMarginRate
{
	TInstID  instID;				//��Լ����
	TMemberID  memberID;				//��Ա����
	TAccountType  accountType;				//�ʻ�����
	TRate  marginRate;				//��֤����
	TRateType  rateType;				//��֤������
};

//Ӧ����������  
struct TUrgentTradePassword
{
	TPassword  urgentPassword;				//Ӧ����������
};

//����Ա����  
struct TUserPassword
{
	TTraderID  userID;				//����Ա����
	TPassword  password;				//����
};

//�ֻ���Լ  
struct TSpotInst
{
	TInstID  instID;				//��Լ����
	TInstName  name;				//��Լ����
	TMarketID  marketID;				//�г�����
	TVarietyType  varietyType;				//Ʒ�����
	TVarietyID  varietyID;				//����Ʒ�ִ���
	TInstUnit  unit;				//���׵�λ����
	TPrice  tick;				//��С�䶯��λ
	TVolume  maxHand;				//����걨����(����)
	TVolume  minHand;				//��С�걨����
	TRate  upperLimit;				//��ͣ����
	TRate  lowerLimit;				//��ͣ����
	TOpenFlag  openFlag;				//��Ծ��־1��Ծ;2����Ծ3ֻƽ 4ֻ��
	TInstStateFlag  tradeState;				//��Լ����״̬
	TPrice  refPrice;				//�ο���
	TRate  recvRate;				//�����տ����
};

//�ֻ����ڽ��պ�Լ  
struct TDeferInst
{
	TInstID  instID;				//��Լ����
	TInstName  name;				//��Լ����
	TMarketID  marketID;				//�г�����
	TVarietyType  varietyType;				//Ʒ�����
	TVarietyID  varietyID;				//����Ʒ�ִ���
	TInstUnit  unit;				//���׵�λ����
	TPrice  tick;				//��С�䶯��λ
	TVolume  maxHand;				//����걨����(����)
	TVolume  minHand;				//��С�걨����
	TRate  upperLimit;				//��ͣ����
	TRate  lowerLimit;				//��ͣ����
	TOpenFlag  openFlag;				//��Ծ��־1��Ծ;2����Ծ3ֻƽ 4ֻ��
	TInstStateFlag  tradeState;				//��Լ����״̬
	TPrice  refPrice;				//�ο���
};

//�ڻ���Լ  
struct TFuturesInst
{
	TInstID  instID;				//��Լ����
	TInstName  name;				//��Լ����
	TMarketID  marketID;				//�г�����
	TVarietyType  varietyType;				//Ʒ�����
	TVarietyID  varietyID;				//����Ʒ�ִ���
	TInstUnit  unit;				//���׵�λ����
	TPrice  tick;				//��С�䶯��λ
	TVolume  maxHand;				//����걨����(����)
	TVolume  minHand;				//��С�걨����
	TRate  upperLimit;				//��ͣ����
	TRate  lowerLimit;				//��ͣ����
	TOpenFlag  openFlag;				//��Ծ��־1��Ծ;2����Ծ3ֻƽ 4ֻ��
	TInstStateFlag  tradeState;				//��Լ����״̬
	TPrice  refPrice;				//�ο���
};

//�ֻ�T+N��Լ  
struct TForwardInst
{
	TInstID  instID;				//��Լ����
	TInstName  name;				//��Լ����
	TMarketID  marketID;				//�г�����
	TVarietyType  varietyType;				//Ʒ�����
	TVolume  deliveryDay;				//��Լ������,����������
	TVarietyID  varietyID;				//����Ʒ�ִ���
	TInstUnit  unit;				//���׵�λ����
	TPrice  tick;				//��С�䶯��λ
	TVolume  maxHand;				//����걨����(����)
	TVolume  minHand;				//��С�걨����(����)
	TRate  upperLimit;				//��ͣ����
	TRate  lowerLimit;				//��ͣ����
	TOpenFlag  openFlag;				//��Ծ��־1��Ծ;2����Ծ3ֻƽ 4ֻ��
	TInstStateFlag  tradeState;				//��Լ����״̬
	TPrice  refPrice;				//�ο���
	TDate  dueDate;				//������
};

//�г���  
struct TMarket
{
	TMarketID  marketID;				//�г�����
	TMarketName  name;				//ȫ��
	TMarketType  type;				//����
	TOkFlag  openFlag;				//��Ծ��־
	TMarketStateFlag  marketState;				//�г�����״̬
};

//��������  
struct TExchange
{
	TExchangeID  exchangeID;				//����������
	TExchangeStateFlag  state;				//����״̬
};

//�ֻ�T+Nǿ��ƽ������  
struct TReqForwardForceMatch
{
	TClientID  buyerClientID;				//��ͻ�����   (not null)
	TMemberID  buyerMemberID;				//���Ա����    (not null)
	TClientID  sellClientID;				//���ͻ�����    (not null)
	TMemberID  sellMemberID;				//����Ա����    (not null)
	TInstID  instID;				//��Լ����       (not null)
	TPrice  price;				//�۸�                  (not null)
	TVolume  volume;				//����           (not null)
	TMatchNo  orignalMatchNo;				//ԭ���ɽ����     (not null)
	TTraderID  operatorID;				//����Ա����             (not null)
};

//�������޶��  
struct TMarketMakerLimit
{
	TMemberID  memberID;				//��Ա����
	TInstID  instID;				//��Լ����
	TMarketID  marketID;				//�г�����
	TLimitType  limitType;				//�޶�����
	TPrice  limit;				//����
};

//�����ֻ���������  
struct TMinsSpotQuotation
{
	TInstID  instID;				//��Լ����
	TPrice  open;				//���̼�
	TPrice  high;				//��߼�
	TPrice  low;				//��ͼ�
	TPrice  close;				//���̼�
	TVolume  volume;				//�ɽ�����˫�ߣ�
	TDate  quoteDate;				//��������
	TDate  quoteTime;				//����ʱ��
};

//�ڻ���������  
struct TMinsFuturesQuotation
{
	TInstID  instID;				//��Լ����
	TInstName  name;				//��Լ����
	TPrice  open;				//���̼�
	TPrice  high;				//��߼�
	TPrice  low;				//��ͼ�
	TPrice  close;				//���̼�
	TVolume  volume;				//�ɽ���
	TVolume  Posi;				//�ֲ���
	TDate  quoteDate;				//��������
	TTime  quoteTime;				//����ʱ��
};

//���ӷ�������  
struct TMinsDeferQuotation
{
	TInstID  instID;				//��Լ����
	TPrice  open;				//���̼�
	TPrice  high;				//��߼�
	TPrice  low;				//��ͼ�
	TPrice  close;				//���̼�
	TVolume  volume;				//�ɽ���
	TVolume  Posi;				//�ֲ���
	TDate  quoteDate;				//��������
	TTime  quoteTime;				//����ʱ��
};

//Զ�ڷ�������  
struct TMinsForwardQuotation
{
	TInstID  instID;				//��Լ����
	TPrice  open;				//���̼�
	TPrice  high;				//��߼�
	TPrice  low;				//��ͼ�
	TPrice  close;				//���̼�
	TVolume  volume;				//�ɽ���
	TVolume  Posi;				//�ֲ���
	TDate  quoteDate;				//��������
	TTime  quoteTime;				//����ʱ��
};

//�ֻ���Լ����״̬���Ʊ�  
struct TSpotInstStateControl
{
	TInstStateFlag  state;				//��Լ����״̬
	TTime  startTime;				//����ʱ��
	TInstID  instID;				//��Լ����
};

//���Ӻ�Լ����״̬���Ʊ�  
struct TDeferInstStateControl
{
	TInstStateFlag  state;				//��Լ����״̬
	TTime  startTime;				//����ʱ��
	TInstID  instID;				//��Լ����
};

//�ڻ���Լ����״̬���Ʊ�  
struct TFuturesInstStateControl
{
	TInstStateFlag  state;				//��Լ����״̬
	TTime  startTime;				//����ʱ��
	TInstID  instID;				//��Լ����
};

//Զ�ں�Լ����״̬���Ʊ�  
struct TForwardInstStateControl
{
	TInstStateFlag  state;				//��Լ����״̬
	TTime  startTime;				//����ʱ��
	TInstID  instID;				//��Լ����
};

//��Ա���Ӻ�Լ�ֲ��޶�  
struct TMemberDeferPosiLimit
{
	TMemberID  memberID;				//��Ա����
	TInstID  instID;				//��Լ����
	TDirection  direction;				//��շ���
	TVolume  limit;				//����
	TAccountType clientType;	//�ͻ�����
};

//�ͻ����Ӻ�Լ�ֲ��޶�  
struct TClientDeferPosiLimit
{
	TClientID  clientID;				//�ͻ�����
	TMemberID  memberID;				//��Ա����
	TInstID  instID;				//��Լ����
	TDirection  direction;				//��շ���
	TVolume  limit;				//����
	TCode	clientSort;			//�ͻ����
	TAccountType clientType;	//�ͻ�����
};

//��Ա�ڻ���Լ�ֲ��޶�  
struct TMemberFuturesPosiLimit
{
	TMemberID  memberID;				//��Ա����
	TInstID  instID;				//��Լ����
	TDirection  direction;				//��շ���
	TVolume  limit;				//����
};

//�ͻ��ڻ���Լ�ֲ��޶�  
struct TClientFuturesPosiLimit
{
	TClientID  clientID;				//�ͻ�����
	TMemberID  memberID;				//��Ա����
	TInstID  instID;				//��Լ����
	TDirection  direction;				//��շ���
	TVolume  limit;				//����
};

//��ԱԶ�ں�Լ�ֲ��޶�  
struct TMemberForwardPosiLimit
{
	TMemberID  memberID;				//��Ա����
	TInstID  instID;				//��Լ����
	TDirection  direction;				//��շ���
	TVolume  limit;				//����
};

//�ͻ�Զ�ں�Լ�ֲ��޶�  
struct TClientForwardPosiLimit
{
	TClientID  clientID;				//�ͻ�����
	TMemberID  memberID;				//��Ա����
	TInstID  instID;				//��Լ����
	TDirection  direction;				//��շ���
	TVolume  limit;				//����
};

//��Ա�ֻ��г�Ȩ��  
struct TMemberSpotMarketRight
{
	TMarketID  marketID;				//�г�����
	TMemberID  memberID;				//��Ա����
	TTradeRight  tradeRight;				//����Ȩ������
};

//��Ա�����г�Ȩ��  
struct TMemberDeferMarketRight
{
	TMarketID  marketID;				//�г�����
	TMemberID  memberID;				//��Ա����
	TTradeRight  tradeRight;				//����Ȩ������
};

//��Ա���Ӻ�ԼȨ��  
struct TMemberDeferInstRight
{
	TInstID  instID;				//��Լ����
	TMemberID  memberID;				//��Ա����
	TAccountType  accountType;				//�ʻ�����
	TTradeRight  tradeRight;				//����Ȩ������
};

//��Ա�ڻ��г�Ȩ��  
struct TMemberFuturesMarketRight
{
	TMarketID  marketID;				//�г�����
	TMemberID  memberID;				//��Ա����
	TTradeRight  tradeRight;				//����Ȩ������
};

//��Ա�ڻ���ԼȨ��  
struct TMemberFuturesInstRight
{
	TInstID  instID;				//��Լ����
	TMemberID  memberID;				//��Ա����
	TAccountType  accountType;				//�ʻ�����
	TTradeRight  tradeRight;				//����Ȩ������
};

//��ԱԶ���г�Ȩ��  
struct TMemberForwardMarketRight
{
	TMarketID  marketID;				//�г�����
	TMemberID  memberID;				//��Ա����
	TTradeRight  tradeRight;				//����Ȩ������
};

//��ԱԶ�ں�ԼȨ��  
struct TMemberForwardInstRight
{
	TInstID  instID;				//��Լ����
	TMemberID  memberID;				//��Ա����
	TAccountType  accountType;				//�ʻ�����
	TTradeRight  tradeRight;				//����Ȩ������
};

//�г�����״̬���Ʊ�  
struct TMarketStateControl
{
	TMarketStateFlag  state;				//�г�����״̬
	TTime  startTime;				//����ʱ��
	TMarketID  marketID;				//�г�����
};

//Զ��Ӧ������  
struct TUrgentForwardOrder
{
	TOrderNo  orderNo;				//������           
	TClientID  clientID;				//�ͻ�����         (not null)
	TInstID  instID;				//��Լ����          (not null)
	TMemberID  memberID;				//��Ա����        (not null)
	TBSFlag  buyOrSell;				//��������       (not null)
	TDate  applyDate;				//�걨����
	TTime  applyTime;				//�걨ʱ��
	TOffsetFlag  offsetFlag;				//��ƽ�ֱ�־   (not null)
	TPrice  price;				//�۸�                         (not null)
	TVolume  amount;				//����                  (not null)
	TVolume  remainAmount;				//ʣ������
	TOrderStatus  status;				//״̬
	TLocalNo  localOrderNo;				//���ر�����            (not null)
	TRate  margin;				//��֤����
	TRateType  marginType;				//��֤������             (not null)
	TTraderID  traderID;				//����Ա����            (not null)
	TTime  cancelTime;				//����ʱ��
	TTraderID  cancelID;				//����Ա����
	TTraderID  checkID;				//����Ա����
	TCheckFlag  checkFlag;				//���˱�־
	TMatchType  matchType;				//����                   (not null)
	TOrderType  orderType;				//ָ������    (not null)
};

//�ڻ�Ӧ������  
struct TUrgentFuturesOrder
{
	TOrderNo  orderNo;				//������
	TClientID  clientID;				//�ͻ�����
	TInstID  instID;				//��Լ����
	TMemberID  memberID;				//��Ա����
	TBSFlag  buyOrSell;				//��������
	TDate  applyDate;				//�걨����
	TTime  applyTime;				//�걨ʱ��
	TOffsetFlag  offSetFlag;				//��ƽ�ֱ�־
	TPrice  price;				//�۸�
	TVolume  amount;				//����
	TVolume  remainAmount;				//ʣ������
	TOrderStatus  status;				//״̬
	TLocalNo  localOrderNo;				//���ر�����
	TRate  margin;				//��֤����
	TRateType  marginType;				//��֤������
	TTraderID  traderID;				//����Ա����
	TTime  cancelTime;				//����ʱ��
	TTraderID  cancelID;				//����Ա����
	TTraderID  checkID;				//����Ա����
	TCheckFlag  checkFlag;				//���˱�־
	TMatchType  matchType;				//����
};

//����Ӧ������
struct TUrgentDeferOrder
{
	TOrderNo  orderNo;				//������
	TBSFlag  buyOrSell;				//��������
	TDate  applyDate;				//�걨����
	TTime  applyTime;				//�걨ʱ��
	TOffsetFlag  offSetFlag;				//��ƽ�ֱ�־
	TPrice  price;				//�۸�
	TVolume  amount;				//����
	TVolume  remainAmount;				//ʣ������
	TOrderStatus  status;				//״̬
	TLocalNo  localOrderNo;				//���ر�����
	TRate  margin;				//��֤����
	TRateType  marginType;				//��֤������
	TClientID  clientID;				//�ͻ�����
	TInstID  instID;				//��Լ����
	TMemberID  memberID;				//��Ա����
	TTraderID  traderID;				//����Ա����
	TTime  cancelTime;				//����ʱ��
	TTraderID  cancelID;				//����Ա����
	TTraderID  checkID;				//����Ա����
	TCheckFlag  checkFlag;				//���˱�־
	TMatchType  matchType;				//����
	TOrderType  orderType;				//ָ������    (not null)
};

//�ֻ�Ӧ������
struct TUrgentSpotOrder
{
	TOrderNo  orderNo;				//������
	TInstID  instID;				//��Լ����
	TClientID  clientID;				//�ͻ�����
	TMemberID  memberID;				//��Ա����
	TBSFlag  buyOrSell;				//��������
	TDate  applyDate;				//�걨����
	TTime  applyTime;				//�걨ʱ��
	TTraderID  traderID;				//����Ա����
	TPrice  price;				//�۸�
	TVolume  amount;				//����
	TVolume  remainAmount;				//ʣ������
	TTime  cancelTime;				//����ʱ��
	TTraderID  cancelID;				//����Ա����
	TOrderStatus  Status;				//״̬
	TLocalNo  localOrderNo;				//���ر�����
	TTraderID  checkID;				//����Ա����
	TCheckFlag  checkFlag;				//���˱�־
	TSpotMatchType  matchType;				//����
	TOrderType  orderType;				//ָ������    (not null)
};

//Ӧ��������ѯ����  
struct TReqQryUrgentOrder
{
	TMarketID  marketID;				//�г�����             (not null)
};

//�ֻ�Ӧ��������������  
struct TUrgentSpotOrderCancel
{
	TOrderNo  orderNo;				//������            (not null)
	TInstID  instID;				//��Լ����           (not null)
	TClientID  clientID;				//�ͻ�����           (not null)
	TMemberID  memberID;				//��Ա����            (not null)
	TTraderID  traderID;				//����Ա����          (not null)
};

//����Ӧ��������������  
struct TUrgentDeferOrderCancel
{
	TOrderNo  orderNo;				//������             (not null)
	TInstID  instID;				//��Լ����             (not null)
	TClientID  clientID;				//�ͻ�����            (not null)
	TMemberID  memberID;				//��Ա����              (not null)
	TTraderID  traderID;				//����Ա����            (not null)
};

//�ڻ�Ӧ��������������  
struct TUrgentFuturesOrderCancel
{
	TOrderNo  orderNo;				//������                 (not null)
	TInstID  instID;				//��Լ����              (not null)
	TClientID  clientID;				//�ͻ�����              (not null)
	TMemberID  memberID;				//��Ա����              (not null)
	TTraderID  traderID;				//����Ա����            (not null)
};

//Զ��Ӧ��������������  
struct TUrgentForwardOrderCancel
{
	TOrderNo  orderNo;				//������           (not null)
	TInstID  instID;				//��Լ����          (not null)
	TClientID  clientID;				//�ͻ�����		(not null)
	TMemberID  memberID;				//��Ա����       (not null)
	TTraderID  traderID;				//����Ա����      (not null)
};

//��Ա���ֲ�ѯ����  
struct TReqQryMemberPosiOver
{
	TMemberID  memberID;				//��Ա����           (not null)
	TMarketID  marketID;				//�г�����            (not null)
	TInstID  instID;				//��Լ����            (not null)
	TAccountType accountType;       // �˻�����           (not null)
	TTraderID  userID;				//����Ա����           (not null)
};

//��Ա���ֲ�ѯ��Ӧ  
struct TRspQryMemberPosiOver
{
	TMemberID  memberID;				//��Ա����
	TMarketID  marketID;				//�г�����
	TClientID  clientID;				//�ͻ�����
	TInstID  instID;				//��Լ����
	TBSFlag  buyOrSell;				//��������
	TVolume  amount;				//����
};

//�ͻ����ֲ�ѯ����  
struct TReqQryClientPosiOver
{
	TClientID  clientID;				//�ͻ�����          (not null)
	TMarketID  marketID;				//�г�����          (not null)
	TInstID  instID;				//��Լ����           (not null)
	TTraderID  userID;				//����Ա����          (not null)
};

//�ͻ����ֲ�ѯ��Ӧ  
struct TRspQryClientPosiOver
{
	TMemberID  memberID;				//��Ա����
	TClientID  clientID;				//�ͻ�����
	TMarketID  marketID;				//�г�����
	TInstID  instID;				//��Լ����
	TBSFlag  buyOrSell;				//��������
	TVolume  amount;				//����
};

//�ʽ����ѯ����  
struct TReqQryCapitalLack
{
	TMemberID  memberID;				//��Ա����           (not null)
	TClientID  clientID;				//�ͻ����� add by chechao,2011.12.19
	TMarketID  marketID;				//�г�����           (not null)
	TInstID  instID;				//��Լ����            (not null)
	TAccountType  accountType;				//�ʻ�����    (not null)
	TVolume  amount;				//����              (not null)
	TBSFlag  buyOrSell;				//��������            (not null)
	TTraderID  userID;				//����Ա����          (not null)
};

//�ʽ����ѯ��Ӧ  
struct TRspQryCapitalLack
{
	TMemberID  memberID;				//��Ա����
	TClientID  clientID;				//�ͻ�����
	TMarketID  marketID;				//�г�����
	TInstID  instID;				//��Լ����
	TBSFlag  buyOrSell;				//��������
	TVolume  amount;				//�ֲܳ�
	TVolume	 availAmount;			//���óֲ�
};

//���ӷ��ʲ�ѯ����  
struct TReqQryDeferFeeRate
{
	TDate  effectDateBegin;				//��ʼ����
	TDate  effectDateEnd;				//��������
};

//����������Ϣ  
struct TInterQuotation
{
	TAbstract  content;				//����
	TTraderID  announcer;				//������
	TTime  announceTime;				//����ʱ��
	TDate  announceDate;				//��������
};

//������������Ϣ��ѯ����  
struct TReqQryBulletinBoard
{
	TMemberID  memberID;				//��Ա����
	TDate  announceDate;				//��������
};

//ǿ�ƽ���Ա�˳�����  
struct TReqForceTraderLogout
{
	TTraderID  traderID;				//����Ա����         (not null)
	TMemberID  memberID;				//��Ա����           (not null)
	TTraderID  userID;				//����Ա����        (not null)
};

//������Ӳ�ѯ����  
struct TReqQryMinsQuotation
{
	TInstID  instID;				//��Լ����          (not null)
	TMarketID  marketID;				//�г�����         (not null)
	TTime  lastTime;				//��һ��ʱ��
};

//�ʽ�����  
struct TReqCapital
{
	TMemberID  memberID;				//��Ա����             
	TAccountType  accountType;				//�ʻ�����      
	TMoney  capital;				//�ʽ�
};

//�ʽ���ˮ  
struct TCapitalSeq
{
	TDate  i_accountDate;				//����
	TMemberID  i_memberID;				//��Ա����
	TAccountType  i_accountType;				//�˻�����
	TBizSort  i_bizSort;				//ҵ������
	TMoney  i_effectAmount;				//�������
};

//�ִ��仯��ϸ  
struct TStorageWasteBook
{
	TDate  i_transDate;				//ʵ�ʷ�������
	TTime  i_transTime;				//ʵ�ʷ���ʱ��
	TClientID  i_clientID;				//�ͻ�����
	TMemberID  i_memberID;				//��Ա����
	TAccountType  i_accountType;				//�˻�����
	TMatchNo  i_sheetNo;				//���ݱ��
	TTransType  i_transType;				//��������
	TVarietyID  i_varietyID;				//����Ʒ�ִ���
	TWeight  i_stdStorage;				//������׼����
};

//״̬ģʽ  
struct TStateMode
{
	TMarketID  marketID;				//�г�����
	TInstID  instID;				//��Լ����
};

//��Ա�ͻ���ѯ����  
struct TReqQryClient
{
	TMemberID  memberID;				//��Ա����         (not null)
	TClientID  clientID;				//�ͻ�����
};

//���ӽ�������  
struct TDeferDeliveryQuotation
{
	TInstID  instID;				//��Լ����
	TVolume  bidLot;				//����
	TVolume  askLot;				//����
	TVolume  midBidLot;				//����������
	TVolume  midAskLot;				//����������
};

//ǿƽ�ɽ���  
struct TReqForceMatch
{
	TClientID  clientID;				//�ͻ�����
	TInstID  instID;				//��Լ����
	TPrice  price;				//ƽ�ּ۸�
	TVolume  offset;				//ƽ������
};

//����Ʒ�ִ���  
struct TVariety
{
	TVarietyID  varietyID;				//����Ʒ�ִ���
	TName  name;				//����Ʒ��ȫ��
	TAbbr  abbr;				//���
	TVarietyType  varietyType;				//Ʒ�����
	TWeight  minPickup;				//��С�������
	TWeight  defaultStdWeight;		//Ĭ�ϱ�׼���� add by litian 20061018
	TWeight  pickupBase;				//�������
	TUnitID  weightUnit;				//������λ
	TDestroyFlag  destroyFlag;				//ע����־
};

//�����ֱ�֤����  
struct TMiddleMarginRate
{
	TInstID  instID;				//��Լ����
	TRate  marginRate;				//��֤����
};

//�汾��Ϣ 
struct TVersion
{
	TVersionInfo versionInfo;		//�汾��
};

#endif	
