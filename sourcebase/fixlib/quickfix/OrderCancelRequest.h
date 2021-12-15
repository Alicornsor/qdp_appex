#ifndef FIX42_ORDERCANCELREQUEST_H
#define FIX42_ORDERCANCELREQUEST_H

#include "Message.h"

namespace FIX42
{

  class OrderCancelRequest : public Message
  {
  public:
    OrderCancelRequest() : Message(MsgType()) {}
    OrderCancelRequest(const FIX::Message& m) : Message(m) {}
    OrderCancelRequest(const Message& m) : Message(m) {}
    OrderCancelRequest(const OrderCancelRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("F"); }

    OrderCancelRequest(
      const FIX::Account& aAccount
      ,
      const FIX::OrderID& aOrderID
      ,
      const FIX::OrigClOrdID& aOrigClOrdID
      ,
      const FIX::SecurityExchange& aSecurityExchange
      ,
      const FIX::ExecBroker& aExecBroker
      ,
      const FIX::SecurityID& aSecurityID
       )
    : Message(MsgType())
    {
      set(aAccount);
      set(aOrderID);
      set(aOrigClOrdID);
      set(aSecurityExchange);
      set(aExecBroker);
      set(aSecurityID);
    }

    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::ClOrdID);
    FIELD_SET(*this, FIX::OrderID);
    FIELD_SET(*this, FIX::OrigClOrdID);
    FIELD_SET(*this, FIX::Side);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::TransactTime);
    FIELD_SET(*this, FIX::OnBehalfOfCompID);
    FIELD_SET(*this, FIX::OnBehalfOfSubID);
    FIELD_SET(*this, FIX::DeliverToCompID);
    FIELD_SET(*this, FIX::ClientRegulatoryAlgorithmID);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::ExecBroker);
    FIELD_SET(*this, FIX::SecurityID);
  };

}

#endif
