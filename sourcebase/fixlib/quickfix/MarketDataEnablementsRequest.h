#ifndef FIX42_MARKETDATAENABLEMENTSREQUEST_H
#define FIX42_MARKETDATAENABLEMENTSREQUEST_H

#include "Message.h"

namespace FIX42
{

  class MarketDataEnablementsRequest : public Message
  {
  public:
    MarketDataEnablementsRequest() : Message(MsgType()) {}
    MarketDataEnablementsRequest(const FIX::Message& m) : Message(m) {}
    MarketDataEnablementsRequest(const Message& m) : Message(m) {}
    MarketDataEnablementsRequest(const MarketDataEnablementsRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UZZ"); }

    MarketDataEnablementsRequest(
      const FIX::RequestID& aRequestID
       )
    : Message(MsgType())
    {
      set(aRequestID);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::RevisionTag);
  };

}

#endif
