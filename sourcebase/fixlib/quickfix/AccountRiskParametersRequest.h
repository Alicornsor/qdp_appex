#ifndef FIX42_ACCOUNTRISKPARAMETERSREQUEST_H
#define FIX42_ACCOUNTRISKPARAMETERSREQUEST_H

#include "Message.h"

namespace FIX42
{

  class AccountRiskParametersRequest : public Message
  {
  public:
    AccountRiskParametersRequest() : Message(MsgType()) {}
    AccountRiskParametersRequest(const FIX::Message& m) : Message(m) {}
    AccountRiskParametersRequest(const Message& m) : Message(m) {}
    AccountRiskParametersRequest(const AccountRiskParametersRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("URR"); }

    AccountRiskParametersRequest(
      const FIX::AcctReqID& aAcctReqID
       )
    : Message(MsgType())
    {
      set(aAcctReqID);
    }

    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::SubscriptionRequestType);
    FIELD_SET(*this, FIX::AcctReqID);
  };

}

#endif
