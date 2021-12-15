/////////////////////////////////////////////////////////////////////////
///@system ִ������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file customDataType.h
///@brief�����˽������ڲ����ݵĵײ�֧����
///@history 
///20050324	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CUSTOMDATATYPE_H
#define CUSTOMDATATYPE_H

#include "UFDataType.h"

/////////////////////////////////////////////////////////////////////////
///CFloatType��һ����С�䶯��λ��
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<22,8> CPriceTickType;
typedef const CUFFloatType<22,8> CReadOnlyPriceTickType;
	
/////////////////////////////////////////////////////////////////////////
///CFloatType��һ���۸���
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<22,8> CPriceType;
typedef const CUFFloatType<22,8> CReadOnlyPriceType;
	
/////////////////////////////////////////////////////////////////////////
///CFloatType��һ��������
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<22,8> CRatioType;
typedef const CUFFloatType<22,8> CReadOnlyRatioType;
	
/////////////////////////////////////////////////////////////////////////
///CFloatType��һ���ʽ���
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<19,3> CMoneyType;
typedef const CUFFloatType<19,3> CReadOnlyMoneyType;
	
/////////////////////////////////////////////////////////////////////////
///CFloatType��һ�����������
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<19,3> CLargeVolumeType;
typedef const CUFFloatType<19,3> CReadOnlyLargeVolumeType;
	
/////////////////////////////////////////////////////////////////////////
///CFloatType��һ����ӯ����
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<8,3> CEarningRatioType;
typedef const CUFFloatType<8,3> CReadOnlyEarningRatioType;
	
/////////////////////////////////////////////////////////////////////////
///CFloatType��һ�������м����
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<22,8> CExRatePriceType;
typedef const CUFFloatType<22,8> CReadOnlyExRatePriceType;
	
/////////////////////////////////////////////////////////////////////////
///CFloatType��һ��������
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<19,3> CFeeType;
typedef const CUFFloatType<19,3> CReadOnlyFeeType;
	
/////////////////////////////////////////////////////////////////////////
///CFloatType��һ�������
/////////////////////////////////////////////////////////////////////////
typedef CUFFloatType<19,3> CInventoryType;
typedef const CUFFloatType<19,3> CReadOnlyInventoryType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ�������
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CNumberType;
typedef CReadOnlyUFIntType CReadOnlyNumberType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ�����к���
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CSequenceNoType;
typedef CReadOnlyUFIntType CReadOnlySequenceNoType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ������޸ĺ�����
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CMillisecType;
typedef CReadOnlyUFIntType CReadOnlyMillisecType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ����ʱ���Ŷӵ������
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CTimeSortIDType;
typedef CReadOnlyUFIntType CReadOnlyTimeSortIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ��������
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CVolumeType;
typedef CReadOnlyUFIntType CReadOnlyVolumeType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ����Լ������
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CUnderlyingMultipleType;
typedef CReadOnlyUFIntType CReadOnlyUnderlyingMultipleType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ������������
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CVolumeMultipleType;
typedef CReadOnlyUFIntType CReadOnlyVolumeMultipleType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ��ͨѶ����
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CCommFluxType;
typedef CReadOnlyUFIntType CReadOnlyCommFluxType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ��ͨѶʱ�κ���
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CCommPhaseNoType;
typedef CReadOnlyUFIntType CReadOnlyCommPhaseNoType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ������ϵ�к���
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CSequenceSeriesType;
typedef CReadOnlyUFIntType CReadOnlySequenceSeriesType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ���Ự�����
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CSessionIDType;
typedef CReadOnlyUFIntType CReadOnlySessionIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ�����������
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CErrorIDType;
typedef CReadOnlyUFIntType CReadOnlyErrorIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ���������Ĵ�����
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CDataCenterIDType;
typedef CReadOnlyUFIntType CReadOnlyDataCenterIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ��ǰ�ñ����
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CFrontIDType;
typedef CReadOnlyUFIntType CReadOnlyFrontIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ�����������
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CRequestIDType;
typedef CReadOnlyUFIntType CReadOnlyRequestIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ�����������
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CTopicIDType;
typedef CReadOnlyUFIntType CReadOnlyTopicIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ��Dbmt�������
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CDbmtTopicIDType;
typedef CReadOnlyUFIntType CReadOnlyDbmtTopicIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ��Dbmt���к���
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CDbmtSequenceIDType;
typedef CReadOnlyUFIntType CReadOnlyDbmtSequenceIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ��DB���������
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CCommandNoType;
typedef CReadOnlyUFIntType CReadOnlyCommandNoType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ����������
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CSettlementIDType;
typedef CReadOnlyUFIntType CReadOnlySettlementIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ���ۼӴ�����
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CTotalNumsType;
typedef CReadOnlyUFIntType CReadOnlyTotalNumsType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ��ƫ��ʱ����
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CDiffSndType;
typedef CReadOnlyUFIntType CReadOnlyDiffSndType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ������ID��
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CTIDType;
typedef CReadOnlyUFIntType CReadOnlyTIDType;
	
/////////////////////////////////////////////////////////////////////////
///CIntType��һ��ʱ�����
/////////////////////////////////////////////////////////////////////////
typedef CUFIntType CILocalTimeType;
typedef CReadOnlyUFIntType CReadOnlyILocalTimeType;
	
/////////////////////////////////////////////////////////////////////////
///CLongType��һ������ʱ����
/////////////////////////////////////////////////////////////////////////
typedef CUFLongType CLongTimeType;
typedef CReadOnlyUFLongType CReadOnlyLongTimeType;

/////////////////////////////////////////////////////////////////////////
///CRangeIntType��һ���·���
/////////////////////////////////////////////////////////////////////////
typedef CUFRangeIntType<1,12> CMonthType;
typedef const CUFRangeIntType<1,12> CReadOnlyMonthType;
	
/////////////////////////////////////////////////////////////////////////
///CRangeIntType��һ����������
/////////////////////////////////////////////////////////////////////////
typedef CUFRangeIntType<0,1> CBoolType;
typedef const CUFRangeIntType<0,1> CReadOnlyBoolType;
	
/////////////////////////////////////////////////////////////////////////
///CRangeIntType��һ������
/////////////////////////////////////////////////////////////////////////
typedef CUFRangeIntType<1900,2100> CYearType;
typedef const CUFRangeIntType<1900,2100> CReadOnlyYearType;
	
/////////////////////////////////////////////////////////////////////////
///CRangeIntType��һ��������
/////////////////////////////////////////////////////////////////////////
typedef CUFRangeIntType<1,31> CDayType;
typedef const CUFRangeIntType<1,31> CReadOnlyDayType;
	
/////////////////////////////////////////////////////////////////////////
///CCharType��һ���ɽ�����Դ��
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CPriceSourceType;
typedef CReadOnlyUFCharType CReadOnlyPriceSourceType;

/////////////////////////////////////////////////////////////////////////
///CCharType��һ������Ȩ��
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CPriorityType;
typedef CReadOnlyUFCharType CReadOnlyPriorityType;

/////////////////////////////////////////////////////////////////////////
///CCharType��һ���ͻ��Ա���
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CClientGendreType;
typedef CReadOnlyUFCharType CReadOnlyClientGendreType;

/////////////////////////////////////////////////////////////////////////
///CCharType��һ���ͻ�״̬��
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CClientStatusType;
typedef CReadOnlyUFCharType CReadOnlyClientStatusType;

/////////////////////////////////////////////////////////////////////////
///CCharType��һ����Ա״̬��
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CParticipantStatusType;
typedef CReadOnlyUFCharType CReadOnlyParticipantStatusType;

/////////////////////////////////////////////////////////////////////////
///CCharType��һ�����׽�ɫ��
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CTradingRoleType;
typedef CReadOnlyUFCharType CReadOnlyTradingRoleType;

