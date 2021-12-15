#ifndef FIX42_LOGON_H
#define FIX42_LOGON_H

#include "Message.h"

namespace FIX42
{

  class Logon : public Message
  {
  public:
    Logon() : Message(MsgType()) {}
    Logon(const FIX::Message& m) : Message(m) {}
    Logon(const Message& m) : Message(m) {}
    Logon(const Logon& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("A"); }

    FIELD_SET(*this, FIX::RawData);
    FIELD_SET(*this, FIX::EncryptMethod);
    FIELD_SET(*this, FIX::HeartBtInt);
    FIELD_SET(*this, FIX::ResetSeqNumFlag);
    FIELD_SET(*this, FIX::OneTimePassword);
  };

}

#endif
