#ifndef FIX42_COLLATERALREPORT_H
#define FIX42_COLLATERALREPORT_H

#include "Message.h"

namespace FIX42
{

  class CollateralReport : public Message
  {
  public:
    CollateralReport() : Message(MsgType()) {}
    CollateralReport(const FIX::Message& m) : Message(m) {}
    CollateralReport(const Message& m) : Message(m) {}
    CollateralReport(const CollateralReport& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UBA"); }

    CollateralReport(
      const FIX::CollInquiryID& aCollInquiryID
      ,
      const FIX::Account& aAccount
      ,
      const FIX::TotalMarginReqs& aTotalMarginReqs
      ,
      const FIX::RealizedPL& aRealizedPL
      ,
      const FIX::PurchasingPower& aPurchasingPower
      ,
      const FIX::Currency& aCurrency
       )
    : Message(MsgType())
    {
      set(aCollInquiryID);
      set(aAccount);
      set(aTotalMarginReqs);
      set(aRealizedPL);
      set(aPurchasingPower);
      set(aCurrency);
    }

    FIELD_SET(*this, FIX::CollInquiryID);
    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::TotalMarginReqs);
    FIELD_SET(*this, FIX::RealizedPL);
    FIELD_SET(*this, FIX::PurchasingPower);
    FIELD_SET(*this, FIX::Currency);
    FIELD_SET(*this, FIX::LastRptRequested);
    FIELD_SET(*this, FIX::AccountName);
    FIELD_SET(*this, FIX::FCMAccountNumber);
  };

}

#endif