/////////////////////////////////////////////////////////////////////////
///CCharType��һ��ȡֵ��ʽ��
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CValueModeType;
typedef CReadOnlyUFCharType CReadOnlyValueModeType;

/////////////////////////////////////////////////////////////////////////
///CCharType��һ��������������
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CParticipantTypeType;
typedef CReadOnlyUFCharType CReadOnlyParticipantTypeType;

/////////////////////////////////////////////////////////////////////////
///CCharType��һ������������
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType COrderTypeType;
typedef CReadOnlyUFCharType CReadOnlyOrderTypeType;

/////////////////////////////////////////////////////////////////////////
///CCharType��һ���Զ������־��
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CIsAutoSuspendType;
typedef CReadOnlyUFCharType CReadOnlyIsAutoSuspendType;

/////////////////////////////////////////////////////////////////////////
///CCharType��һ����Լ��������״̬��
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CInstLifePhaseType;
typedef CReadOnlyUFCharType CReadOnlyInstLifePhaseType;

/////////////////////////////////////////////////////////////////////////
///CCharType��һ��ǿƽ��־��
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CForceCloseFlagType;
typedef CReadOnlyUFCharType CReadOnlyForceCloseFlagType;

/////////////////////////////////////////////////////////////////////////
///CCharType��һ��Ʒ��״̬��
/////////////////////////////////////////////////////////////////////////
typedef CUFCharType CProductStatusType;
typedef CReadOnlyUFCharType CReadOnlyProductStatusType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ������޸Ľ����û�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<15> CActiveUserIDType;
typedef const CUFStringType<15> CReadOnlyActiveUserIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ�������Ա�����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<10> CClearingPartIDType;
typedef const CUFStringType<10> CReadOnlyClearingPartIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ�����ر��������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<18> CCombOrderLocalIDType;
typedef const CUFStringType<18> CReadOnlyCombOrderLocalIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ�����ϵͳ���������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<18> CComOrderSysIDType;
typedef const CUFStringType<18> CReadOnlyComOrderSysIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���ڴ������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<60> CMemTableNameType;
typedef const CUFStringType<60> CReadOnlyMemTableNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ�����������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<30> COrderSysIDType;
typedef const CUFStringType<30> CReadOnlyOrderSysIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���ɽ������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CTradeIDType;
typedef const CUFStringType<20> CReadOnlyTradeIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���û�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<15> CUserIDType;
typedef const CUFStringType<15> CReadOnlyUserIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���û�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<15> CTraderIDType;
typedef const CUFStringType<15> CReadOnlyTraderIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���û�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<15> CUserType;
typedef const CUFStringType<15> CReadOnlyUserType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ�����׽׶α����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<22> CTradingSegementNoType;
typedef const CUFStringType<22> CReadOnlyTradingSegementNoType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ�����׽׶�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CTradingSegementNameType;
typedef const CUFStringType<20> CReadOnlyTradingSegementNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����Ա������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<50> CParticipantNameType;
typedef const CUFStringType<50> CReadOnlyParticipantNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����Ա�����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<10> CParticipantIDType;
typedef const CUFStringType<10> CReadOnlyParticipantIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����Ա�����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CParticipantAbbrType;
typedef const CUFStringType<20> CReadOnlyParticipantAbbrType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���г�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CMarketNameType;
typedef const CUFStringType<20> CReadOnlyMarketNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���г�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<10> CMarketIDType;
typedef const CUFStringType<10> CReadOnlyMarketIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��IP��ַ��
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CIPAddressType;
typedef const CUFStringType<20> CReadOnlyIPAddressType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��ǰ�û������ӷ�ʽ��
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<512> CFrontAddrType;
typedef const CUFStringType<512> CReadOnlyFrontAddrType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��Mac��ַ��
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CMacAddressType;
typedef const CUFStringType<20> CReadOnlyMacAddressType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����Լ������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CInstrumentNameType;
typedef const CUFStringType<20> CReadOnlyInstrumentNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��Ӫҵ��������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<6> CBranchIDType;
typedef const CUFStringType<6> CReadOnlyBranchIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����Լ�����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<30> CInstrumentIDType;
typedef const CUFStringType<30> CReadOnlyInstrumentIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����Լ�ڽ������Ĵ�����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<30> CExchangeInstIDType;
typedef const CUFStringType<30> CReadOnlyExchangeInstIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��֤��������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<50> CIdentifiedCardNoType;
typedef const CUFStringType<50> CReadOnlyIdentifiedCardNoType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��֤��������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<15> CIdentifiedCardTypeType;
typedef const CUFStringType<15> CReadOnlyIdentifiedCardTypeType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ������(��)ͨ����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<10> CExchangeIDType;
typedef const CUFStringType<10> CReadOnlyExchangeIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ������(��)��������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<30> CExchangeNameType;
typedef const CUFStringType<30> CReadOnlyExchangeNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����������������״̬��
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<1> CExchangeLifePhaseType;
typedef const CUFStringType<1> CReadOnlyExchangeLifePhaseType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CDateType;
typedef const CUFStringType<8> CReadOnlyDateType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���ֲ�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CPositionDateTypeType;
typedef const CUFStringType<8> CReadOnlyPositionDateTypeType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��ʱ����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CTimeType;
typedef const CUFStringType<8> CReadOnlyTimeType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����Ͽ�ƽ��־��
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<4> CCombOffsetFlagType;
typedef const CUFStringType<4> CReadOnlyCombOffsetFlagType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����Ϻ�Լ������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<80> CCombInstrumentIDType;
typedef const CUFStringType<80> CReadOnlyCombInstrumentIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���ͻ�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<1> CClientTypeType;
typedef const CUFStringType<1> CReadOnlyClientTypeType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���ͻ�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<80> CClientNameType;
typedef const CUFStringType<80> CReadOnlyClientNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���ͻ�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<18> CClientIDType;
typedef const CUFStringType<18> CReadOnlyClientIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���ʽ��ʺ���
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<12> CAccountIDType;
typedef const CUFStringType<12> CReadOnlyAccountIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ�����Ͷ���ױ���־��
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<4> CCombHedgeFlagType;
typedef const CUFStringType<4> CReadOnlyCombHedgeFlagType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��Ʒ����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<32> CProductType;
typedef const CUFStringType<32> CReadOnlyProductType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ�����ױ������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<18> CClientTradingIDType;
typedef const CUFStringType<18> CReadOnlyClientTradingIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��ϯλ����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<12> CSeatIDType;
typedef const CUFStringType<12> CReadOnlySeatIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��Ʒ��������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<40> CProductNameType;
typedef const CUFStringType<40> CReadOnlyProductNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����֤��ģ�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CMarginTemplateNoType;
typedef const CUFStringType<8> CReadOnlyMarginTemplateNoType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��ģ��������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<40> CTemplateNameType;
typedef const CUFStringType<40> CReadOnlyTemplateNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��������ģ������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CFeeTemplateNoType;
typedef const CUFStringType<8> CReadOnlyFeeTemplateNoType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���û����ر�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<22> CUserOrderLocalIDType;
typedef const CUFStringType<22> CReadOnlyUserOrderLocalIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���û����ر�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<22> COrderRefType;
typedef const CUFStringType<22> CReadOnlyOrderRefType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ�����ر��������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<32> COrderLocalIDType;
typedef const CUFStringType<32> CReadOnlyOrderLocalIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��Ͷ���߱����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<18> CInvestorIDType;
typedef const CUFStringType<18> CReadOnlyInvestorIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��Ͷ����������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<30> CInvestorNameType;
typedef const CUFStringType<30> CReadOnlyInvestorNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���û�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<30> CUserNameType;
typedef const CUFStringType<30> CReadOnlyUserNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���û��������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<4> CUserGroupIDType;
typedef const CUFStringType<4> CReadOnlyUserGroupIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<40> CPasswordType;
typedef const CUFStringType<40> CReadOnlyPasswordType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����ϢժҪ��
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<80> CAbstractType;
typedef const CUFStringType<80> CReadOnlyAbstractType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����Ʒ��Ϣ��
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<40> CProductInfoType;
typedef const CUFStringType<40> CReadOnlyProductInfoType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��Э����Ϣ��
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<40> CProtocolInfoType;
typedef const CUFStringType<40> CReadOnlyProtocolInfoType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��ҵ��Ԫ��
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CBusinessUnitType;
typedef const CUFStringType<20> CReadOnlyBusinessUnitType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ������ϵͳ������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<60> CTradingSystemNameType;
typedef const CUFStringType<60> CReadOnlyTradingSystemNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ������ϵͳ������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<60> CSystemNameType;
typedef const CUFStringType<60> CReadOnlySystemNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��DB����������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<64> CCommandTypeType;
typedef const CUFStringType<64> CReadOnlyCommandTypeType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ�����͹�˾������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<10> CBrokerIDType;
typedef const CUFStringType<10> CReadOnlyBrokerIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���û��Զ�����������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<64> CCustomType;
typedef const CUFStringType<64> CReadOnlyCustomType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CTradingDayType;
typedef const CUFStringType<8> CReadOnlyTradingDayType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ������������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<60> CTopicNameType;
typedef const CUFStringType<60> CReadOnlyTopicNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<12> COrderInsertFailedIDType;
typedef const CUFStringType<12> CReadOnlyOrderInsertFailedIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����ԭ����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<200> COrderInsertFailedReasonType;
typedef const CUFStringType<200> CReadOnlyOrderInsertFailedReasonType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��Ӫҵ����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<40> CDepartmentType;
typedef const CUFStringType<40> CReadOnlyDepartmentType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����֯����������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<40> CInstituteCodeType;
typedef const CUFStringType<40> CReadOnlyInstituteCodeType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���û�����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<4> CClientGroupType;
typedef const CUFStringType<4> CReadOnlyClientGroupType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����Ա�ʺ���
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CParticipantAccountType;
typedef const CUFStringType<20> CReadOnlyParticipantAccountType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����Ȩ���ܺ���
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<4> CGrantFuncSetType;
typedef const CUFStringType<4> CReadOnlyGrantFuncSetType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��Ʒ�ֱ����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<12> CProductIDType;
typedef const CUFStringType<12> CReadOnlyProductIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���ʽ���ˮ����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CAccountSeqNoType;
typedef const CUFStringType<20> CReadOnlyAccountSeqNoType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ�������������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CSettlementGroupIDType;
typedef const CUFStringType<8> CReadOnlySettlementGroupIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����¼ʱ����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CLoginTimeType;
typedef const CUFStringType<8> CReadOnlyLoginTimeType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ������ʱ����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CLocalTimeType;
typedef const CUFStringType<8> CReadOnlyLocalTimeType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��������ʱ����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CExchangeTimeType;
typedef const CUFStringType<8> CReadOnlyExchangeTimeType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ�����д�����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<3> CBankIDType;
typedef const CUFStringType<3> CReadOnlyBankIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ�����з����Ĵ�����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<4> CBankBrchIDType;
typedef const CUFStringType<4> CReadOnlyBankBrchIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ�������˺���
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<40> CBankAccountType;
typedef const CUFStringType<40> CReadOnlyBankAccountType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<100> CNameType;
typedef const CUFStringType<100> CReadOnlyNameType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��ҵ��������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<6> CTradeCodeType;
typedef const CUFStringType<6> CReadOnlyTradeCodeType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����ˮ����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<12> CSerialType;
typedef const CUFStringType<12> CReadOnlySerialType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��������־��
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<2> CDeviceIDType;
typedef const CUFStringType<2> CReadOnlyDeviceIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ���ڻ���˾���б�����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<32> CBankCodingForFutureType;
typedef const CUFStringType<32> CReadOnlyBankCodingForFutureType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ����¼��Ϣ��
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<256> CLoginInfoType;
typedef const CUFStringType<256> CReadOnlyLoginInfoType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ�����̶�����������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<1024> CSeatCustomType;
typedef const CUFStringType<1024> CReadOnlySeatCustomType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��QDP�������ı����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<10> CSystemIDType;
typedef const CUFStringType<10> CReadOnlySystemIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ��������Ϣ��
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<64> CServerAddrType;
typedef const CUFStringType<64> CReadOnlyServerAddrType;

