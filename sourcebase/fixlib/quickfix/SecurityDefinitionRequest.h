#ifndef FIX42_SECURITYDEFINITIONREQUEST_H
#define FIX42_SECURITYDEFINITIONREQUEST_H

#include "Message.h"

namespace FIX42
{

  class SecurityDefinitionRequest : public Message
  {
  public:
    SecurityDefinitionRequest() : Message(MsgType()) {}
    SecurityDefinitionRequest(const FIX::Message& m) : Message(m) {}
    SecurityDefinitionRequest(const Message& m) : Message(m) {}
    SecurityDefinitionRequest(const SecurityDefinitionRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("c"); }

    SecurityDefinitionRequest(
      const FIX::SecurityReqID& aSecurityReqID
      ,
      const FIX::SecurityRequestType& aSecurityRequestType
       )
    : Message(MsgType())
    {
      set(aSecurityReqID);
      set(aSecurityRequestType);
    }

    FIELD_SET(*this, FIX::SecurityReqID);
    FIELD_SET(*this, FIX::SecurityRequestType);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::UserStrategyType);
    FIELD_SET(*this, FIX::NoRelatedSym);

    class NoRelatedSym: public FIX::Group
    {
    public:
    NoRelatedSym() : FIX::Group(146,311,FIX::message_order(
      311,
      312,
      309,
      305,
      310,
      313,
      314,
      315,
      316,
      317,
      436,
      435,
      308,
      306,
      362,
      363,
      307,
      364,
      365,
      319,
      54,
      318,
      0)) {}

      FIELD_SET(*this, FIX::UnderlyingSymbol);
      FIELD_SET(*this, FIX::UnderlyingSymbolSfx);
      FIELD_SET(*this, FIX::UnderlyingSecurityID);
      FIELD_SET(*this, FIX::UnderlyingIDSource);
      FIELD_SET(*this, FIX::UnderlyingSecurityType);
      FIELD_SET(*this, FIX::UnderlyingMaturityMonthYear);
      FIELD_SET(*this, FIX::UnderlyingMaturityDay);
      FIELD_SET(*this, FIX::UnderlyingPutOrCall);
      FIELD_SET(*this, FIX::UnderlyingStrikePrice);
      FIELD_SET(*this, FIX::UnderlyingOptAttribute);
      FIELD_SET(*this, FIX::UnderlyingContractMultiplier);
      FIELD_SET(*this, FIX::UnderlyingCouponRate);
      FIELD_SET(*this, FIX::UnderlyingSecurityExchange);
      FIELD_SET(*this, FIX::UnderlyingIssuer);
      FIELD_SET(*this, FIX::EncodedUnderlyingIssuerLen);
      FIELD_SET(*this, FIX::EncodedUnderlyingIssuer);
      FIELD_SET(*this, FIX::UnderlyingSecurityDesc);
      FIELD_SET(*this, FIX::EncodedUnderlyingSecurityDescLen);
      FIELD_SET(*this, FIX::EncodedUnderlyingSecurityDesc);
      FIELD_SET(*this, FIX::RatioQty);
      FIELD_SET(*this, FIX::Side);
      FIELD_SET(*this, FIX::UnderlyingCurrency);
    };

  };

}

#endif
