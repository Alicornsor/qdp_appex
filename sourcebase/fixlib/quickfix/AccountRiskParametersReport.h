#ifndef FIX42_ACCOUNTRISKPARAMETERSREPORT_H
#define FIX42_ACCOUNTRISKPARAMETERSREPORT_H

#include "Message.h"

namespace FIX42
{

  class AccountRiskParametersReport : public Message
  {
  public:
    AccountRiskParametersReport() : Message(MsgType()) {}
    AccountRiskParametersReport(const FIX::Message& m) : Message(m) {}
    AccountRiskParametersReport(const Message& m) : Message(m) {}
    AccountRiskParametersReport(const AccountRiskParametersReport& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("URP"); }

    AccountRiskParametersReport(
      const FIX::Account& aAccount
      ,
      const FIX::UnsolicitedIndicator& aUnsolicitedIndicator
      ,
      const FIX::AcctReqID& aAcctReqID
      ,
      const FIX::OteInPurchasingPower& aOteInPurchasingPower
      ,
      const FIX::NovInPurchasingPower& aNovInPurchasingPower
      ,
      const FIX::OteBidAsk& aOteBidAsk
      ,
      const FIX::NovBidAsk& aNovBidAsk
      ,
      const FIX::MarginEnabled& aMarginEnabled
       )
    : Message(MsgType())
    {
      set(aAccount);
      set(aUnsolicitedIndicator);
      set(aAcctReqID);
      set(aOteInPurchasingPower);
      set(aNovInPurchasingPower);
      set(aOteBidAsk);
      set(aNovBidAsk);
      set(aMarginEnabled);
    }

    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::UnsolicitedIndicator);
    FIELD_SET(*this, FIX::AcctReqID);
    FIELD_SET(*this, FIX::AccountName);
    FIELD_SET(*this, FIX::FCMAccountNumber);
    FIELD_SET(*this, FIX::OteInPurchasingPower);
    FIELD_SET(*this, FIX::NovInPurchasingPower);
    FIELD_SET(*this, FIX::OteBidAsk);
    FIELD_SET(*this, FIX::NovBidAsk);
    FIELD_SET(*this, FIX::MarginEnabled);
    FIELD_SET(*this, FIX::LastRptRequested);
  };

}

#endif
