#ifndef FIX42_LISTSTATUS_H
#define FIX42_LISTSTATUS_H

#include "Message.h"

namespace FIX42
{

  class ListStatus : public Message
  {
  public:
    ListStatus() : Message(MsgType()) {}
    ListStatus(const FIX::Message& m) : Message(m) {}
    ListStatus(const Message& m) : Message(m) {}
    ListStatus(const ListStatus& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("N"); }

    ListStatus(
      const FIX::ListID& aListID
      ,
      const FIX::CQGListID& aCQGListID
      ,
      const FIX::ListStatusType& aListStatusType
      ,
      const FIX::NoRpts& aNoRpts
      ,
      const FIX::ListOrderStatus& aListOrderStatus
      ,
      const FIX::ContingencyType& aContingencyType
      ,
      const FIX::RptSeq& aRptSeq
      ,
      const FIX::TotNoOrders& aTotNoOrders
       )
    : Message(MsgType())
    {
      set(aListID);
      set(aCQGListID);
      set(aListStatusType);
      set(aNoRpts);
      set(aListOrderStatus);
      set(aContingencyType);
      set(aRptSeq);
      set(aTotNoOrders);
    }

    FIELD_SET(*this, FIX::ListID);
    FIELD_SET(*this, FIX::CQGListID);
    FIELD_SET(*this, FIX::ListStatusType);
    FIELD_SET(*this, FIX::NoRpts);
    FIELD_SET(*this, FIX::ListOrderStatus);
    FIELD_SET(*this, FIX::ContingencyType);
    FIELD_SET(*this, FIX::RptSeq);
    FIELD_SET(*this, FIX::ListStatusText);
    FIELD_SET(*this, FIX::TransactTime);
    FIELD_SET(*this, FIX::TotNoOrders);
    FIELD_SET(*this, FIX::NoOrders);

    class NoOrders: public FIX::Group
    {
    public:
    NoOrders() : FIX::Group(73,67,FIX::message_order(
      67,
      20029,
      20074,
      20103,
      0)) {}

      FIELD_SET(*this, FIX::ListSeqNo);
      FIELD_SET(*this, FIX::ChainOrderID);
      FIELD_SET(*this, FIX::NestedListID);
      FIELD_SET(*this, FIX::NestedCQGListID);
    };

  };

}

#endif
