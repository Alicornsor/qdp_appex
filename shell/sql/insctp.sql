set NAMES utf8;
set @dt =NOW();
select instrumentid from t_oper_instrument where exchangeid="CFFEX" or exchangeid="SHFE" or exchangeid="DCE" or exchangeid="CZCE"
