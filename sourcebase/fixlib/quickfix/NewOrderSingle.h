#ifndef FIX42_NEWORDERSINGLE_H
#define FIX42_NEWORDERSINGLE_H

#include "Message.h"

namespace FIX42
{

  class NewOrderSingle : public Message
  {
  public:
    NewOrderSingle() : Message(MsgType()) {}
    NewOrderSingle(const FIX::Message& m) : Message(m) {}
    NewOrderSingle(const Message& m) : Message(m) {}
    NewOrderSingle(const NewOrderSingle& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("D"); }

    NewOrderSingle(
      const FIX::Account& aAccount
      ,
      const FIX::ExecBroker& aExecBroker
      ,
      const FIX::ClOrdID& aClOrdID
      ,
      const FIX::OrderQty& aOrderQty
      ,
      const FIX::OrdType& aOrdType
      ,
      const FIX::Price& aPrice
      ,
      const FIX::SecurityID& aSecurityID
      ,
      const FIX::Side& aSide
      ,
      const FIX::TransactTime& aTransactTime
       )
    : Message(MsgType())
    {
      set(aAccount);
      set(aExecBroker);
      set(aClOrdID);
      set(aOrderQty);
      set(aOrdType);
      set(aPrice);
      set(aSecurityID);
      set(aSide);
      set(aTransactTime);
    }

    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::ExecBroker);
    FIELD_SET(*this, FIX::ClOrdID);
    FIELD_SET(*this, FIX::ExecInst);
    FIELD_SET(*this, FIX::HandlInst);
    FIELD_SET(*this, FIX::IDSource);
    FIELD_SET(*this, FIX::OrderQty);
    FIELD_SET(*this, FIX::OrdType);
    FIELD_SET(*this, FIX::Price);
    FIELD_SET(*this, FIX::SecurityID);
    FIELD_SET(*this, FIX::Side);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::Text);
    FIELD_SET(*this, FIX::TimeInForce);
    FIELD_SET(*this, FIX::TransactTime);
    FIELD_SET(*this, FIX::SymbolSfx);
    FIELD_SET(*this, FIX::OpenClose);
    FIELD_SET(*this, FIX::StopPx);
    FIELD_SET(*this, FIX::ExDestination);
    FIELD_SET(*this, FIX::OnBehalfOfCompID);
    FIELD_SET(*this, FIX::OnBehalfOfSubID);
    FIELD_SET(*this, FIX::DeliverToCompID);
    FIELD_SET(*this, FIX::SecurityType);
    FIELD_SET(*this, FIX::MaturityMonthYear);
    FIELD_SET(*this, FIX::PutOrCall);
    FIELD_SET(*this, FIX::StrikePrice);
    FIELD_SET(*this, FIX::CustomerOrFirm);
    FIELD_SET(*this, FIX::MaturityDay);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::MaxShow);
    FIELD_SET(*this, FIX::PegDifference);
    FIELD_SET(*this, FIX::CouponRate);
    FIELD_SET(*this, FIX::ExpireDate);
    FIELD_SET(*this, FIX::OrderCapacity);
    FIELD_SET(*this, FIX::MaturityDate);
    FIELD_SET(*this, FIX::ManualOrderIndicator);
    FIELD_SET(*this, FIX::Aggressive);
    FIELD_SET(*this, FIX::TriggerQty);
    FIELD_SET(*this, FIX::ClientRegulatoryAlgorithmID);
  };

}

#endif
