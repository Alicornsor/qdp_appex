#ifndef FIX42_SECURITYDEFINITION_H
#define FIX42_SECURITYDEFINITION_H

#include "Message.h"

namespace FIX42
{

  class SecurityDefinition : public Message
  {
  public:
    SecurityDefinition() : Message(MsgType()) {}
    SecurityDefinition(const FIX::Message& m) : Message(m) {}
    SecurityDefinition(const Message& m) : Message(m) {}
    SecurityDefinition(const SecurityDefinition& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("d"); }

    SecurityDefinition(
      const FIX::SecurityReqID& aSecurityReqID
       )
    : Message(MsgType())
    {
      set(aSecurityReqID);
    }

    FIELD_SET(*this, FIX::SecurityType);
    FIELD_SET(*this, FIX::MaturityMonthYear);
    FIELD_SET(*this, FIX::PutOrCall);
    FIELD_SET(*this, FIX::StrikePrice);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::SecurityReqID);
    FIELD_SET(*this, FIX::SecurityResponseID);
    FIELD_SET(*this, FIX::SecurityResponseType);
    FIELD_SET(*this, FIX::TotalNumSecurities);
    FIELD_SET(*this, FIX::MaturityDate);
    FIELD_SET(*this, FIX::CFICode);
    FIELD_SET(*this, FIX::SecuritySubType);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::Currency);
    FIELD_SET(*this, FIX::Text);
    FIELD_SET(*this, FIX::UserStrategyType);
    FIELD_SET(*this, FIX::ExchangeKeyID);
    FIELD_SET(*this, FIX::NoRelatedSym);

    class NoRelatedSym: public FIX::Group
    {
    public:
    NoRelatedSym() : FIX::Group(146,20050,FIX::message_order(
      20050,
      311,
      312,
      309,
      305,
      310,
      313,
      314,
      315,
      316,
      50542,
      308,
      435,
      50463,
      20051,
      318,
      319,
      54,
      20121,
      0)) {}

      FIELD_SET(*this, FIX::LegNumber);
      FIELD_SET(*this, FIX::UnderlyingSymbol);
      FIELD_SET(*this, FIX::UnderlyingSymbolSfx);
      FIELD_SET(*this, FIX::UnderlyingSecurityID);
      FIELD_SET(*this, FIX::UnderlyingIDSource);
      FIELD_SET(*this, FIX::UnderlyingSecurityType);
      FIELD_SET(*this, FIX::UnderlyingMaturityMonthYear);
      FIELD_SET(*this, FIX::UnderlyingMaturityDay);
      FIELD_SET(*this, FIX::UnderlyingPutOrCall);
      FIELD_SET(*this, FIX::UnderlyingStrikePrice);
      FIELD_SET(*this, FIX::UnderlyingMaturityDate);
      FIELD_SET(*this, FIX::UnderlyingSecurityExchange);
      FIELD_SET(*this, FIX::UnderlyingCouponRate);
      FIELD_SET(*this, FIX::UnderlyingCFICode);
      FIELD_SET(*this, FIX::UnderlyingExDestination);
      FIELD_SET(*this, FIX::UnderlyingCurrency);
      FIELD_SET(*this, FIX::RatioQty);
      FIELD_SET(*this, FIX::Side);
      FIELD_SET(*this, FIX::UnderlyingExchangeKeyID);
    };

  };

}

#endif
