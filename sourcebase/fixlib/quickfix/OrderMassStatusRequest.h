#ifndef FIX42_ORDERMASSSTATUSREQUEST_H
#define FIX42_ORDERMASSSTATUSREQUEST_H

#include "Message.h"

namespace FIX42
{

  class OrderMassStatusRequest : public Message
  {
  public:
    OrderMassStatusRequest() : Message(MsgType()) {}
    OrderMassStatusRequest(const FIX::Message& m) : Message(m) {}
    OrderMassStatusRequest(const Message& m) : Message(m) {}
    OrderMassStatusRequest(const OrderMassStatusRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UAF"); }

    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::IDSource);
    FIELD_SET(*this, FIX::SecurityID);
    FIELD_SET(*this, FIX::Side);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::SymbolSfx);
    FIELD_SET(*this, FIX::SecurityType);
    FIELD_SET(*this, FIX::MaturityMonthYear);
    FIELD_SET(*this, FIX::PutOrCall);
    FIELD_SET(*this, FIX::StrikePrice);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::CouponRate);
    FIELD_SET(*this, FIX::MaturityDate);
    FIELD_SET(*this, FIX::MassStatusReqID);
  };

}

#endif