/////////////////////////////////////////////////////////////////////////
///CVStringType��һ��������Ϣ��
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<80> CErrorMsgType;
typedef const CUFStringType<80> CReadOnlyErrorMsgType;

/////////////////////////////////////////////////////////////////////////
///CVStringType��һ���ֶ�����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<2048> CFieldNameType;
typedef const CUFStringType<2048> CReadOnlyFieldNameType;

/////////////////////////////////////////////////////////////////////////
///CVStringType��һ���ֶ�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<2048> CFieldContentType;
typedef const CUFStringType<2048> CReadOnlyFieldContentType;

/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ���ɽ���������
/////////////////////////////////////////////////////////////////////////
///�κ�����
#define VC_AV '1'
///��С����
#define VC_MV '2'
///ȫ������
#define VC_CV '3'

class CVolumeConditionType : public CUFCharType					
{														
public:													
	CVolumeConditionType(void)									
	{													
	}													
	CVolumeConditionType(const CVolumeConditionType &v)				
	{													
		setValue(v.getValue());							
	}													
	CVolumeConditionType(const char v)							
	{													
		setValue(v);									
	}													
	CVolumeConditionType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CVolumeConditionType& operator=(const CVolumeConditionType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CVolumeConditionType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CVolumeConditionType CReadOnlyVolumeConditionType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ�����뱾״̬ԭ����
/////////////////////////////////////////////////////////////////////////
///�Զ��л�
#define ER_Automatic '1'
///�ֶ��л�
#define ER_Manual '2'
///�۶�
#define ER_Fuse '3'

class CEnterReasonType : public CUFCharType					
{														
public:													
	CEnterReasonType(void)									
	{													
	}													
	CEnterReasonType(const CEnterReasonType &v)				
	{													
		setValue(v.getValue());							
	}													
	CEnterReasonType(const char v)							
	{													
		setValue(v);									
	}													
	CEnterReasonType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CEnterReasonType& operator=(const CEnterReasonType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CEnterReasonType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CEnterReasonType CReadOnlyEnterReasonType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ���ڴ����ݱ����������
/////////////////////////////////////////////////////////////////////////
///����
#define MDB_INSERT '0'
///����
#define MDB_UPDATE '1'
///ɾ��
#define MDB_DELETE '2'
///�ύ
#define MDB_COMMIT '3'

class CMdbActionTypeType : public CUFCharType					
{														
public:													
	CMdbActionTypeType(void)									
	{													
	}													
	CMdbActionTypeType(const CMdbActionTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CMdbActionTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CMdbActionTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CMdbActionTypeType& operator=(const CMdbActionTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CMdbActionTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CMdbActionTypeType CReadOnlyMdbActionTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��ǿƽԭ����
/////////////////////////////////////////////////////////////////////////
///��ǿƽ
#define FCR_NotForceClose '0'
///�ʽ���
#define FCR_LackDeposit '1'
///�ͻ�����
#define FCR_ClientOverPositionLimit '2'
///��Ա����
#define FCR_MemberOverPositionLimit '3'
///�ֲַ�������
#define FCR_NotMultiple '4'

class CForceCloseReasonType : public CUFCharType					
{														
public:													
	CForceCloseReasonType(void)									
	{													
	}													
	CForceCloseReasonType(const CForceCloseReasonType &v)				
	{													
		setValue(v.getValue());							
	}													
	CForceCloseReasonType(const char v)							
	{													
		setValue(v);									
	}													
	CForceCloseReasonType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CForceCloseReasonType& operator=(const CForceCloseReasonType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CForceCloseReasonType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01234"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01234",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01234",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CForceCloseReasonType CReadOnlyForceCloseReasonType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ����Լ����״̬��
/////////////////////////////////////////////////////////////////////////
///����ǰ
#define IS_BeforeTrading '0'
///�ǽ���
#define IS_NoTrading '1'
///��������
#define IS_Continous '2'
///���Ͼ��۱���
#define IS_AuctionOrdering '3'
///���Ͼ��ۼ۸�ƽ��
#define IS_AuctionBalance '4'
///���Ͼ��۴��
#define IS_AuctionMatch '5'
///����
#define IS_Closed '6'

class CInstrumentStatusType : public CUFCharType					
{														
public:													
	CInstrumentStatusType(void)									
	{													
	}													
	CInstrumentStatusType(const CInstrumentStatusType &v)				
	{													
		setValue(v.getValue());							
	}													
	CInstrumentStatusType(const char v)							
	{													
		setValue(v);									
	}													
	CInstrumentStatusType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CInstrumentStatusType& operator=(const CInstrumentStatusType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CInstrumentStatusType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0123456"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0123456",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0123456",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CInstrumentStatusType CReadOnlyInstrumentStatusType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ����ƽ��־��
/////////////////////////////////////////////////////////////////////////
///����
#define OF_Open '0'
///ƽ��
#define OF_Close '1'
///ǿƽ
#define OF_ForceClose '2'
///ƽ��
#define OF_CloseToday '3'
///ƽ��
#define OF_CloseYesterday '4'

class COffsetFlagType : public CUFCharType					
{														
public:													
	COffsetFlagType(void)									
	{													
	}													
	COffsetFlagType(const COffsetFlagType &v)				
	{													
		setValue(v.getValue());							
	}													
	COffsetFlagType(const char v)							
	{													
		setValue(v);									
	}													
	COffsetFlagType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	COffsetFlagType& operator=(const COffsetFlagType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	COffsetFlagType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01234"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01234",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01234",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const COffsetFlagType CReadOnlyOffsetFlagType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ�������۸�������
/////////////////////////////////////////////////////////////////////////
///�����
#define OPT_AnyPrice '1'
///�޼�
#define OPT_LimitPrice '2'
///���ż�
#define OPT_BestPrice '3'
///�嵵��
#define OPT_FiveLevelPrice '4'

class COrderPriceTypeType : public CUFCharType					
{														
public:													
	COrderPriceTypeType(void)									
	{													
	}													
	COrderPriceTypeType(const COrderPriceTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	COrderPriceTypeType(const char v)							
	{													
		setValue(v);									
	}													
	COrderPriceTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	COrderPriceTypeType& operator=(const COrderPriceTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	COrderPriceTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("1234"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("1234",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("1234",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const COrderPriceTypeType CReadOnlyOrderPriceTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ������״̬��
/////////////////////////////////////////////////////////////////////////
///ȫ���ɽ�
#define OS_AllTraded '0'
///���ֳɽ����ڶ�����
#define OS_PartTradedQueueing '1'
///���ֳɽ����ڶ�����
#define OS_PartTradedNotQueueing '2'
///δ�ɽ����ڶ�����
#define OS_NoTradeQueueing '3'
///δ�ɽ����ڶ�����
#define OS_NoTradeNotQueueing '4'
///����
#define OS_Canceled '5'
///�����ѱ��뽻����δӦ��
#define OS_AcceptedNoReply '6'

class COrderStatusType : public CUFCharType					
{														
public:													
	COrderStatusType(void)									
	{													
	}													
	COrderStatusType(const COrderStatusType &v)				
	{													
		setValue(v.getValue());							
	}													
	COrderStatusType(const char v)							
	{													
		setValue(v);									
	}													
	COrderStatusType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	COrderStatusType& operator=(const COrderStatusType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	COrderStatusType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0123456"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0123456",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0123456",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const COrderStatusType CReadOnlyOrderStatusType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ���ڴ��仯������
/////////////////////////////////////////////////////////////////////////
///����
#define MTC_INSERT '0'
///�޸�
#define MTC_UPDATE '1'
///ɾ��
#define MTC_DELETE '2'
///�ύ
#define MTC_COMMIT '3'

class CMemtableChangeTypeType : public CUFCharType					
{														
public:													
	CMemtableChangeTypeType(void)									
	{													
	}													
	CMemtableChangeTypeType(const CMemtableChangeTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CMemtableChangeTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CMemtableChangeTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CMemtableChangeTypeType& operator=(const CMemtableChangeTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CMemtableChangeTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CMemtableChangeTypeType CReadOnlyMemtableChangeTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ���û�������
/////////////////////////////////////////////////////////////////////////
///��Ȼ��
#define UT_Person '1'
///��Ʋ�Ʒ
#define UT_Product '2'
///�ڻ���˾����Ա
#define UT_Manager '3'
///ϯλ
#define UT_Seat '4'

class CUserTypeType : public CUFCharType					
{														
public:													
	CUserTypeType(void)									
	{													
	}													
	CUserTypeType(const CUserTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CUserTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CUserTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CUserTypeType& operator=(const CUserTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CUserTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("1234"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("1234",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("1234",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CUserTypeType CReadOnlyUserTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ������Ȩ����
/////////////////////////////////////////////////////////////////////////
///���Խ���
#define TR_Allow '0'
///ֻ��ƽ��
#define TR_CloseOnly '1'
///���ܽ���
#define TR_Forbidden '2'

class CTradingRightType : public CUFCharType					
{														
public:													
	CTradingRightType(void)									
	{													
	}													
	CTradingRightType(const CTradingRightType &v)				
	{													
		setValue(v.getValue());							
	}													
	CTradingRightType(const char v)							
	{													
		setValue(v);									
	}													
	CTradingRightType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CTradingRightType& operator=(const CTradingRightType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CTradingRightType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("012"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("012",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("012",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CTradingRightType CReadOnlyTradingRightType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ����Ч��������
/////////////////////////////////////////////////////////////////////////
///������ɣ�������
#define TC_IOC '1'
///������Ч
#define TC_GFS '2'
///������Ч
#define TC_GFD '3'
///ָ������ǰ��Ч
#define TC_GTD '4'
///����ǰ��Ч
#define TC_GTC '5'
///���Ͼ�����Ч
#define TC_GFA '6'

class CTimeConditionType : public CUFCharType					
{														
public:													
	CTimeConditionType(void)									
	{													
	}													
	CTimeConditionType(const CTimeConditionType &v)				
	{													
		setValue(v.getValue());							
	}													
	CTimeConditionType(const char v)							
	{													
		setValue(v);									
	}													
	CTimeConditionType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CTimeConditionType& operator=(const CTimeConditionType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CTimeConditionType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123456"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123456",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123456",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CTimeConditionType CReadOnlyTimeConditionType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ���ֲֶ�շ�����
/////////////////////////////////////////////////////////////////////////
///��
#define PD_Net '1'
///��ͷ
#define PD_Long '2'
///��ͷ
#define PD_Short '3'

class CPosiDirectionType : public CUFCharType					
{														
public:													
	CPosiDirectionType(void)									
	{													
	}													
	CPosiDirectionType(const CPosiDirectionType &v)				
	{													
		setValue(v.getValue());							
	}													
	CPosiDirectionType(const char v)							
	{													
		setValue(v);									
	}													
	CPosiDirectionType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CPosiDirectionType& operator=(const CPosiDirectionType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CPosiDirectionType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CPosiDirectionType CReadOnlyPosiDirectionType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��������Դ��
/////////////////////////////////////////////////////////////////////////
///���Բ�����
#define OS_Participant '0'
///���Թ���Ա
#define OS_Administrator '1'

class COrderSourceType : public CUFCharType					
{														
public:													
	COrderSourceType(void)									
	{													
	}													
	COrderSourceType(const COrderSourceType &v)				
	{													
		setValue(v.getValue());							
	}													
	COrderSourceType(const char v)							
	{													
		setValue(v);									
	}													
	COrderSourceType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	COrderSourceType& operator=(const COrderSourceType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	COrderSourceType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const COrderSourceType CReadOnlyOrderSourceType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ����Ա������
/////////////////////////////////////////////////////////////////////////
///���׻�Ա
#define MT_Trading '0'
///�����Ա
#define MT_Settlement '1'

class CMemberTypeType : public CUFCharType					
{														
public:													
	CMemberTypeType(void)									
	{													
	}													
	CMemberTypeType(const CMemberTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CMemberTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CMemberTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CMemberTypeType& operator=(const CMemberTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CMemberTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CMemberTypeType CReadOnlyMemberTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ������������
/////////////////////////////////////////////////////////////////////////
///��
#define D_Buy '0'
///��
#define D_Sell '1'
///��
#define D_Net '2'

class CDirectionType : public CUFCharType					
{														
public:													
	CDirectionType(void)									
	{													
	}													
	CDirectionType(const CDirectionType &v)				
	{													
		setValue(v.getValue());							
	}													
	CDirectionType(const char v)							
	{													
		setValue(v);									
	}													
	CDirectionType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CDirectionType& operator=(const CDirectionType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CDirectionType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("012"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("012",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("012",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CDirectionType CReadOnlyDirectionType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��������
/////////////////////////////////////////////////////////////////////////
///�����
#define C_CNY '1'
///��Ԫ
#define C_UDOLLAR '2'
///�¼���Ԫ
#define C_SGD '3'

class CCurrencyType : public CUFCharType					
{														
public:													
	CCurrencyType(void)									
	{													
	}													
	CCurrencyType(const CCurrencyType &v)				
	{													
		setValue(v.getValue());							
	}													
	CCurrencyType(const char v)							
	{													
		setValue(v);									
	}													
	CCurrencyType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CCurrencyType& operator=(const CCurrencyType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CCurrencyType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CCurrencyType CReadOnlyCurrencyType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ�������־��
/////////////////////////////////////////////////////////////////////////
///�Ѵ���
#define DF_Done '1'
///�ȴ�����
#define DF_Wait '2'

class CDealFlagType : public CUFCharType					
{														
public:													
	CDealFlagType(void)									
	{													
	}													
	CDealFlagType(const CDealFlagType &v)				
	{													
		setValue(v.getValue());							
	}													
	CDealFlagType(const char v)							
	{													
		setValue(v);									
	}													
	CDealFlagType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CDealFlagType& operator=(const CDealFlagType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CDealFlagType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("12"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("12",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("12",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CDealFlagType CReadOnlyDealFlagType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ�����������
/////////////////////////////////////////////////////////////////////////
///���
#define AD_In '1'
///����
#define AD_Out '2'

class CAccountDirectionType : public CUFCharType					
{														
public:													
	CAccountDirectionType(void)									
	{													
	}													
	CAccountDirectionType(const CAccountDirectionType &v)				
	{													
		setValue(v.getValue());							
	}													
	CAccountDirectionType(const char v)							
	{													
		setValue(v);									
	}													
	CAccountDirectionType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CAccountDirectionType& operator=(const CAccountDirectionType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CAccountDirectionType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("12"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("12",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("12",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CAccountDirectionType CReadOnlyAccountDirectionType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��ϵͳ״̬��
/////////////////////////////////////////////////////////////////////////
///�������ݿɲ���״̬
#define SS_DbOperational '0'
///�������ݿ�ʼ����
#define SS_DbBeginImporting '1'
///���ݿ��ϳ�
#define SS_SyncDataReady '2'
///����ͬ����
#define SS_DataSyncing '3'
///�������ϳ�
#define SS_DataSynced '4'
///��Լ�����������³��ɹ�
#define SS_InstrumentTradingDayDown '5'
///���ս��׽���
#define SS_TradingDayOver '6'

class CSystemStatusType : public CUFCharType					
{														
public:													
	CSystemStatusType(void)									
	{													
	}													
	CSystemStatusType(const CSystemStatusType &v)				
	{													
		setValue(v.getValue());							
	}													
	CSystemStatusType(const char v)							
	{													
		setValue(v);									
	}													
	CSystemStatusType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CSystemStatusType& operator=(const CSystemStatusType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CSystemStatusType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0123456"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0123456",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0123456",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CSystemStatusType CReadOnlySystemStatusType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��Ͷ���ױ���־��
/////////////////////////////////////////////////////////////////////////
///Ͷ��
#define CHF_Speculation '1'
///����
#define CHF_Arbitrage '2'
///�ױ�
#define CHF_Hedge '3'
///������
#define CHF_MarketMaker '4'

class CHedgeFlagType : public CUFCharType					
{														
public:													
	CHedgeFlagType(void)									
	{													
	}													
	CHedgeFlagType(const CHedgeFlagType &v)				
	{													
		setValue(v.getValue());							
	}													
	CHedgeFlagType(const char v)							
	{													
		setValue(v);									
	}													
	CHedgeFlagType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CHedgeFlagType& operator=(const CHedgeFlagType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CHedgeFlagType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("1234"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("1234",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("1234",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CHedgeFlagType CReadOnlyHedgeFlagType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��������־��
/////////////////////////////////////////////////////////////////////////
///ɾ��
#define AF_Delete '0'
///����
#define AF_Suspend '1'
///����
#define AF_Active '2'
///�޸�
#define AF_Modify '3'

class CActionFlagType : public CUFCharType					
{														
public:													
	CActionFlagType(void)									
	{													
	}													
	CActionFlagType(const CActionFlagType &v)				
	{													
		setValue(v.getValue());							
	}													
	CActionFlagType(const char v)							
	{													
		setValue(v);									
	}													
	CActionFlagType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CActionFlagType& operator=(const CActionFlagType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CActionFlagType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CActionFlagType CReadOnlyActionFlagType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ����������״̬��
/////////////////////////////////////////////////////////////////////////
///�Ѿ��ύ
#define OAS_Submitted 'a'
///�Ѿ�����
#define OAS_Accepted 'b'
///�Ѿ����ܾ�
#define OAS_Rejected 'c'

class COrderActionStatusType : public CUFCharType					
{														
public:													
	COrderActionStatusType(void)									
	{													
	}													
	COrderActionStatusType(const COrderActionStatusType &v)				
	{													
		setValue(v.getValue());							
	}													
	COrderActionStatusType(const char v)							
	{													
		setValue(v);									
	}													
	COrderActionStatusType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	COrderActionStatusType& operator=(const COrderActionStatusType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	COrderActionStatusType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("abc"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("abc",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("abc",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const COrderActionStatusType CReadOnlyOrderActionStatusType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ����֤��ȡֵģʽ��
/////////////////////////////////////////////////////////////////////////
///������
#define MVM_Ratio '1'
///������
#define MVM_Amt '2'

class CMarginValueModeType : public CUFCharType					
{														
public:													
	CMarginValueModeType(void)									
	{													
	}													
	CMarginValueModeType(const CMarginValueModeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CMarginValueModeType(const char v)							
	{													
		setValue(v);									
	}													
	CMarginValueModeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CMarginValueModeType& operator=(const CMarginValueModeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CMarginValueModeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("12"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("12",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("12",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CMarginValueModeType CReadOnlyMarginValueModeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��������ȡֵģʽ��
/////////////////////////////////////////////////////////////////////////
///������
#define FVM_Ratio '1'
///������
#define FVM_Amt '2'

class CFeeValueModeType : public CUFCharType					
{														
public:													
	CFeeValueModeType(void)									
	{													
	}													
	CFeeValueModeType(const CFeeValueModeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CFeeValueModeType(const char v)							
	{													
		setValue(v);									
	}													
	CFeeValueModeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CFeeValueModeType& operator=(const CFeeValueModeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CFeeValueModeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("12"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("12",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("12",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CFeeValueModeType CReadOnlyFeeValueModeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ������������ͬ��״̬��
/////////////////////////////////////////////////////////////////////////
///δͬ��
#define DS_Asynchronous '1'
///ͬ����
#define DS_Synchronizing '2'
///��ͬ��
#define DS_Synchronized '3'

class CDataSyncStatusType : public CUFCharType					
{														
public:													
	CDataSyncStatusType(void)									
	{													
	}													
	CDataSyncStatusType(const CDataSyncStatusType &v)				
	{													
		setValue(v.getValue());							
	}													
	CDataSyncStatusType(const char v)							
	{													
		setValue(v);									
	}													
	CDataSyncStatusType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CDataSyncStatusType& operator=(const CDataSyncStatusType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CDataSyncStatusType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CDataSyncStatusType CReadOnlyDataSyncStatusType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ���ֲ�������
/////////////////////////////////////////////////////////////////////////
///���ֲ�
#define PT_Net '1'
///�ۺϳֲ�
#define PT_Gross '2'

class CPositionTypeType : public CUFCharType					
{														
public:													
	CPositionTypeType(void)									
	{													
	}													
	CPositionTypeType(const CPositionTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CPositionTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CPositionTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CPositionTypeType& operator=(const CPositionTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CPositionTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("12"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("12",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("12",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CPositionTypeType CReadOnlyPositionTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ����Ȩ������
/////////////////////////////////////////////////////////////////////////
///����Ȩ
#define OT_NotOptions '0'
///����
#define OT_CallOptions '1'
///����
#define OT_PutOptions '2'

class COptionsTypeType : public CUFCharType					
{														
public:													
	COptionsTypeType(void)									
	{													
	}													
	COptionsTypeType(const COptionsTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	COptionsTypeType(const char v)							
	{													
		setValue(v);									
	}													
	COptionsTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	COptionsTypeType& operator=(const COptionsTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	COptionsTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("012"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("012",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("012",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const COptionsTypeType CReadOnlyOptionsTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��ϯλ״̬��
/////////////////////////////////////////////////////////////////////////
///����Ծ
#define SS_NotActive '0'
///�ѵ�¼
#define SS_Login '1'
///�ѵǳ�
#define SS_Logout '2'

class CSeatStatusType : public CUFCharType					
{														
public:													
	CSeatStatusType(void)									
	{													
	}													
	CSeatStatusType(const CSeatStatusType &v)				
	{													
		setValue(v.getValue());							
	}													
	CSeatStatusType(const char v)							
	{													
		setValue(v);									
	}													
	CSeatStatusType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CSeatStatusType& operator=(const CSeatStatusType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CSeatStatusType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("012"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("012",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("012",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CSeatStatusType CReadOnlySeatStatusType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��������Դ��
/////////////////////////////////////////////////////////////////////////
///�û�
#define AS_User '0'
///�ڲ�
#define AS_Internal '1'
///����Ա
#define AS_Administrator '2'

class CActionSourceType : public CUFCharType					
{														
public:													
	CActionSourceType(void)									
	{													
	}													
	CActionSourceType(const CActionSourceType &v)				
	{													
		setValue(v.getValue());							
	}													
	CActionSourceType(const char v)							
	{													
		setValue(v);									
	}													
	CActionSourceType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CActionSourceType& operator=(const CActionSourceType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CActionSourceType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("012"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("012",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("012",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CActionSourceType CReadOnlyActionSourceType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ���Ƿ��Ծ��
/////////////////////////////////////////////////////////////////////////
///����Ծ
#define UIA_NoActive '0'
///��Ծ
#define UIA_Active '1'

class CIsActiveType : public CUFCharType					
{														
public:													
	CIsActiveType(void)									
	{													
	}													
	CIsActiveType(const CIsActiveType &v)				
	{													
		setValue(v.getValue());							
	}													
	CIsActiveType(const char v)							
	{													
		setValue(v);									
	}													
	CIsActiveType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CIsActiveType& operator=(const CIsActiveType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CIsActiveType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CIsActiveType CReadOnlyIsActiveType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��ʹ��api������
/////////////////////////////////////////////////////////////////////////
///�ڲ�Link
#define ALT_INNER '0'
///QDPMDLink
#define ALT_QDPMD 'g'
///QTestLink
#define ALT_QDPTEST 'q'
///APEXLink
#define ALT_APEX 'p'

class CApiLinkTypeType : public CUFCharType					
{														
public:													
	CApiLinkTypeType(void)									
	{													
	}													
	CApiLinkTypeType(const CApiLinkTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CApiLinkTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CApiLinkTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CApiLinkTypeType& operator=(const CApiLinkTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CApiLinkTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0gqp"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0gqp",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0gqp",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CApiLinkTypeType CReadOnlyApiLinkTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ������������
/////////////////////////////////////////////////////////////////////////
///����
#define CC_Immediately '1'
///ֹ��
#define CC_Touch '2'
///ֹӮ
#define CC_TouchProfit '3'
///Ԥ��
#define CC_ParkedOrder '4'
///���¼۴���������
#define CC_LastPriceGreaterThanStopPrice '5'
///���¼۴��ڵ���������
#define CC_LastPriceGreaterEqualStopPrice '6'
///���¼�С��������
#define CC_LastPriceLesserThanStopPrice '7'
///���¼�С�ڵ���������
#define CC_LastPriceLesserEqualStopPrice '8'
///��һ�۴���������
#define CC_AskPriceGreaterThanStopPrice '9'
///��һ�۴��ڵ���������
#define CC_AskPriceGreaterEqualStopPrice 'A'
///��һ��С��������
#define CC_AskPriceLesserThanStopPrice 'B'
///��һ��С�ڵ���������
#define CC_AskPriceLesserEqualStopPrice 'C'
///��һ�۴���������
#define CC_BidPriceGreaterThanStopPrice 'D'
///��һ�۴��ڵ���������
#define CC_BidPriceGreaterEqualStopPrice 'E'
///��һ��С��������
#define CC_BidPriceLesserThanStopPrice 'F'
///��һ��С�ڵ���������
#define CC_BidPriceLesserEqualStopPrice 'H'

class CContingentConditionType : public CUFCharType					
{														
public:													
	CContingentConditionType(void)									
	{													
	}													
	CContingentConditionType(const CContingentConditionType &v)				
	{													
		setValue(v.getValue());							
	}													
	CContingentConditionType(const char v)							
	{													
		setValue(v);									
	}													
	CContingentConditionType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CContingentConditionType& operator=(const CContingentConditionType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CContingentConditionType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123456789ABCDEFH"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123456789ABCDEFH",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123456789ABCDEFH",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CContingentConditionType CReadOnlyContingentConditionType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ����Ʒ������
/////////////////////////////////////////////////////////////////////////
///δ֪����
#define PC_Unknown '0'
///�ڻ�
#define PC_Futures '1'
///��Ȩ
#define PC_Options '2'
///���
#define PC_Combination '3'
///����
#define PC_Spot '4'
///��ת��
#define PC_EFP '5'
///֤ȯ
#define PC_Stocks '7'
///��Ʊ��Ȩ
#define PC_StockOptions '8'

class CProductClassType : public CUFCharType					
{														
public:													
	CProductClassType(void)									
	{													
	}													
	CProductClassType(const CProductClassType &v)				
	{													
		setValue(v.getValue());							
	}													
	CProductClassType(const char v)							
	{													
		setValue(v);									
	}													
	CProductClassType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CProductClassType& operator=(const CProductClassType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CProductClassType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01234578"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01234578",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01234578",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CProductClassType CReadOnlyProductClassType;		


/////////////////////////////////////////////////////////////////////////
///CStringType��һ����Ʒ�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<8> CProductGroupIDType;
typedef const CUFStringType<8> CReadOnlyProductGroupIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ�����ִ�����
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<3> CCurrencyIDType;
typedef const CUFStringType<3> CReadOnlyCurrencyIDType;

/////////////////////////////////////////////////////////////////////////
///CStringType��һ������������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<20> CCurrencyNameType;
typedef const CUFStringType<20> CReadOnlyCurrencyNameType;

/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ����ϱ�֤��������
/////////////////////////////////////////////////////////////////////////
///���ȱ�֤�����
#define MCT_SingleLeg '0'
///��Լ���߱�֤�����
#define MCT_BigLeg '1'
///��Ϻ�Լ��֤��
#define MCT_CombMargin '2'
///Span��֤��
#define MCT_SpanMargin '3'
///���ʣ���Լ������
#define MCT_CombLeftMaxMargin '4'
///���ʣ���Լ˫��
#define MCT_CombLeftAllMargin '5'
///�̺�󵥱�����˫��
#define MCT_TradedBigLeg '6'
///��Լ����
#define MCT_InstrumentBigLeg '7'

class CClientMarginCombTypeType : public CUFCharType					
{														
public:													
	CClientMarginCombTypeType(void)									
	{													
	}													
	CClientMarginCombTypeType(const CClientMarginCombTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CClientMarginCombTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CClientMarginCombTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CClientMarginCombTypeType& operator=(const CClientMarginCombTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CClientMarginCombTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01234567"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01234567",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01234567",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CClientMarginCombTypeType CReadOnlyClientMarginCombTypeType;		


/////////////////////////////////////////////////////////////////////////
///CStringType��һ����Լ�������
/////////////////////////////////////////////////////////////////////////
typedef CUFStringType<30> CInstrumentGroupIDType;
typedef const CUFStringType<30> CReadOnlyInstrumentGroupIDType;

/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��ҵ�������
/////////////////////////////////////////////////////////////////////////
///��ͨ
#define BT_Normal '1'
///����
#define BT_Cancel '2'
///ETF����
#define BT_AppliedForRedeemed '3'
///�����嵵��ʱ�ɽ�ʣ�೷��
#define BT_FiveLevelIOC '4'
///�����嵵��ʱ�ɽ�ʣ��ת�޼�
#define BT_FiveLevelGFD '5'
///��ʱ�ɽ�ʣ�೷��
#define BT_BestPriceIOC '6'
///ȫ��ɽ�����
#define BT_FOK '7'
///�������ż۸�
#define BT_SelfGFD '8'
///�Է����ż۸�
#define BT_CpGFD '9'
///�����������걨
#define BT_SGEMidApp 'a'
///������ϵ�
#define BT_Combination 'b'
///��������ϵ�
#define BT_Grab 'c'
///�������ӽ����걨
#define BT_SGEDeferDeliApp 'd'
///������
#define BT_SWAP 'e'

class CBusinessTypeType : public CUFCharType					
{														
public:													
	CBusinessTypeType(void)									
	{													
	}													
	CBusinessTypeType(const CBusinessTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CBusinessTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CBusinessTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CBusinessTypeType& operator=(const CBusinessTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CBusinessTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123456789abcde"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123456789abcde",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123456789abcde",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CBusinessTypeType CReadOnlyBusinessTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ������״̬��
/////////////////////////////////////////////////////////////////////////
///������ȷ
#define PS_OK '0'
///�������Ժ��ѯ
#define PS_PROCESSING '1'
///���ڳ���
#define PS_REVERSING '2'
///����ʧ��
#define PS_REVFAIL '3'
///������ȷ
#define PS_REVOK '4'

class CProcStatusType : public CUFCharType					
{														
public:													
	CProcStatusType(void)									
	{													
	}													
	CProcStatusType(const CProcStatusType &v)				
	{													
		setValue(v.getValue());							
	}													
	CProcStatusType(const char v)							
	{													
		setValue(v);									
	}													
	CProcStatusType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CProcStatusType& operator=(const CProcStatusType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CProcStatusType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01234"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01234",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01234",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CProcStatusType CReadOnlyProcStatusType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��ת�˽���״̬��
/////////////////////////////////////////////////////////////////////////
///����
#define TS_TRFS_Normal '0'
///������
#define TS_TRFS_Repealed '1'

class CTransferStatusType : public CUFCharType					
{														
public:													
	CTransferStatusType(void)									
	{													
	}													
	CTransferStatusType(const CTransferStatusType &v)				
	{													
		setValue(v.getValue());							
	}													
	CTransferStatusType(const char v)							
	{													
		setValue(v);									
	}													
	CTransferStatusType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CTransferStatusType& operator=(const CTransferStatusType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CTransferStatusType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CTransferStatusType CReadOnlyTransferStatusType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ������֧����־��
/////////////////////////////////////////////////////////////////////////
///�����淽֧������
#define FPF_FPF_BEN '0'
///�ɷ��ͷ�֧������
#define FPF_FPF_OUR '1'
///�ɷ��ͷ�֧������ķ��ã����淽֧�����ܵķ���
#define FPF_FPF_SHA '2'

class CFeePayFlagType : public CUFCharType					
{														
public:													
	CFeePayFlagType(void)									
	{													
	}													
	CFeePayFlagType(const CFeePayFlagType &v)				
	{													
		setValue(v.getValue());							
	}													
	CFeePayFlagType(const char v)							
	{													
		setValue(v);									
	}													
	CFeePayFlagType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CFeePayFlagType& operator=(const CFeePayFlagType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CFeePayFlagType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("012"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("012",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("012",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CFeePayFlagType CReadOnlyFeePayFlagType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ�������־��
/////////////////////////////////////////////////////////////////////////
///���˶�
#define PF_BPWDF_NoCheck '0'
///���ĺ˶�
#define PF_BPWDF_BlankCheck '1'
///���ĺ˶�
#define PF_BPWDF_EncryptCheck '2'

class CPwdFlagType : public CUFCharType					
{														
public:													
	CPwdFlagType(void)									
	{													
	}													
	CPwdFlagType(const CPwdFlagType &v)				
	{													
		setValue(v.getValue());							
	}													
	CPwdFlagType(const char v)							
	{													
		setValue(v);									
	}													
	CPwdFlagType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CPwdFlagType& operator=(const CPwdFlagType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CPwdFlagType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("012"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("012",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("012",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CPwdFlagType CReadOnlyPwdFlagType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ�������˺�������
/////////////////////////////////////////////////////////////////////////
///����
#define BAT_VBAT_BankBook '1'
///���
#define BAT_VBAT_BankCard '2'
///���ÿ�
#define BAT_VBAT_CreditCard '3'

class CBankAccTypeType : public CUFCharType					
{														
public:													
	CBankAccTypeType(void)									
	{													
	}													
	CBankAccTypeType(const CBankAccTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CBankAccTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CBankAccTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CBankAccTypeType& operator=(const CBankAccTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CBankAccTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CBankAccTypeType CReadOnlyBankAccTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ���Ƿ��־��
/////////////////////////////////////////////////////////////////////////
///��
#define YNI_YNI_Yes '0'
///��
#define YNI_YNI_No '1'

class CYesNoIndicatorType : public CUFCharType					
{														
public:													
	CYesNoIndicatorType(void)									
	{													
	}													
	CYesNoIndicatorType(const CYesNoIndicatorType &v)				
	{													
		setValue(v.getValue());							
	}													
	CYesNoIndicatorType(const char v)							
	{													
		setValue(v);									
	}													
	CYesNoIndicatorType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CYesNoIndicatorType& operator=(const CYesNoIndicatorType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CYesNoIndicatorType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CYesNoIndicatorType CReadOnlyYesNoIndicatorType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ����Ч��־��
/////////////////////////////////////////////////////////////////////////
///δȷ��
#define ALF_AVAF_Invalid '0'
///��Ч
#define ALF_AVAF_Valid '1'
///����
#define ALF_AVAF_Repeal '2'
///ʧ��
#define ALF_AVAF_FAIL '3'

class CAvailabilityFlagType : public CUFCharType					
{														
public:													
	CAvailabilityFlagType(void)									
	{													
	}													
	CAvailabilityFlagType(const CAvailabilityFlagType &v)				
	{													
		setValue(v.getValue());							
	}													
	CAvailabilityFlagType(const char v)							
	{													
		setValue(v);									
	}													
	CAvailabilityFlagType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CAvailabilityFlagType& operator=(const CAvailabilityFlagType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CAvailabilityFlagType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0123"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0123",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0123",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CAvailabilityFlagType CReadOnlyAvailabilityFlagType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ����������֧��������
/////////////////////////////////////////////////////////////////////////
///�ึ��
#define PD_Buy '0'
///�ո���
#define PD_Sell '1'
///֧������δ��
#define PD_Unknown '2'

class CPayDirectionType : public CUFCharType					
{														
public:													
	CPayDirectionType(void)									
	{													
	}													
	CPayDirectionType(const CPayDirectionType &v)				
	{													
		setValue(v.getValue());							
	}													
	CPayDirectionType(const char v)							
	{													
		setValue(v);									
	}													
	CPayDirectionType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CPayDirectionType& operator=(const CPayDirectionType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CPayDirectionType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("012"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("012",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("012",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CPayDirectionType CReadOnlyPayDirectionType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��ִ��������
/////////////////////////////////////////////////////////////////////////
///ִ��
#define AT_Exec '1'
///����
#define AT_Abandon '2'

class CActionTypeType : public CUFCharType					
{														
public:													
	CActionTypeType(void)									
	{													
	}													
	CActionTypeType(const CActionTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CActionTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CActionTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CActionTypeType& operator=(const CActionTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CActionTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("12"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("12",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("12",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CActionTypeType CReadOnlyActionTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ����Ȩ��Ȩ���Ƿ����ڻ�ͷ��ı����
/////////////////////////////////////////////////////////////////////////
///����
#define RPFT_Reserve '0'
///������
#define RPFT_UnReserve '1'

class CReservePositionFlagTypeType : public CUFCharType					
{														
public:													
	CReservePositionFlagTypeType(void)									
	{													
	}													
	CReservePositionFlagTypeType(const CReservePositionFlagTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CReservePositionFlagTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CReservePositionFlagTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CReservePositionFlagTypeType& operator=(const CReservePositionFlagTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CReservePositionFlagTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CReservePositionFlagTypeType CReadOnlyReservePositionFlagTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ����Ȩ��Ȩ�����ɵ�ͷ���Ƿ��Զ�ƽ����
/////////////////////////////////////////////////////////////////////////
///�Զ�ƽ��
#define CFT_AutoClose '0'
///�����Զ�ƽ��
#define CFT_NotToClose '1'

class CCloseFlagTypeType : public CUFCharType					
{														
public:													
	CCloseFlagTypeType(void)									
	{													
	}													
	CCloseFlagTypeType(const CCloseFlagTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CCloseFlagTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CCloseFlagTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CCloseFlagTypeType& operator=(const CCloseFlagTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CCloseFlagTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("01"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("01",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("01",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CCloseFlagTypeType CReadOnlyCloseFlagTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��ִ�н����
/////////////////////////////////////////////////////////////////////////
///û��ִ��
#define ERT_NoExec 'n'
///�Ѿ�ȡ��
#define ERT_Canceled 'c'
///ִ�гɹ�
#define ERT_OK '0'
///δ֪
#define ERT_Unknown 'a'

class CExecResultTypeType : public CUFCharType					
{														
public:													
	CExecResultTypeType(void)									
	{													
	}													
	CExecResultTypeType(const CExecResultTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CExecResultTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CExecResultTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CExecResultTypeType& operator=(const CExecResultTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CExecResultTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("nc0a"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("nc0a",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("nc0a",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CExecResultTypeType CReadOnlyExecResultTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��ѯ��״̬��
/////////////////////////////////////////////////////////////////////////
///�Ѿ��ύ
#define FQST_Submitted 'a'
///�Ѿ�����
#define FQST_Accepted 'b'
///�Ѿ����ܾ�
#define FQST_Rejected 'c'

class CForQuoteStatusTypeType : public CUFCharType					
{														
public:													
	CForQuoteStatusTypeType(void)									
	{													
	}													
	CForQuoteStatusTypeType(const CForQuoteStatusTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CForQuoteStatusTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CForQuoteStatusTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CForQuoteStatusTypeType& operator=(const CForQuoteStatusTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CForQuoteStatusTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("abc"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("abc",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("abc",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CForQuoteStatusTypeType CReadOnlyForQuoteStatusTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��������Ӧ�ı��������
/////////////////////////////////////////////////////////////////////////
///��ͨ����
#define OAT_Order '1'
///��Ȩ��Ȩ����ִ��
#define OAT_ExecOrder '2'
///��Ȩ��Ȩ�������
#define OAT_AbandonOrder '3'
///˫�߱��۵�
#define OAT_Quote '4'
///���߱��۵�
#define OAT_SingleQuote '5'
///��������ί�е�
#define OAT_QuoteOrder '5'

class COrderActionTypeType : public CUFCharType					
{														
public:													
	COrderActionTypeType(void)									
	{													
	}													
	COrderActionTypeType(const COrderActionTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	COrderActionTypeType(const char v)							
	{													
		setValue(v);									
	}													
	COrderActionTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	COrderActionTypeType& operator=(const COrderActionTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	COrderActionTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("123455"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("123455",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("123455",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const COrderActionTypeType CReadOnlyOrderActionTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ��Ͷ���������
/////////////////////////////////////////////////////////////////////////
///��ͨͶ����
#define OAT_Normal '1'
///������
#define OAT_MarketMaker '2'

class CInvestorSortType : public CUFCharType					
{														
public:													
	CInvestorSortType(void)									
	{													
	}													
	CInvestorSortType(const CInvestorSortType &v)				
	{													
		setValue(v.getValue());							
	}													
	CInvestorSortType(const char v)							
	{													
		setValue(v);									
	}													
	CInvestorSortType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CInvestorSortType& operator=(const CInvestorSortType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CInvestorSortType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("12"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("12",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("12",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CInvestorSortType CReadOnlyInvestorSortType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ���ɽ�������
/////////////////////////////////////////////////////////////////////////
///��ͨ�ɽ�
#define TT_Normal '1'
///��ϳɽ�
#define TT_Combination '2'

class CTradeTypeType : public CUFCharType					
{														
public:													
	CTradeTypeType(void)									
	{													
	}													
	CTradeTypeType(const CTradeTypeType &v)				
	{													
		setValue(v.getValue());							
	}													
	CTradeTypeType(const char v)							
	{													
		setValue(v);									
	}													
	CTradeTypeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	CTradeTypeType& operator=(const CTradeTypeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	CTradeTypeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("12"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("12",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("12",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const CTradeTypeType CReadOnlyTradeTypeType;		


/////////////////////////////////////////////////////////////////////////
///CEnumCharType��һ����Ȩ��Ȩ��ʽ��
/////////////////////////////////////////////////////////////////////////
///����Ȩ
#define OM_NullOptions '0'
///ŷʽ��Ȩ
#define OM_EuOptions 'E'
///��ʽ��Ȩ
#define OM_AmOptions 'A'

class COptionsModeType : public CUFCharType					
{														
public:													
	COptionsModeType(void)									
	{													
	}													
	COptionsModeType(const COptionsModeType &v)				
	{													
		setValue(v.getValue());							
	}													
	COptionsModeType(const char v)							
	{													
		setValue(v);									
	}													
	COptionsModeType(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	COptionsModeType& operator=(const COptionsModeType &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	COptionsModeType& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("0EA"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("0EA",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("0EA",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const COptionsModeType CReadOnlyOptionsModeType;		


#endif
