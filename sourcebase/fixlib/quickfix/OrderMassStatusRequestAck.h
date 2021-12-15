#ifndef FIX42_ORDERMASSSTATUSREQUESTACK_H
#define FIX42_ORDERMASSSTATUSREQUESTACK_H

#include "Message.h"

namespace FIX42
{

  class OrderMassStatusRequestAck : public Message
  {
  public:
    OrderMassStatusRequestAck() : Message(MsgType()) {}
    OrderMassStatusRequestAck(const FIX::Message& m) : Message(m) {}
    OrderMassStatusRequestAck(const Message& m) : Message(m) {}
    OrderMassStatusRequestAck(const OrderMassStatusRequestAck& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UBR"); }

    OrderMassStatusRequestAck(
      const FIX::MassStatusReqID& aMassStatusReqID
      ,
      const FIX::ReqResult& aReqResult
       )
    : Message(MsgType())
    {
      set(aMassStatusReqID);
      set(aReqResult);
    }

    FIELD_SET(*this, FIX::MassStatusReqID);
    FIELD_SET(*this, FIX::ReqResult);
  };

}

#endif
