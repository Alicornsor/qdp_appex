#ifndef FIX42_USERREQUEST_H
#define FIX42_USERREQUEST_H

#include "Message.h"

namespace FIX42
{

  class UserRequest : public Message
  {
  public:
    UserRequest() : Message(MsgType()) {}
    UserRequest(const FIX::Message& m) : Message(m) {}
    UserRequest(const Message& m) : Message(m) {}
    UserRequest(const UserRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UBE"); }

    UserRequest(
      const FIX::UserRequestID& aUserRequestID
      ,
      const FIX::UserRequestType& aUserRequestType
      ,
      const FIX::Password& aPassword
      ,
      const FIX::NewPassword& aNewPassword
       )
    : Message(MsgType())
    {
      set(aUserRequestID);
      set(aUserRequestType);
      set(aPassword);
      set(aNewPassword);
    }

    FIELD_SET(*this, FIX::UserRequestID);
    FIELD_SET(*this, FIX::UserRequestType);
    FIELD_SET(*this, FIX::Password);
    FIELD_SET(*this, FIX::NewPassword);
  };

}

#endif
