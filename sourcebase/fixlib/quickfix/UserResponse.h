#ifndef FIX42_USERRESPONSE_H
#define FIX42_USERRESPONSE_H

#include "Message.h"

namespace FIX42
{

  class UserResponse : public Message
  {
  public:
    UserResponse() : Message(MsgType()) {}
    UserResponse(const FIX::Message& m) : Message(m) {}
    UserResponse(const Message& m) : Message(m) {}
    UserResponse(const UserResponse& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UBF"); }

    UserResponse(
      const FIX::UserRequestID& aUserRequestID
      ,
      const FIX::UserStatus& aUserStatus
       )
    : Message(MsgType())
    {
      set(aUserRequestID);
      set(aUserStatus);
    }

    FIELD_SET(*this, FIX::UserRequestID);
    FIELD_SET(*this, FIX::UserStatus);
    FIELD_SET(*this, FIX::UserStatusText);
  };

}

#endif
