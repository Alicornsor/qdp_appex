#ifndef FIX42_ACCOUNTDATAREPORT_H
#define FIX42_ACCOUNTDATAREPORT_H

#include "Message.h"

namespace FIX42
{

  class AccountDataReport : public Message
  {
  public:
    AccountDataReport() : Message(MsgType()) {}
    AccountDataReport(const FIX::Message& m) : Message(m) {}
    AccountDataReport(const Message& m) : Message(m) {}
    AccountDataReport(const AccountDataReport& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UAD"); }

    AccountDataReport(
      const FIX::Account& aAccount
      ,
      const FIX::UnsolicitedIndicator& aUnsolicitedIndicator
      ,
      const FIX::AcctReqID& aAcctReqID
       )
    : Message(MsgType())
    {
      set(aAccount);
      set(aUnsolicitedIndicator);
      set(aAcctReqID);
    }

    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::Currency);
    FIELD_SET(*this, FIX::UnsolicitedIndicator);
    FIELD_SET(*this, FIX::AcctReqID);
    FIELD_SET(*this, FIX::AccountName);
    FIELD_SET(*this, FIX::AsOfDate);
    FIELD_SET(*this, FIX::CashExcess);
    FIELD_SET(*this, FIX::CollateralOnDeposit);
    FIELD_SET(*this, FIX::FCMAccountNumber);
    FIELD_SET(*this, FIX::InitialMarginReqs);
    FIELD_SET(*this, FIX::MaintenanceMarginReqs);
    FIELD_SET(*this, FIX::MarketValue);
    FIELD_SET(*this, FIX::OpenTradeEquity);
    FIELD_SET(*this, FIX::TotalAccountValue);
    FIELD_SET(*this, FIX::TotalEndingCashBalance);
    FIELD_SET(*this, FIX::UnrealizedPL);
    FIELD_SET(*this, FIX::SalesSeriesNumber);
    FIELD_SET(*this, FIX::LastRptRequested);
    FIELD_SET(*this, FIX::NoBalances);

    class NoBalances: public FIX::Group
    {
    public:
    NoBalances() : FIX::Group(20061,20063,FIX::message_order(
      20063,
      20064,
      20065,
      20066,
      20067,
      20068,
      20069,
      20070,
      20071,
      20072,
      0)) {}

      FIELD_SET(*this, FIX::BalanceCurrency);
      FIELD_SET(*this, FIX::BalanceEndingCashBalance);
      FIELD_SET(*this, FIX::BalanceTotalAccountValue);
      FIELD_SET(*this, FIX::BalanceOpenTradeEquity);
      FIELD_SET(*this, FIX::BalanceUnrealizedPL);
      FIELD_SET(*this, FIX::BalanceMarketValue);
      FIELD_SET(*this, FIX::BalanceCashExcess);
      FIELD_SET(*this, FIX::BalanceCollateralOnDeposit);
      FIELD_SET(*this, FIX::BalanceInitialMarginReqs);
      FIELD_SET(*this, FIX::BalanceMaintenanceMarginReqs);
    };

  };

}

#endif
