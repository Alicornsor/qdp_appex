set linesize 9999
select t.sysnumber,t.brokerid,t.accountid,t.prebalance,t.available,t.frozenmargin,t.frozenfee,t.positionprofit from t_oper_investoraccount t order by t.sysnumber;
exit;
