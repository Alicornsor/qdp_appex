#ifndef FIX42_ACCOUNTDATAREQUEST_H
#define FIX42_ACCOUNTDATAREQUEST_H

#include "Message.h"

namespace FIX42
{

  class AccountDataRequest : public Message
  {
  public:
    AccountDataRequest() : Message(MsgType()) {}
    AccountDataRequest(const FIX::Message& m) : Message(m) {}
    AccountDataRequest(const Message& m) : Message(m) {}
    AccountDataRequest(const AccountDataRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UAR"); }

    AccountDataRequest(
      const FIX::AcctReqID& aAcctReqID
       )
    : Message(MsgType())
    {
      set(aAcctReqID);
    }

    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::SubscriptionRequestType);
    FIELD_SET(*this, FIX::AcctReqID);
    FIELD_SET(*this, FIX::IncludeBalanceGrp);
  };

}

#endif
