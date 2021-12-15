#ifndef FIX42_ALLOWEDMARKETDATAREPORT_H
#define FIX42_ALLOWEDMARKETDATAREPORT_H

#include "Message.h"

namespace FIX42
{

  class AllowedMarketDataReport : public Message
  {
  public:
    AllowedMarketDataReport() : Message(MsgType()) {}
    AllowedMarketDataReport(const FIX::Message& m) : Message(m) {}
    AllowedMarketDataReport(const Message& m) : Message(m) {}
    AllowedMarketDataReport(const AllowedMarketDataReport& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UZY"); }

    AllowedMarketDataReport(
      const FIX::RequestID& aRequestID
      ,
      const FIX::RevisionTag& aRevisionTag
      ,
      const FIX::LastFragment& aLastFragment
       )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aRevisionTag);
      set(aLastFragment);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::RevisionTag);
    FIELD_SET(*this, FIX::LastFragment);
    FIELD_SET(*this, FIX::NoAllowedInstr);

    class NoAllowedInstr: public FIX::Group
    {
    public:
    NoAllowedInstr() : FIX::Group(20037,55,FIX::message_order(
      55,
      20127,
      0)) {}

      FIELD_SET(*this, FIX::Symbol);
      FIELD_SET(*this, FIX::Unknow);
    };

  };

}

#endif
