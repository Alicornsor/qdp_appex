#ifndef FIX42_FCMCURRENCYRATEREPORT_H
#define FIX42_FCMCURRENCYRATEREPORT_H

#include "Message.h"

namespace FIX42
{

  class FCMCurrencyRateReport : public Message
  {
  public:
    FCMCurrencyRateReport() : Message(MsgType()) {}
    FCMCurrencyRateReport(const FIX::Message& m) : Message(m) {}
    FCMCurrencyRateReport(const Message& m) : Message(m) {}
    FCMCurrencyRateReport(const FCMCurrencyRateReport& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UZT"); }

    FCMCurrencyRateReport(
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
    FIELD_SET(*this, FIX::NoRates);

    class NoRates: public FIX::Group
    {
    public:
    NoRates() : FIX::Group(20054,15,FIX::message_order(
      15,
      20055,
      20023,
      20056,
      0)) {}

      FIELD_SET(*this, FIX::Currency);
      FIELD_SET(*this, FIX::MasterCurrency);
      FIELD_SET(*this, FIX::StatementDate);
      FIELD_SET(*this, FIX::CurrencyRate);
    };

  };

}

#endif
