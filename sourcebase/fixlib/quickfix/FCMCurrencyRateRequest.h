#ifndef FIX42_FCMCURRENCYRATEREQUEST_H
#define FIX42_FCMCURRENCYRATEREQUEST_H

#include "Message.h"

namespace FIX42
{

  class FCMCurrencyRateRequest : public Message
  {
  public:
    FCMCurrencyRateRequest() : Message(MsgType()) {}
    FCMCurrencyRateRequest(const FIX::Message& m) : Message(m) {}
    FCMCurrencyRateRequest(const Message& m) : Message(m) {}
    FCMCurrencyRateRequest(const FCMCurrencyRateRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UZU"); }

    FCMCurrencyRateRequest(
      const FIX::RequestID& aRequestID
      ,
      const FIX::FCMID& aFCMID
       )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aFCMID);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::FCMID);
  };

}

#endif
