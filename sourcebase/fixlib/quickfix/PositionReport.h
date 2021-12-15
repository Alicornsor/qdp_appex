#ifndef FIX42_POSITIONREPORT_H
#define FIX42_POSITIONREPORT_H

#include "Message.h"

namespace FIX42
{

  class PositionReport : public Message
  {
  public:
    PositionReport() : Message(MsgType()) {}
    PositionReport(const FIX::Message& m) : Message(m) {}
    PositionReport(const Message& m) : Message(m) {}
    PositionReport(const PositionReport& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UAP"); }

    PositionReport(
      const FIX::Account& aAccount
       )
    : Message(MsgType())
    {
      set(aAccount);
    }

    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::AvgPx);
    FIELD_SET(*this, FIX::ClOrdID);
    FIELD_SET(*this, FIX::Currency);
    FIELD_SET(*this, FIX::ExecID);
    FIELD_SET(*this, FIX::IDSource);
    FIELD_SET(*this, FIX::LastMkt);
    FIELD_SET(*this, FIX::LastShares);
    FIELD_SET(*this, FIX::OrderID);
    FIELD_SET(*this, FIX::SecurityID);
    FIELD_SET(*this, FIX::Side);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::Text);
    FIELD_SET(*this, FIX::TransactTime);
    FIELD_SET(*this, FIX::SymbolSfx);
    FIELD_SET(*this, FIX::ListID);
    FIELD_SET(*this, FIX::OnBehalfOfCompID);
    FIELD_SET(*this, FIX::DeliverToCompID);
    FIELD_SET(*this, FIX::DeliverToSubID);
    FIELD_SET(*this, FIX::SecurityType);
    FIELD_SET(*this, FIX::SecondaryOrderID);
    FIELD_SET(*this, FIX::MaturityMonthYear);
    FIELD_SET(*this, FIX::PutOrCall);
    FIELD_SET(*this, FIX::StrikePrice);
    FIELD_SET(*this, FIX::MaturityDay);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::CouponRate);
    FIELD_SET(*this, FIX::UnsolicitedIndicator);
    FIELD_SET(*this, FIX::MaturityDate);
    FIELD_SET(*this, FIX::ExchangeKeyID);
    FIELD_SET(*this, FIX::CFICode);
    FIELD_SET(*this, FIX::SecuritySubType);
    FIELD_SET(*this, FIX::AccountName);
    FIELD_SET(*this, FIX::FCMAccountNumber);
    FIELD_SET(*this, FIX::MarketValue);
    FIELD_SET(*this, FIX::OpenTradeEquity);
    FIELD_SET(*this, FIX::UnrealizedPL);
    FIELD_SET(*this, FIX::StatementDate);
    FIELD_SET(*this, FIX::OrderSource);
    FIELD_SET(*this, FIX::TradeID);
    FIELD_SET(*this, FIX::ChainOrderID);
    FIELD_SET(*this, FIX::CQGListID);
    FIELD_SET(*this, FIX::SalesSeriesNumber);
    FIELD_SET(*this, FIX::OrderPlacementTime);
    FIELD_SET(*this, FIX::OrderCheckMark);
    FIELD_SET(*this, FIX::SecondaryClOrderID);
    FIELD_SET(*this, FIX::PosReqType);
    FIELD_SET(*this, FIX::SettlPrice);
    FIELD_SET(*this, FIX::PosReqID);
    FIELD_SET(*this, FIX::ClearingBusinessDate);
  };

}

#endif
