#ifndef FIX42_REQUESTFORPOSITIONSACK_H
#define FIX42_REQUESTFORPOSITIONSACK_H

#include "Message.h"

namespace FIX42
{

  class RequestForPositionsAck : public Message
  {
  public:
    RequestForPositionsAck() : Message(MsgType()) {}
    RequestForPositionsAck(const FIX::Message& m) : Message(m) {}
    RequestForPositionsAck(const Message& m) : Message(m) {}
    RequestForPositionsAck(const RequestForPositionsAck& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UAO"); }

    FIELD_SET(*this, FIX::UnsolicitedIndicator);
    FIELD_SET(*this, FIX::PosReqID);
    FIELD_SET(*this, FIX::PosReqType);
    FIELD_SET(*this, FIX::PosReqResult);
    FIELD_SET(*this, FIX::NoAccounts);

    class NoAccounts: public FIX::Group
    {
    public:
    NoAccounts() : FIX::Group(20058,1,FIX::message_order(
      1,
      0)) {}

      FIELD_SET(*this, FIX::Account);
    };

  };

}

#endif
