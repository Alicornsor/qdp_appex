#ifndef FIX42_AUTHORIZEDACCOUNTSREQUEST_H
#define FIX42_AUTHORIZEDACCOUNTSREQUEST_H

#include "Message.h"

namespace FIX42
{

  class AuthorizedAccountsRequest : public Message
  {
  public:
    AuthorizedAccountsRequest() : Message(MsgType()) {}
    AuthorizedAccountsRequest(const FIX::Message& m) : Message(m) {}
    AuthorizedAccountsRequest(const Message& m) : Message(m) {}
    AuthorizedAccountsRequest(const AuthorizedAccountsRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UZR"); }

    AuthorizedAccountsRequest(
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
    FIELD_SET(*this, FIX::NoAccounts);

    class NoAccounts: public FIX::Group
    {
    public:
    NoAccounts() : FIX::Group(20058,1,FIX::message_order(
      1,
      20010,
      20014,
      20053,
      20059,
      20060,
      0)) {}

      FIELD_SET(*this, FIX::Account);
      FIELD_SET(*this, FIX::AccountName);
      FIELD_SET(*this, FIX::FCMAccountNumber);
      FIELD_SET(*this, FIX::FCMID);
      FIELD_SET(*this, FIX::FCMName);
      FIELD_SET(*this, FIX::ViewOnly);
    };

  };

}

#endif
