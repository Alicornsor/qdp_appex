#ifndef FIX42_COLLATERALINQUIRY_H
#define FIX42_COLLATERALINQUIRY_H

#include "Message.h"

namespace FIX42
{

  class CollateralInquiry : public Message
  {
  public:
    CollateralInquiry() : Message(MsgType()) {}
    CollateralInquiry(const FIX::Message& m) : Message(m) {}
    CollateralInquiry(const Message& m) : Message(m) {}
    CollateralInquiry(const CollateralInquiry& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UBB"); }

    CollateralInquiry(
      const FIX::CollInquiryID& aCollInquiryID
       )
    : Message(MsgType())
    {
      set(aCollInquiryID);
    }

    FIELD_SET(*this, FIX::CollInquiryID);
    FIELD_SET(*this, FIX::Account);
  };

}

#endif
