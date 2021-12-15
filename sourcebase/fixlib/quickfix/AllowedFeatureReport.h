#ifndef FIX42_ALLOWEDFEATUREREPORT_H
#define FIX42_ALLOWEDFEATUREREPORT_H

#include "Message.h"

namespace FIX42
{

  class AllowedFeatureReport : public Message
  {
  public:
    AllowedFeatureReport() : Message(MsgType()) {}
    AllowedFeatureReport(const FIX::Message& m) : Message(m) {}
    AllowedFeatureReport(const Message& m) : Message(m) {}
    AllowedFeatureReport(const AllowedFeatureReport& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UZW"); }

    AllowedFeatureReport(
      const FIX::RequestID& aRequestID
      ,
      const FIX::LastFragment& aLastFragment
       )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aLastFragment);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::LastFragment);
    FIELD_SET(*this, FIX::NoEnablements);

    class NoEnablements: public FIX::Group
    {
    public:
    NoEnablements() : FIX::Group(20038,20039,FIX::message_order(
      20039,
      20040,
      20041,
      20042,
      0)) {}

      FIELD_SET(*this, FIX::EnablementID);
      FIELD_SET(*this, FIX::EnablementGroup);
      FIELD_SET(*this, FIX::BillingGroupID);
      FIELD_SET(*this, FIX::BillingID);
    };

  };

}

#endif
