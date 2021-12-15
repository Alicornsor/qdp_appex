#ifndef FIX42_BUSINESSMESSAGEREJECT_H
#define FIX42_BUSINESSMESSAGEREJECT_H

#include "Message.h"

namespace FIX42
{

  class BusinessMessageReject : public Message
  {
  public:
    BusinessMessageReject() : Message(MsgType()) {}
    BusinessMessageReject(const FIX::Message& m) : Message(m) {}
    BusinessMessageReject(const Message& m) : Message(m) {}
    BusinessMessageReject(const BusinessMessageReject& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("j"); }

    BusinessMessageReject(
      const FIX::Text& aText
      ,
      const FIX::RefMsgType& aRefMsgType
      ,
      const FIX::BusinessRejectReason& aBusinessRejectReason
       )
    : Message(MsgType())
    {
      set(aText);
      set(aRefMsgType);
      set(aBusinessRejectReason);
    }

    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::ClOrdID);
    FIELD_SET(*this, FIX::RefSeqNum);
    FIELD_SET(*this, FIX::Text);
    FIELD_SET(*this, FIX::RefMsgType);
    FIELD_SET(*this, FIX::BusinessRejectRefID);
    FIELD_SET(*this, FIX::BusinessRejectReason);
  };

}

#endif
