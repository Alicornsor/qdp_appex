#ifndef FIX42_REQUESTFORPOSITION_H
#define FIX42_REQUESTFORPOSITION_H

#include "Message.h"

namespace FIX42
{

  class RequestForPosition : public Message
  {
  public:
    RequestForPosition() : Message(MsgType()) {}
    RequestForPosition(const FIX::Message& m) : Message(m) {}
    RequestForPosition(const Message& m) : Message(m) {}
    RequestForPosition(const RequestForPosition& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UAN"); }

    RequestForPosition(
      const FIX::PosReqID& aPosReqID
      ,
      const FIX::PosReqType& aPosReqType
       )
    : Message(MsgType())
    {
      set(aPosReqID);
      set(aPosReqType);
    }

    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::SubscriptionRequestType);
    FIELD_SET(*this, FIX::PosReqID);
    FIELD_SET(*this, FIX::PosReqType);
  };

}

#endif
