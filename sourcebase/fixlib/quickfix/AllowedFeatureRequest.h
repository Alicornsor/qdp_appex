#ifndef FIX42_ALLOWEDFEATUREREQUEST_H
#define FIX42_ALLOWEDFEATUREREQUEST_H

#include "Message.h"

namespace FIX42
{

  class AllowedFeatureRequest : public Message
  {
  public:
    AllowedFeatureRequest() : Message(MsgType()) {}
    AllowedFeatureRequest(const FIX::Message& m) : Message(m) {}
    AllowedFeatureRequest(const Message& m) : Message(m) {}
    AllowedFeatureRequest(const AllowedFeatureRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UZX"); }

    AllowedFeatureRequest(
      const FIX::RequestID& aRequestID
       )
    : Message(MsgType())
    {
      set(aRequestID);
    }

    FIELD_SET(*this, FIX::RequestID);
  };

}

#endif
