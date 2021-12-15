set NAMES utf8;
set @dt =NOW();
select instrumentid from t_oper_instrument where IF((deliveryyear = (select year(@dt))),(deliverymonth <= IF((( select month(@dt)) + 14 ) >= 12 ,12,(select month(@dt))+14)),IF((deliveryyear = ((select year(@dt))+1)),deliverymonth <= IF((( select month(@dt)) + 2  ) <= 0 ,( select month(@dt)),(select month(@dt))+2),deliverymonth < 0))
and ( exchangeid="NYMEX" or exchangeid="BMD" or exchangeid="CBOT" or exchangeid="CME" or exchangeid="COMEX" or exchangeid="EUREX" or exchangeid="HKEX" or exchangeid="ICEU" or exchangeid="LIFFE" or exchangeid="SGX" or exchangeid="TOCOM" )
